#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    struct node *left; // 왼쪽 자식
    struct node *right; // 오른쪽 자식
    struct node *parent; // 부모
    int val; // 노드의 값
    int height; // 노드의 높이
} node;

typedef struct tree {
    node *root; // 루트 노드
} tree;

int max(int a, int b) { // 최대값 반환
    return a>b?a:b;
}

void heightUpdate(node *cur, tree *t) { // 해당 노드부터 루트 노드까지의 높이 업데이트
    while(1) {
        int left=0, right=0;
        if(cur->left) left = cur->left->height;
        if(cur->right) right = cur->right->height;
        cur->height = max(left, right)+1;
        if(cur==t->root) return;
        cur = cur->parent;
    }
}

int isBalanced(node *cur) { // 균형이 망가진 경우 (자식의 높이 차이가 2 이상인 경우)
    int left=0, right=0;
    if(cur->left) left = cur->left->height;
    if(cur->right) right = cur->right->height;
    if(abs(left-right)>1) return 0;
    return 1;
}

void searchAndFixAfterInsertion(node *cur, tree *t) { // 삽입 과정에서 트리의 균형이 망가진 경우 고치기
    while(1) {
        if(!isBalanced(cur)) { // 균형이 망가진 경우
            if(cur->left!=NULL && (cur->right==NULL || cur->left->height>cur->right->height)) { // 왼쪽 자식의 높이가 더 높은 경우
                if(cur->left->left!=NULL && (cur->left->right==NULL || cur->left->left->height > cur->left->right->height)) { // 왼쪽 자식의 자식 중에 왼쪽 자식의 높이가 더 높은 경우
                    //       x
                    //      / \
                    //     y   a          =>     y
                    //    / \                   / \
                    //   z   b                 z   x
                    //  / \                   / \ / \
                    // c   d                 c  d b  a
                    node *x=cur, *y=cur->left, *z=cur->left->left;
                    if(t->root == x) t->root = y; // 루트노드 재설정
                    else if(x->parent->left==x) x->parent->left = y; // x의 부모가 y를 가리키도록 설정
                    else x->parent->right = y;
                    if(y->right) { // b 이동
                        x->left = y->right;
                        y->right->parent = x;
                    } else {
                        x->left = NULL;
                    }
                    y->parent = x->parent;
                    x->parent = y;
                    y->right = x;
                    heightUpdate(x, t);
                } else { // 왼쪽 오른쪽
                    //     x
                    //    / \
                    //   y   a          =>     z
                    //  / \                   / \
                    // b   z                 y   x
                    //    / \               / \ / \
                    //   c   d             b  c d  a
                    node *x=cur, *y=cur->left, *z=cur->left->right;
                    if(t->root == x) t->root = z; // 루트노드 재설정
                    else if(x->parent->left==x) x->parent->left = z; // x의 부모가 z를 가리키도록 설정
                    else x->parent->right = z;
                    if(z->right) { // d 이동
                        x->left = z->right;
                        z->right->parent = x;
                    } else {
                        x->left=NULL;
                    }
                    if(z->left) { // c 이동
                        y->right = z->left;
                        z->left->parent = y;
                    } else {
                        y->right = NULL;
                    }
                    z->parent = x->parent;
                    z->left = y;
                    y->parent = z;
                    z->right = x;
                    x->parent = z;
                    heightUpdate(x, t);
                    heightUpdate(y, t);
                }
            } else { // 오른쪽 자식의 높이가 더 높은 경우
                if(cur->right->right!=NULL && (cur->right->left==NULL || cur->right->right->height > cur->right->left->height)) { // 오른쪽 자식의 자식 중에 오른쪽 자식의 높이가 더 높은 경우
                    //     x
                    //    / \
                    //   a   y          =>     y
                    //      / \               / \
                    //     b   z             x   z
                    //        / \           / \ / \
                    //       c   d         a  b c  d
                    node *x=cur, *y=cur->right, *z=cur->right->right;
                    if(t->root == x) t->root = y; // 루트노드 재설정
                    else if(x->parent->left==x) x->parent->left = y; // x의 부모가 y를 가리키도록 설정
                    else x->parent->right = y;
                    if(y->left) { // b 이동
                        x->right = y->left;
                        y->left->parent = x;
                    } else {
                        x->right = NULL;
                    }
                    y->parent = x->parent;
                    x->parent = y;
                    y->left = x;
                    heightUpdate(x, t);
                } else { // 오른쪽 왼쪽
                    //     x
                    //    / \
                    //   a   y          =>     z
                    //      / \               / \
                    //     z   b             x   y
                    //    / \               / \ / \
                    //   c   d             a  c d  b
                    node *x=cur, *y=cur->right, *z=cur->right->left;
                    if(t->root == x) t->root = z; // 루트노드 재설정
                    else if(x->parent->left==x) x->parent->left = z; // x의 부모가 z를 가리키도록 설정
                    else x->parent->right = z;
                    if(z->right) { // d 이동
                        y->left = z->right;
                        z->right->parent = y;
                    } else {
                        y->left=NULL;
                    }
                    if(z->left) { // c 이동
                        x->right = z->left;
                        z->left->parent = x;
                    } else {
                        x->right = NULL;
                    }
                    z->parent = x->parent;
                    z->left = x;
                    y->parent = z;
                    z->right = y;
                    x->parent = z;
                    heightUpdate(x, t);
                    heightUpdate(y, t);
                }
            }
            return;
        }
        if(cur==t->root) return;
        cur = cur->parent;
    }
}

void searchAndFixAfterRemoval(node *cur, tree *t) { // 삭제 과정에서 트리의 균형이 망가진 경우 고치기
    while(1) {
        if(!isBalanced(cur)) { // 균형이 망가진 경우
            if(cur->left!=NULL && (cur->right==NULL || cur->left->height>cur->right->height)) { // 왼쪽 자식의 높이가 더 높은 경우
                if(cur->left->left!=NULL && (cur->left->right==NULL || cur->left->left->height >= cur->left->right->height)) { // 왼쪽 자식의 자식 중에 왼쪽 자식의 높이가 더 높거나 같은 경우
                    //       x
                    //      / \
                    //     y   a          =>     y
                    //    / \                   / \
                    //   z   b                 z   x
                    //  / \                   / \ / \
                    // c   d                 c  d b  a
                    node *x=cur, *y=cur->left, *z=cur->left->left;
                    if(t->root == x) t->root = y; // 루트노드 재설정
                    else if(x->parent->left==x) x->parent->left = y; // x의 부모가 y를 가리키도록 설정
                    else x->parent->right = y;
                    if(y->right) { // b 이동
                        x->left = y->right;
                        y->right->parent = x;
                    } else {
                        x->left = NULL;
                    }
                    y->parent = x->parent;
                    x->parent = y;
                    y->right = x;
                    heightUpdate(x, t);
                } else { // 왼쪽 오른쪽
                    //     x
                    //    / \
                    //   y   a          =>     z
                    //  / \                   / \
                    // b   z                 y   x
                    //    / \               / \ / \
                    //   c   d             b  c d  a
                    node *x=cur, *y=cur->left, *z=cur->left->right;
                    if(t->root == x) t->root = z; // 루트노드 재설정
                    else if(x->parent->left==x) x->parent->left = z; // x의 부모가 z를 가리키도록 설정
                    else x->parent->right = z;
                    if(z->right) { // d 이동
                        x->left = z->right;
                        z->right->parent = x;
                    } else {
                        x->left=NULL;
                    }
                    if(z->left) { // c 이동
                        y->right = z->left;
                        z->left->parent = y;
                    } else {
                        y->right = NULL;
                    }
                    z->parent = x->parent;
                    z->left = y;
                    y->parent = z;
                    z->right = x;
                    x->parent = z;
                    heightUpdate(x, t);
                    heightUpdate(y, t);
                }
            } else { // 오른쪽 자식의 높이가 더 높은 경우
                if(cur->right->right!=NULL && (cur->right->left==NULL || cur->right->right->height >= cur->right->left->height)) { // 오른쪽 자식의 자식 중에 오른쪽 자식의 높이가 더 높거나 같은 경우
                    //     x
                    //    / \
                    //   a   y          =>     y
                    //      / \               / \
                    //     b   z             x   z
                    //        / \           / \ / \
                    //       c   d         a  b c  d
                    node *x=cur, *y=cur->right, *z=cur->right->right;
                    if(t->root == x) t->root = y; // 루트노드 재설정
                    else if(x->parent->left==x) x->parent->left = y; // x의 부모가 y를 가리키도록 설정
                    else x->parent->right = y;
                    if(y->left) { // b 이동
                        x->right = y->left;
                        y->left->parent = x;
                    } else {
                        x->right = NULL;
                    }
                    y->parent = x->parent;
                    x->parent = y;
                    y->left = x;
                    heightUpdate(x, t);
                } else { // 오른쪽 왼쪽
                    //     x
                    //    / \
                    //   a   y          =>     z
                    //      / \               / \
                    //     z   b             x   y
                    //    / \               / \ / \
                    //   c   d             a  c d  b
                    node *x=cur, *y=cur->right, *z=cur->right->left;
                    if(t->root == x) t->root = z; // 루트노드 재설정
                    else if(x->parent->left==x) x->parent->left = z; // x의 부모가 z를 가리키도록 설정
                    else x->parent->right = z;
                    if(z->right) { // d 이동
                        y->left = z->right;
                        z->right->parent = y;
                    } else {
                        y->left=NULL;
                    }
                    if(z->left) { // c 이동
                        x->right = z->left;
                        z->left->parent = x;
                    } else {
                        x->right = NULL;
                    }
                    z->parent = x->parent;
                    z->left = x;
                    y->parent = z;
                    z->right = y;
                    x->parent = z;
                    heightUpdate(x, t);
                    heightUpdate(y, t);
                }
            }
        }
        if(cur==t->root) return;
        cur = cur->parent;
    }
}

void insertItem(tree *t, int val) {
    node *n = (node*)malloc(sizeof(node));
    n->left=n->parent=n->right=NULL;
    n->val=val;
    n->height=1;

    if(t->root==NULL) { // 트리에 노드가 없는 경우
        t->root = n;
    } else { // 트리에 노드가 있는 경우
        node *cur = t->root;
        while(1) {
            if(val<cur->val && cur->left) cur = cur->left;
            else if(val>cur->val && cur->right) cur = cur->right;
            else break;
        }
        n->parent=cur;
        if(val<cur->val) cur->left=n;
        else cur->right=n;

        heightUpdate(cur, t); // 삽입한 노드부터 높이 업데이트
        searchAndFixAfterInsertion(cur, t); // 높이 균형 맞추기
    }
}

void print(node *n) { // 전위순회
    printf(" %d", n->val);
    if(n->left) print(n->left);
    if(n->right) print(n->right);
}

void printAll(tree *t) {
    if(t->root) print(t->root);
    printf("\n");
}

int search(node *n, int val) { // 값 탐색
    if(val==n->val) return 1;
    if(val<n->val && n->left) return search(n->left, val);
    if(val>n->val && n->right) return search(n->right, val);
    return 0;
}

void searchItem(tree *t, int val) {
    if(t->root && search(t->root, val)) printf("%d\n", val); // 탐색 성공
    else printf("X\n"); // 탐색 실패
}

int del(node *n, int val, tree* t) {
    if(val==n->val) {
        if(!n->left && !n->right) { // 자식이 없는 경우 (그냥 삭제)
            if(n == t->root) t->root=NULL;
            else { // 삭제한 노드가 루트 노드가 아닌 경우
                if(n->parent->left==n) n->parent->left=NULL;
                else n->parent->right=NULL;
                heightUpdate(n->parent, t); // 높이는 삭제한 노드의 원래 부모부터 업데이트
                searchAndFixAfterRemoval(n->parent, t); // 균형이 맞는지 삭제한 노드의 원래 부모부터 확인
            }
            free(n);
        } else if(n->left && !n->right) { // 왼쪽 자식만 있는 경우 (왼쪽 자식을 삭제한 노드의 위치로 이동)
            if(n == t->root) t->root=n->left;
            else { // 삭제한 노드가 루트 노드가 아닌 경우
                if(n->parent->left==n) n->parent->left = n->left;
                else n->parent->right = n->left;
                n->left->parent = n->parent;
                heightUpdate(n->parent, t); // 높이는 삭제한 노드의 원래 부모부터 업데이트
                searchAndFixAfterRemoval(n->parent, t); // 균형이 맞는지 삭제한 노드의 원래 부모부터 확인
            }
            free(n);
        } else if(n->right && !n->left) { // 오른쪽 자식만 있는 경우 (오른쪽 자식을 삭제한 노드의 위치로 이동)
            if(n == t->root) t->root=n->right;
            else { // 삭제한 노드가 루트 노드가 아닌 경우
                if(n->parent->left==n) n->parent->left=n->right;
                else n->parent->right=n->right;
                n->right->parent = n->parent;
                heightUpdate(n->parent, t); // 높이는 삭제한 노드의 원래 부모부터 업데이트
                searchAndFixAfterRemoval(n->parent, t); // 균형이 맞는지 삭제한 노드의 원래 부모부터 확인
            }
            free(n);
        } else { // 자식이 모두 있는 경우 (오른쪽 자식의 가장 왼쪽의 자식을 삭제한 노드의 위치로 이동)
            node *cur = n->right;
            while(cur->left) cur = cur->left;
            n->val = cur->val;
            if(cur->right) { // 이동할 노드가 오른쪽 자식을 가진 경우
                if(cur->parent->left==cur) cur->parent->left=cur->right;
                else cur->parent->right=cur->right;
                cur->right->parent = cur->parent;
            } else { // 이동할 노드가 오른쪽 자식을 가지지 않은 경우
                if(cur->parent->left==cur) cur->parent->left=NULL;
                else cur->parent->right=NULL;
            }
            heightUpdate(cur->parent, t); // 높이는 이동할 노드의 원래 부모부터 업데이트
            searchAndFixAfterRemoval(cur->parent, t); // 균형이 맞는지 이동할 노드의 원래 부모부터 확인
            free(cur);
        }
        return 1;
    }
    if(val<n->val && n->left) return del(n->left, val, t);
    if(val>n->val && n->right) return del(n->right, val, t);
    return 0;
}

void deleteItem(tree *t, int val) {
    if(t->root && del(t->root, val, t)) printf("%d\n", val); // 제거 성공
    else printf("X\n"); // 제거 실패
}

void freeAllNode(node *n) { // 트리의 모든 노드 할당 해제
    if(n->left) freeAllNode(n->left);
    if(n->right) freeAllNode(n->right);
    free(n);
}

void freeTree(tree *t) { // 트리 할당 해제
    freeAllNode(t->root);
    free(t);
}

int main(void) {
    tree *t = (tree*)malloc(sizeof(tree)); t->root=NULL;

    while(1) {
        char ch; scanf("%c%*c", &ch);
        if(ch=='i') { // insert
            int val; scanf("%d%*c", &val);
            insertItem(t, val);
        } else if(ch=='s') { // search
            int val; scanf("%d%*c", &val);
            searchItem(t, val);
        } else if(ch=='d') { // delete
            int val; scanf("%d%*c", &val);
            deleteItem(t, val);
        } else if(ch=='p') { // print
            printAll(t);
        } else if(ch=='q') { // quit
            break;
        }
    }
    freeTree(t); // 메모리 할당 해제
}