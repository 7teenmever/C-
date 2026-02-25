#include <iostream>
using namespace std;
int main(){
    string name;
    int year=2026;
    int age, birth_year, realAge=0, height_feet, height_inch;
    double height_meter, meter;
    char favLetter;
    bool isProgramer, isAdult;
    cout<<"Name: ";
    cin>>name;
    cout<<"Age: ";
    cin>>age;
    cout<<"Birth Year: ";
    cin>>birth_year;
    cout<<"Height: ";
    cin>>height_meter;
    cout<<"Favorite Letter: ";
    cin>>favLetter;
    cout<<"Are You a Programmer: ";
    cin>>isProgramer;
    realAge=year-birth_year;
    meter=height_meter/100;
    height_feet=meter*3.28084;
    height_inch=((meter*3.28084)-height_feet)*12;
    if (age>=18){
        isAdult=true;
    }
    else{
        isAdult=false;
    }
    cout<<endl<<endl;
    cout<<"=== PERSONAL BIO ==="<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Age: "<<age<<" (Calculated "<<realAge<<" )"<<endl;
    cout<<"Height: "<<height_meter<<" (Approx "<<height_feet<<" feet "<<height_inch<<" inches)"<<endl;
    cout<<"Favorite Letter: "<<favLetter<<endl;
    cout<<"Is an Adult: ";if(isAdult==true){cout<<"TRUE\n";}else{cout<<"FALSE\n";}
    cout<<"Is a programmer: ";if(isProgramer==true){cout<<"TRUE\n";}else{cout<<"FALSE\n";}
    cout<<"==================="<<endl;
    return 0;
}