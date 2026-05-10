#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
    int data;
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree* createNode(int data) {
    Tree* newNode = (Tree*)malloc(sizeof(Tree));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Tree* insert(Tree* root, int data) {

    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    }
    else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

void preorder(Tree* root) {

    if (root == NULL)
        return;

    printf("%d ", root->data);

    preorder(root->left);
    preorder(root->right);
}

void inorder(Tree* root) {

    if (root == NULL)
        return;

    inorder(root->left);

    printf("%d ", root->data);

    inorder(root->right);
}

void postorder(Tree* root) {

    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);

    printf("%d ", root->data);
}

Tree* search(Tree* root, int key) {

    if (root == NULL || root->data == key)
        return root;

    if (key < root->data)
        return search(root->left, key);

    return search(root->right, key);
}

Tree* findMin(Tree* root) {

    while (root->left != NULL) {
        root = root->left;
    }

    return root;
}

Tree* deleteNode(Tree* root, int key) {

    if (root == NULL)
        return root;

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    }

    else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    }

    else {

        if (root->left == NULL) {
            Tree* temp = root->right;
            free(root);
            return temp;
        }

        else if (root->right == NULL) {
            Tree* temp = root->left;
            free(root);
            return temp;
        }

        Tree* temp = findMin(root->right);

        root->data = temp->data;

        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

void saveInorderToFile(Tree* root, FILE* fp) {

    if (root == NULL)
        return;

    saveInorderToFile(root->left, fp);

    fprintf(fp, "%d ", root->data);

    saveInorderToFile(root->right, fp);
}

int main() {

    Tree* root = NULL;

    int choice, data;

    while (1) {

        printf("\n------ Binary Search Tree ------");
        printf("\n1. Create/Insert");
        printf("\n2. Preorder");
        printf("\n3. Inorder");
        printf("\n4. Postorder");
        printf("\n5. Search");
        printf("\n6. Delete");
        printf("\n7. Save Traversal to File");
        printf("\n8. Exit");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter data: ");
                scanf("%d", &data);

                root = insert(root, data);
                break;

            case 2:
                printf("Preorder: ");
                preorder(root);
                break;

            case 3:
                printf("Inorder: ");
                inorder(root);
                break;

            case 4:
                printf("Postorder: ");
                postorder(root);
                break;

            case 5:
                printf("Enter value to search: ");
                scanf("%d", &data);

                if (search(root, data))
                    printf("Element found");
                else
                    printf("Element not found");

                break;

            case 6:
                printf("Enter value to delete: ");
                scanf("%d", &data);

                root = deleteNode(root, data);

                printf("Node deleted");
                break;

            case 7: {
                FILE* fp = fopen("bst_traversal.txt", "w");

                if (fp == NULL) {
                    printf("File error");
                    break;
                }

                saveInorderToFile(root, fp);

                fclose(fp);

                printf("Traversal saved to bst_traversal.txt");
                break;
            }

            case 8:
                exit(0);

            default:
                printf("Invalid choice");
        }

        printf("\n");
    }

    return 0;
}