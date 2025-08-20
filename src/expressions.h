#include <iostream>
#include <string>
#include "functions.h"
#include "rational.h"

using Context = std::map<std::string, Function>;

// We store real numbers as rationals so `FORMAT` can switch between the two representations
union State {
    long long integer;
    Rational rational;
    Rational real;
    long double decimal;
    // Function function;
};

class Expression {
public:
    Expression() {}

    Expression(const std::string expr) {}

    // Copy constructor
    Expression(const Expression &other) : expr_(other.expr_) {}

    // Move constructor
    Expression(Expression &&other) : expr_(std::exchange(other.expr_, expr_)) {}

    // Copy assignment
    auto operator=(const Expression &other) -> Expression&;
    
    // Move assignment
    auto operator=(Expression &&other) -> Expression&;

    friend auto operator>>(std::istream &is, Expression &expr) -> std::istream&;

    friend auto operator<<(std::ostream &os, const Expression &expr) -> std::ostream&;

private:
State expr_;
};
