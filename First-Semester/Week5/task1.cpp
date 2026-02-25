#include <iostream>
using namespace std;
void arrayOperations(int arr[], int n){
    float average;
    int maxVal=arr[0], minVal=arr[0], sum=0;
    for(int i=0; i<n; i++){
        if (arr[i]>maxVal)
        {
            maxVal=arr[i];
        }
        if (arr[i]<minVal){
            minVal=arr[i];
        }
        sum+=arr[i];
    }
    average=(float) sum/n;
    cout<<"Max Number: "<<maxVal<<endl;
    cout<<"Min Number: "<<minVal<<endl;
    cout<<"Average: "<<average<<endl;
    cout<<"Reversed Array: ";
    for (int i=n-1; i>=0 ; i--){
        cout<<arr[i]<<" ";
    }
}
int main(){
    int n;
    cout<<"Enter Size of Array: ";
    cin>>n;
    int arr[n];
    cout<<"Enter Arrays Value: \n";
    for(int i=0; i<n; i++){
        cout<<"Number "<<i+1<<": ";
        cin>>arr[i];
    }
    arrayOperations(arr, n);
    return 0;
}