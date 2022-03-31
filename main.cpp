#include <iostream>

#include "include/CES.h"

void console () {
    std::string input;
    std::cout << ">>> ";

    while (std::getline(std::cin, input)) {

        if (input == "exit") {
            break;
        }

        auto res = run(input, "CES-REPL");

        if (res->err != nullptr) {
            std::cout << res->err->str() << std::endl;

        } else if (res->val != nullptr) {
            std::cout << res->val->toString() << std::endl;
        }

        std::cout << ">>> ";
    }
}

int main () {
    console();
}
