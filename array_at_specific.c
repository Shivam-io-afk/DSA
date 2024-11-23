#include <stdio.h>
#include <stdlib.h>

int main(){
    int arr[50];
    int num,pos,size;

    printf("Enter the size of an array - \n");
    scanf("%d",&size);

    for(int i = 0; i < size; i++){
            printf("Enter element %d at - ",i);
            scanf("%d",&arr[i]);
    }

    printf("\nValues Inserted.... !\n");

    

    int choice;
    printf("if you want to insert value at specific position then, \n");
    printf("Enter - 0\n");
    printf("if not - 1\n");
    scanf("%d",&choice);

    switch(choice){
        case 0:
            printf("\nEnter value you want to insert - ");
            scanf("%d",&num);
            printf("\nEnter at which position - ");
            scanf("%d", &pos);
            break;
        case 1:
            exit(0);
            break;
        default : 
            printf("Invalid Input");
            exit(0);
    }


    if(pos < 0 || pos > size){
        printf("Invalid ! Position");
    }
    else{
        for(int j = size - 1; j >= pos-1; j--){
                arr[j+1] = arr[j];
        }

        arr[pos - 1] = num;
        size++;


        printf("\nArray after insertion - \n");
        

        for(int i = 0; i < size; i++){
            (i < size - 1) ? printf("%d, ",arr[i]) : printf("%d",arr[i]) ;
        }
    }




    return 0;
}