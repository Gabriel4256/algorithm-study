// 접미사 배열을 이용한 문제였다.
// 아직은 접미사 배열을 활용하는 것이 익숙치 않다.
// 꼭 다시 한번 봐야 될 부분.
// 문자열

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Comparator {
    const vector<int> &group;
    int t;

    Comparator(const vector<int>& _group, int _t) : group(_group), t(_t){}

    bool operator () (int a, int b){
        if(group[a] != group[b]) return group[a] < group[b];
        
        return group[a+t] < group[b+t];
    }
};

vector<int> getSuffixArray(const string& s){
    int t = 1;
    int n = s.size();
    vector<int> group(n+1);
    for(int i=0; i<n; i++) group[i] = s[i];
    group[n] = -1;

    vector<int> perm(n);
    for(int i=0; i<n; i++) perm[i] = i;

    while(t < n){
        Comparator compareUsing2T(group, t);
        sort(perm.begin(), perm.end(), compareUsing2T);

        t *= 2;
        if(t >= n) break;

        vector<int> newGroup(n+1);
        newGroup[n] = -1;
        newGroup[perm[0]] = 0;
        for(int i=1; i<n; i++){
            if(compareUsing2T(perm[i-1], perm[i]))
                newGroup[perm[i]] = newGroup[perm[i-1]] + 1;
            else
                newGroup[perm[i]] = newGroup[perm[i-1]];
         }
         group = newGroup;
    }
    return perm;
}

//s[i..] 와 s[j..]의 공통 접두사의 길이를 계산
int commonPrefix(const string& s, int i, int j){
    int ret = 0;
    while(i < s.size() && j < s.size() && s[i] == s[j]){
        i++; j++; ret++;
    }
    return ret;
}

int maxSubstr(const string& s, int K){
    int ret = 0;
    vector<int> sufixarr = getSuffixArray(s);
    int n = sufixarr.size();

    for(int i=0; i + K <= n; i++){
        ret = max(ret, commonPrefix(s, sufixarr[i], sufixarr[i + K - 1]));
    }
    return ret;
}

int main(){
    int i,j,K;
    string s;
    for(scanf("%d", &j), i=0; i<j; i++){
        cin >> K >> s;
        cout << maxSubstr(s, K) << endl;
    }
}