// disjoint set을 이용하여 푸는 문제
// 일단 책에 나온 방식대로는 잘 됐는데,
// 그거랑 겉보기에는 차이가 없어보이는 방식이 통과가 안된다.
// maxSet함수에서 memo를 하는 방식인데, 왜 안될까...

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<bool> checked;

struct DisjointSet {
    vector<int> parent, rank, size, dismissed;
    DisjointSet(int n) : parent(n), rank(n, 1), size(n, 1), dismissed(n, -1){
        for(int i=0; i<n; i++){
            parent[i] = i;
        }
    }

    int find(int u){
        if(u == -1) return -1;
        if(u == parent[u]) return u;
        return parent[u] = find(parent[u]);
    }

    int merge(int u, int v){
        if(u == -1 || v == -1) return max<int>(u,v);
        u = find(u); v = find(v);

        if(u == v) return u;
        if(rank[u] > rank[v]) swap(u,v);
        if(rank[u] == rank[v]) rank[v]++;
        parent[u] = v;
        size[v] += size[u];
        return v;
    }

    bool ack(int u, int v){
        int l,k;
        u = find(u); v = find(v);
        if(find(dismissed[u]) == v || find(dismissed[v]) == u) return false;
        
        l = merge(u, v);
        k = merge(dismissed[u], dismissed[v]);
        dismissed[l] = k;
        if(k!=-1)
            dismissed[k] = l;
        return true;

    }

    bool dismiss(int u, int v){
        u = find(u); v = find(v);
        if(u == v) return false;

        u = merge(u, dismissed[v]);
        v = merge(v, dismissed[u]);

        dismissed[u] = v;
        dismissed[v] = u;
        return true;
    }

    int maxSet(){
        int ret = 0;
        checked.clear();
        checked.resize(size.size(), true);
        for(int i=0; i<size.size(); ++i){
            int root = find(i);
            if(root == i){
                // checked[root] = false;
                int enemy = find(dismissed[root]);
                if(enemy > root) continue;
                int enemySize = (enemy == -1 ? 0 : size[enemy]);
                // if(enemy!= -1) checked[enemy] = false;
                ret += max(size[root], enemySize);
            }
        }
        return ret;
    }
};

int main(){
    int i,j,k, no_of_users, no_of_comments;
    string tmp;
    int u1, u2;
    int contradicted;
    int candidates[2] = {-1, -1};
    for(scanf("%d", &j), i=0; i<j; i++){
        contradicted = 0;
        cin >> no_of_users >> no_of_comments;
        DisjointSet* DJS = new DisjointSet(no_of_users);
        for(k=0; k<no_of_comments; k++){
            cin >> tmp >> u1 >> u2;
            if(contradicted)
                continue;
            if(tmp == "ACK"){
                if(!DJS->ack(u1, u2)){
                    contradicted = k + 1;
                }
            }
            else{
                if(!DJS->dismiss(u1, u2)){
                    contradicted = k + 1;
                }
            }
        }
        if(contradicted)
            printf("CONTRADICTION AT %d\n", contradicted);
        else{
            printf("MAX PARTY SIZE IS %d\n", DJS->maxSet());
        }
        delete DJS;
    }
}