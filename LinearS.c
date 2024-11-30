#include <stdio.h>
#include <windows.h> 

//1D ->
int main(){
    int size;
    printf("Enter Size of array - \n");
    scanf("%d",&size);

    int arr[size];
    
    printf("Input the elements in the array - \n");
    for(int k = 0; k < size; k++){
        scanf("%d",&arr[k]);
    }


    printf("Here is resultent Array - \n");
    for(int s = 0; s < size; s++){
        printf("%d ",arr[s]);
    }


    int value;
    printf("\nEnter element you want to search - \n");
    scanf("%d",&value);
    

    printf("Searching... !\n");
    Sleep(2000);



    for(int l = 0; l < size; l++){
        if(arr[l] == value){
            printf("\nElement %d found at array location %d",value,l);
            return 0;
        }
    }
    printf("\nSorry elements %d not exists in arr. ",value);




    return 0;

}
