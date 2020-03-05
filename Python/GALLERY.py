## DFS와 span tree를 이용한 문제.
## 어려운 문제는 아니지만, 사이클이 없다는 것을 눈치채는것과
## 사이클이 없는 그래프는 트리로 볼 수 있다는 것을 잘 기억해두자!
## 혼자 힘으로 풀지 못했다ㅠ

import sys

visited = []
installed = 0
gal_nums = 0; cor_nums = 0;
def dfs(start, adj):
    ## Unwatched, watched, checked를 각각 0,1,2로 표현
    global visited, installed
    child_status = [0,0,0]
    visited[start] = True
    for child in adj[start]:
        if not visited[child]:
            child_status[dfs(child, adj)] +=1

    if child_status[0] > 0:
        ## unwatched인 child가 하나라도 있을 때는 무조건 install해야 한다
        installed +=1
        return 2;
    
    if child_status[2] > 0:
        ## checked된 child가 하나라도 있으면 굳이 check할 필요 x
        return 1;

    return 0


def main():
    global visited, gal_nums, cor_nums, installed
    for _ in range(int(input().strip())):
        installed = 0
        gal_nums, cor_nums = map(int, input().strip().split())
        adj = [[] for _ in range(gal_nums)]
        visited = [False] * gal_nums
        for _ in range(cor_nums):
            n1, n2 = map(int, input().strip().split())
            adj[n1].append(n2)
            adj[n2].append(n1) 
        for i in range(gal_nums):
            if not visited[i]:
                if dfs(i, adj) == 0:
                    installed += 1
        print(installed)

if __name__ == '__main__':
    main()
    