// 간단한 최적화 -> 결정 문제로 바꿔 풀기 문제

#include <iostream>
#include <vector>
using namespace std;



bool decision(const vector<double>& location, int cameras, double gap){
    int installed = 0;
    double prev = -gap - 1;
    for(int i=0; i<location.size(); i++){
        if(location[i] >= prev + gap){
            prev = location[i];
            installed++;
        }
    }
    return installed >= cameras;
}

double optimize(const vector<double>& location, int cameras){
    double lo = 0, hi = 241;

    for(int i=0; i<30; i++){
        double mid = (lo + hi) / 2.0;
        if(decision(location, cameras, mid))
            lo = mid;
        else
            hi = mid;
    }

    return lo;
}

int main() {
    vector<double> locations;
    int i,j,k, no_of_cam, no_of_stations;
    double l;
    for(scanf("%d", &i), j=0; j<i; j++){
        locations.clear();
        cin >> no_of_cam; cin >> no_of_stations;
        for(k=0; k<no_of_stations; k++){
            cin >> l;
            locations.push_back(l);
        }
        cout << fixed;
        cout.precision(2);
        std::cout << optimize(locations, no_of_cam) << std::endl;
    }
    return 0;
}