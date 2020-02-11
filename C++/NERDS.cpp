//선물포장 알고리즘을 이용한 문제
// 점들을 포함하는 최소 다각형을 만드는 식으로 문제를 변형하는 것이 핵심 포인트이다.
// 이런 아이디어를 잘 떠올릴 수 있도록 기하 관련 문제를 많이 풀어봐야겠다.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const double EPSILON = 1e-9;

typedef struct vector2 {
    double x,y;

    explicit vector2(double x_ = 0, double y_ = 0) : x(x_), y(y_){}

    bool operator < (const vector2& rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }
    vector2 operator * (double rhs) const {
        return vector2(x * rhs, y * rhs);
    }

    bool operator == (vector2 rhs) const {
        return fabs(x - rhs.x) < EPSILON && fabs(y -rhs.y) < EPSILON;
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

double ccw(vector2 a, vector2 b, vector2 p){
    return (b - a).cross(p - a);
}

vector<vector2> make_hull(vector<vector2>& points){
    int s_idx = -1;
    double min_val = 1e20;
    vector<vector2> ret;
    vector2 m = *min_element(points.begin(), points.end());
    ret.push_back(m);

    while(true){
        vector2 ph = ret.back(), next = points[0];
        for(int i=0; i<points.size(); i++){
            double cross = ccw(ph, next, points[i]);
            double dist = (next - ph).norm() - (points[i] - ph).norm();
            if(cross < 0 || (cross == 0 && dist < 0))
                next = points[i];            
        }
        if(next == m) break;
        ret.push_back(next);
    }
    return ret;
}

bool inside(const vector<vector2> &poly, vector2 point){
    int cnt = 0;
    for(int i=0; i<poly.size(); i++){
        int next = (i + 1) % poly.size();
        if(poly[i].y > point.y != poly[next].y > point.y){
            double atX = (poly[next].x - poly[i].x) * (point.y - poly[i].y) /
                         (poly[next].y - poly[i].y) + poly[i].x;
            if(point.x < atX)
                cnt++;
        }
    }
    return cnt % 2 > 0;
}

bool segIntersects(vector2 a, vector2 b, vector2 c, vector2 d){
    double ab = ccw(a,b,c) * ccw(a,b,d);
    double cd = ccw(c,d,a) * ccw(c,d,b);

    if(ab == 0 && cd == 0){
        if(b < a) swap(a,b);
        if(d < c) swap(c,d);
        return !(b < c || d < a);
    }
    return ab<=0 && cd <=0;
}

bool polygonIntersects(const vector<vector2> &p1, const vector<vector2> &p2){
    if(inside(p1, p2[0]) || inside(p2, p1[0]))
        return true;
    for(int i=0; i<p1.size(); i++){
        for(int j=0; j<p2.size(); j++){
            if(segIntersects(p1[i], p1[(i+1) % p1.size()],p2[j], p2[(j+1) % p2.size()])){
                return true;
            }
        }
    }
    return false;
}

int main(){
    int i,j,k, N, a,b,c;
    vector<vector2> points[2];
    vector<vector2> p1, p2;
    
    for(scanf("%d", &j), i=0; i<j; i++){
        points[0].clear();
        points[1].clear();
        cin >> N;
        for(k=0; k<N; k++){
            cin >> a >> b >> c;
            points[a].push_back(vector2(b, c));
        }
        p1 = make_hull(points[0]);
        p2 = make_hull(points[1]);
        if(polygonIntersects(p1, p2)){
            printf("THEORY IS INVALID\n");
        }
        else{
            printf("THEORY HOLDS\n");
        }
    }
}