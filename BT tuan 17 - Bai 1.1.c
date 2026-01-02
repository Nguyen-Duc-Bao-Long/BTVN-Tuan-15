#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*============= SET UP ==============*/
void clearBuffer(){
    while (getchar() != '\n');
}

//Khai bao cau truc cho tung node
typedef struct Node{
    int level; //1: chapter     2: section      3: subsection        4: subcsubsection
    int index; //Chi so cua no trong chapter/ section/ subsection/ subsubsection
    char name[100];
    int pages;
    struct Node *children;
    struct Node *siblings;
} Node;

//Tao Node
Node *createNode(int level, int index, char *name){
    Node *p = (Node*)malloc(sizeof(Node));
    p->level = level;
    p->index = index;
    strcpy(p->name, name);
    p->pages = 0;
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
    if (n == 0){
        printf("Nhap so trang \"%s\": ", parent->name);
        scanf("%d", &parent->pages);
        clearBuffer();
        return;
    }
    for (int i=0; i<n; i++){
        Node *child = inputNode(level+1, i);
        addNode(parent, child);
        inputTree(child, level+1);
    }
}

//Ham in ra toan bo cay theo preorder
void printTree(Node *center){
    if (center != NULL){
        if (center->pages != 0){
            printf("%-30s | So trang: %d \n", center->name, center->pages);
        }
        else 
            printf("%s \n", center->name);
        printTree(center->children);
        printTree(center->siblings);
    }
}

/*============YEU CAU 1: XAC DINH SO CHUONG CUA CUON SACH=============*/
int countChapter(Node *book){
    int n = 0;
    Node *p = book->children;
    while(p != NULL){
        n++;
        p = p->siblings;
    }
    return n;
}

/*============YEU CAU 2: TIM CHUONG DAI NHAT CUA CUON SACH=============*/
//Ham tinh tong so trang cua 1 Chapter
int totalPages(Node *chapter){
       if (chapter == NULL) return 0;

    //Neu chapter la node la
    if (chapter->children == NULL) return chapter->pages;
    //Neu chapter co section
    int sum = 0;
    Node *p = chapter->children;
    while (p != NULL){
        sum = sum + totalPages(p);
        p = p->siblings;
    }
    return sum;
}

//Tim chuong dai nhat
Node *findTheLongest(Node *book){
    int maxPages = 0;
    int a;
    Node *maxChapter = NULL;
    Node *p = book->children;
    while (p != NULL){
        a = totalPages(p);
        if(a > maxPages){
            maxPages = a;
            maxChapter = p;
        }
        p = p->siblings;
    }
    return maxChapter;   
}

/*============YEU CAU 3: TIM MOT MUC VA XOA. SAU DO CAP NHAT LAI DANH SACH=============*/
//Ham xoa toan bo cay con
void freeSubTree(Node *p){
    if (p == NULL) return;
    freeSubTree(p->children);
    free(p);
}

//Tim kiem va xoa node o cay anh em (Chi duyet siblings)
int deleteChildren(Node *parent, const char *name){
    if (parent == NULL || parent->children == NULL)
        return 0;

    Node *p = parent->children;
    Node *q = NULL;
    //Duyet tat ca siblings
    while (p != NULL){
        if (strcmp(p->name, name) == 0){
            if (q == NULL)
                parent->children = p->siblings;
            else
                q->siblings = p->siblings;
            freeSubTree(p);
            return 1;
        }
        q = p;
        p = p->siblings;
    }
    return 0;
}

//Tim va xoa Node bat ky (Duyet ca cay)
int deleteNode(Node *root, const char *name){
    if (root == NULL)
        return 0;

    //Thu xoa cac children cua root nhap vao
    if (deleteChildren(root, name))
        return 1;

    //Neu chua xoa duoc se duyet toi cac muc nho hon
    Node *child = root->children;
    while (child != NULL){
        if (deleteNode(child, name))
            return 1;
        child = child->siblings;
    }
    return 0;
}

//Cap nhat lai so trang
int updatePages(Node *p){
    if (p == NULL) return 0;
    if (p->children == NULL) return p->pages;
    int sum = 0;
    Node *child = p->children;
    while (child != NULL){
        sum += updatePages(child);
        child = child->siblings;
    }
    p->pages = sum;
    return sum;
}

/*============YEU CAU 4: TIM MOT CHUONG. SAU DO IN RA CAC DE MUC=============*/
void printHeadings(Node *book){
    char key[100];
    int found = 0;
    Node *p = book->children;
    clearBuffer();
    printf("Nhap ten chuong muon in de muc: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; //Xoa dau xuong dong
    while (p != NULL){
        if (strcmp(key, p->name) == 0){
            found++;
            printTree(p);
            break;
        }
        p = p->siblings;
    }
    if (found == 0){
        printf("Khong tim duoc ten chuong\n");
    }
}

int main(){
    //Set up co ban
    Node *book = createNode(0, 0, "BOOK");
    inputTree(book, 0);
    printTree(book);

    //YEU CAU 1
    printf("Quyen sach co: %d chuong\n", countChapter(book));
  
    //YEU CAU 2
    Node *theLongest = findTheLongest(book);
    printf("Chuong dai nhat la: %s | So trang la: %d\n", theLongest->name, totalPages(theLongest));\

    //YEU CAU 3
    char name[100];
    clearBuffer();
    printf("Nhap ten muc can xoa: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    if (deleteNode(book, name)){
        updatePages(book);
        printf("Da xoa muc \"%s\" thanh cong\n", name);
    } 
    else
        printf("Khong tim thay muc \"%s\" de xoa\n", name);
    printTree(book);

    //YEU CAU 4
    printHeadings(book);

    return 0;
}