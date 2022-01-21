#pragma once

#include <utility>

#include "Primitive.h"

namespace es {
    struct SymbolOptions {
        bool is_const;
        bool global;
        bool force_through_const;
    };

    struct Symbol {
        Primitive* value;
        std::string identifier;
        bool is_const;

        Symbol(Primitive* val, std::string id):
            value(val),
            identifier(std::move(id)),
            is_const(false)
        {}
    };
}