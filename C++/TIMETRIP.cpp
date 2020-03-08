// 벨만 포드 알고리즘을 이용해 푸는 비교적 간단한 문제.
// 쉽게 풀 수 있었다. 다만, reachable과 INFINITY의 우선순위를 잘 따져야 했다.

#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;
vector<vector<pair<int, int>>> adj;

vector<int> bellmanFord(int start, int w){
    vector<int> upper(adj.size(), INF);
    upper[start] = 0;
    bool updated = false;

    for(int i=0; i<adj.size(); i++){
        updated = false;
        for(int here=0; here<adj.size(); here++){
            for(int k=0; k<adj[here].size(); k++){
                int there = adj[here][k].first;
                int cost = w * adj[here][k].second;
                if(upper[here] + cost < upper[there]){
                    upper[there] = upper[here] + cost;
                    updated = true;
                }
            }
        }
        if(!updated) break;
    }
    if(updated && upper[1] < 1e7) upper.clear();
    return upper;
}

pair<int, int> solve(int src, int dest){
    vector<int> min_dist = bellmanFord(src, 1);
    vector<int> max_dist = bellmanFord(src, -1);
    int least, last;
    if(min_dist.size() == 0){
        least = 1e9; //INFINITY
    }
    else if(min_dist[dest] > 1e7){
        return make_pair(-1e9, -1e9); // Unreachable
    }
    else{
        least = min_dist[dest];
    }

    if(max_dist.size() == 0){
        last = 1e9; //INFINITY
    }
    else{
        last = -max_dist[dest];
    }

    return make_pair(least, last);

}

int main(){
    int i,j,k, V, E;
    for(scanf("%d", &j), i=0; i<j; i++){
        adj.clear();
        cin >> V >> E;
        adj.resize(V);
        for(k=0; k<E; k++){
            int a,b,c;
            cin >> a >> b >> c;
            adj[a].push_back(make_pair(b, c));
        }

        pair<int, int> ans = solve(0, 1);
        if(ans.first == -1e9){
            cout << "UNREACHABLE" << endl;
            continue;
        }
        else{
            if(ans.first == 1e9) cout << "INFINITY " ;
            else cout << ans.first << " ";

            if(ans.second == 1e9) cout << "INFINITY" << endl;
            else cout << ans.second << endl;
        }
    }
}