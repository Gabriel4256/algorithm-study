## 간단한 최적화 -> 결정 바꿔풀기 문제
## 다만 기지들 간의 거리를 미리 계산해두는 디테일을 기억하자!

global dist

def get_dist(p1, p2):
    return ((p1[0] - p2[0]) ** 2 + (p1[1] -p2[1]) ** 2) ** 0.5

def genenarate_dist(stations):
    global dist
    for i in range(len(stations)):
        for j in range(len(stations)):
            if i < j:
                dist[i][j] = get_dist(stations[i], stations[j])
            elif i > j:
                dist[i][j] = dist[j][i]
            else:
                dist[i][j] = 0

def decision(stations, power):
    checked = [False] * len(stations)
    # checked[0] = True
    queue = [0]
    
    while len(queue) > 0:
        n = queue.pop(0)
        if not checked[n]:
            checked[n] = True
            for i in range(len(stations)):
                if not checked[i] and dist[n][i] <=power:
                    queue.append(i)
    return checked == [True] * len(stations)

def optimize(stations):
    lo = 0; hi = 2000 
    for _ in range(30):
        mid = (lo + hi) / 2
        if decision(stations, mid):
            hi = mid
        else:
            lo = mid
    return hi

def main():
    global dist
    for _ in range(int(input().strip())):
        stations = []
        dist = [[0] * 101 for _ in range(101)]
        for _ in range(int(input().strip())):
            a,b = map(float, input().strip().split())
            stations.append((a,b))
        genenarate_dist(stations)
        print(format(optimize(stations), ".2f"))    

if __name__ == "__main__":
    main()