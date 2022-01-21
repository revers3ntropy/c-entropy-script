#pragma once

#include <vector>

namespace es::util {
    template <class T>
    void insert (std::vector<T>* vector, T* item, int idx=0) {
        if (idx >= vector->size()) {
            vector->push_back(*item);
            return;
        }
        vector->insert(vector->begin() + idx, *item);
    }

    template<typename Base, typename T>
    inline bool instanceof(const T *ptr) {
        return dynamic_cast<const Base*>(ptr) != nullptr;
    }

    std::vector<std::string>* split(const char *str, char c = ' ');
}