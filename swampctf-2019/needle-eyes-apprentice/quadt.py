#!/usr/bin/env python3
import png  # https://github.com/drj11/pypng/


class node(object):
    def __init__(self, t):
        self.depth = 1
        self.children = []
        print(len(t))
        for x in t:
            if x in {0, 1}:
                self.children.append(x)
            else:
                self.children.append(node(x))
        for c in self.children:
            if c not in {0, 1}:
                self.depth = max(self.depth, 1 + c.depth)

    def set_depth(self, d):
        self.depth = d
        for c in self.children:
            if c not in {0, 1}:
                c.set_depth(d - 1)

    def write_children(self, m, y, x):
        print('write children', y, x, self.depth)
        d = self.depth
        n = 2 ** (d-1)
        for i, c in enumerate(self.children):
            xx = 1 if i == 1 or i == 2 else 0
            if c in {0, 1}:
                for j in range(n):
                    for k in range(n):
                        m[y + (i // 2) * n + j][x + xx * n + k] = c
            else:
                c.write_children(m, y + (i // 2) * n, x + xx * n)

    def write(self, out):
        n = 2 ** self.depth
        m = [[None] * n for _ in range(n)]
        w = png.Writer(n, n, greyscale=True, bitdepth=1)
        self.write_children(m, 0, 0)
        for i in range(n):
            for j in range(n):
                if m[i][j] is None:
                    print("None in {},{}".format(i,j))
        for r in m:
            print(r)
        w.write(out, m)


if __name__ == '__main__':
    with open('quadt.out') as f:
        xs = f.read()
qt = node(eval(xs))
qt.set_depth(qt.depth)
with open('flag.png', 'wb') as f:
    qt.write(f)
