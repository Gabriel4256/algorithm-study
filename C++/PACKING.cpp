// backtracking을 이용해서 답을 찾는 방법을 잘 기억해 두자.
// 그렇게 어려운 문제는 아니었다.

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int memo[101][1002];

int no_of_items;
typedef struct item {
    string name;
    int volume, desp;
} item;
item items[101];

int get_max_desp(int, int);
void reconstruct(int, int, vector<string>&);

int main() {
    int i, j, k, cap;
    for(scanf("%d", &i), j = 0; j < i; j++){
        vector<string> picked;
        memset(memo, -1, sizeof(memo));
        scanf("%d %d", &no_of_items, &cap);
        for(k=0; k<no_of_items; k++){
            cin >> items[k].name >> items[k].volume >> items[k].desp; 
        }
        reconstruct(0, cap, picked);
        printf("%d %d\n", memo[0][cap], (int)picked.size());
        for(k=0; k<picked.size(); k++){
            cout << picked[k] << endl;
        }
    }
}

int get_max_desp(int s_index, int cap){
    int &result = memo[s_index][cap];
    if(result != -1){
        return result;
    }
    if(s_index >= no_of_items || cap <=0)
        return result = 0;
    
    result = get_max_desp(s_index + 1, cap);
    if(items[s_index].volume <= cap){
        int tmp = items[s_index].desp + get_max_desp(s_index + 1, cap - items[s_index].volume);
        result = result > tmp ? result : tmp; 
    }
    return result;
}

void reconstruct(int s_index, int cap, vector<string> &picked){
    if(s_index >= no_of_items || cap <= 0)
        return;
    if(get_max_desp(s_index,cap) == get_max_desp(s_index + 1,cap)){
        reconstruct(s_index + 1, cap, picked);
    }
    else
    {
        picked.push_back(items[s_index].name);
        reconstruct(s_index+1, cap - items[s_index].volume, picked);
    }
}

