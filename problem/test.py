def binary(x):
    print(bin(x)[2:][::-1])


def seq(x):
    r = 20
    for i in range(r):
        print(x ^ (i + 1), end=", ")
    print()


seq(12)
seq(4)
