// 그렇게 어려운 문제는 아닌데, CPP의 사용법 때문에 힘들었던 문제.
// Underflow를 막기 위해 log를 취하고, 곱하기를 덧셈으로 바꾸는 방식은 잘 기억해두자.
// 파이썬으로도 어떻게 되는거 같긴 한데, 알 수 없는 이유때문에 Nonzero return code가 뜬다.
// 조건부 확률이 잘 기억나진 않았지만, 그냥 본능대로 식을 세워 푸니 맞았다.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;


#define INF 999999.0
int no_of_word, no_of_sentence, sen_len;
string ind_to_word[501], sen[102];
double first_word_prob[501], next_word_prob[501][501], wrong_word_prob[501][501], memo[501][101];
double get_prob(int, int);
void reconstruct(int, int, string&);

int main() {
    int i,j,k;
    scanf("%d %d", &no_of_word, &no_of_sentence);
    for(i=0; i<no_of_word; i++)
        cin >> ind_to_word[i];
    for(i=0; i<no_of_word; i++){
        cin >> first_word_prob[i];
        first_word_prob[i] = log(first_word_prob[i]);
    }
    for(i=0; i<no_of_word; i++){
        for(j=0; j<no_of_word; j++){
            cin >> next_word_prob[i][j];
            next_word_prob[i][j] = log(next_word_prob[i][j]);
        }
    }
    for(i=0; i<no_of_word; i++){
        for(j=0; j<no_of_word; j++){
            cin >> wrong_word_prob[i][j];
            wrong_word_prob[i][j] = log(wrong_word_prob[i][j]);
        }
    }
    for(i=0; i<no_of_sentence; i++){
        cin >> sen_len;
        for(j=0; j<sen_len; j++){
            cin >> sen[j];
        }
        // fill(begin(memo), end(memo), 1.0);
        for(k=0; k<501; k++){
            for(int l=0; l<101; l++){
                memo[k][l] = 1;
            }
        }
        // memset(memo, 1, sizeof(memo));
        string answer = "";
        reconstruct(0, 0, answer);
        std::cout << answer << std::endl;
    }
    return 0;
}

double get_prob(int s_index, int prev_word_ind){
    int i;
    if(s_index >= sen_len){
        return 1.0;
    }
    double& result = memo[prev_word_ind][s_index];
    if(result != 1)
        return result;
    result = -INF;
    int cur_word_ind = distance(ind_to_word, find(ind_to_word, ind_to_word + 501, sen[s_index]));
    if(s_index == 0){
        for(i=0; i<no_of_word; i++){
            double cur_prob = first_word_prob[i] + wrong_word_prob[i][cur_word_ind];
            result = max(result, cur_prob + get_prob(s_index + 1, i));
        }
    }
    else{
        for(i=0; i<no_of_word; i++){
            double cur_prob = next_word_prob[prev_word_ind][i] + wrong_word_prob[i][cur_word_ind];
            result = max(result, cur_prob + get_prob(s_index + 1, i));
        }
    }
    return result;
}

void reconstruct(int s_index, int prev_word_ind, string &answer){
    int i;
    if(s_index >= sen_len)
        return;
    int cur_word_ind = distance(ind_to_word, find(ind_to_word, ind_to_word + 501, sen[s_index]));
    if(s_index == 0){
        for(i=0; i<no_of_word; i++){
            double cur_prob = first_word_prob[i] + wrong_word_prob[i][cur_word_ind];
            double result = cur_prob + get_prob(s_index + 1, i);
            if(result == get_prob(s_index, 0)){
                answer += ind_to_word[i];
                answer += " ";
                reconstruct(s_index + 1, i, answer);
                break;
            }
        }
    }
    else{
        for(i=0; i<no_of_word; i++){
            double cur_prob = next_word_prob[prev_word_ind][i] + wrong_word_prob[i][cur_word_ind];
            double result = cur_prob + get_prob(s_index + 1, i);
            if(result == get_prob(s_index, prev_word_ind)){
                answer += ind_to_word[i];
                answer += " ";
                reconstruct(s_index + 1, i, answer);
                break;
            }
        }
    }
}