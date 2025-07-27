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
调用函数fct时，编译器依据考察实参类型与作用域中名为fct的哪个函数的形参类型最匹配，找到最佳匹配时调用该函数。
```cpp
void print(double);
void print(long);
void f()
{
    print(1L); //print(long)
    print(1.0);//print(double)
    print(1);//错误，二义性，无法确定调用哪个函数
}
```
# 第16章 类
## 16.2 类基础
- 一个类由一组成员构成。常见的成员类别是数据成员和成员函数。<br>
- public成员提供类的接口，private成员提供实现细节。
- struct是成员默认为public的class。
```
类是一种将抽象转换为用户定义类型的C++工具，将数据表示和操纵数据的方法组合成一个整洁的包。

类规范由两个部分组成：
1.类声明：以数据成员的方式描述数据部分，以成员函数（被称为方法）的方式描述公有接口。（类的蓝图）
2.类方法定义：描述如何实现类成员函数。（细节）
```
```c++
class X{
    private: //类的表示（实现）是私有的
        int m;
    public: //用户接口是公有的
        X(int i=0):m{i}{} //构造函数（初始化数据成员m）
        int mf(int i) //成员函数
        {
            int old=m;
            m = i; //设置一个新值
            return old; //返回旧值
        }
};
X var{7}; //一个X类型的变量，初始化为7
int use(X var,X* ptr)
{
    int x = var.mf(7); //使用.(点)访问
    int y = ptr->mf(9); //使用->(箭头)访问
    int z = var.m; //错误：不能访问私有成员
}
```
接口（类声明）放在头文件中，实现（类方法的代码）放在源代码文件中。
```c++
#ifndef STOCK00_H_
#define STOCK00_H_

#include <string>
class Stock //class declaration
{
private:
    std::string company;
    double share_val;
    void set_tot(){total_val=shares*share_val;}
public:
    void acquire(const std::string & co, long n,double pr);
} ;
#endif //#ifndef和endif防止多次包含同一个文件
```

1. **访问控制**  
   使用类对象的程序都可以直接访问公有部分，但只能通过公有成员函数来访问对象的私有成员。公有成员函数是程序和对象的私有成员之间的桥梁，提供了对象和程序之间的接口。  
   类设计尽可能将公有接口与实现细节分开，公有接口表示设计的抽象组件，将实现细节放在一起并将它们与抽象分开叫作`封装`。**封装**例子：**数据隐藏**（将数据放在类的私有部分中）；将实现细节隐藏在私有部分中，就像stock类对set_tot()做的那样；将类函数定义和类声明放在不同文件中。
 
2. 控制对成员的访问：公有还是私有
   由于隐藏数据是OOP（一种编程风格）主要目标之一 ，因此数据项通常放在私有部分，组成类接口的成员函数放在公有部分。成员函数也可放在私有部分，通常使用私有成员函数来处理不属于公有接口的实现细节。   
   `不必在类声明中使用关键字private，因为这是类对象的默认访问控制：`
   ```c++
   class World
   {
        float mass; 
        char name[20];//private by default
    public:
        void tellall(void);
        ...
   };
   ```
### 实现类成员函数
与常规函数不同的特征：  
1. 定义成员函数时，使用作用域解析运算符：：来标识函数所属类；
2. 类方法可以访问类的private组件。  
   
类方法的完整名称中包括类名，`Stock::update()`是函数限定名,`update()`是全名的缩写（非限定名）,只能在类作用域中使用。  
2.特征是方法可以访问类的私有成员，如show()方法:
```c++
std::cout<<"Company:"<<company
<<" Shares:"<<shares<<endl
<<" Share Price:$"<<share_val
<<" Total Worth:$"<<total_val<<endl;
```
company\shares都是Stock类的私有成员，不能使用非成员函数访问。  
类方法example:
```c++
//stock00.cpp
#include "stock00.h"
#include<iostream>

void Stock::acquire(const std::string &co,long n,double pr)
{
    company = co;
    if(n<0)
    {
        std::cout<<"Number of shares can't be negative; "
        <<company<<" shares set to 0."<<std::endl;
        shares = 0;
    }
    else
        shares = n;
    share_val = pr;
    set_tot();
}
```
3. 方法使用哪个对象
   创建对象：
   ```
   Stock kate,joe;//声明类变量
   ```
   通过成员运算符使用对象的成员函数：
   ```
   kate.show();
   joe.show();
   ```
### 修改实现
ostream类包含可用于控制格式的成员函数.使用setf()可避免科学计数法
```
std::cout.setf(std::ios_base::fixed,std::ios_base::floatfield);
```
控制格式：`std::cout.precision(3);`显示三位小数  
格式修改一直有效，直到再次修改，因此可能影响客户程序中的后续输出。因此，show()应重置格式信息，使其恢复到被调用前的状态。
```c++
std::streamsize prec = std::cout.precision(3);
std::cout.precision(prec);//reset
```
## 类的构造函数和析构函数
**类构造函数**：专门用于构造新对象、将值赋给它们的数据成员。C++为成员函数提供名称和使用方法，程序员提供方法定义。`没有返回值和声明类型`
```cpp
Stock::Stock(const string& co,long n,double pr)
{
    company = co;
    if(n<0)
    {
      std::cerr<<"Number of shares can't be negative; "
        <<company<<" shares set to 0."<<std::endl;
   shares = 0;
    }
    else
    shares = n;
    share_val = pr;
    set_tot();
}
程序声明对象时，会自动调用构造函数