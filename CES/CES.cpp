#include <string>
#include <iostream>
#include <utility>

#include "../include/Lexer.h"
#include "../include/RTResult.h"
#include "../include/Parser.h"

std::tuple<es::RunTimeResult*, es::Error*> run (const std::string& code, std::string filename) {

    auto* lexer = new es::Lexer(code, std::move(filename));
    es::LexResult lexer_res = lexer->lex();
    if (lexer_res.error) {
        return { nullptr, lexer_res.error };
    }
    std::cout << lexer_res.str() << std::endl;

    auto* parser = new es::Parser(*lexer_res.tokens);
    auto parse_res = parser->parse();
    if (parse_res->err) {
        return { nullptr, parse_res->err };
    }

    return { nullptr, nullptr };
}