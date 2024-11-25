#include <stdio.h>

int main(){
    //Decleration - 
    int arr[2][2] = {10,30,5,9};
    int arrp[2][2] = {{1,5},{4,0}};
    int arrR[][2] = {4,2,5,6,3,4};

    for(int i = 0; i < 2;i++){
        for(int j = 0; j < 2; j++){
            printf("%d ",arrR[i][j]);
        }
    }
}






