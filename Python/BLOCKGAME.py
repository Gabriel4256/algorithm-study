import sys
sys.setrecursionlimit(10 ** 9)

global memo

def decrpyt(board_state):
    result = [[0] * 5 for _ in range(5)] 
    for i in range(5):
        for j in range(5):
            if board_state & (1 << (i * 5 + j)) == 1:
                result[i][j] = 1
    return result


def puttable_places(board_state):
    decrypted = decrpyt(board_state)
    answer = []
    ## 두조각 체크
    for i in range(5):
        for j in range(5): 
            if decrypted[i][j] == 0:
                if i < 4 and decrypted[i+1][j] == 0:
                    answer.append((5*i + j, 5*(i+1) + j))
                    if j < 4 and decrypted[i][j+1] == 0:
                        answer.append((5*i + j, 5*(i+1) + j, 5*i + j + 1))
                    if j > 1 and decrypted[i][j-1] == 0:
                        answer.append((5*i + j, 5*(i+1) + j, 5*i + j + 1))
                if j < 4 and decrypted[i][j+1] == 0:
                    answer.append((5 * i + j, 5 * i + j + 1))
                if i > 0 and decrypted[i-1][j] == 0:
                    if j < 4 and decrypted[i][j+1] == 0:
                        answer.append((5*i + j, 5*(i-1) + j, 5*i + (j + 1)))
                    if j > 1 and decrypted[i][j-1] == 0:
                        answer.append((5*i + j, 5*(i-1) + j, 5*i + j + 1))
    return answer

def find_winner(board_state, turn):
    global memo
    if memo[board_state] != 0:
        return turn * memo[board_state]
    result = -turn
    modified_state = board_state
    for shape in puttable_places(board_state):
        modified_state = board_state
        for point in shape:
            modified_state = modified_state | (1 << point)
        if turn == find_winner(modified_state, -turn):
            result = turn
    
    memo[board_state] = result / turn
    return result

def main():
    global memo
    for _ in range(int(input().strip())):        
        memo = [0] * (1 << 26)
        board = []
        board_state = 1 << 25
        for _ in range(5):
            board.append(list(input().strip()))
        for i in range(5):
            for j in range(5):
                if board[i][j] == 1:
                    board_state |= 1 << (5 * i + j)
        if find_winner(board_state, 1) == 1:
            print('WINNING')
        else:
            print('LOSING')

if __name__ == "__main__":
    main()