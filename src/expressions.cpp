#include "expressions.h"

// Special symbols - in order of precedence
const std::vector<std::string> Expression::operators = {};

/////////////////////////////////////////// Constructors ///////////////////////////////////////////

// Default constructor
Expression::Expression()
: Expression(Rational{}) {}

// Value constructor
Expression::Expression(const Rational& value)
: state_(State::rational)
, value_(value) {}
Expression::Expression(const long double value)
: state_(State::real)
, value_(value) {}

// String constructor (given a line)
Expression::Expression(const std::string& expr, bool) {
	// Let's just do integers and decimals only for now
	*this = parse_constant(expr);
	// const auto words = tokenise(expr, unspaced);

	// // Bad practice - but `calculator` catches this error and prints out the empty string
	// if (words.empty()) throw std::logic_error{""};

	// // Maintain a stack of (lhs, operator)
	// // Expressions pop off the stack whenever they are 'completed' (rhs found)
	// auto exprs = std::stack<std::pair<Expression, std::string>>{};
	// auto curr = Expression{};
	// for (const auto& word : words) {
	//     if (is_operator(word)) {
	//         // do logic
	//         throw std::runtime_error{"operators not yet implemented!"};
	//     } else {
	//         // Parse as a constant - not like this
	//         curr = parse_constant(word);
	//     }
	// }

	// if (!exprs.empty()) {
	//     throw std::runtime_error{"Unmatched operator: " + exprs.top().second};
	// }

	// // Surely unnecessary copy
	// *this = curr;
}

///////////////////////////////////////// Member Functions /////////////////////////////////////////

auto Expression::reformat() -> Expression& {
	if (!is_rational())
		throw std::runtime_error{"Expression cannot be reformatted"};

	state_ = state_ == State::rational ? State::rational_decimal : State::rational;
	return *this;
}

///////////////////////////////////////// Friend Functions /////////////////////////////////////////

auto operator<<(std::ostream& os, const Expression& expr) -> std::ostream& {
	if (expr.state_ == Expression::State::real)
		os << expr.value_.real;
	else if (expr.state_ == Expression::State::rational)
		os << expr.value_.rational;
	else if (expr.state_ == Expression::State::rational_decimal)
		os << expr.value_.rational.as_decimal();
	else
		throw std::runtime_error{"Expression is not numeric"};
	return os;
}

/////////////////////////////////////// Non-member Functions ///////////////////////////////////////

// auto Expression::tokenise(const std::string& expr, bool unspaced) -> std::vector<std::string> {
//     if (unspaced) {
//         // Split by special tokens
//         auto current_word = std::string{};
//         for (const auto& c : expr) {
//             // Currently operators are only one
//             if (is_operator(c)) {
//                 //
//             }
//         }
//     } else {
//         // Split by spaces
//         auto it = std::istringstream{expr};
//         return std::vector<std::string>{
//             std::istream_iterator<std::string>{it},
//             std::istream_iterator<std::string>{}
//         };
//     }
// }

// Try to parse the number as a Rational, and if that isn't possible (hopefully due to integer
// overflow),
//  Try to parse the number as a long double
auto Expression::parse_constant(const std::string& expr) -> Expression {
	if (!std::regex_match(expr.begin(), expr.end(), std::regex{"-?\\d*(\\.\\d+)?"}))
		throw std::runtime_error{"Invalid input: " + expr + " (expected a number)"};
	try {
		return Expression{Rational{expr}};
	} catch (const std::exception& e) {
		try {
			return Expression{std::stold(expr)};
		} catch (const std::exception& e) {
			throw std::runtime_error{"Invalid input: " + expr + " (expected a number)"};
		}
	}
}
