// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>

int main() {
    int i = 1;
    
    repeat:
    if(i <= 10){
    printf("%d -> ",i);
    i++;
    }
    else{
        printf("END");
        exit(0);
    }
    goto repeat;
    return 0;
}