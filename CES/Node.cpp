#include "../include/Node.h"

es::RunTimeResult *es::Node::interpret() {
    return new RunTimeResult();
}

es::RunTimeResult* es::N_number::interpret_() {
    return new es::RunTimeResult();
}

es::RunTimeResult* es::N_access_variable::interpret_() {
    return new RunTimeResult();
}

es::RunTimeResult *es::N_break::interpret_() {
    return new RunTimeResult();
}

es::RunTimeResult *es::N_continue::interpret_() {
    return new RunTimeResult();
}

es::RunTimeResult* es::N_bin_op::interpret_() {
    return new RunTimeResult();
}

es::RunTimeResult *es::N_statements::interpret_() {
    return new RunTimeResult();
}

es::RunTimeResult *es::N_array::interpret_() {
    return new RunTimeResult();
}

es::RunTimeResult* es::N_undefined::interpret_() {
    return new RunTimeResult(new es::Undefined());
}

es::RunTimeResult *es::N_return::interpret_() {
    return expression->interpret();
}
es::RunTimeResult *es::N_yield::interpret_() {
    return expression->interpret();
}



