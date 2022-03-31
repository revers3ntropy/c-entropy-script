#pragma once
#include <map>
#include <utility>
#include <vector>
#include <string>
#include <tuple>

#include "Error.h"
#include "bigint.h"

namespace es {

    class Primitive;
    class Type;
    class Function;
    class Object;
    class Boolean;
    class String;

    using opOverrideRes = std::tuple<Primitive*, Error*>;

    class Primitive {
    protected:
        std::map<std::string, Primitive>* properties;
    public:
        Type* type;
        explicit Primitive(Type* type_):
            type(type_), properties(new std::map<std::string, Primitive>()) {};

        // to override
        virtual bool toBool () {
            return true;
        }

        virtual std::string toString () {
            return "";
        }

        virtual opOverrideRes add (Primitive* p) {
            return {nullptr, OperatorError(nullptr, nullptr, "+")};
        }
        virtual opOverrideRes subtract (Primitive* p) {
            return {nullptr, OperatorError(nullptr, nullptr, "-")};
        }
        virtual opOverrideRes multiply (Primitive* p) {
            return {nullptr, OperatorError(nullptr, nullptr, "*")};
        }
        virtual opOverrideRes divide (Primitive* p) {
            return {nullptr, OperatorError(nullptr, nullptr, "/")};
        }
        virtual opOverrideRes pow (Primitive* p) {
            return {nullptr, OperatorError(nullptr, nullptr, "^")};
        }
        virtual opOverrideRes eq (Primitive* p) {
            return {nullptr, OperatorError(nullptr, nullptr, "==")};
        }
        virtual opOverrideRes gt (Primitive* p) {
            return {nullptr, OperatorError(nullptr, nullptr, ">")};
        }
        virtual opOverrideRes lt (Primitive* p) {
            return {nullptr, OperatorError(nullptr, nullptr, "<")};
        }
        virtual opOverrideRes and_ (Primitive* p) {
            return {nullptr, OperatorError(nullptr, nullptr, "&&")};
        }
        virtual opOverrideRes or_ (Primitive* p) {
            return {nullptr, OperatorError(nullptr, nullptr, "||")};
        }
        virtual opOverrideRes setProperty (Primitive* p) {
            return {nullptr, OperatorError(nullptr, nullptr, "setProperty")};
        }
        virtual opOverrideRes call (Primitive* p) {
            return {nullptr, OperatorError(nullptr, nullptr, "()")};
        }
        virtual opOverrideRes getProperty (Primitive* p) {
            return {nullptr, OperatorError(nullptr, nullptr, "+")};
        }
    };

    class Type : public Primitive {
        bool is_primitive;
        std::string name;
        Type* extends;
        std::vector<Function*>* methods;
        Function* constructor;
        std::vector<Object>* instances = {};
    public:
        explicit Type (
            bool is_primitive=false,
            std::string name = "(anon)",
            std::vector<Function*>* methods={},
            Type* extends=nullptr,
            Function* constructor=nullptr
        );

        std::string toString () override {
            return "<Type: " + name + ">";
        }

        static std::map<std::string, Type*> types;
    };

    inline Type* type(const std::string& name) {
        if (Type::types.contains(name)) {
            return Type::types.at(name);
        }
        return nullptr;
    }

    class Number : public Primitive {
        es::BigNumber* value;
    public:
        Number ():
            Primitive(Type::types["number"]), value(new BigNumber()) {}
        explicit Number (std::string value):
            Primitive(Type::types["number"]), value(new BigNumber(std::move(value))) {}
        explicit Number (es::BigNumber* value):
            Primitive(Type::types["number"]), value(value) {}
    };

    class String : public Primitive {
        std::string value;
    public:
        explicit String (std::string value)
        : Primitive(Type::types["string"]), value(std::move(value)) {}
    };

    class Function : public Primitive {
    public:
        Function(): Primitive(Type::types["function"]) {}

        std::string name;
        // actually type InterpretedArgument*, not void* TODO: better solution
        void* arguments;
        Primitive* this_;
        Type* return_type;
    };

    class Object : public Primitive {
    public:
        Object(): Primitive(Type::types["object"]) {}
    };

    class Undefined : public Primitive {
    public:
        Undefined (): Primitive(Type::types["undefined"]) {}
    };

    class Boolean : public Primitive {
    public:
        bool value;
        explicit Boolean (bool value):
            Primitive(Type::types["boolean"]), value(value) {}
    };
}

