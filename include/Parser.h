#pragma once
#include <utility>

#include "Token.h"
#include "Node.h"
#include "util.h"
#include "Argument.h"
#include "Error.h"

namespace es {
    struct ParseResult {
        Node* node;
        Error* err;

        int reverse_count;
        int last_registered_advance_count;
        int advance_count;

        void register_advance () {
            advance_count = 1;
            last_registered_advance_count++;
        }

        Node* register_parse_res (ParseResult* res) {
            last_registered_advance_count = res->advance_count;
            advance_count += res->advance_count;

            if (res->err)
                err = res->err;
            return res->node;
        }

        Node* try_register_parse_res (ParseResult* res) {
            if (res->err) {
                reverse_count += res->advance_count;
                return nullptr;
            }
            return register_parse_res(res);
        }

        ParseResult* success (Node* node_) {
            node = node_;
            return this;
        }

        ParseResult* failure (Error* err_) {
            err = err_;
            return this;
        }
    };

    class Parser {
        std::vector<Token> tokens;
        Token* current;
        int tok_idx;

    public:
        explicit Parser(std::vector<es::Token> tokens_)
         : tokens(std::move(tokens_)), tok_idx(-1), current(nullptr) {
            advance();
        }
        ParseResult* parse();

    private:
        inline Error* UnexpectedEOF () {
            if (current)
                return new Error(current->end, current->end, "UnexpectedEOFError", "File Ended unexpectedly");
            // current is not defined - really bad error
            Position* pos = tokens[tokens.size()-1].end;
            return new Error(pos, pos, "UnexpectedEOFError", "File Ended unexpectedly, and no EOF was found");
        }

        inline bool advance(ParseResult* res=nullptr) {
            if (tok_idx >= tokens.size()-1) {
                return false;
            }
            if (res) res->register_advance();
            tok_idx++;
            current = &tokens[tok_idx];
            return true;
        }

        inline bool reverse(int amount=1) {
            if (tok_idx < 1) return false;
            tok_idx -= amount;
            current = &tokens[tok_idx];
            return true;
        }

        inline void consume(
            ParseResult* res,
            tt type
        ) {
            if (current->type != type) {
                res->failure(SyntaxError(
                    current->start, current->end,
                    "Expected " + str_tt(type) + " but got " + str_tt(current->type)
                ));
                return;
            }
            advance(res);
        }

        inline void clear_end_statements (ParseResult* res) {
            while (current->type == es::tt::END_STATEMENT)
                advance(res);
        }

        inline void add_end_statement(ParseResult* res) {
            util::insert(&tokens, new Token(current->end, current->end, tt::END_STATEMENT), tok_idx);
        }

        std::tuple<UnInterpretedArgument*, Error*> parameter(ParseResult* res);

        ParseResult* statements(bool use_array=false);
        ParseResult* statement();
        ParseResult* atom();
        ParseResult* atom_identifier(ParseResult* res, Position* start, Token tok);
        ParseResult* power();
        ParseResult* factor();
        ParseResult* term();
        ParseResult* arithmetic_expr();
        ParseResult* comparison_expr();
        ParseResult* expr();
        ParseResult* bin_op();
        ParseResult* type_expr();
        ParseResult* func_call();
        ParseResult* index();
        ParseResult* initiate_var();
        ParseResult* context_expr();
        ParseResult* if_expr();
        ParseResult* while_expr();
        ParseResult* func_core_expr();
        ParseResult* func_expr();
        ParseResult* class_expr();
        ParseResult* for_expr();
        ParseResult* array_expr();
        ParseResult* object_literal_expr();
    };
}
