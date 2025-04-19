#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node {
    struct node *next;
    int val;
} node;

int h(int x, int M) {
    return x%M;
}

void insert(node *arr, int val, int M) {
    int idx = h(val, M);
    node *newNode = (node*)malloc(sizeof(node));
    newNode->next = arr[idx].next;
    newNode->val = val;
    arr[idx].next = newNode;
}

void select(node *arr, int val, int M) {
    int idx = h(val, M);

    int chk=0, rank=0;
    node *cur = arr[idx].next;
    while(cur!=NULL) {
        rank++;
        if(cur->val==val) {
            chk=1;
            break;
        }
        cur = cur->next;
    }
    if(chk) printf("%d\n", rank);
    else printf("0\n");
}

void del(node *arr, int val, int M) {
    int idx = h(val, M);

    int chk=0, rank=0;
    node *cur = &arr[idx];
    while(cur->next!=NULL) {
        rank++;
        if(cur->next->val==val) {
            node *tmp = cur->next;
            cur->next = cur->next->next;
            free(tmp);
            chk=1;
            break;
        }
        cur = cur->next;
    }
    if(chk) printf("%d\n", rank);
    else printf("0\n");
}

void print(node *arr, int M) {
    for(int i=0;i<M;i++) {
        node *cur = arr[i].next;
        while(cur!=NULL) {
            printf(" %d", cur->val);
            cur = cur->next;
        }
    }
    printf("\n");
}

void freeNode(node *n) {
    if(n->next) freeNode(n->next);
    free(n);
}

int main() {
    int M; scanf("%d%*c", &M);
    node *arr = (node*)malloc(sizeof(node)*M);
    for(int i=0;i<M;i++) arr[i].next=NULL;

    while(1) {
        char ch; scanf("%c%*c", &ch);
        if(ch=='p') {
            print(arr, M);
        } else if(ch=='e') {
            break;
        } else {
            int val; scanf("%d%*c", &val);
            if(ch=='i') {
                insert(arr, val, M);
            } else if(ch=='s') {
                select(arr, val, M);
            } else {
                del(arr, val, M);
            }
        }
    }

    for(int i=0;i<M;i++) if(arr[i].next) freeNode(arr[i].next);
    free(arr);
}

/*
Input
13
i 34
i 23
i 26
i 21
s 36
s 26
s 34
s 21
p
d 21
s 34
d 8
e

Output
0
1
2
1
 26 21 34 23
1
1
0
*/