#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *head = NULL;
void createList(int n) {
    struct Node *temp, *newNode;
    int x;
    for(int i = 0; i < n; i++) {
        printf("Enter value: ");
        scanf("%d", &x);
        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = x;
        if(head == NULL) {
            head = newNode;
            newNode->next = head;
        } else {
            temp = head;
            while(temp->next != head)
                temp = temp->next;

            temp->next = newNode;
            newNode->next = head;
        }
    }
}
void display(struct Node *h) {
    if(h == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node *temp = h;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while(temp != h);
    printf("(head)\n");
}
void deleteFirst() {
    if(head == NULL) return;
    struct Node *temp = head, *last = head;
    while(last->next != head)
        last = last->next;
    if(head == head->next) {
        head = NULL;
    } else {
        head = head->next;
        last->next = head;
    }
    free(temp);
}
void deleteLast() {
    if(head == NULL) return;
    struct Node *temp = head, *prev = NULL;
    while(temp->next != head) {
        prev = temp;
        temp = temp->next;
    }
    if(prev == NULL) {
        head = NULL;
    } else {
        prev->next = head;
    }
    free(temp);
}
void deleteBefore(int key) {
    if(head == NULL || head->next == head) return;
    struct Node *prev = NULL, *curr = head, *next = head->next;
    do {
        if(next->data == key) {
            if(curr == head) {
                deleteLast();
            } else {
                prev->next = next;
                free(curr);
            }
            return;
        }
        prev = curr;
        curr = next;
        next = next->next;
    } while(curr != head);
}
void insertFirst(int x) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = x;
    if(head == NULL) {
        head = newNode;
        newNode->next = head;
    } else {
        struct Node *temp = head;
        while(temp->next != head)
            temp = temp->next;

        newNode->next = head;
        temp->next = newNode;
        head = newNode;
    }
}
void insertLast(int x) {
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = x;
    if(head == NULL) {
        head = newNode;
        newNode->next = head;
    } else {
        struct Node *temp = head;
        while(temp->next != head)
            temp = temp->next;
        temp->next = newNode;
        newNode->next = head;
    }
}
void insertBefore(int key, int x) {
    if(head == NULL) return;
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = x;
    struct Node *temp = head, *prev = NULL;
    do {
        if(temp->data == key) {
            if(temp == head) {
                insertFirst(x);
                free(newNode);
                return;
            }
            prev->next = newNode;
            newNode->next = temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    } while(temp != head);
}
void insertAtPos(int pos, int x) {
    if(pos == 1) {
        insertFirst(x);
        return;
    }
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = x;
    struct Node *temp = head;
    for(int i = 1; i < pos - 1 && temp->next != head; i++)
        temp = temp->next;
    newNode->next = temp->next;
    temp->next = newNode;
}

/* Count */
int count() {
    if(head == NULL) return 0;
    int c = 0;
    struct Node *temp = head;
    do {
        c++;
        temp = temp->next;
    } while(temp != head);
    return c;
}
struct Node* copyList() {
    if(head == NULL) return NULL;
    struct Node *temp = head;
    struct Node *newHead = NULL, *last = NULL;
    do {
        struct Node *newNode = malloc(sizeof(struct Node));
        newNode->data = temp->data;
        if(newHead == NULL) {
            newHead = last = newNode;
            newNode->next = newHead;
        } else {
            last->next = newNode;
            newNode->next = newHead;
            last = newNode;
        }
        temp = temp->next;
    } while(temp != head);

    return newHead;
}
struct Node* merge(struct Node *h1, struct Node *h2) {
    if(h1 == NULL) return h2;
    if(h2 == NULL) return h1;
    struct Node *temp = h1;
    while(temp->next != h1)
        temp = temp->next;
    temp->next = h2;
    struct Node *t2 = h2;
    while(t2->next != h2)
        t2 = t2->next;
    t2->next = h1;
    return h1;
}
void reverse() {
    if(head == NULL || head->next == head) return;
    struct Node *prev = NULL, *curr = head, *next;
    struct Node *last = head;
    while(last->next != head)
        last = last->next;
    do {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    } while(curr != head);
    head->next = prev;
    head = prev;
    last->next = head;
}
void search(int key) {
    if(head == NULL) return;
    int pos = 1;
    struct Node *temp = head;
    do {
        if(temp->data == key) {
            printf("Found at position %d\n", pos);
            return;
        }
        pos++;
        temp = temp->next;
    } while(temp != head);

    printf("Not found\n");
}
void sort() {
    if(head == NULL) return;
    struct Node *i, *j;
    int temp;
    for(i = head; i->next != head; i = i->next) {
        for(j = i->next; j != head; j = j->next) {
            if(i->data > j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}
void save() {
    FILE *fp = fopen("list.txt", "w");
    if(fp == NULL) return;
    struct Node *temp = head;
    if(temp != NULL) {
        do {
            fprintf(fp, "%d ", temp->data);
            temp = temp->next;
        } while(temp != head);
    }
    fclose(fp);
    printf("Saved to file\n");
}
int main() {
    int ch, x, n, pos, key;
    struct Node *copy = NULL, *head2 = NULL;
    while(1) {
        printf("\n--- CIRCULAR LINKED LIST MENU ---\n");
        printf("1.Create\t2.Display\t3.Delete First\t4.Delete Last\t");
        printf("5.Delete Before\t6.Insert First\t7.Insert Last\t");
        printf("8.Insert Before\t9.Insert at Position\n10.Count\t");
        printf("11.Copy\t12.Merge\t13.Reverse\t14.Search\t");
        printf("15.Sort\t16.Save\t17.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        switch(ch) {
            case 1:
                printf("How many nodes? ");
                scanf("%d", &n);
                createList(n);
                break;
            case 2:
                display(head);
                break;
            case 3:
                deleteFirst();
                break;
            case 4:
                deleteLast();
                break;
            case 5:
                printf("Enter key: ");
                scanf("%d", &key);
                deleteBefore(key);
                break;
            case 6:
                printf("Enter value: ");
                scanf("%d", &x);
                insertFirst(x);
                break;
            case 7:
                printf("Enter value: ");
                scanf("%d", &x);
                insertLast(x);
                break;
            case 8:
                printf("Enter key & value: ");
                scanf("%d%d", &key, &x);
                insertBefore(key, x);
                break;
            case 9:
                printf("Enter position & value: ");
                scanf("%d%d", &pos, &x);
                insertAtPos(pos, x);
                break;
            case 10:
                printf("Count = %d\n", count());
                break;
            case 11:
                copy = copyList();
                printf("Copied List: ");
                display(copy);
                break;
            case 12:
                printf("Enter nodes for second list: ");
                scanf("%d", &n);
                head2 = NULL;
                for(int i = 0; i < n; i++) {
                    printf("Enter value: ");
                    scanf("%d", &x);
                    struct Node *newNode = malloc(sizeof(struct Node));
                    newNode->data = x;
                    if(head2 == NULL) {
                        head2 = newNode;
                        newNode->next = head2;
                    } else {
                        struct Node *temp = head2;
                        while(temp->next != head2)
                            temp = temp->next;
                        temp->next = newNode;
                        newNode->next = head2;
                    }
                }
                head = merge(head, head2);
                display(head);
                break;
            case 13:
                reverse();
                display(head);
                break;
            case 14:
                printf("Enter key: ");
                scanf("%d", &key);
                search(key);
                break;
            case 15:
                sort();
                display(head);
                break;
            case 16:
                save();
                break;
            case 17:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return  0;
}