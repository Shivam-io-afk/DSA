#include <stdio.h>

int main(){
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