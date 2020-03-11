// 플로이드 워샬 알고리즘을 이용하여 푸는 문제.
// 그닥 어렵지 않았다.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int INF = 1e9;
int adj[200][200];
int W[200][200];

int floyd(int N, vector<pair<pair<int, int>, int>> edges){
    int cnt = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(i == j) W[i][j] = 0;
            else{
                W[i][j] = adj[i][j];
            }
        }
    }

    for(int k=0; k<N; k++){
        for(int i = 0; i<N; i++){
            for(int j=0; j<N; j++){
                W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
            }
        }
    }

    for(int i=0; i<edges.size(); i++){
        int a = edges[i].first.first;
        int b = edges[i].first.second;
        int w = edges[i].second;
        if(W[a][b] > w){
            W[a][b] = w;
            W[b][a] = w;
            for(int j=0; j<N; j++){
                for(int k=0; k<N; k++){
                    W[j][k] = min(W[j][k], W[j][a] + w + W[b][k]);
                    W[j][k] = min(W[j][k], W[j][b] + w + W[a][k]);
                }
            }
        }
        else{
            cnt++;
        }
    }
    return cnt;
}

int main(){
    int i,j,k, V, M, N;
    vector<pair<pair<int, int>, int>> extra_edges;
    for(scanf("%d", &j), i=0; i<j; i++){
        extra_edges.clear();
        fill(&adj[0][0], &adj[199][200], INF);
        cin >> V >> M >> N;
        for(k=0; k<M; k++){
            int a,b, w;
            cin >> a >> b >> w;
            adj[a][b] = min(adj[a][b], w);
            adj[b][a] = min(adj[b][a], w);
        }
        for(k=0; k<N; k++){
            int a,b,w;
            cin >> a >> b >> w;
            extra_edges.push_back(make_pair(make_pair(a,b), w));
        }
        cout << floyd(V, extra_edges) << endl;
    }
}