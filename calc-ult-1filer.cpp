// Concept project for a sample TUI application working solely on cpp. For future projects
// A basic project good for any started. Even ai can make it so i added some interesting functions to extent the terminal
#include <iostream>
#include <string>
#include <iomanip>
using namespace std; //to be removed sooner-later to decrease bloatware from strings
//dodging by reference in first functions for safe input
//declaration of mass arithmetic result
// Might stop at version 1.5 or 2.0 when i aim to reach 2000 lines of code excluding comments
int cnr[1001];
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
    int c=0, r, d=a;
    while (d!=0){
        c+=d%10;
        if (c==a) break;
        c*=10;
        if (c==a) break; //2 times so we have -1 step but more stuff to check
        d/=10;
    }
    return c;
}

// P.S: AI wasnt used to any extend besides advice and minor debugging
// dodging case switch for now as ill add in a new version

void simpledebt(double a, double b, double r){
    cout << "TOTAL INTEREST: " << a*(r/100)*b << endl;
    cout << "YEARLY PAY: " << a*(r/100) << endl;
    cout << "AVERAGE MONTHLY PAY: " << a*(r/100)/12 << endl;
    cout << "DAILY IMPACT: " <<fixed<<setprecision(3)<<a*(r/100)/365 << endl;
}

void complexdebt(double a, double b, double r){
    cout << "TOTAL INTEREST: " << a*mpow(1+r/100, b) << endl;
    for (int i=1; i<=b; i++){
        cout << "YEAR " << i << " INTEREST IS " << a * mpow(1+r/100, i)-a * mpow(1+r/100, i-1) << endl;
    }
}

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
    if (operation=="mul2"){
        cout << int(a<<b) << endl; // a * 2^b
    }
    if (operation=="div2"){
        cout << int(b>>a) << endl; // b / 2^a
    }
    if (operation=="sepmul2"){
        cout << int(1<<a) << endl; //
    }
    if (operation=="sepdiv2"){
        cout << int(1>>a) << endl;
    }
    if (operation=="find"){
        cout << numfinder(a, b) << endl;
    }
    if (operation=="ogl"){
        cout << ogl(a) << " " << ogl(b) << endl;
    }
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
    //more limited as the functions are needed manuanlly
}
void interactivecli(){
    //basic continuous interactive cli
    int a, b;
    string operation;
    while(true){
        cout << "CALC:";
        cin >> a >> b >> operation;
        if (operation=="exit") return;
        OperationIdentifier(a, b, operation);
    }
}

void mastercli(){
    //master mode for real numbers
    double a, b;
    string operation;
    while (true){
        cout << "CALC: ";
        cin >> a >> b >> operation;
        if (operation=="exit")return;
        OperationRealidentifier(a, b, operation);
    }
}

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
}

void ArrayToString(string &c, int *cnr, int ma){
    bool lead=true;
    for(int i=0; i<=ma; i++){
        if (lead && cnr[i]==0) continue;
        lead=false;
        c+=(char)('0'+cnr[i]);
    }
    if (c.empty()) c='0';
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
    cin >> a >> b >> operation;
    if (operation=="exit") return;
    else {
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
    cerr << "main started, argc=" << argc << endl;
    if(argc < 2){
        cout << "Use --help for more" << endl;
        return 1;
    }
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
    else {
        if(argc < 5 ){
            cout << "Use --help for more" << endl;
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