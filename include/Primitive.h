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

    struct types {
        static Type* type;
        static Type* undefined;
        static Type* number;
        static Type* string;
        static Type* array;
        static Type* object;
        static Type* function;
        static Type* error;
        static Type* any;
    };

    class Function : public Primitive {
    public:
        Function(): Primitive(types::function) {}

        std::string name;
        // actually type InterpretedArgument*, not void*
        // TODO: better solution
        void* arguments;
        Primitive* this_;
        Type* return_type;
    };

    class Object : public Primitive {
    public:
        Object(): Primitive(types::object){}
    };

    class Undefined : public Primitive {
    public:
        Undefined (): Primitive(types::undefined) {}
    };
}

