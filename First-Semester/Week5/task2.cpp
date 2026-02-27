#include <iostream>
using namespace std;
void pointerArrayOperations(int *arr, int size){
    int sum = 0;
    int *p = arr;       
    int num[size];        
    int *arrcpy = num;    
    int value = 30;
    bool isExist = false;
    while (p < arr + size){
        sum += *p;        
        *arrcpy = *p;     
        if (*p == value)  
            isExist = true;
        p++;
        arrcpy++;
    }
    cout << "Sum: " << sum << endl;
    cout << "Copied Array: ";
    arrcpy = num;
    while (arrcpy < num + size){
        cout << *arrcpy << " ";
        arrcpy++;
    }
    cout << endl;

    if (isExist){
        cout << "Yes, the value " << value << " exists!\n";
    }
    else{
        cout << "No, there is no value " << value << endl;
    }
    
}

int main(){
    int arr[] = {10, 20, 30, 40, 50};
    int size = 5;
    pointerArrayOperations(arr, size);
    return 0;
}