'''
Write a program non-recursive and recursive program 
to calculate Fibonacci numbers and analyze their time and space complexity.
'''

n = int(input("Enter n: "))
def non_recursive_fibonacci(n):
    a = 0
    b = 1
    if n == 0 or n == 1:
        return n
    for i in range(2, n+1):
        next = a + b
        a = b
        b = next
    return b

def recursive_fibonacci(n):
    if n == 0 or n == 1:
        return n
    return recursive_fibonacci(n-1) + recursive_fibonacci(n-2)

print(f"Non-Recursive: {non_recursive_fibonacci(n)}")
print(f"Recursive: {recursive_fibonacci(n)}")

'''
Output:

Enter n: 8
Non-Recursive: 21
Recursive: 21
'''

# Write a recursive program to solve Tower of Hanoi problem.

n = int(input("Number of discs: "))

def toh(n, t1, t2, t3):
    if n > 0:
        toh(n-1, t1, t3, t2)
        print(f"Move a disc from {t1} to {t3}")
        toh(n-1, t2, t1, t3)

toh(n, 'A', 'B', 'C')