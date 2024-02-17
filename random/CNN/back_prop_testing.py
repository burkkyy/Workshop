import numpy as np

def a_bp(o, l, h):
    delta = o - l
    final = np.zeros((4,3))
    for i in range(4):
        for j in range(3):
            final[i][j] = (o[j][0] - l[j][0])\
            * (h[i][0])
            #* (o[j][0] * (1 - o[j][0]))\
            #* (h[i][0])
    return final.T

def b_bp(o, l, h):
    delta = o - l
    return delta @ np.transpose(h)

if __name__ == '__main__':
    o = np.matrix((0.67, 0.53, 0.52))
    o = o.T
    h = np.matrix((0.1, 0.62, 0.21, 0.62))
    h = h.T
    l = np.matrix((1, 0, 0))
    l = l.T
    print(o.transpose(), l.shape, h.shape)
    print(f"{a_bp(o, l, h)=}")
    print(f"{b_bp(o, l, h)=}")

