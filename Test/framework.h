#pragma once
#include <vector>

#include "../include/Error.h"

namespace es::tests {
    struct TestResult {
        int failed = 0;
        int passed = 0;

        std::vector<Error> fails = {};

        int time = 0;

        void register_res (TestResult* res) {
            failed += res->failed;
            passed += res->passed;

            // merge fails of both tests
            std::vector<es::Error> new_fails = {};

            new_fails.reserve( fails.size() + res->fails.size() ); // preallocate memory for new vector
            new_fails.insert( new_fails.end(), fails.begin(), fails.end() );
            new_fails.insert( new_fails.end(), res->fails.begin(), res->fails.end() );

            fails = new_fails;
        }

        std::string str () {
            std::string out =
                    "---   TEST REPORT   ---"
                    "    " + std::to_string(failed) + " tests failed"
                                                      "    " + std::to_string(passed) + " tests passed"
                                                                                        ""
                                                                                        "In " + std::to_string(time) + "ms\n\n";

            if (failed < 1)
                out += "All Tests Passed!";

            for (auto const& err : fails) {
                out += "\n-----------------\n";
                out += err.str();
            }

            return out;
        }
    };

    class Test {
        int id;
    };
}
