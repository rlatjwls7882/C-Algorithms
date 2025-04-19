#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    struct node *next;
    int val;
} node;

typedef struct list {
    node *header;
} list;

node* newNode(int val) {
    node *n = (node*)malloc(sizeof(node));
    n->val=val;
    n->next = NULL;
    return n;
}

list* newList() {
    list *l = (list*)malloc(sizeof(list));
    l->header = newNode(0);
}

void insert(list *l, int val) {
    node *n = newNode(val);
    n->next = l->header->next;
    l->header->next = n;
}

void print(list *l) {
    node *n = l->header;
    if(n->next) {
        while(n->next) {
            n = n->next;
            printf(" %d", n->val);
        }
    } else {
        printf("0");
    }
    printf("\n");
}

list* merge(list *a, list *b) {
    list *c = newList();
    
    node *nodeA = a->header;
    node *nodeB = b->header;
    while(nodeA->next || nodeB->next) {
        if(!nodeA->next) {
            nodeB = nodeB->next;
            insert(c, nodeB->val);
        } else if(!nodeB->next) {
            nodeA = nodeA->next;
            insert(c, nodeA->val);
        } else if(nodeA->next->val > nodeB->next->val) {
            nodeA = nodeA->next;
            insert(c, nodeA->val);
        } else if(nodeA->next->val < nodeB->next->val) {
            nodeB = nodeB->next;
            insert(c, nodeB->val);
        } else {
            nodeA = nodeA->next;
            nodeB = nodeB->next;
            insert(c, nodeA->val);
        }
    }
    return c;
}

list* intersection(list *a, list *b) {
    list *c = newList();
    
    node *nodeA = a->header;
    node *nodeB = b->header;
    while(nodeA->next && nodeB->next) {
        if(nodeA->next->val > nodeB->next->val) {
            nodeA = nodeA->next;
        } else if(nodeA->next->val < nodeB->next->val) {
            nodeB = nodeB->next;
        } else {
            nodeA = nodeA->next;
            nodeB = nodeB->next;
            insert(c, nodeA->val);
        }
    }
    return c;
}

list* subtract(list *a, list *b) {
    list *c = newList();
    
    node *nodeA = a->header;
    node *nodeB = b->header;
    while(nodeA->next) {
        if(!nodeB->next || nodeA->next->val > nodeB->next->val) {
            nodeA = nodeA->next;
            insert(c, nodeA->val);
        } else if(nodeA->next->val < nodeB->next->val) {
            nodeB = nodeB->next;
        } else {
            nodeA = nodeA->next;
            nodeB = nodeB->next;
        }
    }
    return c;
}

int isSubset(list *a, list *b) {
    node *nodeA = a->header;
    node *nodeB = b->header;
    int last=0; // true
    while(nodeA->next) {
        if(!nodeB->next || nodeA->next->val > nodeB->next->val) {
            nodeA = nodeA->next;
            last = nodeA->val;
        } else if(nodeA->next->val < nodeB->next->val) {
            nodeB = nodeB->next;
        } else {
            nodeA = nodeA->next;
            nodeB = nodeB->next;
        }
    }
    return last;
}

void freeNode(node *n) {
    if(n->next) freeNode(n->next);
    free(n);
}

void freeList(list *l) {
    freeNode(l->header);
    free(l);
}

int main(){
    list *a = newList();
    int n; scanf("%d", &n);
    while(n--) {
        int val; scanf("%d", &val);
        insert(a, val);
    }
    
    list *b = newList();
    scanf("%d", &n);
    while(n--) {
        int val; scanf("%d", &val);
        insert(b, val);
    }
    
    list *c = merge(a, b);
    print(c);
    
    list *d = intersection(a, b);
    print(d);
    
    freeList(a);
    freeList(b);
    freeList(c);
    freeList(d);
}

/*
Input 1
6
3 7 45 88 99 101
4
7 10 15 45

Output 1
 3 7 10 15 45 88 99 101
 7 45

Input 2
0
3
9 20 77

Output 2
 9 20 77
 0

Input 3
0
0

Output 3
 0
 0
*/
