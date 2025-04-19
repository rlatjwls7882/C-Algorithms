#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct list {
    struct list *next;
    struct edge *e;
} list;

typedef struct node {
    int nodeNum;
    struct node *parent;
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

void freeList(list* l) {
    if(l->next) freeList(l->next);
    free(l);
}

/* DSU */
node* find(node *n) {
    if(n == n->parent) return n;
    return n->parent = find(n->parent);
}

int merge(node *x, node *y) {
    x = find(x);
    y = find(y);

    if(x==y) return 0;
    if(x->nodeNum > y->nodeNum) x->parent = y;
    else y->parent = x;
    return 1;
}
/* DSU */

/* PriorityQueue */
typedef struct priority_queue {
    edge *arr;
    int size;
} priority_queue;

void swap(edge *a, edge *b) {
    edge tmp = *a;
    *a = *b;
    *b = tmp;
}

void push(priority_queue *pq, edge *e) {
    pq->size++;
    pq->arr[pq->size] = *e;

    int idx = pq->size;
    while(idx>1) {
        if(pq->arr[idx].cost < pq->arr[idx/2].cost) {
            swap(&pq->arr[idx], &pq->arr[idx/2]);
            idx/=2;
        } else {
            break;
        }
    }
}

edge top(priority_queue *pq) {
    edge a = pq->arr[1];
    pq->arr[1] = pq->arr[pq->size--];
    int idx=1;
    while(idx<=pq->size) {
        if(idx*2+1<=pq->size && pq->arr[idx].cost > pq->arr[idx*2+1].cost && pq->arr[idx*2+1].cost < pq->arr[idx*2].cost) {
            swap(&pq->arr[idx], &pq->arr[idx*2+1]);
            idx = idx*2+1;
        } else if(idx*2<=pq->size && pq->arr[idx].cost > pq->arr[idx*2].cost) {
            swap(&pq->arr[idx], &pq->arr[idx*2]);
            idx = idx*2;
        } else {
            break;
        }
    }
    return a;
}
/* PriorityQueue */

void Kruskal(node *n, edge *e, int N, int M) {
    priority_queue *pq = (priority_queue*)malloc(sizeof(priority_queue));
    pq->arr = (edge*)malloc(sizeof(edge)*M);
    pq->size=0;
    for(int i=0;i<M;i++) push(pq, &e[i]);

    int totalCost=0;
    while(pq->size) {
        edge cur = top(pq);
        if(merge(cur.a, cur.b)) {
            printf(" %d", cur.cost);
            totalCost += cur.cost;
        }
    }
    printf("\n%d", totalCost);
    free(pq->arr);
    free(pq);
}

int main() {
    int N, M; scanf("%d %d", &N, &M);
    node *n = (node*)malloc(sizeof(node)*N);
    edge *e = (edge*)malloc(sizeof(edge)*M);

    for(int i=0;i<N;i++) {
        n[i].l = (list*)malloc(sizeof(list));
        n[i].l->next = NULL;
        n[i].nodeNum = i;
        n[i].parent = &n[i];
    }

    for(int i=0;i<M;i++) {
        int a, b, c; scanf("%d %d %d", &a, &b, &c);
        e[i].a = &n[a-1];
        e[i].b = &n[b-1];
        e[i].cost = c;
        insert(e[i].a, &e[i]);
        insert(e[i].b, &e[i]);
    }
    Kruskal(n, e, N, M);

    // free
    for(int i=0;i<N;i++) freeList(n[i].l);
    free(n);
    free(e);
}
/*
Input1
6 9
1 2 3
1 3 20
2 4 25
2 5 17
3 4 34
3 5 1
3 6 12
4 5 5
5 6 37

Output1
 1 3 5 12 17
38

Input2
5 7
1 2 75
1 4 95
1 3 51
2 4 9
4 3 19
4 5 42
3 5 31

Output2
 9 19 31 51
110
*/