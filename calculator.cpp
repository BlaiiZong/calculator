#include "calculator.h"

auto operator>>(std::istream &is, Calculator &calculator) -> std::istream& {
    std::string line;
    std::getline(std::cin, line);

    // Style choice: these constants only appear once so I'm using string literals
    if (line == "quit") {
        // quit the calculator
        std::cin.setstate(std::ios_base::failbit);
    } if (line == "ANS") {
        // print ans_
    } if (line == "PREANS") {
        // print preans_
    } if (line == "FORMAT") {
        // Check if the previous answer was either rational or real, and print the answer in the other format
    } else {
        // Parse the line as an expression
    }
}