## 매우 쉬운 그리디 문제

def main():
    opponents = []
    players = []
    for _ in range(int(input().strip())):
        input()
        opponents = list(map(int, input().strip().split()))
        players = list(map(int, input().strip().split()))
        
        players.sort()
        opponents.sort()
        
        idx = -1
        for i in range(len(players)):
            if players[i] >= opponents[0]:
                idx = i
                break

        if idx == -1:
            print(0)
        else:
            j = idx
            i = 0
            cnt = 0
            while i < len(opponents) and j < len(players):
                if players[j] >= opponents[i]:
                    j+=1
                    i+=1
                    cnt+=1
                else:
                    j+=1
            print(cnt)
                
        

if __name__ == "__main__":
    main()