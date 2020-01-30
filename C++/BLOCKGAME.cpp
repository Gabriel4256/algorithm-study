// 메모리를 매우 아껴야 하는 문제였다.
// 보드의 상태를 int 하나에 우겨넣는 것까지는 쉽게 떠올렸는데
// 블록에 모양(일자, 기억자)가 들어갈 수 있는 자리들 또한 int에 우겨넣을 수 있다는 것은 깨닫지 못했다.
// 꽤나 기발한 문제였다고 생각한다. 파이썬으로는 아마 못풀지 않을까 싶다..

#include <iostream>
#include <cstring>
#include <vector>
#include <tuple>
using namespace std;

char memo[1 << 25];
int find_winner(int, char);
void pre_calculate(int);
vector<int> moves;

int main() {
    int i,j,k, cnt, board_state;
    for(j=0, scanf("%d", &i); j<i; j++){
        moves.clear();
        memset(memo, 0, sizeof(memo));
        board_state = 0;
        cnt = 0;
        while((k = getchar()) != EOF){
            if(cnt == 25)
                break;
            if(k == '.'){
                cnt++;
            }
            else if(k == '#'){
                board_state += 1 << cnt;
                cnt++;
            }
        }
        pre_calculate(board_state);
        if(find_winner(board_state, 1) == 1)
            printf("WINNING\n");
        else
            printf("LOSING\n");
    }
    return 0;
}

int decrypt(int board_state, char i, char j){
    return board_state & (1 << (5 * i + j));
}

int get_cell(char x, char y){
    return 1 << (5 * x + y);
}

void pre_calculate(int board_state){
    char i,j,k,l;
    int rect;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            rect = get_cell(i, j) + get_cell(i, j + 1) + get_cell(i + 1, j) + get_cell(i + 1, j+1);
            for(k = 0; k<2; k++){
                for(l=0; l<2; l++){
                    moves.push_back(rect - get_cell(i + k, j + l));
                }
            }
        }
    }

    for(i=0; i<5; i++){
        for(j=0; j<5; j++){
            if(decrypt(board_state, i, j) == 0){
                if(i < 4 && decrypt(board_state, i+1, j) == 0){
                    moves.push_back(get_cell(i, j) + get_cell(i + 1, j));
                }
                if(j < 4 && decrypt(board_state, i, j+1) == 0){
                    moves.push_back(get_cell(i, j) + get_cell(i, j+1));
                }
            }
        }
    }
}

int find_winner(int board_state, char turn){
    int i, j;
    char& result = memo[board_state];
    if(result != 0)
        return turn * result;
    result = -turn;
    for(i=0; i<moves.size(); i++){
        if((board_state & moves[i]) == 0){
            if(turn == find_winner(board_state | moves[i], -turn)){
                result = turn;
                break;
            }
        }
    }
    result /= turn;
    return result * turn;
}