## 트립을 사용하거나 (두개의) 힙을 사용하여 풀 수 있는 문제였다.
## 하지만 나는 이진탐색을 사용했다.
## 두개의 힙을 사용하는 기법을 잘 기억해놓자

from bisect import bisect_left
import heapq

def main():
    for _ in range(int(input().strip())):
        N, a, b = map(int, input().strip().split())
        cur = 1983
        nums = [cur]
        ans = 0
        
        max_heap = [-cur]
        heapq.heapify(max_heap)
        min_heap = [] 
        heapq.heapify(min_heap)
        for i in range(1, N):
            
            ## solution 1
            # cur = (cur * a + b) % 20090711
            # pos = bisect_left(nums, cur)
            # nums.insert(pos, cur)
            # if len(nums) % 2 == 0:
            #     ans += nums[len(nums) // 2 - 1]
            # else:
            #     ans += nums[len(nums) // 2]
            cur = (cur * a + b) % 20090711
            if(len(max_heap) > len(min_heap)):
                heapq.heappush(min_heap, cur)
            else:
                heapq.heappush(max_heap, -cur)
            if len(min_heap) > 0  and -max_heap[0] > min_heap[0]:
                t1 = -heapq.heappop(min_heap)
                t2 = -heapq.heappop(max_heap)
                heapq.heappush(min_heap, t2)
                heapq.heappush(max_heap, t1)
            ans += -max_heap[0]
                
        print((ans + 1983) % 20090711)

if __name__ == '__main__':
    main()
    