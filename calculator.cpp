#include "calculator.h"

auto Calculator::run() -> void {
    std::string line;

    std::cout << "Welcome to the command line calculator. Start typing to begin!\n";
    std::cout << "> ";
    while (std::getline(std::cin, line)) {
        // Style choice: these constants only appear once so I'm using string literals
        if (line == "quit") {
            // quit the calculator
            break;
        } if (line == "ANS") {
            // print ans_
        } if (line == "PREANS") {
            // print preans_
        } if (line == "FORMAT") {
            // Check if the previous answer was either rational or real, and print the answer in the other format
        } else {
            // Parse the line as an expression, catch error on fail
            try {
                std::cout << evaluate(line);
            }
            catch(const std::exception& e) {
                std::cerr << e.what();
            }
            
        }
        
        std::cout << "\n> ";
    }

    std::cout << "Goodbye!\n";
}

auto Calculator::evaluate(const std::string& line) -> const Expression& {
    // construct a new expression using Expression(line)
    // evaluate expression, and update the `ans_` variable
}

auto operator>>(std::istream &is, Calculator &calculator) -> std::istream& {
}