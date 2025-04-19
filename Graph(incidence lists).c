#include<stdio.h>
#include<stdlib.h>

typedef struct ListNode {
    int conn, dest;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode *head;
} List;

typedef struct Node {
    List *n;
} Node;

typedef struct Edge {
    int a, b, w;
} Edge;

int searchIdx(Edge *edge, int edgeNum, int a, int b) {
    for(int i=0;i<edgeNum;i++) {
        if(edge[i].a==a && edge[i].b==b || edge[i].a==b && edge[i].b==a) {
            return i;
        }
    }
    return -1;
}

void add(List *list, int dest, int idx) {
    ListNode* create = (ListNode*)malloc(sizeof(ListNode));
    create->next=NULL;
    create->conn=idx;
    create->dest=dest;

    if(list->head==NULL) {
        list->head = create;
    } else {
        if(list->head->dest > create->dest) {
            create->next=list->head;
            list->head=create;
        } else {
            ListNode *cur = list->head;
            while(1) {
                if(cur->next==NULL || cur->next->dest>create->dest) break;
                cur = cur->next;
            }
            create->next=cur->next;
            cur->next=create;
        }
    }
}

int main(void) {
    /* 노드 리스트 선언 start */
    Node *node = (Node*)malloc(sizeof(Node)*6);
    for(int i=0;i<6;i++) {
        node[i].n = (List*)malloc(sizeof(List));
        node[i].n->head=NULL;
    }
    /* 노드 리스트 선언 end */

    /* 엣지 선언 start */
    int edgeNum=8;
    Edge *edge = (Edge*)malloc(sizeof(Edge)*21);
    edge[0].a=1; edge[0].b=2; edge[0].w=1; add(node[0].n, 2, 0); add(node[1].n, 1, 0);
    edge[1].a=1; edge[1].b=3; edge[1].w=1; add(node[0].n, 3, 1); add(node[2].n, 1, 1);
    edge[2].a=1; edge[2].b=4; edge[2].w=1; add(node[0].n, 4, 2); add(node[3].n, 1, 2);
    edge[3].a=1; edge[3].b=6; edge[3].w=2; add(node[0].n, 6, 3); add(node[5].n, 1, 3);
    edge[4].a=2; edge[4].b=3; edge[4].w=1; add(node[1].n, 3, 4); add(node[2].n, 2, 4);
    edge[5].a=3; edge[5].b=5; edge[5].w=4; add(node[2].n, 5, 5); add(node[4].n, 3, 5);
    edge[6].a=5; edge[6].b=5; edge[6].w=4; add(node[4].n, 5, 6);
    edge[7].a=5; edge[7].b=6; edge[7].w=3; add(node[4].n, 6, 7); add(node[5].n, 5, 7);
    /* 엣지 선언 end */

    while(1) {
        char ch; scanf("%c", &ch);
        if(ch=='q') break;
        if(ch=='a') {
            int nodeNum; scanf("%d%*c", &nodeNum);
            int cnt=0;
            if(1<=nodeNum && nodeNum<=6 && node[nodeNum-1].n->head!=NULL) {
                ListNode *cur = node[nodeNum-1].n->head;
                while(1) {
                    if(edge[cur->conn].w!=0) {
                        printf(" %d %d", (edge[cur->conn].a==nodeNum ? edge[cur->conn].b : edge[cur->conn].a), edge[cur->conn].w);
                        cnt++;
                    }
                    if(cur->next==NULL) break;
                    cur = cur->next;
                }
            }
            if(cnt==0) printf("-1");
            printf("\n");
        } else {
            int a, b, w; scanf("%d %d %d%*c", &a, &b, &w);
            if(a<1 || a>6 || b<1 || b>6) {
                printf("-1\n");
                continue;
            }

            int idx = searchIdx(edge, edgeNum, a, b);
            if(idx==-1) {
                edge[edgeNum].a=a; edge[edgeNum].b=b; edge[edgeNum].w=w;
                add(node[a-1].n, b, edgeNum);
                if(a!=b) add(node[b-1].n, a, edgeNum);
                edgeNum++;
            } else {
                edge[idx].w=w;
            }
        }
    }
}