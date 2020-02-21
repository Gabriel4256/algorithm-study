//처음에는 트리로 풀려고 했는데, 자꾸 시간초과가 떠서
//책을 참고해서 map을 이용해서 풀었다. 

#include <iostream>
#include <vector>
#include <map>
using namespace std;

int no_of_nodes;

map<int, int> coords;

bool isDominated(int x, int y){
    map<int, int>::iterator it = coords.lower_bound(x);
    if(it == coords.end()) return false;
    return y < it->second;
}

void removeDominated(int x, int y){
    map<int, int>::iterator it = coords.lower_bound(x);
    if(it == coords.begin()) return;

    --it;

    while(true){
        if(it->second > y) break;

        if(it == coords.begin()){
            coords.erase(it);
            break;
        }
        else{
            map<int, int>::iterator jt = it;
            --jt;
            coords.erase(it);
            it = jt;
        }
    }
}

int registers(int x, int y){
    if(isDominated(x, y)) return coords.size();
    removeDominated(x, y);
    coords[x] = y;
    return coords.size();
}

/// 여기서부터는 트리를 직접 구현한 풀이

struct Treenode {
    int p = 0,q = 0;
    Treenode *left, *right, *parent;

    Treenode(int _p, int _q){
        p = _p; q = _q;
        left = right = parent = NULL;
    }

    bool operator > (Treenode &b){
        return p > b.p && q > b.q;
    }
};

Treenode* remove(Treenode* node){
    Treenode* tmp = node;
    Treenode* parent = NULL;
    if(node->left){
        parent = node;
        node = node->left;
        while(node->right){
            parent = node;
            node = node->right;
        }
    }
    else if(node->right){
        parent = node;
        node = node->right;
        while(node->left){
            parent = node;
            node = node->left;
        }
    }
    if(parent){
        if(parent->right == node)
            parent->right = remove(node);
        else
            parent->left = remove(node);
        node->left = tmp->left;
        node->right = tmp->right;
        return node;
    }
    return NULL;
}

Treenode* search(Treenode* root, Treenode* new_node){
    if(root == NULL) return new_node;

    if(new_node->p < root->p && new_node->q < root->q){
        // new_node의 p,q 둘다 작은 경우에는 insert하지 않는다.
        no_of_nodes--;
        return root;
    }
    else if(new_node->p > root->p && new_node->q > root->q){
        // new_node의 p,q가 root보다 모두 큰 경우
        no_of_nodes--;
        return search(remove(root), new_node);
    }
    else if(new_node->p > root->p){
        // p만 큰 경우
        root-> right = search(root->right, new_node);
        root->right->parent = root;
        return root;
    }
    else if(new_node->q > root->q){
        // q만 큰 경우
        root->left = search(root->left, new_node);
        root->left->parent = root;
        return root;
    }
}

// 트리 풀이 끝

int main(){
    int i,j,k,l, p, q, ans = 0;
    Treenode* root = NULL;
    // vector<Treenode> nodes(100000);
    for(scanf("%d", &j), i=0; i<j; i++){
        coords.clear();
        no_of_nodes = 0;
        root = NULL;
        ans = 0;
        cin >> k;
        for(l=0; l<k; l++){
            cin >> p >> q;
            // Treenode* t = new Treenode(p, q);
            // no_of_nodes++;
            // root = search(root, t);
            // ans += no_of_nodes;
            ans += registers(p, q);
        }
        cout << ans << endl;
    }
}