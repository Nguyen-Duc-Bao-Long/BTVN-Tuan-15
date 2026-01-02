#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*============= SET UP ==============*/
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Khai bao cau truc cho tung node
typedef struct Node{
    int level; //1: chapter     2: section      3: subsection        4: subcsubsection
    int index; //Chi so cua no trong chapter/ section/ subsection/ subsubsection
    char name[100];
    struct Node *children;
    struct Node *siblings;
} Node;
//Tao Node
Node *createNode(int level, int index, char *name){
    Node *p = (Node*)malloc(sizeof(Node));
    p->level = level;
    p->index = index;
    strcpy(p->name, name);
    p->children = NULL;
    p->siblings = NULL;
    return p;
}

//Them Node
void addNode (Node *parent, Node *children){
    if (parent->children == NULL){
        parent->children = children;
    }
    else{
        Node *p = parent->children;
        while (p->siblings != NULL){
            p = p->siblings;
        }
        p->siblings = children;
    }
}

//Ham nhap thong tin cho 1 Node
Node *inputNode(int level, int index){
    char name[100];
    int pages;
    printf("\nNhap ten: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    return createNode(level, index, name);
}

//Ham nhap Node
void inputTree(Node *parent, int level){
    int n;
    printf("So muc con cua \"%s\": ", parent->name);
    scanf("%d", &n);
    clearBuffer();
    for (int i=0; i<n; i++){
        Node *child = inputNode(level+1, i);
        addNode(parent, child);
        inputTree(child, level+1);
    }
}

//Ham in ra toan bo cay theo preorder
void printTree(Node *center){
    if (center == NULL) return;
    printf("%s \n", center->name);
    printTree(center->children);
    printTree(center->siblings);
}

/*============= YEU CAU: KIEM TRA XEM 2 CUON SACH CO PHAI LA BAN SAO CUA NHAU KHONG ==============*/
int isCopy(Node *book1, Node *book2){
    if (book1 == NULL && book2 == NULL) return 1; //Ca 2 deu rong
    if (book1 == NULL || book2 == NULL) return 0; //! trong 2 rong
    
    //So sanh node con va not anh em
    if (book1->level != book2->level)   return 0;
    if (book1->index != book2->index)   return 0;
    
    //So sanh ten cua node (Tru node goc)
    if (book1->level != 0){
        if (strcmp(book1->name, book2->name) != 0)  return 0;
    }
    
    //Bat dau so sanh tuong tu cho cac nhanh con va anh em khac
    return isCopy(book1->children, book2->children) && isCopy(book1->siblings, book2->siblings);
}

int main (){
    //Set up co ban
    Node *book1 = createNode(0, 0, "BOOK 1");
    inputTree(book1, 0);
    printTree(book1);

    Node *book2 = createNode(0, 0, "BOOK 2");
    inputTree(book2, 0);
    printTree(book2);

    //YEU CAU
    if (isCopy(book1, book2)){
        printf("\nHai cuon sach la ban copy cua nhau\n");
    }
    else{
        printf("\nHai cuon sach KHONG phai la ban copy cua nhau\n");
    }
}