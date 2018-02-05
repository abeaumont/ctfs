# Fifteen Puzzle (misc ppc 150)

We are given [128 _15 puzzle_](puzzles.txt), each providing a bit of the flag.
Each bit is set if the puzzle is solvable and unset otherwise.
The task description also provides a code skeleton of how to generate the flag
from this solvability information.

Each puzzle is solvable if the parity of the inversions of the puzzle
matches with the parity of the row
where the empty square is located (starting with row 1 at the bottom).

So we gather all the pieces together to get the flag:

```python
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
```

Running it:

```
> python2 solver.py
SharifCTF{52d3b36b2167d2076b06d8101582b7af}
```
