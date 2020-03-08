// dijkstra 알고리즘을 활용한 문제
// 새로운 가상의 노드를 하나 추가하는 응용이 필요했다.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<pair<int, int>>> adj;

vector<int> dijkstra(int start){
    vector<int> dist;
    dist.resize(adj.size(), 101 * 1000);
    priority_queue<pair<int, int>> pq;

    dist[0] = 0;
    pq.push(make_pair(start, 0));

    while(!pq.empty()){
        pair<int, int> tmp = pq.top();
        pq.pop();
        int node_num = tmp.first;
        int cost = -tmp.second;

        for(int i=0; i<adj[node_num].size(); i++){
            int next_node = adj[node_num][i].first;
            int w = adj[node_num][i].second;
            if(w + cost < dist[next_node]){
                dist[next_node] = w + cost;
                pq.push(make_pair(next_node, -(w + cost))); 
            }
        }
    }

    return dist;
}

int solve(vector<int> fireplaces){
    int ret = 0;
    vector<int> dist = dijkstra(0);

    for(int i=0; i<fireplaces.size(); i++){
        ret += dist[fireplaces[i]];
    }
    return ret;
}

int main(){
    int i,j,k, V, E, n, m, a,b,w;
    vector<int> fireplaces;
    for(scanf("%d", &j), i=0; i<j; i++){
        fireplaces.clear();
        adj.clear();
        scanf("%d %d %d %d", &V, &E, &n, &m);
        adj.resize(V + 1);
        for(k=0; k<E; k++){
            scanf("%d %d %d", &a, &b, &w);
            adj[a].push_back(make_pair(b, w));
            adj[b].push_back(make_pair(a, w));
        }
        for(k=0; k<n; k++){
            cin >> a;
            fireplaces.push_back(a);
        }
        for(k=0; k<m; k++){
            cin >> a;
            adj[0].push_back(make_pair(a, 0));
            adj[a].push_back(make_pair(0, 0)); 
        }

        cout << solve(fireplaces) << endl;
    }
}