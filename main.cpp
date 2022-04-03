#include <iostream>

#include "include/CES.h"
#include "version.h"

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
            auto asArr = dynamic_cast<es::Array*>(res->val);
            if (asArr == nullptr) {
                std::cerr << "invalid result" << std::endl;
                continue;
            }
            for (auto item : *asArr->value) {
                std::cout << item->str() << std::endl;
            }
        }

        std::cout << ">>> ";
    }
}

void welcome_message () {
    std::cout << "Welcome to C++ EntropyScript v" ES_V << " (" << __TIMESTAMP__ << ")" << std::endl;
    std::cout << "(C++ " << CPP_V << ", GCC " << GCC_V << ", Clang " << CLANG_V << ")" << std::endl;
    std::cout << "Type 'exit' to exit" << std::endl;
}

int main () {
    welcome_message();
    console();
}
