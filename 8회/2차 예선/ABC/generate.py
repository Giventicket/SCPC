import random

N = random.choice([6])
M = random.choice([10])
K = -1
print(N, M, K)
for _ in range(M):
    a = random.choice(list(range(1, N+1)))
    b = random.choice(list(range(1, N+1)))
    while a == b:
        a = random.choice(list(range(1, N+1)))
        b = random.choice(list(range(1, N+1)))
    c = random.choice(['A', 'B'])
    print(a, b, c)