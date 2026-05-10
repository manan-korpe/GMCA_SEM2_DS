#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};
struct Node *head = NULL;

void createList(int n){
    int x;
    for(int i = 0; i < n; i++){
        printf("Enter value: ");
        scanf("%d", &x);

        struct Node *newNode = malloc(sizeof(struct Node));
        newNode->data = x;
        newNode->next = NULL;
        if(head == NULL){
            head = newNode;
        } else {
            struct Node *temp = head;
            while(temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
        }
    }
}
void display(struct Node *h){
    while(h != NULL){
        printf("%d -> ", h->data);
        h = h->next;
    }
    printf("NULL\n");
}
void deleteFirst(){
    if(head == NULL) return;
    struct Node *temp = head;
    head = head->next;
    free(temp);
}
void deleteLast(){
    if(head == NULL) return;
    if(head->next == NULL){
        free(head);
        head = NULL;
        return;
    }
    struct Node *temp = head;
    while(temp->next->next != NULL)
        temp = temp->next;

    free(temp->next);
    temp->next = NULL;
}
void deleteBefore(int key){
    if(head == NULL || head->next == NULL) return;

    if(head->next->data == key){
        deleteFirst();
        return;
    }
    struct Node *prev = NULL, *curr = head, *next = head->next;
    while(next != NULL && next->data != key){
        prev = curr;
        curr = next;
        next = next->next;
    }
    if(next == NULL || prev == NULL){
        printf("Not possible\n");
        return;
    }
    prev->next = next;
    free(curr);
}
void insertFirst(int x){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = head;
    head = newNode;
}
void insertLast(int x){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = NULL;
    if(head == NULL){
        head = newNode;
        return;
    }
    struct Node *temp = head;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}
void insertBefore(int key, int x){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = x;
    if(head == NULL) return;
    if(head->data == key){
        newNode->next = head;
        head = newNode;
        return;
    }
    struct Node *temp = head;
    while(temp->next != NULL && temp->next->data != key)
        temp = temp->next;
    if(temp->next == NULL){
        printf("Key not found\n");
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}
void insertAtPos(int pos, int x){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = x;
    if(pos == 1){
        newNode->next = head;
        head = newNode;
        return;
    }
    struct Node *temp = head;
    for(int i = 1; i < pos-1 && temp != NULL; i++)
        temp = temp->next;
    if(temp == NULL){
        printf("Invalid position\n");
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}
int count(){
    int c = 0;
    struct Node *temp = head;
    while(temp){
        c++;
        temp = temp->next;
    }
    return c;
}
struct Node* copyList(){
    struct Node *newHead = NULL, *tail = NULL, *temp = head;
    while(temp){
        struct Node *n = malloc(sizeof(struct Node));
        n->data = temp->data;
        n->next = NULL;
        if(newHead == NULL)
            newHead = tail = n;
        else{
            tail->next = n;
            tail = n;
        }
        temp = temp->next;
    }
    return newHead;
}
struct Node* merge(struct Node *l1, struct Node *l2){
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;
    struct Node *temp = l1;
    while(temp->next != NULL)
        temp = temp->next;
    temp->next = l2;
    return l1;
}
void reverse(){
    struct Node *prev = NULL, *curr = head, *next;
    while(curr){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}
void search(int key){
    struct Node *temp = head;
    int pos = 1;
    while(temp){
        if(temp->data == key){
            printf("Found at position %d\n", pos);
            return;
        }
        temp = temp->next;
        pos++;
    }
    printf("Not found\n");
}
void sort(){
    struct Node *i, *j;
    for(i = head; i != NULL; i = i->next){
        for(j = i->next; j != NULL; j = j->next){
            if(i->data > j->data){
                int t = i->data;
                i->data = j->data;
                j->data = t;
            }
        }
    }
}
void save(){
    FILE *fp = fopen("list.txt", "w");
    struct Node *temp = head;
    while(temp){
        fprintf(fp, "%d ", temp->data);
        temp = temp->next;
    }
    fclose(fp);
    printf("Saved to file\n");
}

int main(){
    int ch, x, n, pos, key;
    struct Node *copy = NULL;
    struct Node *head2 = NULL;
    while(1){
        printf("\n--- LINKED LIST MENU ---\n");
        printf("1.Create List\t2.Display\t3.Delete First\t4.Delete Last\t");
        printf("5.Delete Before Value\t6.Insert First\t7.Insert Last\t");
        printf("8.Insert Before Value\n9.Insert at Position\t10.Count\t");
        printf("11.Copy List\t12.Merge Another List\t13.Reverse\t");
        printf("14.Search\t15.Sort\t16.Save to File\t17.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        switch(ch){
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
                printf("Enter value: ");
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
                printf("Enter key and value: ");
                scanf("%d%d", &key, &x);
                insertBefore(key, x);
                break;
            case 9:
                printf("Enter position and value: ");
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
                printf("Enter number of nodes for second list: ");
                scanf("%d", &n);
                head2 = NULL;
                for(int i = 0; i < n; i++){
                    printf("Enter value: ");
                    scanf("%d", &x);
                    struct Node *newNode = malloc(sizeof(struct Node));
                    newNode->data = x;
                    newNode->next = NULL;
                    if(head2 == NULL){
                        head2 = newNode;
                    } else {
                        struct Node *temp = head2;
                        while(temp->next != NULL)
                            temp = temp->next;
                        temp->next = newNode;
                    }
                }
                head = merge(head, head2);
                printf("Merged List: ");
                display(head);
                break;
            case 13:
                reverse();
                printf("Reversed List: ");
                display(head);
                break;
            case 14:
                printf("Enter value to search: ");
                scanf("%d", &key);
                search(key);
                break;
            case 15:
                sort();
                printf("Sorted List: ");
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
    return 0;
}