#!/usr/bin/python
import os,sys,subprocess
import numpy as np
import matplotlib.pyplot as plt
import time
print("тестуємо задачу2")

print("умова:")
table=[
    [2,2,1],
    [0,2,0],
    [0,0,2]
]
for x in range(3):
    for y in range(3):
        print(table[y][x],end=" ")
    print()
    
print("реальний результат:")
result=[[0,0,0],[0,0,0],[0,0,0]]
for x in range(3):
    for y in range(3):
        a=subprocess.check_output(["test.exe", str(x), str(y), "2"], shell=True)
        print(a.decode("utf-8")[0],end=" ")
        result[y][x] = int(a.decode("utf-8")[0])
    print()

if result == table:
    print("тест пройдено")
else:
    print("тест не пройдено")


print("тестуємо задачу1")



circle1 = plt.Circle((0, 0), 1, color='gray')
rect1 = plt.Rectangle((0,1), -1, -2, color='white')
rect2 = plt.Rectangle((0,0), 1, 1, color='gray')

fig, ax = plt.subplots()
ax.add_patch(circle1)
ax.add_patch(rect1)
ax.add_patch(rect2)
plt.axis([-1, 2, -2, 2])
#0.1 grid 
plt.grid(True, which='both')


import signal
def handler(signum, frame):
    exit(1)
 
signal.signal(signal.SIGINT, handler)


for x in range(1,100):
    try:
        for i in range(3):
            x = np.random.normal(0, 0.7, 1000)[1]+0.5
            y = np.random.normal(0, 0.8, 1000)[1]
            result = subprocess.check_output(["test.exe", str(x)[0:5], str(y)[0:5], "1"], shell=True)
            plt.scatter(x, y, color= ('green' if result.decode("utf-8")[0] == "1" else 'red') )
        plt.pause(0.05)
    except KeyboardInterrupt:
        exit()
