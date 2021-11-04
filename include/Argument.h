#pragma once

#include "Node.h"
#include "Primitive.h"

namespace es {
    struct UnInterpretedArgument {
        std::string name;
        es::Node* type;
    };

    struct InterpretedArgument {
        std::string name;
        es::Primitive* type;
    };
}