#pragma once

namespace es {
    enum tt {
        END_OF_FILE,
        END_STATEMENT,

        IDENTIFIER,
        KEYWORD,

        COMMA,
        DOT,
        COLON,

        NUMBER,
        STRING,

        ASSIGN,
        ADD_ASSIGN,
        SUB_ASSIGN,
        DIV_ASSIGN,
        MUL_ASSIGN,

        ADD,
        SUB,
        DIV,
        MUL,
        POW,
        O_PAREN,
        C_PAREN,
        O_BRACES,
        C_BRACES,
        O_SQUARE,
        C_SQUARE,

        EQUALS,
        NOT_EQUALS,
        NOT,
        LT,
        GT,
        LTE,
        GTE,
        AND,
        OR
    };

    extern std::string SINGLE_LINE_COMMENT;
    extern std::string DIGITS;
    extern std::string NUM_CHARS;
    extern std::string IDENTIFIER_CHARS;
    extern std::map<char, std::string> STR_ESCAPES;
    extern std::vector<std::string> KEYWORDS;
    extern std::map<std::string, tt> SINGLE_CHAR_TOKENS;
    extern std::map<std::string, tt> DOUBLE_CHAR_TOKENS;
    extern std::map<std::string, tt> TRIPLE_CHAR_TOKENS;
};
