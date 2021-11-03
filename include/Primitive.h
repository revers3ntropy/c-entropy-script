#pragma once
#include <map>
#include <vector>
#include <string>

#include "Primitive.h"

namespace es {

    class Type;
    class Function;
    class Object;

    class Primitive {
    protected:
        std::map<std::string, Primitive>* properties;
    public:
        Type* type;
        explicit Primitive(Type* type_):
        type(type_), properties(new std::map<std::string, Primitive>()) {};
    };

    class Type : public Primitive {
        bool is_primitive;
        std::string name;
        Type* extends;
        std::vector<Function>* methods;
        Function* init;
        std::vector<Object>* instances;
    public:
        Type();
    };

    class Function : public Primitive {

    };

    class Object : public Primitive {

    };

}

