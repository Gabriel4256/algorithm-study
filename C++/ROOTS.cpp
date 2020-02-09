// 그리 어려운 문제는 아니었다. 다만, 주어진 구간 안에서 해가 여러 개일 때
// 미분을 활용하여 연쇄적으로 처리해야 한다는 아이디어를 기억하고 가자.

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int highest_coeff;
vector<double> coefficients[5];
vector<double> answers[5];
double decision(double lo, double hi, int level);
double f(double x, int level);

void differentiate(vector<double> &src, vector<double> &tar){
    int level = src.size() - 1;
    for(int i=0; i<src.size() - 1; i++){
        tar.push_back( (level-i) * src[i]);
    }
}

void optimize(){
    answers[0].push_back(-10.1);
    answers[0].push_back(decision(-10.1, 10.1, 1));
    answers[0].push_back(10.1);

    for(int i=1; i<highest_coeff-1; i++){
        answers[i].push_back(-10.1);
        for(int j=0; j<answers[i-1].size()-1; j++){
            if(f(answers[i-1][j], i + 1) * f(answers[i-1][j+1], i + 1) < 0)
                answers[i].push_back(decision(answers[i-1][j], answers[i-1][j+1], i + 1));
        }
        answers[i].push_back(10.1);
    }
    for(int j=0; j<answers[highest_coeff - 2].size() - 1; j++){
        if(f(answers[highest_coeff-2][j], highest_coeff) * f(answers[highest_coeff-2][j+1], highest_coeff) < 0)
            answers[highest_coeff - 1].push_back(
                decision(answers[highest_coeff-2][j], answers[highest_coeff-2][j+1], highest_coeff)
            );
    }
}

void generate_diff_coeffs(){
    for(int i=highest_coeff-1; i>0; i--){
        differentiate(coefficients[i], coefficients[i-1]);
    }
}

double f(double x, int level){
    double answer = 0;
    for(int i=0; i<level + 1; i++){
        answer += coefficients[level - 1][i] * pow(x, level - i);
    }
    return answer;
}

double decision(double lo, double hi, int level){
    // double lo = -10.1, hi = 10.1;
    if(f(lo, level) < 0)
        swap(lo, hi);
    for(int i=0; i<100; i++){
        double mid = (lo + hi) / 2;
        if(f(mid, level) >= 0){
            lo = mid;
        }
        else{
            hi = mid;
        }
    }
    return (lo + hi) / 2;
}

void initialize(){
    for(int i=0; i<5; i++){
        coefficients[i].clear();
        answers[i].clear();
    }
}

int main() {
    int i,j,k;
    double l;
    for(scanf("%d", &j),i=0; i<j; i++){
        initialize();
        scanf("%d", &highest_coeff);
        for(k=0; k<highest_coeff + 1; k++){
            cin >> l;
            coefficients[highest_coeff - 1].push_back(l);
        }
        generate_diff_coeffs();
        optimize();
        cout.precision(10);
        cout << fixed;
        for(int i=0; i<answers[highest_coeff - 1].size(); i++){
            std::cout << answers[highest_coeff-1][i] << " ";
        }
        printf("\n");
        // std::cout << decision() << std::endl;
    }
    return 0;
}
