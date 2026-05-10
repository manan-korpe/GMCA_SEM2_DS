#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ===== Node Structure ===== */
struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

struct Node *head = NULL;

/* ===== Create Node ===== */
struct Node* createNode(int data) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

/* ===== 1. Create List ===== */
void createList(int n) {
    for (int i = 0; i < n; i++) {
        int val;
        printf("Enter value: ");
        scanf("%d", &val);

        struct Node *newNode = createNode(val);

        if (head == NULL) {
            head = newNode;
        } else {
            struct Node *temp = head;
            while (temp->next != NULL)
                temp = temp->next;

            temp->next = newNode;
            newNode->prev = temp;
        }
    }
}

/* ===== 2. Traverse ===== */
void traverse() {
    struct Node *temp = head;
    printf("List: ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

/* ===== 3. Delete First ===== */
void deleteFirst() {
    if (head == NULL) return;

    struct Node *temp = head;
    head = head->next;

    if (head != NULL)
        head->prev = NULL;

    free(temp);
}

/* ===== 4. Delete Last ===== */
void deleteLast() {
    if (head == NULL) return;

    struct Node *temp = head;

    while (temp->next != NULL)
        temp = temp->next;

    if (temp->prev != NULL)
        temp->prev->next = NULL;
    else
        head = NULL;

    free(temp);
}

/* ===== 5. Delete Before Given Data ===== */
void deleteBefore(int key) {
    struct Node *temp = head;

    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp == NULL || temp->prev == NULL) return;

    struct Node *del = temp->prev;

    if (del->prev != NULL)
        del->prev->next = temp;
    else
        head = temp;

    temp->prev = del->prev;
    free(del);
}

/* ===== 6. Insert First ===== */
void insertFirst(int val) {
    struct Node *newNode = createNode(val);

    if (head != NULL) {
        newNode->next = head;
        head->prev = newNode;
    }

    head = newNode;
}

/* ===== 7. Insert Last ===== */
void insertLast(int val) {
    struct Node *newNode = createNode(val);

    if (head == NULL) {
        head = newNode;
        return;
    }

    struct Node *temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
}

/* ===== 8. Insert Before Data ===== */
void insertBefore(int key, int val) {
    struct Node *temp = head;

    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp == NULL) return;

    struct Node *newNode = createNode(val);

    newNode->next = temp;
    newNode->prev = temp->prev;

    if (temp->prev != NULL)
        temp->prev->next = newNode;
    else
        head = newNode;

    temp->prev = newNode;
}

/* ===== 9. Insert at Position ===== */
void insertAtPosition(int pos, int val) {
    if (pos == 1) {
        insertFirst(val);
        return;
    }

    struct Node *temp = head;

    for (int i = 1; i < pos - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp == NULL) return;

    struct Node *newNode = createNode(val);

    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL)
        temp->next->prev = newNode;

    temp->next = newNode;
}

/* ===== 10. Count Nodes ===== */
int count() {
    int c = 0;
    struct Node *temp = head;

    while (temp != NULL) {
        c++;
        temp = temp->next;
    }

    return c;
}

/* ===== 11. Copy List ===== */
struct Node* copyList() {
    struct Node *newHead = NULL, *tail = NULL;
    struct Node *temp = head;

    while (temp != NULL) {
        struct Node *newNode = createNode(temp->data);

        if (newHead == NULL) {
            newHead = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        temp = temp->next;
    }

    return newHead;
}

/* ===== 12. Merge Lists ===== */
struct Node* merge(struct Node *h1, struct Node *h2) {
    if (h1 == NULL) return h2;
    if (h2 == NULL) return h1;

    struct Node *temp = h1;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = h2;
    h2->prev = temp;

    return h1;
}

/* ===== 13. Reverse ===== */
void reverse() {
    struct Node *temp = NULL;
    struct Node *current = head;

    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp != NULL)
        head = temp->prev;
}

/* ===== 14. Search ===== */
void search(int key) {
    struct Node *temp = head;
    int pos = 1;

    while (temp != NULL) {
        if (temp->data == key) {
            printf("Found at position %d\n", pos);
            return;
        }
        temp = temp->next;
        pos++;
    }

    printf("Not found\n");
}

/* ===== 15. Sort ===== */
void sortList() {
    struct Node *i, *j;
    int temp;

    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

/* ===== File Save ===== */
void saveToFile() {
    FILE *fp = fopen("list.txt", "w");
    struct Node *temp = head;

    while (temp != NULL) {
        fprintf(fp, "%d\n", temp->data);
        temp = temp->next;
    }

    fclose(fp);
    printf("Saved to file.\n");
}

/* ===== File Load ===== */
void loadFromFile() {
    FILE *fp = fopen("list.txt", "r");
    int val;

    if (fp == NULL) return;

    while (fscanf(fp, "%d", &val) != EOF) {
        insertLast(val);
    }

    fclose(fp);
}

/* ===== MAIN MENU ===== */
int main() {
    int choice, val, pos, key, n;

    loadFromFile();

    while (1) {
        printf("\n\n--- DOUBLY LINKED LIST MENU ---\n");
        printf("1.Create List\t2.Display\t3.Delete First\t4.Delete Last\t");
        printf("5.Delete Before Value\t6.Insert First\t7.Insert Last\t");
        printf("8.Insert Before Value\n9.Insert at Position\t10.Count\t");
        printf("11.Copy List\t12.Merge Another List\t13.Reverse\t");
        printf("14.Search\t15.Sort\t16.Save to File\t17.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter number of nodes: ");
            scanf("%d", &n);
            createList(n);
            break;

        case 2:
            traverse();
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
            scanf("%d", &val);
            insertFirst(val);
            break;

        case 7:
            printf("Enter value: ");
            scanf("%d", &val);
            insertLast(val);
            break;

        case 8:
            printf("Enter key & value: ");
            scanf("%d %d", &key, &val);
            insertBefore(key, val);
            break;

        case 9:
            printf("Enter position & value: ");
            scanf("%d %d", &pos, &val);
            insertAtPosition(pos, val);
            break;

        case 10:
            printf("Count = %d\n", count());
            break;

        case 11: {
            struct Node *copy = copyList();
            printf("List copied (not displayed separately here)\n");
            break;
        }

        case 12: {
            struct Node *copy = copyList();
            head = merge(head, copy);
            break;
        }

        case 13:
            reverse();
            break;

        case 14:
            printf("Enter key: ");
            scanf("%d", &key);
            search(key);
            break;

        case 15:
            sortList();
            break;

        case 16:
            saveToFile();
            break;

        case 0:
            saveToFile();
            exit(0);

        default:
            printf("Invalid choice\n");
        }
    }

    return 0;
}