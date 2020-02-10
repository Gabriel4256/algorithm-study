// 일반적인 반복 동적 계획법으로 풀면 시간 초과가 뜬다.
// K 값이 10^6까지 커질 수 있는데, 이 경우에는 O(K * (song_num)^2)이기 때문
// 하지만 배열을 이용하면 K를 log(K)로 줄일 수 있다.
// 배열로 전환하는 방식을 이해하는 데 어려움을 많이 겪었다. 책을 빌리면 한번 다시 보자.

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int no_of_songs, song_len[50]; 
double prob[50][50];
int fav_songs[50];
int K;

// double rows[5][50];
double memo[5][50];

class SquareMatrix
{
    private:
        vector<vector<double>> v;
        int mSize;
    public:
        SquareMatrix(int n) : mSize(n)
        {
            v.resize(mSize, vector<double>(mSize, 0));
        }
        ~SquareMatrix()
        {
            for(int i = 0; i< mSize; i++)
                v[i].clear();
            v.clear();
        }
        SquareMatrix identity(int n){
            SquareMatrix result = SquareMatrix(n);
            for(int i=0; i<n; i++)
                for(int j=0; j<n; j++)
                    if(i == j)
                        result.v[i][j] = 1;
                    else
                        result.v[i][j] = 0;
            return result;
        }
        SquareMatrix operator*(SquareMatrix &b){
            SquareMatrix result = SquareMatrix(mSize);
            for(int i = 0; i< mSize; i++)
                for(int j=0; j < mSize; j++)
                    for(int k=0; k < mSize; k++)
                        result.v[j][k] += v[j][i] * b.v[i][k];
            return result;
        }
        SquareMatrix pow(int k){
            if(k == 0)
                return identity(mSize);
            if(k % 2 == 1)
                return pow(k-1) * (*this);
            SquareMatrix half = pow(k / 2);
            return half * half;
        }
        double *operator[](int i){
            return &v[i][0];
        }
};

vector<double> getProb(void){
    SquareMatrix W(4 * no_of_songs);

    for(int i=0; i<3 * no_of_songs; i++)
        W[i][i + no_of_songs] = 1;
    
    for(int i=0; i<no_of_songs; i++){
        for(int j=0; j<no_of_songs; j++){
            W[3 * no_of_songs + i][no_of_songs * (4-song_len[j]) + j] = prob[j][i];
        }
    }
    
    SquareMatrix Wk = W.pow(K);
    vector<double> result(no_of_songs, 0);
    for(int i=0; i<no_of_songs; i++){
        for(int j=0; j<song_len[i]; j++){
            result[i] += Wk[(3 - j) * no_of_songs + i][3 * no_of_songs];
        }
    }
    return result;
}

int main() {
    int i,j,k,l,m,no_of_fav_songs;
    double answer = 0.0;
    vector<double> result;
    // memset(memo, 0, sizeof(memo));
    for(i=0, scanf("%d\n", &j); i<j; i++){
        result.clear();
        scanf("%d %d %d\n", &no_of_songs, &K, &no_of_fav_songs);

        for(k=0; k<no_of_songs; k++){
            scanf("%d \n", &song_len[k]);
        }
        for(k=0; k<no_of_songs; k++){
            for(l=0; l<no_of_songs; l++){
                scanf("%lf \n", &prob[k][l]);
            }
        }
        for(k=0; k<no_of_fav_songs; k++){
            scanf("%d \n", &fav_songs[k]);
        }

        result = getProb();
        for(k=0; k<no_of_fav_songs; k++){
            printf("%.8lf ", result[fav_songs[k]]);
        }
        printf("\n");
    }
    return 0;
}

