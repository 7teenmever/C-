#include <iostream>
using namespace std;
int main(){
    int choise;
    cout<<"Choose one number: \n";
    cout<<"    1 - Right Triangle\n";
    cout<<"    2 - Inverted Right Triangle\n";
    cout<<"    3 - Pyramid\n";
    cout<<"    4 - Number Pyramid\n";
    cout<<"Choise: ";
    cin>>choise;
    switch (choise)
    {
    case 1:
        for (int i = 1; i <= 5; i++)
        {
            for (int j = 0; j < i; j++)
            {
                cout<<"* ";
            }
            cout<<endl;
        }
        break;
    case 2: 
        for (int i = 5; i >= 1; i--)
        {
            for (int j = i; j > 0; j--)
            {
                cout<<"* ";
            }
            cout<<endl;
        }
        
        break;
    case 3:
        for (int i = 1; i <= 4; i++)
        {
            for (int k = 6; k >= i; k--)
            {
                cout<<" ";
            }
            for (int j = 1; j <=i; j++)
            {   
                cout<<"* ";
            }
            cout<<endl;
        }
        break;
    case 4:
        for (int i = 1; i <= 5; i++)
        {
            for (int j = 1; j < i+1; j++)
            {
                cout<<j<<" ";
            }
            cout<<endl;
        }
        break;
    default:
        cout<<"Invalid Choise ! ! !\n";
        break;
    }
    return 0;
}