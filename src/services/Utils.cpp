#include <math.h>
#include <sstream>
#include "services/Utils.h"

void Utils::Vectors::normalize(sf::Vector2f& v)
{
    float length = Utils::Vectors::length(v);
    if (length == 0) v.x = 1;
    else v /= length;
}

float Utils::Vectors::length(sf::Vector2f& v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

void Utils::Vectors::limit(sf::Vector2f& v, float l) {
    if (Utils::Vectors::length(v) > l) Utils::Vectors::setLength(v, l);
}

void Utils::Vectors::setLength(sf::Vector2f& v, float l)
{
    Utils::Vectors::normalize(v);
    v *= l;
}

float Utils::Vectors::getAngle(sf::Vector2f& v)
{
    return atan2(v.y, v.x);
}

float Utils::Vectors::getAngleDeg(sf::Vector2f& v)
{
    return atan2(v.y, v.x) * 180.0/M_PI;
}

void Utils::Vectors::setAngle(sf::Vector2f& v, float a)
{
    float length = Utils::Vectors::length(v);
    v.x = cos(a) * length;
    v.y = sin(a) * length;
    
}

void Utils::Vectors::setAngleDeg(sf::Vector2f& v, float a)
{
    Utils::Vectors::setAngle(v, a * (M_PI/180.0));
    
}

void Utils::Vectors::rotateBy(sf::Vector2f& v, float l)
{
    float angle = Utils::Vectors::getAngle(v);
    float length = Utils::Vectors::length(v);
    v.x = cos(l + angle) * length;
    v.y = sin(l + angle) * length;
    
}

float Utils::Vectors::dot(sf::Vector2f& v1, sf::Vector2f& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

float Utils::Vectors::cross(sf::Vector2f& v1, sf::Vector2f& v2)
{
    return (v1.x * v2.y) - (v1.y * v2.x);
}

void Utils::Vectors::mult(sf::Vector2f& v1, sf::Vector2f& v2)
{
    v1.x *= v2.x;
    v1.y *= v2.y;
}

float Utils::Vectors::distance(sf::Vector2f& v1, sf::Vector2f& v2)
{
    sf::Vector2f distanceVector = v2 - v1;
    return Utils::Vectors::length(distanceVector);
}

sf::Vector2f Utils::Vectors::randomVector() {
    return sf::Vector2f(Utils::Math::randomFloat(0, 1), Utils::Math::randomFloat(0, 1));
}

void Utils::Vectors::pointTo(sf::Vector2f& v1, sf::Vector2f& v2)
{
    sf::Vector2f vectorToTarget = v2 - v1;
    Utils::Vectors::setAngle(v1, Utils::Vectors::getAngle(vectorToTarget));
    
}

float Utils::Math::randomFloat(float const min = 0, float const max = 1) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/(max-min)));
}

sf::Color Utils::Colors::hsv(int hue, float sat, float val) {
    hue %= 360;
    while (hue < 0) hue += 360;

    if (sat < 0.f) sat = 0.f;
    if (sat > 1.f) sat = 1.f;

    if (val < 0.f) val = 0.f;
    if (val > 1.f) val = 1.f;

    int h = hue / 60;
    float f = float(hue) / 60 - h;
    float p = val*(1.f - sat);
    float q = val*(1.f - sat * f);
    float t = val*(1.f - sat * (1 - f));

    switch (h)
    {
        default:
        case 0:
        case 6: return sf::Color(val * 255, t * 255, p * 255);
        case 1: return sf::Color(q * 255, val * 255, p * 255);
        case 2: return sf::Color(p * 255, val * 255, t * 255);
        case 3: return sf::Color(p * 255, q * 255, val * 255);
        case 4: return sf::Color(t * 255, p * 255, val * 255);
        case 5: return sf::Color(val * 255, p * 255, q * 255);
    }
}

sf::Color Utils::Colors::randomColor() {
    return Utils::Colors::hsv(rand(), 1.0, 1.0);
}

std::string Utils::UUID() {

    int abData[NBYTES];

    for (int i = 0; i < NBYTES; i++) {
        abData[i] = rand() % 255;
    }
    abData[6] = 0x40 | (abData[6] & 0xf);
    abData[8] = 0x80 | (abData[8] & 0x3f);

    std::stringstream hexStream;

    for (int i = 0; i < NBYTES; i++) {
        hexStream << std::hex <<  abData[i];
    }

    std::string uuid = hexStream.str();

    uuid.insert(8, "-");
    uuid.insert(13, "-");
    uuid.insert(18, "-");
    uuid.insert(23, "-");

    return uuid;
}  

bool Utils::Collisions::circleRectangle(sf::CircleShape circle, sf::Rect<float> rect) {
    sf::Vector2f circlePos = circle.getPosition();

    float closestX = std::clamp<float>(circlePos.x, rect.left, rect.left + rect.width);
    float closestY = std::clamp<float>(circlePos.y, rect.top,  rect.top  + rect.height);

    sf::Vector2f closestPos = {closestX, closestY};

    return Utils::Vectors::distance(circlePos, closestPos) < circle.getRadius();
}