#include <iostream>
using namespace std;
int main(){
    const float PI=3.14159;
    int radius, diametr=0;
    float circumference=0, area;
    cout<<"Enter Radius of a Circle: ";
    cin>>radius;
    diametr=2*radius;
    circumference=2*PI*radius;
    area=PI*radius*radius;
    cout<<"Diametr: "<<diametr<<endl;
    cout<<"Circumference: "<<circumference<<endl;
    cout<<"Area: "<<area<<endl;
    return 0;
}