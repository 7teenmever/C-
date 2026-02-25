#include <iostream>
using namespace std;
int add(int a, int b){return a+b;}
int sub(int a, int b){return a-b;}
int mul(int a, int b){return a*b;}
int divide(int a, int b){return a/b;}
int module(int a, int b){return a%b;}
void cmds(){
    cout<<"1 - ADD\n2 - SUB\n3 - MUL\n4 - DIV\n5 - MOD\n6 - help\n7 - exit";
}
int main(){
    int a, b, x;
    cmds();
    while(true){
        cout<<"\nEnter Command (1-7): ";
        cin>>x;
        switch (x)
            {
            case 1:
                cout<<"Enter First Number: ";
                cin>>a;
                cout<<"Enter Second Number: ";
                cin>>b;
                cout<<add(a,b);
                break;
            case 2:
                cout<<"Enter First Number: ";
                cin>>a;
                cout<<"Enter Second Number: ";
                cin>>b;
                cout<<sub(a,b);
                break;
            case 3: 
                cout<<"Enter First Number: ";
                cin>>a;
                cout<<"Enter Second Number: ";
                cin>>b;
                cout<<mul(a,b);
                break;
            case 4:
                cout<<"Enter First Number: ";
                cin>>a;
                cout<<"Enter Second Number: ";
                cin>>b;
                cout<<divide(a,b);
                break;
            case 5:
                cout<<"Enter First Number: ";
                cin>>a;
                cout<<"Enter Second Number: ";
                cin>>b;
                cout<<module(a,b);
                break;
            case 6:
                cmds();
                break;
            case 7:
                return 0;
                break;
            default:
                break;
            }
    }

}