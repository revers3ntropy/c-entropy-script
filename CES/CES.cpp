#include <string>
#include <iostream>
#include <utility>

#include "../include/Lexer.h"
#include "../include/RTResult.h"

std::tuple<es::RunTimeResult*, es::Error*> run (const std::string& code, std::string filename) {
    auto* lexer = new es::Lexer(code, std::move(filename));
    es::LexResult lexer_res = lexer->lex();
    std::cout << lexer_res.str() << std::endl;
    return { nullptr, nullptr };
}