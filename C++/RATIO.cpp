// 간단한 이분법 문제

#include <iostream>
#include <cmath>

using namespace std;

double played, won, cur_winning_rate;

bool decision(double streaks){
    double rate = (won + streaks) / (played + streaks);
    return floor(rate * 100) > cur_winning_rate; 
}

int optimize(){
    double lo = -0.1, hi = 2e9 + 1;
    if(!decision(hi))
        return -1;
    for(int i=0; i<100; i++){
        double mid = (lo + hi) / 2;
        if(decision(mid)){
            hi = mid;
        }
        else{
            lo = mid;
        }
    }
    return ceil(hi);
}

int main(){
    int i,j,k;
    for(scanf("%d", &j),i=0; i<j; i++){
        scanf("%lf %lf", &played, &won);
        cur_winning_rate = floor(100 * won / played); 
        std::cout << optimize() << std::endl;
    }
}