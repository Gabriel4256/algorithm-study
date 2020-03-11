// 기본적인 아이디어 자체는 쉽게 떠오르는 문제였지만 세부적인 부분에서 어려웠다.
// 통행료 순으로 노드를 정렬해서 그 순서대로 set에 추가를 함으로써, 전체 경로의 통행료를 
// 쉽게 정할 수 있게 한 것이 주요한 아이디어였다.
// 책을 참고하기 전까지는 내 방식이 왜 틀렸는지 이해하기 어려웠다.

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

const int INF = 1e9;
int adj[501][501];
int W[501][501];

void floyd(int V, int* extras){
    // for(int i=1; i<V+1; i++) adj[i][i] = 0;
    vector<pair<int, int>> delays;
    // delays.resize(V+1);
    for(int i=1; i<V+1; i++){
        delays.push_back(make_pair(extras[i], i));
    }
    sort(delays.begin(), delays.end());
    
    for(int i=1; i<V+1; i++){
        for(int j=1; j<V+1; j++){
            if(i == j) W[i][j] = 0;
            else{
                W[i][j] = adj[i][j];
            }
        }
    }
    for(int k=0; k<V; k++){
        for(int i=1; i<V+1; i++){
            for(int j=1; j<V+1; j++){
                int w = delays[k].second;
                
                adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
                
                W[i][j] = min(W[i][j], adj[i][w] + adj[w][j] + extras[w]);
            }
        }
    }
}

int solve(int src, int dest){
    return W[src][dest];
}

int main(){
    int i,j,k,l,V, E;
    int extras[501];
    cin >> V >> E;
    for(i=0; i<501; i++){
        for(j=0; j<501; j++){
            adj[i][j] = INF;
        }
    }
    for(k=1; k<V + 1; k++){
        cin >> extras[k];
    }
    for(k=0; k<E; k++){
        int a,b,c;
        cin >> a >> b >> c;
        adj[a][b] = c;
        adj[b][a] = c;
    }
    cin >> l;
    floyd(V, extras);
    for(k=0; k<l; k++){
        cin >> i >> j;
        cout << solve(i, j) << endl;
    }
}