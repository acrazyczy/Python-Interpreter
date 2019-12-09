cnt0 = 0
cnt1 = 0
def add0():
	cnt0 += 1
	return cnt0
def add1():
	cnt1 += 2
	return cnt1
x = add0() > add1() == add0()
print (x)
