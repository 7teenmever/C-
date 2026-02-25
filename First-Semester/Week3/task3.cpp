#include <iostream>
using namespace std;
int grade(int a){
    return a/10;
}
void showGrade(int a){
    switch (a)
    {
    case 1:
        cout<<"F";
        break;
    case 2:
        cout<<"F";
        break;
    case 3:
        cout<<"F";
        break;
    case 4:
        cout<<"F";
        break;
    case 5:
        cout<<"D";
        break;
    case 6:
        cout<<"C";
        break;
    case 7:
        cout<<"B";
        break;    
    case 8:
        cout<<"B";
        break;   
    case 9:
        cout<<"A";
        break; 
    case 10:
        cout<<"A+";
        break;
    default:
        break;
    }
    cout<<endl;
    if (a>=9)
    {
        cout<<"Fantastic!";
    }
    else if (a==7 or a==8)
    {
        cout<<"Good Job!";
    }
    else
    {
        cout<<"Try Better!";
    }
}
int main(){
    int mark;
    cout<<"Enter Marks: ";
    cin>>mark;
    cout<<"Grade: ";
    grade(mark);
    showGrade(grade(mark));
    return 0;
}