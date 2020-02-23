// Fenwick 트리로도 풀 수 있고, 트립으로도 풀 수 있는 문제.
// 하지만 Fenwick 트리로 어떻게 풀지 감이 전혀 안왔고, 
// 책의 답을 보고도 한번에 이해가 가지 않았다.
// 출현 빈도를 저장하는 방식을 잘 기억해 두자.

//트립으로 푸는게 더 느렸다.

#include <iostream>
#include <vector>
using namespace std;

struct FenwickTree {
    vector<int> tree;
    FenwickTree(int n) : tree(n+1) {}

    // A[0..pos]의 부분 합을 구한다.
    int sum(int pos){
        //인덱스가 1부터 시작한다고 가정
        ++pos;
        int ret = 0;
        while(pos > 0){
            ret += tree[pos];
            // 다음 구간을 찾기 위해 최종 비트를 지운다.
            pos &= (pos - 1);
        }
        return ret;
    }

    // A[pos]에 val을 더한다. 
    void add(int pos, int val){
        ++pos;
        while(pos < tree.size()){
            tree[pos] += val;
            
            //가장 마지막의 1을 더해준다.
            pos += (pos & -pos);
        }
    }
};

struct Node{
    int key, priority, size;
    Node *left, *right;

    Node(const int _key): key(_key), priority(rand()), size(1), left(NULL), right(NULL){}

    void setLeft(Node* newLeft){
        left = newLeft;
        calcSize();
    }

    void setRight(Node* newRight){
        right = newRight;
        calcSize();
    }

    void calcSize(){
        size = 1;
        if(left)
            size += left->size;
        if(right)
            size += right->size;
    }
};

typedef pair<Node*,Node*> NodePair;

NodePair split(Node* root, int key){
    if(root == NULL) return make_pair<Node*, Node*>(NULL, NULL);
    if(root->key > key){
        NodePair splitted = split(root->left, key);
        root->setLeft(splitted.second);
        return make_pair(splitted.first, root);    
    }
    else{
        NodePair splitted = split(root->right, key);
        root->setRight(splitted.first);
        return make_pair(root, splitted.second);
    }
}

Node* insert(Node* root, Node* new_node){
    if(root == NULL) return new_node;

    if(new_node->priority > root->priority){
        NodePair splitted = split(root, new_node->key);
        new_node->setLeft(splitted.first);
        new_node->setRight(splitted.second);
        return new_node;
    }
    
    if(new_node->key > root->key){
        root->setRight(insert(root->right, new_node));
    }
    else{
        root->setLeft(insert(root->left, new_node));
    }
    return root;
}

Node* kth(Node* root, int k){
    int lsize = 0;
    if(root->left) lsize+=root->left->size;
    if(lsize >= k) return kth(root->left, k);
    if(k == lsize + 1) return root;
    return kth(root->right, k - lsize - 1);
}

int noOfBiggers(Node* root, int key){
    if(root == NULL) return 0;
    if(root->key <= key)
        return noOfBiggers(root->right, key);
    int ret = 0;
    if(root->right)
        ret += root->right->size;
    return ret + 1 + noOfBiggers(root->left, key);
}

Node* merge(Node* a, Node* b){
    if(a == NULL) return b;
    if(b == NULL) return a;
    if(a->priority > b->priority){
        a->setRight(merge(a->right, b));
        return a;
    }
    b->setLeft(merge(a, b->left));
    return b;
}

Node* erase(Node* root, int key){
    if(root == NULL) return NULL;

    if(root->key == key){
        Node* merged = merge(root->left, root->right);
        delete root;
        return merged;
    }
    if(key > root->key){
        root->setRight(erase(root->right, key));
    }
    else
        root->setLeft(erase(root->left, key));
    return root;
}

long long solve(vector<int> &arr){
    FenwickTree F(1000000);
    long long ret = 0;
    for(int i=0; i<arr.size(); i++){
        ret += (long long)F.sum(1000000) - F.sum(arr[i]);
        F.add(arr[i], 1);
    }
    return ret;
}

long long solve2(vector<int> &arr){
    //트립을 이용한 풀이
    Node* root = NULL;
    long long ret = 0;
    for(int i=0; i<arr.size(); i++){
        ret += noOfBiggers(root, arr[i]);
        root = insert(root, new Node(arr[i]));
    }
    return ret;
}

int main(){
    int i,j,k, N;
    vector<int> arr;
    for(scanf("%d", &j), i=0; i<j; i++){
        cin >> N;
        arr.clear();
        arr.resize(N);
        for(k=0; k<N; k++){
            cin >> arr[k]; 
        }
        cout << solve2(arr) << endl;
    }
}