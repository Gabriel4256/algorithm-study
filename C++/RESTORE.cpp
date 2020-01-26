// 전반적인 풀이 방법은 생각을 잘 했으나, 바로 전 단어만 알고도 caching이 가능하도록
// 하려면 다른 단어에 포함되는 단어들을 다 제거하고 시작해야 한다.
// 이 아이디어 없이 하려다 보니 함수가 많이 복잡해졌었다.
// 언제쯤이면 이런 아이디어까지 생각해 내 빈틈없이 문제를 풀 수 있을까....

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>

using namespace std;

string combine(int, int);
string reconstruct(int, int, int);

vector<string> words;
int memo[(1<<16) + 1][15];

int main(){
    int i,j,k,l;
    vector<string> tmp;
    for(i=0, scanf("%d", &j); i<j; i++){
        words.clear();
        tmp.clear();
        memset(memo, -1, sizeof(memo));
        for(l=0,scanf("%d", &k); l<k; l++){
            string word;
            cin >> word;
            words.push_back(word);
        }

        int to_be_deleted[15];
        memset(to_be_deleted, -1, sizeof(to_be_deleted));
        int idx = 0;
        for(k=0; k<words.size(); k++){
            for(l=k+1; l<words.size(); l++){
                if(words[k].find(words[l]) != string::npos){
                    to_be_deleted[l] = 1;
                }
                else if(words[l].find(words[k]) != string::npos){
                    to_be_deleted[k] = 1;
                }
            }
        }

        for(k=0; k<words.size(); k++){
            if(to_be_deleted[k] == -1){
                tmp.push_back(words[k]);
            }
        }
        words = tmp;
        std::cout << reconstruct(1<<15, -1, words.size()-1) << std::endl;
    }
    return 0;
}

string combine(int idx1, int idx2){
    if(idx1 == -1)
        return words[idx2];
    int interleaving = 0;
    string tmp = words[idx1];
    // reverse(tmp.begin(), tmp.end());
    int len = words[idx1].length();
    for(int i=0; i< min(words[idx1].size(), words[idx2].size()); i++){
        if(words[idx1].substr(len - i - 1) == words[idx2].substr(0, i+1)){
            interleaving = i + 1;
        }
    }
    return words[idx2].substr(interleaving);
}

int get_min_len(int chosen, int prev_word_idx, int level){
    
    int& result = prev_word_idx != -1? memo[chosen][prev_word_idx]: memo[1 << 16][0];
    if(result != -1)
        return result;
    if(level == -1)
        return 0;
    result = 600;
    for(int i=0; i<words.size(); i++){
        if((chosen & (1 << i)) != (1 << i)){
            int modified_chosen = chosen | (1 << i);
            string combined = combine(prev_word_idx, i);
            result = min(result, (int)combined.size() + get_min_len(modified_chosen, i, level -1));
        }
    }
    return result;
}

string reconstruct(int chosen, int prev_word_idx, int level){
    if(level == -1)
        return "";
    int target = get_min_len(chosen, prev_word_idx, level);
    for(int i=0; i< words.size(); i++){
        if((chosen & (1 << i)) != (1 << i)){
            int modified_chosen = chosen | (1 << i);
            string combined = combine(prev_word_idx, i);
            if(target == combined.size() + get_min_len(modified_chosen, i, level - 1)){
                return combined + reconstruct(modified_chosen, i, level-1);
            }
        }
    }
}