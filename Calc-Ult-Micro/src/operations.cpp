#include "operations.h"
#include "math.h"
#include "safeinput.hpp"
#include <iostream>
#include <iomanip>
#include <climits>
#include <cfloat>

void OperationIdentifier(int a, int b, const std::string &operation) {
	if (operation == "+") {
		if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b))
			std::cout << "int Overflow\n";
		else std::cout << a + b << "\n";
	}
	if (operation == "-") {
		if ((b < 0 && a > INT_MAX + b) || (b > 0 && a < INT_MIN + b))
			std::cout << "int Overflow\n";
		else std::cout << a - b << "\n";
	}
	if (operation == "*") {
		if (a != 0 && b != 0 && dabs((double)a) > dabs((double)INT_MAX / b))
			std::cout << "int Overflow\n";
		else std::cout << a * b << "\n";
	}
	if (operation == "/") {
		if (b == 0) std::cout << "int Overflow\n";
		else std::cout << a / b << "\n";
	}
	if (operation == "gcd")     { std::cout << mgcd(a, b) << "\n"; }
	if (operation == "frac") {
		int c, d;
		toFraction(a, c, d);
		std::cout << " ";
		toFraction(b, c, d);
	}
	if (operation == "^")       { npow(a, b); }
	if (operation == "logb") {
		double base = safeInput<double>("Enter [real number] base:");
		std::cout << mlog(a, base) << " " << mlog(b, base) << "\n";
	}
	if (operation == "ln")      { std::cout << mln(a) << " " << mln(b) << "\n"; }
	if (operation == "mul2") {
		if (b < 0 || b >= 31) std::cout << "int Overflow\n";
		else std::cout << (double)(a << b) << "\n";
	}
	if (operation == "div2")    { std::cout << (double)(b >> a) << "\n"; }
	if (operation == "sepmul2") {
		if (a < 0 || a >= 31) std::cout << "int Overflow\n";
		else std::cout << (double)(1 << a) << "\n";
	}
	if (operation == "sepdiv2") { std::cout << (double)(1 >> a) << "\n"; }
	if (operation == "find")    { std::cout << numfinder(a, b) << "\n"; }
	if (operation == "ogl")     { std::cout << ogl(a) << " " << ogl(b) << "\n"; }
	if (operation == "sqrt")    { std::cout << msqrt(a) << " " << msqrt(b) << "\n"; }
	if (operation == "sin")     { std::cout << sine(a) << " " << sine(b) << "\n"; }
	if (operation == "cos")     { std::cout << cosine(a) << " " << cosine(b) << "\n"; }
	if (operation == "tan" || operation == "tg") { std::cout << tangent(a) << " " << tangent(b) << "\n"; }
	if (operation == "sec")     { std::cout << secant(a) << " " << secant(b) << "\n"; }
	if (operation == "csc")     { std::cout << cosecant(a) << " " << cosecant(b) << "\n"; }
	if (operation == "ctg" || operation == "cotan") { std::cout << cotangent(a) << " " << cotangent(b) << "\n"; }
}

void OperationRealidentifier(double a, double b, const std::string &operation) {
	auto check = [](double r) -> bool { return r == r + 1; };
	if (operation == "+") {
		double r = a + b;
		if (check(r)) std::cout << "double Overflow\n";
		else std::cout << r << "\n";
	}
	if (operation == "-") {
		double r = a - b;
		if (check(r)) std::cout << "double Overflow\n";
		else std::cout << r << "\n";
	}
	if (operation == "*") {
		if (a != 0 && b != 0 && dabs(a) > DBL_MAX / dabs(b))
			std::cout << "double Overflow\n";
		else std::cout << a * b << "\n";
	}
	if (operation == "/") {
		if (b == 0) std::cout << "double Overflow\n";
		else {
			double r = a / b;
			if (check(r)) std::cout << "double Overflow\n";
			else std::cout << r << "\n";
		}
	}
	if (operation == "sqrt") { std::cout << msqrt(a) << " " << msqrt(b) << "\n"; }
	if (operation == "pow") {
		double r = mfpow(a, b);
		if (check(r)) std::cout << "double Overflow\n";
		else std::cout << r << "\n";
	}
	if (operation == "nroot") {
		int n = safeInput<int>("Enter root order: ");
		std::cout << "\n" << nthroot(a, n) << " " << nthroot(b, n) << "\n";
	}
	if (operation == "epow") { std::cout << meexp(a) << " " << meexp(b) << "\n"; }
	if (operation == "%") {
		int p = safeInput<int>("Enter precision: ");
		percents(a, b, p);
		std::cout << "\n";
	}
}

void FinaOperationIdentifier(const std::string &operation) {
	if (operation == "%") {
		int p = safeInput<int>("ENTER PRECISION: ");
		double a = safeInput<double>("ENTER NUMBER a: ");
		double b = safeInput<double>("ENTER NUMBER b: ");
		percents(a, b, p);
	}
	if (operation == "simpledebt") {
		double a = safeInput<double>("DEBT: SUM is ... ");
		double b = safeInput<double>("DEBT: YEARS are ... ");
		double r = safeInput<double>("Enter Rate offered by bank: ");
		std::cout << "TOTAL INTEREST: " << a * (r / 100) * b << "\n";
		std::cout << "YEARLY PAY: " << a * (r / 100) << "\n";
		std::cout << "AVERAGE MONTHLY PAY: " << a * (r / 100) / 12 << "\n";
		std::cout << "DAILY IMPACT: " << std::fixed << std::setprecision(3) << a * (r / 100) / 365 << "\n";
	}
	if (operation == "complexdebt") {
		double a = safeInput<double>("DEBT: INITIAL SUM is ... ");
		double b = safeInput<double>("DEBT: YEARS are ... ");
		double r = safeInput<double>("Enter Rate offered by bank: ");
		std::cout << "TOTAL INTEREST: " << a * mpow(1 + r / 100, b) - a << "\n";
		for (int i = 1; i <= b; i++) {
			std::cout << "YEAR " << i << " INTEREST IS "
			          << a * mpow(1 + r / 100, i) - a * mpow(1 + r / 100, i - 1) << "\n";
		}
	}
}
