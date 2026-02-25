#include <iostream>
using namespace std;
void Fibonacci(int a){
    int result=0, fNum=0, sNum=1;
    for (int i = 1; i < a; i++){
        result=fNum+sNum;
        cout<<fNum<<" + "<<sNum<<" = "<<result<<endl;
        fNum=sNum;
        sNum=result;
    }
}
void Arithmetic(int startNum, int diference, int times){
    for (int i = 1; i <= times ; i++){
        cout<<startNum<<" ";
        startNum+=diference;
    }
    
}
void Geometric(int startNum, int factor, int times){
    for (int i = 1; i <= times ; i++){
        cout<<startNum<<" ";
        startNum*=factor;
    }
    
}
void showCmds(){
    cout<<"\n====================\n";
    cout<<"1 - Fibonacci\n";
    cout<<"2 - Arithmetical\n";
    cout<<"3 - Geometric\n";
    cout<<"====================\n";
}
int main(){
    int cmds, a, b, c;
    showCmds();
    cin>>cmds;
    switch (cmds)
    {
    case 1:
        cout<<"Enter Times: ";
        cin>>a;
        if (a<=0)
        {
            cout<<"Invalid Input!\n";
            break;
        }
        Fibonacci(a);
        break;
    case 2:
        cout<<"Enter Start Number: ";
        cin>>a;
        cout<<"Enter Diference: ";
        cin>>b;
        cout<<"Enter Times: ";
        cin>>c;
        Arithmetic(a,b,c);
        break;
    case 3:
        cout<<"Enter Start Number: ";
        cin>>a;
        cout<<"Enter Factor: ";
        cin>>b;
        cout<<"Enter Times: ";
        cin>>c;
        Geometric(a,b,c);
        break;
    default:
        cout<<"Invalid Input!\n";
        break;
    }
    return 0;
}