#include <stdio.h>
#include <stdlib.h>


struct node{
    int data;
    struct node *  next;
};


struct node* createNode(struct node* head){
    struct node* newNode = (struct node *)malloc(sizeof(struct node));
    if(newNode == NULL){
        printf("Memory Allocation Failed");
        return;
    }

    newNode->data = head;
    newNode->next = NULL:

    return newNode;

}


void inserting(struct node** head, int data){
    struct node* newNode = (struct node *)malloc(sizeof(struct node));

    newNode->next = *head;
    *head = newNode;
    

}

