#include<stdio.h>
#include<stdlib.h>

int find(int *arr, int left, int right, int k) {
    int mid = (left+right+1)/2;
    if(left==right) {
        if(arr[left]<=k) return left;
        else return -1;
    }
    if(arr[mid]<=k) return find(arr, mid, right, k);
    return find(arr, left, mid-1, k);
}

int main(void) {
    int n, k; scanf("%d%d", &n, &k);
    int *arr = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) scanf("%d", &arr[i]);
    printf(" %d", find(arr, 0, n-1, k));
}