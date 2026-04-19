#include<stdio.h>
#include<stdlib.h>

struct Node{
    int coeff;
    int exp;
    struct Node *next;
};

struct Node* create(){
    struct Node *head = NULL, *temp = NULL, *newNode;
    int n;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        newNode = (struct Node*)malloc(sizeof(struct Node));

        printf("Enter coefficient and exponent: ");
        scanf("%d %d", &newNode->coeff, &newNode->exp);
        newNode->next = NULL;

        if(head == NULL){
            head = temp = newNode;
        } else {
            temp->next = newNode;
            temp = newNode;
        }
    }
    return head;
}

void display(struct Node *head){
    if(head == NULL){
        printf("Polynomial is empty\n");
        return;
    }

    while(head != NULL){
        printf("%dx^%d", head->coeff, head->exp);
        head = head->next;
        if(head != NULL) printf(" + ");
    }
    printf("\n");
}

struct Node* add(struct Node *p1, struct Node *p2){
    struct Node *result = NULL, *tail = NULL;

    while(p1 != NULL && p2 != NULL){
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->next = NULL;

        if(p1->exp == p2->exp){
            newNode->coeff = p1->coeff + p2->coeff;
            newNode->exp = p1->exp;
            p1 = p1->next;
            p2 = p2->next;
        }
        else if(p1->exp > p2->exp){
            newNode->coeff = p1->coeff;
            newNode->exp = p1->exp;
            p1 = p1->next;
        }
        else{
            newNode->coeff = p2->coeff;
            newNode->exp = p2->exp;
            p2 = p2->next;
        }

        if(result == NULL){
            result = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    while(p1 != NULL){
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->coeff = p1->coeff;
        newNode->exp = p1->exp;
        newNode->next = NULL;

        if(result == NULL){
            result = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        p1 = p1->next;
    }

    while(p2 != NULL){
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->coeff = p2->coeff;
        newNode->exp = p2->exp;
        newNode->next = NULL;

        if(result == NULL){
            result = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        p2 = p2->next;
    }

    return result;
}

struct Node* insertSorted(struct Node *head, int coeff, int exp){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;

    if(head == NULL || exp > head->exp){
        newNode->next = head;
        return newNode;
    }

    struct Node *temp = head;

    while(temp->next != NULL && temp->next->exp > exp){
        temp = temp->next;
    }

    if(temp->next != NULL && temp->next->exp == exp){
        temp->next->coeff += coeff;
        free(newNode);
    } else {
        newNode->next = temp->next;
        temp->next = newNode;
    }

    return head;
}

struct Node* multiply(struct Node *p1, struct Node *p2){
    struct Node *result = NULL;

    for(struct Node *i = p1; i != NULL; i = i->next){
        for(struct Node *j = p2; j != NULL; j = j->next){
            int coeff = i->coeff * j->coeff;
            int exp = i->exp + j->exp;

            result = insertSorted(result, coeff, exp);
        }
    }

    return result;
}

void save(struct Node *head){
    FILE *fp = fopen("polynomial.txt", "w");

    if(fp == NULL){
        printf("Error opening file\n");
        return;
    }

    while(head != NULL){
        fprintf(fp, "%dx^%d ", head->coeff, head->exp);
        head = head->next;
    }

    fclose(fp);
    printf("Saved to file successfully\n");
}

int main(){
    struct Node *p1, *p2, *sum, *prod;

    printf("Create Polynomial 1:\n");
    p1 = create();

    printf("Create Polynomial 2:\n");
    p2 = create();

    printf("\nPolynomial 1: ");
    display(p1);

    printf("Polynomial 2: ");
    display(p2);

    sum = add(p1, p2);
    printf("Addition: ");
    display(sum);

    prod = multiply(p1, p2);
    printf("Multiplication: ");
    display(prod);

    save(sum);  

    return 0;
}
