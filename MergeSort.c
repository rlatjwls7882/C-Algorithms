#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    struct node *next;
    int val;
} node;

typedef struct list {
    node *head;
    int size;
} list;

void init(list* list) {
    list->head=NULL;
    list->size=NULL;
}

void insert(list* list, int val) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->val=val;
    if(list->size==0) {
        list->head=newNode;
    } else {
        node* cur = list->head;
        for(int i=0;i<list->size-1;i++) cur = cur->next;
        cur->next=newNode;
    }
    list->size++;
}

list* merge(list* L1, list* L2) {
    list* ret = (list*)malloc(sizeof(list));
    init(ret);
    node* retNode = NULL;

    node* l = L1->head; int idx1=0;
    node* r = L2->head; int idx2=0;
    while(idx1<L1->size && idx2<L2->size) {
        if(l->val<r->val) {
            if(retNode==NULL) {
                retNode=l;
                ret->head=l;
            } else {
                retNode->next = l;
                retNode = retNode->next;
            }
            l = l->next;
            idx1++;
        } else {
            if(retNode==NULL) {
                retNode=r;
                ret->head=r;
            } else {
                retNode->next = r;
                retNode = retNode->next;
            }
            r = r->next;
            idx2++;
        }
    }
    while(idx1<L1->size) {
        retNode->next = l;
        retNode = retNode->next;
        l = l->next;
        idx1++;
    }
    while(idx2<L2->size) {
        retNode->next = r;
        retNode = retNode->next;
        r = r->next;
        idx2++;
    }
    ret->size = L1->size + L2->size;
    return ret;
}

list* partition(list* L, int k) {
    list* L2 = (list*)malloc(sizeof(list));
    init(L2);
    
    node* cur = L->head;
    for(int i=0;i<k-1;i++) cur = cur->next;
    L2->head=cur->next;
    cur->next=NULL;
    L2->size = L->size-k;
    L->size=k;
    return L2;
}

list* mergeSort(list* L) {
    if(L->size>1) {
        list* L2 = partition(L, L->size/2);
        L = mergeSort(L);
        L2 = mergeSort(L2);
        L = merge(L, L2);
    }
    return L;
}

void insertAll(list* li, int n) {
    for(int i=0;i<n;i++) {
        int val; scanf("%d", &val);
        insert(li, val);
    }
}

void printAll(list* li, int n) {
    node* cur = li->head;
    for(int i=0;i<n-1;i++) {
        printf(" %d", cur->val);
        cur = cur->next;
    }
    printf(" %d", cur->val);
}

int main() {
    int n; scanf("%d", &n);
    list* li = (list*)malloc(sizeof(list));
    init(li);
    
    insertAll(li, n);
    li = mergeSort(li);
    printAll(li, n);
}