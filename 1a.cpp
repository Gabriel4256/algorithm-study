#include <iostream>
using namespace std;

int main()
{
    int i, j, k, l, p, m, t;
    int price[1000];
    double min = -1;
    int sum;
    cin >> i;
    for(j=0; j<i; j++){
        min = -1;
        cin >> k; // # of days
        cin >> l; // # of teams
        
        if(l ==0 || k ==0){
            return 0;
        }

        for(p=0; p<k; p++){
            cin >> price[p];    
        }
        
        for(p=l; p<k+1; p++){
            for(m =0; m < k-p + 1; m++){
                for(sum=0, t=m; t< m + p; t++){
                    sum+=price[t];
                }
                if(min == -1 || min > (double)sum / p){
                    min = (double)sum /p;
                }
            }
        }
        
        cout.precision(12);
        cout<<fixed;
        std::cout << min << std::endl;
    }
    return 0;
}
