#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int val;
    struct node *next, *prev;
} node;

typedef struct deque {
    node *front, *back;
    
} deque;

deque* init() {
    deque *deq = (deque*)malloc(sizeof(deque));
    deq->front = deq->back = NULL;
    return deq;
}

node* getNode(int val, node *prev, node *next) {
    node *newNode = (node*)malloc(sizeof(node));
    newNode->val=val;
    newNode->prev = prev;
    newNode->next = next;
    return newNode;
}

void freeNode(node *n) {
    if(n->next) freeNode(n->next);
    free(n);
}

void freeDeq(deque *deq) {
    if(deq->front) freeNode(deq->front);
    free(deq);
}

void print(deque *deq) {
    node *n = deq->front;
    while(n) {
        printf(" %d", n->val);
        n = n->next;
    }
    printf("\n");
}

void push_front(deque *deq, int val) {
    node *newNode = getNode(val, NULL, deq->front);
    if(deq->front) deq->front->prev = newNode;
    deq->front = newNode;
    if(!deq->back) deq->back = deq->front;
}

void push_back(deque *deq, int val) {
    node *newNode = getNode(val, deq->back, NULL);
    if(deq->back) deq->back->next = newNode;
    deq->back = newNode;
    if(!deq->front) deq->front = deq->back;
}

int pop_front(deque *deq) {
    node *delNode = deq->front;
    if(!delNode) {
        printf("underflow\n");
        return 0;
    }
    deq->front = delNode->next;
    if(!deq->front) deq->back = NULL;
    if(delNode->next) delNode->next->prev = NULL;
    free(delNode);
    return 1;
}

int pop_back(deque *deq) {
    node *delNode = deq->back;
    if(!delNode) {
        printf("underflow\n");
        return 0;
    }
    deq->back = delNode->prev;
    if(!deq->back) deq->front = NULL;
    if(delNode->prev) delNode->prev->next = NULL;
    free(delNode);
    return 1;
}

int main(){
    int n; scanf("%d ", &n);
    
    deque *deq = init();
    while(n--) {
        char s[5]; scanf("%s ", s);
        if(s[0]=='P') {
            print(deq);
        } else if(s[0]=='D') {
            if(s[1]=='F') {
                if(!pop_front(deq)) break;
            } else {
                if(!pop_back(deq)) break;
            }
        } else {
            int val; scanf("%d ", &val);
            if(s[1]=='F') {
                push_front(deq, val);
            } else {
                push_back(deq, val);
            }
        }
    }
    freeDeq(deq);
}
/*
Input 1
15
AF 10
AF 20
AF 30
AR 40
AR 50
P
DF
DF
DR
P
DF
DR
DR

Output1
 30 20 10 40 50
 10 40
underflow

Input 2
7
AF 10
AF 20
AR 30
P
DF
DR
P

Output 2
 20 10 30
 10
*/
