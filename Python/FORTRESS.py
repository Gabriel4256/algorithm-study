## tree를 만드는 부분은 생각보다 노가다라 좀 놀랐고,
## 중요했던 부분은 height를 계산하면서 leaf와 leaf간 최대거리를 계산하는 부분이었다.
## 혼자 힘으로 풀릴듯 말듯 실마리를 찾기 힘들었던 문제, 잘 기억해두자

import sys
import math

def distance(p1, p2):
    return ((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2) ** 0.5

class Node:
    parent = None
    children = None
    depth = 0
    
    def __init__(self, info):
        self.center = (info[0], info[1]);
        self.radius = info[2];
        self.children = []
                
    def contains(self, node):
        if distance(self.center, node.center) > max(self.radius, node.radius):
            ## 서로 아예 겹치지 않는 경우
            return False   
        else:
            if self.radius > node.radius:
                ## self가 node를 포함하는 경우
                return True
            else:
                return False

def makeTree(nodes):
    root = nodes[0]
    for i in range(1, len(nodes)):
        start = root
        while start.contains(nodes[i]):
            find = False
            for child in start.children:
                if child.contains(nodes[i]):
                    find = True
                    start = child
                    break
            if not find:
                start.children.append(nodes[i])
                nodes[i].parent = start
                nodes[i].depth = start.depth + 1
                break
    
def height(root):
    global answer
    heights = []
    for child in root.children:
        heights.append(height(child))
    heights = sorted(heights, reverse=True)
    if len(heights) == 0:
        return 0
    if len(heights) >= 2:
        answer = max(answer, heights[0] + heights[1] + 2)
    return heights[0] + 1
    
def main():
    for _ in range(int(input().strip())):
        global answer
        answer = 0
        nodes = []
        for _ in range(int(input().strip())):
            x, y, r = map(int, input().strip().split())
            nodes.append((x,y,r))
        nodes = sorted(nodes, key=lambda n : n[2], reverse=True)
        nodes = list(map(Node, nodes))
        makeTree(nodes)
        h = height(nodes[0])
        if h > answer:
            answer = h
        # answer = max(answer, height(nodes[0])) max가 제대로 동작이 안됨
        print(answer)

answer = 0

if __name__ == "__main__":
    main()