#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
// #include "functions.h"
#include "objects/rational.h"

// using Context = std::map<std::string, Function>;

class Expression {
    // We try to store expressions as high up the enum as we can, i.e. if possible, we store everything as integers.
    // rational and rational_decimal are the same number, and only differ in ostream representation
    //  rational is displayed in the standard fraction format, rational_decimal is displayed as a decimal number
    enum State {
        rational,
        rational_decimal,
        real,
        // function
    };

    union Value {
        Rational rational;
        long double real;
        // Function function;

        Value() : rational(Rational{}) {}
        Value(const Rational& value) : rational(value) {}
        Value(const long double value) : real(value) {}
    };

    const static std::vector<std::string> operators;

public:
    // Default constructor - default value 0
    Expression();

    // Custom string constructor
    Expression(const std::string& expr, bool unspaced = false);

    // Copy constructor
    Expression(const Expression &other) = default;

    // Move constructor
    Expression(Expression &&other) = default;

    // Copy assignment
    auto operator=(const Expression &other) -> Expression& = default;
    
    // Move assignment
    auto operator=(Expression &&other) -> Expression& = default;

    // Destructor
    ~Expression() = default;

    // If state_ is rational or rational_decimal, switches state_ to the other format.
    auto reformat() -> Expression&;

    // Evaluate current expression
    // expr_ will store the final answer
    auto evaluate() -> Expression&;

    friend auto operator>>(std::istream &is, Expression &expr) -> std::istream&;

    friend auto operator<<(std::ostream &os, const Expression &expr) -> std::ostream&;

private:
    // Custom value constructors
    // Given a rational number, initialises value_ as the given number
    Expression(const Rational& value);
    // Given a floating point number, initialises value_ as the given number
    Expression(const long double value);

    auto is_rational() const -> bool {
        return state_ == State::rational || state_ == State::rational_decimal;
    }

    static auto is_operator(const std::string& op) -> bool {
        return std::find(operators.begin(), operators.end(), op) != operators.end();
    }

    static auto tokenise(const std::string& expr, bool unspaced) -> std::vector<std::string>;

    static auto parse_constant(const std::string& expr) -> Expression;

    State state_;
    Value value_;
};
