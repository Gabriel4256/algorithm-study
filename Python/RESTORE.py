## 알고리즘은 맞는데, 제출하면 RTE 에러가 뜬다.
## 나중에 시간 나면 해결해보자, 일단은 c++로 포팅하여 제출했다.

import sys

global memo
global memo2
global no_of_word

def combine(w1, w2):
    if w1 == -1:
        return words[w2]
    if memo2[w1][w2] != '':
        return memo2[w1][w2]
    interleaving = 0
    for i in range(min(len(words[w1]), len(words[w2]))):
        if words[w1][-(i+1):] == words[w2][0:i+1]:
            interleaving = i + 1
        else:
            break
    memo2[w1][w2] = words[w2][interleaving:]
    return memo2[w1][w2]

def get_min_comb(chosen, prev_word_idx, level):
    prev_word = ""
    if prev_word_idx != -1:
        if memo[chosen][prev_word_idx] != '':
            return memo[chosen][prev_word_idx];
    if level == -1:
        return 0
    if prev_word_idx == -1:
        prev_word = ""
    else:
        prev_word = words[prev_word_idx]
    result = 600;
    for i in range(no_of_word):
        if chosen & 1 << i != 1 << i:
            modified_chosen = chosen | 1 << i;
            combined = combine(prev_word_idx, i)
            result = min(result, len(combined) + get_min_comb(modified_chosen, i, level -1))
    memo[chosen][prev_word_idx] = result
    return result

def reconstruct(chosen, prev_word_idx, level):
    prev_word = ""
    if level == -1:
        return ""
    if prev_word_idx == -1:
        prev_word = ""
    else:
        prev_word = words[prev_word_idx]
    target = get_min_comb(chosen, prev_word_idx, level)
    for i in range(no_of_word):
        if chosen & 1 << i != 1 << i:
            modified_chosen = chosen | (1 << i);
            combined = combine(prev_word_idx, i)
            if target == len(combined) + get_min_comb(modified_chosen, i, level -1):
                return combined + reconstruct(modified_chosen, i, level-1)

if __name__ == "__main__":
    global no_of_word
    words =[]
    for _ in range(int(sys.stdin.readline().strip())):
        words = []
        memo = [[''] * 15 for _ in range((1 << 16)+ 1)];
        memo2 = [[''] * 15 for _ in range(15)]
        no_of_word = int(sys.stdin.readline().strip());
        for _ in range(no_of_word):
            words.append(sys.stdin.readline().strip())

        to_be_deleted = []
        for i in range(len(words)):
            for j in range(i+1, len(words)):
                if words[i] in words[j]:
                    to_be_deleted.append(i)
                elif words[j] in words[i]:
                    to_be_deleted.append(j)
        for i in to_be_deleted:
            del words[i]
        
        no_of_word = len(words)
        print(reconstruct(1<<15, -1, no_of_word-1))
    