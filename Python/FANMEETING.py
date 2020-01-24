import sys
# 카라츠바 알고리즘 적용하면 될듯 


# def subTo(a,b):
    

# def addTo(a,b):
#     result = [0 for i in range(max(len(a), len(b)))]
#     for i in range(max(len(a), len(b))):
#         tmp = 0
#         if i < len(a):
#             tmp += a[i]
#         if i < len(b):
#             tmp += b[i]
#         result[i] = tmp
#     return result

# def karatsuba(a, b):
#     if len(a) < len(b):
#         return karatsuba(b, a)
#     if len(a) == 0 or len(b) == 0:
#         return []

#     half = len(a) // 2
    
#     # a의 첫번째 조각
#     pa0 = a[:half]
#     pa1 = a[half:]
    
#     pb0 = b[:min(half, len(b))]
#     pb1 = b[min(half, len(b)):]
    
#     z2 = karatsuba(pa1, pb1)
#     z0 = karatsuba(pa0, pb0)
    
#     a0 = addTo(a0, a1)
#     b0 = addTo(b0, b1)
    
#     z1 = 
    

i = int(input())
for j in range(i):
    members = input()
    fans = input()
    cnt = 0
    
    state = True
    for k in range(0, len(fans) - len(members) + 1):
        state = True
        for l in range(len(members)):
            if members[l] == 'M' and fans[k + l] == 'M':
                state = False
                break
        if state:
            cnt += 1
    print(cnt)