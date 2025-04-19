#include<stdio.h>
#include<stdlib.h>

int main(void) {
    int n, k; scanf("%d%d", &n, &k);
    int *arr = (int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++) scanf("%d", &arr[i]);

    int left=0, right=n-1;
    while(left<right) {
        int mid = (left+right)/2;
        if(arr[mid]>=k) right=mid;
        else left=mid+1;
    }
    if(arr[left]<k) left=n;
    printf(" %d", left);
}