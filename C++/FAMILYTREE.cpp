// 촌수를 세는 문제.
// 공통 조상을 찾는 것까지는 생각했는데 이것을 어떻게 구간 트리와
// 연결시킬지 생각하는 것이 정말 어려웠다.
// 이걸 순회하면서 나온 경로로 풀 생각을 하다니...
// 이런 통찰은 언제쯤 가질 수 있을까

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int INT_MAX = numeric_limits<int>::max();

struct RMQ{
    int n;

    vector<int> rangeMin;
    RMQ(const vector<int> &array){
        n = array.size();
        rangeMin.resize(4 * n);
        init(array, 0, n-1, 1);
    }

    int init(const vector<int> &array, int left, int right, int node){
        if(left == right) return rangeMin[node] = array[left];
        
        int mid = (left + right) / 2;
        return rangeMin[node] = max(init(array, left, mid, 2 * node), init(array, mid +1, right, 2 * node + 1));
    }

    int query(int left, int right, int node, int nodeLeft, int nodeRight){
        if(left > right) swap(left, right);
        if(left > nodeRight || nodeLeft > right) return -INT_MAX;
        
        if(left <= nodeLeft && right >= nodeRight) 
            return rangeMin[node];

        int mid = (nodeLeft + nodeRight) / 2;

        return max(
                query(left, right, 2 * node, nodeLeft, mid),
                query(left, right, 2 * node + 1, mid + 1, nodeRight)
                );
    }

    int query(int left, int right){
        return query(left, right, 1, 0, n-1);
    }
};

struct TreeNode{
    vector<TreeNode*> children;
    int key, level;

    TreeNode(int _key, int _level): key(_key), level(_level){}

    void setChild(TreeNode* child){
        children.push_back(child);
    }
};

void traverse(TreeNode* root, vector<int> &result, int level){
    if(root == NULL) return;
    root->level = level;
    result.push_back(root->key);
    for(int i=0; i<root->children.size(); i++){
        traverse(root->children[i], result, level - 1);
        result.push_back(root->key);
    }
}

int main(){
    vector<TreeNode*> nodes;
    int i,j,k,N,Q,tmp;
    vector<int> trvs_result;
    vector<int> appearance;
    vector<pair<int, int>> inputs;

    for(scanf("%d", &j), i=0; i<j; i++){
        scanf("%d %d", &N, &Q);
        inputs.clear();
        trvs_result.clear();
        appearance.clear();
        appearance.resize(N, -1);
        nodes.clear();
        nodes.resize(10 * N);
        for(k=0; k<N; k++){
            nodes[k] = new TreeNode(k, 0);
        }
        for(k=1; k<N; k++){
            scanf("%d", &tmp);
            nodes[tmp]->setChild(nodes[k]);
        }

        traverse(nodes[0], trvs_result, 0);
        for(k=0; k<trvs_result.size(); k++){
            if(appearance[trvs_result[k]] == -1)
                appearance[trvs_result[k]] = k;
            trvs_result[k] = nodes[trvs_result[k]]->level;
        }
        RMQ rmq(trvs_result);
        for(k=0; k<Q; k++){
            int n1, n2;
            scanf("%d %d", &n1, &n2);
            int max_height = rmq.query(appearance[n1], appearance[n2]);
            printf("%d\n", 2 * max_height - nodes[n1]->level - nodes[n2]->level);
        }
        for(k=0; k<N; k++){
            delete nodes[k];
        }
    }
}