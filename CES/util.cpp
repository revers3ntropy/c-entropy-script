#include <vector>
#include <string>

#include "../include/util.h"

std::vector<std::string>* es::util::split(const char *str, char c) {
    // https://stackoverflow.com/questions/53849/how-do-i-tokenize-a-string-in-c
    auto* result = new std::vector<std::string>();
    do {
        const char *begin = str;
        while(*str != c && *str)
            str++;
        result->emplace_back(begin, str);
    } while (0 != *str++);
    return result;
}