#pragma once

#include "RTResult.h"
#include "Error.h"
#include "Primitive.h"

namespace es {
    class Node {
    public:
        Position* start;
        Position* end;
        bool is_terminal;

        RunTimeResult* interpret();

    private:
        virtual RunTimeResult* interpret_() {
            return nullptr;
        };

    protected:
        Node (Position* start_, Position* end_, bool is_terminal_):
            start(start_), end(end_), is_terminal(is_terminal_) {};
    };

    class N_number: public Node {
        RunTimeResult* interpret_ () override;
        N_number (Position* start_, Position* end_, std::string value):
            Node(start_, end_, true) {}
    };

    class N_access_variable: public Node {
        RunTimeResult* interpret_ () override;
    public:
        N_access_variable (Position* start_, Position* end_, std::string value):
            Node(start_, end_, true) {}
    };
}