#include "geometry.h"
#include "math.h"
#include "safeinput.hpp"
#include <iostream>
#include <iomanip>
#include <string>

static cart2 cartlist[10001];

static void calcmidpoint(double x1, double y1, double x2, double y2, double &xmid, double &ymid) {
	xmid = (x1 + x2) / 2;
	ymid = (y1 + y2) / 2;
}

static void calcdim2() {
	std::string shape = safeInput<std::string>("Enter shape to work with [triangle/square/hexagon/circle/cartezian]: ");
	if (shape == "triangle") {
		std::string type = safeInput<std::string>("Select type [echilateral/isoceles/any]: ");
		double l1, l2, l3, a1, a2, a3;
		if (type == "echilateral") {
			l1 = safeInput<double>("Enter side length: ");
			std::cout << "All angles are OBVIOUSLY 60 degrees\n";
			std::cout << "All heights are " << l1 * msqrt(3) / 2 << "\n";
			std::cout << "Area: " << (msqrt(3) / 4) * l1 * l1 << "\n";
			std::cout << "Perimeter: " << l1 * 3 << "\n";
		} else if (type == "isoceles") {
			l1 = safeInput<double>("Enter the repeated side length: ");
			l2 = safeInput<double>("Enter the base length: ");
			double h = msqrt(l1 * l1 - (l2 / 2) * (l2 / 2));
			std::cout << "Height: " << h << "\n";
			std::cout << "Area: " << (l2 * h) / 2 << "\n";
			std::cout << "Perimeter: " << l1 * 2 + l2 << "\n";
		} else if (type == "any") {
			std::string sol = safeInput<std::string>("Select what to give [2l1a/1l2a/3l]: ");
			std::cout << "First will check if triangle you yapping is valid\n";
			if (sol == "3l") {
				l1 = safeInput<double>("Enter side 1: ");
				l2 = safeInput<double>("Enter side 2: ");
				l3 = safeInput<double>("Enter side 3: ");
				if (l1 + l2 <= l3 || l1 + l3 <= l2 || l2 + l3 <= l1) {
					std::cout << "Invalid triangle — sides violate triangle inequality\n";
					return;
				}
				double s = (l1 + l2 + l3) / 2;
				double area = msqrt(s * (s - l1) * (s - l2) * (s - l3));
				std::cout << "Valid triangle\n";
				std::cout << "Perimeter: " << l1 + l2 + l3 << "\n";
				std::cout << "Area (Heron): " << area << "\n";
			} else if (sol == "2l1a") {
				l1 = safeInput<double>("Enter side 1: ");
				l2 = safeInput<double>("Enter side 2: ");
				std::string chois = safeInput<std::string>("Is the angle [between] the sides or [next] to side 1: ");
				if (chois == "between") {
					a1 = safeInput<double>("Enter angle between them (degrees): ");
					double a1r = a1 * pi / 180.0;
					double l3 = msqrt(l1 * l1 + l2 * l2 - 2 * l1 * l2 * cosine(a1r));
					double s = (l1 + l2 + l3) / 2;
					std::cout << "Side 3   : " << l3 << "\n";
					std::cout << "Area     : " << 0.5 * l1 * l2 * sine(a1r) << "\n";
					std::cout << "Perimeter: " << l1 + l2 + l3 << "\n";
					double sinA = sine(a1r) / l3;
					double x = l1 * sinA;
					for (int i = 0; i < 100; i++) {
						double fx = sine(x) - l1 * sinA;
						double dfx = cosine(x);
						if (dabs(dfx) < 1e-12) break;
						x -= fx / dfx;
					}
					double a2 = x * 180.0 / pi;
					double a3 = 180.0 - a1 - a2;
					std::cout << "Angle A1 : " << a1 << " degrees (given)\n";
					std::cout << "Angle A2 : " << a2 << " degrees\n";
					std::cout << "Angle A3 : " << a3 << " degrees\n";
				} else {
					a1 = safeInput<double>("Enter known angle (degrees): ");
					double sina2 = (l2 * sine(a1)) / l1;
					if (dabs(sina2) > 1.0) { std::cout << "No valid triangle — sine out of range\n"; return; }
					double x = sina2;
					for (int i = 0; i < 100; i++) {
						double fx = sine(x) - sina2;
						double dfx = cosine(x);
						if (dabs(dfx) < 1e-12) break;
						x -= fx / dfx;
					}
					double a2_acute = x * 180.0 / pi;
					double a2_obtuse = 180.0 - a2_acute;
					double a3_acute  = 180.0 - a1 - a2_acute;
					double a3_obtuse = 180.0 - a1 - a2_obtuse;
					std::cout << "CASE 1 (acute A2): A2=" << a2_acute  << " A3=" << a3_acute  << " degrees\n";
					if (a3_acute > 0) {
						double l3_acute = (l1 * sine(a3_acute * pi / 180.0)) / sine(a1 * pi / 180.0);
						std::cout << "  Side 3: " << l3_acute << "\n";
						double s = (l1 + l2 + l3_acute) / 2;
						std::cout << "  Area  : " << msqrt(s * (s - l1) * (s - l2) * (s - l3_acute)) << "\n";
					}
					if (a3_obtuse > 0 && dabs(a2_acute - a2_obtuse) > 0.0001) {
						double l3_obtuse = (l1 * sine(a3_obtuse * pi / 180.0)) / sine(a1 * pi / 180.0);
						std::cout << "CASE 2 (obtuse A2): A2=" << a2_obtuse << " A3=" << a3_obtuse << " degrees\n";
						std::cout << "  Side 3: " << l3_obtuse << "\n";
						double s = (l1 + l2 + l3_obtuse) / 2;
						std::cout << "  Area  : " << msqrt(s * (s - l1) * (s - l2) * (s - l3_obtuse)) << "\n";
					}
				}
			} else if (sol == "1l2a") {
				l1 = safeInput<double>("Enter the known side: ");
				a1 = safeInput<double>("Enter angle opposite to it (degrees): ");
				a2 = safeInput<double>("Enter a second angle (degrees): ");
				a3 = 180 - a1 - a2;
				if (a3 <= 0) { std::cout << "Invalid — angles dont sum to 180\n"; return; }
				std::cout << "Third angle: " << a3 << " degrees\n";
				double ratio = l1 / sine(a1 * pi / 180.0);
				double l2_calc = ratio * sine(a2 * pi / 180.0);
				double l3_calc = ratio * sine(a3 * pi / 180.0);
				std::cout << "Side 2: " << l2_calc << "\nSide 3: " << l3_calc << "\n";
				double s = (l1 + l2_calc + l3_calc) / 2;
				std::cout << "Area  : " << msqrt(s * (s - l1) * (s - l2_calc) * (s - l3_calc)) << "\n";
				std::cout << "Perimeter: " << l1 + l2_calc + l3_calc << "\n";
			}
		}
	} else if (shape == "square") {
		double l = safeInput<double>("Enter length of one side: ");
		std::cout << "DIAGONAL: "     << l * msqrt(2) << "\n";
		std::cout << "AREA: "         << l * l << "\n";
		std::cout << "PERIMETER: "    << l * 4 << "\n";
		std::cout << "HALF DISTANCE: "<< msqrt(l * l + l * l / 4) << "\n";
	} else if (shape == "hexagon") {
		double l = safeInput<double>("Enter length of one side: ");
		std::cout << "DIAGONAL COUNT: " << 9 << "\n";
		std::cout << "LONG DIAGONAL: "  << l * 2 << "\n";
		std::cout << "SHORT DIAGONAL: " << l * msqrt(3) << "\n";
		std::cout << "AREA: "           << (3 * msqrt(3) / 2) * l * l << "\n";
		std::cout << "PERIMETER: "      << l * 6 << "\n";
	} else if (shape == "circle") {
		double radius = safeInput<double>("Enter radius length: ");
		std::cout << "AREA: "          << circlearea(radius) << "\n";
		std::cout << "CIRCUMFERENCE: " << 2 * pi * radius << "\n";
		std::cout << "DIAMETER: "      << 2 * radius << "\n";
	} else if (shape == "cartezian") {
		int a = safeInput<int>("Enter number of points (max 10000): ");
		if (a <= 0 || a > 10000) { std::cout << "Invalid\n"; return; }
		for (int i = 1; i <= a; i++) {
			std::cout << "Point " << i << " of " << a << " — ";
			cartlist[i].x = safeInput<double>("x." + std::to_string(i) + ": ");
			cartlist[i].y = safeInput<double>("y" + std::to_string(i) + ": ");
		}
		std::cout << "\n[1] Multidistance\n[2] Distance between two\n[3] Midpoints\n";
		int task = safeInput<int>("Choose task: ");
		if (task == 1) {
			for (int i = 1; i <= a; i++)
				for (int j = i + 1; j <= a; j++) {
					double dx = cartlist[j].x - cartlist[i].x;
					double dy = cartlist[j].y - cartlist[i].y;
					std::cout << "d(P" << i << ",P" << j << ") = " << msqrt(dx * dx + dy * dy) << "\n";
				}
		} else if (task == 2) {
			int i = safeInput<int>("Index of point 1: ");
			int j = safeInput<int>("Index of point 2: ");
			if (i < 1 || i > a || j < 1 || j > a) return;
			double dx = cartlist[j].x - cartlist[i].x;
			double dy = cartlist[j].y - cartlist[i].y;
			std::cout << "Distance: " << msqrt(dx * dx + dy * dy) << "\n";
		} else if (task == 3) {
			int mode = safeInput<int>("Consecutive [2] or chosen pair [1]: ");
			if (mode == 2) {
				for (int i = 1; i < a; i++) {
					double xmid, ymid;
					calcmidpoint(cartlist[i].x, cartlist[i].y, cartlist[i+1].x, cartlist[i+1].y, xmid, ymid);
					std::cout << "Mid(P" << i << ",P" << i+1 << ") = " << xmid << " " << ymid << "\n";
				}
			} else {
				int i = safeInput<int>("Index of point 1: ");
				int k = safeInput<int>("Index of point 2: ");
				double xmid, ymid;
				calcmidpoint(cartlist[i].x, cartlist[i].y, cartlist[k].x, cartlist[k].y, xmid, ymid);
				std::cout << "Midpoint: " << xmid << " " << ymid << "\n";
			}
		}
	} else {
		std::cout << "Unknown shape\n";
	}
}

static double evalPoly(double *coefs, int degree, double x) {
	double result = 0;
	for (int i = 0; i <= degree; i++)
		result += coefs[i] * mpow(x, degree - i);
	return result;
}

static double derivPoly(double *coefs, int degree, double x) {
	double h = 0.0001;
	return (evalPoly(coefs, degree, x + h) - evalPoly(coefs, degree, x - h)) / (2.0 * h);
}

static double integralPoly(double *coefs, int degree, double a, double b, int n) {
	if (n % 2 != 0) n++;
	double h = (b - a) / n;
	double result = evalPoly(coefs, degree, a) + evalPoly(coefs, degree, b);
	for (int i = 1; i < n; i++) {
		double x = a + i * h;
		result += (i % 2 == 0 ? 2.0 : 4.0) * evalPoly(coefs, degree, x);
	}
	return result * h / 3.0;
}

static double newtonRoot(double *coefs, int degree, double guess) {
	double x = guess;
	for (int i = 0; i < 1000; i++) {
		double fx  = evalPoly(coefs, degree, x);
		double dfx = derivPoly(coefs, degree, x);
		if (dabs(dfx) < 1e-12) break;
		double xnew = x - fx / dfx;
		if (dabs(xnew - x) < 1e-10) { x = xnew; break; }
		x = xnew;
	}
	return x;
}

static int parseCoefs(double *coefs) {
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
		if (f.at(i) == '-') { sign = -1.0; i++; }
		else if (f.at(i) == '+') { i++; }
		std::string numstr = "";
		while (i < len && ((f.at(i) - '0' >= 0 && f.at(i) - '0' <= 9) || f.at(i) == '.')) {
			numstr += f.at(i); i++;
		}
		if (!numstr.empty()) {
			double val = 0, d = 1;
			bool afterdot = false;
			for (char c : numstr) {
				if (c == '.') { afterdot = true; continue; }
				if (!afterdot) val = val * 10 + (c - '0');
				else { d *= 10; val += (c - '0') / d; }
			}
			coefs[++degree] = sign * val;
		}
	}
	return degree;
}

static void printPoly(double *coefs, int degree) {
	std::cout << "f(x) = ";
	bool first = true;
	for (int i = 0; i <= degree; i++) {
		int power = degree - i;
		if (coefs[i] == 0) continue;
		if (!first && coefs[i] > 0) std::cout << "+";
		std::cout << coefs[i];
		if (power > 1) std::cout << "x^" << power;
		else if (power == 1) std::cout << "x";
		first = false;
	}
	std::cout << "\n";
}

static void calculuscli() {
	std::cout << "CALCULUS CALCULATOR\n";
	std::cout << "[1] Evaluate f(x)\n[2] Derivative f'(x)\n[3] Definite integral\n";
	std::cout << "[4] Root finder (Newton)\n[5] Tangent line\n[6] All-in-one\n";
	int choice = safeInput<int>("Choice: ");
	double coefs[20] = {0};
	int degree = parseCoefs(coefs);
	if (degree < 0) { std::cout << "No valid coefficients\n"; return; }
	printPoly(coefs, degree);
	if (choice == 1) {
		double x = safeInput<double>("Enter x: ");
		std::cout << "f(" << x << ") = " << evalPoly(coefs, degree, x) << "\n";
	} else if (choice == 2) {
		double x = safeInput<double>("Enter x: ");
		std::cout << "f'(" << x << ") = " << derivPoly(coefs, degree, x) << "\n";
	} else if (choice == 3) {
		double a = safeInput<double>("Lower bound: ");
		double b = safeInput<double>("Upper bound: ");
		int n = safeInput<int>("Intervals: ");
		std::cout << "Integral = " << integralPoly(coefs, degree, a, b, n) << "\n";
	} else if (choice == 4) {
		double guess = safeInput<double>("Initial guess: ");
		double root = newtonRoot(coefs, degree, guess);
		std::cout << "Root = " << root << "\n";
	} else if (choice == 5) {
		double x = safeInput<double>("Enter x: ");
		double fx = evalPoly(coefs, degree, x);
		double dfx = derivPoly(coefs, degree, x);
		std::cout << "y = " << dfx << "(x - " << x << ") + " << fx << "\n";
	} else if (choice == 6) {
		double x = safeInput<double>("x for eval/deriv: ");
		double a = safeInput<double>("Lower bound integral: ");
		double b = safeInput<double>("Upper bound integral: ");
		int n = safeInput<int>("Intervals: ");
		std::cout << "f(" << x << ") = " << evalPoly(coefs, degree, x) << "\n";
		std::cout << "f'(" << x << ") = " << derivPoly(coefs, degree, x) << "\n";
		std::cout << "Integral = " << integralPoly(coefs, degree, a, b, n) << "\n";
	}
}

static double masin(double x) {
	if (x < -1 || x > 1) return -1;
	double t = x;
	for (int i = 0; i < 100; i++) {
		double ft = sine(t) - x;
		double dft = cosine(t);
		if (dabs(dft) < 1e-12) break;
		t -= ft / dft;
	}
	return t;
}

static double macos(double x) {
	if (x < -1 || x > 1) return -1;
	return (pi / 2.0) - masin(x);
}

static double matan(double x) {
	return masin(x / msqrt(1 + x * x));
}

static void trigarith() {
	std::cout << "TRIGONOMETRY\n[1] sin/cos/tan/cot/sec/csc\n[2] Inverse: asin/acos/atan\n[3] Degree <-> Radian\n";
	int choice = safeInput<int>("Choice: ");
	if (choice == 1) {
		std::string unit = safeInput<std::string>("Input in [deg] or [rad]: ");
		double val = safeInput<double>("Value: ");
		double r = (unit == "deg") ? val * pi / 180.0 : val;
		std::cout << "sin: " << sine(r) << "\ncos: " << cosine(r) << "\n";
		std::cout << "tan: " << tangent(r) << "\ncot: " << cotangent(r) << "\n";
		std::cout << "sec: " << secant(r) << "\ncsc: " << cosecant(r) << "\n";
	} else if (choice == 2) {
		std::string fn = safeInput<std::string>("Function [asin/acos/atan]: ");
		double val = safeInput<double>("Value: ");
		std::string unit = safeInput<std::string>("Output in [deg] or [rad]: ");
		double result = -1;
		if (fn == "asin") result = masin(val);
		else if (fn == "acos") result = macos(val);
		else if (fn == "atan") result = matan(val);
		if (unit == "deg") result *= 180.0 / pi;
		std::cout << fn << "(" << val << ") = " << result << "\n";
	} else if (choice == 3) {
		std::string dir = safeInput<std::string>("[dtr] or [rtd]: ");
		double val = safeInput<double>("Value: ");
		if (dir == "dtr") std::cout << val << " deg = " << val * pi / 180.0 << " rad\n";
		else if (dir == "rtd") std::cout << val << " rad = " << val * 180.0 / pi << " deg\n";
	}
}

static void calcdim3() {
	std::string shape = safeInput<std::string>("Enter shape [cube/sphere/cylinder/cone/cartezian3d]: ");
	if (shape == "cube") {
		double l = safeInput<double>("Side: ");
		std::cout << "VOLUME: " << l * l * l << "\nSURFACE: " << 6 * l * l << "\n";
		std::cout << "FACE DIAG: " << l * msqrt(2) << "\nSPACE DIAG: " << l * msqrt(3) << "\n";
	} else if (shape == "sphere") {
		double r = safeInput<double>("Radius: ");
		std::cout << "VOLUME: " << spherevolume(r) << "\nSURFACE: " << spheresurface(r) << "\n";
	} else if (shape == "cylinder") {
		double r = safeInput<double>("Radius: ");
		double h = safeInput<double>("Height: ");
		std::cout << "VOLUME: " << pi * r * r * h << "\n";
		std::cout << "LATERAL SA: " << 2 * pi * r * h << "\n";
		std::cout << "TOTAL SA: " << 2 * pi * r * (r + h) << "\n";
	} else if (shape == "cone") {
		double r = safeInput<double>("Radius: ");
		double h = safeInput<double>("Height: ");
		double sl = msqrt(r * r + h * h);
		std::cout << "SLANT: " << sl << "\nVOLUME: " << (pi * r * r * h) / 3 << "\n";
		std::cout << "LATERAL SA: " << pi * r * sl << "\nTOTAL SA: " << pi * r * (r + sl) << "\n";
	} else if (shape == "cartezian3d") {
		int n = safeInput<int>("Number of points: ");
		if (n <= 0 || n > 10000) return;
		double px[10001], py[10001], pz[10001];
		for (int i = 1; i <= n; i++) {
			px[i] = safeInput<double>("x: ");
			py[i] = safeInput<double>("y: ");
			pz[i] = safeInput<double>("z: ");
		}
		int task = safeInput<int>("[1] All distances [2] Two-point distance [3] Midpoint: ");
		if (task == 1) {
			for (int i = 1; i <= n; i++)
				for (int j = i + 1; j <= n; j++)
					std::cout << "d(P" << i << ",P" << j << ") = "
					          << msqrt((px[j]-px[i])*(px[j]-px[i]) + (py[j]-py[i])*(py[j]-py[i]) + (pz[j]-pz[i])*(pz[j]-pz[i])) << "\n";
		} else if (task == 2) {
			int i, j;
			i = safeInput<int>("Point 1: ");
			j = safeInput<int>("Point 2: ");
			std::cout << "Distance: " << msqrt((px[j]-px[i])*(px[j]-px[i]) + (py[j]-py[i])*(py[j]-py[i]) + (pz[j]-pz[i])*(pz[j]-pz[i])) << "\n";
		} else if (task == 3) {
			int i, j;
			i = safeInput<int>("Point 1: ");
			j = safeInput<int>("Point 2: ");
			std::cout << "Midpoint: (" << (px[i]+px[j])/2 << ", " << (py[i]+py[j])/2 << ", " << (pz[i]+pz[j])/2 << ")\n";
		}
	}
}

void geometrycli() {
	std::cout << "GEOMETRY CALCULATOR\n";
	std::cout << "[1] 2D geometry\n[2] 3D geometry\n[3] Trigonometry\n[4] Calculus\n";
	int choice = safeInput<int>("Choice: ");
	if (choice == 1) calcdim2();
	else if (choice == 2) calcdim3();
	else if (choice == 3) trigarith();
	else calculuscli();
}
