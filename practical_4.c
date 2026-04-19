// Create a “Queue” user-defined structure with the following data members: 1. A Data 2. A link to the next node 
// Perform the following operations on Simple queue using user-defined functions: 1. Insert an element 
// 2. Remove an element 3. Display 4. Isfull 5. Isempty Create a file which stores all values of list. 

#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

struct Node *front = NULL;
struct Node *rear = NULL;

// Insert (Enqueue)
void enqueue(){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    if(newNode == NULL){
        printf("Queue is Full (Memory not available)\n");
        return;
    }

    printf("Enter value: ");
    scanf("%d", &newNode->data);
    newNode->next = NULL;

    if(front == NULL){
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

// Remove (Dequeue)
int dequeue(){
    if(front == NULL){
        printf("Queue is Empty\n");
        return -1;
    }

    struct Node *temp = front;
    int val = temp->data;

    front = front->next;
    if(front == NULL) rear = NULL;

    free(temp);
    return val;
}

// Display
void display(){
    if(front == NULL){
        printf("Queue is Empty\n");
        return;
    }

    struct Node *temp = front;
    printf("Queue: ");
    while(temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// isEmpty
int isEmpty(){
    return front == NULL;
}

// isFull (only when memory fails)
int isFull(){
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    if(temp == NULL) return 1;
    free(temp);
    return 0;
}

// Save to file
void save(){
    FILE *fp = fopen("queue_linked.txt", "w");

    if(fp == NULL){
        printf("Error opening file\n");
        return;
    }

    struct Node *temp = front;
    while(temp != NULL){
        fprintf(fp, "%d ", temp->data);
        temp = temp->next;
    }

    fclose(fp);
    printf("Queue saved to file successfully\n");
}

int main(){
    int ch, val;

    while(1){
        printf("\n1.Enqueue  2.Dequeue  3.Display  4.isEmpty  5.isFull  6.Save  7.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch(ch){
            case 1: enqueue(); break;

            case 2:
                val = dequeue();
                if(val != -1)
                    printf("Removed: %d\n", val);
                break;

            case 3: display(); break;

            case 4:
                if(isEmpty()) printf("Queue is Empty\n");
                else printf("Queue is not Empty\n");
                break;

            case 5:
                if(isFull()) printf("Queue is Full\n");
                else printf("Queue is not Full\n");
                break;

            case 6: save(); break;

            case 7: exit(0);

            default: printf("Invalid choice\n");
        }
    }
}
