#include <string>

#include "../include/Token.h"

std::string es::str_tt(es::tt t) {
    switch (t) {
        case END_OF_FILE: return "EOF";
        case NUMBER: return "NUMBER";
        case STRING: return "STRING";
        case END_STATEMENT: return ";";
        case IDENTIFIER: return "IDENTIFIER";
        case KEYWORD: return "KEYWORD";
        case COMMA: return ",";
        case ASSIGN: return ":=";
        case ADD: return "+";
        case SUB: return "-";
        case DIV: return "/";
        case MUL: return "*";
        case POW: return "^";
        case O_PAREN: return "(";
        case C_PAREN: return ")";
        case O_BRACES: return "{";
        case C_BRACES: return "}";
        case O_SQUARE: return "[";
        case C_SQUARE: return "]";
        case EQUALS: return "==";
        case NOT_EQUALS: return "!=";
        case NOT: return "!";
        case LT: return "<";
        case GT: return ">";
        case LTE: return "<=";
        case GTE: return ">=";
        case DOT: return ".";
        case COLON: return ":";
        case ADD_ASSIGN: return "+=";
        case SUB_ASSIGN: return "-=";
        case DIV_ASSIGN: return "/=";
        case MUL_ASSIGN: return "*=";
        case AND: return "&&";
        case OR: return "||";
    }
    return "Unknown";
};

bool es::Token::matches(es::tt t, const std::string& v) const {
    return t == type && v == value;
}
