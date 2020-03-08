// dijkstra 알고리즘을 이용하는 응용문제, 꽤 어려운 문제였다.
// 어떻게 하면 최대한 상태(노드들)를 간단하게 표현할 수 있을지 고민하자

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> dist;
vector<vector<pair<int, int>>> adj;

int vertex(int n){
    return n + 200;
}

void dijkstra(int start){
    priority_queue<pair<int, int>> pq;  //# node, cost
    dist.clear();
    dist.resize(adj.size(), 1e9);

    dist[start] = 0;
    pq.push(make_pair(start, 0));
    
    while(!pq.empty()){
        auto tmp = pq.top();
        int node_num = tmp.first;
        int cost = -tmp.second;
        pq.pop();
        if(cost > dist[node_num]) continue;

        for(int i=0; i<adj[node_num].size(); i++){
            int there = adj[node_num][i].first;
            int nextDis = cost + adj[node_num][i].second;

            if(nextDis < dist[there]){
                dist[there] = nextDis;
                pq.push(make_pair(there, -nextDis));
            }
        }
    }
}

void makeGraph(vector<pair<int, int>> &records){
    adj.clear();
    adj.resize(402);
    queue<int> q;

    for(int i=-200; i<201; i++){
        for(int j=0; j<records.size(); j++){
            int diff = records[j].first - records[j].second;
            if(i * diff <= 0){
                int next = i + diff == 0 ? 401 : vertex(i + diff);
                adj[vertex(i)].push_back(make_pair(next, records[j].first));
            }
        }
    }
}

int solve(vector<pair<int, int>> &records){
    makeGraph(records);
    dijkstra(vertex(0));
    return dist[401];
}

int main(){
    int i,j,k, M;
    vector<pair<int, int>> records;
    for(scanf("%d", &j), i=0; i<j; i++){
        records.clear();
        cin >> M;
        for(k=0; k<M; k++){
            int a,b;
            cin >> a >> b;
            records.push_back(make_pair(a, b));
        }
        int ans = solve(records);
        if(ans < 1e9)
            cout << ans << endl;
        else
            cout << "IMPOSSIBLE" << endl;
    }
}