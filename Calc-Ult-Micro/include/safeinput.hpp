#ifndef SAFEINPUT_HPP
#define SAFEINPUT_HPP

#include <iostream>
#include <string>
#include <limits>

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

#endif
