# scope
a='outer1'
print(a)
def f(a):
    print('f',a)
    a='f new'
    print(a)
    return 'ret'+a
a='outer2'
print(a)
a=f(a)
print(a)
