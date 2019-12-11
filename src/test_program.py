a = 1
def f() :
	a += 1
	return a
def g(x = 2) :
	return x
def h(x = 3) :
	return x
f()
print (g() , h())
