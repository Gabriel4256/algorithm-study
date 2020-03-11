// 크루스칼 / 프림 알고리즘을 이용한 minimum spanning tree를 찾는 문제
// 간단한 문제였다.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct DisJointSet{
    vector<int> parent, rank, size;
    DisJointSet(int n) : parent(n), rank(n, 1), size(n, 1){
        for(int i=0; i<n; i++){
            parent[i] = i;
        }
    }

    int find(int u){
        int i = u;
        while(parent[i] != i)
            i = parent[i];
        return parent[u] = i;
    }

    bool merge(int u, int v){
        u = find(u); v = find(v);
        if(u == v) return false;

        if(rank[u] < rank[v])
            swap(u, v);
        parent[v] = u;
        if(rank[v] == rank[u]){
            rank[v]++;
        }
        size[u] += size[v];
        return true;
    }
};

double kruskal(vector<pair<double, pair<int, int>>> edges){
    double ret = 0;
    
    sort(edges.begin(), edges.end());

    DisJointSet DJS(500);

    for(int i=0; i<edges.size(); i++){
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        double w = edges[i].first;

        if(DJS.find(u) == DJS.find(v)) continue;

        ret += w;
        DJS.merge(u, v);     
    }
    return ret;
}

double getDist(pair<int, int> a, pair<int, int> b){
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

vector<pair<double, pair<int, int>>> calculateDist(vector<pair<int,int>> points, vector<pair<int, int>> linked){
    vector<pair<double, pair<int, int>>> edges;
    
    for(int i=0; i<points.size(); i++){
        for(int j=0; j<points.size(); j++){
            if(i == j) continue;
            edges.push_back(make_pair(getDist(points[i], points[j]), make_pair(i, j)));
        }
    }
    for(int i=0; i<linked.size(); i++){
        edges.push_back(make_pair(0, make_pair(linked[i].first, linked[i].second)));
    }
    return edges;
}

int main(){
    int i,j,k, N, M;
    vector<int> posX, posY;
    vector<pair<int, int>> linked;
    for(scanf("%d", &j), i=0; i<j; i++){
        cin >> N >> M;
        posX.clear(); posY.clear();
        posX.resize(N); posY.resize(N);
        linked.clear();
        for(k=0; k<N; k++){
            cin >> posX[k];
        }
        for(k=0; k<N; k++){
            cin >> posY[k];
        }
        for(k=0; k<M; k++){
            int a,b;
            cin >> a >> b;
            linked.push_back(make_pair(a, b));
        }
        vector<pair<int, int>> points;
        for(k=0; k<N; k++){
            points.push_back(make_pair(posX[k], posY[k]));
        }
        auto edges = calculateDist(points, linked);
        cout.precision(10);
        cout << fixed;
        cout << kruskal(edges) << endl;
    }
}