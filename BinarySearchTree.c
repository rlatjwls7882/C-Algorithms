#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    struct node *left, *right, *parent;
    int val;
} node;

typedef struct tree {
    node *root;
} tree;

void init(tree *t) {
    t->root=NULL;
}

void insertItem(tree *t, int val) {
    printf("\n");
    node *n = (node*)malloc(sizeof(node));
    n->left=n->parent=n->right=NULL;
    n->val=val;
    if(t->root==NULL) {
        t->root = n;
    } else {
        node *cur = t->root;
        while(1) {
            if(val<cur->val && cur->left) cur = cur->left;
            else if(val>cur->val && cur->right) cur = cur->right;
            else break;
        }
        n->parent=cur;
        if(val<cur->val) cur->left=n;
        else cur->right=n;
    }
}

void print(node *n) {
    printf(" %d", n->val);
    if(n->left) print(n->left);
    if(n->right) print(n->right);
}

void printAll(tree *t) {
    if(t->root) print(t->root);
    printf("\n");
}

int search(node *n, int val) {
    if(val==n->val) return 1;
    if(val<n->val && n->left) return search(n->left, val);
    if(val>n->val && n->right) return search(n->right, val);
    return 0;
}

void searchItem(tree *t, int val) {
    if(t->root && search(t->root, val)) printf("%d\n", val);
    else printf("X\n");
}

int del(node *n, int val, tree* t) {
    if(val==n->val) {
        if(!n->left && !n->right) {
            if(n == t->root) t->root=NULL;
            else if(n->parent->left==n) n->parent->left=NULL;
            else n->parent->right=NULL;
        } else if(n->left && !n->right) {
            if(n == t->root) t->root=n->left;
            else if(n->parent->left==n) n->parent->left = n->left;
            else n->parent->right = n->left;
            n->left->parent = n->parent;
        } else if(n->right && !n->left) {
            if(n == t->root) t->root=n->right;
            else if(n->parent->left==n) n->parent->left=n->right;
            else n->parent->right=n->right;
            n->right->parent = n->parent;
        } else {
            node *cur = n->right;
            while(cur->left) cur = cur->left;
            n->val = cur->val;
            if(cur->right) {
                if(cur->parent->left==cur) cur->parent->left=cur->right;
                else cur->parent->right=cur->right;
                cur->right->parent = cur->parent;
            } else {
                if(cur->parent->left==cur) cur->parent->left=NULL;
                else cur->parent->right=NULL;
            }
        }
        return 1;
    }
    if(val<n->val && n->left) return del(n->left, val, t);
    if(val>n->val && n->right) return del(n->right, val, t);
    return 0;
}

void deleteItem(tree *t, int val) {
    if(t->root && del(t->root, val, t)) printf("%d\n", val);
    else printf("X\n");
}

int main(void) {
    tree *t = (tree*)malloc(sizeof(tree)); init(t);
    /* format
    p -> PreOrder printing
    q -> quit
    i x -> insert x
    s x -> search x
    d x -> delete x
    */
    while(1) {
        char ch; scanf("%c%*c", &ch);
        if(ch=='i') {
            int val; scanf("%d%*c", &val);
            insertItem(t, val);
        } else if(ch=='s') {
            int val; scanf("%d%*c", &val);
            searchItem(t, val);
        } else if(ch=='d') {
            int val; scanf("%d%*c", &val);
            deleteItem(t, val);
        } else if(ch=='p') {
            printAll(t);
        } else if(ch=='q') {
            break;
        }
    }
}