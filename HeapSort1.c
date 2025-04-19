#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void upHeap(int *arr, int i) {
    while(i>1 && arr[i]>arr[i/2]) {
        swap(&arr[i], &arr[i/2]);
        i/=2;
    }
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

void insertItem(int *arr, int *size, int val) {
    arr[++*size] = val;
    upHeap(arr, *size);
    printf("0\n");
}

void deleteMax(int *arr, int *size) {
    printf("%d\n", arr[1]);
    arr[1]=arr[(*size)--];
    downHeap(arr, 1, *size);
}

void print(int *arr, int size) {
    for(int i=1;i<=size;i++) printf(" %d", arr[i]);
    printf("\n");
}

int main(void) {
    int *arr = (int*)malloc(sizeof(int)*100);
    int size=0;

    while(1) {
        char ch; scanf("%c%*c", &ch);
        if(ch=='i') {
            int val; scanf("%d%*c", &val);
            insertItem(arr, &size, val);
        } else if(ch=='d') {
            deleteMax(arr, &size);
        } else if(ch=='p') {
            print(arr, size);
        } else {
            break;
        }
    }
}