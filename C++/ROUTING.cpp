// 간단한 다익스트라 알고리즘 활용 문제

#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

const int INF = 20000;
vector<vector<pair<int, double>>> adj;
vector<double> dist;

void dijkstra(int src){
    dist.clear();
    dist.resize(adj.size(), INF);
    vector<int> ret;
    priority_queue<pair<int, double>> pq;

    pq.push(make_pair(src, 0));
    dist[src] = 0;

    while(!pq.empty()){
        pair<int, double> tmp = pq.top();
        int no = tmp.first;
        double cost = -tmp.second;
        pq.pop();
        if(cost > dist[no]) continue;

        for(int i=0; i< adj[no].size(); i++){
            int there = adj[no][i].first;
            double nextDis = cost + adj[no][i].second;

            if(nextDis < dist[there]){
                dist[there] = nextDis;
                pq.push(make_pair(there, -nextDis));
            }
        }
    }
}

int main(){
    int i,j,k, nodes, edges;
    for(scanf("%d", &j), i=0; i<j; i++){
        cin >> nodes >> edges;
        adj.clear();
        adj.resize(nodes);

        for(k=0; k<edges; k++){
            int a,b;
            float c;
            cin >> a >> b >> c;
            adj[a].push_back(make_pair(b, log10(c)));
            adj[b].push_back(make_pair(b, log10(c)));
        }

        dijkstra(0);
        cout.precision(11);
        cout << fixed;
        cout << pow((double)10,dist[nodes-1]) << endl; 
    }
}