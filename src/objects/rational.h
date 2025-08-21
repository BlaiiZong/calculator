#include <compare>
#include <iostream>

class Rational {
	using ll = long long;
	using ull = unsigned long long;

public:
	// Default constructor - default value 0
	Rational();

	// Value constructor
	Rational(ll numerator);
	Rational(ll numerator, ll denominator);

	Rational(const std::string& expr);

	// Copy constructor
	Rational(const Rational& other) = default;

	// Move constructor
	Rational(Rational&& other) = default;

	// Copy assignment
	auto operator=(const Rational& other) -> Rational& = default;

	// Move assignment
	auto operator=(Rational&& other) -> Rational& = default;

	// Destructor
	~Rational() = default;

	auto as_decimal() const -> long double {
		return static_cast<long double>(1.0 * numerator_ / denominator_);
	}

	// Hopefully no integer overflow happens here... otherwise all the efforts in
	// the multiplication section goes to waste
	friend auto operator+(const Rational& lhs, const Rational& rhs) -> Rational {
		return Rational{lhs.numerator_ * rhs.denominator_ + rhs.numerator_ * lhs.denominator_,
		                lhs.denominator_ * rhs.denominator_};
	}

	friend auto operator-(const Rational& lhs, const Rational& rhs) -> Rational {
		return lhs + Rational{-1} * rhs;
	}

	// a/b * c/d = ac/bd : compute a/d and b/c, then multiply the resulting
	// numerators and denominators This minimises the probability of integer
	// overflow
	friend auto operator*(const Rational& lhs, const Rational& rhs) -> Rational {
		const auto ad = Rational{lhs.numerator_, rhs.denominator_};
		const auto bc = Rational{rhs.numerator_, lhs.denominator_};
		return Rational{ad.numerator_ * bc.numerator_, ad.denominator_ * bc.denominator_};
	}

	friend auto operator/(const Rational& lhs, const Rational& rhs) -> Rational {
		return lhs * Rational{rhs.denominator_, lhs.denominator_};
	}

	friend auto operator^(const Rational base, size_t power) -> Rational;

	auto operator*=(const Rational& other) -> Rational& {
		*this = *this * other;
		return *this;
	}

	friend auto operator==(const Rational& lhs, const Rational& rhs) -> bool {
		const auto ratio = lhs / rhs;
		return ratio.numerator_ == 1 && ratio.denominator_ == 1;
	}

	friend auto operator<=>(const Rational& lhs, const Rational& rhs) -> std::strong_ordering;

	friend auto operator<<(std::ostream& os, const Rational& rational) -> std::ostream&;

private:
	static auto gcd(ull a, ull b) -> ll;

	// Simplify the rational number by dividing numerator and denominator by their
	// greatest common divisor
	auto simplify() -> void;

	ll numerator_;
	ll denominator_;
};
