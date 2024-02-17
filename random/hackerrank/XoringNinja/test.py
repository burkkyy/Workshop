def ninja(a):
    x, y = 0, 0
    s = 1 << len(a)
    for i in range(1, s, 1):
        for j, b in enumerate(bin(i)[i+1:1:-1]):
            if int(b) != 0:
                y ^= a[j]
        #print(y)
        x += y
        y = 0
    return x

def p(a):
    n = len(a)
    p = [0] * n
    p[0] = n
    for i in range(1, len(a), 1):
        n -= 2
        p[i] += p[i - 1] + n
    #print(f"{p=}")
    return p

def f(a, p):
    ans = ['0'] * 32
    for i in range(32):
        m = 0
        for j in range(len(a)):
            try:
                m += int(bin(a[j])[i+2]) * p[j]
            except IndexError:
                pass
        if m % 2 != 0:
            ans[i] = '1'
    
    fa = 0
    for i in range(len(ans)):
        fa += (1 << i) * int(ans[i])
    return fa

def g(a, p):
    ans = [0] * 32
    for i, c in enumerate(a):
        for j, b in enumerate(bin(c)[c+1:1:-1]):
            ans[j] += p[i] * int(b)
            #print(f"{i=} {c=} {j=} {b=}")
    print(ans[::-1])
    for i in range(len(ans)):
        while ans[i] > 1:
            #print(ans[i], ans[i+1])
            ans[i] -= 2
            ans[i+1] += 1
            if(ans[i] == 0 or ans[i] == 1):
                break
    print(ans[::-1])

if __name__ == '__main__':
    #f(range(int(1e5)))
    a = (43, 543, 3, 45, 4)
    p = p(a)
    print(f"{a=}")
    for i in a:
        print(f"bin({i})={bin(i)}")
    print(f"{p=}\n{f(a, p)=}")
    print(f"{ninja(a)=} {bin(ninja(a))=}")
    g(a, p)
    #print(f"{g(a, p)}")
    #ans = ninja(range(20))
    #print(ans & int(1e9 + 7))
