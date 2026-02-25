#include <iostream>
using namespace std;
int main(){
    int appleCount=5, orangeCount=7,swap=0;
    cout<<"Apples: "<<appleCount<<endl<<"Oranges: "<<orangeCount<<endl;
    swap=appleCount;
    appleCount=orangeCount;
    orangeCount=swap;
    cout<<"Swap"<<endl;
    cout<<"Apples: "<<appleCount<<endl<<"Oranges: "<<orangeCount<<endl;
    return 0;
}