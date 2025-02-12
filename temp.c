#include <stdio.h>
#include <stdlib.h>
struct Node * RRRotation(struct Node *);
struct Node * LRRotation(struct Node *);
struct Node * RLRotation(struct Node *);
struct Node * LLRotation(struct Node *);


struct Node {
    struct Node *lchild;
    int data;
    int height;
    struct Node *rchild;
} *root = NULL;

int nodeHeight(struct Node *p) {
    if (p == NULL) return 0;  // Return 0 for NULL nodes
    return p->height;         // Directly return the height
}

int balanceFactor(struct Node *p) {
    if (p == NULL) return 0;  // Return 0 for NULL nodes
    return nodeHeight(p->lchild) - nodeHeight(p->rchild);
}

// Rotation Functions
struct Node* LLRotation(struct Node *p) {
    struct Node *pl = p->lchild;
    p->lchild = pl->rchild;
    pl->rchild = p;

    // Update heights
    p->height = nodeHeight(p);
    pl->height = nodeHeight(pl);

    return pl;  // New root
}

struct Node* LRRotation(struct Node *p) {
    p->lchild = RRRotation(p->lchild);
    return LLRotation(p);
}

struct Node* RLRotation(struct Node *p) {
    p->rchild = LLRotation(p->rchild);
    return RRRotation(p);
}

struct Node* RRRotation(struct Node *p) {
    struct Node *pr = p->rchild;
    p->rchild = pr->lchild;
    pr->lchild = p;

    // Update heights
    p->height = nodeHeight(p);
    pr->height = nodeHeight(pr);

    return pr;  // New root
}

struct Node *RInsert(struct Node *p, int key) {
    if (p == NULL) {
        struct Node *t = (struct Node *)malloc(sizeof(struct Node));
        t->data = key;
        t->height = 1;  // New node is initially at height 1
        t->lchild = t->rchild = NULL;
        return t;  // Return new node
    }
    if (key < p->data) {
        p->lchild = RInsert(p->lchild, key);
    } else if (key > p->data) {
        p->rchild = RInsert(p->rchild, key);
    } else {
        printf("\nKey %d is repeated. Not adding to tree.\n", key);
        return p;  // Return unchanged node for duplicates
    }

    // Update height of current node
    p->height = nodeHeight(p);

    // Check for balance and perform rotations if necessary
    int balance = balanceFactor(p);
    if (balance > 1) {  // Left heavy
        if (key < p->lchild->data) {
            return LLRotation(p);  // LL Case
        } else {
            return LRRotation(p);  // LR Case
        }
    }
    if (balance < -1) {  // Right heavy
        if (key > p->rchild->data) {
            return RRRotation(p);  // RR Case
        } else {
            return RLRotation(p);  // RL Case
        }
    }

    return p;  // Return unchanged node pointer
}

void Inorder(struct Node *p) {
    if (p) {
        Inorder(p->lchild);
        printf("%d ", p->data);
        Inorder(p->rchild);
    }
}

int main() {
    root = RInsert(root, 10);
    root = RInsert(root, 5);
    root = RInsert(root, 15);
    root = RInsert(root, 20);
    root = RInsert(root, 25);
    root = RInsert(root, 30);
    root = RInsert(root, 40);
    root = RInsert(root, 50);
    
    // Attempting to insert duplicate key
    root = RInsert(root, 10);
    root = RInsert(root, 5);

    printf("Inorder:");
    Inorder(root);
    return 0;
}
