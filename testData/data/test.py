#! /usr/bin/python3
import filecmp
import os
if os.path.exists("temp"):
    os.system("rm -rf ./temp")
os.makedirs("temp")

for i in range(1, 46):
    if i == 25 or i == 27 or i == 30 or i == 35 or i == 36 or i == 37 or i == 38 or i == 39 or i == 40 or i == 41 or i == 42:
        continue;
    inst ="./python_interpreter < testData/test"+str(i)+".in > temp/test"+str(i)+".out"
    print(inst)
    os.system(inst)
    if not filecmp.cmp("testData/test"+str(i)+".out","temp/test"+str(i)+".out"):
        f = open("testData/test" + str(i) + ".in", mode='r')
        title = f.readline()[1:]
        print("test", i, "wrong:", title)
# os.system("rm -rf ./temp")
# os.makedirs("temp")


# for i in range(0, 20):
#    inst = "./python_interpreter < BigIntegerTest/BigIntegerTest" + str(i) + ".in > temp/test" + str(i) + ".out"
#    print(inst)
#    os.system(inst)
#    if not filecmp.cmp("BigIntegerTest/BigIntegerTest" + str(i) + ".out", "temp/test" + str(i) + ".out"):
#        print("big integer test", i, "wrong")

