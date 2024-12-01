#include <stdio.h>
#include <stdlib.h>


struct node {
    int data;
    struct node *next;
};


struct node* createNode(int data){
    struct node* newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}


void insert(struct node** head, int data) {
    struct node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void delete(struct node** head, int key){
    struct node* temp = *head, *prev = NULL;

    if(temp != NULL && temp->data == key){
        *head = temp->next;
        free(temp);
        return;
    }
    
    while(temp != NULL && temp->data != key){
        prev = temp;
        temp = temp->next;
    }


    if(temp == NULL){
        return;
    }

    prev->next = temp->next;
    free(temp);
}



int printing(struct node* head){
    struct node * temp = head;
    while(temp != NULL){
        printf("%d -> ",temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
} 



int main(){
    struct node *head = NULL; 

    insert(&head,25);
    insert(&head,31);
    insert(&head,88);
    insert(&head,100);

    printing(head);

    delete(&head,25);

    printing(head);


    return 0;
}