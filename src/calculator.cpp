#include "calculator.h"

Calculator::Calculator(std::size_t precision, long long)
: preans_(Expression{})
, ans_(Expression{})
, dp_(precision) {
// , mod_(mod) {
	std::cout << std::fixed << std::setprecision(static_cast<int>(dp_));
}

auto Calculator::run() -> void {
	std::string line;

	std::cout << "Welcome to the command line calculator. Start typing to begin!\n";
	std::cout << "> ";
	while (std::getline(std::cin, line)) {
		// Style choice: these constants only appear once so I'm using string
		// literals
		if (line == "quit") {
			// quit the calculator
			break;
		}
		else if (line == "ANS") {
			// print ans_
			std::cout << ans_;
		}
		else if (line == "PREANS") {
			// print preans_
			std::cout << preans_;
			update_ans(std::move(preans_));
		}
		else if (line == "FMT" || line == "FORMAT") {
			// Check if the previous answer was either rational or real, and print the
			// answer in the other format
			try {
				std::cout << ans_.reformat();
			} catch (const std::exception& e) {
				std::cerr << e.what();
			}
		}
		else {
			// Parse the line as an expression, catching any errors that come up
			try {
				std::cout << evaluate(line);
			} catch (const std::exception& e) {
				std::cerr << e.what();
			}
		}

		std::cout << "\n> ";
	}

	std::cout << "Goodbye!\n";
}

// parse `line` as an expression, and update the `ans_` variable as necessary
auto Calculator::evaluate(const std::string& line) -> const Expression& {
	update_ans(Expression{line});
	return ans_;
}
