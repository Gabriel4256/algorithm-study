// 다각형 클리핑 문제를 해결하는 기본적인 알고리즘인
// 서덜랜드 호지맨 알고리즘을 이용
// 거의 책을 참고해서 풀었다.

/*
벡터 관련 지식들

직선과 직선의 교차
a + p * b 와 c + q * d의 교점을 구하면
p = (c - a) X d / (b X d) 가 나오고 이 p를 a + p * b에 대입하면 교점을 구할 수 있다.

점과 직선 사이의 거리
외적을 통해 어떤 점이 어떤 직선을 기준으로 어느쪽에 있는지도 알 수 있다.
점과 선 사이의 거리는 project를 한 뒤 두 점 사이의 거리를 구하면 된다.

다각형의 면적
다각형의 면적을 구할 때는 어떤 점을 기준으로 하여 그 점과 다른 변들로 만든 삼각형들의 넓이의 합으로
구할 수 있다. 오목 다각형인 경우에도 가능. 이 삼각형들의 넓이는 외적을 이용해 구할 수 있다.

내부/외부 판별
주어진 점이 다각형 내부에 있는지 판단하려면 점에서 시작하는 반직선을 만들어 그 반직선이 다각형의 변과
몇 번 만나는지 세면 된다. 짝수번이면 외부에 있는 것이고, 홀수번이면 내부.
*/


#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef struct vector2 {
    double x,y;

    explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_){}

    vector2 operator * (double rhs) const {
        return vector2(x * rhs, y * rhs);
    }

    vector2 operator / (double rhs) const {
        return vector2(x / rhs, y / rhs);
    }

    vector2 operator + (const vector2& rhs) const {
        return vector2(x + rhs.x, y + rhs.y);
    }

    vector2 operator - (const vector2& rhs) const {
        return vector2(x - rhs.x, y - rhs.y);
    }

    double dot(const vector2& rhs) const {
        return x* rhs.x + y * rhs.y;
    }

    double cross(const vector2& rhs) const {
        return x * rhs.y - rhs.x * y;
    }

    double norm() const {
        return hypot(x, y);
    }

    vector2 normalize() const {
        return vector2( x / norm(), y / norm());
    }

    vector2 project(const vector2& rhs) const {
        vector2 r = rhs.normalize();
        return r * r.dot(*this);
    }

} vector2;
const double EPSILON = 1e-9;
typedef vector<vector2> polygon;

double ccw(vector2 a, vector2 b, vector2 p){
    return (b - a).cross(p - a);
}

vector2 lineIntersection(vector2 a, vector2 b, vector2 c, vector2 d){
    // 직선 ab와 cd의 교점을 구하는 함수
    double det = (b-a).cross(d-c);

    if(fabs(det) < EPSILON) return vector2(-1, -1);
    return a + (b-a) * ((c-a).cross(d - c) / det);
}

polygon cutpoly(polygon p, vector2 a, vector2 b){
    vector<bool> insides(p.size());
    polygon ret;
    for(int i=0; i<p.size(); i++){
        insides[i] = ccw(a, b, p[i]) >= 0;
    }

    for(int i=0; i<p.size(); i++){
        if(insides[i]) ret.push_back(p[i]);
        int next = (i + 1) % p.size();
        if(insides[i] != insides[next]){
            vector2 cross_point = lineIntersection(a, b, p[i], p[next]);
            ret.push_back(cross_point);
        }
    }

    return ret;
}

polygon intersection(const polygon& p, double x1, double x2, double y1, double y2){
    vector2 a(x1, y1), b(x1, y2), c(x2, y1), d(x2, y2);
    polygon ret;
    ret = cutpoly(p, a, c);
    ret = cutpoly(ret, c, d);
    ret = cutpoly(ret, d, b);
    ret = cutpoly(ret, b, a);

    return ret;
}

double area(polygon &p){
    double ret = 0;
    for(int i=0; i<p.size(); i++){
        int next = (i + 1) % p.size();
        ret += p[i].x * p[next].y - p[i].y * p[next].x;
    }
    return fabs(ret) / 2.0;
}

int main(){
    int i,j,k,l;
    int x1, x2, y1, y2, N;
    double tmp1, tmp2;
    polygon p;
    for(scanf("%d", &j),i=0; i<j; i++){
        p.clear();
        cin >> x1 >> y1 >> x2 >> y2 >> N;
        for(int k=0; k<N; k++){
            cin >> tmp1 >> tmp2;
            p.push_back(vector2(tmp1, tmp2));
        }
        p = intersection(p, x1, x2, y1, y2);
        cout.precision(10);
        cout << fixed;
        cout << area(p) << endl;
    }
}