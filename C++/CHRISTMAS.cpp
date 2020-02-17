// 부분합 문제.
// 어려운 문제는 아니었지만, 생각을 잘못해서 0번째 부분합(항상 0)을 만들어줘야 하는 것을
// 생각하지 못했다. 무조건 0인 첫번째 부분합이 필요한지 부분합 문제를 풀 때는 잘 생각해보자

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int no_of_boxes, no_of_children;
int psum[100001];

int search1(){
    vector<long long> checked;
    checked.resize(no_of_children, 0);
    long long answer = 0;
    for(int i=0; i<no_of_boxes + 1; i++){
        checked[psum[i]]++;
    }
    for(int i=0; i<no_of_children; i++){
        if(checked[i] >=2)
        answer = (answer + (checked[i] * (checked[i] - 1)) / 2) % 20091101;
    }
    return answer;
}

int search2(){
    vector<int> prev, memo;
    memo.clear();
    prev.clear();
    prev.resize(no_of_children, -1);
    memo.resize(no_of_boxes + 1, 0);
    // memset(prev, -1, sizeof(prev));
    for(int i=0; i<no_of_boxes + 1; i++){
        if(i > 0)
            memo[i] = memo[i-1];
        else
            memo[i] = 0;
        
        int prev_idx = prev[psum[i]];
        if(prev_idx != -1) memo[i] = max(memo[i], memo[prev_idx] + 1);
        prev[psum[i]] = i;
    }
    return memo.back();
}

int main(){
    int i,j,k,l;
    for(scanf("%d", &j), i=0; i<j; i++){
        scanf("%d %d", &no_of_boxes, &no_of_children);
        psum[0] = 0;
        for(k=1; k<no_of_boxes+1; k++){
            cin >> l;
            psum[k] = (psum[k-1] + l) % no_of_children;
        }
        // search2();
        std::cout << search1() << " " << search2()<< std::endl;
    }
}