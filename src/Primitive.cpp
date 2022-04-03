#include "../include/Primitive.h"
#include "../include/RTResult.h"

#include <utility>

std::map<std::string, es::Type*> es::Type::types = {
    {"type", new es::Type() },
    {"undefined", new es::Type() },
    {"number", new es::Type() },
    {"string", new es::Type() },
    {"array", new es::Type() },
    {"object", new es::Type() },
    {"function", new es::Type() },
    {"error", new es::Type() },
    {"any", new es::Type() }
};

es::Type::Type(
    bool is_primitive,
    std::string name,
    std::vector<Function *> *methods,
    es::Type *extends,
    es::Function *constructor
) : Primitive(nullptr),
    is_primitive(is_primitive),
    name(std::move(name)),
    methods(methods),
    extends(extends),
    constructor(constructor)
{
    // set up the current type for the first type to be defined: type
    if (es::Type::types.contains("type")) {
        type = es::type("type");
    } else {
        type = this;
    }
}

es::opOverrideRes es::Number::add(es::Primitive* p) {
    auto* asNum = dynamic_cast<Number*>(p);
    if (asNum == nullptr) {
        return {nullptr, TypeError(nullptr, nullptr, "Num", p->type->name)};
    }
    return {new Number(*value + asNum->value), nullptr};
}

es::opOverrideRes es::Number::subtract(es::Primitive* p) {
    auto* asNum = dynamic_cast<Number*>(p);
    if (asNum == nullptr) {
        return {nullptr, TypeError(nullptr, nullptr, "Num", p->type->name)};
    }
    return {new Number(*value - asNum->value), nullptr};
}

es::opOverrideRes es::Number::multiply(es::Primitive* p) {
    auto* asNum = dynamic_cast<Number*>(p);
    if (asNum == nullptr) {
        return {nullptr, TypeError(nullptr, nullptr, "Num", p->type->name)};
    }
    return {new Number(*value * asNum->value), nullptr};
}

es::opOverrideRes es::Number::divide(es::Primitive* p) {
    auto* asNum = dynamic_cast<Number*>(p);
    if (asNum == nullptr) {
        return {nullptr, TypeError(nullptr, nullptr, "Num", p->type->name)};
    }
    return {new Number(*value / asNum->value), nullptr};
}