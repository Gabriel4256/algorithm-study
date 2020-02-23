// 구간 트리를 이용한 문제.
// 그리 어려운 문제는 아니었다. 구간 트리의 구현을 잘 기억해 두자.
// pair를 써서 min, max를 모두 저장하는 구간 트리 하나를 만드는 것 보다
// min, max를 저장하는 구간 트리 두개를 만드는 게 더 빠르다.
// 왜인지는 정확히는 모르겠다. 아무래도 pair에 접근하는게 int보다 훨씬 느린 것(3배 이상) 같다.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INT_MAX = numeric_limits<int>::max();

// 구간 트리 구현
struct RMQ {
    // 배열의 길이
    int n;

    //각 구간의 최소치
    vector<int> rangeMinMax;
    RMQ(const vector<int>& array){
        n = array.size();
        rangeMinMax.resize(n * 4);
        init(array, 0, n-1, 1);
    }

    // node 노드가 array[left...right] 배열을 표현할 때
    // node를 루트로 하는 서브트리를 초기화하고, 이 구간의 최소치를 반환한다.
    int init(const vector<int>& array, int left, int right, int node){
        if(left == right)
            return rangeMinMax[node] = array[left];
        int mid = (left + right) / 2;
        int leftMin = init(array, left, mid, node * 2);
        int rightMin = init(array, mid+1, right, node * 2 + 1);
        return rangeMinMax[node] = min(leftMin, rightMin);
    }

    // node가 표현하는 범위 array[nodeLeft..nodeRight]가 주어질 때
    // 이 범위와 array[left..Right]의 교집합의 최소치를 구한다.
    int query(int left, int right, int node, int nodeLeft, int nodeRight){
        // 두 구간이 겹치지 않으면 아주 큰 값을 반환
        if(right < nodeLeft || nodeRight < left) return INT_MAX;
        
        //node가 표현하는 범위가 array[left..right]에 완전히 포함되는 경우
        if(left <= nodeLeft && nodeRight <= right)
            return rangeMinMax[node];
        
        //양쪽 구간을 나눠서 푼 뒤 결과를 합친다.
        int mid = (nodeLeft + nodeRight) /  2;
        int minVal = min(
                        query(left, right, 2 * node, nodeLeft, mid),
                        query(left, right, 2 * node + 1, mid + 1, nodeRight)
                    );
        return minVal;
    }

    //query를 외부에서 호출하기 위한 인터페이스
    int query(int left, int right){
        return query(left, right, 1, 0, n-1);
    }

    // array[index] = newValue로 바뀌었을 때 node를 루트로 하는
    // 구간 트리를 갱신하고 노드가 표현하는 구간의 최소치를 반환한다.
    int update(int index, int newValue, int node, int nodeLeft, int nodeRight){
        
        // index 노드가 표현하는 구간과 상관없는 경우엔 무시한다.
        if(index < nodeLeft || index > nodeRight)
            return rangeMinMax[node];

        // 트리의 리프까지 내려온 경우
        if(nodeLeft == nodeRight) 
            return rangeMinMax[node] = newValue;
        
        int mid = (nodeLeft + nodeRight) / 2;
        int minVal = min(
                        update(index, newValue, 2 * node, nodeLeft, mid), 
                        update(index, newValue, 2 * node + 1, mid + 1, nodeRight)
                    );
        return rangeMinMax[node] = minVal;
    }

    // update를 외부에서 호출하기 위한 인터페이스
    int update(int index, int newValue){
        return update(index, newValue, 1, 0, n-1);
    }
};
///////////



int main(){
    int i,j,k, N, Q;
    vector<int> signs, minusSigns;
    for(scanf("%d", &j), i=0; i<j; i++){
        cin >> N >> Q;
        minusSigns.clear();
        minusSigns.resize(N);
        signs.clear();
        signs.resize(N);
        for(k=0; k<N; k++){
            int tmp;
            scanf("%d", &tmp);
            signs[k] = tmp;
            minusSigns[k] = -tmp;
        }
        RMQ* rmq = new RMQ(signs);
        RMQ* rmq2 = new RMQ(minusSigns);
        
        for(k=0; k<Q; k++){
            int tmp1, tmp2;
            scanf("%d %d", &tmp1, &tmp2);
            int minVal = rmq->query(tmp1, tmp2);
            int maxVal = -rmq2->query(tmp1, tmp2);
            printf("%d\n", maxVal - minVal);
        }
        delete rmq; delete rmq2;
    }
}