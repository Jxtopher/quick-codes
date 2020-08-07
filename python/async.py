import asyncio

from random import randint
from typing import List


async def my_sum(tab : List[int], start : int, end : int) -> int:
    print(str(start) + " " + str(end))
    r = 0
    for i in range(start, end):
        r += tab[i]
    return r

if __name__ == '__main__':
    tab = [randint(0, 20000) for i in range(20000)]
    
    n = 100
    results = 0
    for i in range(1, n+1):
        results += asyncio.run(my_sum(tab, (i - 1) * int(len(tab) / n), i * int(len(tab) / n)))
        

    print(str(results) + " " + str(sum(tab)))