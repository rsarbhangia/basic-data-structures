//I'll be implementing binary tree using structures in C
//author: @rsarbhangia Data: 20/04/2021

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node* leftPtr;
    int data;
    struct node* rightPtr;
}Node;


//It insert data x in a node pointed by S, which point to the
//Root node. It returns pointer to the root node
Node *insertNode(Node *s, int x){
    if(!s){
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->data = x,newNode->leftPtr = NULL,newNode->rightPtr = NULL;
        s = newNode;
    }
    else if(x <= s->data){
        s->leftPtr = insertNode(s->leftPtr, x);
    }
    else{
        s->rightPtr = insertNode(s->rightPtr, x);
    }
    return s;

}

//This will print element of a tree and will not return anything
//In-order
void printTree(Node* root){
    if(!root){
        return;
    }
    printTree(root->leftPtr);
    printf("%d ", root->data);
    printTree(root->rightPtr);

}



int main(){
    FILE *fp;
    fp = fopen("test.txt", "r+");
    int n;
    //printf("Enter number of nodes: ");
    fscanf(fp, " %d", &n);
    // scanf(" %d", &n);

    int ele;  //Used to scan element for our tree
    Node *root = NULL;//Root of our tree
    for(int i = 0;i < n;i++){
        // scanf(" %d", &ele);
        fscanf(fp, " %d", &ele);
        root = insertNode(root, ele);
    }


    //printf("Now printing the tree: ");
    printTree(root);

}