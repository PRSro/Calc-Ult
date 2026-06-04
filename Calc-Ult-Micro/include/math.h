#ifndef MATH_H
#define MATH_H

extern const double e;
extern const double pi;
extern const double ln2;

int iabs(int a);
double dabs(double a);
int mgcd(int a, int b);
double mpow(double a, int b);
int npow(int a, int b);
void toFraction(double exp, int &p, int &q);
double msqrt(double a);
double nthroot(double a, int n);
double mln(double a);
double mlog(double a, double base);
double meexp(double x);
double mfpow(double a, double b);
int numfinder(int a, int b);
void percents(double a, double b, int s);
int ogl(int a);
int ivectorcomparison(int ll, int *anr, int *bnr);
int vectorcomparison(int la, int lb, int *anr, int *bnr);
long long factorial(int n);
double sine(double a);
double cosine(double a);
double tangent(double a);
double cotangent(double a);
double secant(double a);
double cosecant(double a);
double circlearea(double a);
double spherevolume(double a);
double spheresurface(double a);

#endif
