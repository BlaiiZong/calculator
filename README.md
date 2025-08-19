# Calculator

A command line calculator for evaluating mathematical expressions, written in C++.
This calculator is intended to be as intuitive as possible, that is, it will parse notation such as `a^x`, `|x|`, etc., as well as supporting custom functions.
One important note to make is the [whitespace predence functionality](#whitespace-precendence), which allows you to forgo parentheses in some cases.

## Usage:

1. Use `make` to generate the `calculator` executable.
2. Use `./calculator` to run the calculator.
   - Input expressions as usual in the commandline, and press `enter` to evaluate them.
   - The calculator will remember custom variables and functions during runtime, allowing you to reuse earlier results.

## Functionality

### Expressions

Most expressions can be entered as you would on a normal calculator.

The calculator supports (will support, todo) most conventional mathematical functions, such as sqrt, exp, log, and the trigonometry collection.

### Whitespace precendence

"Whitespace predence" gives expressions which contain no whitespace higher precedence than whitespace-separated expressions.
This is intended to help remove the use of parentheses in some (small) cases, to increase the efficiency and readability of typing expressions.

For example, contrary to the usual order of operations, the expression `1+2 * 3+4` would evaluate `1+2 = 3` and `3+4 = 7` first, resulting in `3 * 7 = 21`, whereas a usual calculator would require parentheses for the same expression: `(1 + 2) * (3 + 4)`.
Otherwise, the usual conventions for typing mathematical expressions hold.

### Custom functions and variables

The calculator allows custom variables and functions to be created during runtime.

Functions are differentiated according to the name of the function, as well as the number of variables in the function.
That is, `f(x) = ...` and `f(x, y) = ...` can simultaneously be saved in memory.

Variables and functions names must start with a letter, but otherwise can be any string of letters, numbers or underscores which does not conflict with the [reserved keywords](#reserved-keywords).

## Magic Numbers

The calculator uses a few magic numbers to save the following information.
The magic numbers can be modified in runtime using the command `set(<x>, <new_x>)`, where `<x>` is the command line argument for the value, and `<new_x>` is the new value of `<x>`.

| Information | Command Line Argument | Default | Description                                                                                                                  |
| ----------- | --------------------- | ------- | ---------------------------------------------------------------------------------------------------------------------------- |
| Modulus     | `mod`                 | 10^9 +7 | Default modulus for calculations potentially involving large numbers (exponentiation, products, sums)                        |
| Precision   | `dp`                  | 6       | The number of decimal places to which floating point numbers are calculated. <br> The calculator treats `eps` as `10 ^ -dp`. |

## Reserved Keywords

### Commands

ANS, PREANS, FORMAT, quit

these keywords (and function definitions) don't update ans

### Constants

e, pi

### Analytic Functions

sqrt, exp, ln, log, sin, cos, tan, cot, sec, cosec, asin, acos, atan, acot, asec, acosec

### Set-iterated operations

min, max, sum, prod ???
set support, e.g. min\_{1, 2, 3}(x^2)

### Discrete functions

nCr, nPr, gcd, lcm ???

### Calculus???

d/dx ???

## Operator Precedence

(), [], {}, ||

^, !

\*, /, %

+, -

## TODO (self)

- Mathematical functions (how to do nCk?)
- Custom function currying
- Support vectors and matrices
- Complex numbers
- Integer overflow warning
