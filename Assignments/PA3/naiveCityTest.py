from pwn import *
from random import randrange, choice
import threading


class Arbitary:
    def __init__(self, length: int, load: str = None, save: str = None) -> None:
        self.length = length
        self.load = load
        self.save = save
        self.size = randrange(5, 10)*2

    def randomPos(self) -> int: return randrange(0, self.size-1)

    def newMap(self) -> str:
        if self.load is None:
            return f"1 {self.size}"
        else:
            return f"2 {self.load}"

    def saveMap(self) -> str:
        if self.save is not None:
            return f"8 {self.save}"
        else:
            return ""

    def preload(self) -> str:
        return "1 1 1 1 1 3 2 1 1 5 0 1 5 6 7 7 7 7 7 7 7 1 3"

    def build(self) -> str:
        return f"1 {randrange(1,6)} {self.randomPos()} {self.randomPos()}"

    def demolish(self) -> str:
        return f"2 {self.randomPos()} {self.randomPos()}"

    def nextTurn(self) -> str: return ' '.join("7"*randrange(10))

    def longInfo(self) -> str:
        return f"4 {self.randomPos()} {self.randomPos()}"

    def mapStatus(self) -> str: return "5 6"

    def end(self) -> str: return "9"

    def generate(self) -> list[str]:
        a = [self.build, self.demolish, self.nextTurn]
        b = [self.longInfo, self.mapStatus]
        return \
            [self.newMap(), self.preload()] + \
            [choice(b)() if randrange(1, 4) % 3 == 0 else choice(a)() for _ in range(self.length)] + \
            [self.mapStatus(), self.saveMap(), self.end()]


class Comparator:
    def __init__(self, bin: str, demo: str, tester: Arbitary, timeout: int = 1, showinput: bool = False) -> None:
        self.bin = bin
        self.dbin = demo
        self.inputs = tester.generate()
        self.result = False
        self.timeout = timeout
        self.showinput = showinput

    def run(self):
        def runOnce(b: str, result: list):
            io = process(b)
            for i in self.inputs:
                io.sendline(i.encode("ascii"))
            result.append(io.recvall(self.timeout).decode("utf-8"))

        results = []
        t1 = threading.Thread(target=runOnce, args=(self.bin, results))
        t2 = threading.Thread(target=runOnce, args=(self.dbin, results))
        t1.start()
        t2.start()
        t1.join()
        t2.join()

        self.result = results[0] == results[1]
        return self

    def report(self) -> None:
        print("===\nCompare result:", self.result, "\n===")
        if self.showinput:
            print("***\nInput string:\n" + ' '.join(self.inputs) + "\n***")


def main():
    Comparator('./simplecity', './demo', Arbitary(500,
               load='b.txt', save='c.txt')).run().report()


main()