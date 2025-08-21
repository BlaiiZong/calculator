#include "rational.h"

// Default constructor
Rational::Rational() : Rational(0) {}

Rational::Rational(long long numerator) : Rational(numerator, 1) {}

Rational::Rational(long long numerator, long long denominator) : numerator_(numerator), denominator_(denominator) {
    if (denominator_ == 0)
        throw std::domain_error{"Division by 0 error!"};
}

auto operator<<(std::ostream& os, const Rational& rational) -> std::ostream& {
    os << rational.numerator_;
    if (rational.denominator_ != 1) os << "/" << rational.denominator_;
    return os;
}
