    //예외 case들 잘 확인하고, 나눗셈할 때 필요에 따라 double로 형변환하고 하는 것 잊지 말기
    //memset 잊지 말자, 초기화에 유용

    #include <iostream>
    #include <vector>
    #include <algorithm>
    #include <cstring>
    #include <cmath>
    using namespace std;

    int memo[102][12] = {-1,};
    int sq_sums[102] = {-1,};
    int sums[102] = {-1,};
    int len = 0;

    int get_min_err(int start, int end, vector<int> &numbers){
        if(start > end)
            return 0;
        int s, sq;
        s = (start == 0) ? 0 : sums[start-1];
        sq = (start == 0) ? 0: sq_sums[start-1];
        int avg = round((double)(sums[end] - s) / (end-start+1));
        int ai2 = sq_sums[end] - sq;
        int ai = sums[end] - s;
        return ai2 - 2* avg * ai + avg * avg * (end-start + 1); 
    }

    int quantize(int start, vector<int> &numbers, int numcnt){
        int& ret = memo[start][numcnt];
        if(ret != -1)
            return ret;
        ret = 1e9; 

        if(numcnt == 1){
            ret = get_min_err(start, numbers.size() - 1, numbers);
        }
        else{
            for(int i=start; i<numbers.size(); ++i){
                ret = min(ret, get_min_err(start, i-1, numbers) + quantize(i, numbers, numcnt-1));
            }
        }
        return ret;
    }

    int main()
    {
        int i;
        cin >> i;
        for(int j=0; j<i; j++){
            int numcnt, tmp;
            vector<int> numbers;
            cin >> len; cin >> numcnt;
            
            for(int k=0; k<len; k++){
                cin >> tmp;
                numbers.push_back(tmp);
            }
            sort(numbers.begin(), numbers.end());
            memset(memo, -1, sizeof(memo));
            memset(sq_sums, -1, sizeof(sq_sums));
            memset(sums, -1, sizeof(sums));

            for(int k=0; k<len; k++){
                if(k == 0){
                    sums[k] = numbers[k];
                    sq_sums[k] = numbers[k] * numbers[k];
                }
                else{
                    sums[k] = sums[k-1] + numbers[k];
                    sq_sums[k] = sq_sums[k-1] + numbers[k] * numbers[k];
                }
            }
            std::cout << quantize(0, numbers, numcnt) << std::endl;
        }

        return 0;
    }
