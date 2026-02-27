#include <iostream>
using namespace std;
    const int rows=3;
    const int cols=3;
void addMatrix(int m1[rows][cols], int m2[rows][cols], int r[rows][cols]){
    cout<<"ADD: "<<endl;
    for(int i=0; i<rows; i++){
        for (int j = 0; j <cols ; j++){
            r[i][j]=m1[i][j]+m2[i][j];
            cout<<r[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void mulMatrix(int m1[rows][cols], int m2[rows][cols], int r[rows][cols]){
    cout<<"MULTIPLY: "<<endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            r[i][j] = 0;             
            for (int k = 0; k < 3; k++) {
                r[i][j] += m1[i][k] * m2[k][j];
            }
            cout<<r[i][j]<<" ";
        }
}
    cout<<endl;
}
void transposeMatrix1(int m1[rows][cols], int m2[rows][cols], int r[rows][cols]){
    cout<<"Transpose of the Fisrt Matrix: ";
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            r[i][j]=m1[j][i];
            cout<<r[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void transposeMatrix2(int m1[rows][cols], int m2[rows][cols], int r[rows][cols]){
    cout<<"Transpose of the Fisrt Matrix: ";
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            r[i][j]=m2[j][i];
            cout<<r[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
int main(){

    int matrix1[rows][cols]={{1, 2, 3},{4, 5, 6},{7, 8, 9}};
    int matrix2[rows][cols]={{9, 8, 7},{6, 5, 4},{3, 2, 1}};
    int result[rows][cols];
    addMatrix(matrix1, matrix2, result);
    mulMatrix(matrix1, matrix2, result);
    transposeMatrix1(matrix1, matrix2, result);
    transposeMatrix2(matrix1, matrix2, result);
    return 0;
}