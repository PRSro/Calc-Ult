// Concept project for a sample TUI application working solely on cpp. For future projects
// A basic project good for any started. Even ai can make it so i added some interesting functions to extent the terminal
#include <iostream>
#include <string>
using namespace std; //to be removed sooner-later to decrease bloatware from strings
//dodging by reference in first functions for safe input

//declaration of mass arithmetic result
int cnr[1000];
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

int mpow(int a, int b){
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
        cout << mpow(a,b) << endl;
    }
    if (operation=="mul2"){
        cout << int(a<<b) << endl; // a * 2^b
    }
    if (operation=="div2"){
        cout << int(b>>a) << endl; // b / 2^a
    }
    if (operation=="sepmul2"){
        cout << int(1<<a) << endl;
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