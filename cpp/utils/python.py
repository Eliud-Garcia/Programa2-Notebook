
from functools import cmp_to_key

def next_int(): return int(input())
def read_array(): return map(int, input().split())
def read_list(): return list(map(int, input().split()))

def comparator(a, b):
  if a < b:
    return -1
  else:
    return 1


t = next_int()
for _ in range(t):
  n = next_int()
  a = read_list()
  a = sorted(a, key=cmp_to_key(comparator))
  
  i = 0
  j = n - 1
  
  #while i <= j:
  #if i == j:
  #for i in range(n)
  print(int(ans))

#vector 
arr = []
a.append(10)

#deque
from collections import deque
q = deque()
q.append(("a", 8))
q.popleft()

#set
st = set()
st.add(1)

#mapa
mp = dict()
mp["str"] = "x"
mp["k"] = 21
