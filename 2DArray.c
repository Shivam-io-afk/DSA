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



/* General formula to calculate address of particular element by Row major order */

//Suppose We have matrix in m*n order so ( 'm' for row and 'n' for coloumn) -
a[i][j] = Base + ((i*n) + j) * size { -> which is '4' given in question or int has '4' bytes 'memory'}

//if base index started from 1 so
a[i][j] = Base + (((i-1)*n) + j-1) * size { -> which is '4' given in question or int has '4' bytes 'memory'}




