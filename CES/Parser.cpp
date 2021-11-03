#include <tuple>

#include "../include/Parser.h"

es::ParseResult* es::Parser::parse() {
    if (tokens.empty() || !current || current->type == es::tt::END_OF_FILE)
        return new ParseResult();

    auto* res = statements(true);

    if (!res->err && (!current || current->type != es::tt::END_OF_FILE))
        return res->failure(UnexpectedEOF());

    return res;
}

std::tuple<es::UnInterpretedArgument*, es::Error*> es::Parser::parameter(es::ParseResult* res) {
    std::string name = current->value;
    es::Node* type = new es::N_access_variable(current->end, current->end, "any");

    consume(res, es::tt::IDENTIFIER);

    return {nullptr, nullptr};
}

es::ParseResult *es::Parser::statements(bool use_array) {
    return nullptr;
}

es::ParseResult *es::Parser::statement() {
    return nullptr;
}

es::ParseResult *es::Parser::atom() {
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
