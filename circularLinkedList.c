#include<stdio.h>
#include<stdlib.h>
struct Node{
    int data;
    struct Node*next;
}*head=NULL;
typedef struct Node Node;
Node *last;
void create(){
    if(head==NULL){printf("\nAlready Created");}
    head=(Node*)malloc(sizeof(Node));
    printf("\nenter head");
    scanf("%d",&head->data);
    head->next=head;
    last=head;
}
void insert(int key){
    if(head==NULL){printf("\nCreate a linked list first");}
    Node *t=(Node*)malloc(sizeof(Node));
    t->data=key;
    t->next=last->next;
    last->next=t;
}
void display(){
    Node *p=head;
    do{
        printf("\n%d",p->data);
        p=p->next;
    }while(p!=head);
}
int main(){
    create();
    insert(12);
    insert(13);
    insert(14);
    insert(15);

    return 0;
}
