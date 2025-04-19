#include<stdio.h>
#include<stdlib.h>

int findPivot(int l, int r) {
    return rand()%(r-l+1)+l;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int inPlacePartition(int *arr, int l, int r, int k) {
    swap(&arr[k], &arr[r]);
    int i=l, j=r-1, pivot=arr[r];
    while(i<=j) {
        while(i<=j && arr[i]<=pivot) {
            i++;
        }
        while(i<=j && arr[j]>=pivot) {
            j--;
        }
        if(i<j) swap(&arr[i], &arr[j]);
    }
    swap(&arr[i], &arr[r]);
    return i;
}

void inPlaceQuickSort(int *arr, int l, int r) {
    if(l>=r) return;
    int k = findPivot(l, r);
    int i = inPlacePartition(arr, l, r, k);
    inPlaceQuickSort(arr, l, i-1);
    inPlaceQuickSort(arr, i+1, r);
}

int main() {
    int n; scanf("%d", &n);
    int *arr = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) scanf("%d", &arr[i]);
    inPlaceQuickSort(arr, 0, n-1);
    for(int i=0;i<n;i++) printf(" %d", arr[i]);
}