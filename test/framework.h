#include "../include/CES.h"

#define expect(expected, code)                                             \
    TEST_CASE("Test " + std::to_string(__COUNTER__), "[single-file]" ) {   \
        auto res = run(code, "TEST-ENV");                                  \
        if (res->err) {                                                    \
            REQUIRE((expected) == res->err->name);                         \
        } else {                                                           \
            REQUIRE((expected) == res->val->str());                        \
        }                                                                  \
    }
