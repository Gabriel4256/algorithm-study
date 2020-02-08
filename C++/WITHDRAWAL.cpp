// 그리 어렵지 않은 최적화 -> 선택 문제
// greedy한 선택을 할 수 있다는 것을 알아내는 것이 중요했다.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int no_of_classes;
int classes[1000][2];


bool decision(double rank, int K){
    double result = 0;
    vector<double> tmp;
    for(int i=0; i<no_of_classes; i++){
        tmp.push_back(classes[i][1] * rank - classes[i][0]);
    }
    sort(tmp.begin(), tmp.end(), greater<double>());
    for(int i=0; i<K; i++){
        result += tmp[i];
    }
    return result >= 0;
}

double optimize(int K){
    double lo = 0, hi = 1.01;
    for(int i=0; i<100; i++){
        double mid = (lo + hi) / 2;
        if(decision(mid, K))
            hi = mid;
        else
            lo = mid;
    }
    return hi;
}

int main(){
    int i,j,K,l;
    for(scanf("%d", &j), i=0; i<j; i++){

        scanf("%d %d", &no_of_classes, &K);
        for(l=0; l<no_of_classes; l++){
            scanf("%d %d", &classes[l][0], &classes[l][1]);
        }
        cout.precision(10);
        cout << fixed;
        std::cout << optimize(K) << std::endl;
    }
}