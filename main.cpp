#include <iostream>

#include "include/bigint.h"
#include "include/CES.h"

void console () {
    std::string input;
    std::cout << ">>> ";
    while (std::getline(std::cin, input)) {
        if (input == "exit") {
            break;
        }
        auto [res, error] = run(input, "CES-REPL");
        if (error) {
            std::cout << error->str() << std::endl;
            return;
        }

        std::cout << ">>> ";
    }
}

int main () {
    console();
    return 0;
}
