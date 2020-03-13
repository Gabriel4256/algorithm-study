// 포드 폴커슨 알고리즘을 활용한 문제.
// 주어진 문제를 어떻게 네트워크 유량 문제로 바꿀 것인지가 키포인트였다.
// 아직 낯설어서 그런지 체감 난이도는 매우 높았다.

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define MAX_V 2000

const int INF = 1e9;
int N, M;

int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

int networkFlow(int src, int sink, int max_wins){
    memset(flow, 0, sizeof(flow));
    int totalFlow = 0;

    queue<int> q;
    int add_wins = 0;

    while(add_wins <= max_wins){
        while(true){
            vector<int> parent(N + M + 2, -1);
            q.push(src);

            while(!q.empty()){
                int here = q.front(); q.pop();
                for(int there=0; there<N+M+2; there++){
                    if(capacity[here][there] > flow[here][there] && parent[there] == -1){
                        parent[there] = here;
                        q.push(there);
                    }
                }
            }

            if(parent[sink] == -1) break;
            int amount = INF;

            for(int i = sink; i != src; i = parent[i]){
                amount = min(amount, capacity[parent[i]][i] - flow[parent[i]][i]);
            }

            for(int i= sink; i != src; i = parent[i]){
                flow[parent[i]][i] += amount;
                flow[i][parent[i]] -= amount;
            }

            totalFlow += amount;
        }

        if(totalFlow == M) break;
        for(int i=0; i<N; i++){
            capacity[i + 2][1]++;
        }
        add_wins++;
    }

    if(add_wins > max_wins) return -1;
    
    return add_wins;
}

void makeGraph(vector<int> &wins, vector<pair<int, int>> &matches, int min_wins){
    // source는 0, sink는 1번째 node
    // int N = wins.size();
    memset(capacity, 0, sizeof(capacity));
    // matches to players, source to matches
    for(int i=0; i<matches.size(); i++){
        int p1 = matches[i].first, p2 = matches[i].second;
        capacity[2 + N + i][p1+ 2] = 1;
        capacity[2 + N + i][p2 + 2] = 1;
        capacity[0][2 + N + i] = 1;
    }

    //players to sink, 0번째 플레이어만 1로 시작, 나머지는 0으로 시작.
    capacity[2][1] = min_wins - wins[0];
    for(int i=1; i<N; i++){
        capacity[2 + i][1] = min_wins - 1 - wins[i]; 
    }
}

int min_wins(vector<int> &wins, vector<pair<int, int>> &matches){
    // 0번 player가 최소한 이겨야 하는 승수를 반환
    int cnt = 0, max_val = 0;
    for(int i=0; i<N; i++){
        if(max_val < wins[i]){
            cnt = 1;
            max_val = wins[i];
        }
        else if(max_val == wins[i]){
            cnt++;
        }
    }
    if(cnt > 1 || wins[0] != max_val)
        max_val++;
    
    return max_val;
}

int main(){
    int i,j,k, max_wins;
    vector<int> wins;
    vector<pair<int, int>> matches;
    for(scanf("%d", &j), i=0; i<j; i++){
        max_wins = 0;
        wins.clear();
        matches.clear();
        cin >> N >> M;
        wins.resize(N);
        for(k=0; k<N; k++){
            cin >> wins[k];
        }
        for(k=0; k<M; k++){
            int a,b;
            cin >> a >> b;
            if(a == 0 || b == 0) max_wins++;
            matches.push_back(make_pair(a,b));
        }
        int min_w = min_wins(wins, matches);
        makeGraph(wins, matches, min_w);
        int ans = networkFlow(0, 1, max_wins + wins[0] - min_w);
        if(ans == -1) cout << ans << endl;
        else cout << ans + min_w << endl;
    }
}