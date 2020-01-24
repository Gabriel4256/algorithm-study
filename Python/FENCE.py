# https://hsp1116.tistory.com/31 참조
# 스위핑 알고리즘 + 스택 사용하여 해결

# 스위핑 기법과 stack 사용, 잘 기억해둘 것

import sys

i = int(input())
st = []
for j in range(i):
    st = []
    result = 0
    num = int(input())
    blocks = input()
    blocks = list(map(int, blocks.split(' ')))
    blocks.append(0)
    
    area = 0
    length = 0
    for i in range(num + 1):
        while st and blocks[i] <= blocks[st[-1]]:
            pos = st[-1]
            del st[-1]
            if not st:
                length = i
            else:
                length = i -st[-1] -1 
            area = length * blocks[pos]
            result = max(result, area) 
        st.append(i)
    print(result)