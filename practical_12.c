// Create a Structure with following Data Members:  
// 1. Integer Array  
// 2. Size of the Array  
// Sort the Array using various Sorting algorithms such as 
// (i) Quick Sort (ii) Heap Sort And store the sorted Array in a text file. 

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct{
    int arr[MAX];
    int size;
}Array;

void quickSort(Array *a, int low, int high){

    if(low >= high)
        return;

    int pivot = low;
    int i = low + 1;
    int j = high;

    while(i <= j){

        while(i <= high && a->arr[i] <= a->arr[pivot]) i++;

        while(j > low && a->arr[j] > a->arr[pivot]) j--;

        if(i < j){
            int temp = a->arr[i];
            a->arr[i] = a->arr[j];
            a->arr[j] = temp;
        }
    }

    int temp = a->arr[pivot];
    a->arr[pivot] = a->arr[j];
    a->arr[j] = temp;

    quickSort(a, low, j - 1);
    quickSort(a, j + 1, high);
}

void heapify(Array *a, int n, int i){

    int largest = i;

    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < n && a->arr[left] > a->arr[largest]){
        largest = left;
    }

    if(right < n && a->arr[right] > a->arr[largest]){
        largest = right;
    }

    if(largest != i){

        int temp = a->arr[i];
        a->arr[i] = a->arr[largest];
        a->arr[largest] = temp;

        heapify(a, n, largest);
    }
}

void heapSort(Array *a){

    int n = a->size;

    for(int i = n/2 - 1; i >= 0; i--){
        heapify(a, n, i);
    }

    for(int i = n-1; i > 0; i--){

        int temp = a->arr[0];
        a->arr[0] = a->arr[i];
        a->arr[i] = temp;

        heapify(a, i, 0);
    }
}

void save(Array *a){
    FILE* fp = fopen("practical_12.txt","w");

    if(fp==NULL){
        printf("fp error");
        return;
    }

   for(int i=0; i<a->size; i++){
     fprintf(fp, "%d ", a->arr[i]);
   }
   fclose(fp);
}

void main(){
    Array a;
    printf("Enter size of array:");
    scanf("%d",&a.size);

    printf("Enter Array Elements:\n");
    for(int i = 0; i < a.size; i++) {
        scanf("%d", &a.arr[i]);
    }

    while(1){
    int choice=-1;
    printf("\n1.quick sort \t2.heap sort \t3.save \t4.exit\n");
    printf("Enter your choice : ");
    scanf("%d",&choice);

    switch(choice){
        case 1:quickSort(&a, 0, a.size-1);
        printf("Data sorted successfully");
        break;
        case 2:heapSort(&a);
        printf("Data sorted successfully");
        break;
        case 3:save(&a);
        break;
        case 4:exit(0);
        break;
        default:
        printf("Enter valide choice");
    }
    }
}