// Concept project for a sample TUI application working solely on cpp. For future projects
// A basic project good for any started. Even ai can make it so i added some interesting functions to extent the terminal
#include <iostream>
#include <string>
#include <iomanip>
/*---VARIABLES---*/
//to be transported in another file

struct cart2 {
	double x, y;
} cartlist[10001];

struct StatData {
	int numInt, numReal, numStr;
	int rowInt, rowReal, rowStr;
	int total;
	int **integers;
	double **reals;
	std::string **strings;
};
const double e=2.71828182845904523536;
const double pi=3.14159265358979323846;
const double ln2=0.6931471805599453;
/*Functions*/
//safe input template made for more security hardening, useful for a future patch, probably 1.3.5, very similar to Python
template <typename T>
T safeInput(const std::string &prompt) {
	T value;
	while (true) {
		std::cout << prompt;
		if (std::cin >> value) return value;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Invalid input, try again\n";
	}
}
//below are operation algorithms -> will think of which to add for extension
int abs(int a) {
	int mask = a >> 31;       // all 0s if positive, all 1s (0xFFFFFFFF) if negative, more efficient shifting for int
	return (a + mask) ^ mask;
}

double dabs(double a) {
	return (a<0)?-a:a;
}

int mgcd (int a, int b) {
	int c=a, d=b;
	while(d != 0)
	{
		int r=c%d;
		c=d;
		d=r;
	}
	return c;
}

double mpow(double a, int b) {
    if (b == 0) return 1;
    if (b == 1) return a;
    if (b > 1) {
        double c = a;
        for (int i = 1; i < b; i++) c *= a;
        return c;
    }
    else {
        if (a == 0) return 0;
        double c = a;
        int posb = -b;
        for (int i = 1; i < posb; i++) c *= a;
        return 1.0 / c;
    }
}

int npow(int a, int b) {
	if (b==1) return a;
	else if (b==0) return 1;
	int c=a;
	if (b>1) {
		for (int i=1; i<b; i++) {
			c*=a;
		}
		return c;
	}
	return 0;
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
	if (a<0) return -1;
	double c=a, c1=1;
	while (c-c1 > 0.00000001 || c1-c > 0.00000001) {
		c1=c;
		c=(c+a/c)/2; // Newton
	}
	return c;
}

double nthroot(double a, int n) {
	if (a < 0 && n % 2 == 0) return -1;
	double x = a / n;
	double x1;
	for (int i = 0; i < 1000; i++) {
		x1 = ((n - 1) * x + a / mpow(x, n - 1)) / n; // Newton again
		if (x1 - x < 0.00000001 && x - x1 < 0.00000001) break;
		x = x1;
	}
	return x1;
}
//ln and log models
double mln(double a) {
	if (a <= 0) return -1;
	// Reduce: if a is large, use ln(a) = ln(a/2) + ln(2)
	int k = 0;
	while (a > 1.5) {
		a /= 2.0;
		k++;
	}
	while (a < 0.5) {
		a *= 2.0;
		k--;
	}
	// Now a is near 1, series converges fast
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
	// e^x Taylor: 1 + x + x^2/2! + x^3/3! ...
	double result = 1.0, term = 1.0;
	for (int i = 1; i < 150; i++) {
		term *= x / i;
		result += term;
		if (term < 0.000000000001 && term > -0.000000000001) break;
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
	int c=a, r, cnt=0;
	while (c!=0) {
		r=c%10;
		if (r==b) cnt++;
		c/=10;
	}
	return cnt;
}

void percents(double a, double b, int s) {
	// let p% of a = b, b<a: => p=100b/a;
	double mi=(a<b)?a:b;
	double ma=(a<b)?b:a;
	double p=(double)mi*100/ma;
	std::cout << mi << " represents " <<std::fixed<<std::setprecision(s)<<p<<"% of "<<ma;
	return;
}

int ogl(int a) {
	//remade the function so it acctually returns good value | V1.2.0
	int ogl=0, n=a;
	while (n != 0) {
		ogl = ogl * 10 + n % 10;
		n /= 10;
	}
	return ogl;
}

int ivectorcomparison(int ll, int *anr, int *bnr) {
	for (int i=0; i<ll; i++) {
		if (anr[i]==bnr[i]) continue;
		else if (anr[i]>bnr[i]) {
			return -1;
		}
		else {
			return -2;
		}
	}
	return 0;
}

int vectorcomparison(int la, int lb, int *anr, int *bnr) {
	if (la<lb) return -2;
	else if (la>lb) return -1;
	//return with minus to not confuse with the shortcut calculator
	else {
		int shortcut=0;
		for (int i=0; i<la; i++) {
			if (anr[i]==bnr[i]) {
				shortcut++;
			}
			else break;
		}
		if (shortcut==la) return 0;
		else return ivectorcomparison(shortcut, anr, bnr);
	}
}

long long factorial(int n) {
	long long fn = 1;
	while (n > 1) {
		fn *= n;
		n--;
	}
	return fn;
}

double sine(double a) {
	//using the Taylor series
	int texp=3;
	double rez=a;
	long long f;
	int sign=-1;
	while(texp!=1001) {
		rez+=sign*mfpow(a, texp)/factorial(texp);
		sign*=-1;
		texp+=2;
	}
	return rez;
}

double cosine(double a) {
	//using the Taylor series
	int texp=2;
	double rez=1.0;
	long long f;
	int sign=-1;
	while(texp!=1001) {
		rez+=sign*mfpow(a, texp)/factorial(texp);
		sign*=-1;
		texp+=2;
	}
	return rez;
}

double tangent(double a) {
	double s=sine(a), c=cosine(a);
	if (dabs(s) < 1e-12 && dabs(c) < 1e-12) {
		return -1;
	}
	return s / c;
}

double cotangent(double a) {
	double s = sine(a);
	if (dabs(s) < 1e-12)
		return -1;
	return cosine(a) / s;
}

double secant(double a) {
	double c = cosine(a);
	if (dabs(c) < 1e-12)
		return -1;
	return 1.0 / c;
}

double cosecant(double a) {
	double s = sine(a);
	if (dabs(s) < 1e-12)
		return  -1;
	return 1.0 / s;
}
// P.S: AI wasnt used to any extend besides maths advice and minor debugging
// dodging case switch for now as ill add in a new version
// handling functions below
// althogh redundant might need noting

double circlearea(double a) {
	return pi*a*a;
}
double spherevolume(double a) {
	return 1.333333333333333333*circlearea(a)*a;
}
double spheresurface(double a) {
	return 4*circlearea(a);
}

void simpledebt(double a, double b, double r) {
	std::cout << "TOTAL INTEREST: " << a*(r/100)*b << "\n";
	std::cout << "YEARLY PAY: " << a*(r/100) << "\n";
	std::cout << "AVERAGE MONTHLY PAY: " << a*(r/100)/12 << "\n";
	std::cout << "DAILY IMPACT: " <<std::fixed<<std::setprecision(3)<<a*(r/100)/365 << "\n";
}

void complexdebt(double a, double b, double r) {
	std::cout << "TOTAL INTEREST: " << a*mpow(1+r/100, b)-a << "\n";
	for (int i=1; i<=b; i++) {
		std::cout << "YEAR " << i << " INTEREST IS " << a * mpow(1+r/100, i) - a * mpow(1+r/100, i-1) << "\n";
	}
}
// as of V1.2.0 all work
void OperationIdentifier(int a, int b, std::string operation) {
	if (operation=="+") {
		std::cout << a+b << "\n";
	}
	if (operation=="-") {
		std::cout << a-b << "\n";
	}
	if (operation=="*") {
		std::cout << a*b << "\n";
	}
	if (operation=="/") {
		std::cout << a/b << "\n";
	}
	if (operation=="gcd") {
		std::cout << mgcd(a, b) << "\n";
	}
	if (operation=="frac") {
		int c, d;
		toFraction(a, c, d);
		std::cout << " ";
		toFraction(b, c, d);
	}
	if (operation=="^") {
		std::cout << npow(a, b) << "\n";
	}
	if (operation=="logb") {
		std::cout << "Enter [real number] base:\n";
		double base=safeInput<double>("Enter [real number] base:");
		std::cout << mlog(a, base) << " " << mlog(b, base) << "\n";
	}
	if (operation=="ln") {
		std::cout << mln(a) << " " << mln(b) << "\n";
	}
	if (operation=="mul2") {
		std::cout << (double)(a<<b) << "\n"; // a * 2^b
	}
	if (operation=="div2") {
		std::cout << (double)(b>>a) << "\n"; // b / 2^a
	}
	if (operation=="sepmul2") {
		std::cout << (double)(1<<a) << "\n"; //
	}
	if (operation=="sepdiv2") {
		std::cout << (double)(1>>a) << "\n";
	}
	if (operation=="find") {
		std::cout << numfinder(a, b) << "\n";
	}
	if (operation=="ogl") {
		std::cout << ogl(a) << " " << ogl(b) << "\n";
	}
	if (operation=="sqrt") {
		std::cout << msqrt(a) << " " << msqrt(b) << "\n";
	}
	if (operation=="sin") {
		std::cout << sine(a) << " " << sine(b) << "\n";
	}
	if (operation=="cos") {
		std::cout << cosine(a) << " " << cosine(b) << "\n";
	}
	if (operation=="tan" || operation=="tg") {
		std::cout << tangent(a) << " " << tangent(b) << "\n";
	}
	if (operation=="sec") {
		std::cout << secant(a) << " " << secant(b) << "\n";
	}
	if (operation=="csc") {
		std::cout << cosecant(a) << " " << cosecant(b) << "\n";
	}
	if (operation=="ctg" || operation=="cotan") {
		std::cout << cotangent(a) << " " << cotangent(b) << "\n";
	}

}

void FinaOperationIdentifier(std::string operation) {
	if (operation=="%") {
		int p=safeInput<int>("ENTER PRECISION: ");
		std::cout << "\n";
		std::cout << "ENTER NUMBERS: (a>b, double)\n";
		double a=safeInput<double>("ENTER NUMBER a: ");
		double b=safeInput<double>("ENTER NUMBER b: ");
		percents(a, b, p);
	}
	if (operation=="simpledebt") {
		double a=safeInput<double>("DEBT: SUM is ... ");
		std::cout << "\n";
		double b=safeInput<double>("DEBT: YEARS are ... ");
		std::cout << "\n";
		double r=safeInput<double>("Enter Rate offered by bank: ");
		simpledebt(a, b, r);
	}
	if (operation=="complexdebt") {
		// Ds=S*r/100+b
		double a=safeInput<double>("DEBT: INITIAL SUM is ... ");
		std::cout << "\n";
		double b=safeInput<double>("DEBT: YEARS are ... ");
		std::cout << "\n";
		double r=safeInput<double>("Enter Rate offered by bank: ");
		std::cout << "\n";
		complexdebt(a, b, r);
	}
}

void OperationRealidentifier(double a, double b, std::string operation) {
	if (operation=="+") {
		std::cout << a+b << "\n";
	}
	if (operation=="-") {
		std::cout << a-b << "\n";
	}
	if (operation=="*") {
		std::cout << a*b << "\n";
	}
	if (operation=="/") {
		std::cout << a/b << "\n";
	}
	if (operation=="sqrt") {
		std::cout << msqrt(a) << " " << msqrt(b) << "\n";
	}
	if (operation=="pow") {
		std::cout << mfpow(a, b) << "\n";
	}
	if (operation=="nroot") {
		std::cout << "Integer power" << "\n";
		int n=safeInput<int>("Enter root order: ");
		std::cout << "\n" << nthroot(a, n) << " " << nthroot(b, n) << "\n";
	}
	if (operation=="epow") {
		std::cout << meexp(a) << " " << meexp(b) << "\n";
	}
	if (operation=="%") {
		std::cout << "If the numbers are double this will calculate the percentage of both the smaller one over the larger one and vice versa" << "\n";
		int p = safeInput<int>("Enter precision: ");
		percents(a, b, p);
		std::cout << "\n";
	}
	//more limited as the functions are needed manuanlly and might move each definition to a separate cpp
}

void interactivecli() {
	int a, b;
	std::string operation;
	while(true) {
		operation = safeInput<std::string>("CALC: ");
		if (operation=="exit") return;
		a = safeInput<int>("Enter A: ");
		b = safeInput<int>("Enter B: ");
		OperationIdentifier(a, b, operation);
	}
}

void mastercli() {
	double a, b;
	std::string operation;
	while(true) {
		operation = safeInput<std::string>("CALC: ");
		if (operation=="exit") return;
		a = safeInput<double>("Enter A: ");
		b = safeInput<double>("Enter B: ");
		OperationRealidentifier(a, b, operation);
	}
}
//Smart Statistics funtions remade from scratc
//Container replacing multi parse

bool yesno(const std::string &prompt) {
	std::string ans = safeInput<std::string>(prompt);
	return (ans=="y"||ans=="Y"||ans=="yes"||ans=="Yes");
}

void stage1(StatData &d) {
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

void stage2(StatData &d) {
	// allocate and fill integers
	if (d.numInt > 0) {
		d.integers = new int*[d.numInt];
		for (int i = 0; i < d.numInt; i++) {
			d.integers[i] = new int[d.rowInt];
			std::cout << "Integer column " << i+1 << " of " << d.numInt << ":\n";
			for (int j = 0; j < d.rowInt; j++) {
				d.integers[i][j] = safeInput<int>("  value: ");
			}
		}
	}
	// allocate and fill reals
	if (d.numReal > 0) {
		d.reals = new double*[d.numReal];
		for (int i = 0; i < d.numReal; i++) {
			d.reals[i] = new double[d.rowReal];
			std::cout << "Real column " << i+1 << " of " << d.numReal << ":\n";
			for (int j = 0; j < d.rowReal; j++) {
				d.reals[i][j] = safeInput<double>("  value: ");
			}
		}
	}
	// allocate and fill strings
	if (d.numStr > 0) {
		d.strings = new std::string*[d.numStr];
		for (int i = 0; i < d.numStr; i++) {
			d.strings[i] = new std::string[d.rowStr];
			std::cout << "String column " << i+1 << " of " << d.numStr << ":\n";
			for (int j = 0; j < d.rowStr; j++) {
				d.strings[i][j] = safeInput<std::string>("  value: ");
			}
		}
	}
}

void stage3(StatData &d) {
	// column widths for pretty print
	int colw = 12;

	// top border
	std::cout << "+";
	for (int i = 0; i < d.total; i++) {
		for (int k = 0; k < colw; k++) std::cout << "-";
		std::cout << "+";
	}
	std::cout << "\n";

	// header row
	std::cout << "|";
	int col = 0;
	for (int i = 0; i < d.numInt;  i++) {
		std::cout << std::setw(colw) << ("INT_"  + std::to_string(i+1)) << "|";
		col++;
	}
	for (int i = 0; i < d.numReal; i++) {
		std::cout << std::setw(colw) << ("REAL_" + std::to_string(i+1)) << "|";
		col++;
	}
	for (int i = 0; i < d.numStr;  i++) {
		std::cout << std::setw(colw) << ("STR_"  + std::to_string(i+1)) << "|";
		col++;
	}
	std::cout << "\n";

	// divider
	std::cout << "+";
	for (int i = 0; i < d.total; i++) {
		for (int k = 0; k < colw; k++) std::cout << "-";
		std::cout << "+";
	}
	std::cout << "\n";

	// rows — find max row count across all column types
	int maxrows = 0;
	if (d.numInt  > 0 && d.rowInt  > maxrows) maxrows = d.rowInt;
	if (d.numReal > 0 && d.rowReal > maxrows) maxrows = d.rowReal;
	if (d.numStr  > 0 && d.rowStr  > maxrows) maxrows = d.rowStr;

	for (int j = 0; j < maxrows; j++) {
		std::cout << "|";
		for (int i = 0; i < d.numInt;  i++) {
			if (j < d.rowInt)  std::cout << std::setw(colw) << d.integers[i][j];
			else               std::cout << std::setw(colw) << " ";
			std::cout << "|";
		}
		for (int i = 0; i < d.numReal; i++) {
			if (j < d.rowReal) std::cout << std::setw(colw) << d.reals[i][j];
			else               std::cout << std::setw(colw) << " ";
			std::cout << "|";
		}
		for (int i = 0; i < d.numStr;  i++) {
			if (j < d.rowStr)  std::cout << std::setw(colw) << d.strings[i][j];
			else               std::cout << std::setw(colw) << " ";
			std::cout << "|";
		}
		std::cout << "\n";
	}

	// bottom border
	std::cout << "+";
	for (int i = 0; i < d.total; i++) {
		for (int k = 0; k < colw; k++) std::cout << "-";
		std::cout << "+";
	}
	std::cout << "\n";
}

void stage4(StatData &d) {
	std::cout << "\nSTAGE 4: Dataset Computation\n";
	std::cout << "Available column types and indices:\n";

	// show what columns exist so user knows what to pick
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

	// validate indices
	bool validA = (typeA=="int"  && idxA >= 0 && idxA < d.numInt)  ||
	              (typeA=="real" && idxA >= 0 && idxA < d.numReal);
	bool validB = (typeB=="int"  && idxB >= 0 && idxB < d.numInt)  ||
	              (typeB=="real" && idxB >= 0 && idxB < d.numReal);

	if (!validA || !validB) {
		std::cout << "Invalid column selection.\n";
		return;
	}

	std::cout << "\nAvailable operations:\n";
	std::cout << "  Arithmetic : +  -  *  /\n";
	std::cout << "  Power      : pow (real^real)\n";
	std::cout << "  Roots      : sqrt  nroot\n";
	std::cout << "  Log        : ln  logb\n";
	std::cout << "  Integer    : gcd  ^  mul2  div2  find  ogl\n";
	std::cout << "  Output     : frac\n";
	std::cout << "NOTE: integer-only ops require int columns\n";
	std::string operation = safeInput<std::string>("Operation: ");
	// determine row count — use the shorter column to avoid out of bounds
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
		std::cout << "| " << std::setw(10) << a << " | "
		          << std::setw(10) << b << " | ";
		if      (operation=="+")    std::cout << std::setw(10) << a+b;
		else if (operation=="-")    std::cout << std::setw(10) << a-b;
		else if (operation=="*")    std::cout << std::setw(10) << a*b;
		else if (operation=="/")    std::cout << std::setw(10) << (b!=0 ? a/b : 0);
		else if (operation=="pow")  std::cout << std::setw(10) << mfpow(a, b);
		else if (operation=="^")    std::cout << std::setw(10) << mfpow(a, b);
		else if (operation=="sqrt") std::cout << std::setw(10) << msqrt(a);
		else if (operation=="ln")   std::cout << std::setw(10) << mln(a);
		else if (operation=="logb") {
			double base = safeInput<double>("Base for row " + std::to_string(j+1) + ": ");
			std::cout << std::setw(10) << mlog(a, base);
		}
		else if (operation=="nroot") {
			int n = safeInput<int>("n for row " + std::to_string(j+1) + ": ");
			std::cout << std::setw(10) << nthroot(a, n);
		}
		// integer-only operations — cast back
		else if (operation=="gcd") {
			if (typeA!="int"||typeB!="int") {
				std::cout << "INT ONLY";
			}
			else std::cout << std::setw(10) << mgcd((int)a, (int)b);
		}
		else if (operation=="^") {
			if (typeA!="int"||typeB!="int") {
				std::cout << "INT ONLY";
			}
			else std::cout << std::setw(10) << mfpow((int)a, (int)b);
		}
		else if (operation=="mul2") {
			if (typeA!="int"||typeB!="int") {
				std::cout << "INT ONLY";
			}
			else std::cout << std::setw(10) << ((int)a<<(int)b);
		}
		else if (operation=="div2") {
			if (typeA!="int"||typeB!="int") {
				std::cout << "INT ONLY";
			}
			else std::cout << std::setw(10) << ((int)b>>(int)a);
		}
		else if (operation=="find") {
			if (typeA!="int"||typeB!="int") {
				std::cout << "INT ONLY";
			}
			else std::cout << std::setw(10) << numfinder((int)a, (int)b);
		}
		else if (operation=="ogl") {
			if (typeA!="int"||typeB!="int") {
				std::cout << "INT ONLY";
			}
			else std::cout << std::setw(10) << ogl((int)a);
		}
		else if (operation=="frac") {
			int p, q;
			toFraction(a, p, q);
		}
		else {
			std::cout << "UNKNOWN OP";
		}

		std::cout << " |\n";
	}

	std::cout << "+------------+------------+------------+\n";

	// offer to save result as new column
	if (yesno("Save results as a new real column? [y/n]: ")) {
		double **newReals = new double*[d.numReal + 1];
		for (int i = 0; i < d.numReal; i++) newReals[i] = d.reals[i];
		newReals[d.numReal] = new double[rows];
		for (int j = 0; j < rows; j++) {
			double a = (typeA=="int") ? (double)d.integers[idxA][j] : d.reals[idxA][j];
			double b = (typeB=="int") ? (double)d.integers[idxB][j] : d.reals[idxB][j];
			if      (operation=="+")   newReals[d.numReal][j] = a+b;
			else if (operation=="-")   newReals[d.numReal][j] = a-b;
			else if (operation=="*")   newReals[d.numReal][j] = a*b;
			else if (operation=="/")   newReals[d.numReal][j] = (b!=0)?a/b:0;
			else if (operation=="pow") newReals[d.numReal][j] = mfpow(a, b);
			else                       newReals[d.numReal][j] = 0;
		}
		for (int i = 0; i < d.numReal; i++) delete[] d.reals[i];
        delete[] d.reals;
		d.reals = newReals;
		d.numReal++;
		d.rowReal = rows;
		d.total++;
		std::cout << "Saved as REAL_" << d.numReal << "\n";
		std::cout << "Re-running stage 3 with updated data:\n";
		stage3(d);
	}
}

void freeStatData(StatData &d) {
	for (int i = 0; i < d.numInt;  i++) delete[] d.integers[i];
	for (int i = 0; i < d.numReal; i++) delete[] d.reals[i];
	for (int i = 0; i < d.numStr;  i++) delete[] d.strings[i];
	if (d.numInt  > 0) delete[] d.integers;
	if (d.numReal > 0) delete[] d.reals;
	if (d.numStr  > 0) delete[] d.strings;
}

void statisticscli() {
	std::cout << "STATISTIC STAGE\n";
	std::cout << "STAGE 1: Data typing — define your columns and row counts\n";
	std::cout << "STAGE 2: Data entry — fill in the values\n";
	std::cout << "STAGE 3: Pretty print — table output\n\n";
	std::cout << "STAGE 4: Compute across columns operation of choice\n";
	StatData d = {0};
	stage1(d);
	stage2(d);
	stage3(d);
	stage4(d);
	freeStatData(d);
}

void calcmidpoint(double x1, double y1, double x2, double y2, double &xmid, double &ymid) {
	ymid=(y1+y2)/2;
	xmid=(x1+x2)/2;
}

double xcoef[20];
void coeficientruler(std::string f, double *xcoef, double x1, double y1) {
	int degree = 0;
	// parse space-separated coefficients from string
	// e.g. "3 2 1" -> xcoef[0]=3, xcoef[1]=2, xcoef[2]=1
	int i = 0;
	int len = f.length();
	while (i < len && degree < 20) {
		// skip spaces
		while (i < len && f.at(i) == ' ') i++;
		if (i >= len) break;
		// read sign
		double sign = 1.0;
		if (f.at(i) == '-') {
			sign = -1.0;
			i++;
		}
		else if (f.at(i) == '+') {
			i++;
		}
		// read digits including decimal
		std::string numstr = "";
		while (i < len && (f.at(i)-'0'>=0 && f.at(i)-'0'<=9 || f.at(i)=='.')) {
			numstr += f.at(i);
			i++;
		}
		if (!numstr.empty()) {
			// manual string to double
			double val=0, d=1;
			bool afterdot = false;
			for (char c:numstr) {
				if (c == '.') {
					afterdot = true;
					continue;
				}
				if (!afterdot) val = val*10 + (c-'0');
				else {
					d *= 10;
					val += (c-'0')/d;
				}
			}
			xcoef[degree++] = sign * val;
		}
	}
	// evaluate polynomial at x1
	// xcoef[0] is highest degree coefficient
	double res = 0;
	for (int k = 0; k < degree; k++) {
		res += xcoef[k] * mpow(x1, degree-1-k);
	}
	std::cout << "f(x) = ";
	for (int k = 0; k < degree; k++) {
		int power = degree-1-k;
		if (xcoef[k] == 0) continue;
		if (k > 0 && xcoef[k] > 0) std::cout << "+";
		std::cout << xcoef[k];
		if (power > 1) std::cout << "x^" << power;
		else if (power == 1) std::cout << "x";
	}
	std::cout << "\n";

	std::cout << "f(" << x1 << ") = " << res << "\n";

	if (res == y1)
		std::cout << "Point (" << x1 << ", " << y1 << ") belongs to f(x)\n";
	else
		std::cout << "Point (" << x1 << ", " << y1 << ") does NOT belong to f(x)\n" << "Closest y value at x=" << x1 << " is " << res << "\n";
}

void calcdim2(cart2 *cartlist) {
	std::string shape = safeInput<std::string>("Enter shape to work with [triangle/square/hexagon/circle/cartezian]: ");
	if (shape=="triangle") {
		std::string type = safeInput<std::string>("Select type [echilateral/isoceles/any]: ");
		double l1, l2, l3;
		double a1, a2, a3;
		if (type=="echilateral") {
			l1 = safeInput<double>("Enter side length: ");
			std::cout << "All angles are OBVIOUSLY 60 degrees\n";
			std::cout << "All heights are " << l1*msqrt(3)/2 << "\n";
			std::cout << "Area: " << (msqrt(3)/4)*l1*l1 << "\n";
			std::cout << "Perimeter: " << l1*3 << "\n";
		}
		else if(type=="isoceles") {
			l1 = safeInput<double>("Enter the repeated side length: ");
			l2 = safeInput<double>("Enter the base length: ");
			double h = msqrt(l1*l1 - (l2/2)*(l2/2));
			std::cout << "Height: " << h << "\n";
			std::cout << "Area: " << (l2*h)/2 << "\n";
			std::cout << "Perimeter: " << l1*2+l2 << "\n";
		}
		else if(type=="any") {
			std::string sol = safeInput<std::string>("Select what to give [2l1a/1l2a/3l]: ");
			std::cout << "First will check if triangle you yapping is valid\n";
			if(sol=="3l") {
				l1 = safeInput<double>("Enter side 1: ");
				l2 = safeInput<double>("Enter side 2: ");
				l3 = safeInput<double>("Enter side 3: ");
				// triangle inequality
				if(l1+l2<=l3 || l1+l3<=l2 || l2+l3<=l1) {
					std::cout << "Invalid triangle — sides violate triangle inequality\n";
					return;
				}
				// Heron's formula
				double s = (l1+l2+l3)/2;
				double area = msqrt(s*(s-l1)*(s-l2)*(s-l3));
				std::cout << "Valid triangle\n";
				std::cout << "Perimeter: " << l1+l2+l3 << "\n";
				std::cout << "Area (Heron): " << area << "\n";
			}
			else if(sol=="2l1a") {
				l1 = safeInput<double>("Enter side 1: ");
				l2 = safeInput<double>("Enter side 2: ");
				std::string chois = safeInput<std::string>("Is the angle [between] the sides or [next] to side 1: ");
				if(chois=="between") {
					a1 = safeInput<double>("Enter angle between them (degrees): ");
					double a1r = a1 * pi / 180.0;
					double l3 = msqrt(l1*l1 + l2*l2 - 2*l1*l2*cosine(a1r));
					double s = (l1 + l2 + l3) / 2;
					std::cout << "Side 3   : " << l3 << "\n";
					std::cout << "Area     : " << 0.5*l1*l2*sine(a1r) << "\n";
					std::cout << "Perimeter: " << l1+l2+l3 << "\n";
					// recover remaining angles via law of sines
					double sinA = sine(a1r) / l3;
					double a2r_acute = 0.0;
					{	// Newton asin for angle opposite l1
						double x = l1 * sinA;
						for (int i = 0; i < 100; i++) {
							double fx = sine(x) - l1*sinA;
							double dfx = cosine(x);
							if (dabs(dfx) < 1e-12) break;
							x -= fx / dfx;
						}
						a2r_acute = x;
					}
					double a2 = a2r_acute * 180.0 / pi;
					double a3 = 180.0 - a1 - a2;
					std::cout << "Angle A1 : " << a1 << " degrees (given)\n";
					std::cout << "Angle A2 : " << a2 << " degrees\n";
					std::cout << "Angle A3 : " << a3 << " degrees\n";
				}
				else {
					a1 = safeInput<double>("Enter known angle (degrees): ");
					double sina2 = (l2 * sine(a1)) / l1;
					if (dabs(sina2) > 1.0) {
						std::cout << "No valid triangle — sine out of range\n";
						return;
					}
					// ambiguous case: two possible triangles
					// asin approximation via Newton on sine(x)=sina2, x in [0, pi/2]
					double a2_acute = 0.0;
					{
						double x = sina2; // initial guess
						for (int i = 0; i < 100; i++) {
							double fx  = sine(x) - sina2;
							double dfx = cosine(x);
							if (dabs(dfx) < 1e-12) break;
							x -= fx / dfx;
						}
						a2_acute = x * 180.0 / pi; // radians to degrees
					}
					double a2_obtuse = 180.0 - a2_acute;
					double a3_acute  = 180.0 - a1 - a2_acute;
					double a3_obtuse = 180.0 - a1 - a2_obtuse;

					std::cout << "CASE 1 (acute A2): A2=" << a2_acute  << " A3=" << a3_acute  << " degrees\n";
					if (a3_acute > 0) {
						double l3_acute = (l1 * sine(a3_acute * pi / 180.0)) / sine(a1 * pi / 180.0);
						std::cout << "  Side 3: " << l3_acute << "\n";
						double s = (l1 + l2 + l3_acute) / 2;
						std::cout << "  Area  : " << msqrt(s*(s-l1)*(s-l2)*(s-l3_acute)) << "\n";
					} else {
						std::cout << "  (invalid — angles don't sum to 180)\n";
					}

					if (a3_obtuse > 0 && dabs(a2_acute - a2_obtuse) > 0.0001) {
						std::cout << "CASE 2 (obtuse A2): A2=" << a2_obtuse << " A3=" << a3_obtuse << " degrees\n";
						double l3_obtuse = (l1 * sine(a3_obtuse * pi / 180.0)) / sine(a1 * pi / 180.0);
						std::cout << "  Side 3: " << l3_obtuse << "\n";
						double s = (l1 + l2 + l3_obtuse) / 2;
						std::cout << "  Area  : " << msqrt(s*(s-l1)*(s-l2)*(s-l3_obtuse)) << "\n";
					} else {
						std::cout << "  (no second valid case)\n";
					}
				}
			}
			else if(sol=="1l2a") {
				l1 = safeInput<double>("Enter the known side: ");
				a1 = safeInput<double>("Enter angle opposite to it (degrees): ");
				a2 = safeInput<double>("Enter a second angle (degrees): ");
				a3 = 180 - a1 - a2;
				if(a3 <= 0) {
					std::cout << "Invalid — angles dont sum to 180\n";
					return;
				}
				std::cout << "Third angle: " << a3 << " degrees\n";
				// law of sines: l1/sin(a1) = l2/sin(a2) = l3/sin(a3)
				double ratio = l1 / sine(a1 * pi / 180.0);
				double l2_calc = ratio * sine(a2 * pi / 180.0);
				double l3_calc = ratio * sine(a3 * pi / 180.0);
				std::cout << "Side 2: " << l2_calc << "\n";
				std::cout << "Side 3: " << l3_calc << "\n";
				double s = (l1 + l2_calc + l3_calc) / 2;
				std::cout << "Area  : " << msqrt(s*(s-l1)*(s-l2_calc)*(s-l3_calc)) << "\n";
				std::cout << "Perimeter: " << l1 + l2_calc + l3_calc << "\n";
			}
		}
	}
	else if (shape=="square") {
		double l = safeInput<double>("Enter length of one side: ");
		std::cout << "DIAGONAL: "     << l*msqrt(2) << "\n";
		std::cout << "AREA: "         << l*l << "\n";
		std::cout << "PERIMETER: "    << l*4 << "\n";
		std::cout << "HALF DISTANCE: "<< msqrt(l*l+l*l/4) << "\n";
		std::cout << "All angles 90 degrees, diagonal splits into 45 degrees\n";
	}
	else if (shape=="hexagon") {
		double l = safeInput<double>("Enter length of one side: ");
		std::cout << "DIAGONAL COUNT: " << 9 << "\n"; // fixed: 1/2*6*(6-3) is integer division = 0
		std::cout << "LONG DIAGONAL: "  << l*2 << "\n";
		std::cout << "SHORT DIAGONAL: " << l*msqrt(3) << "\n";
		std::cout << "AREA: "           << (3*msqrt(3)/2)*l*l << "\n";
		std::cout << "PERIMETER: "      << l*6 << "\n";
		std::cout << "Interior angle: 120 degrees\n";
	}
	else if (shape=="circle") {
		double radius = safeInput<double>("Enter radius length: ");
		std::cout << "AREA: "          << circlearea(radius) << "\n";
		std::cout << "CIRCUMFERENCE: " << 2*pi*radius << "\n";
		std::cout << "DIAMETER: "      << 2*radius << "\n";
		std::cout << "\nDEF: A circle is all points equidistant from a center, that distance being the radius\n";
		std::cout << "Equation: x^2 + y^2 = r^2\n";
		std::cout << "Sine is the y coordinate, cosine the x coordinate of a point on the unit circle\n";
	}
	else if (shape=="cartezian") {
		int a = safeInput<int>("Enter number of points (max 10000): ");
		if(a <= 0 || a > 10000) {
			std::cout << "Invalid number of points\n";
			return;
		}
		for(int i=1; i<=a; i++) {
			std::cout << "Point " << i << " of " << a << " — ";
			cartlist[i].x = safeInput<double>("x."+std::to_string(i)+": ");
			cartlist[i].y = safeInput<double>("y"+std::to_string(i)+": ");
		}
		std::cout << "\n[1] Multidistance between consecutive points\n";
		std::cout << "[2] Distance between two specific points\n";
		std::cout << "[3] Midpoints between consecutive or chosen points\n";
		int task = safeInput<int>("Choose task: ");
		if(task==1) {
			// all pairs
			for(int i=1; i<=a; i++) {
				for(int j=i+1; j<=a; j++) {
					double dx = cartlist[j].x - cartlist[i].x;
					double dy = cartlist[j].y - cartlist[i].y;
					std::cout << "d(P" << i << ",P" << j << ") = " << msqrt(dx*dx+dy*dy) << "\n";
				}
			}
		}
		else if(task==2) {
			int i = safeInput<int>("Index of point 1: ");
			int j = safeInput<int>("Index of point 2: ");
			if(i<1||i>a||j<1||j>a) {
				std::cout << "Invalid indices\n";
				return;
			}
			double dx = cartlist[j].x - cartlist[i].x;
			double dy = cartlist[j].y - cartlist[i].y;
			std::cout << "Distance: " << msqrt(dx*dx+dy*dy) << "\n";
		}
		else if(task==3) {
			int mode = safeInput<int>("Consecutive of all [2] or chosen pair [1]: ");
			double v[10000][2];
			if(mode==2) {
				for(int i=1; i<a; i++) {
					calcmidpoint(cartlist[i].x, cartlist[i].y, cartlist[i+1].x, cartlist[i+1].y, v[i][0], v[i][1]);
					std::cout << "Mid(P" << i << ",P" << i+1 << ") = " << v[i][0] << " " << v[i][1] << "\n";
				}
			}
			else {
				int i = safeInput<int>("Index of point 1: ");
				int k = safeInput<int>("Index of point 2: ");
				if(i<1||i>a||k<1||k>a) {
					std::cout << "Invalid indices\n";
					return;
				}
				calcmidpoint(cartlist[i].x, cartlist[i].y, cartlist[k].x, cartlist[k].y, v[0][0], v[0][1]);
				std::cout << "Midpoint: " << v[0][0] << " " << v[0][1] << "\n";
			}
		}
	}
	else {
		std::cout << "Unknown shape\n";
	}
}

// numerical derivative via central difference
double mderiv(double (*f)(double), double x) {
	double h = 0.0001;
	return (f(x + h) - f(x - h)) / (2.0 * h);
}

// numerical integral via Simpson's rule
double mintegral(double (*f)(double), double a, double b, int n) {
	if (n % 2 != 0) n++; // Simpson needs even intervals
	double h = (b - a) / n;
	double result = f(a) + f(b);
	for (int i = 1; i < n; i++) {
		double x = a + i * h;
		result += (i % 2 == 0 ? 2.0 : 4.0) * f(x);
	}
	return result * h / 3.0;
}

// evaluate polynomial from coefficient array at x
// coefs[0] is highest degree, same convention as coeficientruler
double evalPoly(double *coefs, int degree, double x) {
	double result = 0;
	for (int i = 0; i <= degree; i++) {
		result += coefs[i] * mpow(x, degree - i);
	}
	return result;
}

// numerical derivative of polynomial at x
double derivPoly(double *coefs, int degree, double x) {
	double h = 0.0001;
	return (evalPoly(coefs, degree, x + h) - evalPoly(coefs, degree, x - h)) / (2.0 * h);
}

// numerical integral of polynomial via Simpson
double integralPoly(double *coefs, int degree, double a, double b, int n) {
	if (n % 2 != 0) n++;
	double h = (b - a) / n;
	double result = evalPoly(coefs, degree, a) + evalPoly(coefs, degree, b);
	for (int i = 1; i < n; i++) {
		double x = a + i * h;
		result += (i % 2 == 0 ? 2.0 : 4.0) * evalPoly(coefs, degree, x);
	}
	return result * h / 3.0;
}

// Newton's method root finder for polynomial
double newtonRoot(double *coefs, int degree, double guess) {
	double x = guess;
	for (int i = 0; i < 1000; i++) {
		double fx  = evalPoly(coefs, degree, x);
		double dfx = derivPoly(coefs, degree, x);
		if (dabs(dfx) < 1e-12) break;
		double xnew = x - fx / dfx;
		if (dabs(xnew - x) < 1e-10) {
			x = xnew;
			break;
		}
		x = xnew;
	}
	return x;
}

// parse coefficient string into array, returns degree
int parseCoefs(double *coefs) {
	std::cout << "Enter polynomial coefficients highest to lowest degree\n";
	std::cout << "Space separated (e.g. '3 2 1' means 3x^2 + 2x + 1): ";
	std::cin.ignore();
	std::string f;
	std::getline(std::cin, f);
	int degree = -1;
	int i = 0, len = f.length();
	while (i < len && degree < 19) {
		while (i < len && f.at(i) == ' ') i++;
		if (i >= len) break;
		double sign = 1.0;
		if      (f.at(i) == '-') {
			sign = -1.0;
			i++;
		}
		else if (f.at(i) == '+') {
			i++;
		}
		std::string numstr = "";
		while (i < len && ((f.at(i)-'0'>=0 && f.at(i)-'0'<=9) || f.at(i)=='.')) {
			numstr += f.at(i);
			i++;
		}
		if (!numstr.empty()) {
			double val = 0, d = 1;
			bool afterdot = false;
			for (char c : numstr) {
				if (c == '.') {
					afterdot = true;
					continue;
				}
				if (!afterdot) val = val * 10 + (c - '0');
				else {
					d *= 10;
					val += (c - '0') / d;
				}
			}
			coefs[++degree] = sign * val;
		}
	}
	return degree; // degree of polynomial = index of last coef
}

void printPoly(double *coefs, int degree) {
	std::cout << "f(x) = ";
	bool first = true;
	for (int i = 0; i <= degree; i++) {
		int power = degree - i;
		if (coefs[i] == 0) continue;
		if (!first && coefs[i] > 0) std::cout << "+";
		std::cout << coefs[i];
		if      (power > 1) std::cout << "x^" << power;
		else if (power == 1) std::cout << "x";
		first = false;
	}
	std::cout << "\n";
}

void calculuscli() {
	std::cout << "CALCULUS CALCULATOR\n";
	std::cout << "Works on polynomials defined by their coefficients\n";
	std::cout << "CHOOSE MODE:\n";
	std::cout << "  [1] Evaluate f(x) at a point\n";
	std::cout << "  [2] Numerical derivative f'(x) at a point\n";
	std::cout << "  [3] Numerical definite integral [a, b]\n";
	std::cout << "  [4] Find a root near a guess (Newton's method)\n";
	std::cout << "  [5] Tangent line at a point\n";
	std::cout << "  [6] Evaluate + derivative + integral in one pass\n";

	int choice = safeInput<int>("Choice: ");

	double coefs[20] = {0};
	int degree = parseCoefs(coefs);
	if (degree < 0) {
		std::cout << "No valid coefficients entered\n";
		return;
	}
	printPoly(coefs, degree);

	if (choice == 1) {
		double x = safeInput<double>("Enter x: ");
		std::cout << "f(" << x << ") = " << evalPoly(coefs, degree, x) << "\n";
	}
	else if (choice == 2) {
		double x = safeInput<double>("Enter x: ");
		std::cout << "f'(" << x << ") ≈ " << derivPoly(coefs, degree, x) << "\n";
	}
	else if (choice == 3) {
		double a = safeInput<double>("Enter lower bound a: ");
		double b = safeInput<double>("Enter upper bound b: ");
		int    n = safeInput<int>   ("Enter intervals (even, e.g. 1000): ");
		std::cout << "∫[" << a << "," << b << "] f(x) dx ≈ "
		          << integralPoly(coefs, degree, a, b, n) << "\n";
	}
	else if (choice == 4) {
		double guess = safeInput<double>("Enter initial guess: ");
		double root  = newtonRoot(coefs, degree, guess);
		std::cout << "Root near " << guess << ": x ≈ " << root << "\n";
		std::cout << "Verification: f(" << root << ") = "
		          << evalPoly(coefs, degree, root) << "\n";
	}
	else if (choice == 5) {
		double x  = safeInput<double>("Enter x: ");
		double fx  = evalPoly(coefs, degree, x);
		double dfx = derivPoly(coefs, degree, x);
		std::cout << "f(" << x << ")  = " << fx  << "\n";
		std::cout << "f'(" << x << ") = " << dfx << "\n";
		std::cout << "Tangent line: y = " << dfx << "(x - " << x << ") + " << fx << "\n";
		std::cout << "Simplified  : y = " << dfx << "x + " << (fx - dfx * x) << "\n";
	}
	else if (choice == 6) {
		double x = safeInput<double>("Enter x for evaluation and derivative: ");
		double a = safeInput<double>("Enter lower bound a for integral: ");
		double b = safeInput<double>("Enter upper bound b for integral: ");
		int    n = safeInput<int>   ("Enter intervals (e.g. 1000): ");
		std::cout << "f(" << x << ")  = " << evalPoly(coefs, degree, x)  << "\n";
		std::cout << "f'(" << x << ") = " << derivPoly(coefs, degree, x) << "\n";
		std::cout << "∫[" << a << "," << b << "] ≈ "
		          << integralPoly(coefs, degree, a, b, n) << "\n";
	}
	else {
		std::cout << "Invalid choice\n";
	}
}

double masin(double x) {
    if (x < -1 || x > 1) return -1; // out of domain
    double t = x;
    for (int i = 0; i < 100; i++) {
        double ft  = sine(t) - x;
        double dft = cosine(t);
        if (dabs(dft) < 1e-12) break;
        t -= ft / dft;
    }
    return t; // radians
}

double macos(double x) {
    if (x < -1 || x > 1) return -1;
    return (pi / 2.0) - masin(x); // identity: acos(x) = pi/2 - asin(x)
}

double matan(double x) {
    // atan(x) = asin(x / sqrt(1 + x^2))
    return masin(x / msqrt(1 + x*x));
}

void trigarith() {
    std::cout << "TRIGONOMETRY\n";
    std::cout << "  [1] sin / cos / tan / cot / sec / csc at a value\n";
    std::cout << "  [2] Inverse: asin / acos / atan\n";
    std::cout << "  [3] Degree <-> Radian converter\n";
    int choice = safeInput<int>("Choice: ");

    if (choice == 1) {
        std::string unit = safeInput<std::string>("Input in [deg] or [rad]: ");
        double val = safeInput<double>("Value: ");
        double r = (unit == "deg") ? val * pi / 180.0 : val;
        std::cout << "sin : " << sine(r)      << "\n";
        std::cout << "cos : " << cosine(r)    << "\n";
        std::cout << "tan : " << tangent(r)   << "\n";
        std::cout << "cot : " << cotangent(r) << "\n";
        std::cout << "sec : " << secant(r)    << "\n";
        std::cout << "csc : " << cosecant(r)  << "\n";
    }
    else if (choice == 2) {
        std::string fn = safeInput<std::string>("Function [asin/acos/atan]: ");
        double val = safeInput<double>("Value: ");
        std::string unit = safeInput<std::string>("Output in [deg] or [rad]: ");
        double result = -1;
        if      (fn == "asin") result = masin(val);
        else if (fn == "acos") result = macos(val);
        else if (fn == "atan") result = matan(val);
        else { std::cout << "Unknown function\n"; return; }
        if (result == -1 && fn != "atan") { std::cout << "Out of domain\n"; return; }
        if (unit == "deg") result *= 180.0 / pi;
        std::cout << fn << "(" << val << ") = " << result << "\n";
    }
    else if (choice == 3) {
        std::string dir = safeInput<std::string>("Convert [dtr] degrees to radians or [rtd] radians to degrees: ");
        double val = safeInput<double>("Value: ");
        if      (dir == "dtr") std::cout << val << " deg = " << val * pi / 180.0 << " rad\n";
        else if (dir == "rtd") std::cout << val << " rad = " << val * 180.0 / pi << " deg\n";
        else std::cout << "Unknown direction\n";
    }
    else { std::cout << "Invalid choice\n"; }
}

void calcdim3() {
    std::string shape = safeInput<std::string>("Enter shape [cube/sphere/cylinder/cone/cartezian3d]: ");

    if (shape == "cube") {
        double l = safeInput<double>("Enter side length: ");
        std::cout << "VOLUME      : " << l*l*l << "\n";
        std::cout << "SURFACE     : " << 6*l*l << "\n";
        std::cout << "FACE DIAG   : " << l*msqrt(2) << "\n";
        std::cout << "SPACE DIAG  : " << l*msqrt(3) << "\n";
        std::cout << "PERIMETER   : " << 12*l << "\n";
    }
    else if (shape == "sphere") {
        double r = safeInput<double>("Enter radius: ");
        std::cout << "VOLUME      : " << spherevolume(r) << "\n";  // already defined
        std::cout << "SURFACE     : " << spheresurface(r) << "\n"; // already defined
        std::cout << "DIAMETER    : " << 2*r << "\n";
    }
    else if (shape == "cylinder") {
        double r = safeInput<double>("Enter radius: ");
        double h = safeInput<double>("Enter height: ");
        std::cout << "VOLUME      : " << pi*r*r*h << "\n";
        std::cout << "LATERAL SA  : " << 2*pi*r*h << "\n";
        std::cout << "TOTAL SA    : " << 2*pi*r*(r+h) << "\n";
        std::cout << "SLANT HEIGHT: " << h << " (straight)\n";
    }
    else if (shape == "cone") {
        double r = safeInput<double>("Enter base radius: ");
        double h = safeInput<double>("Enter height: ");
        double sl = msqrt(r*r + h*h); // slant height
        std::cout << "SLANT HEIGHT: " << sl << "\n";
        std::cout << "VOLUME      : " << (pi*r*r*h)/3 << "\n";
        std::cout << "LATERAL SA  : " << pi*r*sl << "\n";
        std::cout << "TOTAL SA    : " << pi*r*(r+sl) << "\n";
    }
    else if (shape == "cartezian3d") {
        // extend cart2 inline with a z coordinate
        int n = safeInput<int>("Enter number of points (max 10000): ");
        if (n <= 0 || n > 10000) { std::cout << "Invalid\n"; return; }
        double px[10001], py[10001], pz[10001];
        for (int i = 1; i <= n; i++) {
            std::cout << "Point " << i << " of " << n << "\n";
            px[i] = safeInput<double>("x: ");
            py[i] = safeInput<double>("y: ");
            pz[i] = safeInput<double>("z: ");
        }
        std::cout << "[1] All pairwise distances\n";
        std::cout << "[2] Distance between two points\n";
        std::cout << "[3] Midpoint between two points\n";
        int task = safeInput<int>("Task: ");
        if (task == 1) {
            for (int i = 1; i <= n; i++)
                for (int j = i+1; j <= n; j++) {
                    double dx=px[j]-px[i], dy=py[j]-py[i], dz=pz[j]-pz[i];
                    std::cout << "d(P"<<i<<",P"<<j<<") = " << msqrt(dx*dx+dy*dy+dz*dz) << "\n";
                }
        }
        else if (task == 2) {
            int i = safeInput<int>("Point 1 index: ");
            int j = safeInput<int>("Point 2 index: ");
            if (i<1||i>n||j<1||j>n) { std::cout << "Invalid\n"; return; }
            double dx=px[j]-px[i], dy=py[j]-py[i], dz=pz[j]-pz[i];
            std::cout << "Distance: " << msqrt(dx*dx+dy*dy+dz*dz) << "\n";
        }
        else if (task == 3) {
            int i = safeInput<int>("Point 1 index: ");
            int j = safeInput<int>("Point 2 index: ");
            if (i<1||i>n||j<1||j>n) { std::cout << "Invalid\n"; return; }
            std::cout << "Midpoint: ("
                      << (px[i]+px[j])/2 << ", "
                      << (py[i]+py[j])/2 << ", "
                      << (pz[i]+pz[j])/2 << ")\n";
        }
    }
    else { std::cout << "Unknown shape\n"; }
}

void geometrycli() {
	std::cout << "GEOMETRY CALCULATOR" << "\n";
	std::cout << "This mode isnt responsible for any simulation of the provided shapes" << "\n";
	std::cout << "CHOOSE MODE: [1] cartezian/euclidean geometry 2D calculation" << "\n";
	std::cout << "             [2] cartezian/euclidean geometry 3D calculation" << "\n";
	std::cout << "             [3] trigonometric values" << "\n";
	std::cout << "             [4] calculus" << "\n";
	int choice=safeInput<int>("Choice number int value: ");
	if(choice==1) {
		cart2 cartlist[10000];
		calcdim2(cartlist);
	}
	else if (choice==2) {
		calcdim3();
	}
	else if (choice==3) {
		trigarith();
	}
	else {
		calculuscli();
	}
}

void stringToArray(const std::string &a, const std::string &b, int *anr, int *bnr) {
	int la=a.length(), lb=b.length();
	int i=-1;
	for (char c:a) {
		anr[++i]=c-'0';
	}
	i=-1;
	for (char c:b) {
		bnr[++i]=c-'0';
	}
	return;
}

void ArithmeticIdentifier(int *anr, int *bnr, int *cnr, int la, int lb, std::string operation, int &ma) {
	ma=(la>=lb)?la:lb;
	if (operation=="+") {
		int remainder=0;
		for(int i=0; i<ma; i++) {
			int avr=(la>i)?anr[la-i-1]:0;
			int bvr=(lb>i)?bnr[lb-i-1]:0;
			int s=avr+bvr+remainder;
			cnr[ma-i]=s%10;
			remainder=s/10;
			//saving result at the same digit as one calculated and doing additional steps if remainder exists
		}
		cnr[0]=remainder;
	}
	if (operation=="-") {
		int cmp=vectorcomparison(la, lb, anr, bnr);
		if (cmp==0) {
			cnr[0]=0;
		}
		else if (cmp==-1) {
			int borrow=0;
			for(int i=0; i<ma; i++) {
				int avr=(la>i)?anr[la-i-1]:0;
				int bvr=(lb>i)?bnr[lb-i-1]:0;
				avr-=borrow;
				int s=avr-bvr;
				if (s<0) {
					borrow=1;
					s+=10;
				}
				else borrow=0;// dropping next digit if necesarry / result is negative
				cnr[ma-i]=s;
				//saving result at the same digit as one calculated and doing additional steps if remainder exists
			}
			cnr[0]=0;
		}
		else if (cmp==-2) {
			int borrow=0;
			for(int i=0; i<ma; i++) {
				int avr=(la>i)?bnr[la-i-1]:0;
				int bvr=(lb>i)?anr[lb-i-1]:0; //swapped
				avr-=borrow;
				int s=avr-bvr;
				if (s<0) {
					borrow=1;
					s+=10;
				}
				else borrow=0;
				cnr[ma-i]=s;
			}
			cnr[0]=-1; //negative
		}
	}
}

void ArrayTostring(std::string &c, int *cnr, int ma) {
	if (cnr[0]==-1) c+='-';
	bool lead=true;
	for(int i=0; i<=ma; i++) {
		if (cnr[i]==-1) continue;
		if (lead && cnr[i]==0) continue;
		lead=false;
		c+=(char)('0'+cnr[i]);
	}
	if (c.empty() || c=="-") c="0";
	return;
}

void masscli(int *cnr) {
	std::cout << "------------------------------------------------------------WARNING-----------------------------------------------------" << "\n";
	std::cout << "This mode supports numbers with 1000!" << "\n";
	std::cout << "Method: from std::string it becomes a table of 100 then arithmetic is done manuanlly for each and saved in a separate array" << "\n";
	std::cout << "Manually codes since im too lazy and id like to make the project worth the effort" << "\n";
	std::cout << "As of V1.1.0, the only avabile operation for this mode is + and -" << "\n";
	std::cout << "--------------------------------------------------------END OF WARNING--------------------------------------------------" << "\n";
	std::string a, b, operation;
	while (true) {
		operation=safeInput<std::string>("CALC: ");
		if (operation=="exit") return;
		else {
			a=safeInput<std::string>("Vector 1: ");
			b=safeInput<std::string>("Vector 2: ");
			int la=a.length(), lb=b.length(), ma;
			int anr[a.length()], bnr[b.length()];
			std::string c="";
			stringToArray(a, b, anr, bnr);
			ArithmeticIdentifier(anr, bnr, cnr, la, lb, operation, ma);
			ArrayTostring(c, cnr, ma);
			std::cout << c << "\n";
		}
	}
}

void financialcli() {
	std::cout << "The Ultra Pro Corporatist Calculator made with good intentions" << "\n";
	std::cout << "Educational purposes: you will be prompted with questions for a more accurate calculation" << "\n";
	std::string operation=safeInput<std::string>("FINANCE CALC: ");
	FinaOperationIdentifier(operation);
}

//more comprehensive help

void help() {
	std::cout << "============================================================\n";
	std::cout << "          CALC-ULT | Ultimate Calculator | Help Guide        \n";
	std::cout << "============================================================\n\n";

	std::cout << "-- COMPILATION & EXECUTION --\n";
	std::cout << "  Compile  : g++ calc-ult-1filer.cpp -o calc\n";
	std::cout << "  Linux/Mac: ./calc <mode> [args]\n";
	std::cout << "  Windows  : .\\calc <mode> [args]\n\n";

	std::cout << "-- MODES --\n";
	std::cout << "  ./calc static <a> <b> <operation>   Integer arithmetic (non-interactive)\n";
	std::cout << "  ./calc interactive                  Interactive integer calculator (REPL)\n";
	std::cout << "  ./calc master                       Interactive real-number calculator (REPL)\n";
	std::cout << "  ./calc mass                         Big-number arithmetic (up to 1000 digits)\n";
	std::cout << "  ./calc financial                    Financial/debt calculator\n";
	std::cout << "  ./calc geometry                     Geometry calculator (2D/3D)\n";
	std::cout << "  ./calc converter                    Unit converter\n";
	std::cout << "  ./calc help                         Show this help message\n\n";

	std::cout << "-- STATIC MODE OPERATIONS (./calc static <a> <b> <op>) --\n";
	std::cout << "  +         Addition\n";
	std::cout << "  -         Subtraction\n";
	std::cout << "  *         Multiplication\n";
	std::cout << "  /         Division\n";
	std::cout << "  ^         Power: a^b\n";
	std::cout << "  gcd       Greatest common divisor of a and b\n";
	std::cout << "  sqrt      Square root of both a and b\n";
	std::cout << "  find      Count occurrences of digit b in number a\n";
	std::cout << "  ogl       Reverse digits of both a and b\n";
	std::cout << "  mul2      a * 2^b  (left bit-shift)\n";
	std::cout << "  div2      b / 2^a  (right bit-shift)\n";
	std::cout << "  sepmul2   2^a\n";
	std::cout << "  sepdiv2   1 >> a\n\n";

	std::cout << "-- INTERACTIVE MODE (./calc interactive) --\n";
	std::cout << "  Syntax  : CALC: <operation> <a> <b>\n";
	std::cout << "  NOTE    : For '%', 'simpledebt', 'complexdebt' — only type the operation, prompts follow\n";
	std::cout << "  exit    : Quit interactive mode\n\n";

	std::cout << "-- MASTER MODE (./calc master) — real numbers --\n";
	std::cout << "  Syntax  : CALC: <operation> <a> <b>\n";
	std::cout << "  Supports: +  -  *  /  sqrt  %\n";
	std::cout << "  exit    : Quit master mode\n\n";

	std::cout << "-- MASS MODE (./calc mass) — big integers up to 1000 digits --\n";
	std::cout << "  Syntax  : CALC: <operation> <a> <b>\n";
	std::cout << "  Supports: +  -\n";
	std::cout << "  exit    : Quit mass mode\n\n";

	std::cout << "-- FINANCIAL MODE (./calc financial) --\n";
	std::cout << "  %           Percentage: what % is the smaller of the larger number\n";
	std::cout << "  simpledebt  Simple interest: total interest, yearly & monthly pay, daily impact\n";
	std::cout << "  complexdebt Compound interest: total and per-year breakdown\n\n";

	std::cout << "-- GEOMETRY MODE (./calc geometry) --\n";
	std::cout << "  [1] 2D Cartesian — shapes: square, hexagon, circle, cartezian (point sets)\n";
	std::cout << "      cartezian sub-tasks: multidistance, midpoints, certain distance, slope\n";
	std::cout << "  [2] 3D Cartesian — (coming soon)\n";
	std::cout << "  [3] Trigonometric values — (coming soon)\n";
	std::cout << "  [4] Calculus\n\n";

	std::cout << "-- CONVERTER MODE (./calc converter) --\n";
	std::cout << "  Units: Volume, Mass, Distance, Surface, Speed, Digital Info Storage [dig],\n";
	std::cout << "         Density, Inch-to-Cm, Feet-to-m\n\n";

	std::cout << "-- CONSTANTS USED INTERNALLY --\n";
	std::cout << "  e  = 2.71828182845904523536\n";
	std::cout << "  pi = 3.14159265358979323846\n";
	std::cout << " ln2 = 0.6931471805599453\n\n";

	std::cout << "============================================================\n";
	std::cout << "  Version note: geometry 3D, trig, and calculus are stubs.\n";
	std::cout << "  Mass mode supports + and - only as of current version.\n";
	std::cout << "============================================================\n";
	std::cout << "-- OTHER FEATURES PLANNED: base converter, geometry completions";
}

void massconverter() {
	std::cout << "The mass converter is supposed to convert certain units" << "\n";
	std::string converter=safeInput<std::string>( "Choose measure to convert: Volume, Mass, Distance, Surface, Speed, Digital Info Storage [dig], Density, Inch-to-Cm, Feet-to-m: ");
}

const char padding='0';
const std::string hexalphabet="0123456789abcdef";

void split(const std::string &a, std::string &c) {
	std::string seq;
	int s=a.length();
	c="";
	if (s%2==1) {
		seq= {padding, a.at(0)};
		c+=seq+' ';
		for(int i=1; i<s; i+=2) {
			seq= {a.at(i), a.at(i+1)};
			c+=seq+' ';
		}
	}
	else {
		for(int i=0; i<s; i+=2) {
			seq= {a.at(i), a.at(i+1)};
			c+=seq+' ';
		}
	}
}

void parser(const std::string &a, std::string &final) {
	for(char l:a) {
		if (l==' ') {
			continue;
		}
		else final+=l;
	}
}

void reverser(const std::string &a, std::string &c) {
	int n=a.length();
	std::string seq;
	for (int y=n-1; y>=0; y--) {
		seq=a.at(y);
		c+=seq;
	}
}

int deconvert_pair(const std::string &pair) {
	int h = hexalphabet.find(pair.at(0));
	int l  = hexalphabet.find(pair.at(1));
	return h * 16 + l;
}

void base16_deconvert(const std::string &a, long long &b) {
	if(a=="0") {
		b=0;
		return;
	}
	bool negative = (a.at(0) == '-');
	std::string temp=negative?a.substr(1):a, clean, c;
	split(temp,c);
	parser(c, clean);
	b=0;
	int la=clean.length();
	for(int i=0; i<la; i+=2) {
		std::string pair= {clean.at(i), clean.at(i+1)};
		b=b*256+deconvert_pair(pair);
	}
	if(negative)b*=-1;
}

void base16_convert(long long b, std::string &final) {
	final="";
	if (b==0) {
		final="0";
		return;
	}
	long long d=std::abs(b);
	while(d!=0) {
		int r=d%16;
		final+=hexalphabet.at(r);
		d/=16;
	}
	std::string temp;
	reverser(final, temp);
	final=temp;
	if(b<0) final.insert(0, "-");
}

void raw_bytes_print(const std::string &a) {
	for (char c : a)
		std::cout << (int)(unsigned char)c << ' ';
}

void suggestions() {
	std::cout << "THE OBSCURON's PERSONAL HEX LIBRARY IN CPP FOR SPEED AND EFFICIENCY\n";
	std::cout << "═══════════════════════════════════════════════════════════════════════════════\n";
	std::cout << "│        function      │             intent              │        params       │\n";
	std::cout << "───────────────────────────────────────────────────────────────────────────────\n";
	std::cout << "│ split                │ chunk string into hex pairs     │ (str, &out)         │\n";
	std::cout << "│ parser               │ strip spaces from hex string    │ (str, &out)         │\n";
	std::cout << "│ reverser             │ reverse a string                │ (str, &out)         │\n";
	std::cout << "│ deconvert_pair       │ hex pair to byte value          │ (str) → int         │\n";
	std::cout << "│ base16_convert       │ number to hex string            │ (long long, &out)   │\n";
	std::cout << "│ base16_deconvert     │ hex string to number            │ (str, &out)         │\n";
	std::cout << "│ raw_bytes_print      │ print raw byte values           │ (str)               │\n";
	std::cout << "│ load_ciphertext      │ load+normalize hex input        │ (&out)              │\n";
	std::cout << "│ print_ciphertext     │ display hex in spaced pairs     │ (str)               │\n";
	std::cout << "│ hex_xor              │ XOR hex string against key      │ (str, key, &out)    │\n";
	std::cout << "│ large_hex_encrypt    │ encrypt string to hex           │ (str, &out)         │\n";
	std::cout << "│ large_hex_decrypt    │ decrypt hex to string           │ (str, &out)         │\n";
	std::cout << "│ hex_operators        │ command dispatcher              │ (char)              │\n";
	std::cout << "│ suggestions          │ print this help table           │ none                │\n";
	std::cout << "═══════════════════════════════════════════════════════════════════════════════\n";
}

void large_hex_encrypt(const std::string &a, std::string &out) {
	std::string temp=a;
	for (char ch : temp) {
		std::string part;
		base16_convert((long long)(unsigned char)ch, part);
		out += part + ' ';
	}
}

void large_hex_decrypt(const std::string &a, std::string &out) {
	std::string clean;
	parser(a, clean);
	int n=clean.length();
	for (int i = 0; i < n; i += 2) {
		std::string pair = { clean.at(i), clean.at(i+1) };
		out += (char)deconvert_pair(pair);
	}
}

void hex_xor(const std::string &a, unsigned char key, std::string &out) {
	std::string clean;
	if (a.find(' ') != std::string::npos) {
		parser(a, clean);
	} else {
		std::string paired;
		split(a, paired);
		parser(paired, clean);
	}
	int m=clean.length();
	for (int i = 0; i < m; i += 2) {
		std::string pair = { clean.at(i), clean.at(i+1) };
		unsigned char byte = (unsigned char)deconvert_pair(pair);
		byte ^= key;
		std::string part;
		base16_convert((long long)byte, part);
		if (part.length() == 1) part = "0" + part;
		out += part + ' ';
	}
}

void hex_xor_bruteforce(const std::string &a) {
	const std::string common = "etaoinshrdlu ";

	int best_key = 0;
	int best_score = -1;
	std::string best_result;

	for (int key = 0; key < 256; key++) {
		std::string candidate;
		hex_xor(a, (unsigned char)key, candidate);

		// decrypt candidate back to string
		std::string decoded;
		large_hex_decrypt(candidate, decoded);

		// score by common english characters
		int score = 0;
		for (char c : decoded)
			if (common.find((char)tolower(c)) != std::string::npos)
				score++;

		// print all candidates so user can inspect
		std::cout << "key=0x" << std::hex << std::setw(2) << std::setfill('0') << key
		          << std::dec << " score=" << std::setw(3) << score
		          << " | " << decoded << '\n';

		if (score > best_score) {
			best_score = score;
			best_key   = key;
			best_result = decoded;
		}
	}

	std::cout << "\n══════════════════════════════════\n";
	std::cout << "  BEST CANDIDATE\n";
	std::cout << "══════════════════════════════════\n";
	std::cout << "  key:    0x" << std::hex << std::setw(2)
	          << std::setfill('0') << best_key << std::dec << " (" << best_key << ")\n";
	std::cout << "  score:  " << best_score << "\n";
	std::cout << "  result: " << best_result << "\n";
	std::cout << "  bytes:  ";
	raw_bytes_print(best_result);
	std::cout << "\n══════════════════════════════════\n";
}

void hex_operators(char a) {
	switch(a) {
	case 'e': {
		long long num = safeInput<long long>("Enter number: ");
		std::string result;
		base16_convert(num, result);
		std::cout << "hex: " << result << '\n';
		break;
	}
	case 'd': {
		std::string hex = safeInput<std::string>("Enter hex: ");
		long long result;
		base16_deconvert(hex, result);
		std::cout << "decimal: " << result << '\n';
		break;
	}
	case 'x': {
		std::string hex = safeInput<std::string>("Enter hex string: ");
		int key = safeInput<int>("Enter key (0-255): ");
		std::string result;
		hex_xor(hex, (unsigned char)key, result);
		std::cout << "xored: " << result << '\n';
		break;
	}
	case 'b': {
		std::string input = safeInput<std::string>("Enter string to encrypt: ");
		std::string result;
		large_hex_encrypt(input, result);
		std::cout << "encrypted: " << result << '\n';
		break;
	}
	case 'r': {
		std::string input = safeInput<std::string>("Enter hex to decrypt: ");
		std::string result;
		large_hex_decrypt(input, result);
		std::cout << "decrypted: " << result << '\n';
		break;
	}
	case 'w': {
		// raw bytes print
		std::string input = safeInput<std::string>("Enter string for raw bytes: ");
		std::cout << "bytes: ";
		raw_bytes_print(input);
		std::cout << '\n';
		break;
	}
	case 'p': {
		// print ciphertext in spaced pairs
		std::string input = safeInput<std::string>("Enter hex to display: ");
		std::string paired;
		split(input, paired);
		std::cout << "paired: " << paired << '\n';
		break;
	}
	case 'l': {
		// load and normalize ciphertext
		std::string raw = safeInput<std::string>("Enter ciphertext (spaced or not): ");
		std::string paired, clean;
		split(raw, paired);
		parser(paired, clean);
		std::cout << "normalized: " << clean << '\n';
		std::cout << "paired:     " << paired << '\n';
		break;
	}
	case 'f': {
		// // brute force XOR
		std::string hex = safeInput<std::string>("Enter hex ciphertext: ");
		hex_xor_bruteforce(hex);
		break;
	}
	case 'q': {
		std::cout << "exiting hex mode\n";
		break;
	}
	default: {
		suggestions();
		break;
	}
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		help();
		return 1;
	}
	std::string mode=argv[1];
	if(mode=="interactive") {
		interactivecli();
	}
	else if(mode=="master") {
		mastercli();
	}
	else if (mode=="help") {
		help();
	}
	else if (mode=="mass") {
		int cnr[1001];
		masscli(cnr);
	}
	else if (mode=="financial") {
		financialcli();
	}
	else if (mode=="converter") {
		massconverter();
	}
	else if (mode=="geometry") {
		geometrycli();
	}
	else if (mode=="statistics") {
		statisticscli();
	}
	else if (mode=="hex") {
		suggestions();
		char cmd;
		do {
			cmd = safeInput<char>("HEX (e/d/x/b/r/w/p/l/f/q): ");
			hex_operators(cmd);
		} while (cmd != 'q');
	}
	else {
		if(argc < 5 ) {
			std::cout << "Use --help for more" << "\n";
			help();
			return 1;
		}
		int a=std::stoi(argv[2]);
		int b=std::stoi(argv[3]);
		std::string operation=argv[4];
		if (mode=="static") {
			OperationIdentifier(a, b, operation);
		}
	}
	return 0;
}

//as a last notice i finally see why monoliths arent supposed to be made most of the time
//next project will be a cluster of microservices, i didnt decide what to do yet
