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

float Utils::Vectors::distance(sf::Vector2f& v1, sf::Vector2f& v2)
{
    sf::Vector2f distanceVector = v2 - v1;
    return Utils::Vectors::length(distanceVector);
}

void Utils::Vectors::pointTo(sf::Vector2f& v1, sf::Vector2f& v2)
{
    sf::Vector2f vectorToTarget = v2 - v1;
    Utils::Vectors::setAngle(v1, Utils::Vectors::getAngle(vectorToTarget));
    
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