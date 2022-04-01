#pragma once

#include "Primitive.h"
#include "Error.h"

namespace es {
    struct RunTimeResult {
        Primitive* val;
        Error* err;
        Primitive* func_return;
        bool should_break;
        bool should_continue;

        explicit RunTimeResult(Primitive* val):
            val(val), err(nullptr), func_return(nullptr), should_break(false), should_continue(false) {};

        RunTimeResult():
            val(nullptr), err(nullptr), func_return(nullptr), should_break(false), should_continue(false) {};

        [[nodiscard]] std::string str() const{
            if (err) {
                return "<RunTimeResult: " + err->str() + ">";
            }
            if (val) {
                return "<RunTimeResult: " + val->str() + ">";
            }
            return "<RunTimeResult: empty>";

        }
    };
}