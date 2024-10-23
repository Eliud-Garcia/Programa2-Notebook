
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
    x = 0
    ans = 0
    while i <= j:
        if i == j:
            if x > a[i]:
                ans += a[i]
            else:
                df = a[i] - x
                ans += min(a[i], (df + 1) / 2 + 1)
            i+=1
        elif x + a[i] < a[j]:
            x += a[i]
            ans += a[i]
            i+=1
        else:
            restante = a[j] - x
            a[i] -= restante
            ans += (restante + 1)
            j-=1
            x = 0
    print(int(ans))
    
