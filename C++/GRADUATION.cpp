// 어렵지 않게 bitmask와 동적계획법을 이용하여 풀 수 있었다.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int memo[(1 << 16) + 1]; // 앞의 4bit는 몇번째 학기인지 나타내고 그 뒤의 12bit는 들은 과목 정보

vector<int> subjects;
vector<int> semesters;
vector<int> semesters_from;
int max_subjects, should_be_taken;

void generate_semesters_from(){
    semesters_from.clear();
    semesters_from.resize(semesters.size());
    semesters_from[semesters.size()-1] = semesters[semesters.size()-1];
    for(int i=semesters.size() - 2; i>-1; i--){
        semesters_from[i] = semesters_from[i + 1] | semesters[i];
    }
}

int get_semester(int info){
    return (info & ((1 << 15) + (1 << 14) + (1 << 13) + (1 << 12))) >> 12; 
}

int no_of_1s(int bits){
    int cnt=0;
    for(int i=0; i<12; i++){
        if((bits & (1 << i)) != 0)
            cnt++;
    }
    return cnt;
}

vector<int> combination(int takeable, int num, int taken){
    vector<int> ret;
    if(num == 0)
        return ret;
    if(no_of_1s(takeable) == num){
        ret.push_back(taken | takeable);
        return ret;
    }

    for(int i=0; i<12; i++){
        if((takeable & (1 << i)) > 0){
            auto res1 = combination(takeable - (1 << i), num - 1, taken | (1 << i));
            auto res2 = combination(takeable - (1 << i), num, taken);
            ret.insert(ret.end(), res1.begin(), res1.end());
            ret.insert(ret.end(), res2.begin(), res2.end());
            return ret;
        }
    }
}

int next_sem(int bits){
    return bits + (1 << 12);
}

int search(int info){
    // 학기도 0번째 학기부터 시작
    int cur_sem = get_semester(info);
    int taken = info & ((1 << 12) - 1);
    // int cur_sem = semester;
    // int taken = info;

    if(no_of_1s(taken) >= should_be_taken){
        return 0;
    }

    if(cur_sem == semesters.size()){
        return 100;
    }

    int &result = memo[info];
    if(result != -1) return result;

    if(no_of_1s(taken | semesters_from[cur_sem]) < should_be_taken)
        return 100;
    result = 100;
    
    // 이미 들었던 거 거르고
    int takeable = (semesters[cur_sem] & ~taken);

    for(int i=0; i<subjects.size(); i++){
        if((takeable & (1 << i))){
            if((taken & subjects[i]) != subjects[i])
                takeable &= ~(1 << i);
        }
    }
    // int length = min(no_of_1s(takeable), max_subjects);
    // vector<int> combs = combination(takeable, length, 0);
    for(int take = takeable; take > 0; take = ((take - 1) & takeable)){
        if(no_of_1s(take) > max_subjects)
            continue;
        result = min(result, 1 + search(next_sem(info | take)));
    }

    // for(int i=0; i<combs.size(); i++){
    //     result = min(result, 1 + search(next_sem(info | combs[i])));
    // }
    result = min(result, search(next_sem(info)));
    return result;
}

int main() {
    int i,j,k,l,m, N, K, M, L, tmp, tmp2;
    for(scanf("%d", &j), i=0; i<j; i++){
        subjects.clear();
        semesters.clear();
        semesters_from.clear();
        memset(memo, -1, sizeof(memo));
        cin >> N >> should_be_taken >> M >> max_subjects;
        for(k=0; k<N; k++){
            cin >> l;
            tmp = 0;
            for(m=0; m<l; m++){
                cin >> tmp2;
                tmp |= (1 << tmp2);
            }
            subjects.push_back(tmp);
        } 
        for(k=0; k<M; k++){
            cin >> l;
            tmp = 0;
            for(m=0; m<l; m++){
                cin >> tmp2;
                tmp |= (1 << tmp2);
            }
            semesters.push_back(tmp);
        }
        generate_semesters_from();
        int ans = search(0);
        if(ans > M)
            cout << "IMPOSSIBLE" << endl;
        else
            cout << ans << endl;
    }
    return 0;
}