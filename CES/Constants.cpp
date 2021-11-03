#include <string>
#include <vector>
#include <map>

#include "../include/Constants.h"

std::string es::SINGLE_LINE_COMMENT = "//";
std::string es::DIGITS = "0123456789";

std::string es::NUM_CHARS = "0123456789._";
std::string es::IDENTIFIER_CHARS = "_$abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

std::map<char, std::string> es::STR_ESCAPES = {
    {'n', "\n"},
    {'b', "\b"},
    {'f', "\f"},
    {'r', "\r"},
    {'v', "\v"},
    {'t', "\t"}
};

std::vector<std::string> es::KEYWORDS = {
        "var",
        "global",
        "let",
        "const",
        "if",
        "else",
        "while",
        "for",
        "in",
        "continue",
        "break",
        "func",
        "return",
        "yield",
        "class",
        "extends"
};

std::map<std::string, es::tt> es::SINGLE_CHAR_TOKENS = {
    {"*", es::tt::MUL},
    {"/", es::tt::DIV},
    {"+", es::tt::ADD},
    {"-", es::tt::SUB},
    {"(", es::tt::O_BRACES},
    {")", es::tt::C_BRACES},
    {"^", es::tt::POW},
    {"{", es::tt::O_BRACES},
    {"}", es::tt::C_BRACES},
    {",", es::tt::COMMA},
    {"[", es::tt::O_SQUARE},
    {"]", es::tt::C_SQUARE},
    {";", es::tt::END_STATEMENT},
    {":", es::tt::COLON},
    {".", es::tt::DOT},
    {"=", es::tt::ASSIGN},
    {">", es::tt::GT},
    {"<", es::tt::LT},
    {"!", es::tt::NOT},
};

std::map<std::string, es::tt> es::DOUBLE_CHAR_TOKENS = {
    {"==", es::tt::EQUALS},
    {"!=", es::tt::NOT_EQUALS},
    {">=", es::tt::GTE},
    {"<=", es::tt::LTE},
    {"+=", es::tt::ADD_ASSIGN},
    {"-=", es::tt::SUB_ASSIGN},
    {"*=", es::tt::MUL_ASSIGN},
    {"/=", es::tt::DIV_ASSIGN},
    {"&&", es::tt::AND},
    {"||", es::tt::OR},
};

std::map<std::string, es::tt> es::TRIPLE_CHAR_TOKENS = {};