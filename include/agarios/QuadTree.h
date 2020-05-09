#ifndef QTREE_H_
#define QTREE_H_

#include <vector>
#include <functional>
#include "SFML/Graphics.hpp"

class QuadTree
{

    private:
        QuadTree* topLeft;
        QuadTree* bottomLeft;
        QuadTree* bottomRight;
        QuadTree* topRight;

        std::vector<sf::Transformable*> objects;
        sf::Rect<float> boundary;
        unsigned int capacity;

    public:
        QuadTree(sf::Rect<float> const boundary, unsigned int const capacity);

    private:
        // split a leaf node into a 4 sub trees
        bool split();

    public:
        bool insert(sf::Transformable* const object);
        bool remove(sf::Transformable* const object);
        bool isLeaf() const;
        unsigned int count() const;

        // Return all objects that are in a node that intersects the body
        std::vector<sf::Transformable*> getObjectsIntersects(sf::CircleShape const body) const;
        void forEach(std::function<void(sf::Transformable* object)> what) const;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif