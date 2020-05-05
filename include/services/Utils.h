#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <functional>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

#define NBYTES 16

namespace Utils
{
    namespace Arrays
    {
        template<typename T>
        std::vector<T> filter(std::vector<T> arr, std::function<bool(const T&)> predicate) {
            std::vector<T> filtered;
            copy_if(arr.begin(), arr.end(), back_inserter(filtered), predicate);
            return filtered;
        };

        template<typename T, typename K>
        std::vector<K> map(std::vector<T> arr, std::function<K (const T&)> predicate) {
            std::vector<K> maped;
            for (int i = 0; i < arr.size(); i++) {
                maped.push_back(predicate(arr[i]));
            }
            return maped;
        };

        template<typename T>
        bool includes(std::vector<T> arr, T key) {
            for (int i = 0; i < arr.size(); i++) {
                if (arr[i] == key) return true;
            }
            return false;
        }
    } // namespace Arrays

    namespace Vectors
    {

        void setAngle(sf::Vector2f& v, float a);
        void setAngleDeg(sf::Vector2f& v, float a);	
        float getAngle(sf::Vector2f& v);
        float getAngleDeg(sf::Vector2f& v);
        void rotateBy(sf::Vector2f& v, float l);
        
        void normalize(sf::Vector2f& v);
        void setLength(sf::Vector2f& v, float l);
        float length(sf::Vector2f& v);
        void limit(sf::Vector2f& v, float l);
        
        float dot(sf::Vector2f& v1, sf::Vector2f& v2);
        float cross(sf::Vector2f& v1, sf::Vector2f& v2);
        float distance(sf::Vector2f& v1, sf::Vector2f& v2);
        void pointTo(sf::Vector2f& v1, sf::Vector2f& v2);

    } // namespace Vectors

    namespace Math
    {
        float randomFloat(float const min, float const max);
    } // namespace Math

    namespace Colors
    {
        sf::Color hsv(int hue, float sat, float val);
        sf::Color randomColor();
    } // namespace Math

    std::string UUID();

} // namespace Utils

#endif