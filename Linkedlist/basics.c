#include <stdio.h>
#include <stdlib.h>



struct node{
    int data;
    struct node* next;
};


void traversalLinkedlist(struct node* ptr){
    while(ptr != NULL){
        printf("%d ",ptr->data);
        ptr = ptr->next;
    }
}

int main(){
    struct node * head;
    struct node * first;
    struct node * sec;

    head = (struct node *)malloc(sizeof(struct node));
    first = (struct node *)malloc(sizeof(struct node));
    sec = (struct node *)malloc(sizeof(struct node));


    head->data = 5;
    head->next = first;

    first->data = 10;
    first->next = sec;

    sec->data = 19;
    sec->next = NULL;

    traversalLinkedlist(head);    
}
