#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void selection_sort(int* arr, int n) {
    for(int i=0;i<n-1;i++) {
        int minIdx = i;
        for(int j=i+1;j<n;j++) {
            if(arr[minIdx]>arr[j]) minIdx=j;
        }
        swap(&arr[i], &arr[minIdx]);
    }
}

int* insertion_sort(int* arr, int n) {
    int* sorted = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) {
        int tmp = arr[i];
        int j=i-1;
        while(j>=0 && sorted[j]>tmp) {
            sorted[j+1]=sorted[j];
            j--;
        }
        sorted[j+1]=tmp;
    }
    return sorted;
}

int main() {
    int n; scanf("%d", &n);
    int *arr = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) arr[i] = rand();
    int *arrForSelectionSort = arr;

    clock_t start = clock();
    arr = insertion_sort(arr, n);
    clock_t end = clock();
    printf("Insertion Sort: %ldms\n", end-start);

    start = clock();
    selection_sort(arr, n);
    end = clock();
    printf("Selection Sort: %ldms\n", end-start);
    // for(int i=0;i<n;i++) printf(" %d", arr[i]);
}