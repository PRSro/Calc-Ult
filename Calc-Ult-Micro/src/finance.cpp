#include "finance.h"
#include "operations.h"
#include "safeinput.hpp"
#include <iostream>

void financialcli() {
	std::cout << "The Ultra Pro Corporatist Calculator made with good intentions\n";
	std::cout << "Educational purposes: you will be prompted with questions for a more accurate calculation\n";
	std::string operation = safeInput<std::string>("FINANCE CALC: ");
	FinaOperationIdentifier(operation);
}
