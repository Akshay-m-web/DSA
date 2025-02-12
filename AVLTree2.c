#include<stdio.h>
#include<stdlib.h>
struct Node {
    struct Node *lchild,*rchild;
    int data;
    int height;

}*root=NULL;

int nodeHeight(struct Node *p){
    int hl,hr;
    if(p==NULL)return  0;
    hl=p->lchild?p->lchild->height:0;
    hr=p->rchild?p->rchild->height:0;
    return (hl>hr ? hl+1: hr+1);
}

int balanceFactor(struct Node *p){
    if(p==NULL)return 0;
    return nodeHeight(p->lchild)-nodeHeight(p->rchild);
}

struct Node* LLRotation(struct Node *p){
    struct Node *pl=p->lchild;
    struct Node *plr=pl->rchild;
    pl->rchild=p;
    p->lchild=plr;
    p->height=nodeHeight(p);
    pl->height=nodeHeight(pl);
    if(root==p){
        root=pl;
    }
    return pl;
}

struct Node* RRRotation(struct Node *p){
    struct Node *pr=p->rchild;
    struct Node *prl=pr->lchild;
    pr->lchild=p;
    p->rchild=prl;
    p->height=nodeHeight(p);
    pr->height=nodeHeight(pr);
    if(root==p){
        root=pr;
    }
    return pr;
}

struct Node * Insert(struct Node *p,int key){
    struct Node *t=NULL;
    if(p==NULL){
        t=(struct Node *)malloc(sizeof(struct Node));
        t->data=key;
        t->height=1;
        t->lchild=t->rchild=NULL;
        return t;
    }
    if(key<p->data){
        p->lchild=Insert(p->lchild,key);
    }
    else if(key>p->data){
        p->rchild=Insert(p->rchild,key);
    }
    else{
        printf("\nKey Repeted"); return p;
    }
    p->height=nodeHeight(p);
    if(balanceFactor(p)==2 && balanceFactor(p->lchild)==1)
        return LLRotation(p);
    else if(balanceFactor(p)==2 && balanceFactor(p->lchild)==-1){
        //LRRotation
        p->lchild=RRRotation(p->lchild);
        return LLRotation(p);
    }
    else if(balanceFactor(p)==-2 && balanceFactor(p->rchild)==1){
        //RL
        p->rchild=LLRotation(p->rchild);
        return RRRotation(p);
    }
    else if(balanceFactor(p)==-2 && balanceFactor(p->rchild)==-1)
        return RRRotation(p);

return p;
}
void preorder(struct Node *p){
    if(p){
        printf("Data: %d   BalanceFactor: %d\n",p->data,balanceFactor(p));
        preorder(p->lchild);
        preorder(p->rchild);
    }
}

int main(){
    int ch,key;
    printf("1.Construct AVL Tree\n2.print Preorder Traversal with Balance Factor\n3.exit");
    while(1){
        printf("\nYour Choice");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                    while(1){
                        printf("Enter key (-1 to stop):");
                        scanf("%d",&key);
                        if(key==-1)break;
                        root=Insert(root,key);
                    }preorder(root);
                    break;
            case 2:preorder(root);break;
            case 3: exit(0);
            default:printf("\nEnter Valid Choice");
        }
    }
return 0;
}