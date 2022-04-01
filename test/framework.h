#include "../include/CES.h"


#define expect(expected, code)                                      \
    TEST_CASE("name", "[single-file]") {                            \
        auto res = run(code, "TEST-ENV");                           \
        if (res->err) {                                             \
            REQUIRE(res->err->name == expected);                    \
        } else {                                                    \
            REQUIRE(res->val->str() == expected);                   \
        }                                                           \
}