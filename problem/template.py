import os
import sys

from io import BytesIO, IOBase

_str = str
str = lambda x=b"": x if isinstance(x, bytes) else _str(x).encode()

BUFSIZE = 8192


class UnionFind:
    def __init__(self, n):
        self.reps = [i for i in range(n)]
        self.rank = [0] * n

    def find(self, x):
        while x != self.reps[x]:
            self.reps[x] = self.reps[self.reps[x]]
            x = self.reps[x]
        return x

    def merge(self, x, y):
        x = self.find(x)
        y = self.find(y)
        if x == y:
            return
        if self.rank[x] > self.rank[y]:
            self.reps[y] = x
        else:
            self.reps[x] = y
            if self.rank[x] == self.rank[y]:
                self.rank[y] += 1


class SegmentTree:
    def __init__(self, a, n):
        self.n = n
        self.t = [0] * (4 * n)
        for i in range(n):
            self.t[i + n] = a[i]
        for i in range(n - 1, 0, -1):
            self.t[i] = self.t[i << 1] + self.t[i << 1 | 1]

    def update(self, i, v):
        i += self.n
        self.t[i] = v
        while i > 1:
            i >>= 1
            self.t[i] = self.t[i << 1] + self.t[i << 1 | 1]

    def query(self, l, r):
        res = 0
        l += self.n
        r += self.n
        while l <= r:
            if l & 1 == 1:
                res += self.t[l]
                l += 1
            if r & 1 == 0:
                res += self.t[r]
                r -= 1
            l >>= 1
            r >>= 1
        return res


class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._file = file
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2)
            self.buffer.write(b)
            self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()

    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2)
            self.buffer.write(b)
            self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0)
            self.buffer.seek(0)


class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")


def solve():
    pass


def main():
    t = 1
    # t=int(input())
    while t:
        solve()
        t -= 1


if __name__ == "__main__":
    main()
