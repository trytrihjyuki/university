I <- lista par odcinkow
S = set()
sorted(A, key = lambda x: x.fk)
S.add(A[0])

last = A[0].k
for i in range(2,n):
    if A[i].p > last:
        S.add(A[i])
        last = A[i].k

