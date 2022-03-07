from random import randint


def gen(name, n):
    f = open(name, "w")
    opers = ["+", "-", "*", "/"]
    for i in range(n - 1):
        num = randint(0, 100)
        op = opers[randint(0, 3)]
        f.write(str(num) + " " + op + " ")
    f.write(str(randint(-100, 100)))
    f.close()


# gen("data1.txt", 500)
# gen("data2.txt", 1000)
# gen("data3.txt", 1500)
gen("data4.txt", 2000)
