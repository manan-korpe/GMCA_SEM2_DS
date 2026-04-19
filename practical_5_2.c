
// Create a “Circular Queue” user-defined structure with the following data members: 1. A Data 2. A link to the next node
// Perform the following operations on Circular queue using userdefined functions: 1. Insert an element 
// 2. Remove an element 3. Display 4. Isfull 5. Isempty Create a file which stores all values of list

#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

struct Node *front = NULL;
struct Node *rear = NULL;

int isEmpty(){
    return front == NULL;
}

int isFull(){
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    if(temp == NULL) return 1;
    free(temp);
    return 0;
}

void enqueue(){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));

    if(newNode == NULL){
        printf("Queue is Full (Memory not available)\n");
        return;
    }

    printf("Enter value: ");
    scanf("%d", &newNode->data);

    if(front == NULL){
        front = rear = newNode;
        rear->next = front; 
    } else {
        rear->next = newNode;
        rear = newNode;
        rear->next = front;   
    }
}

// Dequeue
int dequeue(){
    if(isEmpty()){
        printf("Queue is Empty\n");
        return -1;
    }

    int val;
    struct Node *temp = front;

    if(front == rear){
        val = front->data;
        front = rear = NULL;
    } else {
        val = front->data;
        front = front->next;
        rear->next = front;   
    }

    free(temp);
    return val;
}

void display(){
    if(isEmpty()){
        printf("Queue is Empty\n");
        return;
    }

    struct Node *temp = front;
    printf("Queue: ");

    do{
        printf("%d -> ", temp->data);
        temp = temp->next;
    }while(temp != front);

    printf("(back to front)\n");
}

void save(){
    FILE *fp = fopen("circular_linked_queue.txt", "w");

    if(fp == NULL){
        printf("Error opening file\n");
        return;
    }

    if(!isEmpty()){
        struct Node *temp = front;
        do{
            fprintf(fp, "%d ", temp->data);
            temp = temp->next;
        }while(temp != front);
    }

    fclose(fp);
    printf("Queue saved to file successfully\n");
}

int main(){
    int ch, val;

    while(1){
        printf("\n1.Enqueue 2.Dequeue 3.Display 4.isEmpty 5.isFull 6.Save 7.Exit\n");
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
