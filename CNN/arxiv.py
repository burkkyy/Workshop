import numpy as np
import math

def cross_entropy(yi, pi):
    x = -1*(yi * math.log(pi)) + (1 - yi)*(1 - math.log(pi))
    return x


if __name__ == '__main__':
    yi = (0, 1)
    pi = np.arange(0.1, 1.0, 0.1)
    for i in pi:
        for j in yi:
            print(f"j: {j} i: {i:0.2f} ans: {cross_entropy(j, i)}")

