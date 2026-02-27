#include <iostream>
using namespace std;
int main(){
    int size;
    cout<<"Enter size of array: ";
    cin>>size; 
    int *arr=new int[size];
    for(int i=0;i<size; i++){
        cout<<"Enter element "<<i+1<<": ";
        cin>>arr[i];
    }
    int newsize;
    cout<<"Enter new size: ";
    cin>>newsize;
    int *newarray=new int[newsize];
    for(int i=0;i<newsize;i++){
        if (i<size){
            newarray[i]=arr[i];
        }
        if (i>=size){
            cout<<"Enter element "<<i+1<<": ";
            cin>>newarray[i];
        }       
    } 
    delete[] arr;
    arr=newarray;
    return 0;
} 