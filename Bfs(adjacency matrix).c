#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

/* Graph */
typedef struct node {
    int nodeNum, visited;
} node;

typedef struct edge {
    node *a, *b;
} edge;
/* Graph */

/* Queue */
typedef struct list {
    struct list *prev, *next;
    struct node *n;
} list;

typedef struct queue {
    list *front, *back;
} queue;

void push(queue *q, node *n) {
    list *l = (list*)malloc(sizeof(list));
    l->n = n;
    l->next = NULL;
    l->prev = q->back;
    if(q->back) q->back->next = l;
    q->back = l;
    if(!q->front) q->front = l;
}

node* front(queue *q) {
    node* tmp = q->front->n;
    q->front = q->front->next;
    if(q->front && q->front->prev) free(q->front->prev);
    return tmp;
}
/* Queue */

int main() {
    int N, M, S; scanf("%d%d%d", &N, &M, &S);
    node *n = (node*)malloc(sizeof(node)*N);
    edge *e = (edge*)malloc(sizeof(edge)*M);
    int matrix[N][N];
    memset(matrix, -1, sizeof(matrix));

    for(int i=0;i<N;i++) {
        n[i].nodeNum = i;
        n[i].visited=0;
    }

    for(int i=0;i<M;i++) {
        int a, b; scanf("%d%d", &a, &b);
        e[i].a = &n[a-1];
        e[i].b = &n[b-1];
        matrix[a-1][b-1]=i;
        matrix[b-1][a-1]=i;
    }

    queue *q = (queue*)malloc(sizeof(queue));
    q->front = q->back = NULL;
    push(q, &n[S-1]);
    while(q->front) {
        node *cur = front(q);
        if(cur->visited) continue;
        cur->visited=1;
        printf("%d\n", cur->nodeNum+1);

        for(int i=0;i<N;i++) if(matrix[cur->nodeNum][i]!=-1) push(q, &n[i]);
    }

    free(q);
    free(n);
    free(e);
}

/*
Input1
6 9 1
3 5
1 3
4 1
2 3
3 4
6 4
3 6
1 2
2 5

Output1
1
2
3
4
5
6

Input2
8 12 4
1 2
2 4
4 7
3 6
6 1
7 6
7 8
1 3
2 7
1 4
2 5
7 5

Output2
4
1
2
7
3
6
5
8
*/