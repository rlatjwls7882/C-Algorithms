#include<stdio.h>
#include<stdlib.h>

int arr[101], size;

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void upHeap(int i, int curSize) {
    while(1) {
        if(i*2+1<=curSize && arr[i*2]<arr[i*2+1] && arr[i*2+1]>arr[i]) {
            swap(&arr[i], &arr[i*2+1]);
            i = i*2+1;
        } else if(i*2<=curSize && arr[i*2]>arr[i]) {
            swap(&arr[i], &arr[i*2]);
            i = i*2;
        } else {
            break;
        }
    }
}

void buildHeap(int curSize) {
    for(int i=curSize/2;i>=1;i--) {
        upHeap(i, curSize);
    }
}

void inPlaceHeapSort() {
    for(int curSize=size;curSize>1;curSize--) {
        buildHeap(curSize);
        swap(&arr[1], &arr[curSize]);
    }
}

void printArray() {
    for(int i=1;i<=size;i++) printf(" %d", arr[i]);
    printf("\n");
}

int main() {
    scanf("%d", &size);
    for(int i=1;i<=size;i++) scanf("%d", &arr[i]);
    inPlaceHeapSort();
    printArray();
}