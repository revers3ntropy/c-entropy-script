#include "../include/Primitive.h"

#include <utility>

es::Type* es::types::type = new es::Type();
es::Type* es::types::undefined = new es::Type();
es::Type* es::types::number = new es::Type();
es::Type* es::types::string = new es::Type();
es::Type* es::types::array = new es::Type();
es::Type* es::types::object = new es::Type();
es::Type* es::types::function = new es::Type();
es::Type* es::types::error = new es::Type();
es::Type* es::types::any = new es::Type();

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
    // set up the current type for the first type ot be defined: type
    if (es::types::type)
        type = es::types::type;
    else
        type = this;
}
