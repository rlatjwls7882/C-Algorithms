#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define INF 0x3f3f3f3f

/* Graph */
typedef struct list {
    struct list *next;
    struct edge *e;
} list;

typedef struct node {
    int nodeNum, minCost;
    list *l;
} node;

typedef struct edge {
    node *a, *b;
    int cost;
} edge;

void insert(node *n, edge *e) {
    list *l = (list*)malloc(sizeof(list));
    l->next = n->l->next;
    l->e = e;
    n->l->next = l;
}

node* getAnotherNode(node *n, edge *e) {
    if(e->a==n) return e->b;
    return e->a;
}

void freeList(list *l) {
    if(l->next) freeList(l->next);
    free(l);
}
/* Graph */

/* PriorityQueue */
typedef struct priority_queue {
    node *heap;
    int size;
} priority_queue;

void swap(node *a, node *b) {
    node tmp = *a;
    *a = *b;
    *b = tmp;
}

void push(priority_queue *pq, node *n, int cost) {
    pq->size++;
    pq->heap[pq->size]=*n;
    pq->heap[pq->size].minCost = cost;
    int idx=pq->size;
    while(idx>1) {
        if(pq->heap[idx].minCost < pq->heap[idx/2].minCost) {
            swap(&pq->heap[idx], &pq->heap[idx/2]);
            idx/=2;
        } else {
            break;
        }
    }
}

node top(priority_queue *pq) {
    node tmp = pq->heap[1];
    swap(&pq->heap[1], &pq->heap[pq->size]);
    pq->size--;
    int idx=1;
    while(idx<=pq->size) {
        if(idx*2+1<=pq->size && pq->heap[idx].minCost > pq->heap[idx*2+1].minCost && pq->heap[idx*2+1].minCost < pq->heap[idx*2].minCost) {
            swap(&pq->heap[idx], &pq->heap[idx*2+1]);
            idx = idx*2+1;
        } else if(idx*2<=pq->size && pq->heap[idx].minCost > pq->heap[idx*2].minCost) {
            swap(&pq->heap[idx], &pq->heap[idx*2]);
            idx = idx*2;
        } else {
            break;
        }
    }
    return tmp;
}
/* PriorityQueue */

void Dijkstra(node *n, edge *e, int N, int M, int S) {
    priority_queue *pq = (priority_queue*)malloc(sizeof(priority_queue));
    pq->heap = (node*)malloc(sizeof(node)*10000);
    pq->size=0;
    push(pq, &n[S-1], 0);

    while(pq->size) {
        node cur = top(pq);
        if(n[cur.nodeNum].minCost<=cur.minCost) continue;
        n[cur.nodeNum].minCost = cur.minCost;
        list *l = cur.l;
        while(l->next) {
            l = l->next;
            node *next = getAnotherNode(&n[cur.nodeNum], l->e);
            push(pq, next, cur.minCost+l->e->cost);
        }
    }
    for(int i=0;i<N;i++) if(n[i].minCost!=0 && n[i].minCost!=INF) printf("%d %d\n", n[i].nodeNum+1, n[i].minCost);
    free(pq->heap);
    free(pq);
}

int main() {
    int N, M, S; scanf("%d%d%d", &N, &M, &S);
    node *n = (node*)malloc(sizeof(node)*N);
    edge *e = (edge*)malloc(sizeof(edge)*M);

    for(int i=0;i<N;i++) {
        n[i].nodeNum = i;
        n[i].minCost = INF;
        n[i].l = (list*)malloc(sizeof(list));
        n[i].l->next = NULL;
    }

    for(int i=0;i<M;i++) {
        int a, b, c; scanf("%d%d%d", &a, &b, &c);
        e[i].a = &n[a-1];
        e[i].b = &n[b-1];
        e[i].cost = c;
        insert(e[i].a, &e[i]);
        insert(e[i].b, &e[i]);
    }
    Dijkstra(n, e, N, M, S);

    // free
    for(int i=0;i<N;i++) freeList(n[i].l);
    free(n);
    free(e);
}

/*
Input1
5 7 1
1 2 1
1 4 5
5 1 10
3 5 3
4 3 1
3 1 2
2 3 2

Output1
2 1
3 2
4 3
5 5

Input2
8 12 7
1 2 1
2 4 2
4 7 7
3 6 1
6 1 4
7 6 9
7 8 1
1 3 2
2 7 5
1 4 1
2 5 2
7 5 2

Output2
1 5
2 4
3 7
4 6
5 2
6 8
8 1

Input3
5 3 2
1 2 1
1 3 1
1 4 1

Output3
1 1
3 2
4 2
*/