#include <iostream>
#include <string>
#include "calculator.h"

int main(){
    // TODO: Check for magic number modifications (command line arguments)
    Calculator calc;
    std::string line;

    std::cout << "Welcome to the command line calculator. Start typing to begin!\n";
    std::cout << "> ";
    while (std::cin >> calc) {
        std::cout << "\n> ";
    }

    std::cout << "Goodbye!\n";
}
