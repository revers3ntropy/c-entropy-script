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

    template<typename Base, typename T>
    inline bool instanceof(const T *ptr) {
        return dynamic_cast<const Base*>(ptr) != nullptr;
    }

    std::vector<std::string>* split(const std::string& str, char by) {
        auto* out = new std::vector<std::string>();
        std::string current;

        for (char char_ : str) {
            if (char_ == by) {
                out->push_back(current);
                current.clear();
                continue;
            }
            current += char_;
        }

        return out;
    }
}