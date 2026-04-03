// Concept project for a sample TUI application working solely on cpp. For future projects
// A basic project good for any started. Even ai can make it so i added some interesting functions to extent the terminal
#include <iostream>
#include <string>
#include <iomanip>
//dodging by reference in first functions for safe input
//declaration of algebraic functions and needed constants
// Might stop at version 1.5 as i see the extend is getting rather too diverse
const double e=2.71828182845904523536;
const double pi=3.14159265358979323846;
//below are operation algorithms -> will think of which to add for extension
int mgcd (int a, int b){
    int c=a, d=b;
    while(d != 0)
    {
        int r=c%d;
        c=d;
        d=r;
    }
    return c;
}

double mpow(double a, int b){
    if (b==1) return a;
    else if (b==0) return 1;
    double c=a;
    if (b>1){
        if(a>0){
            for (int i=1; i<b; i++){
                c*=a;
            }
            return c;
        }
    }
    return 0;
}

int npow(int a, int b){
    if (b==1) return a;
    else if (b==0) return 1;
    int c=a;
    if (b>1){
        for (int i=1; i<b; i++){
            c*=a;
        } 
        return c;
    }
    return 0;
}
double msqrt(double a){
    if (a<0) return -1;
    double c=a, c1=1;
    while (c-c1 > 0.00000001 || c1-c > 0.00000001){
        c1=c;
        c=(c+a/c)/2; // Newton
    }
    return c;
}

int numfinder(int a, int b){
    int c=a, r, cnt=0;
    while (c!=0){
        r=c%10;
        if (r==b) cnt++;
        c/=10;
    }
    return cnt;
}

void percents(double a, double b, int s){
    // let p% of a = b, b<a: => p=100b/a;
    double mi=(a<b)?a:b;
    double ma=(a<b)?b:a;
    double p=(double)mi*100/ma;
    std::cout << mi << " represents " <<std::fixed<<std::setprecision(s)<<p<<"% of "<<ma;
    return;
}

int ogl(int a){
    //remade the function so it acctually returns good value | V1.2.0
    int ogl=0, n=a;
    while (n != 0) {
        ogl = ogl * 10 + n % 10;
        n /= 10;
    }
    return ogl;
}

int ivectorcomparison(int ll, int *anr, int *bnr){
    for (int i=0; i<ll; i--){
        if (anr[i]==bnr[i]) continue;
        else if (anr[i]>bnr[i]){return -1;}
        else {return -2;}
    }
    return 0;
}

int vectorcomparison(int la, int lb, int *anr, int *bnr){
    if (la<lb) return -2;
    else if (la>lb) return -1;
    //return with minus to not confuse with the shortcut calculator
    else {
        int shortcut=0;
        for (int i=0; i<la; i++){
            if (anr[i]==bnr[i]){shortcut++;}
            else break;
        }
        if (shortcut==la) return 0;
        else return ivectorcomparison(shortcut, anr, bnr);
    }
}
// P.S: AI wasnt used to any extend besides maths advice and minor debugging
// dodging case switch for now as ill add in a new version
// Geometry functions below
//althogh redundant might need noting

double circlearea(double a){
    return pi*a*a;
}
double spherevolume(double a){
    return 1.333333333333333333*circlearea(a)*a;
}
double spheresurface(double a){
    return 4*circlearea(a);
}

void simpledebt(double a, double b, double r){
    std::cout << "TOTAL INTEREST: " << a*(r/100)*b << "\n";
    std::cout << "YEARLY PAY: " << a*(r/100) << "\n";
    std::cout << "AVERAGE MONTHLY PAY: " << a*(r/100)/12 << "\n";
    std::cout << "DAILY IMPACT: " <<std::fixed<<std::setprecision(3)<<a*(r/100)/365 << "\n";
}

void complexdebt(double a, double b, double r){
    std::cout << "TOTAL INTEREST: " << a*mpow(1+r/100, b)-a << "\n";
    for (int i=1; i<=b; i++){
        std::cout << "YEAR " << i << " INTEREST IS " << a * mpow(1+r/100, i)-a * mpow(1+r/100, i-1) << "\n";
    }
}
// as of V1.2.0 all work
void OperationIdentifier(int a, int b, std::string operation){
    if (operation=="+"){
        std::cout << a+b << "\n";
    }
    if (operation=="-"){
        std::cout << a-b << "\n";
    }
    if (operation=="*"){
        std::cout << a*b << "\n";
    }
    if (operation=="/"){
        std::cout << a/b << "\n";
    }
    if (operation=="gcd"){
        std::cout << mgcd(a, b) << "\n";
    }
    if (operation=="^"){
        std::cout << npow(a, b) << "\n";
    }
    if (operation=="mul2"){
        std::cout << (double)(a<<b) << "\n"; // a * 2^b
    }
    if (operation=="div2"){
        std::cout << (double)(b>>a) << "\n"; // b / 2^a
    }
    if (operation=="sepmul2"){
        std::cout << (double)(1<<a) << "\n"; //
    }
    if (operation=="sepdiv2"){
        std::cout << (double)(1>>a) << "\n";
    }
    if (operation=="find"){
        std::cout << numfinder(a, b) << "\n";
    }
    if (operation=="ogl"){
        std::cout << ogl(a) << " " << ogl(b) << "\n";
    }
    if (operation=="sqrt"){
        std::cout << msqrt(a) << " " << msqrt(b) << "\n";
    }
}

void FinaOperationIdentifier(std::string operation){
    if (operation=="%"){
        std::cout << "ENTER PRECISION: ";
        int p;
        std::cin >> p;
        std::cout << "\n";
        std::cout << "ENTER NUMBERS: (a>b) ";
        double a, b;
        std::cin >> a >> b;
        percents(a, b, p);
    }
    if (operation=="simpledebt"){
        std::cout << "DEBT: SUM is ... " << "\n"; // Ds=S*r/100+b
        double a;
        std::cin >> a;
        std::cout << "\n";
        std::cout << "DEBT: YEARS is ... ";
        double b;
        std::cin >> b;
        std::cout << "\n";
        std::cout << "Enter Rate offered by bank: ";
        double r;
        std::cin >> r;
        simpledebt(a, b, r);
    }
    if (operation=="complexdebt"){
        std::cout << "DEBT: INITIAL SUM is ... " << "\n"; // Ds=S*r/100+b
        double a;
        std::cin >> a;
        std::cout << "\n";
        std::cout << "DEBT: YEARS is ... ";
        double b;
        std::cin >> b;
        std::cout << "\n";
        std::cout << "Enter Rate offered by bank: ";
        double r;
        std::cin >> r;
        complexdebt(a, b, r);
    }
}

void OperationRealidentifier(double a, double b, std::string operation){
     if (operation=="+"){
        std::cout << a+b << "\n";
    }
    if (operation=="-"){
        std::cout << a-b << "\n";
    }
    if (operation=="*"){
        std::cout << a*b << "\n";
    }
    if (operation=="/"){
        std::cout << a/b << "\n";
    }
    if (operation=="sqrt"){
        std::cout << msqrt(a) << " " << msqrt(b) << "\n";
    }
    if (operation=="%"){
        std::cout << "If the numbers are double this will calculate the percentage of both the smaller one over the larger one and vice versa" << "\n";
        std::cout << "Enter precision: " << "\n";
        int p;
        std::cin >> p;
        percents(a, b, p);
        std::cout << "\n";
    }
    //more limited as the functions are needed manuanlly and might move each definition to a separate cpp
}
void interactivecli(){
    //basic continuous interactive cli
    int a, b;
    std::string operation;
    while(true){
        std::cout << "CALC:";
        std::cin >> operation;
        if (operation=="exit") return;
        else {std::cin >> a >> b;  OperationIdentifier(a, b, operation);}
    }
}

void mastercli(){
    //master mode for real numbers
    double a, b;
    std::string operation;
    while (true){
        std::cout << "CALC: ";
        std::cin >> operation;
        if (operation=="exit")return;
        else{std::cin >> a >> b; OperationRealidentifier(a, b, operation);}
    }
}

// Statistics functions
void stage1(int &columns, int &a, int &c, int &b, int &d, int &g){
    std::cout << "The number of colums will be set to ...";
    std::cin >> columns;
    std::cout << "Enter number of integer values" << "\n";
    std::cin >> a;
    std::cout << "Enter length of rows for integer values" << "\n";
    int h;
    std::cin >> h;
    if (a==0){
        std::cout << "Enter number of real values" << "\n"; 
        std::cin >> c;
        std::cout << "Enter length of rows for real values" << "\n";
        int g;
        std::cin >> g;
    }
    else {
        std::string e;
        std::cout << "Add real numbers?[y/N]" << "\n"; 
        std::cin >> e; 
        if(e=="y"||e=="Y"||e=="Yes"||e=="yes"){
            std::cout << "Enter number of real values" << "\n"; 
            std::cin >> c;
            std::cout << "Enter length of rows for real values" << "\n";
            int g;
            std::cin >> g;
        }
     }
     std::cout << "Add char to value correspondence?[y/n]" << "\n";
     std::string f;
     std::cin >> f;
     if (f=="y"){
        std::cout << "Add strings? [Y/n]" << "\n";
        std::string ans;
        std::cin >> ans;
        if(ans=="y"||ans=="Y"||ans=="Yes"||ans=="yes"){
        std::cout << "Enter number of strings" << "\n";
        std::cin >> b;
     }
     d=a+b+c;
     std::cout << "The total number of values is " << d << " " << a << " out of them int, " << b << " out of them std::strings, " << c << " out of them real!" << "\n";
    }
}

void stage2(int columns, int columnschar, int columnsreal, int a, int c, int b, int rowa, int rowb, int rowc, char **charc, int **integer, double **real) {
	if (c!=0) {
		for (int i=1; i<=columnschar; i++) {
			std::cout << "Enter char values, Series" << i << " out of " << c;
			for(int j=1; j<=c; j++) {
				std::cin >> charc[i][j];
			}
		}
	}
	if (b!=0) {
		for (int i=1; i<=columns; i++) {
			std::cout << "Enter integer values, Series" << i << " out of " << b;
			for(int j=1; j<=b; j++) {
				std::cin >> integer[i][j];
			}
		}
	}
	if (a!=0) {
		for (int i=1; i<=columnsreal; i++) {
			std::cout << "Enter real values, Series" << i << " out of " << a;
			for(int j=1; j<=a; j++) {
				std::cin >> real[i][j];
			}
		}
	}
}

// pretty print steps
// 1: border the matrices
// 2: asign values in an intermediary matrice (for example 0 for border and lines/chars, 1 for chara, 2 for integer, 3 for real values)
// 3. print everything according to translation and give an id: make a pointer to the value at that, get the length in chars and add to print

/* void stage3(int a, int c, int b, char **charc, int **integer, int **real){
    if (c!=0) {
        for(int i=1; i<=a; i++){
            for(int j=1; j<=a+b+c; j++){
            
            }
        }
	}
	if (b!=0) {

	}
	if (a!=0) {

	}
} */

void statisticscli(){
    //good to mention: struct vs class:
    //struct is good for public datasets and has everything public by default.
    //classes and struct seem deprecated/not what we need for such sweaty statistics, not because i dont like them but because OOP for this project seems useless
    //instead we will do a declaration of struct after the vector is declared acording to the user
    std::cout << "STATISTIC STAGE" << "\n";
    std::cout << "STAGE 1: Data typing" << "\n";
    std::cout << "EXPLANATION: You give the number of values and type of values. accordingly a table can either be generated or the dataset can be worked with" << "\n";
    std::cout << "STAGE 2: Basic statistics" << "\n";
    std::cout << "EXPLANATION: There will be calculated the mean, the average, the highest/lowest points, the mode, and based on subgroups and given data there will be given results" << "\n";
    std::cout << "EXPLANATION: But first introduce ";
    std::cout << "STAGE 3: Pretty print" << "\n";
    std::cout << "EXPLANATION: Everything will be printed accordingly." << "\n";
    std::cout << "ENTER: number of values" << "\n";
    int a, b, c, d, g, columns;
    stage1(columns, a, c, b, d, g);
      /*  stage2();
    stage3(); */
}
struct cart2 {
    double x;
    double y;
} cartlist[10001];

void calcmidpoint(double x1, double y1, double x2, double y2, double &xmid, double &ymid){
    ymid=(y1+y2)/2;
    xmid=(x1+x2)/2;
}

void calcdim2(cart2 *cartlist){
    std::cout << "Enter shape to work with" << '\n';
    std::string shape;
    std::cin >> shape;
    if (shape=="triangle"){

    }
    else if (shape=="square"){
        double l;
        std::cout << "Enter length of one side" << "\n";
        std::cin >> l;
        std::cout << "DIAGONAL1: " << l*msqrt(2) << "\n";
        std::cout << "AREA: " << l*l << "\n";
        std::cout << "ANGLE BETWEEN EACH SIDE IS 90 degrees" << "\n";
        std::cout << "ANGLE BETWEEN ANY SIDE AND DIAGONAL IS 45 degrees" << "\n";
        double hl=l*l+l*l/4;
        std::cout << "HALF DISTANCE: " << msqrt(hl) << "\n";
        std::cout << "2 HALF DISTANCES FORM AN isoceles triangle" << "\n";
        std::cout << "VOLUME: DOESNT EXIST" << "\n";
        std::cout << "SURFACE AREA: DOESNT EXIST" << "\n";
        std::cout << "The easiest shape of all I forgot why i added this" << "\n";
    }
    else if (shape=="hexagon"){
        double l;
        std::cout << "Enter lenght of one side" << "\n";
        std::cin >> l;
        std::cout << "DIAGONAL NUMBERS: " << 1/2*6*(6-3) << "\n";
        std::cout << "DIAGONAL1: " << l*2 << "\n";
        std::cout << "DIAGONAL2: " << l*msqrt(3) << "\n";
        std::cout << "AREA: " << (3*msqrt(3)/2)*l*l << "\n";
        std::cout << "ANGLE BETWEEN EACH SIDE IS 120 degrees" << "\n";
        std::cout << "ANGLE BETWEEN A SIDE AND DIAGONAL1 IS 60 degrees" << "\n";
        std::cout << "ANGLE BETWEEN A SIDE AND DIAGONAL2 IS 30 degrees" << "\n";
        double hl=l*l*4+l*l/4;
        std::cout << "HALF DISTANCE: " << msqrt(hl) << "\n";
        std::cout << "2 HALF DISTANCES FORM AN isoceles triangle" << "\n";
        std::cout << "VOLUME: DOESNT EXIST" << "\n";
        std::cout << "SURFACE AREA: DOESNT EXIST" << "\n";
        std::cout << "Difficulty:Medium" << "\n";
    }
    else if (shape=="circle"){
        double radius;
        std::cout << "Enter Radius length" << "\n";
        std::cin>>radius;
        std::cout<< "AREA: " << circlearea(radius) << "\n";
        std::cout<< "Barely anything else to calculate so here is a short lesson about them" << "\n";
    }
    else if (shape=="cartezian"){
        std::cout << "Enter number of points to work with" << '\n';
        int a;
        std::cin >> a;
        double k, j;
        std::cout << "WARNING: max points stored go up to 10000, the limit is the one of double" << '\n';
        for(int i=1; i<=a; i++){
            std::cout << "Enter coordinates for point number " << i << " out of " << a << "\n";
            std::cin >> cartlist[i].x >> cartlist[i].y;
        }
        std::cout << "What to do?" << '\n';
        std::cout << "[1] calculate multidistance (distance between all points) and output in pretty format" << '\n';
        std::cout << "[2] calculate certain distance " << '\n';
        std::cout << "[3] calculate middle points between consecutive/input distances" << '\n';
        std::cout << "[4] calculate slope or make/insert function" << '\n'; // insert as in to find out which points correspond to that equation and correspondence x and y
        int task;
        std::cin >> task;
        if(task==1){

        }
        else if(task==3){
            double v[10000][2];
            std::cout << "For input/points at your choice press 1, for consecutive of all press 2" << '\n';
            int b;
            std::cin >> b;
            if (b==2){
                for(int i=0; i<a; i++){
                    calcmidpoint(cartlist[i].x, cartlist[i].y, cartlist[i+1].x, cartlist[i+1].y, v[i][0], v[i][1]);
                    std::cout << v[i][0] << " " << v[i][1] << "\n";
                }
            }
            else {
                std::cout << "Enter indeces of the points to calculate" << "\n";
                int k, i;
                std::cin >> i >> k;
                calcmidpoint(cartlist[i].x, cartlist[i].y, cartlist[k].x, cartlist[k].y, v[k][0], v[k][1]);
                std::cout << v[k][0] << " " << v[k][1] << "\n";
        }
        }
        else if(task==2){

        }
        else {
            std::cout << "f(x)=";
            std::string function;
            std::cin >> function;
        }
    }
}
void geometrycli(){
    std::cout << "GEOMETRY CALCULATOR" << "\n";
    std::cout << "This mode isnt responsible for any simulation of the provided shapes" << "\n";
    std::cout << "CHOOSE MODE: [1] cartezian/euclidean geometry 2D calculation" << "\n";
    std::cout << "             [2] cartezian/euclidean geometry 3D calculation" << "\n";
    std::cout << "             [3] trigonometric values" << "\n";
    std::cout << "             [4] calculus" << "\n";
    int choice;
    std::cin >> choice;
    if(choice==1){
        cart2 cartlist[10000];
        calcdim2(cartlist);
    }
    else if (choice==2){
        // calcdim3
    }
    else if (choice==3){
        // trigarith, to be coded soon
    }   
    else {
         // calculuscli(); //only outputs rules as i didnt learn calculus
    }             
}

void stringToArray(const std::string &a, const std::string &b, int *anr, int *bnr){
    int la=a.length(), lb=b.length();
    int i=-1;
    for (char c:a){
        anr[++i]=c-'0';
    }
    i=-1;
    for (char c:b){
        bnr[++i]=c-'0';
    }
    return;
}

void ArithmeticIdentifier(int *anr, int *bnr, int *cnr, int la, int lb, std::string operation, int &ma){
    ma=(la>=lb)?la:lb;
    if (operation=="+"){
        int remainder=0;
        for(int i=0; i<ma; i++){
            int avr=(la>i)?anr[la-i-1]:0;
            int bvr=(lb>i)?bnr[lb-i-1]:0;
            int s=avr+bvr+remainder;
            cnr[ma-i]=s%10;
            remainder=s/10;
             //saving result at the same digit as one calculated and doing additional steps if remainder exists
        }
        cnr[0]=remainder;
    }
    if (operation=="-"){
        int cmp=vectorcomparison(la, lb, anr, bnr);
        if (cmp==0){ cnr[0]=0;}
        else if (cmp==-1){
            int borrow=0;
            for(int i=0; i<ma; i++){
                int avr=(la>i)?anr[la-i-1]:0;
                int bvr=(lb>i)?bnr[lb-i-1]:0;
                avr-=borrow;
                int s=avr-bvr;
                if (s<0){ borrow=1; s+=10; }
                else borrow=0;// dropping next digit if necesarry / result is negative
                cnr[ma-i]=s;
             //saving result at the same digit as one calculated and doing additional steps if remainder exists
            }
            cnr[0]=0;
        }
        else if (cmp==-2){
            int borrow=0;
            for(int i=0; i<ma; i++){
                int avr=(la>i)?bnr[la-i-1]:0;
                int bvr=(lb>i)?anr[lb-i-1]:0; //swapped
                avr-=borrow;
                int s=avr-bvr;
                if (s<0){ borrow=1; s+=10; }
                else borrow=0;
                cnr[ma-i]=s;
            }
            cnr[0]=-1; //negative
        }
    }

}

void ArrayTostring(std::string &c, int *cnr, int ma){
    if (cnr[0]==-1) c+='-';
    bool lead=true;
    for(int i=0; i<=ma; i++){
        if (cnr[i]==-1) continue;
        if (lead && cnr[i]==0) continue;
        lead=false;
        c+=(char)('0'+cnr[i]);
    }
    if (c.empty() || c=="-") c="0";
    return;
}

void masscli(int *cnr){
    std::cout << "------------------------------------------------------------WARNING-----------------------------------------------------" << "\n";
    std::cout << "This mode supports numbers with 1000!" << "\n";
    std::cout << "Method: from std::string it becomes a table of 100 then arithmetic is done manuanlly for each and saved in a separate array" << "\n";
    std::cout << "Manually codes since im too lazy and id like to make the project worth the effort" << "\n";
    std::cout << "As of V1.1.0, the only avabile operation for this mode is +" << "\n";
    std::cout << "--------------------------------------------------------END OF WARNING--------------------------------------------------" << "\n";
    std::string a, b, operation;
    while (true){
    std::cout << "CALC: ";
    std::cin >> operation;
    if (operation=="exit") return;
    else {
        std::cin >> a >> b;
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

void financialcli(){
    std::cout << "The Ultra Pro Corporatist Calculator made with good intentions" << "\n";
    std::cout << "Educational purposes: you will be prompted with questions for a more accurate calculation" << "\n";
    std::cout << "FINANCE CALC: ";
    std::string operation;
    std::cin >> operation;
    FinaOperationIdentifier(operation);
}

//more comprehensive help

void help(){
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
    std::cout << "  [4] Calculus — (coming soon)\n\n";

    std::cout << "-- CONVERTER MODE (./calc converter) --\n";
    std::cout << "  Units: Volume, Mass, Distance, Surface, Speed, Digital Info Storage [dig],\n";
    std::cout << "         Density, Inch-to-Cm, Feet-to-m\n\n";

    std::cout << "-- CONSTANTS USED INTERNALLY --\n";
    std::cout << "  e  = 2.71828182845904523536\n";
    std::cout << "  pi = 3.14159265358979323846\n\n";

    std::cout << "============================================================\n";
    std::cout << "  Version note: geometry 3D, trig, and calculus are stubs.\n";
    std::cout << "  Mass mode supports + and - only as of current version.\n";
    std::cout << "============================================================\n";
    std::cout << "-- OTHER FEATURES PLANNED: log/ln, mpow for decimal, debranching to a microservice version, bug fixes, functionality fix";
}

void massconverter(){
    std::cout << "The mass converter is supposed to convert certain units" << "\n";
    std::cout << "Choose measure to convert: Volume, Mass, Distance, Surface, Speed, Digital Info Storage [dig], Density, Inch-to-Cm, Feet-to-m" << "\n";
    std::string converter;
    std::cin >> converter;
}

int main(int argc, char *argv[]){
    std::string mode=argv[1];
    if(argc < 2 && mode != "static"){
        help();
        return 1;
    }
    if(mode=="interactive"){
        interactivecli();
    }
    else if(mode=="master"){
        mastercli();
    }
    else if (mode=="help"){
        help();
    }
    else if (mode=="mass"){
        int cnr[1001];
        masscli(cnr);
    }
    else if (mode=="financial"){
        financialcli();
    }
    else if (mode=="converter"){
        massconverter();
    }
    else if (mode=="geometry"){
        geometrycli();
    }
    else {
        if(argc < 5 ){
            std::cout << "Use --help for more" << "\n";
            help();
            return 1;
        }
        int a=std::stoi(argv[2]);
        int b=std::stoi(argv[3]);
        std::string operation=argv[4];
        if (mode=="static"){
            OperationIdentifier(a, b, operation);
        }
    }
    return 0;
}

//as a last notice i finally see why monoliths arent supposed to be made most of the time
//next project will be a cluster of microservices, i didnt decide what to do yet
