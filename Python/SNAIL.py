## RTE가 발생했을 때는 overflow가 아닌지 의심

memo = [[-1] * 1001 for _ in range(1001)]

def snail(height, days):
    if memo[height][days] != -1:
        return memo[height][days]
    elif days >= height:
        memo[height][days] = 1
    elif height > 2 * days:
        memo[height][days] = 0
    else:
        memo[height][days] = 0.25 * snail(height-1, days-1) + 0.75* snail(height-2, days-1)
    return memo[height][days]

for _ in range(int(input())):
    # global memo
    height, days = map(int, input().split(' ')) 

    # for j in range(days+1):
    #     for k in range(height + 1):
    #         if k == 0:
    #             memo[j][k] = 1
    #         else:
    #             if j >= k:
    #                 memo[j][k] = 1
    #             elif k > 2 * j:
    #                 memo[j][k] = 0
    #             else:
    #                 memo[j][k] = 0.75 * memo[j-1][k-2] + 0.25 * memo[j-1][k-1]
    
    print(snail(height, days))
                    
            
            