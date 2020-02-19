//어렵지 않은 KMP 활용 문제
//시계, 반시계 두가지 방향을 모두 따져야 하는데, 함수를 따로 만들 필요 없이
//shifts 함수에 두 문자열 입력을 다른 순서대로 넣어주면 반대방향이 된다는 것을 
//인지하는 것이 포인트! 

#include <iostream>
#include <vector>
using namespace std;

vector<int> getPartialMatch(const string &s){
    vector<int> pi(s.size(), 0);
    int begin = 1, match = 0;
    while(begin + match < s.size()){
        if(s[match] == s[begin + match]){
            ++match;
            pi[begin + match - 1] = match;
        }
        else{
            if(match == 0)
                ++begin;
            else{
                begin += match - pi[match-1];
                match = pi[match-1];
            }
        }
    }
    return pi;
}

int shifts(const string &s1, const string &s2){
    int begin = 0; 
    int match = 0;
    vector<int> pi = getPartialMatch(s2);
    while(begin < s1.length()){
        if(s1[(begin + match) % s1.length()] == s2[match]){
            ++match;
            if(match == s1.length())
                return begin;
        }
        else{
            if(match == 0)
                ++begin;
            else{
                begin += match - pi[match - 1];
                match = pi[match - 1];
            }
        }
    }
    return -1;
}

int main() {
    int i,j,k, N;
    vector<string> s;
    for(scanf("%d", &j), i=0; i<j; i++){
        cin >> N;
        s.resize(N+1);
        for(k=0; k<N+1; k++){
            cin >> s[k];
        }
        int ans = 0;
        for(k=0; k<N; k++){
            if(k % 2 == 0)
                ans += shifts(s[k+1], s[k]);
            else
                ans += shifts(s[k], s[k+1]);
        }
        cout << ans << endl;
    }
    return 0;
}