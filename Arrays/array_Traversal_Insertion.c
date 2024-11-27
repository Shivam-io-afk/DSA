#include <stdio.h>

void arrayTraversalInsertion();



int main(){
    
    arrayTraversalInsertion();
 
    return 0;
}



void arrayTraversalInsertion(){
    int val, i;
    int arr[50];

    printf("Enter size of Array - ");
    scanf("%d",&val);

    for(i = 0; i < val; i++){
        printf("Enter %d values - ",i);
        scanf("%d",&arr[i]);
    }

    printf("Here is Traversing Result of Array - ");
    for(i = 0; i < val; i++){
        (i < val - 1) ? printf("%d, ",arr[i]) : printf("%d",arr[i]) ;
    }
    
}