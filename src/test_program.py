a=1
b=2
c=3
def fc():
	print(c)
def fb():
	c=7
	print(b)
	fc()
def fa():
	b=3
	print(a)
	fb()
fa()
