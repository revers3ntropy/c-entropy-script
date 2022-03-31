#include <string>
#include <iostream>
#include <utility>

#include "../include/Lexer.h"
#include "../include/RTResult.h"
#include "../include/Parser.h"

es::RunTimeResult* run (const std::string& code, std::string filename, es::Context* context = new es::Context()) {
    auto final_res = new es::RunTimeResult();

    auto* lexer = new es::Lexer(code, std::move(filename));
    es::LexResult lexer_res = lexer->lex();
    if (lexer_res.error) {
        final_res->err = lexer_res.error;
        return final_res;
    }
    std::cout << lexer_res.str() << std::endl;

    auto* parser = new es::Parser(*lexer_res.tokens);
    auto parse_res = parser->parse();
    if (parse_res->err || !parse_res->node) {
        final_res->err = parse_res->err;
        return final_res;
    }
    std::cout << parse_res->str() << std::endl;

    auto interpret_res = parse_res->node->interpret(context);
    if (interpret_res->err) {
        final_res->err = interpret_res->err;
        return final_res;
    }
    std::cout << interpret_res->str() << std::endl;

    final_res->val = interpret_res->val;

    return final_res;
}