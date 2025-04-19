#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* DAG */
typedef struct list {
    struct list *next;
    struct edge *e;
} list;

typedef struct node {
    int inDegree, visited;
    char nodeNum;
    list *l;
} node;

typedef struct edge {
    node *a, *b;
} edge;

void insert(node *n, edge *e) {
    list *l = (list*)malloc(sizeof(list));
    l->next = n->l->next;
    l->e = e;
    n->l->next = l;
}

void freeList(list *cur) {
    if(cur->next) freeList(cur->next);
    free(cur);
}
/* DAG */

/* Queue */
typedef struct queueList {
    struct queueList *prev, *next;
    node *n;
} queueList;

typedef struct queue {
    queueList *front, *back;
} queue;

void insertQ(queue *q, node *n) {
    queueList *l = (queueList*)malloc(sizeof(queueList));
    l->prev = q->back;
    l->next=NULL;
    l->n = n;
    if(q->back) q->back->next = l;
    q->back = l;
    if(!q->front) q->front = l;
}

node* frontQ(queue *q) {
    node *tmp = q->front->n;
    q->front = q->front->next;
    if(q->front) free(q->front->prev);
    return tmp;
}
/* Queue */

void topologicalSort(node *n, int N) {
    queue *q = (queue*)malloc(sizeof(queue));
    q->back=q->front=NULL;

    for(int i=0;i<N;i++) if(n[i].inDegree==0) insertQ(q, &n[i]);

    char order[N]; int idx=0;
    while(q->front) {
        node *cur = frontQ(q);
        order[idx++] = cur->nodeNum;

        list *l = cur->l;
        while(l->next) {
            l = l->next;
            if(--l->e->b->inDegree==0) insertQ(q, l->e->b);
        }
    }

    if(idx==N) {
        for(int i=0;i<N;i++) printf("%c ", order[i]);
    } else {
        printf("0");
    }
    free(q);
}

int main() {
    int N; scanf("%d%*c", &N);
    node *n = (node*)malloc(sizeof(node)*N);
    int charToNodeNum[128] = {0, };
    for(int i=0;i<N;i++) {
        n[i].inDegree=n[i].visited=0;
        scanf("%c%*c", &n[i].nodeNum);
        n[i].l = (list*)malloc(sizeof(list));
        n[i].l->next = NULL;
        charToNodeNum[n[i].nodeNum]=i;
    }

    int M; scanf("%d%*c", &M);
    edge *e = (edge*)malloc(sizeof(edge)*M);
    for(int i=0;i<M;i++) {
        char u, v; scanf("%c %c%*c", &u, &v);
        e[i].a = &n[charToNodeNum[u]];
        e[i].b = &n[charToNodeNum[v]];
        e[i].b->inDegree++;
        insert(e[i].a, &e[i]);
    }
    topologicalSort(n, N);
    for(int i=0;i<N;i++) freeList(n[i].l);
    free(n);
    free(e);
}
/*
Input1
3
A B C
3
A B
C A
C B

Output1
C A B

Input2
4
A B C D
6
A B
C A
C B
A D
B D
D C

Output2
0
*/