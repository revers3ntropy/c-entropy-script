#include <tuple>
#include <iostream>

#include "../include/Parser.h"

es::ParseResult* es::Parser::parse() {
    if (tokens.empty() || !current || current->type == es::tt::END_OF_FILE) {
        return new ParseResult();
    }

    es::ParseResult* res = statements(true);

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

es::ParseResult* es::Parser::statements(bool use_array) {
    auto* res = new ParseResult();
    std::cout << current->str() << std::endl;
    std::cin.ignore();
    auto* start = current->start->clone();

    std::vector<es::Node> statements = {};

    statements.push_back(*res->register_parse_res(statement()));
    if (res->err) {
        return res;
    }

    bool more_statements = true;

    while (true) {
        int new_line_count = 0;

        while (current->type == es::tt::END_STATEMENT) {
            if (!advance(res)) goto end;
            new_line_count++;
        }
        if (new_line_count == 0) {
            more_statements = false;
        }

        if (!more_statements) {
            break;
        }
        es::Node* new_statement = res->try_register_parse_res(statement());
        if (!new_statement) {
            reverse(res->reverse_count);
            continue;
        }
        statements.push_back(*new_statement);
    }

end:

    clear_end_statements(res);

    es::Node* node = new N_statements(start, current->end, &statements);
    if (use_array) node = new N_array(start, current->end, &statements, true);

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
        if (current->type != es::tt::END_STATEMENT)
            expression = res->register_parse_res(expr());
        return res->success(new N_return(start, current->end, expression));

    } else if (current->matches(es::tt::KEYWORD, "yield")) {
        if (!advance(res)) return res->failure(UnexpectedEOF());
        Node* expression = new N_undefined(start, current->end);
        if (current->type != es::tt::END_STATEMENT)
            expression = res->register_parse_res(expr());
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
    auto* tok = current;

    switch (tok->type) {
        case es::tt::NUMBER:
            advance(res);
            return res->success(new es::N_number(tok->start, tok->end, tok->value));

        case es::tt::STRING:
            advance(res);
            return res->success(new es::N_string(tok->start, tok->end, tok->value));
    }

    return nullptr;
}

es::ParseResult *es::Parser::atom_identifier(es::ParseResult *res, es::Position *start, es::Token tok) {
    return nullptr;
}

es::ParseResult *es::Parser::power() {
    return nullptr;
}

es::ParseResult *es::Parser::factor() {
    return nullptr;
}

es::ParseResult *es::Parser::term() {
    return nullptr;
}

es::ParseResult *es::Parser::arithmetic_expr() {
    return nullptr;
}

es::ParseResult *es::Parser::comparison_expr() {
    return nullptr;
}

es::ParseResult *es::Parser::expr() {
    return nullptr;
}

es::ParseResult *es::Parser::bin_op() {
    return nullptr;
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
