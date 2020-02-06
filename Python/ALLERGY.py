## 그렇게 어려운 문제는 아니었다. 다만, 음식 -> 친구 관계를 친구 -> 음식 관계로 바꾸는 것이 주요했고,
## Python이다 보니 그 외에도 탐색 순서를 최적화해서 prune되는 가지들이 많도록 추가했다.

global friends, foods, no_of_friends, no_of_foods, eat, eaten_by
global served, least, satisfied, state, no_of_1s, priority

def get_no_of_1s(bit):
    cnt = 0
    for i in range(50):
        if ((1 << i) & bit) > 0:
            cnt+=1
    return cnt

def prune(chosen, state):
    global least, no_of_1s
    cnt = 0
    remaining = no_of_friends - get_no_of_1s(state)
    # l = sorted(no_of_1s, key=lambda x: -x)
    for i in range(len(no_of_1s)):
        if remaining <=0:
            break
        remaining -= no_of_1s[i]
        cnt+=1
    

    return remaining > 0 or cnt + chosen >= least
        
def search(chosen, state):
    global no_of_foods, least, satisfied, no_of_friends, eat, priority
    
    idx  = -1
    if prune(chosen, state):
        return
    
    if state == ((1 << no_of_friends) - 1):
        least = min(least, chosen)
        return
    for i in priority:
        if state & (1 << i) == 0:
            idx = i
            break
    for food in eat[idx]:
        search(chosen + 1, state | eaten_by[food])
    
def main():
    global friends, foods, no_of_friends, no_of_foods, eat, eaten_by, no_of_1s, least, eat
    global priority
    for i in range(int(input())):
        state = 0
        no_of_friends, no_of_foods = map(int, input().strip().split())
        least = 500
        no_of_1s = [0] * no_of_foods
        eaten_by = [0] * no_of_foods
        eat = [[] for _ in range(no_of_friends)]
        priority = [i for i in range(0, no_of_friends)]
        friends = input().strip().split()
        for i in range(no_of_foods):
            tmp = input().strip().split()
            for j in range(1, len(tmp)):
                eaten_by[i] += 1 << friends.index(tmp[j])
                no_of_1s[i] += 1
                eat[friends.index(tmp[j])].append(i)
        priority = sorted(priority, key=lambda x: len(eat[x]))
        no_of_1s.sort(reverse=True)
        search(0, 0)
        print(least)
if __name__ == "__main__":
    main()
    

    