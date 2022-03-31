#include "../include/Node.h"

es::RunTimeResult *es::Node::interpret(es::Context* context) {
    RunTimeResult* res = interpret_(context);

    if (res->err && res->err->start == nullptr)
        res->err->start = start;
    if (res->err && res->err->end == nullptr)
        res->err->end = start;

    return res;
}

es::RunTimeResult* es::N_number::interpret_(es::Context* context) {
    std::cout << "number" << std::endl;
    return new es::RunTimeResult(new es::Number(value));
}

es::RunTimeResult *es::N_string::interpret_(es::Context* context) {
    return new RunTimeResult(new es::String(value));
}

es::RunTimeResult* es::N_access_variable::interpret_(es::Context* context) {
    auto res = new RunTimeResult();
    auto [primitive_val, err] = context->get(value);
    if (err) {
        res->err = err;
    } else {
        res->val = primitive_val;
    }
    return res;
}

es::RunTimeResult *es::N_break::interpret_(es::Context* context) {
    auto* res = new RunTimeResult();
    res->should_break = true;
    return res;
}

es::RunTimeResult *es::N_continue::interpret_(es::Context* context) {
    auto* res = new RunTimeResult();
    res->should_continue = true;
    return res;
}

es::RunTimeResult* es::N_bin_op::interpret_(es::Context* context) {
    auto* res = new es::RunTimeResult();

    auto* left_res = left->interpret(context);
    if (left_res->err) return left_res;
    if (!left_res->val) {
        res->err = new Error(start, op_tok->start,"TypeError",
                             "Left side of operand '" + es::str_tt(op_tok->type) + "' Cannot be void*");
        return res;
    }

    auto* right_res = right->interpret(context);
    if (right_res->err) return right_res;
    if (!right_res->val) {
        res->err = new Error(op_tok->end, end,"TypeError",
                             "Right side of operand '" + es::str_tt(op_tok->type) + "' Cannot be void*");
        return res;
    }

    auto* l = left_res->val;
    auto* r = right_res->val;

    auto register_res = [&](std::tuple<Primitive*, Error*> op_res) {
        auto [val, err] = op_res;
        if (err) res->err = err;
        if (val) res->val = val;
        // keep everything on one line below: allows returning of this func
        return res;
    };

    auto register_error = [&](std::tuple<Primitive*, Error*> op_res) {
        auto [val, err] = op_res;
        if (err) {
            res->err = err;
            return res;
        }
        return (RunTimeResult*)nullptr;
    };

    switch (op_tok->type) {
        case es::tt::LTE: {
            auto [lt_val, lt_error] = l->lt(r);
            if (lt_error) {
                res->err = lt_error;
                return res;
            }
            auto [eq_val, eq_err] = l->eq(r);
            if (eq_err) {
                res->err = eq_err;
                return res;
            }
            return register_res(lt_val->or_(eq_val));
        } case es::tt::GTE: {
            auto [gt_val, gt_error] = l->gt(r);
            if (gt_error) {
                res->err = gt_error;
                return res;
            }
            auto [eq_val, eq_err] = l->eq(r);
            if (eq_err) {
                res->err = eq_err;
                return res;
            }
            return register_res(gt_val->or_(eq_val));
        } case es::tt::NOT_EQUALS: {
            auto [val, err] = l->eq(r);
            if (err) {
                res->err = err;
                return res;
            }
            res->val = new Boolean(!(bool)val);

        } case es::tt::ADD:
            return register_res(l->add(r));
        case es::tt::SUB:
            return register_res(l->subtract(r));
        case es::tt::MUL:
            return register_res(l->multiply(r));
        case es::tt::DIV:
            return register_res(l->divide(r));
        case es::tt::POW:
            return register_res(l->pow(r));
        case es::tt::EQUALS:
            return register_res(l->eq(r));
        case es::tt::LT:
            return register_res(l->lt(r));
        case es::tt::GT:
            return register_res(l->gt(r));
        case es::tt::AND:
            return register_res(l->and_(r));
        case es::tt::OR:
            return register_res(l->or_(r));
        default:
            res->err = SyntaxError(start, end, "Invalid Binary Operator '" + es::str_tt(op_tok->type) + "'");
            return res;
    }
}

es::RunTimeResult *es::N_statements::interpret_(es::Context* context) {
    return new RunTimeResult();
}

es::RunTimeResult *es::N_array::interpret_(es::Context* context) {
    return new RunTimeResult();
}

es::RunTimeResult* es::N_undefined::interpret_(es::Context* context) {
    return new RunTimeResult(new es::Undefined());
}

es::RunTimeResult *es::N_return::interpret_(es::Context* context) {
    return expression->interpret(context);
}
es::RunTimeResult *es::N_yield::interpret_(es::Context* context) {
    return expression->interpret(context);
}

es::RunTimeResult *es::N_unary_op::interpret_(es::Context *context) {
    RunTimeResult* res = operand->interpret(context);
    if (res->err) return res;

    switch (op_tok->type) {
        case es::tt::NOT:
            res->val = new Boolean(!(bool)res->val);
            return res;

        case es::tt::ADD:
            if (res->val->type != es::Type::types["number"])
                res->err = TypeError(start, end, "Number", res->val->type->toString(), "");
            return res;

        case es::tt::SUB: {
            if (res->val->type != es::Type::types["number"])
                res->err = TypeError(start, end, "Number", res->val->type->toString(), "");
            auto [result, err] = (new Number())->subtract(res->val);
            res->err = err;
            res->val = result;
            return res;

        } default:
            res->err = SyntaxError(start, end, "Invalid Unary operator: " + str_tt(op_tok->type));
            return res;
    }
}
