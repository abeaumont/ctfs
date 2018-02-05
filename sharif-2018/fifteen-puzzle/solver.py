def is_solvable(puzzle):
    x = [x.strip() for x in ''.join([x.strip()[1:] for x in puzzle]).split('|', 16)[:16]]
    blank = 4 - x.index('') / 4
    x.remove('')
    x = map(int, x)
    inv = 0
    for i in range(15):
        for j in range(i + 1, 15):
            if x[i] > x[j]:
                inv += 1
    return inv % 2 == blank % 2

with open('puzzles.txt') as f:
    lines = f.readlines()
flag = ' '
for i in range(128):
    flag = ('1' if is_solvable(lines[11*i+2:11*i+9:2]) else '0') + flag
print('SharifCTF{%016x}' % int(flag, 2))
