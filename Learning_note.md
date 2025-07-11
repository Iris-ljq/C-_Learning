# 抽象机制 
## 3.2 类 
自定义数据类型，表示某种概念 
### 3.2.1 具体类型 
类似内置类型

    一个复数类型和一个无穷精度整数与内置int非常相像，但有自己的语义和操作集合；vector和string很像内置的数组，只不过可操作性更好。
具体类型的典型特征：**表现形式是定义的一部分**
#### 一种算数类型
```cpp
class complex{
    double re,im;
public:
    complex()
}

# 函数
## 12.1 函数声明
定义函数的过程是描述某项操作应该如何执行的过程。<br>
函数声明：函数名、返回值类型、参数数量和类型。 <br>
返回类型 函数名（参数类型）；<br>
```c++
Elem* next_elem();//无参数，返回elem*
void exit(int); //int类型参数，无返回值
double sqrt(double);//double类型参数，返回double类型
```
__隐式参数类型转换__
```c++
double s2=sqrt(2);//用实参double{2}调用函数sqrt()
```
对于类成员函数，类的名字也是函数类型一部分<br>
_内联机制？_
### _矩阵算法_
### 函数声明的组成要件
- 函数名
- 参数列表
- 返回类型
- inline 愿望：通过内联函数体实现函数调用
- constexpr 当给定常量表达式作为实参时，应该可以在编译时对函数求值
- noexcept 函数不允许抛出异常
- 链接说明 如static
### 函数定义
特殊的函数声明
函数参数名不属于函数类型的一部分，不同的声明语句允许使用不同的参数名<br>
通过未命名参数表示参数未在函数中使用<br>
```c++
void search(table* t,const char* key,const char*) {} 
//未用到第三个参数
```
### 返回值
```c++
string to_string(int a); //前置返回类型
auto to_string(int a)->string; //后置返回类型
```
两种声明等价<br>
return指定返回值<br>
调用自身->__递归__
```c++
int fac2(int n)
{
    if(n>1)
        return n*fac2(n-1);
    return 1;
}
```
- 一旦函数返回了结果，所占存储空间就被重新分配。指针所指位置的内容会未知改变，不能返回指向局部非static变量的指针<br>

错误示例1：
```c++
int* fp()
{
    int local=1;
    //…
    return &local;
}
```
错误示例2：引用
```c++
int& fp()
{
    int local=1;
    //…
    return local;
}
```
不存在void值，可以调用void函数令其作为另一个void函数的返回值：
```cpp
void g(int* p);
void h(int* p)
{
    return g(p);//等价于“g(p);return;”
}
```
_可以将一个未按常规方式（通过return或者“跳转到函数末尾”）返回的函数标记为[[noreturn]]_

### constexpr函数
    函数无法在编译时求值，常量表达式必须在编译时能确定值，因此函数不能在常量表达式中被调用
例外：constexpr函数

constexpr出现在**函数定义**中，含义：“如果给定了常量表达式作为实参，则该函数应该能用在常量表达式中”。<br>
```cpp
constexpr int fac(int n)
{
    return (n>1)?n*fac(n-1):1;
}
constexpr int f9=fac(9); //必须在编译时求值
```
constexpr出现在**对象定义**中，含义：“在编译时对初始化器求值”。
```cpp
void f(int n)
{
    int f5=fac(5);//可能在编译时求值
    int fn=fac(n);//在运行时求值（n是变量）

    constexpr int f6=fac(6);//必须在编译时求值
    constexpr int fnn=fac(n);//错误：无法确保在编译时求值

    char a[fac(4)];//OK；数组尺寸必须是常量，而fac()恰好是constexpr
    char a2[fac(n)];//错误；n是变量
}
```
### 局部变量
线程执行到局部变量或常量的定义处时，她们将被初始化。<br>
若把变量声明为**static**，该对象在线程第一次到达它的定义时被初始化。

## 12.3 重载函数
    不同函数在不同类型的对象上执行相同概念的任务，给它们起同一个名字。
**重载（overloding）**：为不同数据类型的同一种操作起相同的名字<br>

    c++基本操作中，加法只有一个名字+，但是既可以执行整数值的加法，也可以执行浮点数的加法，还能执行这些类型彼此之间的加法
### 自动重载解析


