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
} edge;

int getAnotherNodeNum(int nodeNum, edge *e) {
    if(e->a->nodeNum==nodeNum) return e->b->nodeNum;
    return e->a->nodeNum;
}

node* getAnotherNode(int nodeNum, edge *e) {
    if(e->a->nodeNum==nodeNum) return e->b;
    return e->a;
}

void insert(node *n, edge *e) {
    list *l = (list*)malloc(sizeof(list));
    int to = getAnotherNodeNum(n->nodeNum, e);
    l->next=NULL;
    l->e=e;

    list *cur = n->l;
    while(cur->next!=NULL) {
        int nextNodeNum = getAnotherNodeNum(n->nodeNum, cur->next->e);
        if(to<nextNodeNum) break;
        cur = cur->next;
    }
    l->next = cur->next;
    cur->next = l;
}

void dfs(node *cur) {
    list *l = cur->l;
    cur->visited=1;
    printf("%d\n", cur->nodeNum);
    while(l->next) {
        node *next = getAnotherNode(cur->nodeNum, l->next->e);
        if(!next->visited) dfs(next);
        l = l->next;
    }
}

void freeList(list *l) {
    if(l->next) freeList(l->next);
    free(l);
}

int main() {
    int N, M, S; scanf("%d%d%d", &N, &M, &S);
    node *n = (node*)malloc(sizeof(node)*N);
    edge *e = (edge*)malloc(sizeof(edge)*M);

    for(int i=0;i<N;i++) {
        n[i].nodeNum=i+1;
        n[i].visited=0;
        n[i].l = (list*)malloc(sizeof(list));
        n[i].l->next=NULL;
    }

    for(int i=0;i<M;i++) {
        int u, v; scanf("%d%d", &u, &v);
        e[i].a = &n[u-1];
        e[i].b = &n[v-1];
        insert(e[i].a, &e[i]);
        insert(e[i].b, &e[i]);
    }

    dfs(&n[S-1]);
    for(int i=0;i<N;i++) freeList(n[i].l);
    free(n);
    free(e);
}

/*
Input1
5 7 1
1 2
1 4
5 1
3 5
4 3
3 1
2 3

Output1
1
2
3
4
5

Input2
8 12 7
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
7
2
1
3
6
4
5
8
*/
