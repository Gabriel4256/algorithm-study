## 아주 간단한 스택 문제

global start, end

def check_pair(a, b):
    global start, end
    return start.index(a) == end.index(b) and start.index(a) != -1

def main():
    global start, end
    start = ['(', '{', '[']
    end = [')', '}', ']']
    for _ in range(int(input().strip())):
        stack = []
        correct = True
        brackets = str(input().strip())
        for s in brackets:
            if s in start:
                stack.append(s)
            else:
                if len(stack) == 0 or not check_pair(stack.pop(), s):
                    correct = False
                    break
        if correct and len(stack) == 0:
            print("YES")
        else:
            print("NO")

if __name__ == "__main__":
    main()