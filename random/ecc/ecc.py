def find_points_brute_force(a, b, p):
    print(f"y^2 = x^3 + x over Z/{p}Z")
    for x in range(0, p):
        for y in range(0, p):
            xmodp = (x**3 + x) % p
            ymodp = (y**2) % p
            #print(f"({x}, {y})", end=' \t')
            #print(f"y^2 (mod {p}) = {ymodp}", end=' \t')
            #print(f"x^3 + x (mod {p}) = {xmodp}", end=' \t')
            if xmodp == ymodp:
                print(x, y)
                #print(f"POINT ON CURVE")
            else:
                pass
            #print()

if __name__ == '__main__':
    find_points_brute_force(1, 0, 5869)

