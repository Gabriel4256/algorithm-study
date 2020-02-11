// 내 방식대로도 해보고, 책에 나온대로도 해봤는데 둘다 알 수 없는 이유로 답이 나오지 않아
// 그냥 코드를 베꼈다. 아이디어를 생각해내는 것은 그리 어렵지 않았는데, 디테일한 부분에서
// 실수를 한 것 같다.

#include <iostream>

#include <vector>

#include <cmath>

using namespace std;

 

const double EPSILON = 1e-9;

const double INFTY = 1e200;

const double PI = 2.0*acos(0.0);

//2차원 벡터를 표현한다

 

struct vector2

{

        double x, y;

        //생성자를 explicit으로 지정하면 vector2를 넣을 곳에 잘못해

        //실수가 들어가는 일을 방지

        explicit vector2(double x_ = 0, double y_ = 0) :x(x_), y(y_)

        {

        }

        //두 벡터의 비교

        bool operator==(const vector2 &rhs) const

        {

               return x == rhs.x&&y == rhs.y;

        }

        bool operator<(const vector2 &rhs) const

        {

               return x != rhs.x ? x < rhs.x : y < rhs.y;

        }

        //벡터의 덧셈과 뺄셈

        vector2 operator+(const vector2 &rhs) const

        {

               return vector2(x + rhs.x, y + rhs.y);

        }

        vector2 operator-(const vector2 &rhs) const

        {

               return vector2(x - rhs.x, y - rhs.y);

        }

        //실수로 곱셈

        vector2 operator*(double rhs) const

        {

               return vector2(x*rhs, y*rhs);

        }

        //벡터의 길이를 반환

        double norm() const

        {

               return hypot(x, y);

        }

        //방향이 같은 단위 벡터를 반환

        //영벡터에 대해 호출한 경우 반환 값은 정의되지 않는다

        vector2 normalize() const

        {

               return vector2(x / norm(), y / norm());

        }

        //x축의 양의 방ㅎ향으로부터 이 벡터까지 반시계 방향으로 잰 각도

        double polar() const

        {

               return fmod(atan2(y, x) + 2 * PI, 2 * PI);

        }

        //내적/외적의 구현

        double dot(const vector2 &rhs) const

        {

               return x * rhs.x + y * rhs.y;

        }

        double cross(const vector2 &rhs) const

        {

               return x * rhs.y - rhs.x*y;

        }

        //이 벡터를 rhs에 사영한 결과

        vector2 project(const vector2 &rhs) const

        {

               vector2 r = rhs.normalize();

               return r * r.dot(*this);

        }

};
 

int obstacleNum;

vector<vector2> center; //중심

vector<int> radius; //반지름

 

//2차 방정식 ax^2+bx+c=0의 모든 실근을 크기 순서대로 반환

vector<double> solve2(double a, double b, double c)

{

        double d = b * b - 4 * a*c;

        //해가 없는 경우

        if (d < -EPSILON)

               return vector<double>();

        //중근

        if (d < EPSILON)

               return vector<double>(1, -b / (2 * a));

        vector<double> result;

        result.push_back((-b - sqrt(d)) / (2 * a));

        result.push_back((-b + sqrt(d)) / (2 * a));

        return result;

}

 

//here에 있던 공이 1초마다 dir만큼 굴러갈 때, center를 중심으로 하고

//반지름 radius인 장애물과 몇 초 후에 충돌하는지 반환

//충돌하지 않을 경우 '아주 큰 값' INFTY를 반환

double hitCircle(vector2 here, vector2 dir, vector2 center, int radius)

{

        //f(t)=here+t*dir;

        //(center-f(t))*(center-f(t)) =

        //((dir*dir)*t^2) + (2*(here-center)*dir)*t + (center*center + here*here - 2*(center*here) - radius*radius)

        double a = dir.dot(dir);

        double b = 2 * dir.dot(here - center);

        double c = center.dot(center) + here.dot(here) - 2 * here.dot(center) - radius * radius;

 

        vector<double> sols = solve2(a, b, c);

        if (sols.empty() || sols[0] < EPSILON)

               return INFTY;

        return sols[0];

}

 

//here에 있던 공이 dir 방향으로 굴러와 center를 중심으로 하는 장애물에서

//contact 위치에서 충돌했을 때 공의 새로운 방향 반환

vector2 reflect(vector2 dir, vector2 center, vector2 contact)

{

        return (dir - dir.project(contact - center) * 2).normalize();

}

 

//공의 현재 위치와 방향이 주어질 때 최대 10번의 충돌 출력

void simulate(vector2 here, vector2 dir)

{

        //방향은 항상 단위 벡터로 저장

        dir = dir.normalize();

        int hitCount = 0;

        while (hitCount < 100)

        {

               //이번에 충돌한 장애물을 찾는다

               int circle = -1;

               double time = INFTY * 0.5;

               //각 장애물을 순회하며 가장 먼저 만나는 장애물을 찾는다

               for (int i = 0; i < obstacleNum; i++)

               {

                       double candidate = hitCircle(here, dir, center[i], radius[i] + 1);

                       if (candidate < time)

                       {

                              time = candidate;

                              circle = i;

                       }

               }

               //더 이상 장애물에 충돌하지 않고 게임판을 벗어나는 경우

               if (circle == -1)

                       break;

               //부딪히는 장애물의 번호를 출력

               if (hitCount++)

                       cout << " ";

               cout << circle;

               //공의 새 위치를 계산

               vector2 contact = here + dir * time;

               //부딪힌 위치와 새 방향으로 here과 dir 변경

               dir = reflect(dir, center[circle], contact);

               here = contact;

        }

        cout << endl;

}

 

int main(void)

{

        int test_case;

        cin >> test_case;

        if (test_case < 1 || test_case>50)

               exit(-1);

 

        for (int i = 0; i < test_case; i++)

        {

               center.clear();

               radius.clear();

               int x, y, dx, dy;

               cin >> x >> y >> dx >> dy >> obstacleNum;

               if (x < 0 || x>100 || y < 0 || y>100)

                       exit(-1);

               if (dx < -10 || dx>10 || dy < -10 || dy>10)

                       exit(-1);

 

               vector2 here(x, y);

               vector2 dir(dx, dy);

              

               for (int j = 0; j < obstacleNum; j++)

               {

                       int cx, cy;

                       cin >> cx >> cy;

                       center.push_back(vector2(cx, cy));

                       int r;

                       cin >> r;

                       radius.push_back(r);

               }

               simulate(here, dir);

        }

        return 0;

}