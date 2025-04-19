#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int h(int x, int M) {
    return x%M;
}

void insert(int *arr, int val, int M) {
    int idx = h(val, M);

    for(int i=0;i<M;i++) {
        if(arr[(idx+i)%M]==0) {
            arr[(idx+i)%M]=val;
            for(int j=0;j<i;j++) printf("C");
            printf("%d\n", (idx+i)%M);
            return;
        }
    }
    printf("-1\n");
}

void select(int *arr, int val, int M) {
    int idx = h(val, M);

    for(int i=0;i<M;i++) {
        if(arr[(idx+i)%M]==val) {
            printf("%d %d\n", (idx+i)%M, arr[(idx+i)%M]);
            return;
        }
    }
    printf("-1\n");
}

int main() {
    int M, n; scanf("%d %d%*c", &M, &n);
    int *arr = (int*)malloc(sizeof(int)*M);
    for(int i=0;i<M;i++) arr[i]=0;

    while(1) {
        char ch; scanf("%c", &ch);
        if(ch=='e') {
            break;
        } else {
            int val; scanf("%d%*c", &val);
            if(ch=='i') {
                insert(arr, val, M);
            } else {
                select(arr, val, M);
            }
        }
    }
    free(arr);
}

/*
Input1
7 3
i 17011112
i 17012345
i 17012687
s 17011111
e

Output1
6
0
CC1
-1

Input2
13 10
i 16110243
i 17011111
i 17012331
i 17012354
i 17013672
i 16012342
s 17012354
i 15013986
i 102067
i 113478
i 14012322
s 16110243
e

Output2
6
0
11
8
C1
C9
8 17012354
CC2
4
CC3
12
6 16110243
*/