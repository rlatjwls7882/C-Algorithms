#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    char val;
    struct node *next;
} node;

typedef struct list {
    int size;
    node *header;
} list;

node* newNode(char val) {
    node *n = (node*)malloc(sizeof(node));
    n->val=val;
    n->next = NULL;
    return n;
}

list* newList() {
    list *l = (list*)malloc(sizeof(list));
    l->size=0;
    l->header = newNode(0);
}

void insert(list* l, int pos, char val) {
    if(l->size+1<pos) {
        printf("invalid position\n");
        return;
    }
    node *n = newNode(val);
    l->size++;

    node *cur = l->header;
    while(pos-->1) cur = cur->next;
    n->next = cur->next;
    cur->next = n;
}

void search(list *l, int pos) {
    if(l->size<pos) {
        printf("invalid position\n");
        return;
    }
    
    node *cur = l->header;
    while(pos-->0) cur = cur->next;
    printf("%c\n", cur->val);
}

void del(list *l, int pos) {
    if(l->size<pos) {
        printf("invalid position\n");
        return;
    }
    l->size--;

    node *cur = l->header;
    while(pos-->1) cur = cur->next;
    node *delNode = cur->next;
    cur->next = cur->next->next;
    free(delNode);
}

void print(list *l) {
    node *n = l->header;
    while(n->next) {
        n = n->next;
        printf("%c", n->val);
    }
    printf("\n");
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
    list *l = newList();
    
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
    freeList(l);
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
