## 쉬운 문제, 실수를 줄이자.

global memo

def decrypt(board_state):
    answer = []
    for i in range(3):
        tmp = []
        for j in range(3):
            num = (board_state >> (2 * (i * 3 + j))) & 3
            tmp.append(num)
        answer.append(tmp)
    return answer

def check_winner(board_state):
    arr = decrypt(board_state)
    for i in range(3):
        if arr[i] == [1] * 3 or arr[i] == [2] * 3:
            return arr[i][0]
        if arr[0][i] > 0 and arr[0][i] == arr[1][i] and arr[1][i] == arr[2][i]:
            return arr[0][i]
    if arr[0][0] > 0 and arr[0][0] == arr[1][1] and arr[1][1] == arr[2][2]:
        return arr[0][0]
    if arr[0][2] > 0 and arr[0][2] == arr[1][1] and arr[1][1] == arr[2][0]:
        return arr[0][2]
    return 0

def find_winner(board_state, turn, level):
    global memo
    if memo[board_state] != -1:
        return memo[board_state]
    tmp = check_winner(board_state)
    if tmp > 0:
        return tmp
    if level == 10:
        return 0
    result = -1
    for i in range(9):
        if (board_state >> (2 * i)) & 3 == 0:
            modified_state = board_state | (turn << (2 * i))
            tmp_result = find_winner(modified_state, 3 - turn, level + 1)
            if tmp_result == turn:
                result = tmp_result
                break
            elif tmp_result == 0:
                result = tmp_result
            else:
                if result != 0:
                    result = tmp_result
    memo[board_state] = result
    return result    
    

def main():
    global memo
    for _ in range(int(input())):
        counter = 0
        board_state = 1 << 18;
        xnum = 0; onum = 0;
        memo = [-1] * (1 << 19)
        for _ in range(3):
            for l in input().strip():
                if l == 'x':
                    board_state |= (1 << (counter * 2))
                    xnum +=1
                elif l == 'o':
                    board_state |= (2 << (counter * 2))
                    onum +=1
                counter += 1
        turn = 1
        if onum < xnum:
            turn = 2
        winner = find_winner(board_state, turn, xnum + onum + 1)
        if winner == 0:
            print('TIE')
        elif winner == 1:
            print('x')
        else:
            print('o')

if __name__ == "__main__":
    main()