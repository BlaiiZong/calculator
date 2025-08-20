#include "expressions.h"

// Move assignment
auto Expression::operator=(Expression &&other) -> Expression& {
    if (this != &other) {
        std::swap(expr_, other.expr_);
    }
    return *this;
}