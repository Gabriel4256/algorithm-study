## python으로는 홈페이지에서 통과 불가능
## 저자의 답변은 특이한 테크닉이 있어 실전에서 따라하기는 어려울 듯함

import sys


for i in range(int(input())):
    input()
    A = list(map(int, input().split(' ')))
    B = list(map(int, input().split(' ')))
    
    memo = {}
    result = 0
    for i in range(len(A)-1, -1, -1):
        for j in range(len(B) - 1, -1, -1):
            if i == len(A) - 1 and j == len(B) - 1:
                if A[i] == B[j]:
                    memo[(i,j)] = [A[i]]
                else:
                    memo[(i,j)] = [A[i], B[j]]
                result = max(result, len(memo[(i,j)]))
            else:
                maxv = 0
                if A[i] == B[i]:
                    llist = [A[i]]
                else:
                    llist = [A[i], B[i]]
                # liist = list(set([A[i], B[j]]))
                for k in range(i+1, len(A)):
                    if A[k] > A[i]:
                        if A[i] in memo[(k, j)]:
                            if len(memo[(k, j)]) > maxv:
                                maxv = len(memo[(k, j)])
                                liist = memo[(k,j)]
                        else:
                            if len(memo[(k, j)]) + 1 > maxv:
                                maxv = len(memo[(k, j)]) + 1
                                liist = [A[i]] + memo[(k, j)]
                for k in range(j+1, len(B)):
                    if B[k] > B[j]:
                        if B[j] in memo[(i, k)]:
                            if len(memo[(i, k)]) > maxv:
                                maxv = len(memo[(i, k)])
                                liist = memo[(i,k)]
                        else:
                            if len(memo[(i, k)]) + 1 > maxv:
                                maxv = len(memo[(i, k)]) + 1
                                liist = [B[j]] + memo[(i, k)]
                memo[(i, j)] = liist
                result = max(maxv, result)
    # print(memo)
    print(result)
