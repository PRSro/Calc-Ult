#include "bigint.h"
#include "math.h"
#include "safeinput.hpp"
#include <iostream>
#include <string>
#include <vector>

void stringToArray(const std::string &a, const std::string &b, int *anr, int *bnr) {
	int i = -1;
	for (char c : a) anr[++i] = c - '0';
	i = -1;
	for (char c : b) bnr[++i] = c - '0';
}

void ArithmeticIdentifier(int *anr, int *bnr, int *cnr, int la, int lb, const std::string &operation, int &ma) {
	ma = (la >= lb) ? la : lb;
	if (operation == "+") {
		int remainder = 0;
		for (int i = 0; i < ma; i++) {
			int avr = (la > i) ? anr[la - i - 1] : 0;
			int bvr = (lb > i) ? bnr[lb - i - 1] : 0;
			int s = avr + bvr + remainder;
			cnr[ma - i] = s % 10;
			remainder = s / 10;
		}
		cnr[0] = remainder;
	}
	if (operation == "-") {
		int cmp = vectorcomparison(la, lb, anr, bnr);
		if (cmp == 0) {
			cnr[0] = 0;
		} else if (cmp == -1) {
			int borrow = 0;
			for (int i = 0; i < ma; i++) {
				int avr = (la > i) ? anr[la - i - 1] : 0;
				int bvr = (lb > i) ? bnr[lb - i - 1] : 0;
				avr -= borrow;
				int s = avr - bvr;
				if (s < 0) { borrow = 1; s += 10; }
				else borrow = 0;
				cnr[ma - i] = s;
			}
			cnr[0] = 0;
		} else if (cmp == -2) {
			int borrow = 0;
			for (int i = 0; i < ma; i++) {
				int avr = (la > i) ? bnr[la - i - 1] : 0;
				int bvr = (lb > i) ? anr[lb - i - 1] : 0;
				avr -= borrow;
				int s = avr - bvr;
				if (s < 0) { borrow = 1; s += 10; }
				else borrow = 0;
				cnr[ma - i] = s;
			}
			cnr[0] = -1;
		}
	}
}

void ArrayTostring(std::string &c, int *cnr, int ma) {
	if (cnr[0] == -1) c += '-';
	bool lead = true;
	for (int i = 0; i <= ma; i++) {
		if (cnr[i] == -1) continue;
		if (lead && cnr[i] == 0) continue;
		lead = false;
		c += (char)('0' + cnr[i]);
	}
	if (c.empty() || c == "-") c = "0";
}

void masscli(int *cnr) {
	std::cout << "------------------------------------------------------------WARNING-----------------------------------------------------\n";
	std::cout << "This mode supports numbers with 1000!\n";
	std::cout << "As of V1.1.0, the only available operation for this mode is + and -\n";
	std::cout << "--------------------------------------------------------END OF WARNING--------------------------------------------------\n";
	std::string a, b, operation;
	while (true) {
		operation = safeInput<std::string>("CALC: ");
		if (operation == "exit") return;
		a = safeInput<std::string>("Vector 1: ");
		b = safeInput<std::string>("Vector 2: ");
		int la = a.length(), lb = b.length(), ma;
		std::vector<int> anr(a.length()), bnr(b.length());
		std::string c = "";
		stringToArray(a, b, anr.data(), bnr.data());
		ArithmeticIdentifier(anr.data(), bnr.data(), cnr, la, lb, operation, ma);
		ArrayTostring(c, cnr, ma);
		std::cout << c << "\n";
	}
}
