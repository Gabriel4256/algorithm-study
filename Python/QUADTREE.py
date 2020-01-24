import sys
from functools import reduce

def get_segs(s):
    result = []
    index = 0
    cnt = 0
    while cnt< 4:
        if s[index] != 'x':
            result.append(s[index])
            index +=1
        else:
            tmp = get_segs(s[index+ 1: ])
            tmp = reduce(lambda x,y: x+y, tmp)
            result.append('x' + tmp)
            index += 1 + len(tmp)
        cnt+=1
    return result
            
        
    
def get_rev(s):
    tmp =  ['', '', '', '']
    result = ''
    if s == 'w' or s == 'b':
        return s
    if s[0] == 'x':
        tmp = get_segs(s[1:])
    for i in range(4):
        tmp[i] = get_rev(tmp[i])
    return 'x' + tmp[2] + tmp[3] + tmp[0] + tmp[1]
            
i = input()
for j in range(int(i)):
    s = input()
    print(get_rev(s))
    
    