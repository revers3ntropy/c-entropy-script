#pragma once
#include <string>
#include <map>
#include <utility>

#include "Position.h"
#include "Constants.h"

namespace es {

    std::string str_tt (es::tt t);

    struct Token {
        Position* start;
        Position* end;
        tt type;
        std::string value;

        Token (Position* start_, Position* end_, tt type_, std::string value_="") :
            start(start_->clone()), end(end_->clone()), type(type_), value(std::move(value_)) {}

        bool matches(tt type, std::string* value) const;
        inline std::string str() const {
            auto out = "<Token: " + str_tt(type);
            if (!value.empty())
               out += "|" + value;
            return out + ">";
        }
    };
}
