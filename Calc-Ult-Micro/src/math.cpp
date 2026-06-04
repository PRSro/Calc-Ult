#include "math.h"
#include <iostream>
#include <iomanip>
#include <climits>
#include <cfloat>

const double e = 2.71828182845904523536;
const double pi = 3.14159265358979323846;
const double ln2 = 0.6931471805599453;

int iabs(int a) {
	int mask = a >> 31;
	return (a + mask) ^ mask;
}

double dabs(double a) {
	return (a < 0) ? -a : a;
}

int mgcd(int a, int b) {
	int c = a, d = b;
	while (d != 0) {
		int r = c % d;
		c = d;
		d = r;
	}
	return c;
}

double mpow(double a, int b) {
	if (b == 0) return 1;
	if (b == 1) return a;
	double aa = dabs(a);
	if (b > 1) {
		double c = a;
		for (int i = 1; i < b; i++) {
			if (dabs(c) > DBL_MAX / aa) return 0;
			c *= a;
		}
		return c;
	} else {
		if (a == 0) return 0;
		double c = a;
		int posb = -b;
		for (int i = 1; i < posb; i++) {
			if (dabs(c) > DBL_MAX / aa) return 0;
			c *= a;
		}
		return 1.0 / c;
	}
}

int npow(int a, int b) {
	if (b < 0) { std::cout << "int Overflow\n"; return 0; }
	if (b == 0) { std::cout << "1\n"; return 1; }
	if (b == 1) { std::cout << a << "\n"; return a; }
	int c = a;
	for (int i = 1; i < b; i++) {
		if (c > INT_MAX / a) { std::cout << "int Overflow\n"; return 0; }
		c *= a;
	}
	std::cout << c << "\n";
	return c;
}

void toFraction(double exp, int &p, int &q) {
	q = 1;
	while (exp - (int)exp > 0.000001) {
		exp *= 10;
		q *= 10;
	}
	p = (int)exp;
	int g = mgcd(p < 0 ? -p : p, q);
	p /= g;
	q /= g;
	std::cout << p << "/" << q;
}

double msqrt(double a) {
	if (a < 0) return -1;
	double c = a, c1 = 1;
	while (c - c1 > 0.00000001 || c1 - c > 0.00000001) {
		c1 = c;
		c = (c + a / c) / 2;
	}
	return c;
}

double nthroot(double a, int n) {
	if (a < 0 && n % 2 == 0) return -1;
	double x = a / n;
	double x1;
	for (int i = 0; i < 1000; i++) {
		x1 = ((n - 1) * x + a / mpow(x, n - 1)) / n;
		if (x1 - x < 0.00000001 && x - x1 < 0.00000001) break;
		x = x1;
	}
	return x1;
}

double mln(double a) {
	if (a <= 0) return -1;
	int k = 0;
	while (a > 1.5) { a /= 2.0; k++; }
	while (a < 0.5) { a *= 2.0; k--; }
	double z = (a - 1.0) / (a + 1.0);
	double z2 = z * z;
	double term = z;
	double result = z;
	for (int i = 1; i < 100; i++) {
		term *= z2;
		result += term / (2 * i + 1);
	}
	return 2.0 * result + k * ln2;
}

double mlog(double a, double base) {
	return mln(a) / mln(base);
}

double meexp(double x) {
	double result = 1.0, term = 1.0;
	for (int i = 1; i < 150; i++) {
		term *= x / i;
		result += term;
		if (dabs(term) < 0.000000000001) break;
	}
	return result;
}

double mfpow(double a, double b) {
	if (a == 0) return 0;
	if (b == 0) return 1;
	if (a < 0) return -1;
	return meexp(b * mln(a));
}

int numfinder(int a, int b) {
	int c = a, r, cnt = 0;
	while (c != 0) {
		r = c % 10;
		if (r == b) cnt++;
		c /= 10;
	}
	return cnt;
}

void percents(double a, double b, int s) {
	double mi = (a < b) ? a : b;
	double ma = (a < b) ? b : a;
	double p = (double)mi * 100 / ma;
	std::cout << mi << " represents " << std::fixed << std::setprecision(s) << p << "% of " << ma;
}

int ogl(int a) {
	int ogl = 0, n = a;
	while (n != 0) {
		ogl = ogl * 10 + n % 10;
		n /= 10;
	}
	return ogl;
}

int ivectorcomparison(int ll, int *anr, int *bnr) {
	for (int i = 0; i < ll; i++) {
		if (anr[i] == bnr[i]) continue;
		else if (anr[i] > bnr[i]) return -1;
		else return -2;
	}
	return 0;
}

int vectorcomparison(int la, int lb, int *anr, int *bnr) {
	if (la < lb) return -2;
	else if (la > lb) return -1;
	else {
		int shortcut = 0;
		for (int i = 0; i < la; i++) {
			if (anr[i] == bnr[i]) shortcut++;
			else break;
		}
		if (shortcut == la) return 0;
		else return ivectorcomparison(shortcut, anr, bnr);
	}
}

long long factorial(int n) {
	if (n < 0) { std::cout << "long long Overflow\n"; return 0; }
	long long fn = 1;
	while (n > 1) {
		if (fn > LLONG_MAX / n) { std::cout << "long long Overflow\n"; return 0; }
		fn *= n; n--;
	}
	return fn;
}

double sine(double a) {
	int texp = 3;
	double rez = a;
	int sign = -1;
	while (texp != 1001) {
		rez += sign * mfpow(a, texp) / factorial(texp);
		sign *= -1;
		texp += 2;
	}
	return rez;
}

double cosine(double a) {
	int texp = 2;
	double rez = 1.0;
	int sign = -1;
	while (texp != 1001) {
		rez += sign * mfpow(a, texp) / factorial(texp);
		sign *= -1;
		texp += 2;
	}
	return rez;
}

double tangent(double a) {
	double s = sine(a), c = cosine(a);
	if (dabs(s) < 1e-12 && dabs(c) < 1e-12) return -1;
	return s / c;
}

double cotangent(double a) {
	double s = sine(a);
	if (dabs(s) < 1e-12) return -1;
	return cosine(a) / s;
}

double secant(double a) {
	double c = cosine(a);
	if (dabs(c) < 1e-12) return -1;
	return 1.0 / c;
}

double cosecant(double a) {
	double s = sine(a);
	if (dabs(s) < 1e-12) return -1;
	return 1.0 / s;
}

double circlearea(double a) {
	return pi * a * a;
}

double spherevolume(double a) {
	return 1.333333333333333333 * circlearea(a) * a;
}

double spheresurface(double a) {
	return 4 * circlearea(a);
}
