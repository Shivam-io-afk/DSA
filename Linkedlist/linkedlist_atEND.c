#include <stdio.h>
#include <stdlib.h>


struct node {
    int data;
    struct node* next;
};


struct node* createNode(int data){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    if(newNode == NULL){
        printf("Memory not allocated");
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
        printf("%d", temp->data);
        temp = temp -> next;
    }

    printf("-> NULL\n");


}
int main(){
    struct node *head = NULL;
    int choice;
    printf("Insertion in linked list ->");
    
    while(1 != 0){
        printf("\nEnter what you want to do -> \n");
        printf("1> To insert at end \n");
        printf("2> To Display \n");

        scanf("%d",&choice);
        switch(choice){
            case 1:
                int val;
                printf("Insert your value - ");
                scanf("%d",&val);
                insertAtEND(&head, val);
                break;
            case 2:
                printf("List - \n");
                printList(head);
            default:
                exit(0);
        }
    }
    return 0;
}
