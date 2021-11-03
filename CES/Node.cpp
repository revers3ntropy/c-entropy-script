#include "../include/Node.h"

es::RunTimeResult *es::Node::interpret() {
    return nullptr;
}

es::RunTimeResult* es::N_number::interpret_() {
    return new es::RunTimeResult();
}

es::RunTimeResult *es::N_access_variable::interpret_() {
    return nullptr;
}
