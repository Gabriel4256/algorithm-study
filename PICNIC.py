import sys

global rlship

def check(students):
    count = 0
    if len(students) == 0:
        return 1
    
    for i in range(len(rlship)):
        if rlship[students[0]][i] and i in students:
            tmp = students[::]
            tmp.remove(i)
            del tmp[0]
            count += check(tmp)
    return count
        
    

i = int(input())
for j in range(i):
    tmp = input();
    tmp = tmp.split(' ')
    k = tmp[0]
    l = tmp[1]
    # (k, l) = input().split(' ')
    k = int(k)
    l = int(l)

    t = (input()).split(' ')
    if t[-1] == '':
        t = t[:-1]
    t = list(map(int, t))
    rlship = [[False for j in range(k)] for i in range(k)]
    for i in range(0,len(t),2):
        rlship[t[i]][t[i+1]] = True
        rlship[t[i+1]][t[i]] = True
    students = [i for i in range(k)]
    print(check(students))
        
    