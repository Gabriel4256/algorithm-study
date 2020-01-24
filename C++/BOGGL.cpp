#include <iostream>
using namespace std;

string word;
char board[5][5];

bool check(int startx, int starty, int wordindex){
    char target = word.at(wordindex);
    bool result = false;    
    if(wordindex >= word.size()){
        return true;
    }
    if(startx < 4 && starty < 4 && board[startx + 1][starty + 1] == target){
        result = result || check(startx + 1, starty + 1,wordindex + 1);
    }
    if(startx < 4 && board[startx+1][starty] == target){
        result = result || check(startx + 1, starty, wordindex + 1);
    }
    if(startx > 0 && board[startx-1][starty] == target){
        result = result ||check(startx - 1, starty, wordindex + 1);
    }
    if(starty < 4 && board[startx][starty + 1] == target){
        result = result ||check(startx, starty +1, wordindex + 1);
    }
    if(starty > 0 && board[startx][starty-1] == target){
        result = result ||check(startx, starty-1, wordindex + 1);
    }    
    if(startx > 0 && starty < 4 && board[startx-1][starty+1] == target){
        result = result ||check(startx - 1, starty+1, wordindex + 1);
    }
    if(startx > 0 && starty > 0 && board[startx-1][starty - 1] == target){
        result = result ||check(startx - 1, starty - 1, wordindex + 1);
    }
    if(startx < 4 && starty > 0 && board[startx+1][starty -1] == target){
        result = result ||check(startx + 1, starty - 1, wordindex + 1);
    }
    return result;
}

int main()
{
    int t, i, j, k, l, m, n;
    cin >> i;
    // string words[10];
    bool result;
    // char board[5][5];
    
    for(t =0; t<i; t++){
    //get board contents
        for(j=0; j<5; j++){
            for(k=0; k<5; k++){
                board[j][k] = cin.get();
            }
            cin.get();
        }

    // get words to find
        cin >> j;
        for(k=0; k<6; k++){
            result = false;
            // getline(cin, word);
            // cin.get();
            cin >> word;
            std::cout << word << std::endl;
            for(l =0; l< word.size(); l++){
                for(m=0; m <5; m++){
                    for(n=0; n<5; n++){
                        if(board[m][n] == word.at(0)){
                            result = result || check(m, n, 1);
                        }
                    }
                }
            }
            std::cout << word << ": "<< result<< endl;
        }
    }
    return 0;
}
