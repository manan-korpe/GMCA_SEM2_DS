#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
    struct node *prev;
} node;

node *head1 = NULL;
node *head2 = NULL;

node* createNode(int data) {
    node *newnode = (node*)malloc(sizeof(node));
    newnode->data = data;
    newnode->next = newnode->prev = NULL;
    return newnode;
}

void insertFirst(node **head, int data) {
    node *newnode = createNode(data);
    if (*head == NULL) {
        *head = newnode;
        newnode->next = newnode->prev = newnode;
        return;
    }
    node *last = (*head)->prev;
    newnode->next = *head;
    newnode->prev = last;
    last->next = newnode;
    (*head)->prev = newnode;
    *head = newnode;
}

void insertLast(node **head, int data) {
    node *newnode = createNode(data);
    if (*head == NULL) {
        *head = newnode;
        newnode->next = newnode->prev = newnode;
        return;
    }
    node *last = (*head)->prev;
    newnode->next = *head;
    newnode->prev = last;
    last->next = newnode;
    (*head)->prev = newnode;
}

int count(node *head) {
    if (head == NULL) return 0;
    int c = 0;
    node *temp = head;
    do {
        c++;
        temp = temp->next;
    } while (temp != head);
    return c;
}

void traverse(node *head) {
    if (head == NULL) return;
    node *temp = head;
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);
    printf("\n");
}

void deleteFirst(node **head) {
    if (*head == NULL) return;
    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
        return;
    }
    node *last = (*head)->prev;
    node *temp = *head;
    *head = (*head)->next;
    last->next = *head;
    (*head)->prev = last;
    free(temp);
}

void deleteLast(node **head) {
    if (*head == NULL) return;
    if ((*head)->next == *head) {
        free(*head);
        *head = NULL;
        return;
    }
    node *last = (*head)->prev;
    node *secondLast = last->prev;
    secondLast->next = *head;
    (*head)->prev = secondLast;
    free(last);
}

void deleteBefore(node **head, int key) {
    if (*head == NULL || (*head)->next == *head) return;

    node *temp = *head;
    do {
        if (temp->data == key) {
            node *del = temp->prev;

            if (del == temp) return;

            if (del == *head) {
                deleteFirst(head);
                return;
            }

            node *p = del->prev;
            p->next = temp;
            temp->prev = p;
            free(del);
            return;
        }
        temp = temp->next;
    } while (temp != *head);
}

void insertBefore(node **head, int key, int data) {
    if (*head == NULL) return;

    node *temp = *head;
    do {
        if (temp->data == key) {
            node *newnode = createNode(data);
            node *p = temp->prev;

            newnode->next = temp;
            newnode->prev = p;
            p->next = newnode;
            temp->prev = newnode;

            if (temp == *head)
                *head = newnode;

            return;
        }
        temp = temp->next;
    } while (temp != *head);
}

void insertAtPos(node **head, int pos, int data) {
    if (pos <= 1 || *head == NULL) {
        insertFirst(head, data);
        return;
    }

    int c = 1;
    node *temp = *head;

    do {
        if (c == pos - 1) {
            node *newnode = createNode(data);
            node *nxt = temp->next;

            newnode->next = nxt;
            newnode->prev = temp;
            temp->next = newnode;
            nxt->prev = newnode;
            return;
        }
        temp = temp->next;
        c++;
    } while (temp != *head);

    insertLast(head, data);
}

node* copyList(node *head) {
    node *newh = NULL;
    if (head == NULL) return NULL;

    node *temp = head;
    do {
        insertLast(&newh, temp->data);
        temp = temp->next;
    } while (temp != head);

    return newh;
}

node* mergeList(node *h1, node *h2) {
    node *res = NULL;
    node *t;

    if (h1) {
        t = h1;
        do {
            insertLast(&res, t->data);
            t = t->next;
        } while (t != h1);
    }

    if (h2) {
        t = h2;
        do {
            insertLast(&res, t->data);
            t = t->next;
        } while (t != h2);
    }

    return res;
}

void reverse(node **head) {
    if (*head == NULL) return;

    node *curr = *head;
    node *temp = NULL;

    do {
        temp = curr->next;
        curr->next = curr->prev;
        curr->prev = temp;
        curr = temp;
    } while (curr != *head);

    *head = (*head)->next;
}

node* search(node *head, int key) {
    if (head == NULL) return NULL;

    node *temp = head;
    do {
        if (temp->data == key)
            return temp;
        temp = temp->next;
    } while (temp != head);

    return NULL;
}

void sort(node *head) {
    if (head == NULL) return;

    node *i, *j;
    int t;

    i = head;
    do {
        j = i->next;
        while (j != head) {
            if (i->data > j->data) {
                t = i->data;
                i->data = j->data;
                j->data = t;
            }
            j = j->next;
        }
        i = i->next;
    } while (i->next != head);
}

void saveToFile(node *head) {
    FILE *fp = fopen("list.txt", "w");
    if (!fp) return;

    if (head != NULL) {
        node *temp = head;
        do {
            fprintf(fp, "%d ", temp->data);
            temp = temp->next;
        } while (temp != head);
    }

    fclose(fp);
}

int main() {
    int ch, data, pos, key;
    node *temp;

    while (1) {
        printf("\n1.Insert First\t2.Insert Last\t3.Insert At Pos\t4.Insert Before\t5.Delete First\t6.Delete Last\t7.Delete Before\t8.Traverse\n9.Count\t10.Copy\t11.Merge\t12.Reverse\t13.Search\t14.Sort\t15.Save\t16.Exit\n");
        scanf("%d", &ch);

        switch (ch) {
            case 1: scanf("%d", &data); 
            insertFirst(&head1, data); 
            break;
            case 2: scanf("%d", &data); 
            insertLast(&head1, data); 
            break;
            case 3: scanf("%d %d", &pos, &data); 
            insertAtPos(&head1, pos, data); 
            break;
            case 4: scanf("%d %d", &key, &data); 
            insertBefore(&head1, key, data); 
            break;
            case 5: 
            deleteFirst(&head1); 
            break;
            case 6: 
            deleteLast(&head1); 
            break;
            case 7: scanf("%d", &key); 
            deleteBefore(&head1, key); 
            break;
            case 8: traverse(head1); 
            break;
            case 9: printf("%d\n", count(head1)); 
            break;
            case 10: head2 = copyList(head1); 
            break;
            case 11: temp = mergeList(head1, head2); 
            traverse(temp); 
            break;
            case 12: reverse(&head1); 
            break;
            case 13:
                scanf("%d", &key);
                temp = search(head1, key);
                if (temp) printf("Found\n");
                else printf("Not Found\n");
                break;
            case 14: sort(head1); 
            break;
            case 15: saveToFile(head1); 
            break;
            case 16: exit(0);
            break;
            default:
            printf("Entervalid choice");
        }
    }

    return 0;
}


ENROLLMENT NO: 255690694020		NAME: Korpe Manan K.