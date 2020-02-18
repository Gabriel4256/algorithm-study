// 간단한 queue 문제

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int K, N;


int search(){
    queue<long long> qu;
    long long prev_sig = -1;
    int ret = 0;
    long long cur_sum = 0;
    for(int i=0; i<N; i++){
        prev_sig = i == 0 ? 1983 : (prev_sig * 214013LL + 2531011LL) % (1LL << 32); 
        int input = prev_sig % 10000 + 1;
        cur_sum += input;
        qu.push(input);
        while(cur_sum >= K){
            if(cur_sum == K)
                ret++;
            cur_sum -= qu.front();
            qu.pop();
        }
    }
    return ret;
}

int main() {
    int i,j,k;
    for(scanf("%d", &j),i=0; i<j; i++){
        scanf("%d %d", &K, &N);
        cout << search() << endl;
    }
    return 0;
}