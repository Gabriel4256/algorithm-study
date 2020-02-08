## 정말 어려운 문제였다. 거의 이틀 정도를 썼고, 책을 참고하면서도 쉽게 풀리지 않았다.
## 특히 어려웠던 부분은 
##  1.각 칸에서 선택할 수 있는 숫자들을 bitmask 형태로 나타내는 아이디어와
##  2.탐색의 단위를 각 칸별로 할 건지, 아니면 힌트 별로 할건지 결정하는 것과
##  3. 이를 결정했을 때 어떤 식으로 CSP를 구현할 것인지 였다. (자료구조 등)

## p.s 기회가 되면 비슷한 문제를 다시 풀어보는게 좋겠다.

from functools import reduce
global width, board, hints, mapping, checked, answer, find, candidates

def no_of_1s(bits):
    '''get the number of 1s in bits'''
    cnt = 0
    for i in range(0, 10):
        if bits & (1 << i) > 0:
            cnt+=1
    return cnt

def get_sum(bits):
    '''get the sum of corresponding bits'''
    result = 0
    for i in range(0, 10):
        if bits & (1 << i) > 0:
            result += i
    return result 

def generate_candidates():
    global candidates
    candidates = [[[0] * 1024 for _ in range(46)] for _ in range(10)]
    for i in range(0, 1024, 2):
        s = get_sum(i)
        l = no_of_1s(i)
        for j in range(0, i+1, 2):
            if i & j == j:
                candidates[l][s][j] |= (i & ~j)
            
def get_candidates(length, summ, known):
    global candidates

    return candidates[length][summ][known]

    result = 0
    for i in range(2, 1025, 2):
        if no_of_1s(i) == length and get_sum(i) == summ and (i & known) == known:
            result |= i
    return result & ~known

def print_answer():
    s = ""
    for i in range(width):
        for j in range(width):
            if answer[i][j]:
                s += str(answer[i][j]) + " "
            else:
                s += str(0) + " "
        s += '\n'
    print(s)

            

def search():
    global hints, width, find
    target = (-1, -1)
    minval = (1 << 10) - 1
    if find:
        return
    # for hint in hints:
    #     if hint[2] == 0:
    #         for i in range(hint[1] + 1, width + 1):
    #             if i == width or board[i][hint[1]] != 1 or width:
    #                 continue
    #             if not answer[hint[0]][i]:
    #                 target = (hint[0], i)
    #                 break
    #     else:
    #         for i in range(hint[0] + 1, width + 1):
    #             if i== width or board[i][hint[1]] != 1:
    #                 continue
    #             if not answer[i][hint[1]]:
    #                 target = (i, hint[1])
    #                 break
    for i in range(width):
        for j in range(width):
            if not answer[i][j] and board[i][j] == 1:
                h1, h2 = mapping[i][j]
                cand = get_candidates(h1[4], h1[3], h1[5]) & get_candidates(h2[4], h2[3], h2[5])
                if no_of_1s(cand) < no_of_1s(minval):
                    minval = cand
                    target = (i, j)
                

    if target == (-1, -1):
        find = True
        print_answer()
        return
        
    
    h1, h2 = mapping[target[0]][target[1]]
    # candidates =  get_candidates(h1[4], h1[3], h1[5]) & get_candidates(h2[4], h2[3], h2[5]) 
    if minval == 0:
        return
    for i in range(1, 10):
        if (1 << i) & minval > 0:
            h1[5] |= (1 << i)
            h2[5] |= (1 << i)
            answer[target[0]][target[1]] = i
            search()
            if find:
                return
            h1[5] -= (1 << i)
            h2[5] -= (1 << i)
            answer[target[0]][target[1]] = False
        
    
    

def get_len(y, x, direction):
    '''get the list of grids to summate'''
    global board, mapping, hints
    result = []
    cnt = 0
    if direction == 0:
        ## horizontal
        for i in range(x+1, width+1):
            if i == width or board[y][i] != 1:
                return i - x - 1
            if mapping[y][i] == 0:
                mapping[y][i] = []
            mapping[y][i].append(hints[-1])
    else:
        ## vertical
        for i in range(y+1, width+1):
            if i == width or board[i][x] != 1:
                return i - y - 1 
            if mapping[y][i] == 0:
                mapping[y][i] = []
            mapping[i][x].append(hints[-1])

def initialize():
    global board, hints, mapping, answer, find, width
    board = []
    find = False
    hints = []
    width = int(input().strip())
    mapping = [[0] * width for _ in range(width)]
    answer = [[False] * width for _ in range(width)]
    generate_candidates()


def main():
    global width, board, hints
    for _ in range(int(input())):
        initialize()
        for _ in range(width):
            board.append(list(map(int, input().strip().split())))
        no_of_hints = int(input().strip())
        for _ in range(no_of_hints):
            a,b,c,d = map(int, input().strip().split())
            hints.append([a-1, b-1, c, d])
            length = get_len(a-1, b-1, c)
            hints[-1].append(length)
            hints[-1].append(0)
            # board[a-1][b-1] = [c, d, tmp, 0]
            # priority.append((a-1, b-1, c, d))
        hints = sorted(hints, key=lambda x: x[4])
        search()

if __name__ == "__main__":
    main()