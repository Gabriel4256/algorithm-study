// KMP 알고리즘을 이용하는 문제, KMP를 알고 있다면 그리 어렵지 않게 풀 수 있는 문제였다.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> getPartialMatch(const string& N){
    // pi[i]는 0부터 i번째 까지의 문자를 포함하는 문자열의 가장 긴 접두사이자 접미사의 길이를 의미
    vector<int> pi(N.length(), 0);

    int begin = 1;
    int match = 0;
    while(begin + match < N.size()){
        if(N[begin + match] == N[match]){
            //일치하는 경우
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

vector<int> getLengths(const vector<int>& pi){
    vector<int> ret;
    int k = pi[pi.size() - 1];
    while(k > 0){
        ret.push_back(k);
        k = pi[k-1];
    }
    return ret;
}

int main(){
    int i,j,k;
    string s1, s2;
    // for(scanf("%d", &j), i=0; i<j; i++){
    cin >> s1 >> s2;
    vector<int> ans = getLengths(getPartialMatch(s1 + s2));
    sort(ans.begin(), ans.end());
    for(k=0; k<ans.size(); k++)
        cout << ans[k] << " ";
    cout << (s1+ s2).length() << endl;
    // }
}