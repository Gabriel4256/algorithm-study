// 쉬운 이분법 문제

#include <iostream>

using namespace std;

double loan, days ,interest;

double f(int days, double pay){
    if(days == 0)
        return loan;
    else{
        return f(days-1, pay) * interest - pay;
    }
}

double optimize(){
    double lo = 0, hi = loan * interest;
    for(int i=0; i<100; i++){
        double mid = (lo + hi) / 2;
        if(f(days, mid) <=0 ){
            hi = mid;
        }
        else{
            lo = mid;
        }
    }
    return hi;
}

int main(){
    int i,j,k;
    for(scanf("%d", &j), i=0; i<j; i++){
        scanf("%lf %lf %lf", &loan, &days, &interest);
        interest = 1 + interest / 12 / 100;
        cout.precision(10);
        cout << fixed;
        std::cout << optimize() << std::endl;
    }
    return 0;
}