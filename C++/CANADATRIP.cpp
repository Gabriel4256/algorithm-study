// 간단한 최적화 -> 결정 문제
// 똑같은 algorithm의 python 코드를 그대로 포팅했다.

#include <iostream>
#include <vector>

int no_of_cities;
int cities[5000][3];

bool decision(double distance, int K){
    int cnt = 0;
    for(int i=0; i<no_of_cities; i++){
        if(distance >= cities[i][0]){
            cnt += cities[i][1] / cities[i][2] + 1;
        }
        else if(distance < cities[i][0] - cities[i][1]){
            continue;
        }
        else{
            cnt += (distance - (cities[i][0] - cities[i][1])) / cities[i][2] + 1;
        }
    }
    return cnt >= K;
}

int optimize(int K){
    double lo = 0, hi = 8030001;
    for(int i=0; i<25; i++){
        double mid = (lo + hi) / 2;
        if(decision(mid, K)){
            hi = mid;
        }
        else{
            lo = mid;
        }
    }
    return hi;
}

int main(){
    int i,j,K,l;
    for(i=0, scanf("%d", &j); i < j; i++){
        scanf("%d %d", &no_of_cities, &K);
        for(l=0; l<no_of_cities; l++){
            scanf("%d %d %d", &cities[l][0], &cities[l][1], &cities[l][2]);
        }
        std::cout << optimize(K) << std::endl;
    }
}