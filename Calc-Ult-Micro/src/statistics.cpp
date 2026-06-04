#include "statistics.h"
#include "math.h"
#include "safeinput.hpp"
#include <iostream>
#include <iomanip>
#include <string>

static bool yesno(const std::string &prompt) {
	std::string ans = safeInput<std::string>(prompt);
	return (ans == "y" || ans == "Y" || ans == "yes" || ans == "Yes");
}

static void stage1(StatData &d) {
	d.numInt  = safeInput<int>("Enter number of integer columns: ");
	d.rowInt  = (d.numInt > 0) ? safeInput<int>("Enter number of rows for integers: ") : 0;
	if (d.numInt == 0 || yesno("Add real number columns? [y/n]: ")) {
		d.numReal = safeInput<int>("Enter number of real columns: ");
		d.rowReal = safeInput<int>("Enter number of rows for reals: ");
	} else {
		d.numReal = 0;
		d.rowReal = 0;
	}
	if (yesno("Add string columns? [y/n]: ")) {
		d.numStr = safeInput<int>("Enter number of string columns: ");
		d.rowStr = safeInput<int>("Enter number of rows for strings: ");
	} else {
		d.numStr = 0;
		d.rowStr = 0;
	}
	d.total = d.numInt + d.numReal + d.numStr;
	std::cout << "Total columns: " << d.total
	          << " | Int: "    << d.numInt
	          << " | Real: "   << d.numReal
	          << " | String: " << d.numStr << "\n";
}

static void stage2(StatData &d) {
	if (d.numInt > 0) {
		d.integers = new int*[d.numInt];
		for (int i = 0; i < d.numInt; i++) {
			d.integers[i] = new int[d.rowInt];
			std::cout << "Integer column " << i+1 << " of " << d.numInt << ":\n";
			for (int j = 0; j < d.rowInt; j++)
				d.integers[i][j] = safeInput<int>("  value: ");
		}
	}
	if (d.numReal > 0) {
		d.reals = new double*[d.numReal];
		for (int i = 0; i < d.numReal; i++) {
			d.reals[i] = new double[d.rowReal];
			std::cout << "Real column " << i+1 << " of " << d.numReal << ":\n";
			for (int j = 0; j < d.rowReal; j++)
				d.reals[i][j] = safeInput<double>("  value: ");
		}
	}
	if (d.numStr > 0) {
		d.strings = new std::string*[d.numStr];
		for (int i = 0; i < d.numStr; i++) {
			d.strings[i] = new std::string[d.rowStr];
			std::cout << "String column " << i+1 << " of " << d.numStr << ":\n";
			for (int j = 0; j < d.rowStr; j++)
				d.strings[i][j] = safeInput<std::string>("  value: ");
		}
	}
}

static void stage3(StatData &d) {
	int colw = 12;
	std::cout << "+";
	for (int i = 0; i < d.total; i++)
		for (int k = 0; k < colw; k++) std::cout << "-";
	std::cout << "+\n";
	std::cout << "|";
	int col = 0;
	for (int i = 0; i < d.numInt;  i++) { std::cout << std::setw(colw) << ("INT_"  + std::to_string(i+1)) << "|"; col++; }
	for (int i = 0; i < d.numReal; i++) { std::cout << std::setw(colw) << ("REAL_" + std::to_string(i+1)) << "|"; col++; }
	for (int i = 0; i < d.numStr;  i++) { std::cout << std::setw(colw) << ("STR_"  + std::to_string(i+1)) << "|"; col++; }
	std::cout << "\n";
	std::cout << "+";
	for (int i = 0; i < d.total; i++)
		for (int k = 0; k < colw; k++) std::cout << "-";
	std::cout << "+\n";
	int maxrows = 0;
	if (d.numInt  > 0 && d.rowInt  > maxrows) maxrows = d.rowInt;
	if (d.numReal > 0 && d.rowReal > maxrows) maxrows = d.rowReal;
	if (d.numStr  > 0 && d.rowStr  > maxrows) maxrows = d.rowStr;
	for (int j = 0; j < maxrows; j++) {
		std::cout << "|";
		for (int i = 0; i < d.numInt;  i++)
			std::cout << std::setw(colw) << (j < d.rowInt ? d.integers[i][j] : 0) << "|";
		for (int i = 0; i < d.numReal; i++)
			std::cout << std::setw(colw) << (j < d.rowReal ? d.reals[i][j] : 0.0) << "|";
		for (int i = 0; i < d.numStr;  i++)
			std::cout << std::setw(colw) << (j < d.rowStr ? d.strings[i][j] : "") << "|";
		std::cout << "\n";
	}
	std::cout << "+";
	for (int i = 0; i < d.total; i++)
		for (int k = 0; k < colw; k++) std::cout << "-";
	std::cout << "+\n";
}

static void stage4(StatData &d) {
	std::cout << "\nSTAGE 4: Dataset Computation\n";
	std::cout << "Available column types and indices:\n";
	for (int i = 0; i < d.numInt;  i++) std::cout << "  INT_"  << i+1 << "  (integer)\n";
	for (int i = 0; i < d.numReal; i++) std::cout << "  REAL_" << i+1 << " (real)\n";
	for (int i = 0; i < d.numStr;  i++) std::cout << "  STR_"  << i+1 << "  (string)\n";
	std::cout << "\nSelect column A type [int/real]: ";
	std::string typeA = safeInput<std::string>("");
	std::cout << "Select column A index (1-based): ";
	int idxA = safeInput<int>("") - 1;
	std::cout << "Select column B type [int/real]: ";
	std::string typeB = safeInput<std::string>("");
	std::cout << "Select column B index (1-based): ";
	int idxB = safeInput<int>("") - 1;
	bool validA = (typeA=="int"  && idxA >= 0 && idxA < d.numInt)  ||
	              (typeA=="real" && idxA >= 0 && idxA < d.numReal);
	bool validB = (typeB=="int"  && idxB >= 0 && idxB < d.numInt)  ||
	              (typeB=="real" && idxB >= 0 && idxB < d.numReal);
	if (!validA || !validB) { std::cout << "Invalid column selection.\n"; return; }
	std::cout << "\nAvailable operations:\n";
	std::cout << "  Arithmetic : +  -  *  /\n";
	std::cout << "  Power      : pow (real^real)\n";
	std::cout << "  Roots      : sqrt  nroot\n";
	std::cout << "  Log        : ln  logb\n";
	std::cout << "  Integer    : gcd  ^  mul2  div2  find  ogl\n";
	std::cout << "  Output     : frac\n";
	std::string operation = safeInput<std::string>("Operation: ");
	int rowA = (typeA=="int") ? d.rowInt  : d.rowReal;
	int rowB = (typeB=="int") ? d.rowInt  : d.rowReal;
	int rows = (rowA < rowB) ? rowA : rowB;
	std::cout << "\nResults (" << rows << " rows):\n";
	std::cout << "+------------+------------+------------+\n";
	std::cout << "|      A     |      B     |   RESULT   |\n";
	std::cout << "+------------+------------+------------+\n";
	for (int j = 0; j < rows; j++) {
		double a = (typeA=="int") ? (double)d.integers[idxA][j] : d.reals[idxA][j];
		double b = (typeB=="int") ? (double)d.integers[idxB][j] : d.reals[idxB][j];
		std::cout << "| " << std::setw(10) << a << " | " << std::setw(10) << b << " | ";
		if      (operation == "+")    std::cout << std::setw(10) << a+b;
		else if (operation == "-")    std::cout << std::setw(10) << a-b;
		else if (operation == "*")    std::cout << std::setw(10) << a*b;
		else if (operation == "/")    std::cout << std::setw(10) << (b!=0 ? a/b : 0);
		else if (operation == "pow")  std::cout << std::setw(10) << mfpow(a, b);
		else if (operation == "sqrt") std::cout << std::setw(10) << msqrt(a);
		else if (operation == "ln")   std::cout << std::setw(10) << mln(a);
		else if (operation == "logb") {
			double base = safeInput<double>("Base for row " + std::to_string(j+1) + ": ");
			std::cout << std::setw(10) << mlog(a, base);
		}
		else if (operation == "nroot") {
			int n = safeInput<int>("n for row " + std::to_string(j+1) + ": ");
			std::cout << std::setw(10) << nthroot(a, n);
		}
		else if (operation == "gcd") {
			if (typeA != "int" || typeB != "int") std::cout << "INT ONLY";
			else std::cout << std::setw(10) << mgcd((int)a, (int)b);
		}
		else if (operation == "^") {
			if (typeA != "int" || typeB != "int") std::cout << "INT ONLY";
			else std::cout << std::setw(10) << mfpow((int)a, (int)b);
		}
		else if (operation == "mul2") {
			if (typeA != "int" || typeB != "int") std::cout << "INT ONLY";
			else std::cout << std::setw(10) << ((int)a << (int)b);
		}
		else if (operation == "div2") {
			if (typeA != "int" || typeB != "int") std::cout << "INT ONLY";
			else std::cout << std::setw(10) << ((int)b >> (int)a);
		}
		else if (operation == "find") {
			if (typeA != "int" || typeB != "int") std::cout << "INT ONLY";
			else std::cout << std::setw(10) << numfinder((int)a, (int)b);
		}
		else if (operation == "ogl") {
			if (typeA != "int" || typeB != "int") std::cout << "INT ONLY";
			else std::cout << std::setw(10) << ogl((int)a);
		}
		else if (operation == "frac") {
			int p, q;
			toFraction(a, p, q);
		}
		else { std::cout << "UNKNOWN OP"; }
		std::cout << " |\n";
	}
	std::cout << "+------------+------------+------------+\n";
	if (yesno("Save results as a new real column? [y/n]: ")) {
		double **newReals = new double*[d.numReal + 1];
		for (int i = 0; i < d.numReal; i++) newReals[i] = d.reals[i];
		newReals[d.numReal] = new double[rows];
		for (int j = 0; j < rows; j++) {
			double a = (typeA=="int") ? (double)d.integers[idxA][j] : d.reals[idxA][j];
			double b = (typeB=="int") ? (double)d.integers[idxB][j] : d.reals[idxB][j];
			if      (operation == "+")   newReals[d.numReal][j] = a+b;
			else if (operation == "-")   newReals[d.numReal][j] = a-b;
			else if (operation == "*")   newReals[d.numReal][j] = a*b;
			else if (operation == "/")   newReals[d.numReal][j] = (b!=0) ? a/b : 0;
			else if (operation == "pow") newReals[d.numReal][j] = mfpow(a, b);
			else                         newReals[d.numReal][j] = 0;
		}
		for (int i = 0; i < d.numReal; i++) delete[] d.reals[i];
		delete[] d.reals;
		d.reals = newReals;
		d.numReal++;
		d.rowReal = rows;
		d.total++;
		std::cout << "Saved as REAL_" << d.numReal << "\n";
		stage3(d);
	}
}

static void freeStatData(StatData &d) {
	for (int i = 0; i < d.numInt;  i++) delete[] d.integers[i];
	for (int i = 0; i < d.numReal; i++) delete[] d.reals[i];
	for (int i = 0; i < d.numStr;  i++) delete[] d.strings[i];
	if (d.numInt  > 0) delete[] d.integers;
	if (d.numReal > 0) delete[] d.reals;
	if (d.numStr  > 0) delete[] d.strings;
}

void statisticscli() {
	std::cout << "STATISTIC STAGE\n";
	std::cout << "STAGE 1: Data typing\nSTAGE 2: Data entry\nSTAGE 3: Pretty print\nSTAGE 4: Compute\n";
	StatData d = {0};
	stage1(d);
	stage2(d);
	stage3(d);
	stage4(d);
	freeStatData(d);
}
