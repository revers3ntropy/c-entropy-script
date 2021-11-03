#include <iostream>

#include "include/CES.h"

void console () {
    std::string input;
    std::cout << ">>> ";
    while (std::getline(std::cin, input)) {
        if (input == "exit")
            break;
        auto [res, error] = run(input, "CES-REPL");
        std::cout << ">>> ";
    }
}

int main () {
    console();
    return 0;
}
