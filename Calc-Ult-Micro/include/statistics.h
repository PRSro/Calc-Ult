#ifndef STATISTICS_H
#define STATISTICS_H

#include <string>

struct StatData {
	int numInt, numReal, numStr;
	int rowInt, rowReal, rowStr;
	int total;
	int **integers;
	double **reals;
	std::string **strings;
};

void statisticscli();

#endif
