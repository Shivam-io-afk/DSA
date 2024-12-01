#include <stdio.h>
#include <stdlib.h>


struct node {
    int data;
    struct node *next;
}


void createNode(struct node* head,int data){
    struct node* newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}


void insert(struct node** head, int data){
    struct node** newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = *head;
    *head = newNode;
}


void delete(struct node** head, int data){
    

}