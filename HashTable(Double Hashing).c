#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int h(int x, int M) {
    return x % M;
}

int hPrime(int x, int q) {
    return q - (x % q);
}

void insert(int *arr, int val, int M, int q) {
    int idx = h(val, M);
    int dx = hPrime(val, q);

    for(int i=0;i<M;i++) {
        if(arr[(idx+i*dx)%M]==0) {
            arr[(idx+i*dx)%M]=val;
            for(int j=0;j<i;j++) printf("C");
            printf("%d\n", (idx+i*dx)%M);
            return;
        }
    }
    printf("-1\n");
}

void select(int *arr, int val, int M, int q) {
    int idx = h(val, M);
    int dx = hPrime(val, q);

    for(int i=0;i<M;i++) {
        if(arr[(idx+i*dx)%M]==val) {
            printf("%d %d\n", (idx+i*dx)%M, arr[(idx+i*dx)%M]);
            return;
        }
    }
    printf("-1\n");
}

void print(int *arr, int M) {
    for(int i=0;i<M;i++) printf(" %d", arr[i]);
    printf("\n");
}

int main() {
    int M, n, q; scanf("%d %d %d%*c", &M, &n, &q);
    int *arr = (int*)malloc(sizeof(int)*M);
    for(int i=0;i<M;i++) arr[i]=0;

    while(1) {
        char ch; scanf("%c%*c", &ch);
        if(ch=='e') {
            print(arr, M);
            break;
        } else if(ch=='p') {
            print(arr, M);
        } else {
            int val; scanf("%d%*c", &val);
            if(ch=='i') {
                insert(arr, val, M, q);
            } else {
                select(arr, val, M, q);
            }
        }
    }
    free(arr);
}

/*
Input
13 10 11
i 25
i 13
i 16
i 15
i 70
p
i 28
i 31
i 20
i 14
s 20
s 27
i 38
e

Output
12
0
3
2
5
 13 0 15 16 0 70 0 0 0 0 0 0 25
C7
CC9
CC11
1
11 20
-1
CCC4
 13 14 15 16 38 70 0 28 0 31 0 20 25
*/