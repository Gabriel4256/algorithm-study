//
// memoization
// 1차적으로 나머지를 메모하는데, 여기서 저장해야 되는 것은
// 원본 숫자보다 작은 것이 확정되었는지 여부와 사용 가능한 남은 숫자들
// 사용 가능한 남은 숫자들을 어떻게 메모할 것인가?
// 사용가능한 모든 숫자들을 정렬하고, 중복되는 숫자들의
// 첫 index들만 저장해도 여러 개가 된다. 이걸 어떻게 지혜롭게 처리할 수 있을까.
// => 다른 사람의 코드를 보고 bitmask를 활용할 수 있다는 것을 깨달았다.

// 나머지를 메모하기 위한 것 하나, 그리고 개수를 세기 위한 reconstruct 하나
// 악몽같은 문제였다.. 메모이제이션을 할 때 memo의 key 값으로 여러 값을 동시에 써야 했기에, map을 쓸까도 고민했지만
// 더 좋은 방법이 있을 것 같았다. bitmask라는 아이디어를 들어도 어떻게 써야할지 바로 감이 안왔고,
// 방식을 참고해서 구현하는 과정에서도 type 간 변환이나 type의 boundary에 대한 생각이 많이 부족해서 오래 걸렸다.
// 여러모로 깨달은 게 많았던 문제였다.

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int memo[2][1 << 16][20]; //자릿수는 최대 15자리이기 때문에, 각 자리의 숫자가 쓰였는지를 기록
// 각각 앞의 선택으로 인해 이미 작은 수인지, 자릿수별 숫자가 쓰였는지, 그리고 나머지
int divisor; //계란 개수, 이것으로 나누어 떨어져야 한다.
vector<int> cur_price; //현재 가격 (자리수 별로 저장)
int avail_num[10][2]; //정렬되었을 때 기준으로 중복되는 숫자들의 시작 인덱스 및 end 인덱스
int get_num(int, int, int, int);

int main(){
    int i,j,k;
    string num;
    for(i=0, scanf("%d", &j); i<j; i++){
        memset(memo, -1, sizeof(memo));
        memset(avail_num, -1, sizeof(avail_num));
        cur_price.clear();

        cin >> num;
        for(k=num.size()-1; k>-1; k--){
            cur_price.push_back(num[k] - 48);
        }
        vector<int> cp = cur_price;
        sort(cp.begin(), cp.end());
        for(k=0; k<cp.size(); k++){
            if(k == 0 || cp[k] != cp[k-1]){
                avail_num[cp[k]][0] = k;
            }
            if(k == cp.size() - 1 
                || cp[k] != cp[k+1]){
                avail_num[cp[k]][1] = k;
            }
        }
        scanf("%d", &divisor);
        printf("%d\n", get_num(0, 1 << 15, cur_price.size() - 1, 0));
    }
    return 0;
}


bool can_choose(int chosen, int index){
    return !((chosen & 1 << index) == 1 << index);
}

int can_choose_num(int chosen, int num){
    int idx = avail_num[num][0];
    if(idx == -1)
        return -1;
    while(idx <= avail_num[num][1]){
        if(can_choose(chosen, idx)){
            return idx;
        }
        idx++;
    }
    return -1;
}

int choose(int chosen, int index){
    return chosen | (1 << index);
}

int get_num(int smaller, int chosen, int level, int rest){
    int &result = memo[smaller][chosen][rest];
    int new_chosen = -1;
    if(result != -1)
        return result;

    if(level == -1){
        if(rest % divisor == 0 && smaller == 1)
            return 1;
        else
            return 0;
    }
    result = 0;
    for(int i=0; i<10; i++){
        bool check = (smaller == 1) || (i <= cur_price[level]);
        if(check){
            int idx = can_choose_num(chosen, i);
            if(idx > -1){
                new_chosen = choose(chosen, idx);
                bool issmaller = (smaller == 1) || i < cur_price[level];
                result += get_num(issmaller? 1 : 0, new_chosen, level-1, (10 * rest + i) % divisor); 
                result %= (int)(1e9 + 7);                 
            }
        }
    }
    return result;
}
