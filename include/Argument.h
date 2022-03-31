#pragma once

#include "Node.h"
#include "Primitive.h"

namespace es {
    struct UnInterpretedArgument {
        std::string name;
        Node* type;
    };

    struct InterpretedArgument {
        std::string name;
        Primitive* type;
    };
}