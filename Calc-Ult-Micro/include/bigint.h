#ifndef BIGINT_H
#define BIGINT_H

#include <string>

void stringToArray(const std::string &a, const std::string &b, int *anr, int *bnr);
void ArithmeticIdentifier(int *anr, int *bnr, int *cnr, int la, int lb, const std::string &operation, int &ma);
void ArrayTostring(std::string &c, int *cnr, int ma);
void masscli(int *cnr);

#endif
