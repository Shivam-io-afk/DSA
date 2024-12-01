#include <stdio.h>
#include <stdlib.h>


struct node{
    int data;
    struct node *  next;
};


struct node* createNode(int data){
    struct node* newNode = (struct node *)malloc(sizeof(struct node));
    if(newNode == NULL){
        printf("Memory Allocation Failed");
        return 0;
    }

    newNode->data = data;
    newNode->next = NULL;

    return newNode;

}


void inserting(struct node** head, int data){
    struct node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}



//--------------------------------------------->
void insertAtIndex(struct node** head, int index, int value) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;

    if (index == 0) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    struct node* temp = *head;
    int count = 0;
    while (temp != NULL && count < index - 1) {
        temp = temp->next;
        count++;
    }

    if (temp == NULL) {
        printf("Index out of bounds.\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}
//--------------------------------------------->



void printing(struct node *head){
    struct node* temp = head;
    while(temp != NULL){
        printf("%d -> ",temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}


int main(){
    struct node* head = NULL;

    inserting(&head,65); 
    inserting(&head,42); 
    inserting(&head,89); 

    printing(head);


    insertAtIndex(&head, 3, 12);
    printing(head);
}