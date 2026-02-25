#include <iostream>
using namespace std;
int balance=0;
void checkBalance(){
    cout<<"Balance: "<<balance<<endl;
}
void deposit(){
    int cash;
    cin>>cash;
    if(cash<0){
        cout<<"Invalid Input\n";
    }
    else{
        balance+=cash;
        cout<<"Balance Was Deposited!\n";
    }
    
}
void withdraw(){
    int cash;
    cout<<"How Much You Want to Withdraw: ";
    cin>>cash;
    if (balance<cash)
    {
        cout<<"There Are Not enough Funds In Your Account!\n";
    }
    else if(cash<0){
        cout<<"Invalid Input!\n";
    }
    else{
        balance-=cash;
        cout<<"Successful Operation!\n";
    }
}
void cmds(){
    cout<<"====================";
    cout<<"\n1 - Check Balance\n2 - Deposit\n3 - Withdraw\n4 - help\n5 - exit\n";
    cout<<"====================\n";
}
int main(){
    int choice;
    cmds();
    while (true)
    {
        cout<<"Enter Choice: ";
        cin>>choice;
        switch (choice)
        {
        case 1:
            checkBalance();
            break;
        case 2:
            deposit();
            break;
        case 3:
            withdraw();
            break;
        case 4:
            cmds();
            break;
        case 5:
            return 0;
            break;
        default:
            cout<<"Invalid Input!\n";
            break;
        }
    }
    return 0;
}