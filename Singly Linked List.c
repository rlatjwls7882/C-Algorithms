#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    char val;
    struct node *next;
} node;

typedef struct list {
    node *n;
} list;

void insert(list* l, int pos, char val) {
    node *newNode = (node*)malloc(sizeof(node));
    newNode->next=NULL;
    newNode->val=val;
    
    if(pos==1) {
        newNode->next=l->n;
        l->n=newNode;
    } else {
        node *n = l->n;
        while(pos-->2) {
            if(!n || !n->next) {
                printf("invalid position\n");
                free(newNode);
                return;
            }
            n = n->next;
        }
        newNode->next = n->next;
        n->next = newNode;
    }
}

void search(list *l, int pos) {
    if(!l->n) {
        printf("invalid position\n");
        return;
    }
    
    node *n = l->n;
    while(pos-->1) {
        if(!n->next) {
            printf("invalid position\n");
            return;
        }
        n = n->next;
    }
    printf("%c\n", n->val);
}

void del(list *l, int pos) {
    if(!l->n) {
        printf("invalid position\n");
        return;
    }
    
    node *delNode;
    if(pos==1) {
        delNode = l->n;
        l->n = l->n->next;
    } else {
        node *n = l->n;
        while(pos-->2) {
            if(!n->next) {
                printf("invalid position\n");
                return;
            }
            n = n->next;
        }
        if(!n->next) {
            printf("invalid position\n");
            return;
        }
        delNode = n->next;
        n->next = n->next->next;
    }
    free(delNode);
}

void print(list *l) {
    node *n = l->n;
    while(n) {
        printf("%c", n->val);
        n = n->next;
    }
    printf("\n");
}

void freeNode(node *n) {
    if(n->next) freeNode(n->next);
    free(n);
}

int main(){
    list *l = (list*)malloc(sizeof(list));
    l->n = NULL;
    
    int n; scanf("%d", &n);
    while(n--) {
        char ch; scanf(" %c", &ch);
        if(ch=='P') {
            print(l);
        } else {
            int pos; scanf(" %d", &pos);
            if(ch=='G') {
                search(l, pos);
            } else if(ch=='D') {
                del(l, pos);
            } else {
                char val; scanf(" %c", &val);
                insert(l, pos, val);
            }
        }
    }
    if(l->n) freeNode(l->n);
    free(l);
}

/*
Input1:
5
A 1 S
A 2 t
A 3 r
A 3 a
P

Output1:
Star

Input2:
9
A 1 D
A 2 a
A 3 y
D 1
P
G 3
A 1 S
P
G 3

Output2:
ay
invalid position
Say
y
*/
