import random

filepath = 'map.txt'
lines: int = 81

assert lines <= 81 and lines >= 0

with open(filepath, 'w') as file:
    txt = '\n'.join(
        ['\t'.join(
            [str(random.randint(1, 6)) for _ in range(9)])
         for _ in range(lines)] +
        ['\t'.join(['0' for _ in range(9)])
         for _ in range(81 - lines)])

    file.write(txt)
