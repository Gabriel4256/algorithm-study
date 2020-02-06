// 난이도는 '하' 였지만 체감 난이도는 중 이상이었다.
// 모양을 기억할 때 x, y 좌표 순서상 가장 먼저 나오는 것을 (0,0) 으로 잡고 나머지의 좌표를 저장하는 것을 기억하자.


#include <iostream>

#include <string>

#include <vector>

#include <algorithm>

using namespace std;

//게임판 정보

int boardH, boardW; //board Height(세로), board Width(가로)

vector<string> board;

//블록의 크기

int blockSize;

//게임판의 각 칸이 덮였는지를 나타낸다

//1이면 #이거나 이미 덮은 칸, 0이면 .

int covered[10][10];

//블록의 회전된 형태를 계산하고 상대 좌표의 목록으로 저장

vector<vector<pair<int, int>>> rotations; //이차원 벡터

//2차원 배열 arr을 시계방향으로 90도 돌린 결과 반환

vector<string> rotate(const vector<string> &arr)

{
    vector<string> result(arr[0].size(), string(arr.size(), ' '));
    for(int i=0; i<arr.size(); i++){
        for(int j=0; j<arr[0].size(); j++){
            result[j][arr.size() - 1 - i] = arr[i][j];
        }
    }
    return result;
}

//block의 네가지 회전 형태를 만들고 이들을 상대 좌표의 목록으로 변환

void generateRotations(vector<string> block)

{
    rotations.clear();
    rotations.resize(4);
    for(int rot=0; rot<4; rot++){
        int originX = -1; int originY = -1;
        for(int i=0; i<block.size(); i++){
            for(int j=0; j<block[i].size(); j++){
                if(block[i][j] == '#'){
                    if(originY == -1){
                        originY = i;
                        originX = j;
                    }
                    rotations[rot].push_back(make_pair(i - originY, j - originX));
                }
            }
        }
        block = rotate(block);
    }

    sort(rotations.begin(), rotations.end());
    rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());

    blockSize = rotations[0].size();
}

//(y, x)를 왼쪽 위칸으로 해서 주어진 블록을 delta=1이면 놓고, -1이면 없앤다

//블록을 놓을 때 이미 놓인 블록이나 #과 겹치면 거짓을, 아니면 참을 반환

bool set(int y, int x, const vector<pair<int, int>> &points, int delta)

{
    bool result = true;
    for (int i=0; i<points.size(); i++){
        if(y + points[i].first >=0 && y + points[i].first < boardH && x + points[i].second >= 0 && x + points[i].second < boardW){
            covered[y + points[i].first][x + points[i].second] += delta;
            result = result && (covered[y + points[i].first][x + points[i].second] == 1);
        }
        else{
            result = false;
        }
    }
    return result;
}

int best; //지금까지 찾은 최적해

//놓을 수 있는 블록의 수는 단순히 남은 빈 칸의 수를 블록의 크기로 나눈 것

//거기에 이미 놓은 수를 더했을 때 기존 최적해보다 작을 경우 최적해

int blockPrune(int placed) //가지치기

{

    int cnt = 0;

    for (int i = 0; i < boardH; i++)

        for (int j = 0; j < boardW; j++)

            cnt += !(covered[i][j]) ? 1 : 0;

    return ((cnt / blockSize) + placed <= best);
}

void search(int placed) //placed:지금까지 놓은 블록의 수

{
    if(blockPrune(placed))
        return;
    int y = -1, x = -1;
    for(int i = 0; i<boardH; i++){
        for(int j=0; j< boardW; j++){
            if(covered[i][j] == 0){
                x = j;
                y = i;
                break;
            }
        }
        if(y != -1)
            break;
    }

    if(y == -1){
        best = max(best, placed);
        return;
    }

    for(int i=0; i<rotations.size(); i++){
        if (set(y, x, rotations[i], 1))
            search(placed + 1);
        set(y, x, rotations[i], -1);
    }
    covered[y][x] = 1;
    search(placed);
    covered[y][x] = 0;
}

int main(void)

{

    int i, j, k, l;
    char tmp;
    string tmp2;
    vector<string> blocks;
    int blockH, blockW;
    for (j = 0, scanf("%d", &i); j < i; j++)
    {
        scanf("%d %d %d %d", &boardH, &boardW, &blockH, &blockW);
        blocks.clear();
        best = 0;
        for (k = 0; k < boardH; k++)
        {
            cin >> tmp2;
            for (l = 0; l < boardW; l++)
            {
                covered[k][l] = (tmp2[l] == '.') ? 0 : 1;
            }
        }
        for (k = 0; k < blockH; k++)
        {
            cin >> tmp2;
            blocks.push_back(tmp2);
        }
        generateRotations(blocks);
        search(0);
        std::cout << best << std::endl;
    }
    return 0;
}