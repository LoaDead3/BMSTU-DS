from random import randint

n = 1500
m = 1500

f = open("data/data0.txt", "w")

f.write('1\n')
f.write(str(n) + '\n')
for i in range(n):
    f.write('0 ')
f.write('\n')

f.write(str(n) + '\n')
f.write(str(m) + '\n')
for i in range(n):
    for j in range(m):
        f.write('0 ')
    f.write('\n')
f.close()
print("0")


g = 0.1
f = open("data/data20.txt", "w")

f.write('1\n')
f.write(str(n) + '\n')
strn = [0 for x in range(n)]
for i in range(int(n * g)):
    strn[randint(0, n - 1)] = randint(0, 100)
for i in range(n):
    f.write(str(strn[i]) + ' ')
f.write("\n")
f.write(str(n) + '\n')
f.write(str(m) + '\n')
arr = []
for i in range(n):
    arr.append([0 for x in range(m)])
tmp = 0
while tmp < int(n * m * g):
    x = randint(0, m - 1)
    y = randint(0, n - 1)
    if(arr[x][y] == 0):
        arr[x][y] = randint(1, 100)
        tmp += 1

for i in range(n):
    for j in range(m):
        f.write(str(arr[i][j]) + " ")
    f.write('\n')
f.close()
print("20")

g = 0.40
f = open("data/data40.txt", "w")

f.write('1\n')
f.write(str(n) + '\n')
strn = [0 for x in range(n)]
for i in range(int(n * g)):
    strn[randint(0, n - 1)] = randint(0, 100)
for i in range(n):
    f.write(str(strn[i]) + ' ')
f.write("\n")
f.write(str(n) + '\n')
f.write(str(m) + '\n')
arr = []
for i in range(n):
    arr.append([0 for x in range(m)])
tmp = 0
while tmp < int(n * m * g):
    x = randint(0, m - 1)
    y = randint(0, n - 1)
    if(arr[x][y] == 0):
        arr[x][y] = randint(1, 100)
        tmp += 1
for i in range(n):
    for j in range(m):
        f.write(str(arr[i][j]) + " ")
    f.write('\n')
f.close()
print("20")

g = 0.60
f = open("data/data60.txt", "w")

f.write('1\n')
f.write(str(n) + '\n')
strn = [0 for x in range(n)]
for i in range(int(n * g)):
    strn[randint(0, n - 1)] = randint(0, 100)
for i in range(n):
    f.write(str(strn[i]) + ' ')
f.write("\n")
f.write(str(n) + '\n')
f.write(str(m) + '\n')
arr = []
for i in range(n):
    arr.append([0 for x in range(m)])
tmp = 0
while tmp < int(n * m * g):
    x = randint(0, m - 1)
    y = randint(0, n - 1)
    if(arr[x][y] == 0):
        arr[x][y] = randint(1, 100)
        tmp += 1
for i in range(n):
    for j in range(m):
        f.write(str(arr[i][j]) + " ")
    f.write('\n')
f.close()
print("20")

g = 0.80
f = open("data/data80.txt", "w")

f.write('1\n')
f.write(str(n) + '\n')
strn = [0 for x in range(n)]
for i in range(int(n * g)):
    strn[randint(0, n - 1)] = randint(0, 100)
for i in range(n):
    f.write(str(strn[i]) + ' ')
f.write("\n")
f.write(str(n) + '\n')
f.write(str(m) + '\n')
arr = []
for i in range(n):
    arr.append([0 for x in range(m)])
tmp = 0
while tmp < int(n * m * g):
    x = randint(0, m - 1)
    y = randint(0, n - 1)
    if(arr[x][y] == 0):
        arr[x][y] = randint(1, 100)
        tmp += 1
for i in range(n):
    for j in range(m):
        f.write(str(arr[i][j]) + " ")
    f.write('\n')
f.close()
print("20")

g = 1
f = open("data/data100.txt", "w")
tmp = (int)(1 / g)

f.write('1\n')
f.write(str(n) + '\n')
for i in range(n):
    f.write(str(randint(1, 100)) + ' ')
f.write('\n')

f.write(str(n) + '\n')
f.write(str(m) + '\n')
for i in range(n):
    for j in range(m):
        f.write(str(randint(1, 100)) + ' ')
    f.write('\n')
f.close()
print("100")