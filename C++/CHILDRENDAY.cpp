// BFS와 약간의 정수론 지식을 활용하여 푸는 문제.
// 난이도는 상이었지만, 체감상 그리 어렵지는 않았다.
// 나머지를 계산할 때 뒤에 붙여가는 느낌으로 할건지, 앞에 붙이는 느낌으로 할건지
// 이 순서를 잘 정해야 그래프로 나타내기 쉽기 때문에, 이 부분이 주요했다.

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

vector<bool> visited;

bool compare(vector<int> &digits, int min_val){
    int tmp = min_val;
    int digit_cnt = 0;
    while(tmp){
        tmp /= 10;
        digit_cnt++;
    }
    if(digits.size() > digit_cnt)
        return true;
    else if(digits.size() < digit_cnt)
        return false;
    else{
        int num = 0;
        for(int i=0; i<digits.size(); ++i){
            num += digits[i] * pow(10, digits.size() - i - 1);
        }
        return num >= min_val;
    }
}

bool test(vector<int>& t){
    string target = "35355353545";
    for(int i=0; i<t.size(); i++){
        if(t[i] + 48 != target.at(i))
            return false;
    }
    return true;
}

vector<int> bfs(vector<int>& digits, int quo, int min_val, int remainder){
    queue<pair<int, vector<int>>> q;
    visited.clear();
    visited.resize(quo, false);

    for(int i=0; i<digits.size(); i++){
        vector<int> tmp;
        tmp.push_back(digits[i]);
        q.push(pair<int, vector<int>>((digits[i]) % quo, tmp));
        visited[digits[i] % quo] = true;
    }
    while(!q.empty()){
        pair<int, vector<int>> tmp = q.front();
        q.pop();
        // if(test(tmp.second)){
        //     printf("d\n");
        // }
        for(int i=0; i<digits.size(); i++){
            int next = (tmp.first * 10 + digits[i]) % quo;
            if(!visited[next] || next == remainder){
                vector<int> next_num = tmp.second;
                next_num.push_back(digits[i]);
                q.push(pair<int, vector<int>>(next, next_num));
                visited[next] = true;

                if(remainder == next && compare(next_num, min_val))
                    return next_num;
            }
        }
    }
    return vector<int>();
}

vector<int> convert(string digits){
    vector<int> ret;
    for(int i=0; i<digits.length(); i++){
        ret.push_back(digits.at(i) - 48);
    }
    return ret;
}

void print_digits(vector<int>& digits){
    for(int i=0; i<digits.size(); i++)
        printf("%d", digits[i]);
    printf("\n");
}

int main(){
    int i,j,k, N, M;
    string digits;
    for(scanf("%d", &j), i=0; i<j; i++){
        cin >> digits >> N >> M;
        vector<int> digs = convert(digits);
        sort(digs.begin(), digs.end());
        vector<int> ans = bfs(digs, N, M + N, M);
        if(ans.size() == 0)
            cout << "IMPOSSIBLE" << endl;
        else
            print_digits(ans);
    }   
}