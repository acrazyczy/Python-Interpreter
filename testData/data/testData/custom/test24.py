# logic
global_flag=False
def ok(b):
    if b:
        print("ok")
    elif global_flag:
        print('Global fatal')
    else:
        print('local fatal')
def true_call():
    print('call true')
    return True
def false_call():
    print('call false')
    return False

ok(3<4 and 4<5)
ok(3<5 and true_call())
ok(3<5 or true_call())
ok(3>5 and true_call())
ok(3>5 or true_call())

global_flag=True
print('flag change')
ok(3<4<5)
ok(3<5>4)
ok(3<5<4)
