#include<stdio.h>
#include<stdlib.h>

typedef struct tree {
    struct tree *parent, *left, *right;
    int data;
    int visited;
} tree;

typedef struct root {
    struct tree* root;
} root;

void addChild(tree* cur, int b, int c) {
    cur->visited=0;
    if(b) {
        cur->left = (tree*)malloc(sizeof(tree));
        cur->left->data=b;
        cur->left->parent=cur;
        cur->left->visited=0;
    } else cur->left=0;
    if(c) {
        cur->right = (tree*)malloc(sizeof(tree));
        cur->right->data=c;
        cur->right->parent=cur;
        cur->right->visited=0;
    } else cur->right=0;
}

int main() {
    root root;
    root.root = (tree*)malloc(sizeof(tree));
    root.root->parent=0;
    root.root->data=-1;

    tree* cur = root.root;
    int n; scanf("%d", &n);
    while(n-->0) {
        int a, b, c; scanf("%d %d %d", &a, &b, &c);
        if(cur->data==-1) {
            cur->data=a;
            addChild(cur, b, c);
        } else {
            while(cur->data!=a) {
                if(cur->left && !(cur->left->visited)) cur = cur->left;
                else if(cur->right && !(cur->right->visited)) cur = cur->right;
                else {
                    cur->visited=1;
                    cur = cur->parent;
                }
            }
            addChild(cur, b, c);
        }
    }

    int m; scanf("%d", &m);
    while(m-->0) {
        char s[101]; scanf("%s", s);
        cur = root.root;
        printf(" %d", cur->data);
        for(char* pch=s;*pch;pch++) {
            if(*pch=='R') cur = cur->right;
            else cur = cur->left;
            printf(" %d", cur->data);
        }
        printf("\n");
    }
}