#pragma once
#include <string>
#include <vector>

#include "Token.h"
#include "Error.h"

namespace es {

    struct  LexResult {
        Error* error;
        std::vector<es::Token>* tokens;

        std::string str() {
            std::string out = "<LexResult: ";
            if (error)
                out += error->str();

            if (tokens) {
                out += "[\n";
                for (int i = 0; i < tokens->size(); i++) {
                    out += "    ";
                    out += (*tokens)[i].str();
                    // only add a ', ' if this is not the last element in the vector
                    if (i < tokens->size()-1)
                        out += ", \n";
                }
                out += "\n]";
            }

            return out + ">";
        }
    };

    class Lexer {
        std::string text;
        char current_char;
        std::string current_char_str;
        Position* position;
        std::vector<Token>* tokens;

    public:
        Lexer (std::string msg, std::string filename);
        LexResult lex();

    private:
        void advance();
        void line_comment();
        void add_eof();
        bool can_advance();
        Token* make_number();
        Token* make_identifier();
        std::tuple<Token*, Error*> unknownToken();
        std::tuple<Token*, Error*> make_string();
    };
}


