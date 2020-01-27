// 별로 어렵지 않은 문제였다.

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int memo[21474837];
int foods[20][2];

int main(){
    int i,j,k,l;
    int no_of_foods, budget;
    for(i=0, scanf("%d", &j); i<j; i++){
        // foods.clear();
        // memset(memo, 0, sizeof(memo));
        scanf("%d %d", &no_of_foods, &budget);
        for(k=0; k<no_of_foods; k++){
            scanf("%d %d", &foods[k][0], &foods[k][1]);
        }
        for(k=0; k< budget / 100 + 1; k++){
            if(k == 0)
                memo[k] = 0;
            else{
                memo[k] = 0;
                for(l=0; l<no_of_foods; l++){
                    if(foods[l][0] / 100 <= k){
                        memo[k] = max(memo[k], foods[l][1] + memo[k - foods[l][0] / 100]);
                    }
                }
            }
        }
        std::cout << memo[budget / 100] << std::endl;
    }
    return 0;
}