#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//Khai bao cau truc node
typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

//Tao node
Node *createNode(int x){
    Node *p = (Node*)malloc(sizeof(Node));
    p->data = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

//Them node ben trai
void *addLeft(Node *root, int x){
    root->left = createNode(x);
}

//Them node ben phai
void *addRight(Node *root, int x){
    root->right = createNode(x);
}

/*======YEU CAU 1: IN CAC NUT THEO 3 CACH DUYET=======*/
//Duyet truoc
void NLR(Node *root){
    if (root != NULL){
        printf("%d ", root->data);
        NLR(root->left);
        NLR(root->right);
    }
}

//Duyet sau
void LRN(Node *root){
    if(root != NULL){ //Neu cay khong rong
        LRN(root->left);
        LRN(root->right);
        printf("%d ", root->data);
    }
}

//Duyet giua
void LNR(Node *root){
    if(root != NULL){ //Neu cay khong rong
        LNR(root->left);
        printf("%d ", root->data);
        LNR(root->right);
    }
}

/*======YEU CAU 2: VIET GIAI THUAT VUN DONG VA IN RA=======*/
//Ham swap gia tri cua 2 con tro
void swap(Node *a, Node *b){
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

//Ham vun dong, dam bao node cha lon hon node con
void heapify (Node *p){
    if (p == NULL) return;
    Node *largest = p;
    //Kiem tra con trai
    if (p->left != NULL && p->left->data > largest->data){
        largest = p->left;
    }
    //Kiem tra con phai
    if (p->right != NULL && p->right->data > largest->data){
       largest = p->right;
    }
    if (largest != p){
        swap(p, largest);
        heapify(largest);
    }
}

//Tao dong (postorder)
void createHeap(Node *root){
    if (root == NULL) return;
    createHeap(root->left);
    createHeap(root->right);
    heapify(root);
}


int main(){
    //Khoi tao cay
    Node *root = createNode(4);
    addLeft(root, 1);
    addRight(root, 3);
    addLeft(root->left, 2);
    addRight(root->left, 16);
    addLeft(root->right, 9);
    addRight(root->right, 10);
    addLeft(root->left->left, 14);
    addRight(root->left->left, 8);
    addLeft(root->left->right, 7);

    //YEU CAU 1
    NLR(root);
    printf("\n");
    LRN(root);
    printf("\n");
    LNR(root);
    printf("\n");

    //YEU CAU 2
    createHeap(root);
    LRN(root);

    return 0;
}