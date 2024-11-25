#include <stdio.h>


void printingPointer();
int main(){
    printingPointer();
    return 0;
}


 
void printingPointer(){
    int arr[50];
    int *p;
    p = arr;

    printf("Enter - ");
    for(int i = 0; i < 5; i++){
        // scanf("%d",(arr+i));
        scanf("%d",(p+i));
        // scanf("%d",(i+arr));
        // scanf("%d",&p[i]);
    }



    for(int i = 0; i < 5; i++){
        // printf("%d, ",arr[i]);
        // printf("%d ",*(p+i));
        // printf("%d ",i[arr]);
        printf("%d ",i[p]);
    }
}




