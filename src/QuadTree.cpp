#include "agarios/QuadTree.h"
#include "services/Utils.h"
#include "services/Console.h"


QuadTree::QuadTree(sf::Rect<float> const boundary,
                   unsigned int const capacity) : 
                   boundary(boundary),
                   capacity(capacity),
                   objects({}),
                   topRight(NULL), bottomRight(NULL), bottomLeft(NULL), topLeft(NULL) { }

bool QuadTree::split() {
    if (!this->isLeaf() || this->objects.empty()) {
        return false;
    }

    sf::Vector2f size = {this->boundary.width / 2, this->boundary.height / 2};
    sf::Rect<float> topRightRect =    sf::Rect<float>({this->boundary.left + (this->boundary.width / 2), this->boundary.top},                               size);
    sf::Rect<float> bottomRightRect = sf::Rect<float>({this->boundary.left + (this->boundary.width / 2), this->boundary.top + (this->boundary.height / 2)}, size);
    sf::Rect<float> bottomLeftRect =  sf::Rect<float>({this->boundary.left,                              this->boundary.top + (this->boundary.height / 2)}, size);
    sf::Rect<float> topLeftRect =     sf::Rect<float>({this->boundary.left,                              this->boundary.top},                               size);

    this->topRight = new QuadTree(topRightRect, this->capacity);
    this->bottomRight = new QuadTree(bottomRightRect, this->capacity);
    this->bottomLeft = new QuadTree(bottomLeftRect, this->capacity);
    this->topLeft = new QuadTree(topLeftRect, this->capacity);

    while(!this->objects.empty()) {
        sf::Transformable* object = this->objects[this->objects.size() - 1];

        if (!this->topRight->insert(object) && 
            !this->bottomRight->insert(object) && 
            !this->bottomLeft->insert(object) && 
            !this->topLeft->insert(object)) {
            return false;
        }

        this->objects.pop_back();
    }

    return true;
}

bool QuadTree::remove(sf::Transformable* const object) {
    if (this->isLeaf()) {
        if (Utils::Arrays::includes<sf::Transformable*>(this->objects, object)) {
            for (int i = 0; i < this->objects.size(); i++) {
                if (this->objects[i] == object) {
                    this->objects.erase(this->objects.begin() + i);
                    return true;
                }
            }
        }

        // the object is not in the objects vector
        return false;
    }
 
    if (!this->topRight->remove(object) && 
        !this->bottomRight->remove(object) && 
        !this->bottomLeft->remove(object) && 
        !this->topLeft->remove(object)) {
        // the object is not in the sub trees 
        return false;
    }

    // shrink
    if (this->count() <= this->capacity) {
        this->objects.insert(this->objects.end(), this->topRight->objects.begin(),    this->topRight->objects.end());
        this->objects.insert(this->objects.end(), this->bottomRight->objects.begin(), this->bottomRight->objects.end());
        this->objects.insert(this->objects.end(), this->bottomLeft->objects.begin(),  this->bottomLeft->objects.end());
        this->objects.insert(this->objects.end(), this->topLeft->objects.begin(),     this->topLeft->objects.end());

        delete this->topRight;
        delete this->bottomRight;
        delete this->bottomLeft;
        delete this->topLeft;

        topRight = NULL;
        bottomRight = NULL;
        bottomLeft = NULL;
        topLeft = NULL;
    }

    return true;
}

bool QuadTree::insert(sf::Transformable* const object) {
    if (!this->boundary.contains(object->getPosition())) {
        return false;
    }

    if (this->isLeaf()) {
        if (this->objects.size() < this->capacity) {
            this->objects.push_back(object);
            return true;
        }

        if (!this->split()) {
            return false;
        }
    }

     if (!this->topRight->insert(object) && 
         !this->bottomRight->insert(object) && 
         !this->bottomLeft->insert(object) && 
         !this->topLeft->insert(object)) {
        // the object is not in the sub trees 
        return false;
    }

    return true;
}

bool QuadTree::isLeaf() const {
    return !(this->topRight);
}

unsigned int QuadTree::count() const {
    if (this->isLeaf()) {
        return this->objects.size();
    }

    return this->topLeft->count() + 
           this->bottomRight->count() + 
           this->bottomLeft->count() + 
           this->topLeft->count();
}

std::vector<sf::Transformable*> QuadTree::getObjectsIntersects(sf::CircleShape const body) const {
    if (!Utils::Collisions::circleRectangle(body, this->boundary)) {
        return {};
    }

    if (this->isLeaf()) {
        return this->objects;
    }

    std::vector<sf::Transformable*> intersects = {};

    std::vector<sf::Transformable*> topRightIntersects = this->topRight->getObjectsIntersects(body);
    std::vector<sf::Transformable*> bottomRightIntersects = this->bottomRight->getObjectsIntersects(body);
    std::vector<sf::Transformable*> bottomLeftIntersects = this->bottomLeft->getObjectsIntersects(body);
    std::vector<sf::Transformable*> topLeftIntersects = this->topLeft->getObjectsIntersects(body);

    intersects.insert(intersects.end(), topRightIntersects.begin(),    topRightIntersects.end());
    intersects.insert(intersects.end(), bottomRightIntersects.begin(), bottomRightIntersects.end());
    intersects.insert(intersects.end(), bottomLeftIntersects.begin(),  bottomLeftIntersects.end());
    intersects.insert(intersects.end(), topLeftIntersects.begin(),     topLeftIntersects.end());

    return intersects;
}

void QuadTree::forEach(std::function<void(sf::Transformable* object)> what) const {
    if (this->isLeaf()) {
        for (int i = 0; i < this->objects.size(); i++) {
            what(this->objects[i]);
        }
    } else {
        this->topRight->forEach(what);
        this->bottomRight->forEach(what);
        this->bottomLeft->forEach(what);
        this->topLeft->forEach(what);
    }
}

void QuadTree::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (this->isLeaf()) {
        sf::RectangleShape rectShape = sf::RectangleShape({this->boundary.width, this->boundary.height});
        rectShape.setPosition({this->boundary.left, this->boundary.top});
        rectShape.setFillColor(sf::Color::Transparent);
        rectShape.setOutlineColor(sf::Color::Red);
        rectShape.setOutlineThickness(0.05 * (float)(1 + ((int)target.getView().getSize().x / 70)));
        target.draw(rectShape, states);
    } else {
        this->topRight->draw(target, states);
        this->bottomRight->draw(target, states);
        this->bottomLeft->draw(target, states);
        this->topLeft->draw(target, states);
    }
}
