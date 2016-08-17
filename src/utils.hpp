#include <vector>


template <typename T>
inline void fill(std::vector<T> &vector, int size) {
    vector.reserve(size);
    vector.resize(size);
}
