#include "rational.h"

// Default constructor
Rational::Rational() : Rational(0) {}

Rational::Rational(long long numerator) : Rational(numerator, 1) {}

Rational::Rational(long long numerator, long long denominator) : numerator_(numerator), denominator_(denominator) {
    if (denominator_ == 0)
        throw std::domain_error{"Division by 0 error!"};
    simplify();
}

Rational::Rational(const std::string& expr) {
    const auto decimal_places = expr.find('.') == std::string::npos ? 0 : expr.length() - 1 - expr.find('.');
    denominator_ = (Rational{10}^decimal_places).numerator_;
    numerator_ = static_cast<long long>(std::stold(expr) * denominator_);
    simplify();
}

auto operator^(const Rational base, size_t power) -> Rational {
    auto current = base;
    auto result = Rational{1};
    while (power) {
        if (power & 1) result *= current;
        current *= current;
        power >>= 1;
    }
    return result;
}

auto operator<<(std::ostream& os, const Rational& rational) -> std::ostream& {
    os << rational.numerator_;
    if (rational.denominator_ != 1) os << "/" << rational.denominator_;
    return os;
}

auto Rational::gcd(unsigned long long a, unsigned long long b) -> unsigned long long {
    if (a < b) std::swap(a, b);
    return b == 0 ? a : gcd(b, a % b);
}

// Simplify the rational number by dividing numerator and denominator by their greatest common divisor
auto Rational::simplify() -> void {
    if (denominator_ < 0) {
        numerator_ *= -1;
        denominator_ *= -1;
    }
    const auto gcd = Rational::gcd(abs(numerator_), denominator_);
    numerator_ /= gcd;
    denominator_ /= gcd;
}
