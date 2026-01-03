#include <iostream>
using namespace std;

struct Node
{
    int value; // gia tri nut   
    Node* left; // Con tro toi nut con trai
    Node* right; // Con tro toi nut con phai

    // Ham tao.
    Node(int v, Node* l, Node* r)
    {
        value = v;  
        left = l;
        right = r;
    }
};

// Lop cay nhi phan tim kiem.
class BSTree
{
private:
    Node *root; 
public:
    // Ham tao (ban dau cay rong).
    BSTree(){
        root = NULL;
    }

    // Ham huy (xoa het cac nut tren cay).
    ~BSTree(){
        makeEmpty();
    }

    // Kiem tra cay co rong hay khong.
    bool isEmpty(){
        return root == NULL;
    }

    // Xoa het cac nut tren cay.
    void makeEmpty(){
        makeEmpty(root);
        root = NULL;
    }

    // Chen mot nut val1 moi vao cay.
    void insert(int val1){
        return insert(val1,root);
    }

    // Tim nut val2
    Node* search(int val2){
        return search(val2,root);       
    }

    // Xoa rong cay (viet theo kieu de quy).
    void makeEmpty(Node*& t){
        if (t == NULL) return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = NULL;
    }

    // Chen mot nut val1 moi vao cay (viet theo kieu de quy).
    void insert(int val1, Node*& t){
        if (t == NULL){
            t = new Node(val1, NULL, NULL);
            return;
        }
        if (val1 < t->value){
            insert(val1, t->left);
        }
        else if (val1 > t->value){
            insert(val1, t->right);
        }
    }

    // Tim kiem nut co gia tri cho truoc (viet theo kieu de quy).
    Node* search(int val2, Node* t){
        if (t == NULL) return NULL;
        if (t->value == val2){
            return t;
        }
        else if (t->value > val2){
            return search(val2, t->left);
        }
        else
            return search(val2, t->right);
    }
};

void PREORDER_travl(Node* t){
    if (t == NULL) return;
    cout << t->value << " ";
    PREORDER_travl(t->left);
    PREORDER_travl(t->right);
}

void INORDER_travl(Node* t){
    if (t == NULL) return;
    INORDER_travl(t->left);
    cout << t->value << " ";
    INORDER_travl(t->right);
}

void POSTORDER_travl(Node* t){
    if (t == NULL) return;
    POSTORDER_travl(t->left);
    POSTORDER_travl(t->right);
    cout << t->value << " ";
}


int main()
{
    BSTree bst;

    // Chen cac node co gia tri duoi day .
    bst.insert(5);
    bst.insert(6);
    bst.insert(3);
    bst.insert(8);
    bst.insert(7);
    bst.insert(4);
    bst.insert(2);
    Node *root = bst.search(5);
    cout << "duyet cay thu tu truoc" << endl;
    PREORDER_travl(root);
    cout << "\nduyet cay thu tu giua" << endl;
    INORDER_travl(root);
    cout << "\nduyet cay thu tu sau" << endl;
    POSTORDER_travl(root);
    cout << endl;
    // Tim hai node co gia tri 4 va 9.
    Node* n1 = bst.search(4);
    Node* n2 = bst.search(9);

    // In ket qua tim kiem
    if (n1 != NULL)
        cout << "Node có gia tri = 4 la " << n1->value << endl;
    if (n2 == NULL)
        cout << "Khong tim thay node co gia tri =9" << endl;
  
    // Lam rong cay.
    bst.makeEmpty();
    if (bst.isEmpty())
        cout << "Cay da bi xoa rong" << endl;

    return 0;
}
