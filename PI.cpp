    //59번째 줄에서 무한대 값을 어떤식으로 처리했는지 잘 기억해두자 (1e9)
    //진짜 개고생했다;;;;

    #include <iostream>
    #include <limits>
    #include<bits/stdc++.h> 
    using namespace std;

    string S;
    int memo[10002];


    int get_pattern_score(string s){
        int result = 10;
        bool arith_seq = true;
        bool alternating = true;

        if(s == string(s.size(), s[0])){
            // 모두 같을 때
            return 1;
        }
        
        // 등차수열인지 확인
        for(int i=0; i< s.size() - 1; ++i){
            if(s[i+1] - s[i] != s[1] - s[0]){
                arith_seq = false;
            }
        }

        // 두 숫자가 번갈아가며 나타나는지 확인
        for(int i=0; i<s.size(); ++i){
            if(s[i] != s[i % 2]){
                alternating = false;
            }
        }

        if(arith_seq){
            result = min(result, 5);
            if(s[1] - s[0] == 1 || s[1] - s[0] == -1){
                result = min(result, 2);
            }
        }
        if(alternating){
            result = min(result, 4);
        }
        // std::cout << result << std::endl;
        return result;
    }

    int get_min_comp(int start){
        //[start, end] 구간의 난이도 계산
        if(start == S.size()){
            return 0;
        }
        int& ret = memo[start];
        if(ret != -1){
            return ret;
        }
        ret = 1e9;
        for(int i=3; i<=5; ++i){
            if(start + i <= S.size()){
                ret = min(ret, get_min_comp(start + i) + get_pattern_score(S.substr(start, i)));
            }
        }
        return ret;
    }

    int main()
    {
        int n;
        char mybuffer[500001];
        setvbuf(stdin, mybuffer, _IOFBF, sizeof(mybuffer));

        cin >> n;
        for(int i=0; i<n; i++){
            cin >> S;
            fill_n(memo, 10002, -1);
            std::cout << get_min_comp(0) << std::endl;
        }

        return 0;
    }
