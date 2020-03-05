## 오일러 서킷/트레일을 활용한 문제
## DFS를 활용하여 해결 가능하다.
## 그렇게 어려운 문제는 아니었지만 예외처리에 좀 공을 들여야 한다.

import sys

def toNumber(s):
    return ord(s) - 97

def toLetter(s):
    return chr(s + 97)

def getEulerCircuit(here, adj, path):
    for there in range(26):
        while adj[here][there]> 0:
            adj[here][there] -= 1
            getEulerCircuit(there, adj, path)
            # path.append(adj[here][there].pop())
    path.append(here)

def solve(edges, adj):
    start = -1; end = -1
    path = []
    for i in range(26):
        if edges[i][0] == edges[i][1]:
            continue
        elif edges[i][0] + 1 == edges[i][1]:
            if start != -1:
                return False
            start = i
        elif edges[i][0] == edges[i][1] + 1:
            if end != -1:
                return False
            end = i
        else:
            return False
    if start != -1 and end != -1:
        getEulerCircuit(start, adj, path)
    elif start == -1 and end == -1:
        for i in range(26):
            if edges[i][1] > 0:
                getEulerCircuit(i, adj, path)
                break
    else:
        return False
    return path

def construct(path, words):
    ret = []
    if len(path) == 0:
        return []
    for i in range(0, len(path) - 1):
        # ret.append(words[path[i]][path[i+1]])
        # if len(words[path[i]][path[i+1]]) == 0:
        #     continue
        ret.append(words[path[i]][path[i+1]].pop())
    return ret
        

def main():
    for _ in range(int(input().strip())):
        adj = [[0 for _ in range(26)] for _ in range(26)]
        words = [[[] for _ in range(26)] for _ in range(26)]
        valid = True
        edges = [[0 for _ in range(2)] for _ in range(26)]# no of in, out edges
        word_num = int(input().strip())
        for _ in range(word_num):
            w = input().strip()
            adj[toNumber(w[0])][toNumber(w[-1])] += 1
            words[toNumber(w[0])][toNumber(w[-1])].append(w)
            edges[toNumber(w[-1])][0] += 1
            edges[toNumber(w[0])][1] += 1
        
        ret = solve(edges, adj)
        if not ret or len(ret) != word_num + 1:
            print("IMPOSSIBLE")
            continue
        
        ret.reverse()
        # ret = construct(ret, words)
        print(*construct(ret, words), sep= ' ')
    
if __name__ == '__main__':
    main()
    