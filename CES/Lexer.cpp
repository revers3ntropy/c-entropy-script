#include <iostream>
#include <utility>
#include <vector>

#include "../include/Lexer.h"

es::Lexer::Lexer(std::string msg, std::string filename):
    text(std::move(msg)),
    position(new es::Position(-1, 0, -1, std::move(filename))
) {
    tokens = new std::vector<es::Token>();
    current_char = (char)0;
    advance();
}

es::LexResult es::Lexer::lex() {
    if (text.empty()) {
        add_eof();
        return {nullptr, tokens};
    }

    while (can_advance()) {

        if (isspace(current_char)) {
            advance();
        } else if (isdigit(current_char)) {
            tokens->push_back(*make_number());

        } else if (
            current_char == es::SINGLE_LINE_COMMENT[0] &&
            position->idx < text.length()-1 &&
            text[position->idx + 1] == es::SINGLE_LINE_COMMENT[1]
        ) {
            line_comment();
        } else if (es::IDENTIFIER_CHARS.find(current_char) != std::string::npos) {
            tokens->push_back(*make_identifier());
        } else if (
            current_char == '`' ||
            current_char == '\'' ||
            current_char == '"'
        ) {
            auto [tok, err] = make_string();
            if (err)
                return { err, nullptr };
            tokens->push_back(*tok);

        } else {
            auto [tok, err] = unknownToken();
            if (err) return {err, nullptr};
            tokens->push_back(*tok);
        }
    }

    add_eof();
    return {nullptr, tokens};
}

void es::Lexer::advance() {
    position->advance(current_char);
    current_char = text[position->idx];
    current_char_str = std::string(1, current_char);
}

es::Token *es::Lexer::make_number() {
    Position* start = position->clone();
    std::string num_str;
    int dot_count = 0;

    while (
        can_advance() &&
        es::NUM_CHARS.find(current_char) != std::string::npos
    ) {
        if (current_char == '.') {
            if (dot_count > 0)
                break;
            dot_count++;
            num_str += '.';
        } else if (current_char != '_')
            num_str += current_char;
        advance();
    }

    return new es::Token(start, position->clone(), es::tt::NUMBER, num_str);
}

void es::Lexer::line_comment() {
    while (current_char != '\n' && can_advance())
        advance();
    advance();
}

void es::Lexer::add_eof() {
    tokens->push_back((es::Token){
        position->clone(),
        position->clone(),
        es::tt::END_OF_FILE
    });
}

bool es::Lexer::can_advance() {
    return position->idx < text.length();
}

std::tuple<es::Token*, es::Error*> es::Lexer::make_string() {
    es::Position* start = position->clone();
    std::string str;
    char end_str_char = current_char;
    advance();

    while (current_char != end_str_char && can_advance()) {
        if (current_char == '\\') {
            advance();
            if (es::STR_ESCAPES.count(current_char)) {
                str += es::STR_ESCAPES[current_char];
                advance();
                continue;
            }
        }
        str += current_char_str;
        advance();
    }

    if (current_char != end_str_char) {
        return {
            nullptr,
            SyntaxError(position, position, "Must close string with same character as you started it")
        };
    }

    advance();

    return {
        new es::Token(start, position, es::tt::STRING, str),
        nullptr
    };
}

std::tuple<es::Token*, es::Error*> es::Lexer::unknownToken() {

    if (position->idx < text.length()-2) {
        for (const auto& triple : es::TRIPLE_CHAR_TOKENS) {
            std::string key = triple.first;
            es::tt token = triple.second;
            if (key[0] == current_char) {
                if (key[1] == text[position->idx + 1]) {
                    if (key[2] == text[position->idx + 2]) {
                        Position* start = position->clone();
                        advance(); advance(); advance();
                        return {
                            new es::Token(start, position, token),
                            nullptr
                        };
                    }
                }
            }
        }
    }

    if (position->idx < text.length()-1) {
        for (const auto& double_ : es::DOUBLE_CHAR_TOKENS) {
            std::string key = double_.first;
            es::tt token = double_.second;
            if (key[0] == current_char) {
                if (key[1] == text[position->idx + 1]) {
                    Position* start = position->clone();
                    advance(); advance();
                    return {
                        new es::Token(start, position, token),
                        nullptr
                    };
                }
            }
        }
    }

    if (es::SINGLE_CHAR_TOKENS.contains(current_char_str)) {
        Position* start = position->clone();
        es::tt tok = es::SINGLE_CHAR_TOKENS[current_char_str];
        advance();
        return {
            new es::Token(start, position, tok),
            nullptr
        };
    }

    es::Position* start = position->clone();
    return {nullptr, IllegalCharError(start, current_char)};
}

es::Token* es::Lexer::make_identifier() {
    std::string id_str;
    es::Position* start = position->clone();

    std::string all_identifier_chars = es::IDENTIFIER_CHARS + es::DIGITS;

    while (can_advance() && all_identifier_chars.find(current_char) != std::string::npos) {
        id_str += current_char_str;
        advance();
    }

    es::tt tok_type = es::tt::IDENTIFIER;

    if (std::find(es::KEYWORDS.begin(), es::KEYWORDS.end(), id_str) != es::KEYWORDS.end())
        tok_type = es::tt::KEYWORD;

    return new es::Token(start, position, tok_type, id_str);
}
