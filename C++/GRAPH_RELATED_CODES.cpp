// 이 파일은 그래프 부분의 코드들을 모아놓은 것에 불과하다.
// 실행이나 테스트는 X

// 깊이 우선 탐색
#include <vector>
#include <iostream>

vector<bool> visited;

// dfs 탐색
void dfs(int here){
    visited[here] = true;
    
    // 모든 인접 정점을 순회
    for(int i=0; i< adj[here].size(); ++i){
        int there = adj[here][i];

        if(!visited[there])
            dfs(there)
    }
}

//위상 정렬
vector<int> topologicalSort(){
    int n = adj.size();
    seen = vector<int>(n,0);
    order.clear();
    for(int i=0; i<n; ++i) if(!seen[i]) dfs(i);
    reverse(order.begin(), order.end())

    //만약 그래프가 DAG가 아니라면 정렬 결과에 역방향 간선이 있다.
    for(int i=0; i<n; i++){
        for(int j= i + 1; j < n; j++)
            if(adj[order[j]][order[i]])
                return vector<int>();
    }

    //없는 경우라면 깊이 우선 탐색에서 얻은 순서를 반환
    return order;
}


// 오일러 서킷
// 방향 그래프의 경우
// 만일 방향이 없는 그래프라면 adj를 한번씩만 업데이트 해주면 된다.
// 또한, 오일러 트레일을 찾고 싶은 경우라면 간선의 개수가 홀수인
// 시작점을 찾아서 그 점을 시작으로 탐색한다.
void getEulerCircuit(int here, vector<int>& circuit){
    for(int there = 0; there < adj.size(); there++){
        while(adj[here][there] > 0){
            adj[here][there]--;
            adj[there][here]--;
            getEulerCircuit(there, circuit);
        }
    }
    circuit.push_back(here);
}

// 간선 구분
/*
	1. 트리 간선: 스패닝 트리에 포함된 간선
	2. forward edge(순방향 간선): 스패닝 트리의 선조에서 자손으로 연결되지만 트리 간선이 아닌 간선
	3. back edge(역방향 간선): 스패닝 트리의 자손에서 선조로 연결되는 간선
    4. cross edge(교차 간선): 1,2,3에 해당하지 않는 나머지 간선들
*/

void dfs2(int here){
    discovered[here] = counter++;

    //모든 인접 정점을 순회하면서
    for(int i=0; i < adj[here].size(); i++){
        int there = adj[here][i];

        // 아직 방문한 적 없다면 방문한다.
        if(discovered[there] == -1){
            // tree edge
            dfs2(there);
        }

        //만약 there가 here보다 늦게 발견됐으면 there는 here의 후손이다.
        else if(discovered[here] < discovered[there])
            // forward edge
            cout << "forward edge" << endl;
        
        //만약 dfs2(there)가 아직 종료하지 않았다면 there는 here의 선조다
        else if(finished[there] == 0)
            // back edge

        // 이 외의 경우는 모두 교차 간선
        else
        {

        }
        finished[here] = 1;
    }
}

// 절단점 찾기
int findCutVertex(int here, bool isRoot){
    //발견 순서를 기록한다.
    discovered[here] = counter++;
    int ret = discovered[here];

    //루트인 경우 절단점 판정을 위해 자손 서브트리의 개수를 센다.
    int children = 0;
    for(int i=0; i < adj[here].size(); i++){
        int there = adj[here][i];
        if(discovered[there] == -1){
            ++children;

            // 이 서브트리에서 갈 수 있는 가장 높은 정점의 번호
            int subtree = findCutVertex(there, false);

            //그 번호가 자기 자신 이하라면 현재 위치는 절단점
            if(!isRoot && subtree >= discovered[here])
                isCutVertex[here] = true;
            ret = min(ret, subtree);
        }
        else
            ret = min(ret, discovered[there]);
    }

    // 루트인 경우 절단점 판정은 서브트리의 개수로 한다.
    if(isRoot) isCutVertex[here] = (children >= 2);
    return ret;
}
