## 간단한 topological sort 문제

import sys

adj = 26 * [[]]
checked = [False] * 26
top_order = []

def toNumber(w):
    ret = ord(w) - 97
    if ret < 0 or ret > 25:
        return 0
    return ord(w) - 97

def toLetter(n):
    return chr(n + 97)

def dfs(start):
    global checked, adj, top_order
    if checked[start]:
        return
    checked[start] = True
    for i in range(26):
        if adj[start][i] and not checked[i]:
            dfs(i)
    top_order.append(start)

def main():
    global checked, adj, top_order
    for _ in range(int(input().strip())):
        invalid = False
        starts = [True] * 26
        words = []
        top_order = []
        checked = [False] * 26
        adj = [[False] * 26 for _ in range(26)]
        for _ in range(int(input().strip())):
            w = input().strip()
            if len(words) > 0:
                for i in range(min(len(w), len(words[-1]))):
                    if w[i] == words[-1][i]:
                        continue
                    else:
                        if adj[toNumber(w[i])][toNumber(words[-1][i])]:
                            invalid = True
                            break
                        if starts[toNumber(w[i])]:
                            starts[toNumber(w[i])] = False
                        adj[toNumber(words[-1][i])][toNumber(w[i])] = True
                        break
            # if invalid:
            #     break
            words.append(w)
        if invalid:
            print("INVALID HYPOTHESIS")
            continue

        for i in range(26):
            if starts[i]:
                dfs(i)
        top_order.reverse()
        print(*list(map(lambda x: chr(x + 97), top_order)), sep = '')
    # print(top_order)
    # for i in range(25, -1, -1):
        
                
if __name__ == '__main__':
    main()
    