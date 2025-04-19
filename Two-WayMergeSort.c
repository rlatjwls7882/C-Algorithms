#include<stdio.h>
#include<memory.h>
#include<stdlib.h>

int min(int a, int b) { return a<b?a:b; }

void merge(int* arr, int start, int mid, int end) {
    int *tmp = (int*)malloc(sizeof(int)*(end-start+1));
    int idx=0;
    int l=start, r=mid;
    while(l<mid && r<=end) {
        if(arr[l]<arr[r]) tmp[idx++]=arr[l++];
        else tmp[idx++]=arr[r++];
    }
    while(l<mid) tmp[idx++]=arr[l++];
    while(r<=end) tmp[idx++]=arr[r++];

    idx=0;
    while(start<=end) arr[start++]=tmp[idx++];
    free(tmp);
}

int main(void) {
    int n; scanf("%d", &n);
    int *arr = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) scanf("%d", &arr[i]);

    for(int i=2;;i*=2) {
        for(int j=0;j<n;j+=i) merge(arr, j, min(j+i/2, n-1), min(j+i, n)-1);
        for(int i=0;i<n;i++) printf(" %d", arr[i]); printf("\n");
        if(i>=n) break;
    }
    free(arr);
}