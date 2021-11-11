from itertools import permutations

def str2number(substitution, w):
    t = 1
    n = 0
    for l in list(w)[::-1]:
        n += t*substitution[l]
        t*=10

    return n

def check(substitution, operator, x, y, z):
    xn = str2number(substitution, x)
    yn = str2number(substitution, y)
    zn = str2number(substitution, z)

    return operator(xn, yn) == zn

def solve(x, y, z, operator_s):
    if operator_s == '+':
        operator = lambda x, y: x+y
    elif operator_s == '-':
        operator = lambda x, y: x-y
    elif operator_s == '*':
        operator = lambda  x, y: x*y
    elif operator_s == '/':
        operator = lambda  x, y: x/y

    letters = set(x).union(set(y).union(set(z)))
    for s in permutations(list(range(10)), r=len(letters)):
        substitution = {l: s[i] for i, l in enumerate(letters)}
        if check(substitution, operator, x, y, z):
            print_ans(substitution)
            return

    print('\n[-] Did not find any good substitution')

def print_ans(substitution):
    print('\n[+] Found good substitution:')
    for l in substitution:
        print(f'{l} := {substitution[l]}')


if __name__ == '__main__':
    solve('KIOTO', 'OSAKA', 'TOKIO', '+')
    solve('ZERO', 'ZERO', 'JEDEN', '+')
    solve('WILK', 'UNIKA', 'LUDZI', '+')
    solve('ROZUM', 'DUŻO', 'MOŻE', '-')
    solve('SEND', 'MORE', 'MONEY', '+')
    solve('USA', 'USSR', 'PEACE', '+')
    solve('PYTHON', 'CPP', 'BLESS', '+')
