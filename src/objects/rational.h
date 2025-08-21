#include <iostream>

class Rational {
public:
    // Default constructor - default value 0
    Rational();

    // Value constructor
    Rational(long long numerator);
    Rational(long long numerator, long long denominator);

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
        return static_cast<long double>(numerator_ / denominator_);
    }

    friend auto operator+(const Rational& lhs, const Rational& rhs) -> Rational;

    friend auto operator<<(std::ostream& os, const Rational& rational) -> std::ostream&;

private:
    long long numerator_;
    long long denominator_;
};
