#include <iostream>
using namespace std;
void primeRange(int x, int y){
    for (int i = x; i <= y; i++){
        bool isPrime=true;
        for (int j = 2; j < i; j++){
            if(i%j==0){
                isPrime=false;
                break;
            }
        }
        if(i<2){
            continue;
        }
        else if (isPrime){
            cout<<i<<" ";
        }
    }
    
}
int main(){
    int startNum, endNum;
    cout<<"Enter Start Number: ";
    cin>>startNum;
    cout<<"Eneter End Number: ";
    cin>>endNum;
    primeRange(startNum, endNum);
    return 0;
}