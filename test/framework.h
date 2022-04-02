#include "../include/CES.h"

extern std::string current_file;

#define file(name) current_file = name;

#define expect(expected, code)                                      \
    TEST_CASE(                                                      \
        "Test" + std::to_string(__COUNTER__),                       \
        "[single-file, " + current_file + "]"                       \
    ) {                                                             \
        auto res = run(code, "TEST-ENV");                           \
        if (res->err) {                                             \
            REQUIRE(res->err->name == (expected));                  \
        } else {                                                    \
            REQUIRE(res->val->str() == (expected));                 \
        }                                                           \
    }
