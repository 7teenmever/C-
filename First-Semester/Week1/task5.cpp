#include <iostream>
using namespace std;
int main(){
    int x=10, y=20;
    cout<<"\nIs "<<x<<" Greater than "<<y<<" ?"<<endl;
    if (x>y)
    {
        cout<<true;
    }
    else{
        cout<<false;
    }
    cout<<"\nIs "<<x<<" less than or equal to "<<y<<" ?"<<endl;
    if (x<=y)
    {
        cout<<true;
    }
    else
    {
        cout<<false;
    }
    cout<<"\nIs "<<x<<"equal to "<<y<<" ?"<<endl;
    if (x==y)
    {
        cout<<true;
    }
    else
    {
        cout<<false;
    }
    cout<<endl;
    bool isSunny=true, isWeekend=false;
    cout<<"Is it sunny AND the weekend? "<<(isSunny && isWeekend)<<endl;
    cout<<"Is it sunny OR the weekend? "<<(isSunny || isWeekend)<<endl;
    cout<<"Is it NOT sunny? "<<(!isSunny)<<endl;
    
    
    return 0;
}