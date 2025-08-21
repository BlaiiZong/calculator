#include "expression.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

class Calculator {
public:
	Calculator(std::size_t precision = 6, long long mod = static_cast<long long>(1e9 + 7));

	auto run() -> void;

	// Evaluate the current expression
	auto evaluate(const std::string& line) -> const Expression&;

	// Reads a line of input until the newline character, parsing expressions as
	// it goes friend auto operator>>(std::istream &is, Calculator &calculator) ->
	// std::istream&;

	// Outputs the current expression and updates the format_
	// friend auto operator<<(std::ostream &os, const Calculator &calculator) ->
	// std::ostream&;

private:
	auto update_ans(const Expression&& new_ans) -> void {
		preans_ = std::exchange(ans_, new_ans);
	}

	// Context context; // not yet
	Expression preans_;
	Expression ans_;
	std::size_t dp_;
	// long long mod_;
};
