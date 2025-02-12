#include<stdio.h>
#include<stdlib.h>
struct Node {
    struct Node *lchild;
    int data;
    int height;
    struct Node *rchild;
}*root=NULL;


int nodeHeight(struct Node *p){
    int hl,hr;
    /*check the height of left and right subtree
     whichever is greater return it*/
    hl=p->lchild?p->lchild->height:0;
    hr=p->rchild?p->rchild->height:0;
    return hl>hr?hl+1:hr+1;
}

int balanceFactor(struct Node *p){
    int hl,hr;
    hl=p->lchild?p->lchild->height:0;
    hr=p->rchild?p->rchild->height:0;
    return hl-hr;
}

//Rotation Functions 
struct Node* LLRotation(struct Node *p){

    struct Node *pl=p->lchild;
    struct Node *plr=pl->rchild;

    pl->rchild=p;
    p->lchild=plr;

    //modify heights of p and pl
    p->height=nodeHeight(p);
    pl->height=nodeHeight(pl);

    //if imbalance node was root modify it with new root
    if(root==p){
        root=pl;
    }
    return pl;
}

struct Node* LRRotation(struct Node *p){

    struct Node *pl=p->lchild;
    struct Node *plr=pl->rchild;

    p->lchild=plr->rchild;
    plr->rchild=p;
    pl->rchild=plr->lchild;
    plr->lchild=pl;
    

    //modify heights of p and pl and plr
    p->height=nodeHeight(p);
    pl->height=nodeHeight(pl);
    plr->height=nodeHeight(plr);

    //if imbalance node was root modify it with new root
    if(root==p){
        root=plr;
    }
    return plr;
}
struct Node* RLRotation(struct Node *p){

    struct Node *pr=p->rchild;
    struct Node *prl=pr->lchild;

    p->rchild=prl->lchild;
    prl->lchild=p;
    pr->lchild=prl->rchild;
    prl->rchild=pr;

    //modify heights of p and pr and prl
    p->height=nodeHeight(p);
    pr->height=nodeHeight(pr);
    prl->height=nodeHeight(prl);

    //if imbalance node was root modify it with new root
    if(root==p){
        root=prl;
    }
    return prl;
}

struct Node* RRRotation(struct Node *p){

    struct Node *pr=p->rchild;
    struct Node *prl=pr->lchild;

    pr->lchild=p;
    p->rchild=prl;

    //modify heights of p and pr
    p->height=nodeHeight(p);
    pr->height=nodeHeight(pr);

    //if imbalance node was root modify it with new root
    if(root==p){
        root=pr;
    }
    return pr;
}

struct Node *RInsert(struct Node *p,int key){
    struct Node *t=NULL;
    if(p==NULL){
        t=(struct Node*)malloc(sizeof(struct Node));
        t->data=key;
        //set the height of first node to 1
        t->height=1;
        t->lchild=t->rchild=NULL;
        return t;
    }
    if(key<p->data){
        p->lchild=RInsert(p->lchild,key);
    }
    else if(key>p->data){
        p->rchild=RInsert(p->rchild,key);
    }

    //update height of every node
    p->height=nodeHeight(p);

    /*code for checking balance factor and deciding 
    whether to perform LL or LR or RR or RL */

    /*if balance factor of p is 2 means it is left imbalance
    and balance factor of p->lchild is postive means the p is
    LL-imbalance*/
    if(balanceFactor(p)==2 && balanceFactor(p->lchild)==1){
        //perform LL-rotation
        return LLRotation(p);
    }
    if(balanceFactor(p)==2 && balanceFactor(p->lchild)==-1){
        //perform LR-rotation
        return LRRotation(p);
    }
    if(balanceFactor(p)==-2 && balanceFactor(p->rchild)==1){
        //perform RL-rotation
        return RLRotation(p);
    }
    if(balanceFactor(p)==-2 && balanceFactor(p->lchild)==-1){
        //perform RR-rotation
        return RRRotation(p);
    }
    return p;
}

void Inorder(struct Node *p){
    if(p){
        Inorder(p->lchild);
        printf("%d ",p->data);
        Inorder(p->rchild);
    }
}
int main(){
    root=RInsert(root,10);
    RInsert(root,5);
    RInsert(root,10);
    RInsert(root,15);
    RInsert(root,20);
    RInsert(root,25);
    RInsert(root,30);
    //RInsert(root,5);
    RInsert(root,40);
    RInsert(root,50);
    printf("Inorder:");
    Inorder(root);
    return 0;
}