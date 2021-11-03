#pragma once
#include <string>
#include <utility>

#include "Position.h"

namespace es {

    class Error {
        Position* start;
        Position* end;
        std::string name;
        std::string detail;
    public:

        Error(Position* start_, Position* end_, std::string  name_, std::string detail_) :
            start(start_->clone()), end(end_->clone()), name(std::move(name_)), detail(std::move(detail_)){};

        inline std::string str() const {
            return name + ": " + detail + " at " + start->str();
        }
    };

    struct TraceBack {
        std::vector<Position> calls;
        Error err;

        std::string str() {
            std::string out = err.str();
            for (const auto& pos : calls)
                out += pos.str();
            return out;
        }
    };

    inline Error* IllegalCharError(Position* start, char char_) {
        Position* end = start->clone();
        end->advance(char_);
        return new Error(
            start->clone(), end,
            "IllegalCharError",
            "'" + std::string(1, char_) + "'"
        );
    }

    inline Error* SyntaxError(Position* start, Position* end, std::string detail) {
        return new Error(start, end, "SyntaxError", detail);
    }
}

