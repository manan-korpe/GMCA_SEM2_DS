#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Stack {
    int arr[MAX];
    int top;
};

void init(struct Stack *s) {
    s->top = -1;
}

int isEmpty(struct Stack *s) {
    return (s->top == -1);
}

int isFull(struct Stack *s) {
    return (s->top == MAX - 1);
}

void push(struct Stack *s) {
    int value;

    printf("Enter value : ");
    scanf("%d",&value);  

    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->arr[++(s->top)] = value;
}

int pop(struct Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->arr[(s->top)--];
}

int peep(struct Stack *s) {
    int pos;

    printf("Enter Position : ");
    scanf("%d",&pos);

    if (s->top - pos + 1 < 0) {
        printf("Invalid Position\n");
        return -1;
    }
    return s->arr[s->top - pos + 1];
}

int save(struct Stack *s) {
    FILE *fp = fopen("stack_output.txt", "w");
    
    if (fp == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    while (!isEmpty(s)) {
        fprintf(fp, "%d ", pop(s));
    }

    fprintf(fp, "\n");
    fclose(fp);

    return 0;
}

int main() {
    struct Stack s;
    init(&s);

    int ch, x;
    while(1){
        printf("\n1:push\t2:pop\t3:peep\t4:isEmpty\t5:isFull\t6:exit\nEnter Choice : ");
        scanf("%d",&ch);
        switch(ch){
            case 1:push(&s);
            break;
            
            case 2:printf("poped Element is %d",pop(&s));
            break;

            case 3:printf("peeked Element is %d",peep(&s));
            break;

            case 4:if(isEmpty(&s)) printf("Stack is Empty");
                else printf("Stack is not Empty");
            break;

            case 5:if(isFull(&s)) printf("Stack is Full");
                else printf("Stack is not Full");
            break;

            case 6:save(&s);
            printf("Exiting....");
            exit(0);

            default:printf("Enter Valid Choice");
            break;
        }
    }

    return 0;
}