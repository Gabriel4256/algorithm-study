## 간단한 최적화 -> 결정 문제
## 분명 알고리즘은 맞는데, Python이라서 시간초과가 뜬다.
## CPP로 같은 코드를 짰더니 가볍게 통과했다...

global picket_numbers

def generate_picket_numbers(cities):
    global picket_numbers
    picket_numbers = [[0] * len(cities)]
    for city in cities:
        picket_numbers.append(city[1] / city[2]) 

def decision(cities, distance, K):
    cnt = 0
    for i in range(len(cities)):
        if distance >= cities[i][0]:
            cnt+= cities[i][1] // cities[i][2] + 1
        elif distance <cities[i][0] - cities[i][1]:
            continue
        else:
            cnt+=  (distance - (cities[i][0] - cities[i][1])) // cities[i][2] + 1
    return cnt >= K

def optimize(cities, K):
    lo = 0; hi = 8030001
    for _ in range(22):
        mid = (lo + hi) / 2
        if decision(cities, mid, K):
            hi = mid
        else:
            lo = mid
    return hi

def main():
    for _ in range(int(input().strip())):
        cities = []
        no_of_cities, K = map(int, input().strip().split())
        for _ in range(no_of_cities):
            L, M, G = map(int, input().strip().split())
            cities.append((L, M, G))
        print(int(optimize(cities, K)))

if __name__ == "__main__":
    main()