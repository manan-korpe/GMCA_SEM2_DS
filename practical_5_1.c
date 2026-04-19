#include<stdio.h>
#include<stdlib.h>

#define MAX 100

struct Queue{
    int arr[MAX];
    int size;
    int front;
    int rear;
};

void init(struct Queue *q){
    q->front = q->rear = -1;
}

int isEmpty(struct Queue *q){
    return q->front == -1;
}

int isFull(struct Queue *q){
    return (q->rear + 1) % q->size == q->front;
}

void enqueue(struct Queue *q){
    if(isFull(q)){
        printf("Queue Overflow\n");
        return;
    }

    int value;
    printf("Enter value: ");
    scanf("%d", &value);

    if(isEmpty(q)){
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % q->size;
    }

    q->arr[q->rear] = value;
}

int dequeue(struct Queue *q){
    if(isEmpty(q)){
        printf("Queue Underflow\n");
        return -1;
    }

    int val = q->arr[q->front];

    if(q->front == q->rear){
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % q->size;
    }

    return val;
}

void display(struct Queue *q){
    if(isEmpty(q)){
        printf("Queue is Empty\n");
        return;
    }

    printf("Queue: ");
    int i = q->front;

    while(1){
        printf("%d | ", q->arr[i]);
        if(i == q->rear) break;
        i = (i + 1) % q->size;
    }
    printf("\n");
}

void save(struct Queue *q){
    FILE *fp = fopen("circular_queue.txt", "w");

    if(fp == NULL){
        printf("Error opening file\n");
        return;
    }

    if(!isEmpty(q)){
        int i = q->front;
        while(1){
            fprintf(fp, "%d ", q->arr[i]);
            if(i == q->rear) break;
            i = (i + 1) % q->size;
        }
    }

    fclose(fp);
    printf("Queue saved to file successfully\n");
}

int main(){
    struct Queue q;

    printf("Enter size of queue (max %d): ", MAX);
    scanf("%d", &q.size);

    if(q.size <= 0 || q.size > MAX){
        printf("Invalid size\n");
        return 0;
    }

    init(&q);

    int ch, val;

    while(1){
        printf("\n1.Enqueue 2.Dequeue 3.Display 4.isEmpty 5.isFull 6.Save 7.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch(ch){
            case 1: enqueue(&q); break;

            case 2:
                val = dequeue(&q);
                if(val != -1)
                    printf("Removed: %d\n", val);
                break;

            case 3: display(&q); break;

            case 4:
                if(isEmpty(&q)) printf("Queue is Empty\n");
                else printf("Queue is not Empty\n");
                break;

            case 5:
                if(isFull(&q)) printf("Queue is Full\n");
                else printf("Queue is not Full\n");
                break;

            case 6: save(&q); break;

            case 7: exit(0);

            default: printf("Invalid choice\n");
        }
    }
}
