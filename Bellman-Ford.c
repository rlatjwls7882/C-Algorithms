#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INF 0x3f3f3f3f

typedef struct node {
    int nodeNum, minCost;
} node;

typedef struct edge {
    node *a, *b;
    int cost;
} edge;

int min(int a, int b) {
    return a<b?a:b;
}

void BellmanFord(node *n, edge *e, int N, int M, int S) {
    n[S-1].minCost=0;
    for(int i=0;i<N;i++) {
        int change=0;
        for(int j=0;j<M;j++) {
            if(e[j].a->minCost!=INF) {
                if(e[j].b->minCost > e[j].a->minCost+e[j].cost) {
                    e[j].b->minCost = e[j].a->minCost+e[j].cost;
                    change=1;
                }
            }
        }

        if(!change) break;
        else if(i==N-1) {
            printf("cycle!");
            return;
        }
    }
    for(int i=0;i<N;i++) if(i!=S-1 && n[i].minCost!=INF) printf("%d %d\n", i+1, n[i].minCost);
}

int main() {
    int N, M, S; scanf("%d%d%d", &N, &M, &S);
    node *n = (node*)malloc(sizeof(node)*N);
    edge *e = (edge*)malloc(sizeof(edge)*M);

    for(int i=0;i<N;i++) {
        n[i].nodeNum = i;
        n[i].minCost = INF;
    }

    for(int i=0;i<M;i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        e[i].a = &n[a-1];
        e[i].b = &n[b-1];
        e[i].cost = c;
    }
    BellmanFord(n, e, N, M, S);

    free(n);
    free(e);
}

/*
Input1
5 7 1
1 2 1
1 4 5
5 1 -2
3 5 3
3 4 1
1 3 2
3 2 -3

Output1
2 –1
3 2
4 3
5 5

Input2
4 5 1
1 2 1
2 3 -2
3 1 2
3 4 1
1 4 5

Output2
2 1
3 –1
4 0
*/