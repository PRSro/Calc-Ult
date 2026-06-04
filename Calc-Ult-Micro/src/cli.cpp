#include "cli.h"
#include "operations.h"
#include "safeinput.hpp"
#include <iostream>
#include <iomanip>
#include <string>

void interactivecli() {
	int a, b;
	std::string operation;
	while (true) {
		operation = safeInput<std::string>("CALC: ");
		if (operation == "exit") return;
		a = safeInput<int>("Enter A: ");
		b = safeInput<int>("Enter B: ");
		OperationIdentifier(a, b, operation);
	}
}

void mastercli() {
	double a, b;
	std::string operation;
	while (true) {
		operation = safeInput<std::string>("CALC: ");
		if (operation == "exit") return;
		a = safeInput<double>("Enter A: ");
		b = safeInput<double>("Enter B: ");
		OperationRealidentifier(a, b, operation);
	}
}

void massconverter() {
	std::cout << "The mass converter is supposed to convert certain units\n";
	safeInput<std::string>("Choose measure to convert: Volume, Mass, Distance, Surface, Speed, Digital Info Storage [dig], Density, Inch-to-Cm, Feet-to-m: ");
}

void help() {
	std::cout << "============================================================\n";
	std::cout << "          CALC-ULT | Ultimate Calculator | Help Guide        \n";
	std::cout << "============================================================\n\n";
	std::cout << "-- COMPILATION & EXECUTION --\n";
	std::cout << "  Compile  : g++ main.cpp math.cpp utils.cpp operations.cpp statistics.cpp geometry.cpp bigint.cpp finance.cpp hex.cpp cli.cpp -o calc\n";
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
	std::cout << "  +         Addition\n  -         Subtraction\n  *         Multiplication\n";
	std::cout << "  /         Division\n  ^         Power: a^b\n  gcd       Greatest common divisor\n";
	std::cout << "  sqrt      Square root of both a and b\n  find      Count occurrences of digit b in number a\n";
	std::cout << "  ogl       Reverse digits of both a and b\n  mul2      a * 2^b  (left bit-shift)\n";
	std::cout << "  div2      b / 2^a  (right bit-shift)\n  sepmul2   2^a\n  sepdiv2   1 >> a\n\n";
	std::cout << "-- INTERACTIVE MODE --\n  Syntax: CALC: <operation> <a> <b>\n  exit    : Quit\n\n";
	std::cout << "-- MASTER MODE (real numbers) --\n  Supports: +  -  *  /  sqrt  %\n  exit    : Quit\n\n";
	std::cout << "-- MASS MODE (big integers up to 1000 digits) --\n  Supports: +  -\n  exit    : Quit\n\n";
	std::cout << "-- FINANCIAL MODE --\n  %           Percentage\n  simpledebt  Simple interest\n  complexdebt Compound interest\n\n";
	std::cout << "-- GEOMETRY MODE --\n  [1] 2D Cartesian — shapes, point sets\n  [2] 3D Cartesian\n  [3] Trigonometric values\n  [4] Calculus\n\n";
	std::cout << "-- CONVERTER MODE --\n  Units: Volume, Mass, Distance, Surface, Speed, Digital Info Storage [dig], Density, Inch-to-Cm, Feet-to-m\n\n";
	std::cout << "-- CONSTANTS --\n  e  = 2.71828182845904523536\n  pi = 3.14159265358979323846\n ln2 = 0.6931471805599453\n\n";
	std::cout << "============================================================\n";
	std::cout << "  NOTE: geometry 3D, trig, calculus, and converter are stubs.\n";
	std::cout << "  Mass mode supports + and - only as of current version.\n";
	std::cout << "============================================================\n";
}
