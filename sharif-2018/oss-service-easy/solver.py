from verify import n, k, m1, x1, y1, m2, x2, y2, public, verify

def mult(x1, y1, x2, y2, k):
    """(x1^2 + ky^1)(x^2 + ky^2)"""

    return (x1 * x2 + k*y1*y2) % n, (x1 * y2 - y1 * x2) % n


x, y = mult(x1, y1, x2, y2, k)
print(verify(public, (m1 * m2) % n, (x, y)))
print('x: {}\ny: {}'.format(x, y))
