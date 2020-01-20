#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

int memo[1002][1002] = {-1,};

int find_ways(int days, int height){
    if(height<0){
        height = 0;
    }
    int& ret = memo[days][height];
    if(ret != -1){
        return ret;
    }
    if(height<=0){
        ret = pow(4, days);
    }
    if(days == 0){
        if(height<=0){
            ret = 1;
        }
        else{
            ret = 0;
        }
    }
    else{
        ret = find_ways(days-1, height-1) + 3 * find_ways(days-1, height-2);
    }
    return ret;
}

int main()
{
    int i;
    cin >> i;
    for(int j=0; j<i; ++i){
        int height, days;

        cin >> height; cin >> days;
        memset(memo,-1, sizeof(memo));

        std::cout << ((double)find_ways(days, height) / pow(4, days)) << std::endl;
    }
    return 0;
}
