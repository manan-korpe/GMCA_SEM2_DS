#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

struct Node *head = NULL;

void insertFirst(int x){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = head;
    head = newNode;
}

void insertEnd(int x){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = NULL;

    if(head == NULL){
        head = newNode;
        return;
    }

    struct Node *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
}

void insertSorted(int x){
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = NULL;

    if(head == NULL || x < head->data){
        newNode->next = head;
        head = newNode;
        return;
    }

    struct Node *temp = head;
    while(temp->next != NULL && temp->next->data < x){
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

void display(){
    struct Node *temp = head;

    if(temp == NULL){
        printf("List is empty\n");
        return;
    }

    printf("List: ");
    while(temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void deleteByAddress(struct Node *ptr){
    if(head == NULL || ptr == NULL){
        printf("Invalid operation\n");
        return;
    }

    if(head == ptr){
        head = head->next;
        free(ptr);
        return;
    }

    struct Node *temp = head;
    while(temp->next != NULL && temp->next != ptr){
        temp = temp->next;
    }

    if(temp->next == NULL){
        printf("Address not found\n");
        return;
    }

    temp->next = ptr->next;
    free(ptr);
}

struct Node* getNode(int pos){
    struct Node *temp = head;
    int i = 1;

    while(temp != NULL && i < pos){
        temp = temp->next;
        i++;
    }
    return temp;
}

struct Node* copyList(){
    if(head == NULL) return NULL;

    struct Node *newHead = NULL, *tail = NULL;
    struct Node *temp = head;

    while(temp != NULL){
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = temp->data;
        newNode->next = NULL;

        if(newHead == NULL){
            newHead = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        temp = temp->next;
    }

    return newHead;
}

void save(){
    FILE *fp = fopen("linked_list.txt", "w");

    if(fp == NULL){
        printf("Error opening file\n");
        return;
    }

    struct Node *temp = head;
    while(temp != NULL){
        fprintf(fp, "%d ", temp->data);
        temp = temp->next;
    }

    fclose(fp);
    printf("List saved to file successfully\n");
}

int main(){
    int ch, x, pos;
    struct Node *copy = NULL;

    while(1){
        printf("1.Insert First\t2.Insert End\t3.Insert Sorted\t4.Delete by Position\t5.Display\t6.Copy List\t7.Save\t8.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch(ch){
            case 1:
                printf("Enter value: ");
                scanf("%d", &x);
                insertFirst(x);
                break;

            case 2:
                printf("Enter value: ");
                scanf("%d", &x);
                insertEnd(x);
                break;

            case 3:
                printf("Enter value: ");
                scanf("%d", &x);
                insertSorted(x);
                break;

            case 4:
                printf("Enter position to delete: ");
                scanf("%d", &pos);
                deleteByAddress(getNode(pos));
                break;

            case 5:
                display();
                break;

            case 6:
                copy = copyList();
                printf("Copied List: ");
                while(copy != NULL){
                    printf("%d -> ", copy->data);
                    copy = copy->next;
                }
                printf("NULL\n");
                break;

            case 7:
                save();
                break;

            case 8:
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }
}
