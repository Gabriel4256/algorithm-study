// 꽤나 난이도 있는 삼분법 문제. 거의 책을 참고하다시피 해서 풀었다.
// 삼분법의 개념은 그리 어려운 게 아니지만, 이 문제는 어떤 식으로 풀어나가야 될지
// 방향을 정하는 게 어려웠다.

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

vector<pair<double, double>> polys[2];
vector<pair<double, double>> up_and_low[2][2];

double get_val(double x, int polynum, int height){
    // polynum은 다각형 번호, height는 up인지 low인지
    auto tmp = up_and_low[polynum][height];
    for(int i=0; i<tmp.size(); i++){
        if(tmp[i].first >= x){
            double answer = (tmp[i].second - tmp[i-1].second) / (tmp[i].first - tmp[i-1].first) * (x - tmp[i].first) + tmp[i].second;
            return answer;
        }
    }
}

double f(double x){
    return min(get_val(x, 0, 0), get_val(x, 1, 0)) - max(get_val(x, 0, 1), get_val(x, 1, 1));
}

bool compare(pair<double, double> a, pair<double, double> b){
    return a.first < b.first;
}

void divide(){
    // 위껍질과 아래껍질로 분리해서 up, down에 저장.
    int prev_state = -1;
    for(int i=0; i<2; i++){
        prev_state = -1;
        for(int j=0; j<polys[i].size(); j++){
            auto next = (j == polys[i].size() - 1) ? polys[i][0]: polys[i][j+1];  
            if(polys[i][j].first < next.first){
                if(up_and_low[i][1].size() == 0){
                    up_and_low[i][1].push_back(polys[i][j]);
                    up_and_low[i][1].push_back(next);
                    prev_state = 0;
                    continue;
                }
                if(prev_state == 1)
                    up_and_low[i][1].push_back(polys[i][j]);
                if(prev_state == 0)
                    up_and_low[i][1].push_back(next);
                prev_state = 0;
            }
            else if(polys[i][j].first > next.first){
                if(up_and_low[i][0].size() == 0){
                    up_and_low[i][0].push_back(polys[i][j]);
                    up_and_low[i][0].push_back(next);
                    prev_state = 1;
                    continue;
                }
                if(prev_state == -1 || prev_state == 0)
                    up_and_low[i][0].push_back(polys[i][j]);
                if(prev_state == -1 || prev_state == 1)  
                    up_and_low[i][0].push_back(next);
                prev_state = 1;
            }
        }
        // up_and_low[i][0].erase(std::unique(up_and_low[i][0].begin(), up_and_low[i][0].end()), up_and_low[i][0].end());
        // up_and_low[i][1].erase(std::unique(up_and_low[i][1].begin(), up_and_low[i][1].end()), up_and_low[i][1].end());
        sort(up_and_low[i][0].begin(), up_and_low[i][0].end(), compare);
        sort(up_and_low[i][1].begin(), up_and_low[i][1].end(), compare);
    }    
}

double optimize(double lo, double hi){
    if(hi < lo) return 0;

    for(int i=0; i<200; i++){
        if(f((2 * lo + hi) / 3) > f((lo + 2* hi) / 3))
            hi = (lo + 2 * hi) / 3;
        else
            lo = (2 * lo + hi) / 3;
    }
    return max(0.0, f(hi));
}

void initialize(){
    for(int i=0; i<2; i++){
        polys[i].clear();
        for(int j=0; j<2; j++){
            up_and_low[i][j].clear();
        }
    }
}

int main() {
    int i,j,k,l,m;
    double tmp, tmp2;
    double maxval[2], minval[2]; 
    
    for(scanf("%d", &j), i=0; i<j; i++){
        initialize();
        for(m=0; m<2; m++){
            maxval[m] = 0;
            minval[m] = 100;
            polys[m].clear();
        }
        scanf("%d %d", &k, &l);
        for(m=0; m<k; m++){
            cin >> tmp;
            cin >> tmp2;
            maxval[0] = max(tmp, maxval[0]);
            minval[0] = min(tmp, minval[0]);
            polys[0].push_back(make_pair(tmp, tmp2));
        }
        for(m=0; m<l; m++){
            cin >> tmp;
            cin >> tmp2;
            maxval[1] = max(tmp, maxval[1]);
            minval[1] = min(tmp, minval[1]);
            polys[1].push_back(make_pair(tmp, tmp2));
        }
        divide();
        cout.precision(10);
        cout << fixed;
        std::cout << optimize(max(minval[0], minval[1]), min(maxval[0], maxval[1])) << std::endl; 
    }
    return 0;
}