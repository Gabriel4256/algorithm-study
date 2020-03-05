// BFS를 이용하여 푸는 문제.
// 뭔가 참신하면서도 간단한 방법이 있을 줄 알았는데, 그냥 일일히 하는거였다.
// 수열의 길이가 최대 8이라는 점을 주목해서 팩토리얼을 취해도 그렇게 커지지 않는다는 것을
// 알아챘어야 했는데...
// 또한 전처리 과정도 눈여겨 보자

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
using namespace std;

map<vector<int>, int> dist;


void bfs(vector<int>& start){
    queue<vector<int>> qu;
    qu.push(start);
    dist[start] = 0;

    while(!qu.empty()){
        auto here = qu.front();
        qu.pop();
        for(int i= 2; i<here.size() + 1; i++){
            for(int j=0; j<here.size() - i + 1; j++){
                auto tmp = here;
                reverse(tmp.begin() + j, tmp.begin() + j + i);
                if(dist.count(tmp) == 0){
                    dist[tmp] = dist[here] + 1;
                    qu.push(tmp);
                }
            }
        }
    }
}

void preCalculate(){
    dist.clear();
    for(int i=1; i<9; i++){
        vector<int> start;
        for(int j=0; j<i; j++)
            start.push_back(j);
        bfs(start);
    }
}

void convert(vector<int>& nums){
    vector<int> tmp = nums;
    sort(tmp.begin(), tmp.end());
    for(int i=0; i<nums.size(); i++){
        auto it = find(tmp.begin(), tmp.end(), nums[i]);
        nums[i] = std::distance(tmp.begin(), it);
    }
}

int solve(vector<int>& nums){
    convert(nums);
    return dist[nums];
}

int main(){
    int i,j,k,l,m;
    preCalculate();
    for(scanf("%d", &j), i=0; i<j; i++){
        vector<int> nums;
        cin >> k;
        for(l=0; l<k; l++){
            cin >> m;
            nums.push_back(m);
        }
        cout << solve(nums) << endl;
    }
}