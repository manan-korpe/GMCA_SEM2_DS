// Write a program to convert an infix arithmetic expression (parenthesize / unparenthesized) into postfix notation.
// Write a program to evaluate a postfix expression.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char Stack_Operator[MAX];
float  Stack_Value[MAX];

int top_operator = -1, top_value = -1;

void pushOperator(char c) {
    if (top_operator == MAX - 1) {
        printf("Operator Stack Overflow\n");
        exit(1);
    }
    Stack_Operator[++top_operator] = c;
}

char popOperator() {
    if (top_operator == -1) {
        printf("Operator Stack Underflow\n");
        exit(1);
    }
    return Stack_Operator[top_operator--];
}

char peekOperator() {
    return Stack_Operator[top_operator];
}

void pushValue(float v) {
    if (top_value == MAX - 1) {
        printf("Value Stack Overflow\n");
        exit(1);
    }
    Stack_Value[++top_value] = v;
}

float popValue() {
    if (top_value == -1) {
        printf("Value Stack Underflow\n");
        exit(1);
    }
    return Stack_Value[top_value--];
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

void infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;
    char ch;

    top_operator = -1; // reset

    for (i = 0; infix[i] != '\0'; i++) {
        ch = infix[i];

        if (ch >= '0' && ch <= '9') {
            postfix[j++] = ch;
        }
        else if (ch == '(') {
            pushOperator(ch);
        }
        else if (ch == ')') {
            while (top_operator != -1 && peekOperator() != '(') {
                postfix[j++] = popOperator();
            }
            popOperator(); // remove '('
        }
        else {
            while (top_operator != -1 && precedence(peekOperator()) >= precedence(ch)) {
                postfix[j++] = popOperator();
            }
            pushOperator(ch);
        }
    }

    while (top_operator != -1) {
        postfix[j++] = popOperator();
    }

    postfix[j] = '\0';
}

float evaluatePostfix(char postfix[]) {
    int i;
    char ch;

    top_value = -1; // reset

    for (i = 0; postfix[i] != '\0'; i++) {
        ch = postfix[i];

        if (ch >= '0' && ch <= '9') {
            pushValue((float)ch - '0');
        }
        else {
            float b = popValue();
            float a = popValue();

            switch (ch) {
                case '+': pushValue(a + b); break;
                case '-': pushValue(a - b); break;
                case '*': pushValue(a * b); break;
                case '/':
                    if (b == 0) {
                        printf("Division by zero error\n");
                        exit(1);
                    }
                    pushValue(a / b);
                    break;
            }
        }
    }

    return popValue();
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    float result = evaluatePostfix(postfix);

    printf("Evaluation result: %f\n", result);

    return 0;
}