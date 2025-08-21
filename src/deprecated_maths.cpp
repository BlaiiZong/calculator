#include "deprecated_maths.h"
#include <iostream>
#define nl << "\n"
#define cnl cout nl
using namespace std;
string command = "";

int main() {
	egcd(2584, 4181, 1000000);
	command = "q";
	while (command != "q") {
		if (command == "f" || command == "functions") {
			print_functions();
		}
		else if (command == "print") {
			int num;
			cin >> num;
			print(num);
		}
		else if (command == "mod") {
			int num, MOD;
			cin >> num >> MOD;
			mod(num, MOD);
		}
		else if (command == "pow") {
			int base, power, MOD;
			cin >> base >> power >> MOD;
			pow(base, power, MOD);
		}
		else if (command == "gcd") {
			int num1, num2;
			cin >> num1 >> num2;
			gcd(num1, num2);
		}
		else if (command == "egcd") {
			int num1, num2, value;
			cin >> num1 >> num2 >> value;
			egcd(num1, num2, value);
		}
		cout << "Enter command: ";
		cin >> command;
	}

	return 0;
}
