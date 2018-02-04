#!/usr/bin/env sage
def mult(x1, y1, x2, y2, k):
    """(x1^2 + ky^1)(x^2 + ky^2)"""

    return (x1 * x2 + k*y1*y2) % n, (x1 * y2 - y1 * x2) % n

def pollard(k, m):
    # Generate a valid prime m0 < m and x0
    while True:
        while True:
            u = randrange(n)
            v = randrange(n)
            m0 = m*(u*u+k*v*v)%n
            if m0 % 4 == 3: break
        x0 = pow(-k, (m0 + 1)/4, m0)
        if pow(x0, 2, m0) == -k % m0:
            break
    xx = [0,Integer(x0)]
    mm = [0,m0]

    # Generate the series x_i, m_i, till m_I
    while not (xx[-2] <= mm[-1] <= mm[-2]):
        mm.append((xx[-1] * xx[-1] + k) / mm[-1] % n)
        xx.append(min(xx[-1] % mm[-1], (mm[-1] - xx[-1]) % mm[-1]) % n)

    # Multiply all the equations to get s0, t0
    s, t = xx[1], 1
    for x in xx[2:-1]:
        s, t = s * x-k * t, s + x*t

    # Get s1, t1 from s0, t0
    M = mul(mm[2:]) % n
    s1 = s * inverse_mod(M, n) % n
    t1 = t * inverse_mod(M, n) % n

    # Get s2, t2 either trivially or recursivelly
    if is_square(mm[-1]):
        s2, t2 = sqrt(mm[-1]), 0
    elif mm[-1] == k:
        s2, t2 = 0, 1
    else:
        # Change variables and solve recursively
        s22, t22 = pollard(Integer(-mm[-1]), -k)
        # Change variables back
        t2 = inverse_mod(t22, n)
        s2 = s22 * t2

    # Get s4, t4 multiplying previous solutions
    s3, t3 = mult(u, v, s1, t1, k)
    s4, t4 = mult(s3, t3, s2, t2, k)

    # Obtain the solution to the original problem
    m0inv = inverse_mod(Integer(m0), n)
    return s4 * m * m0inv % n, t4 * m * m0inv % n


n = 108504503412454373447900779392896455789182908920252767679102572784833248190682207737154598741166656146295499891768592408962529857168166275863130804227243036676846199142906617137007877378696363607314850559328607693669984310189715960464177540321389050644453028598966277046571994650300388605135199566812211180551
k = 96418402323876864512491639972930583881318685814783562179751981420110811774390896080021079024657494752001051891183358590923934531389848653055409236592228196204683162829359099715583891741617111941684481041179057606706801620321693724317614343290846702947941240579335556736392623484157714059707148044213280632330
m = 9045418907335068770268779849124564950219260545189341826614770092040336019517687130751801431148236418688112027601673969058529643735762961447504773552645699712014099935774980274016297241177481291819364059206708658744657881196289540965565219550846730216720833999741328972855594202081834339846728109

x, y = pollard(k, m)
print "x: {}\ny: {}".format(x, y)
