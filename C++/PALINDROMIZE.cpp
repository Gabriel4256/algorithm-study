// KMP를 이용한 어렵지 않은 문제, 
// 결국 같은 문제라는 걸 알아채기 위해서는 약간의 통찰이 필요하다.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> getPartialMatch(const string &s){
    vector<int> pi(s.length(), 0);
    int begin = 1, match = 0;
    while(begin + match < s.size()){
        if(s[begin + match] == s[match]){
            ++match;
            pi[begin + match - 1] = match;
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
    return pi;
}

int findPDR(const string& s){
    int begin = 0, match = 0;
    int end = s.size() - 1;
    int max_subPDR = 0;
    string rev = s;
    reverse(rev.begin(), rev.end());
    vector<int> pi = getPartialMatch(rev);
    while(begin + match< s.size()){
        if(s[begin + match] == rev[match]){
            ++match;
            if(begin + match == s.size()){
                return 2 * s.size() - match;
                // max_subPDR = max(max_subPDR, end - begin + 1);
            }
        }
        else{
            if(match == 0)
                ++begin;
            else{
                begin += match - pi[match -1];
                match = pi[match - 1]; 
            }
        }
    }
    return 2 * s.size() - max_subPDR;
}

int main(){
    int i,j,k;
    string s;
    for(scanf("%d", &j), i=0; i<j; i++){
        cin >> s;
        cout << findPDR(s) << endl;
    }
}