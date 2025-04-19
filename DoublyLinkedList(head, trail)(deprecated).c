#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    struct node *prev, *next;
    char data;
} node;

typedef struct list {
    node *head, *tail;
    int size;
} list;

void init(list* list) {
    list->head=0;
    list->tail=0;
    list->size=0;
}

void add(list* list, int r, char e) {
    if(list->size+1<r) {
        printf("invalid position\n");
        return;
    }

    node* newNode = (node*)malloc(sizeof(node));
    newNode->data=e;
    if(list->size==0) {
        list->head = newNode;
        list->tail = newNode;
    } else if(r==1) {
        list->head->prev = newNode;
        newNode->next = list->head;
        list->head = newNode;
    } else if(list->size+1 == r) {
        newNode->prev=list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    } else {
        node* cur = list->head;
        while(r-->1) cur = cur->next;
        cur->prev->next = newNode;
        newNode->prev = cur->prev;
        cur->prev = newNode;
        newNode->next = cur;
    }
    list->size++;
}

void print(list* list) {
    if(list->size==0) {
        printf("invalid position\n");
        return;
    }

    node* cur = list->head;
    while(1) {
        printf("%c", cur->data);
        if(cur == list->tail) break;
        cur = cur->next;
    }
    printf("\n");
}

void del(list* list, int r) {
    if(r>list->size) {
        printf("invalid position\n");
        return;
    }

    if(r==1 && list->size==1) {
        list->head=0;
        list->tail=0;
    } else if(r==1) {
        list->head = list->head->next;
    } else if(r==list->size) {
        list->tail = list->tail->prev;
    } else {
        node* cur = list->head;
        while(r-->1) cur = cur->next;
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
    }
    list->size--;
}

void get(list* list, int r) {
    if(r>list->size) {
        printf("invalid position\n");
        return;
    }

    node* cur = list->head;
    while(r-->1) cur = cur->next;
    printf("%c\n", cur->data);
}

int main() {
    list list;
    init(&list);

    int n; scanf("%d", &n);
    while(n-->0) {
        char a; scanf("%c%c",&a,&a);
        if(a=='A') {
            char c; int b; scanf("%d%c%c",&b,&c,&c);
            add(&list, b, c);
        } else if(a=='D') {
            int b; scanf("%d",&b);
            del(&list, b);
        } else if(a=='G') {
            int b; scanf("%d",&b);
            get(&list, b);
        } else print(&list);
    }
}
