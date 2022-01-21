#pragma once
#include <utility>

#include "RTResult.h"
#include "Error.h"
#include "Primitive.h"
#include "Token.h"
#include "Context.h"

namespace es {
    class Node {
    public:
        Position* start;
        Position* end;
        bool is_terminal;

        RunTimeResult* interpret(Context* context);

    private:
        // placeholder -- must be overridden in every sub-class
        virtual RunTimeResult* interpret_(Context* context) {
            return nullptr;
        };

    protected:
        Node (Position* start, Position* end, bool is_terminal_=false):
            start(start->clone()), end(end->clone()), is_terminal(is_terminal_) {};
    };

    class TerminalNode : public Node {
    protected:
        std::string value;
    public:
        TerminalNode(Position* start, Position* end, std::string value_="") :
            Node(start, end, true), value(std::move(value_)) {};
    };

    // TERMINAL NODES

    class N_number: public TerminalNode {
        RunTimeResult* interpret_ (Context* context) override;
    public:
        N_number (Position* start, Position* end, std::string value):
            TerminalNode(start, end, std::move(value)) {}
    };

    class N_string: public TerminalNode {
        RunTimeResult* interpret_ (Context* context) override;
    public:
        N_string (Position* start, Position* end, std::string value):
        TerminalNode(start, end, std::move(value)) {}
    };

    class N_access_variable: public TerminalNode {
        RunTimeResult* interpret_ (Context* context) override;
    public:
        N_access_variable (Position* start, Position* end, std::string value):
            TerminalNode(start, end, std::move(value)) {}
    };

    class N_undefined: public TerminalNode {
        RunTimeResult* interpret_ (Context* context) override;
    public:
        N_undefined (Position* start, Position* end):
        TerminalNode(start, end) {}
    };

    class N_break: public TerminalNode {
        RunTimeResult* interpret_ (Context* context) override;
    public:
        N_break (Position* start, Position* end):
            TerminalNode(start, end) {}
    };

    class N_continue: public TerminalNode {
        RunTimeResult* interpret_ (Context* context) override;
    public:
        N_continue (Position* start, Position* end):
            TerminalNode(start, end) {}
    };

    // NON_TERMINAL NODES

    class N_return: public Node {
        RunTimeResult* interpret_ (Context* context) override;
        Node* expression;
    public:
        N_return (Position* start, Position* end, Node* expression):
        Node(start, end), expression(expression) {}
    };

    class N_yield: public Node {
        RunTimeResult* interpret_ (Context* context) override;
        Node* expression;
    public:
        N_yield (Position* start, Position* end, Node* expression):
        Node(start, end), expression(expression) {}
    };

    class N_bin_op: public Node {
        RunTimeResult* interpret_ (Context* context) override;
        Node* left;
        Node* right;
        Token* op_tok;
    public:
        N_bin_op (Position* start, Position* end, Node* left, Token* op_tok, Node* right):
            Node(start, end), left(left), op_tok(op_tok), right(right) {}
    };

    class N_unary_op: public Node {
        RunTimeResult* interpret_ (Context* context) override;
        Node* operand;
        Token* op_tok;
    public:
        N_unary_op (Position* start, Position* end, Node* operand, Token* op_tok):
            Node(start, end), operand(operand), op_tok(op_tok) {}
    };

    class N_statements: public Node {
        RunTimeResult* interpret_ (Context* context) override;
        std::vector<Node>* items;
    public:
        N_statements (Position* start, Position* end, std::vector<Node>* items_):
            Node(start, end), items(items_) {}
    };

    class N_array: public Node {
        RunTimeResult* interpret_ (Context* context) override;
        std::vector<Node>* items;
        bool should_copy;
    public:
        N_array (Position* start, Position* end, std::vector<Node>* items, bool should_copy=false):
            Node(start, end), items(items), should_copy(should_copy) {}
    };
}