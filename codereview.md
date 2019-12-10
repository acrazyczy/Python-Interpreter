[TOC]
# 变量和函数名管理
## 用到的类和对象
### `class name_space`
用于储存变量名与变量值的映射关系，以及函数名与 funcdef 节点的映射关系。
#### `static std::map<> static_func_sys`, `static std::map<> static_var_sys`
`name_space` 的静态成员，表示全局名称空间的函数和变量声明。
#### `std::map<> func_table`
'name_space' 的静态成员，用来存储函数参数表。
#### `static bool is_global_block`
`name_space` 的静态成员，表示当前是否为全局语句块。
#### `func_sys`, `var_sys`
`name_space` 的成员，表示一个名称空间的函数和变量声明。
### `std::stack<name_space> stack_workspace`
栈工作区。
### `std::stack<std::vector<std::string> >`
用于储存当前语句块声明的所有变量和函数。
### `loop_cnt`
当前嵌套的循环语句块层数。
## 代码逻辑
### 处理函数调用
栈工作区新建名称空间到栈顶。

函数参数作为新名称空间下变量进行声明。

退出函数前，栈顶弹出。
### 处理 Suite 节点
新建语句块。

退出节点前，在当前名称空间中删除所有该语句块的变量和函数声明，删除语句块。
### 处理选择语句
无需特殊处理。
### 处理循环语句
进入时 `++ loop_cnt`，退出时 `-- loop_cnt`
# 跳转语句处理
## 用到的类
`class BREAK_SIGN`：抛出中断。

`class CONTINUE_SIGN`：抛出跳过。

`class RETURN_SIGN`：抛出返回，含 `antlrcpp::Any` 类型的公有成员。
## 代码逻辑
访问到跳转语句时，如果是 `return` 则直接返回 `RETURN_SIGN`；否则只有在外层有循环时才返回对应的类。

当子函数返回以上三个类之一时:

循环节点访问函数接住中断/跳过，终止/跳过循环，并正常返回；

函数调用节点接住返回，并返回其公有成员；

其余函数直接返回并返回相同的类。
# 其它细节
## 平凡返回值
原则上，所有不需要特别返回值的，都返回 `nullptr`。
## `visitReturn_stmt` 的返回值
如果返回是空，则返回 `nullptr`；

否则一律返回 `std::vector<dtype>`。