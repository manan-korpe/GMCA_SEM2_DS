// Create a Structure with following Data Members:  
// 1. Integer Array  
// 2. Size of the Array  
// Sort the Array using various Sorting algorithms such as 
// (i) Selection Sort (ii) Bubble Sort (iii) Two-way Merge Sort  And store the sorted Array in a text file. 

#include <stdio.h>
#define MAX 10

typedef struct{
    int arr[MAX];
    int size;
}Array;

void selection(Array *a){
    for(int i=0; i<a->size-1; i++){
        int min = i;
        for(int j=i+1; j<a->size; j++){

            if(a->arr[min] > a->arr[j])
                min = j;
        }

        int temp = a->arr[i];
        a->arr[i] = a->arr[min];
        a->arr[min] = temp;
    }
}

void bubble(Array *a){
    for(int i=0;i<a->size-1; i++){
        int swap = 0;
        for(int j=0;j<a->size-i-1;j++){
            if(a->arr[j] > a->arr[j+1]){
                int temp = a->arr[j];
                a->arr[j] = a->arr[j+1];
                a->arr[j+1] = temp;
                swap =1;
            }
        }
        if(swap == 0) break;
    }
}


void main(){
    Array a;
    printf("Enter size of array:");
    scanf("%d",&a.size);

    printf("Enter Array Elements:\n");
    for(int i = 0; i < a.size; i++) {
        scanf("%d", &a.arr[i]);
    }
}