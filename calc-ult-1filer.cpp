// Concept project for a sample TUI application working solely on cpp. For future projects
// A basic project good for any started. Even ai can make it so i added some interesting functions to extent the terminal
#include <iostream>
#include <string>
#include <iomanip>
using namespace std; //to be removed sooner-later to decrease bloatware from strings
//dodging by reference in first functions for safe input
//declaration of algebraic functions and needed constants
// Might stop at version 1.5 as i see the extend is getting rather too diverse
int cnr[1001];
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
    return d;
}

double mpow(double a, int b){
    if (b==1) return a;
    else if (b==0) return 1;
    double c=a;
    if (b>1){
        for (int i=1; i<b; i++){
            c*=a;
        } 
        return c;
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
    cout << mi << " represents " <<fixed<<setprecision(s)<<p<<"% of "<<ma;
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

int vectoromparison(int ll, int *anr, int *bnr){
    for (int i=0; i>ll; i--){
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
        else return vectoromparison(shortcut, anr, bnr);
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
    cout << "TOTAL INTEREST: " << a*(r/100)*b << "\n";
    cout << "YEARLY PAY: " << a*(r/100) << "\n";
    cout << "AVERAGE MONTHLY PAY: " << a*(r/100)/12 << "\n";
    cout << "DAILY IMPACT: " <<fixed<<setprecision(3)<<a*(r/100)/365 << "\n";
}

void complexdebt(double a, double b, double r){
    cout << "TOTAL INTEREST: " << a*mpow(1+r/100, b)-a << "\n";
    for (int i=1; i<=b; i++){
        cout << "YEAR " << i << " INTEREST IS " << a * mpow(1+r/100, i)-a * mpow(1+r/100, i-1) << "\n";
    }
}
// as of V1.2.0 all work
void OperationIdentifier(int a, int b, string operation){
    if (operation=="+"){
        cout << a+b << "\n";
    }
    if (operation=="-"){
        cout << a-b << "\n";
    }
    if (operation=="*"){
        cout << a*b << "\n";
    }
    if (operation=="/"){
        cout << a/b << "\n";
    }
    if (operation=="gcd"){
        cout << mgcd(a, b) << "\n";
    }
    if (operation=="^"){
        cout << npow(a, b) << "\n";
    }
    if (operation=="mul2"){
        cout << (double)(a<<b) << "\n"; // a * 2^b
    }
    if (operation=="div2"){
        cout << (double)(b>>a) << "\n"; // b / 2^a
    }
    if (operation=="sepmul2"){
        cout << (double)(1<<a) << "\n"; //
    }
    if (operation=="sepdiv2"){
        cout << (double)(1>>a) << "\n";
    }
    if (operation=="find"){
        cout << numfinder(a, b) << "\n";
    }
    if (operation=="ogl"){
        cout << ogl(a) << " " << ogl(b) << "\n";
    }
    if (operation=="sqrt"){
        cout << msqrt(a) << " " << msqrt(b) << "\n";
    }
}

void FinaOperationIdentifier(string operation){
    if (operation=="%"){
        cout << "ENTER PRECISION: ";
        int p;
        cin >> p;
        cout << "\n";
        cout << "ENTER NUMBERS: (a>b) ";
        double a, b;
        cin >> a >> b;
        percents(a, b, p);
    }
    if (operation=="simpledebt"){
        cout << "DEBT: SUM is ... " << "\n"; // Ds=S*r/100+b
        double a;
        cin >> a;
        cout << "\n";
        cout << "DEBT: YEARS is ... ";
        double b;
        cin >> b;
        cout << "\n";
        cout << "Enter Rate offered by bank: ";
        double r;
        cin >> r;
        simpledebt(a, b, r);
    }
    if (operation=="complexdebt"){
        cout << "DEBT: INITIAL SUM is ... " << "\n"; // Ds=S*r/100+b
        double a;
        cin >> a;
        cout << "\n";
        cout << "DEBT: YEARS is ... ";
        double b;
        cin >> b;
        cout << "\n";
        cout << "Enter Rate offered by bank: ";
        double r;
        cin >> r;
        complexdebt(a, b, r);
    }
}

void OperationRealidentifier(double a, double b, string operation){
     if (operation=="+"){
        cout << a+b << "\n";
    }
    if (operation=="-"){
        cout << a-b << "\n";
    }
    if (operation=="*"){
        cout << a*b << "\n";
    }
    if (operation=="/"){
        cout << a/b << "\n";
    }
    if (operation=="sqrt"){
        cout << msqrt(a) << " " << msqrt(b) << "\n";
    }
    if (operation=="%"){
        cout << "If the numbers are double this will calculate the percentage of both the smaller one over the larger one and vice versa" << "\n";
        // will need a different % function since it needs precision and fixing of unorder
    }
    //more limited as the functions are needed manuanlly and might move each definition to a separate cpp
}
void interactivecli(){
    //basic continuous interactive cli
    int a, b;
    string operation;
    while(true){
        cout << "CALC:";
        cin >> operation;
        if (operation=="exit") return;
        else {cin >> a >> b;  OperationIdentifier(a, b, operation);}
    }
}

void mastercli(){
    //master mode for real numbers
    double a, b;
    string operation;
    while (true){
        cout << "CALC: ";
        cin >> operation;
        if (operation=="exit")return;
        else{cin >> a >> b; OperationRealidentifier(a, b, operation);}
    }
}

// Statistics functions
void stage1(int &a, int &c, int &b, int &d){
    cout << "Enter number of integer values" << "\n";
    cin >> a;
    cout << "Enter length of rows for integer values" << "\n";
    int h;
    if (a==0){
        cout << "Enter number of real values" << "\n"; 
        double c; 
        cin >> c;
        cout << "Enter length of rows for real values" << "\n";
        int g;
        cin >> g;
    }
    else {
        string e;
        cout << "Add real numbers?[y/N]" << "\n"; 
        cin >> e; 
        if(e=="y"||e=="Y"||e=="Yes"||e=="yes"){
            cout << "Enter number of real values" << "\n"; 
            int c; 
            cin >> c;
            cout << "Enter length of rows for real values" << "\n";
            int i;
            cin >> i;
        }
     }
     cout << "Add char to value correspondence?[y/n]" << "\n";
     string f;
     cin >> f;
     if (f=="y"){
        cout << "Add strings? [Y/n]" << "\n";
        string ans;
        cin >> ans;
        if(ans=="y"||ans=="Y"||ans=="Yes"||ans=="yes"){
        cout << "Enter number of strings" << "\n";
        cin >> b;
     }
     cout << "The total number of values is " << d << " " << a << " out of them int, " << b << " out of them strings, " << c << " out of them real!" << "\n";
    }
}

void stage2(int a, int c, int b, int rowa, int rowb, int rowc, char **charc, int **integer, double **real) {
	if (c!=0) {
		for (int i=1; i<=c; i++) {
			cout << "Enter char values, Series" << i << " out of " << c;
			for(int j=1; j<=rowc; j++) {
				cin >> charc[i][j];
			}
		}
	}
	if (b!=0) {
		for (int i=1; i<=b; i++) {
			cout << "Enter integer values, Series" << i << " out of " << b;
			for(int j=1; j<=rowb; j++) {
				cin >> integer[i][j];
			}
		}
	}
	if (a!=0) {
		for (int i=1; i<=a; i++) {
			cout << "Enter real values, Series" << i << " out of " << a;
			for(int j=1; j<=rowa; j++) {
				cin >> real[i][j];
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
            for()
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
    //classes and struct seem deprecated/not what we need for such sweaty statistics, not because i dont like them but because OOP for this project seems uselless
    //instead we will do a declaration of class after the vector is declared acording to the user
    cout << "STATISTIC STAGE" << "\n";
    cout << "STAGE 1: Data typing" << "\n";
    cout << "EXPLANATION: You give the number of values and type of values. accordingly a table can either be generated or the dataset can be worked with" << "\n";
    cout << "STAGE 2: Basic statistics" << "\n";
    cout << "EXPLANATION: There will be calculated the mean, the average, the highest/lowest points, the mode, and based on subgroups and given data there will be given results" << "\n";
    cout << "EXPLANATION: But first introduce ";
    cout << "STAGE 3: Pretty print" << "\n";
    cout << "EXPLANATION: Everything will be printed accordingly." << "\n";
    cout << "ENTER: number of values" << "\n";
    int a, b, c, d;
    stage1(a, c, b, d);
      /*  stage2();
    stage3(); */
}
struct cart2 {
    double x;
    double y;
} cartlist[10001];

void calcdim2(cart2 *cartlist){
    cout << "Enter shape to work with" << '\n';
    string shape;
    cin >> shape;
    if (shape=="triangle"){

    }
    else if (shape=="square"){

    }
    else if (shape=="hexagon"){

    }
    else if (shape=="circle"){

    }
    else if (shape=="cartezian"){
        cout << "Enter number of points to work with" << '\n';
        int a;
        cin >> a;
        double k, j;
        cout << "WARNING: max points stored go up to 10000, the limit is the one of double" << '\n';
        for(int i=1; i<=a; i++){
            cout << "Enter coordinates for point number " << i << " out of " << a << "\n";
            cin >> cartlist[i].x >> cartlist[i].y;
        }
        cout << "What to do?" << '\n';
        cout << "[1] calculate multidistance (distance between all points) and output in pretty format" << '\n';
        cout << "[2] calculate certain distance " << '\n';
        cout << "[3] calculate middle points " << '\n';
        cout << "[4] calculate slope or make/insert function" << '\n'; // insert as in to find out which points correspond to that ecuation and correspondence x and y
    }
}
void geometrycli(){
    cout << "GEOMETRY CALCULATOR" << "\n";
    cout << "This mode isnt responsible for any simulation of the provided shapes" << "\n";
    cout << "CHOOSE MODE: [1] cartezian/euclidean 2D calculation" << "\n";
    cout << "             [2] cartezian/euclidean 3D calculation" << "\n";
    cout << "             [3] trigonometric values" << "\n";
    cout << "             [4] calculus" << "\n";
    int choice;
    if(choice==1){
        // calcdim2
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
void StringToArray(const string &a, const string &b, int *anr, int *bnr){
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

void ArithmeticIdentifier(int *anr, int *bnr, int *cnr, int la, int lb, string operation, int &ma){
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

void ArrayToString(string &c, int *cnr, int ma){
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

void masscli(){
    // might be extended to up too  1000 digits if things go well
    cout << "------------------------------------------------------------WARNING-----------------------------------------------------" << "\n";
    cout << "This mode supports numbers with 1000!" << "\n";
    cout << "Method: from string it becomes a table of 100 then arithmetic is done manuanlly for each and saved in a separate array" << "\n";
    cout << "Manually codes since im too lazy and id like to make the project worth the effort" << "\n";
    cout << "As of V1.1.0, the only avabile operation for this mode is +" << "\n";
    cout << "--------------------------------------------------------END OF WARNING--------------------------------------------------" << "\n";
    string a, b, operation;
    while (true){
    cout << "CALC: ";
    cin >> operation;
    if (operation=="exit") return;
    else {
        cin >> a >> b;
        int la=a.length(), lb=b.length(), ma;
        int anr[a.length()], bnr[b.length()];
        string c="";
        StringToArray(a, b, anr, bnr);
        ArithmeticIdentifier(anr, bnr, cnr, la, lb, operation, ma);
        ArrayToString(c, cnr, ma);
        cout << c << "\n";
        }
    }
}

void financialcli(){
    cout << "The Ultra Pro Corporatist Calculator made with good intentions" << "\n";
    cout << "Educational purposes: you will be prompted with questions for a more accurate calculation" << "\n";
    cout << "FINANCE CALC: ";
    string operation;
    cin >> operation;
    FinaOperationIdentifier(operation);
}

void help(){
    cout << "Powershell and Linux/MacOS CLI Usage:" << "\n";
    cout << "execute: chmod +x ./calc" << "\n";
    cout << "usage: ./calc <a> <b> <operation>" << "\n";
    cout << "--------------------------------------" << "\n";
    cout << "Windows CMD usage" << "\n";
    cout << "execute: chmod +x .\\calc" << "\n";
    cout << "usage: .\\calc <a> <b> <operation>" << "\n";
    cout << "The program cant be run yet without ./ as its a prealpha version and isnt compiled yet" << "\n";
    cout << "--------------------------------------" << "\n";
    cout << "Interactive Usage" << "\n";
    cout << "<operation> <a> <b>" << "\n"; //Bug assesment: infinite loop if used same as general syntax, will fix next version with updated help guide
}

int main(int argc, char *argv[]){
    string mode=argv[1];
    if(mode=="interactive"){
        interactivecli();
    }
    else if(mode=="mastercli"){
        mastercli();
    }
    else if (mode=="help"){
        help();
    }
    else if (mode=="masscli"){
        masscli();
    }
    else if (mode=="financialcli"){
        financialcli();
    }
    else {
        if(argc < 5 ){
            cout << "Use --help for more" << "\n";
            help();
            return 1;
        }
        int a=stoi(argv[2]);
        int b=stoi(argv[3]);
        string operation=argv[4];
        if (mode=="static"){
            OperationIdentifier(a, b, operation);
        }
    }
    return 0;
}