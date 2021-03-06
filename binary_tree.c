//I'll be implementing "binary search tree" using structures in C
//author: @rsarbhangia Data: 20/04/2021

//Version 1.01
//Change Log: Printing Tree in a tree structure xxx
//Added functionality to print tree in pre-order for uniqueness
//Version 1.02
//Patched the bug regarding Segmentation error

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node{
    struct node* leftPtr;
    int data;
    struct node* rightPtr;
}Node;


//It insert data x in a node pointed by S, which point to the
//Root node. It returns pointer to the root node
//Specs: Avg: O(logN), Worst: O(N)
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

//It deletes node with value "x", and returns the value x
//Returns -1 if not found
Node* deleteNode(Node* s, int x){
    Node *root = s;
    Node *p = NULL;
    while(s && (s->data != x)){//Finding pos of x
        p = s;
        if(x < s->data){
            s = s->leftPtr;
        }
        else{
            s = s->rightPtr;
        }
    }
    if(!s){//If x is not found
        return NULL;
    }

    if(s->leftPtr && s->rightPtr){//Both children there
        Node *iter = s->leftPtr;
        p = s;
        while(iter->rightPtr){
            p = iter;
            iter = iter->rightPtr;
        }
        s->data = iter->data;
        s = iter;
    }

    if(!s->leftPtr && !s->rightPtr){   //If the node is a leaf
        if(!p){
            free(s);
            s = NULL;
            return s;
        }
        if(s->data <= p->data){
            p->leftPtr = NULL;
        }
        else{
            p->rightPtr = NULL;
        }
    }
    else if(!s->leftPtr && s->rightPtr){//Right child present
        if(!p){
            p = s;
            s = s->rightPtr;
            free(p);
            p = NULL;
            return s;
        }
        if(s->data <= p->data){
            p->leftPtr = s->rightPtr;
        }
        else{
            p->rightPtr = s->rightPtr;
        }
    }
    else if(s->leftPtr && !s->rightPtr){//Left Child present
        if(!p){
            p = s;
            s = s->leftPtr;
            free(p);
            p = NULL;
            return s;
        }
        if(s->data <= p->data){
            p->leftPtr = s->leftPtr;
        }
        else{
            p->rightPtr = s->leftPtr;
        }
    }

    free(s);
    s = NULL;
    return root;
}


//This will print element of a tree and will not return anything
//In-order 
//Specs: O(N) = 2T(N/2) + c
void printTree(Node* s){
    if(!s){
        return;
    }
    printTree(s->leftPtr);
    printf("%d ", s->data);
    printTree(s->rightPtr);

}

//Will print tree in pre-order, implementing this function 
//to check tree uniquely
void printTreePre(Node* s){
    if(!s){
        return;
    }
    printf("%d ", s->data);
    printTreePre(s->leftPtr);
    printTreePre(s->rightPtr);

}


//This will print a tree in a pattern similar to a tree
void printTreePattern(int *arr, int len, int counter){
    for(int i = 0;i < len;i++){
        for(int j = 0;j < pow(2,i);j++){
            for(int k = 0;k < counter;k++){
                printf(" ");
            }
            printf("%d", arr[i+j]);
        }
        counter /= 2;
    }
}

int *TreeToArr(Node *s, int *arr, int counter){
    if(!s){
        return NULL;
    }
    arr[counter++] = s->data;
    TreeToArr(s->leftPtr, arr, counter);
    TreeToArr(s->rightPtr, arr, counter);

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


    printf("Now printing the tree(in-order): ");
    //int numLev = ceil(log(n+1));
    printTree(root);
    printf("\nThe tree(pre-order): ");
    printTreePre(root);
    printf("\n\n");

   int x;
   fscanf(fp, " %d", &x);
   root = deleteNode(root, x);

   printf("After deletion the tree(in-order): ");
    //int numLev = ceil(log(n+1));
    printTree(root);
    printf("\nThe tree(pre-order): ");
    printTreePre(root);
    printf("\n\n");

}