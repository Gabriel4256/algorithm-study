// 그냥 어렵지 않은 약수의 개수 구하는 문제
// 에라토스테네스의 체와 지수로부터 나머지 구하는 공식을 이용

#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

#define MAX_NUM 10000001
int minFactor[MAX_NUM];
int num_of_factors[MAX_NUM];
int minFactor_power[MAX_NUM];

int factor_cnt(int num, int factor){
    int cnt = 0;
    while(num % factor == 0){
        num /= factor;
        cnt+=1;
    }
    return cnt;
}

void eratos(int hi){
    for(int i=2; i<hi + 1; i++){
        minFactor[i]= i;
    }
    minFactor[0]= minFactor[1] = -1;
    int sqrtn = int(sqrt(hi));
    for(int i=2; i<=sqrtn; i++){
        if(minFactor[i] == i){
            for(int j = i * i; j<=hi; j+=i){
                if(minFactor[j]== j){
                    minFactor[j]= i;
                }
            }
        }
    }
}

void count_factors(int hi){
    for(int i=2; i<=hi; i++){
        if(minFactor[i] == i){
            num_of_factors[i] = 2;
            minFactor_power[i] = 1;
        }
        else{
            int offspring = i / minFactor[i];
            if(minFactor[i] != minFactor[offspring])
                minFactor_power[i] = 1;
            else
                minFactor_power[i] = minFactor_power[offspring] + 1;
            num_of_factors[i] = (minFactor_power[i] + 1) * num_of_factors[offspring] / (minFactor_power[i]); 
        }
    }
}

int count(int lo, int hi, int factor_num){
    int cnt = 0;
    for(int i=lo; i<hi + 1; i++){
        if(num_of_factors[i] == factor_num){
            cnt++;
        }
    }
    return cnt;
}

void getFactorsBrute(int hi){
    memset(num_of_factors, 0, sizeof(num_of_factors));
    for(int div = 1; div < hi + 1; div++){
        for(int mult = div; mult <= hi; mult += div){
            num_of_factors[mult]++;
        }
    }
}

int main(){
    int i,j,k,l,n,lo,hi;
    getFactorsBrute(MAX_NUM - 1);
    for(scanf("%d", &j), i=0; i<j; i++){
        scanf("%d %d %d", &n, &lo, &hi);
        // eratos(hi);
        // count_factors(hi);
        std::cout << count(lo, hi, n) << std::endl; 
    }
}