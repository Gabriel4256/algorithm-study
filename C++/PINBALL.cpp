// 작동하지 않는 코드, PINBALL2에 답이있다.
// 방식 자체는 틀리지 않았다.

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

vector<int> answer;

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

vector2 circles[50];
int radius[50], N;

vector2 perpendicularFoot(vector2 p, vector2 a, vector2 b){
    return a + (p-a).project(b - a);
}

double pointToLine(vector2 p, vector2 a, vector2 b){
    return (p - perpendicularFoot(p,a,b)).norm();
}

vector2 intersect_with_circle(vector2 center, vector2 a, vector2 b,double radius){
    return a + ((center - a).project(b - a).normalize()) * radius;
}

vector2 next_collision(vector2& start, vector2& dxdy){
    vector2 next_start, next_dxdy;
    int idx = -1;
    double min_dist = 10001;
    for(int i=0; i<N; i++){
        if(dxdy.dot(circles[i] - start) > 0){
            if(pointToLine(circles[i], start, start + dxdy) < radius[i]){
                // answer.push_back(i);
                vector2 new_start = intersect_with_circle(circles[i], start, dxdy, radius[i]);
                if((new_start - start).norm() < min_dist){
                    idx = i;
                    next_start = new_start;
                    min_dist = (new_start - start).norm();
                    vector2 tmp = circles[i] - new_start;
                    vector2 a = tmp.normalize() * dxdy.dot(tmp.normalize());
                    vector2 b = dxdy - a;
                    next_dxdy = b - a;
                }
            }
        }
    }
    if(idx != -1){
        answer.push_back(idx);
        next_collision(next_start, next_dxdy);
    }
}

int main(){
    int i,j,k;
    vector2 start, dx_dy;
    double start_x, start_y, start_dx, start_dy;
    for(scanf("%d", &j), i=0; i<j; i++){
        answer.clear();
        cin >> start_x >> start_y >> start_dx >> start_dy >> N;
        for(int k=0; k<N; k++){
            cin >> circles[k].x >> circles[k].y >> radius[k];
            radius[k]++;
        }
        start = vector2(start_x, start_y);
        dx_dy = vector2(start_dx, start_dy);
        next_collision(start, dx_dy);
        for(int i=0; i< answer.size(); i++){
            cout << answer[i] << " ";
        }
        cout << endl;
    }

}