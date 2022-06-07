#include <iostream>
#include <stdexcept>

using namespace std;

class Node {
    friend class BinTree;
    int key;
    Node *left, *right;

public:
    Node(int k = 0, Node *l = NULL, Node *r = NULL) {
        key = k;
        left = l;
        right = r;
    }

    ~Node() {
        key = 0;
        left = NULL;
        right = NULL;
    }
};



class BinTree {
protected:
    Node *root;
    void print_tree(int, Node *);
    void delete_tree(Node *);
    Node* add_node(Node *, Node *);///копирование дерева

public:
    BinTree() {
        root == NULL;
    }

    BinTree(int len) {
        root = NULL;
        for (int i = 0; i < len; i++) {
            int k = rand() % 100;
            this->add(k);
        }
    }

    BinTree(int len, int *arr) {
        root = NULL;
        for (int i = 0; i < len; i++) {
            this->add(arr[i]);
        }
    }

    BinTree(const BinTree &tree) {
        root = add_node(root, tree.root);
    }

    ~BinTree(){
        delete_tree(root);
    }
    BinTree &operator=(const BinTree &);
    void add(int);
    Node *del(int);
    Node *del(Node *);
    void print();
    Node *find(int);
    int max();
    int min();
    ///elem* BFS();
    ///void LRK(Node* );

};

void BinTree::add(int k) {
    if (root == NULL) {
        root = new Node(k);
        return;
    }
    Node *node = root;
    while (node) {
        if (node->key > k && node->left == NULL) {
            node->left = new Node(k);
            return;
        } else if (node->key <= k && node->right == NULL) {
            node->right = new Node(k);
            return;
        }
        if (node->key > k)
            node = node->left;
        else
            node = node->right;

    }}
void BinTree::delete_tree(Node * node) {
    if (node){
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }
}
Node * BinTree::add_node(Node * n, Node * node) {
    if(!node){
        return  NULL;
    }
    n =new Node(node ->key);
    n -> left =add_node(n->left,node->left);
    n -> right = add_node(n->right, node->right);
    return n;
}

BinTree& BinTree::operator=(const BinTree & tree) {
    if(this != &tree){
        delete_tree(root);///удалить дерево
        root = add_node(root, tree.root);
    }
    return *this;
}

void BinTree::print() {
    print_tree(1, root);
    cout << endl;
}

void BinTree::print_tree(int k, Node* node) {

    if (node != NULL)
    {

        print_tree (k+5, node->right);
        for(int i = 0; i < k; i++) {
            cout << " ";
        }
        cout << node->key  << endl;
        print_tree (k+5, node->left);
    }

}

Node* BinTree ::find(int k) {
    if (root == NULL)
        return NULL;
    Node* n = root;
    while(n) {
        if (n->key == k){
            return n;
        } else if (n->key > k && n->left == NULL) {
            return NULL;
        } else if (n->key < k && n->right == NULL) {
            return NULL;
        }
        if (n->key > k)
            n = n->left;
        else
            n = n->right;
    }
}

int BinTree::min() {
    Node *curr = root;
    while (curr->left) {
        curr = curr->left;
    }
    if (curr) {
        return curr->key;
    }
    return -1;
}

int BinTree::max() {
    Node *curr = root;
    while (curr->right) {
        curr = curr->right;
    }
    if (curr) {
        return curr->key;
    }
    return -1;
}
////Проблемное удаление
Node *BinTree::del(Node *s) {
    return del(s->key);
}

Node *BinTree::del(int k) {
    Node *current = root;
    Node *parent = NULL;
    Node *s;
    while (current && current->key != k) {
        parent = current;
        if (current->key > k)
            current = current->left;
        else
            current = current->right;
    }
    if (!current)
        throw invalid_argument("Ti sho? Key not found.");

    else if (current->left == NULL)
        if (parent && parent->left == current) {
            parent->left = current->right;
            delete current;
            return  parent->left;
        } else if (parent && parent->right == current){
            parent->right = current->right;
            delete current;
            return parent->right;
        }
        else {
            s = current->right;
            root = s;
            return root;
        }
}
///проблема кончилась

int test() {
    int a[] = {13, 1, 45, 3, 4, 56};
    BinTree hah(10);
    BinTree heh(hah);
    BinTree hoh(6);
    BinTree hih(6, a);
    hoh = hah;
    hah.print();
    cout<< "////////////////////////////////////////////////////////////////"<< endl;
    heh.print();
    cout<< "////////////////////////////////////////////////////////////////"<< endl;
    hoh.print();
    cout<< "////////////////////////////////////////////////////////////////"<< endl;
    hih.print();
    cout<< "////////////////////////////////////////////////////////////////"<< endl;

    cout<< "min="<< hih.min()<< endl;
    cout<< "max="<< hih.max()<< endl;
    cout<< "search 3="<< hih.find(3)<< endl;
    cout<< "search 1000="<< hih.find(1000)<< endl;
}
int main(){
   test();
}