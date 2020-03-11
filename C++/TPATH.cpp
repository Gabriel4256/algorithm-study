// 최소 너비(width) spanning tree를 구하는 문제.
// 하한값을 미리 설정해두고 탐색을 하는 것이 키포인트였다.
// 아이디어를 떠올리면 쉬운 문제이지만, 아이디어가 떠오르지 않아 힘들었다..

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// vector<pair<int, int>> adj[2000];

struct DisjointSet{
    vector<int> size, rank, parent;

    DisjointSet(int n): size(n, 1), rank(n,1), parent(n){
        for(int i=0; i<n; i++){
            parent[i] = i;
        }
    }

    int find(int u){
        int i = u;
        while(i!=parent[i])
            i = parent[i];
        return parent[u] = i;
    }

    void merge(int u, int v){
        u = find(u); v = find(v);

        if(u == v) return;

        if(u < v) swap(u,v);
        if(rank[u] == rank[v]) rank[u]++;
        size[u] += size[v];
        parent[v] = u;
        return;
    }
};

int solve(int N, vector<pair<int, pair<int,int>>> &edges){
    sort(edges.begin(),edges.end());
    int prev_min = -1;
    int ret = 1e9;
    // vector<pair<bool, int>> memo();

    for(int i=0; i<edges.size(); i++){
        if(edges[i].first == prev_min) continue;
        prev_min = edges[i].first;
        DisjointSet DJS(N);
        DJS.merge(edges[i].second.first, edges[i].second.second);
        if(DJS.find(0) == DJS.find(N-1)){
            return 0;
        }
        for(int j= i + 1; j<edges.size(); j++){
            DJS.merge(edges[j].second.first, edges[j].second.second);
            if(DJS.find(0) == DJS.find(N-1)){
                ret = min(ret, edges[j].first - edges[i].first);
                break;
            }
        }
    }

    return ret;
}

int main(){
    int i,j,k, N, M;
    vector<pair<int, pair<int,int>>> edges;
    for(scanf("%d", &j), i=0; i<j; i++){
        edges.clear();
        cin >> N >> M;
        for(k=0; k<M; k++){
            int u,v,w;
            cin >> u >> v >> w;
            edges.push_back(make_pair(w, make_pair(u,v)));
        }
        cout << solve(N, edges) << endl;
    }
}