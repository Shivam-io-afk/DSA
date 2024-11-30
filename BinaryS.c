#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

int main(){
    int size;
    
    printf("Enter Size of array - ");
    scanf("%d",&size);

    int arr[size];
    printf("Enter elements in {sorted} order - \n");
    
    for(int el = 0; el < size; el++)
        scanf("%d",&arr[el]);
    
    printf("Here is resultent array -\n");
    for(int el = 0; el < size; el++)
        printf("%d ",arr[el]);


    int balue;
    printf("\nEnter The element you want to search - ");
    scanf("%d",&balue);

    printf("Searching... !\n");
    Sleep(2000);

    int low, mid, high;
    low = 0;
    high = size - 1;


    while(low <= high){
        mid = (low + high) / 2;

        if(arr[mid] == balue){
            printf("Found at %d location\n",mid);
            exit(0);
        }
        else if(arr[mid] < balue){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }




    return 0;

}