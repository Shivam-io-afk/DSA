#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}



void insertAtbeg(struct node** head, int data) {
    struct node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}



void printList(struct node* head) {
    struct node* temp = head;
    while (temp != NULL) { 
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}


int main() {
    struct node* head = NULL;
    int choice;
    printf("Insertion in linked list ->");
    
    while(1 != 0){
        printf("\nEnter what you want to do -> \n");
        printf("1> To insert \n");
        printf("2> To Display \n");
        printf("3> To Exit \n");

        scanf("%d",&choice);
        switch(choice){
            case 1:
                int val;
                printf("Insert your value - ");
                scanf("%d",&val);
                insertAtbeg(&head, val);
                break;
            case 2:
                printf("List - \n");
                printList(head);
                break;
            case 3:
                exit(0);
            default:
                exit(0);
        }
    }


    return 0;
}
