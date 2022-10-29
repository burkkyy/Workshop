import time

def f(n):
    start = time.monotonic()
    """
    for i in range(0, n, 1):
        for j in range(i + 1, n, 1):
            pass
    """
    for i in range(n):
        pass

    end = time.monotonic()
    print(f"time {end - start:2f}")

if __name__ == '__main__':
    f(99957)

