#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void downHeap(int *arr, int i, int size) {
    while(1) {
        if(i*2+1<=size && arr[i*2+1]>=arr[i*2] && arr[i*2+1]>arr[i]) {
            swap(&arr[i], &arr[i*2+1]);
            i = i*2+1;
        } else if(i*2<=size && arr[i*2]>arr[i]) {
            swap(&arr[i], &arr[i*2]);
            i = i*2;
        } else {
            break;
        }
    }
}

int main(void) {
    int n; scanf("%d", &n);
    int *arr = (int*)malloc(sizeof(int)*(n+1));
    for(int i=1;i<=n;i++) scanf("%d", &arr[i]);
    for(int i=n;i>=1;i--) downHeap(arr, i, n);
    for(int i=1;i<=n;i++) printf(" %d", arr[i]);
}