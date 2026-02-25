#include <iostream>
using namespace std;
int main(){
    int startNum, endNum, sum=0, evenCount=0, oddCount=0, primeCount=0, counter=0;
    float average=0;
    cout<<"Enter Start Number: ";
    cin>>startNum;
    cout<<"Enter End Number: ";
    cin>>endNum;
    if (startNum>endNum)
    {
        cout<<"Invalid Input !\n";
        return 0;
    }
    for (int i = startNum; i <= endNum; i++)
    {
        sum+=i;                      // sum of all numbers
        counter++;
        cout<<i<<" ";
        if(i%2==0){
            evenCount++;            //even
        }
        else{
            oddCount++;             //odd
        }
        bool isPrime=true;
        for (int n = 2; n < i; n++)  //prime
        {
            if (i%n==0)
            {
                isPrime=false;
                break;
            }
        }
        if (i<2)
        {
            isPrime=false;
        }
        if (isPrime){
            cout<<"(prime) ";
            primeCount++;
        }
        if(i%3==0 && i%5==0){
            cout<<"FizzBuzz ";
        }
        else if (i%3==0)
        {
            cout<<"Fizz ";
        }
        else if (i%5==0)
        {
            cout<<"Buzz ";
        }
        
        cout<<endl;
    }
    average=(float)sum/counter;
    cout<<endl;
    cout<<"Even Numbers: "<<evenCount<<endl;
    cout<<"Odd Numbers: "<<oddCount<<endl;
    cout<<"Prime Numbers: "<<primeCount<<endl;
    cout<<"Sum of All Numbers: "<<sum<<endl;
    cout<<"Average: "<<average<<endl;
    return 0;
}