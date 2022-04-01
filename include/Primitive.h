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
    class Array;
    class Null;

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

        virtual inline opOverrideRes clone () {
            return {nullptr, OperatorError(nullptr, nullptr, "clone")};
        }

        virtual inline std::string str () {
            return "(no implementation of 'str')";
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
        Type* extends;
        std::vector<Function*>* methods;
        Function* constructor;
        std::vector<Object>* instances = {};
    public:
        std::string name;

        explicit Type (
            bool is_primitive=false,
            std::string name = "(anon)",
            std::vector<Function*>* methods={},
            Type* extends=nullptr,
            Function* constructor=nullptr
        );

        std::string str () override {
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
        Number() :
                Primitive(Type::types["number"]), value(new BigNumber()) {}

        explicit Number(std::string value) :
                Primitive(Type::types["number"]), value(new BigNumber(std::move(value))) {}

        explicit Number(es::BigNumber* value) :
                Primitive(Type::types["number"]), value(value) {}

        inline opOverrideRes clone() override {
            return {new Number(value), nullptr};
        }

        inline std::string str () override {
            return value->str();
        }

        opOverrideRes add(Primitive *p) override;
    };

    class String : public Primitive {
        std::string value;
    public:
        explicit String (std::string value)
        : Primitive(Type::types["string"]), value(std::move(value)) {}

        inline std::string str () override {
            return value;
        }
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

    class Boolean : public Primitive {
    public:
        bool value;
        explicit Boolean (bool value):
            Primitive(Type::types["boolean"]), value(value) {}

        inline std::string str () override {
            return std::to_string(value);
        }
    };

    class Array : public Primitive {
        std::vector<Primitive*>* value;
    public:
        explicit Array (std::vector<Primitive*>* value)
                : Primitive(Type::types["array"]), value(value) {}

        virtual inline std::string str () {
            std::string str = "[";
            for (auto element : *value) {
                str += element->str();
                str += ", ";
            }
            return str + "]";
        }
    };

    class Null : public Primitive {
    public:
        explicit Null ():
                Primitive(Type::types["undefined"]) {}
    };
}

