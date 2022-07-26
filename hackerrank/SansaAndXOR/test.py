def san(a):
    #print(f"{len(a)=}")
    if len(a) == 0:
        print()
        return
    itter = 0
    temp = 0;
    current = 0
    for i in range(1, len(a)+1, 1):
        for j in range(0, len(a) - i + 1, 1):
            for k in range(j, j + i, 1):
                print(f"{a[k]=} {bin(a[k])=}", end=' ')
                #c[a[k]] += 1
                itter += 1
                current ^= a[k]
            print()
    print(f"{itter} ans {current} ans bin {bin(current)}")

if __name__ == '__main__':
    """
    for i in range(int(10)):#1E+5)):
        print(f"size: {i} itter: ", end='')
        san(range(i))
    """

    x = (98, 74, 12)
    p = [0 for i in range(len(x))]
    current = len(x)
    p[0] = len(x)
    for i in range(1, len(p), 1):
        current -= 2
        p[i] += p[i-1] + current
    print(p)

    ans = []
    for i in range(4):
        msb_count = 0
        for j in range(len(x)):
            msb_count += int(bin(x[j])[i+2]) * p[j]
        ans.append(msb_count)

    print(f"im trying {ans}")
    san(x)
        #print(f"size: {n}\n{a=}\n{c=}\n{p=}")
        #s_c = set(c)
        #s_p = set(p)
        #print(f"size: {n}, prediction: {s_c==s_p}")
     
    #print(f"size: {3} itter: ", end='')
    #san((3, 4, 5))

