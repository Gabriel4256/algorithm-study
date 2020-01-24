// 두번째 메모하는 과정하고 backtracking(reconstruct) 하는 과정을 한번에 하려고 했는데, 생각보다 잘 안됐다.
// 엄청나게 어렵거나 한 문제는 아니다. 다만 방법을 좀 잘못 선택한 것 같다.

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int memo[502];
int memo2[502];
int no_of_element;
int numbers[501];
const int MAX = 2000000000 + 1;

int get_lis_len(int);
void reconstruct(int, int, vector<int>&);
int get_count(int);

int main() {
    int i,j,k;
    double count;
    vector<int> answer;
    scanf("%d", &i);
    for(j=0; j<i; j++){
        answer.clear();
        scanf("%d %lf", &no_of_element, &count);
        memset(memo, -1, sizeof(memo));
        for(k=0; k<502; k++){
            memo2[k] = -1.0;
        }
        for(k=0; k<no_of_element; k++){
            cin >> numbers[k];
        }
        reconstruct(-1, count, answer);
        cout << answer.size() << endl;
        for(k= 0; k < answer.size(); k++){
            cout << answer[k] << " ";
        }
        cout << endl;
    }
    return 0;
}

int get_lis_len(int prev_num_idx){
    int i;
    int &result = memo[prev_num_idx + 1];
    
    if(prev_num_idx == no_of_element-1)
        return (result = 0);

    if(result != -1)
        return result;
    int prev_num = prev_num_idx  > -1 ? numbers[prev_num_idx] : -1;
    result = 0;
    for(i=prev_num_idx + 1; i<no_of_element; i++){
        if(numbers[i] > prev_num){
            result = max(result, 1 + get_lis_len(i));
        }
    }
    return result;
}

int get_count(int prev_num_idx){
    if(prev_num_idx == no_of_element-1)
        return 1;
    int &result = memo2[prev_num_idx + 1];
    if(result != -1)
        return result;
    result = 0;
    int prev_num = prev_num_idx > -1 ? numbers[prev_num_idx] : -1;
    for(int i = prev_num_idx + 1; i< no_of_element; i++){
        if(numbers[i] > prev_num && get_lis_len(i) + 1 == get_lis_len(prev_num_idx))
            result = min<long long>(MAX, (long long)result + get_count(i));
    }
    if(result == 0)
        result = 1;  
    return result;
}

void reconstruct(int prev_num_idx, int target, vector<int> &answer){

    int prev_num = prev_num_idx > -1 ? numbers[prev_num_idx] : -1;
    for(int i= no_of_element-1; i> prev_num_idx; i--){
        if(get_lis_len(i) + 1 == get_lis_len(prev_num_idx) && numbers[i] > prev_num){
            int count = get_count(i);
            if(target <= count){
                answer.push_back(numbers[i]);
                reconstruct(i, target, answer);
                break;
            }
            else{
                target -= count;
            }
        }
    }
}

// double reconstruct(int prev_num_idx, double target, vector<int> &answer){
//     int i;
//     double &result = memo2[prev_num_idx + 1];
//     if(prev_num_idx == no_of_element - 1)
//         return 1;
//     if(result != -1)
//         return result;
//     result = 0;
//     int prev_number = prev_num_idx > -1 ? numbers[prev_num_idx] : -1;
//     for(i=no_of_element-1; i > prev_num_idx; i--){
//         if(numbers[i] > prev_number){
//             if(get_lis_len(i) + 1 == get_lis_len(prev_num_idx)){
//                 double tmp = min(1e10, reconstruct(i, target-result, answer));
//                 result = min(1e10, result + tmp);
//                 if(result >= target){
//                     answer.push_back(numbers[i]);
//                     break;
//                 }
//             }
//         }
//     }
//     if(result == 0)
//         result = 1;
//     return result;
// }