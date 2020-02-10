// 쉬운 최대공약수 활용 문제

#include <iostream>
#include <cmath>
using namespace std;

int ratio[1000];
int in_pot[1000];
int to_be_put[1000];

int gcd(int a, int b){
    if(a == 0 || b== 0)
        return a + b;
    if(a > b)
        return gcd(a % b, b);
    else
        return gcd(a, b % a);
}

int calculate(int n){
    int gcd_result = ratio[0];
    for(int i=1; i<n; i++){
        gcd_result = gcd(gcd_result, ratio[i]); 
    }

    double maxval = 1;
    for(int i=0; i<n; i++){
        maxval = max(maxval, (double)in_pot[i] / (ratio[i] / gcd_result));
    }
    maxval = int(ceil(maxval));

    for(int i=0; i<n; i++){
        cout << ratio[i] / gcd_result * maxval - in_pot[i] << " "; 
    }
    cout << endl;
}

int main(){
    int i,j,k,n;
    for(scanf("%d", &j), i=0; i<j; i++){
        scanf("%d", &n);
        for(k=0; k<n; k++)
            cin >> ratio[k];
        for(k=0; k<n; k++)
            cin >> in_pot[k];
        calculate(n);
    }
}