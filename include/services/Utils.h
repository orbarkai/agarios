#include <vector>
#include <functional>

namespace Utils
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

} // namespace Utils
