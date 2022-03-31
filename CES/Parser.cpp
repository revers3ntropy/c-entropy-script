#include <tuple>
#include <iostream>

#include "../include/Parser.h"

es::ParseResult* es::Parser::parse() {

    auto* res = new ParseResult();

    if (tok_idx != -1 || tokens.empty()) {
        return res;
    }

    advance();

    if (!current || current->type == es::tt::END_OF_FILE || tok_idx != 0) {
        return res;
    }

    res = statements(true);

    if (!res) {
        return new es::ParseResult {nullptr, UnexpectedEOF()};
    }

    if (!res->err && (!current || current->type != es::tt::END_OF_FILE)) {
        return res->failure(UnexpectedEOF());
    }

    return res;
}

std::tuple<es::UnInterpretedArgument*, es::Error*> es::Parser::parameter(es::ParseResult* res) {
    std::string name = current->value;
    es::Node* type = new es::N_access_variable(current->end, current->end, "any");

    consume(res, es::tt::IDENTIFIER);

    return {nullptr, nullptr};
}

es::ParseResult* es::Parser::statements(bool top_lvl) {
    auto* res = new ParseResult();
    auto* start = current->start->clone();

    auto* statements = new std::vector<es::Node*>();

    statements->push_back(res->register_parse_res(statement()));
    if (res->err) {
        return res;
    }

    while (true) {
        int new_line_count = 0;

        while (current->type == es::tt::END_STATEMENT) {
            if (!advance(res)) goto end;
            new_line_count++;
        }
        if (new_line_count == 0) {
            break;
        }

        es::Node* new_statement = res->try_register_parse_res(statement());
        if (!new_statement) {
            reverse(res->reverse_count);
            continue;
        }
        statements->push_back(new_statement);
    }

end:

    clear_end_statements(res);

    es::Node* node = new N_statements(start, current->end, statements, top_lvl);

    // final error check
    if (res->err) {
        return res;
    }
    return res->success(node);
}

es::ParseResult* es::Parser::statement() {
    auto* res = new ParseResult();
    Position* start = current->start->clone();

    if (current->matches(es::tt::KEYWORD, "return")) {
        if (!advance(res)) return res->failure(UnexpectedEOF());
        Node* expression = new N_undefined(start, current->end);
        if (current->type != es::tt::END_STATEMENT) {
            expression = res->register_parse_res(expr());
        }
        return res->success(new N_return(start, current->end, expression));

    } else if (current->matches(es::tt::KEYWORD, "yield")) {
        if (!advance(res)) return res->failure(UnexpectedEOF());
        Node* expression = new N_undefined(start, current->end);
        if (current->type != es::tt::END_STATEMENT) {
            expression = res->register_parse_res(expr());
        }
        return res->success(new N_yield(start, current->end, expression));

    } else if (current->matches(es::tt::KEYWORD, "break")) {
        if (!advance(res)) return res->failure(UnexpectedEOF());
        return res->success(new N_break(start, current->end));

    }  else if (current->matches(es::tt::KEYWORD, "continue")) {
        if (!advance(res)) return res->failure(UnexpectedEOF());
        return res->success(new N_continue(start, current->end));
    }

    auto* expression = res->register_parse_res(expr());
    if (res->err) return res;
    return res->success(expression);
}

es::ParseResult *es::Parser::atom() {
    auto* res = new ParseResult();
    Token* tok = current;

    if (tok->type == tt::NUMBER) {
        advance(res);
        return res->success(new es::N_number(tok->start, tok->end, tok->value));
    }
    if (tok->type == tt::STRING) {
        advance(res);
        return res->success(new es::N_string(tok->start, tok->end, tok->value));
    }
    std::cout << " null ptr from atom" << std::endl;
    return nullptr;
}

es::ParseResult *es::Parser::atom_identifier(es::ParseResult *res, es::Position *start, es::Token tok) {
    return nullptr;
}

es::ParseResult *es::Parser::power() {
    return bin_op(ParseResult::ATOM_EXPR, {tt::POW}, ParseResult::FACTOR_EXPR);
}

es::ParseResult *es::Parser::factor() {
    auto res = new ParseResult();
    auto tok = current;

    if (tok->type == tt::SUB || tok->type == tt::ADD) {
        advance(res);
        auto factor_ = res->register_parse_res(factor());
        if (res->err) return res;
        return res->success(new N_unary_op(tok->start, tok->end, factor_, tok));
    }

    return power();
}

es::ParseResult *es::Parser::term() {
    return bin_op(ParseResult::FACTOR_EXPR, {tt::MUL, tt::DIV});
}

es::ParseResult *es::Parser::arithmetic_expr() {
    return bin_op(ParseResult::TERM_EXPR, {tt::ADD, tt::SUB});
}

es::ParseResult *es::Parser::comparison_expr() {
    auto res = new ParseResult();

    if (current->type == tt::NOT) {
        auto op_tok = current;
        advance(res);
        auto node = res->register_parse_res(expr());
        if (res->err) return res;
        return res->success(new N_unary_op(op_tok->start, current->start, node, op_tok));
    }

    auto node = res->register_parse_res(bin_op(
            ParseResult::ARITH_EXPR,
            {tt::EQUALS, tt::NOT_EQUALS, tt::GT, tt::LTE, tt::LT}
    ));
    if (res->err) return res;
    return res->success(node);
}

es::ParseResult *es::Parser::expr() {
    auto* res = new es::ParseResult();

    clear_end_statements(res);

    if (current->type == tt::KEYWORD && (current->value == "let")) {
        return initiate_var();

    } else if (current->matches(tt::KEYWORD, "if")) {
        return if_expr();

    } else if (current->matches(tt::KEYWORD, "while")) {
        return while_expr();

    } else if (current->matches(tt::KEYWORD, "for")) {
        return for_expr();

    } else if (current->matches(tt::KEYWORD, "func")) {
        return func_expr();

    } else if (current->matches(tt::KEYWORD, "class")) {
        return class_expr();

    }
    auto* node = res->register_parse_res(bin_op(ParseResult::COMPARISON_EXPR, {es::AND, es::OR}));

    if (res->err) return res;

    return res->success(node);
}

es::ParseResult *es::Parser::bin_op(ParseResult::bin_op_funcs func_a, std::vector<tt> ops, ParseResult::bin_op_funcs func_b) {
    auto* res = new ParseResult();

    // other option is to pass through the function to be run, which is very painful
    // not a good solution
    ParseResult* a_res;
    switch (func_a) {
        case ParseResult::COMPARISON_EXPR:
            a_res = comparison_expr(); break;
        case ParseResult::ARITH_EXPR:
            a_res = arithmetic_expr(); break;
        case ParseResult::TERM_EXPR:
            a_res = term(); break;
        case ParseResult::FACTOR_EXPR:
            a_res = factor(); break;
        case ParseResult::ATOM_EXPR:
            a_res = atom(); break;
    }
    if (a_res == nullptr) return res;

    auto left = res->register_parse_res(a_res);
    if (res->err != nullptr) return res;

    while (std::find(ops.begin(), ops.end(), current->type) != ops.end()) {
        auto op_tok = current;
        advance(res);

        ParseResult* b_res;
        switch (func_b) {
            case ParseResult::COMPARISON_EXPR:
                b_res = comparison_expr(); break;
            case ParseResult::ARITH_EXPR:
                b_res = arithmetic_expr(); break;
            case ParseResult::TERM_EXPR:
                b_res = term(); break;
            case ParseResult::FACTOR_EXPR:
                b_res = factor(); break;
            case ParseResult::ATOM_EXPR:
                b_res = atom(); break;
        }
        if (b_res == nullptr) return res;

        auto right = res->register_parse_res(b_res);
        if (res->err != nullptr) return res;
        left = new N_bin_op(left->start, right->end, left, op_tok, right);
    }
    return res->success(left);
}

es::ParseResult *es::Parser::type_expr() {
    return nullptr;
}

es::ParseResult *es::Parser::func_call() {
    return nullptr;
}

es::ParseResult *es::Parser::index() {
    return nullptr;
}

es::ParseResult *es::Parser::initiate_var() {
    return nullptr;
}

es::ParseResult *es::Parser::context_expr() {
    return nullptr;
}

es::ParseResult *es::Parser::if_expr() {
    return nullptr;
}

es::ParseResult *es::Parser::while_expr() {
    return nullptr;
}

es::ParseResult *es::Parser::func_core_expr() {
    return nullptr;
}

es::ParseResult *es::Parser::func_expr() {
    return nullptr;
}

es::ParseResult *es::Parser::class_expr() {
    return nullptr;
}

es::ParseResult *es::Parser::for_expr() {
    return nullptr;
}

es::ParseResult *es::Parser::array_expr() {
    return nullptr;
}

es::ParseResult *es::Parser::object_literal_expr() {
    return nullptr;
}