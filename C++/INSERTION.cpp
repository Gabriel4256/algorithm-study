// 트립(treap)을 이용하여 푸는 문제
// 알고보면 정말 간단한 문젠데, 생각하기는 어려웠다.
// kth 함수를 어떻게 하면 잘 활용할 수 있을지 생각해보자

#include <iostream>
#include <vector>
using namespace std;

typedef int KeyType;

struct Node {
    KeyType key;

    // 이 노드의 우선순위
    // 이 노드들 루트로 하는 서브트리의 크기(size)
    int priority, size;

    Node *left, *right;

    Node(const KeyType& _key) : key(_key), priority(rand()), size(1), left(NULL), right(NULL){}
    
    void setLeft(Node* newLeft){ left = newLeft; calcSize();}
    void setRight(Node* newRight){ right = newRight; calcSize();}

    void calcSize() {
        size = 1;
        if(left) size += left->size;
        if(right) size += right->size;
    }
};

typedef pair<Node*,Node*> NodePair;

// root를 루트로 하는 트립을 key 미만의 값과 이상의 값을 갖는
// 두 개의 트립으로 분리
NodePair split(Node* root, KeyType key){
    if(root == NULL) return NodePair(NULL, NULL);

    if(root->key < key){
        NodePair rs = split(root->right, key);
        root->right = rs.first;
        return NodePair(root, rs.second);
    }
    
    NodePair ls = split(root->left, key);
    root->setLeft(ls.second);
    return NodePair(ls.first, root);
}

Node* insert(Node* root, Node* node){
    if(root == NULL) return node;

    if(root->priority < node->priority){
        NodePair splitted = split(root, node->key);
        node->setLeft(splitted.first);
        node->setRight(splitted.second);
        return node;
    }
    else if(node->key < root->key){
        root->setLeft(insert(root->left, node));
    }
    else{
        root->setRight(insert(root->right, node));
    }
    return root;
}

//a와 b가 두 개의 트립이고 max(a) < min(b)일 때 이 둘을 합친다.
Node* merge(Node* a, Node* b){
    if(a == NULL) return b;
    if(b == NULL) return a;
    if(a->priority < b->priority){
        b->setLeft(merge(a, b->left));
        return b;
    }
    a->setRight(merge(a->right, b));
    return a;
}

//root를 루트로 하는 트립에서 key를 지우고 결과 트립의 루트를 반환
Node* erase(Node* root, KeyType key){
    if(root == NULL) return root;
    
    if(root->key == key){
        Node* ret = merge(root->left, root->right);
        delete root;
        return ret;
    }

    if(key < root->key)
        root->setLeft(erase(root->left, key));
    else
        root->setRight(erase(root->right, key));
    return root;
}

// root를 루트로 하는 트리 중에서 크기 상으로 k번째 원소를 반환한다.
Node* kth(Node* root, int k){
    int leftSize = 0;
    if(root->left) leftSize = root->left->size;
    if(k <= leftSize) return kth(root->left, k);
    if(k == leftSize + 1) return root;
    return kth(root->right, k - leftSize - 1);
}

// key보다 작은 키값의 수를 반환한다.
int countLessThan(Node* root, KeyType key){
    if(root == NULL) return 0;
    if(root->key >= key) return countLessThan(root->right, key);
    int leftSize = 0;
    if(root->left) leftSize = root->left->size;
    return leftSize + 1 + countLessThan(root->right, key); 
}   

void solve(vector<int> moves){
    vector<int> ret;
    Node* root = NULL;
    // for(int i=0; i<nums.size(); i++){
    //     root = insert(root, new Node(KeyType(i - nums[], i + 1)));
    // }

    for(int i=0; i<moves.size(); i++){
        root =  insert(root, new Node(i+1));
    }
    for(int i= moves.size() - 1; i > -1; i--){
        Node* ans = kth(root, root->size - moves[i]);
        ret.push_back(ans->key);
        root = erase(root, ans->key);
    }

    for(int i = ret.size() - 1; i> -1; i--){
        printf("%d ", ret[i]);
    }
    // traverse(root);
    printf("\n");
}

int main(){
    int i,j,k,l;
    vector<int> moves;
    for(scanf("%d", &j), i=0; i<j; i++){
        moves.clear();
        cin >> k;
        moves.resize(k);
        for(l=0; l<k; l++){
            cin >> moves[l];
        }
        solve(moves);
    }
}