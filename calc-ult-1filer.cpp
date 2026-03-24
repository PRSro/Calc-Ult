// Concept project for a sample TUI application working solely on cpp. For future projects
// A basic project good for any started. Even ai can make it so i added some interesting functions to extent the terminal
#include <iostream>
#include <string>
#include <iomanip>
using namespace std; //to be removed sooner-later to decrease bloatware from strings
//dodging by reference in first functions for safe input
//declaration of algebraic functions and needed constants
// Might stop at version 1.5 or 2.0 when i aim to reach 2000 lines of code excluding comments
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
    cout << "TOTAL INTEREST: " << a*(r/100)*b << endl;
    cout << "YEARLY PAY: " << a*(r/100) << endl;
    cout << "AVERAGE MONTHLY PAY: " << a*(r/100)/12 << endl;
    cout << "DAILY IMPACT: " <<fixed<<setprecision(3)<<a*(r/100)/365 << endl;
}

void complexdebt(double a, double b, double r){
    cout << "TOTAL INTEREST: " << a*mpow(1+r/100, b)-a << endl;
    for (int i=1; i<=b; i++){
        cout << "YEAR " << i << " INTEREST IS " << a * mpow(1+r/100, i)-a * mpow(1+r/100, i-1) << endl;
    }
}
// as of V1.2.0 all work
void OperationIdentifier(int a, int b, string operation){
    if (operation=="+"){
        cout << a+b << endl;
    }
    if (operation=="-"){
        cout << a-b << endl;
    }
    if (operation=="*"){
        cout << a*b << endl;
    }
    if (operation=="/"){
        cout << a/b << endl;
    }
    if (operation=="gcd"){
        cout << mgcd(a, b) << endl;
    }
    if (operation=="^"){
        cout << npow(a, b) << endl;
    }
    if (operation=="mul2"){
        cout << (double)(a<<b) << endl; // a * 2^b
    }
    if (operation=="div2"){
        cout << (double)(b>>a) << endl; // b / 2^a
    }
    if (operation=="sepmul2"){
        cout << (double)(1<<a) << endl; //
    }
    if (operation=="sepdiv2"){
        cout << (double)(1>>a) << endl;
    }
    if (operation=="find"){
        cout << numfinder(a, b) << endl;
    }
    if (operation=="ogl"){
        cout << ogl(a) << " " << ogl(b) << endl;
    }
    if (operation=="sqrt"){
        cout << msqrt(a) << " " << msqrt(b) << endl;
    }
}

void FinaOperationIdentifier(string operation){
    if (operation=="%"){
        cout << "ENTER PRECISION: ";
        int p;
        cin >> p;
        cout << endl;
        cout << "ENTER NUMBERS: (a>b) ";
        double a, b;
        cin >> a >> b;
        percents(a, b, p);
    }
    if (operation=="simpledebt"){
        cout << "DEBT: SUM is ... " << endl; // Ds=S*r/100+b
        double a;
        cin >> a;
        cout << endl;
        cout << "DEBT: YEARS is ... ";
        double b;
        cin >> b;
        cout << endl;
        cout << "Enter Rate offered by bank: ";
        double r;
        cin >> r;
        simpledebt(a, b, r);
    }
    if (operation=="complexdebt"){
        cout << "DEBT: INITIAL SUM is ... " << endl; // Ds=S*r/100+b
        double a;
        cin >> a;
        cout << endl;
        cout << "DEBT: YEARS is ... ";
        double b;
        cin >> b;
        cout << endl;
        cout << "Enter Rate offered by bank: ";
        double r;
        cin >> r;
        complexdebt(a, b, r);
    }
}

void OperationRealidentifier(double a, double b, string operation){
     if (operation=="+"){
        cout << a+b << endl;
    }
    if (operation=="-"){
        cout << a-b << endl;
    }
    if (operation=="*"){
        cout << a*b << endl;
    }
    if (operation=="/"){
        cout << a/b << endl;
    }
    if (operation=="sqrt"){
        cout << msqrt(a) << " " << msqrt(b) << endl;
    }
    if (operation=="%"){
        cout << "If the numbers are double this will calculate the percentage of both the smaller one over the larger one and vice versa" << endl;
        // will need a different % function since it needs precision and fixing of unorder
    }
    //more limited as the functions are needed manuanlly
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


void statisticscli(){
    //good to mention: struct vs class:
    //struct is good for public datasets and has everything public by default.
    //To make things easier we will use a class instead with more OOP flavour
    //leaving this commented for a future version
    cout << "STATISTIC STAGE" << endl;
    cout << "STAGE 1: Data typing" << endl;
    cout << "EXPLANATION: You give the number of values and type of values. accordingly a table can either be generated or the dataset can be worked with" << endl;
    cout << "STAGE 2: Basic statistics" << endl;
    cout << "EXPLANATION: There will be calculated the mean, the average, the highest/lowest points, the mode, and based on subgroups and given data there will be given results" << endl;
    cout << "STAGE 3: Pretty print" << endl;
    cout << "EXPLANATION: Everything will be printed accordingly." << endl;
    cout << "ENTER: number of values" << endl;
/*   stage1();
    stage2();
    stage3(); */
}

void geometrycli(){
    cout << "GEOMETRY CALCULATOR" << endl;
    cout << "CHOOSE MODE: [1] cartezian/euclidean 2D calculation" << endl;
    cout << "             [2] cartezian/euclidean 3D calculation" << endl;
    cout << "             [3] trigonometric values" << endl;
    cout << "             [4] calculus" << endl;                
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
    cout << "------------------------------------------------------------WARNING-----------------------------------------------------" << endl;
    cout << "This mode supports numbers with 1000!" << endl;
    cout << "Method: from string it becomes a table of 100 then arithmetic is done manuanlly for each and saved in a separate array" << endl;
    cout << "Manually codes since im too lazy and id like to make the project worth the effort" << endl;
    cout << "As of V1.1.0, the only avabile operation for this mode is +" << endl;
    cout << "--------------------------------------------------------END OF WARNING--------------------------------------------------" << endl;
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
        cout << c << endl;
        }
    }
}

void financialcli(){
    cout << "The Ultra Pro Corporatist Calculator made with good intentions" << endl;
    cout << "Educational purposes: you will be prompted with questions for a more accurate calculation" << endl;
    cout << "FINANCE CALC: ";
    string operation;
    cin >> operation;
    FinaOperationIdentifier(operation);
}

void help(){
    cout << "Powershell and Linux/MacOS CLI Usage:" << endl;
    cout << "execute: chmod +x ./calc" << endl;
    cout << "usage: ./calc <a> <b> <operation>" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Windows CMD usage" << endl;
    cout << "execute: chmod +x .\\calc" << endl;
    cout << "usage: .\\calc <a> <b> <operation>" << endl;
    cout << "The program cant be run yet without ./ as its a prealpha version and isnt compiled yet" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Interactive Usage" << endl;
    cout << "<operation> <a> <b>" << endl; //Bug assesment: infinite loop if used same as general syntax
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
            cout << "Use --help for more" << endl;
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