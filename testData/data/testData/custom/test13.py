# default arguments
def func(a,b=4,c=5):
    print(a,b,c)
    c-=a
    a+=b
    print(a,b,c)

func(1,c=3)