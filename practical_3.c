// Create a “Queue” structure with following Data members: 1. Integer Array 2. Size of the Array  
// Perform the following operations on Simple queue using user-defined functions: 1. Insert an element 
// 2. Remove an element 3. Display 4. Isfull 5. Isempty Create a file which stores all  values of Array.

#include<stdio.h>
#include<stdlib.h>

#define MAX 100

struct Queue{
    int arr[MAX];
    int size;
    int rear;
    int front;
};

void init(struct Queue *q){
    q->front = q->rear = -1;
}

void enqueue(struct Queue *q){
    if(q->rear >= q->size - 1){
        printf("Queue overflow");
        return;
    }

    int value;
    printf("Enter value ");
    scanf("%d",&value);

    if(q->front == -1) q->front = 0;
    
    q->arr[++q->rear] = value;
}

int dequeue(struct Queue *q){
    if(q->front == -1 || q->front > q->rear){
        printf("Queue underflow");
        return -1;
    }

    return q->arr[q->front++];

}

int isEmpty(struct Queue *q){
    return q->front == -1 || q->front > q->rear;
}

int isFull(struct Queue *q){
    return q->rear == q->size - 1;
}

int save(struct Queue *q) {
    FILE *fp = fopen("queue_output.txt", "w");
    
    if (fp == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    for(int i = q->front; i <= q->rear; i++){
        fprintf(fp, "%d ", q->arr[i]);
    }


    fprintf(fp, "\n");
    fclose(fp);
    printf("Queue Saved in File successfuly.");
    return 0;
}


void display(struct Queue *q){
    if(isEmpty(q)){
        printf("Queue is empty");
        return;
    }

    printf("Queue is : ");
    for(int i = q->front; i<=q->rear;i++){
        printf("%d | ",q->arr[i]);
    }
}

int main(){
    struct Queue q;

    printf("Enter size of queue (max %d): ", MAX);
    scanf("%d", &q.size);

    if(q.size <= 0 || q.size > MAX){
        printf("Invalid size!\n");
        return 0;
    }

    init(&q);

    int ch, x;
    while(1){
        printf("\n1:enqueue\t2:dequeue\t3:display\t4:isEmpty\t5:isFull\t6:save\t7:exit\nEnter Choice : ");
        scanf("%d",&ch);
        switch(ch){
            case 1:enqueue(&q);
            break;
            
            case 2:int val = dequeue(&q);
            if(val != -1)   printf("Removed Element is %d", val);
            break;

            case 3:display(&q);
            break;

            case 4:if(isEmpty(&q)) printf("Queue is Empty");
                else printf("Queue is not Empty");
            break;

            case 5:if(isFull(&q)) printf("Queue is Full");
                else printf("Queue is not Full");
            break;

            case 6:save(&q);
            break;

            case 7:
            printf("Exiting....");
            exit(0);

            default:printf("Enter Valid Choice");
            break;
        }
    }

    return 0;
}