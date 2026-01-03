#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//Set up
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

//Ham add node
void addNode(Node *root, int x){
    if (root == NULL) return;
    if (root->left == NULL){
        root->left = createNode(x);
        return;
    }
    else if (root->right == NULL){
        root->right = createNode(x);
        return;
    }
    else{
        addNode(root->left, x);
        addNode(root->right, x);
    }
}

/*======YEU CAU 1: TAO CAY=======*/
//Ham tao cay
Node *createTree(int n){
    int x;
    Node *root = NULL;
    if (n <= 0) return NULL;
 
    printf("Nhap gia tri cua Node thu 1 (root): ");
    scanf("%d", &x);
    root = createNode(x);

    for (int i=2; i<=n; i++){
        printf("Nhap gia tri cua Node thu %d: \n", i);
        scanf("%d", &x);
        addNode(root, x);
    }
    return root;
}

/*======YEU CAU 2: KIEM TRA XEM 2 CAY CO GIONG NHAU KHONG=======*/
int isCopy (Node *root1, Node *root2){
    if (root1 == NULL && root2 == NULL) return 1;
    if (root1 == NULL || root2 == NULL) return 0;
    if (root1->data != root2->data) return 0;

    return isCopy(root1->left, root2->left) && isCopy(root1->right, root2->right);
}


int main(){
    int n, k;
    Node *Tree1, *Tree2;

    //YEU CAU 1: TAO 2 CAY NHI PHAN

    //Tao cay 1
    printf("Nhap so node cua Tree1: ");
    scanf("%d", &n);
    Tree1 = createTree(n);

    //Tao cay 2
    printf("Nhap so node cua Tree2: ");
    scanf("%d", &k);
    Tree2 = createTree(k);

    //YEU CAU 2: KIEM TRA 2 CAY XEM CO GIONG NHAU KHONG
    if(isCopy(Tree1, Tree2)){
        printf("Hai cay nay la nhu nhau");
    }
    else{
        printf("Hai cay nay la khac nhau");
    }

    return 0;
}