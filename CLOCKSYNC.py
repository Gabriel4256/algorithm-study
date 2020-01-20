# 파이썬 시간제한 때문에 테스트 불가능

import sys

info = [[False for i in range(16)] for j in range(10)]
info[0][0] = True; info[0][1] = True; info[0][2] = True
info[1][3] = True; info[1][7] = True; info[1][9] = True; info[1][11] = True 
info[2][4] = True; info[2][10] = True; info[2][14] = True; info[2][15] = True
info[3][0] = True; info[3][4] = True; info[3][5] = True; info[3][6] = True; info[3][7] =True
info[4][6] =True; info[4][7] =True; info[4][8] =True; info[4][10] =True; info[4][12] =True
info[5][0] = True; info[5][2] =True; info[5][14] =True; info[5][15] =True
info[6][3] =True; info[6][14] =True; info[6][15] =True
info[7][4] =True; info[7][5] =True; info[7][7] =True; info[7][14]=True; info[7][15]=True
info[8][1]=True; info[8][2] =True; info[8][3] =True; info[8][4] =True; info[8][5]=True
info[9][3]=True; info[9][4]=True; info[9][5] =True; info[9][9] =True; info[9][13] =True

def wind(swn, clocks):
    for i in range(16):
        if info[swn][i]:
            if clocks[i] == 3:
                clocks[i] = 6
            elif clocks[i] == 6:
                clocks[i] = 9
            elif clocks[i] == 9:
                clocks[i] = 12
            else:
                clocks[i] = 3
    
def get_num(clocks, swtchnum):
    minn = 1000000
    swtchcnt = 0
    if clocks == [12 for i in range(16)]:
        return (True, 0)
    for i in range(0,4):
        tmpc = clocks[::]
        for j in range(i):
            wind(swtchnum, tmpc)
        tmp = get_num(tmpc, swtchnum + 1)
        if tmp[0]:
            minn = min(minn, tmp[1] + i)
    if minn == 1000000:
        return (False, -1)
    return (True, minn)

i = int(input())
minnum = 0

for j in range(i):
    tmp = input()
    tmp = tmp.split(' ')
    clocks = tmp
    print(get_num(clocks, 0)[1])
