#include "rational.h"

// Default constructor
Rational::Rational()
: Rational(0) {}

Rational::Rational(ll numerator)
: Rational(numerator, 1) {}

Rational::Rational(ll numerator, ll denominator)
: numerator_(numerator)
, denominator_(denominator) {
	if (denominator_ == 0)
		throw std::domain_error{"Division by 0 error!"};
	simplify();
}

// Given an potentially decimal number, multiply it by the smallest power of 10
// which will make it an integer, and set that power of 10 as the denominator.
//  e.g 3.14 = 314/100, since there are two digits after the decimal place.
Rational::Rational(const std::string& expr) {
	auto decimal_places = std::size_t{0};
	auto numerator = expr;
	if (expr.find('.') != std::string::npos) {
		decimal_places = expr.length() - 1 - expr.find('.');
		numerator.erase(numerator.find('.'), 1);
	}

	if (decimal_places > 18) throw std::runtime_error{""};
	denominator_ = (Rational{10} ^ decimal_places).numerator_;
	try {
		numerator_ = std::stoll(numerator);
	} catch (const std::out_of_range& e) {
		throw std::runtime_error{""};
	}
	simplify();
}

auto operator^(const Rational base, size_t power) -> Rational {
	auto current = base;
	auto result = Rational{1};
	while (power) {
		if (power & 1)
			result *= current;
		current *= current;
		power >>= 1;
	}
	return result;
}

auto operator<=>(const Rational& lhs, const Rational& rhs) -> std::strong_ordering {
	if (lhs.numerator_ >= 0 && rhs.numerator_ < 0)
		return std::strong_ordering::greater;
	const auto ratio = lhs / rhs;
	return ratio.numerator_ <=> ratio.denominator_;
}

auto operator<<(std::ostream& os, const Rational& rational) -> std::ostream& {
	os << rational.numerator_;
	if (rational.denominator_ != 1)
		os << "/" << rational.denominator_;
	return os;
}

auto Rational::gcd(ull a, ull b) -> ll {
	if (a < b)
		std::swap(a, b);
	return b == 0 ? static_cast<ll>(a) : gcd(b, a % b);
}

// Simplify the rational number by dividing numerator and denominator by their
// greatest common divisor
auto Rational::simplify() -> void {
	if (denominator_ < 0) {
		numerator_ *= -1;
		denominator_ *= -1;
	}
	const auto gcd = Rational::gcd(static_cast<ull>(abs(numerator_)), static_cast<ull>(denominator_));
	numerator_ /= gcd;
	denominator_ /= gcd;
}
