## 강결합 컴포넌트를 이용한 문제
## 정말 어려운 문제였다. 처음 접한 2-SAT문제였는데, 이런 식으로 풀거라는 건 상상도 못했다.
## 어떤 사건의 발생/비발생을 각각 노드로 만들어서 의존 관계를 만들어 가는 것이 신기했다.
## 또한 타잔의 강결합 컴포넌트 탐색 알고리즘을 사용했는데 이것도 작성하는 연습을 꼭 해야겠다.

## 위상정렬을 한 다음 만나는 컴포넌트를 순서대로 거짓으로 분류하는데 이것이 왜 작동하는지 정확히
## 이해가 안된다.

discovered = []
finished =[]
dCounter = 0
sccCounter = 0

stack = []
adj = []
sccId = []

def overlap(m1, m2):
    return not (m1[1] <= m2[0] or m2[1] <= m1[0])

def scc(here):
    global discovered, finished, stack, adj, dCounter, sccId, sccCounter

    stack.append(here)
    discovered[here] = dCounter
    dCounter += 1

    ret = discovered[here]

    for there in adj[here]:
        if discovered[there] == -1:
            ## not discovered yet
            ret = min(ret, scc(there))

        elif discovered[there] < discovered[here] and not finished[there]:
            ret = min(ret, discovered[there])
    
    if ret == discovered[here]:
        while True:
            t = stack.pop(-1)
            sccId[t] = sccCounter
            if t == here:
                break
        sccCounter += 1
    
    finished[here] = True
    return ret


def tarjanSCC():
    global discovered, finished, dCounter, sccCounter, sccId, adj, stack
    sccId = [-1] * len(adj)
    discovered = [-1] * len(adj)
    finished = [False] * len(adj)
    sccId = [-1] * len(adj)
    dCounter = sccCounter = 0
    stack = []

    for i in range(len(adj)):
        if sccId[i] == -1:
            scc(i)

def makeGraph(times):
    global adj
    adj = [[] for _ in range(2 * len(times))]
    for i in range(0, len(times), 2):
        adj[2 * i].append(2 * (i + 1) + 1) ## !A -> B
        adj[2 * i + 1].append(2 * (i + 1)) ## A -> !B
        adj[2 * (i + 1)].append(2 * i + 1) ## !B -> A
        adj[2 * (i + 1) + 1].append(2* i)  ## B -> !A
    
    for i in range(len(times)):
        for j in range(i+1, len(times)):
            if overlap(times[i], times[j]):
                ## 회의 두개가 겹치는 경우
                adj[2 * i + 1].append(2 * j) ## i -> !j
                adj[2 * j + 1].append(2 * i) ## j -> !i
    
def solve(times):
    global sccId
    tarjanSCC()
    
    for i in range(0, len(sccId), 2):
        if sccId[i] == sccId[i+1]:
            return False

    nodes = []
    for i in range(len(sccId)):
        nodes.append((sccId[i], i))
    nodes = sorted(nodes, key= lambda x: x[0], reverse = True)

    chosen = [-1] * (len(nodes) // 2)
    for i in range(len(nodes)):
        val = nodes[i][1] // 2
        isTrue = (nodes[i][1] % 2) == 1
        if chosen[val] != -1:
            continue
        chosen[val] = not isTrue
    
    ret = []
    for i in range(len(times)):
        if chosen[i]:
            ret.append(str(times[i][0]) + " " + str(times[i][1]))
    return ret

def main():
    for _ in range(int(input().strip())):
        times = []
        for _ in range(int(input().strip())):
            a1, a2, b1, b2 = map(int, input().strip().split())
            times.append((a1, a2))
            times.append((b1, b2))
        makeGraph(times)
        answer = solve(times)
        if not answer:
            print("IMPOSSIBLE")
        else:
            print("POSSIBLE")
            print(*answer, sep = '\n')

if __name__ == "__main__":
    main()