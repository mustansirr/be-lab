# # fibonacci numbers

# n = int(input('N: '))
# def nonrecursive(n):
#     a = 0
#     b = 1
#     if n == 0 or n == 1:
#         return n;
#     for i in range(2, n+1):
#         next = a + b
#         a = b
#         b = next
#     return b
# fib = nonrecursive(n)
# print('Fibonacci Number:', fib)

# def recursive(n):
#     if n == 0 or n == 1:
#         return n
#     return recursive(n-1) + recursive(n-2)

# fib2 = recursive(n)
# print('Fibonacci: ', fib2)

# TOH

N = int(input("Number of discs: "))
def toh(N, t1, t2, t3):
    if N > 0:
        toh(N-1, t1, t3, t2)
        print(f'Move disc from {t1} to {t3}')
        toh(N-1, t2, t1, t3)

toh(N, 'A', 'B', 'C')