#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include "expressions.h"

class Calculator {
public:
    Calculator(std::size_t precision = 6, long long mod = 1e9+7) : dp_(6), mod_(mod) {
        std::cout << std::fixed << std::setprecision(dp_);
    }

    // Reads a line of input until the newline character, parsing expressions as it goes
    friend auto operator>>(std::istream &is, Calculator &calculator) -> std::istream&;

    // Outputs the current expression and updates the format_
    // friend auto operator<<(std::ostream &os, const Calculator &calculator) -> std::ostream&;

private:
    auto update_ans(const Expression &new_ans) -> void {
        preans_ = std::exchange(ans_, new_ans);
    }

    Context context;
    Expression preans_;
    Expression ans_;
    std::size_t dp_;
    long long mod_;
};
