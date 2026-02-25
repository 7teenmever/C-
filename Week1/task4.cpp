#include <iostream>
using namespace std;
int main(){
    int a=10;
    int counter1=a, counter2=a;
    cout<<"Initial Value of Number is: "<<a<<endl;
    a+=10;
    a-=3;
    a*=2;
    cout<<"Now Number is: "<<a<<endl;
    cout<<"Number before ++counter: "<<counter1<<endl;
    ++counter1;
    cout<<"Number After ++counter: "<<counter1<<endl;
    cout<<"Number Before counter++: "<<counter2<<endl;
    counter2++;
    cout<<"Number After counter++: "<<counter2<<endl; 
    return 0;
}