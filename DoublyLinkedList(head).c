#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    struct node *next, *prev;
    int val;
} node;

typedef struct list {
    node *n;
    int size;
} list;

void insert(list *l, int pos, char val) {
    if(l->size+1<pos) {
        printf("invalid position\n");
        return;
    }
    
    node *newNode = (node*)malloc(sizeof(node));
    newNode->next=newNode->prev=NULL;
    newNode->val=val;
    l->size++;
    
    node *cur = l->n;
    while(pos-->1) cur = cur->next;
    newNode->prev = cur;
    newNode->next = cur->next;
    if(cur->next) cur->next->prev = newNode;
    cur->next = newNode;
}

void select(list *l, int pos) {
    if(l->size<pos) {
        printf("invalid position\n");
        return;
    }
    
    node *cur = l->n;
    while(pos-->0) cur = cur->next;
    printf("%c\n", cur->val);
}

void del(list *l, int pos) {
    if(l->size<pos) {
        printf("invalid position\n");
        return;
    }
    l->size--;
    
    node *cur = l->n;
    while(pos-->0) cur = cur->next;
    
    node *delNode = cur;
    if(cur->next) cur->next->prev = cur->prev;
    cur->prev->next = cur->next;
    free(delNode);
}

void print(list *l) {
    node *cur = l->n->next;
    while(cur) {
        printf("%c", cur->val);
        cur = cur->next;
    }
    printf("\n");
}

void freeNode(node *n) {
    if(n->next) freeNode(n->next);
    free(n);
}

int main(){
    list *l = (list*)malloc(sizeof(list));
    l->n = (list*)malloc(sizeof(node));
    l->n->next=l->n->prev=NULL;
    l->size=0;
    
    int n; scanf("%d", &n);
    while(n--) {
        char ch; scanf(" %c", &ch);
        if(ch=='P') {
            print(l);
        } else {
            int pos; scanf(" %d", &pos);
            if(ch=='G') {
                select(l, pos);
            } else if(ch=='D') {
                del(l, pos);
            } else {
                char val; scanf(" %c", &val);
                insert(l, pos, val);
            }
        }
    }
    freeNode(l->n);
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
