// 양방향 BFS를 이용하여 푸는 문제, 어려운 문제는 아니었지만
// 최적화 측면에서 공을 좀 들여야 했다.
// 많이 실행되는 작은 연산들을 최대한 최적화 하는 것이 중요하다는 교훈을 얻었다.
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

const int MAX_DISKS = 12;

int visited[1 << ((MAX_DISKS)*2)];
int no_of_disks;

vector<int> getTop(int state){
    vector<int> ret = {100, 100, 100, 100};
    for(int i=0; i<no_of_disks; i++){
        int pos = (state & (3 << (2 * i))) >> (2 * i);
        ret[pos] = min(ret[pos], i);
    }
    return ret;
}

int move(int state, int disk_no, int pos){
    int cur_pos = state & (3 << disk_no * 2);
    return state - cur_pos +  (pos << (disk_no * 2));
}

int inc(int n){
    int plus = n > 0 ? 1 : -1;
    return n + plus;
}

int bfs(int here, int dest){
    queue<pair<int, int>> q;
    
    if(here == dest) return 0;

    visited[here] = 1;
    visited[dest] = -1;
    q.push(pair<int, int>(here, 1));
    q.push(pair<int, int>(dest, -1));

    while(!q.empty()){
        pair<int, int> tmp = q.front();
        q.pop();
        vector<int> tops = getTop(tmp.first);
        for(int i=0; i<4; i++){
            for(int j=0; j<4; j++){
                if(i == j || tops[i] >= tops[j]) continue;
                
                int next = move(tmp.first, tops[i], j);
                if(visited[next] == 0){
                    q.push(make_pair(next, inc(tmp.second)));
                    visited[next] = inc(tmp.second);
                }
                else if(next !=0 && signbit((float)visited[next]) != signbit((float)tmp.second)){
                    return abs(visited[next]) + abs(tmp.second) -1;
                }
            }
        }
    }
    return -1;
}

int getDest(){
    int ret = 0;
    for(int i=0; i<no_of_disks; i++){
        ret |= (3 << (2 * i));
    }
    return ret;
}

int main(){
    int i,j,k,l,m,n;
    for(scanf("%d", &j), i=0; i<j; i++){
        int start = 0;
        cin >> no_of_disks;
        memset(visited, 0, sizeof(visited));
        for(k=0; k<4; k++){
            cin >> l;
            for(m=0; m<l; m++){
                cin >> n;
                start |= (k << (2 * (n-1)));
            }
        }

        cout << bfs(start, getDest()) << endl;
    }
}