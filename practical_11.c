// Create a Structure with following Data Members:  
// 1. Integer Array  
// 2. Size of the Array  
// Sort the Array using various Sorting algorithms such as 
// (i) Selection Sort (ii) Bubble Sort (iii) Two-way Merge Sort  And store the sorted Array in a text file. 

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

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
    printf("Data sorted successfully");
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
    printf("Data sorted successfully");
}

void save(Array *a){
    FILE* fp = fopen("pratical_11.txt","w");
    
    if(fp == NULL){
        printf("file error");
        return;
    }

    for(int i=0; i<a->size; i++){
        fprintf(fp, "%d ", a->arr[i]);
    }

    fclose(fp);
    printf("sorted data saved in file pratical_11 ");
}

void merge(Array *a, int low, int mid, int high){
    int temp[MAX];

    int lb = low;
    int mb = mid+1;
    int k=low;
    while(lb <=mid && mb <=high){
        if(a->arr[lb] <= a->arr[mb]){
            temp[k] = a->arr[lb++]; 
        }else{
            temp[k] = a->arr[mb++]; 
        }
        k++;
    }

    while(lb <=mid){
        temp[k] = a->arr[lb++]; 
        k++;
    }

    while(mb <=high){
        temp[k] = a->arr[mb++]; 
        k++;
    }

    for(int i=low; i<=high; i++){
        a->arr[i] = temp[i];
    }
}

void mergeSort(Array *a,int low,int high){
    if(low >= high) return;

    int mid = (low+high)/2;
    mergeSort(a, low,mid);
    mergeSort(a,mid+1, high);
    merge(a, low, mid, high);
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
    printf("\n1.Selection sort \t2.Bubble sort \t3.Two-way Merge Sort \t4.save data \t5.exit\n");
    printf("Enter your choice : ");
    scanf("%d",&choice);

    switch(choice){
        case 1:selection(&a);
        break;
        case 2:bubble(&a);
        break;
        case 3:
        mergeSort(&a, 0, a.size-1);
        printf("Data sorted successfully");
        break;
        case 4:save(&a);
        break;
        case 5:exit(0);
        break;
        default:
        printf("Enter valide choice");
    }
    }
}