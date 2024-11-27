#include <stdio>
#include <stdlib.h>


struct node {
    int data;
    struct node* next;
}


struct node* createNode(int data){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    if(newNode == NULL){
        prinf("Memory not allocated");
        exit(0);
    }

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
} 



void insertAtEND(struct node** head,int data){
    struct node* newNode = createNode(data);
    if(*head == NULL){
        *head = newNode;
        return;
    }

    struct node *temp = *head;
    if(temp != NULL){
        temp = temp->next;
    }
    temp->next = newNode;

}

int printList(struct node* head){
    struct node* temp = head;
    if(temp != NULL){
        
    }
}
int main(){
    struct node *temp = NULL;
    insertAtEND(&temp,30);



    return 0;
}
