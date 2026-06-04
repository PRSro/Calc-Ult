#include "cli.h"
#include "operations.h"
#include "statistics.h"
#include "geometry.h"
#include "bigint.h"
#include "finance.h"
#include "hex.h"
#include "safeinput.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		help();
		return 1;
	}
	std::string mode = argv[1];
	if (mode == "interactive") {
		interactivecli();
	} else if (mode == "master") {
		mastercli();
	} else if (mode == "help") {
		help();
	} else if (mode == "mass") {
		int cnr[1001];
		masscli(cnr);
	} else if (mode == "financial") {
		financialcli();
	} else if (mode == "converter") {
		massconverter();
	} else if (mode == "geometry") {
		geometrycli();
	} else if (mode == "statistics") {
		statisticscli();
	} else if (mode == "hex") {
		suggestions();
		char cmd;
		do {
			cmd = safeInput<char>("HEX (e/d/x/b/r/w/p/l/f/q): ");
			hex_operators(cmd);
		} while (cmd != 'q');
	} else {
		if (argc < 5) {
			std::cout << "Use --help for more\n";
			help();
			return 1;
		}
		int a, b;
		try {
			a = std::stoi(argv[2]);
			b = std::stoi(argv[3]);
		} catch (...) {
			std::cout << "Error: <a> and <b> must be integers.\n";
			return 1;
		}
		std::string operation = argv[4];
		if (mode == "static") {
			OperationIdentifier(a, b, operation);
		}
	}
	return 0;
}
