#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct list {
    struct list *next;
    struct edge *e;
} list;

typedef struct node {
    int nodeNum, visited;
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

/* PriorityQueue */
typedef struct pqNode {
    node *n;
    int cost;
} pqNode;

typedef struct priority_queue {
    pqNode *arr;
    int size;
} priority_queue;

void swap(pqNode *a, pqNode *b) {
    pqNode tmp = *a;
    *a = *b;
    *b = tmp;
}

node* getAnotherNode(node *n, edge *e) {
    if(n == e->a) return e->b;
    return e->a;
}

void push(priority_queue *pq, edge *e, node *n) {
    pq->size++;
    pq->arr[pq->size].n = getAnotherNode(n, e);
    pq->arr[pq->size].cost = e->cost;

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

pqNode top(priority_queue *pq) {
    pqNode a = pq->arr[1];
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

void Prim_Jarnik(node *n, edge *e, int N, int M) {
    priority_queue *pq = (priority_queue*)malloc(sizeof(priority_queue));
    pq->arr = (pqNode*)malloc(sizeof(pqNode)*1001);
    pq->size=0;

    printf(" 1");
    n[0].visited=1;
    list *l = n[0].l;
    while(l->next) {
        l = l->next;
        push(pq, l->e, &n[0]);
    }

    int totalCost=0;
    while(pq->size) {
        pqNode cur = top(pq);
        if(cur.n->visited) continue;
        printf(" %d", cur.n->nodeNum);
        cur.n->visited = 1;
        totalCost += cur.cost;

        l = cur.n->l;
        while(l->next) {
            l = l->next;
            push(pq, l->e, cur.n);
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
        n[i].nodeNum = i+1;
        n[i].visited = 0;
    }

    for(int i=0;i<M;i++) {
        int a, b, c; scanf("%d %d %d", &a, &b, &c);
        e[i].a = &n[a-1];
        e[i].b = &n[b-1];
        e[i].cost = c;
        insert(e[i].a, &e[i]);
        insert(e[i].b, &e[i]);
    }
    Prim_Jarnik(n, e, N, M);

    // free
    for(int i=0;i<N;i++) freeList(n[i].l);
    free(n);
    free(e);
}
/*
Input
5 7
1 2 1
1 4 2
1 5 4
2 5 7
4 5 3
3 5 5
2 3 6

Output
 1 2 4 5 3
11
*/