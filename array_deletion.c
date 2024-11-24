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
    printf("\nArray Before Deletion - \n");
    for(int i = 0; i < size; i++){
        (i < size - 1) ? printf("%d, ",arr[i]) : printf("%d",arr[i]) ;
    }
    

    int choice;
    printf("\nif you want to delete from at specific position \n");
    printf("\nEnter - 1\n");
    printf("If not - 2\n");
    scanf("%d",&choice);

    switch(choice){
        case 1:
            printf("\nEnter position you want to Delete - ");
            scanf("%d",&pos);
            break;
        case 2:
            exit(0);
            break;
        default : 
            printf("Invalid Input, Try again !");
            exit(0);
    }

    int vals;

    if(pos < 0 || pos > size){
        printf("Invalid ! Position");
    }
    else{
        vals = arr[pos - 1];
        for(int j = pos - 1; j < size - 1; j++){
                arr[j] = arr[j+1];
        }

        size--;


        printf("\nArray after Deletion - \n");
        for(int i = 0; i < size; i++){
            (i < size - 1) ? printf("%d, ",arr[i]) : printf("%d",arr[i]) ;
        }
        printf("\n%d Deleted",vals);
    }




    return 0;
}