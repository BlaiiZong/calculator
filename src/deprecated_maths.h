using namespace std;

/************************************************************

                    FUNCTION DEFINITIONS

************************************************************/

void print(int num);
int mod(int num, int MOD);
int pow(int base, int power, int MOD);
int sign(int num);
int abs(int num);
int gcd(int num1, int num2);
void egcd(int num1, int num2, int value);
void egcd_reverse(int& x, int& y, int multiples[], int cum_prod, int i);

struct Rational {
	int numer;
	int denom;
	Rational simplify() {
		Rational q;
		int d = gcd(numer, denom);
		printf("d: %d\n", d);
		q.numer = numer / d;
		q.denom = denom / d;
		if (q.denom < 0) {
			q.numer *= -1;
			q.denom *= -1;
		}
		return q;
	}
};
Rational add_rational(Rational q1, Rational q2);
Rational mult_rational(int n, Rational q);
Rational mult_rational(Rational q1, Rational q2);

struct Vector_2D {
	Rational x;
	Rational y;
};
Vector_2D add_2D_vec(Vector_2D v1, Vector_2D v2);
Vector_2D scalar_mult_2D(int n, Vector_2D v);
Vector_2D scalar_mult_2D(Rational q, Vector_2D v);
void print_2D_vec(Vector_2D v);

void print_functions();

/************************************************************

                    FUNCTIONS BEGIN HERE

************************************************************/

// Prints out a single integer
void print(int num) {
	printf("%d\n", num);
}

int mod(int num, int MOD) {
	return (num % MOD) + MOD * (num % MOD < 0);
}

int sign(int num) {
	return (num < 0) ? -1 : 1;
}

int abs(int num) {
	return num * sign(num);
}

// Fast exponentiation
int pow(int base, int power, int MOD) {
	int result = 1, index = 0;
	while (1 << index <= power) {
		if (power & 1 << index)
			result = result * base % MOD;
		base = base * base % MOD;
		index++;
	}
	return result;
}

int gcd(int num1, int num2) {
	if (abs(num1) < abs(num2))
		swap(num1, num2);
	printf("GCD: %d %d\n", num1, num2);
	return (num2) ? gcd(num2, num1 % num2) : num1;
}

/************************************************************

                        NUMBER THEORY?

************************************************************/

// it just works :tm:
void egcd(int num1, int num2, int value) {
	int b = num1, a = num2;
	if (num1 < num2)
		swap(num1, num2);
	int multiples[1005], i = -1, cum_prod;

	while (num2) {
		printf("EGCD: %d %d\n", num1, num2);
		multiples[++i] = num1 / num2;
		cum_prod = num1 % num2; // temp var
		num1 = num2;
		num2 = cum_prod;
	}
	printf("EGCD: %d %d\n", num1, num2);

	int d = num1, x = 0, y = 0; // ax + by = 0, num1 = a, num2 = b;
	cum_prod = 1;
	if (value % d) {
		cout << "There are no solutions to this congruence relation.\n";
		printf("The solution found was: %d*%d %c %d*%d = %d\n", x, a, ((y < 0) ? '-' : '+'), abs(y), b, value);
		return;
	}

	egcd_reverse(x, y, multiples, cum_prod, i - 1);
	x *= value / d;
	y *= value / d;
	if (x * a + y * b == -value) {
		x *= -1;
		y *= -1;
	}
	if (x * a + y * b != value) {
		printf("Warning!!! Incorrect solution!!!\n");
	}
	printf("A solution to the equation is %d*%d %c %d*%d = %d\n",
	       x,
	       a,
	       ((y < 0) ? '-' : '+'),
	       abs(y),
	       b,
	       value);
	printf("A set of solutions to the congruence %dx = %d (mod %d) is:\n{", b, value, a);
	y = mod(y, a / d);
	while (y < a - a / d) {
		cout << y << ", ";
		y += a / d;
	}
	cout << y << "}\n";
}

void egcd_reverse(int& x, int& y, int multiples[], int cum_prod, int i) {
	if (i == 0) {
		x += cum_prod;
		y -= cum_prod * multiples[i];
	}
	else if (i == 1) {
		y -= cum_prod;
		egcd_reverse(x, y, multiples, cum_prod * multiples[i], i - 1);
	}
	else if (i > 1) {
		egcd_reverse(x, y, multiples, cum_prod, i - 2);
		egcd_reverse(x, y, multiples, cum_prod * multiples[i], i - 1);
	}
}

/**********************************************************

                        RATIONALS

**********************************************************/

// Addition of rationals
Rational add_rational(Rational q1, Rational q2) {
	Rational q;
	q.numer = q1.numer * q2.denom + q2.numer * q1.denom;
	q.denom = q1.denom * q2.denom;
	return q.simplify();
}

// Multiplication of rationals
Rational mult_rational(int n, Rational q) {
	Rational ret = {n * q.numer, q.denom};
	return ret.simplify();
}
Rational mult_rational(Rational q1, Rational q2) {
	Rational q;
	q.numer = q1.numer * q2.numer;
	q.denom = q1.denom * q2.denom;
	return q.simplify();
}

/**********************************************************

                        VECTORS

**********************************************************/

// Addition of vectors
Vector_2D add_2D_vec(Vector_2D v1, Vector_2D v2) {
	Vector_2D v;
	v.x = add_rational(v1.x, v2.x);
	v.y = add_rational(v1.y, v2.y);
	return v;
}

// Multiplication of vectors
Vector_2D scalar_mult_2D(int n, Vector_2D v) {
	Vector_2D ret = {mult_rational(n, v.x), mult_rational(n, v.y)};
	return ret;
}
Vector_2D scalar_mult_2D(Rational q, Vector_2D v) {
	Vector_2D ret = {mult_rational(q, v.x), mult_rational(q, v.y)};
	return ret;
}

// Prints out a 2D vector
void print_2D_vec(Vector_2D v) {
	printf("2D vector: (%d/%d, %d/%d)\n", v.x.numer, v.x.denom, v.y.numer, v.y.denom);
}

/**********************************************************

                        MISC

**********************************************************/

void print_functions() {
	string basic = "print: num\n"
	               "mod: num, MOD\n"
	               "pow: base, power, MOD\n"
	               "gcd: num1, num2\n",
	       num_theory = "egcd: num1, num2, value\n",
	       rationals = "addQ: q1, q2\n"
	                   "multQ: n/q1, q2\n",
	       vec_2D = "a2v: v1, v2\n"
	                "scalar2v: n/q, v\n"
	                "print2v: v\n";

	printf("\nBasic functions\n%s"
	       "\nNumber theory\n%s"
	       "\nRationals\n%s"
	       "\n2D Vec\n%s",
	       basic.c_str(),
	       num_theory.c_str(),
	       rationals.c_str(),
	       vec_2D.c_str());
}