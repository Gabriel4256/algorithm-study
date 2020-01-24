## 알고리즘도 맞고, 여기서 돌려봤을 때는 아무 문제가 없는 코드인데, 채점 서버에서 돌리면 입출력에서부터 에러가 난다.
## 거지같은 알고스팟 ㅅㅄㅄㅄㅅㅄㅄㅄㅄㅄㅄㅄㅄ
## 결국 C++로 옮겨서 해결, 나중에 시간나면 고쳐서 다시 해봐야겠다.

import sys
import math
from functools import reduce

memo = []
sys.setrecursionlimit = 10**8

def get_prob(s_index, prev_word):
    """
    주어진 문장에서의 시작 index (단어의 index)와 그 전의 word가 주어졌을 때 최대 확률을 계산
    """
    result = 0
    # 시작일 경우
    if s_index >= sen_len:
        return 1.0
    if memo[s_index][prev_word] != -1:
        return memo[s_index][prev_word]
    cur_word_ind = words.index(sen[s_index])
    if s_index == 0:
        for i in range(no_of_word):
            cur_prob = first_word_prob[i] * wrong_word_prob[i][cur_word_ind]
            if cur_prob != -math.inf:
                result = max(result, cur_prob * get_prob(s_index + 1, i))
    else:
        for i in range(no_of_word):
            cur_prob = next_word_prob[prev_word][i] * wrong_word_prob[i][cur_word_ind]
            if cur_prob !=-math.inf:
                result = max(result, cur_prob * get_prob(s_index + 1, i))
    memo[s_index][prev_word] = result
    return result

def reconstruct(s_index, prev_word, answer):
    if s_index >= len(sen):
        return
    cur_word_ind = words.index(sen[s_index])
    if s_index == 0:
        for i in range(no_of_word):
            cur_prob = first_word_prob[i] * wrong_word_prob[i][cur_word_ind]
            result = cur_prob * get_prob(s_index + 1, i)
            if result == get_prob(s_index, 0):
                answer.append(words[i])
                reconstruct(s_index + 1, i, answer)
                break
    else:
        for i in range(no_of_word):
            cur_prob = next_word_prob[prev_word][i] * wrong_word_prob[i][cur_word_ind]
            result = cur_prob * get_prob(s_index + 1, i)
            if result == get_prob(s_index, prev_word):
                answer.append(words[i])
                reconstruct(s_index + 1, i, answer)
                break


if __name__ == "__main__":
    ##
    # no_of_word, no_of_sentence = map(int, input().strip().split())
    # words = input().strip().split()
    # first_word_prob = [float(x) for x in sys.readline().strip().split()]
    # next_word_prob = []
    # wrong_word_prob = []
    # sen_len = 0
    # sen = []
    ##

    no_of_word, no_of_sentence = [int(x) for x in sys.stdin.readline().strip().split()]
    words = sys.stdin.readline().strip().split()
    first_word_prob = [float(x) for x in sys.stdin.readline().strip().split()]
    next_word_prob = [0] * no_of_word 
    wrong_word_prob = [0] * no_of_word
    sen_len = 0
    sen = []


    for i in range(no_of_word):
        next_word_prob[i] = [float(x) for x in sys.stdin.readline().strip().split()]
    for i in range(no_of_word):
        wrong_word_prob[i] = [float(x) for x in sys.stdin.readline().strip().split()]

    for _ in range(no_of_sentence):
        tmp = sys.stdin.readline().strip().split()
        sen_len = int(tmp[0])
        sen = tmp[1:]
        memo = [[-1] * no_of_word for _ in range(sen_len)]
        answer = [] 
        reconstruct(0, 0, answer)
        # print(reduce(lambda x, y: x + " "  + y, answer))

