// 채점 사이트에 문제가 안올라와있어서 검증은 받지 못했다.
// 주어진 문제를 유량 네트워크로 구성하고 컷으로 나누는 생각을 하는 것이 키포인트 였다.
// 역시 익숙치 않아 그런지 생각해낼 수 없었다.

#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

#define MAX_V 1000
const int INF = 1e9;
int capacity[MAX_V][MAX_V];
int flow[MAX_V][MAX_V];
// int V;
int N, M;

int networkFlow(int src, int sink){
    int totalFlow = 0;
    queue<int> q;
    memset(flow, 0, sizeof(flow));

    while(true){
        q.push(src);
        vector<int> parent(N + M + 2, -1);

        while(!q.empty()){
            int here = q.front(); q.pop();

            for(int there = 0; there<N + M + 2; there++){
                if(capacity[here][there] > flow[here][there] && parent[there] == -1){
                    q.push(there);
                    parent[there] = here;
                }
            }
        }

        if(parent[sink] == -1) break;
        int amount = INF;
        for(int i = sink; i != src; i = parent[i]){
            amount = min(amount, capacity[parent[i]][i] -  flow[parent[i]][i]);
        }

        for(int i= sink; i!=src; i = parent[i]){
            flow[parent[i]][i] += amount;
            flow[i][parent[i]] -= amount;
        }
        totalFlow += amount;
    }

    return totalFlow;
}

int main(){
    int i,j,k,l, a,b, total_earnings;
    for(scanf("%d", &j), i=0; i<j; i++){
        memset(capacity, 0, sizeof(capacity));
        total_earnings = 0;
        cin >> N >> M;
        for(k=0; k<N; k++){
            cin >> capacity[0][2 + k];
            total_earnings += capacity[0][2 + k];
        }
        for(k=0; k<M; k++){
            cin >> capacity[2 + N + k][1];
        }
        for(k=0; k<N; k++){
            for(l=0; l<M; l++){
                cin >> a;
                if(a == 1){
                    capacity[2 + k][2 + N + l] = INF;
                }
            }
        }
        cout << total_earnings - networkFlow(0, 1) << endl; 
    }
}