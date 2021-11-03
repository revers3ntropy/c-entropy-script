#pragma once

namespace es::util {
    template <class T>
    void insert (std::vector<T>* vector, T* item, int idx=0) {
        if (idx >= vector->size()) {
            vector->push_back(*item);
            return;
        }
        vector->insert(vector->begin() + idx, *item);
    }
}