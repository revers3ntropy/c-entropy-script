#pragma once
#include <string>
#include <utility>
#include <vector>
#include <iostream>


namespace es {
    struct Position {
        std::string file;
        int idx;
        int ln;
        int col;

        Position(int idx_, int ln_, int col_, std::string file_)
            : idx(idx_), ln(ln_), col(col_), file(std::move(file_)) {}

        ~Position() {
            delete &idx;
            delete &ln;
            delete &col;
            delete &file;
        }

        inline void advance(char current_char) {
            idx++;
            col++;

            if (current_char == '\n') {
                ln++;
                col = 0;
            }
        }
        inline Position* clone() const {
            return new Position(idx, ln, col, file);
        }

        inline std::string str() const {
            return "File '" + file + "', " + std::to_string(ln+1) + ":" + std::to_string(col+1);
        }

        static inline Position* nil () {
            return new Position(-1, -1, -1, "Unknown");
        }
    };
}




