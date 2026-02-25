#include <iostream>
using namespace std;
void rightTriangle(int size){
    for (int i = 1; i <= size; i++)
    {
        for (int j = 1; j <= i ; j++)
        {
            cout<<"* ";
        }
        cout<<endl;
    }
}

void pyramid(int size){
    for (int i = 1; i <= size; i++){
        for (int k = size; k >= i; k--)
        {
            cout<<" ";
        }
        for (int j = 1; j <=i; j++)
        {   
            cout<<"* ";
        }
            cout<<endl;
    }
    
}

void square(int size){
    for (int i = 1; i <= size; i++)
    {
        for(int j=1; j<=size; j++){
            cout<<"* ";
        }
        cout<<endl;
    }
    
}
void choise(int choise, int size){
    switch (choise)
    {
    case 1:
        rightTriangle(size);
        break;
    case 2:
        pyramid(size);
        break;
    case 3:
        square(size);
        break;    
    default:
        cout<<"Invalid Input!\n";
        break;
    }
}
void showCmds(){
    cout<<"1 - Right Triangle\n";
    cout<<"2 - Pyramid\n";
    cout<<"3 - Square\n";
}
int main(){
    showCmds();
    int size, choice;
    cout<<"Choice: ";
    cin>>choice;
    cout<<"Enter Size: ";
    cin>>size;
    if (choice < 1 or size < 0)
    {
        cout<<"Invalid Choice or Size!\n";
        return 0;
    }
    choise(choice, size);
    return 0;
}