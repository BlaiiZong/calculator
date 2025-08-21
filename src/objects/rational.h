#include <iostream>

class Rational {
public:
    // Default constructor - default value 0
    Rational();

    // Value constructor
    Rational(long long numerator);
    Rational(long long numerator, long long denominator);

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

    friend auto operator+(Rational lhs, const Rational& rhs) -> Rational;

    friend auto operator*(const Rational& lhs, const Rational& rhs) -> Rational {
        return Rational{lhs.numerator_ * rhs.numerator_, lhs.denominator_ * rhs.denominator_};
    }

    friend auto operator^(Rational base, size_t power) -> Rational;

    auto operator*=(const Rational& other) -> Rational& {
        *this = *this * other;
        return *this;
    }

    friend auto operator<<(std::ostream& os, const Rational& rational) -> std::ostream&;

private:
    static auto gcd(unsigned long long a, unsigned long long b) -> long long;

    // Simplify the rational number by dividing numerator and denominator by their greatest common divisor
    auto simplify() -> void;

    long long numerator_;
    long long denominator_;
};
