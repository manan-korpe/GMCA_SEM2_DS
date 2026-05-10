#include <Stdio.h>
#define SIZE 10

typedef struct{
    int data[SIZE];
    int front;
    int rare;
}Stack;

void push(Stack *s){
    if(s->rare >= SIZE){
        printf("Stack overflow");
        return;
    }
    int value =0;
    printf("Enter value:");
    scanf("%d",&value);

    s->data[++s->rare] = value;
}

int pop(Stack *s){
    if(s->rare == -1){
        printf("Stack Underflow");
    }

    return s->data[s->rare--];
}

int peek(Stack *s){
    if(s->rare == -1){
        printf("Stack Underflow");
        return -1;
    }
    int value=-1;
    printf("Enter peek numebr");
    scanf("%d",&value);

    int temp = s->rare - value+1 ;
    // printf("value: %d ( %d %d)",s->rare, value+1,temp);
    return s->data[temp];
}


void main(){
    Stack s;
    s.rare = s.front = -1; 
    push(&s);
    push(&s);
    printf("%d \n",peek(&s));
    printf("%d \n",peek(&s));
}