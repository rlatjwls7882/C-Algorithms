#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#define INF 0x3f3f3f3f

/* Graph */
typedef struct list { // 간선리스트를 담을 구조체
    struct list *next;
    struct edge *e;
} list;

typedef struct node { // 정점을 담을 구조체
    list *l;
    int nodeNum, totalCost, visited;
} node;

typedef struct edge { // 간선은 담을 구조체
    node *a, *b;
    int cost;
} edge;

void insertNode(node *n, edge *e) { // 해당 정점의 간선리스트에 새 간선 추가
    list *newList = (list*)malloc(sizeof(list));
    newList->next=NULL;
    newList->e=e;

    list *cur = n->l;
    while(cur->next) cur = cur->next;
    cur->next = newList;
}

void freeList(list *l) { // 간선리스트 메모리 할당 해제
    if(l->next) freeList(l->next);
    free(l);
}
/* Graph */

/* TopologicalSort */
typedef struct TopologicalOrder { // 위상 순서를 담을 구조체
    node *n;
} TopologicalOrder;

void dfs(node *n, int *maxNum, TopologicalOrder *t) { // dfs를 이용한 TopologicalSort
    n->visited=1;
    list *cur = n->l;
    while(cur->next) {
        cur = cur->next;
        if(!cur->e->b->visited) dfs(cur->e->b, maxNum, t);
    }
    t[(*maxNum)--].n = n;
}

void TopologicalSort(node *n, int N, TopologicalOrder *t) { // 모든 정점 위상순서 마킹
    int maxNum=N-1;
    for(int i=0;i<N;i++) {
        if(!n[i].visited) dfs(&n[i], &maxNum, t);
    }
}
/* TopologicalSort */

/* FindShortestPath */
int min(int a, int b) { // 작은 값 리턴
    return a<b?a:b;
}

void FindShortestPath(TopologicalOrder *t, int N) {
    for(int i=0;i<N;i++) {
        if(t[i].n->totalCost!=INF) { // 시작지점에서 방문이 가능한 정점인 경우
            list *l = t[i].n->l;
            while(l->next) {
                l = l->next;
                l->e->b->totalCost = min(l->e->b->totalCost, l->e->a->totalCost + l->e->cost); // 위상순서로 i+1번인 정점을 통해 갈 수 있는 최단거리 계산
            }
        }
    }
}
/* FindShortestPath */

int main(void) {
    int N, M, S; scanf("%d%d%d", &N, &M, &S); // 정점의 개수 N, 간선의 개수 M, 출발정점 S
    node *n = (node*)malloc(sizeof(node)*N); // 정점 정보
    edge *e = (edge*)malloc(sizeof(edge)*M); // 간선 정보
    TopologicalOrder *t = (TopologicalOrder*)malloc(sizeof(TopologicalOrder)*N); // 위상순서 정보

    // 정점의 초기 정보
    for(int i=0;i<N;i++) {
        n[i].totalCost=INF;
        n[i].nodeNum=i;
        n[i].visited=0;
        n[i].l = (list*)malloc(sizeof(list));
        n[i].l->next = NULL;
    }
    n[S-1].totalCost=0;

    // 간선 정보 입력
    for(int i=0;i<M;i++) {
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        e[i].a = &n[u-1];
        e[i].b = &n[v-1];
        e[i].cost = w;
        insertNode(e[i].a, &e[i]);
    }

    // 위상정렬
    TopologicalSort(n, N, t);

    // 최단거리 계산
    FindShortestPath(t, N);

    // 방문가능한 정점의 최단거리 출력
    for(int i=0;i<N;i++) {
        if(i+1!=S && n[i].totalCost!=INF) printf("%d %d\n", i+1, n[i].totalCost);
    }

    // free
    for(int i=0;i<N;i++) freeList(n[i].l);
    free(n);
    free(e);
    free(t);
}

/*
Input1
5 7 1
1 2 1
1 4 2
5 1 -2
5 4 1
4 3 -1
1 3 5
3 2 -3

Output1
2 -2
3 1
4 2

Input2
6 6 4
6 1 1
4 6 1
2 4 -1
6 3 1
2 5 4
4 1 8

Output2
1 2
3 2
6 1

*/