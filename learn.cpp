#include <iostream>
using namespace std;

#include <iostream>
#include <vector>  // 引入 vector 头文件

int main() {
    
    /*enum color { red, blue=5, green } a;
    a = green;
    cout << a << endl;
    int i=10;
    float f= static_cast<float>(i);*/

       /*cout<<"accept?\n";
        char answer =0;
        cin>>answer;//cin标准输入流 <<输出 >>输入
        switch (answer)
        {
            case 'y':
                return true;
            case 'n':
                return false;
            default:
                cout<<"I'll take that for a no.\n";
                return false;
        
        //if (answer=='y') return true;
       // return false;
    }*/

    char v[6];
    char* p; //指针指向字符
    char* p = &v[3]; //p指向v的第4个元素 &指v[3]的地址
    char x = *p; //*p是p所指向的对象 *表示内容

    void copy_fct()
    {
        int v1[] = {0,1,2,3,4,5,6,7,8,9};
        int v2[10];
        for(auto i = 0; i!=10; ++i)
        v2[i] = v1[i];
    }
    void print ()
    {
        int v[] = {0,1,2,3,4,5,6,7,8,9};
        for(auto x:v)
           cout<<x<<'\n'; //对于v的每个元素，将其从头到尾依次放入x并打印
        for(auto&x : v)
            ++x; //&表示……的引用，类似指针，区别是无需用*访问引用值
                 //令x指向一个元素，不把v的值拷贝到变量x中
    }

    int count_x(char* p,char x)

    {
        if(p==nullptr) return 0;
        int count=0; 
        for(; *p!=0; ++p)
            if(*p==x) ++count;
        return count;
    }

    //结构
    struct Vector{
        int sz;
        double* elem;
    }
    
    void vector_init(Vector& v,int s)
    {
        v.elem=new double[s]; //分配一个数组，包含s个double值
        v.sz=s;
    }

    void f(Vector v,Vector& rv,Vector* pv)
    {
        int i1 = v.sz; //通过名字访问
        int i2 = rv.sz; //通过引用访问
        int i3 = pv->sz; //通过指针访问
    }
    double read_and_sum(int s)
    {
        Vector v;
        vector_init(v,s);
        for(int i=0;i!=s;++i)
            cin>>v.elem[i];
        double sum=0;
        for(int i=0;i!=s;++i)
            sum+=v.elem[i];
        return sum;
    }

    //类
    class Vector{
        public:
            Vector(int s):elem{new double[s]},sz{s}{} //构建一个vector 
            //new从自由空间获取s个double类型元素，并用一个指向这些元素的指针初始化elem
            //用s初始化sz

            double& operator[](int i){return elem[i];}    

    }
    double read_and_sum(int s)
    {
        Vector v(s); //包含s个元素的向量
        for(int i=0;i!=v.size();++i)
            cin>>v[i];
        double sum=0;
        for(int i=0;i!=v.size();++i)
            sum+=v[i];
        return sum;
    }

    //枚举
    enum class Color {red,blue,green}; //class指明枚举是强类型
    enum class Traffic_light {green,yellow,red};
    //enum class只定义赋值、初始化和比较（== <）
    Color col=Color::red;
    Traffic_light light=Traffic_light::red;

    //次强类型的普通enum
    Traffic_light& operator++(Traffic_light& t) //前置递增运算符++
    {
        switch(t){
            case Traffic_light::green: return t=Traffic_light::yellow;
            case Traffic_light::yellow: return t=Traffic_light::red;
            case Traffic_light::red: return t=Traffic_light::green;
        }
    }
    Traffic_light next=++light; //next变成Traffic_light::green
    return 0;
}

//2.4 模块化
//定义多个独立开发部分（函数、用户自定义类型、类层次、模版）的交互关系
//第一步把某部分的接口和实现分离开 用声明描述接口
//声明指定了使用某个函数或某种类型所需的所有内容
double sqrt(double); //这个平方根函数接受一个double,返回值也是一个double
class Vector{
    public:
        Vector(int s);
        double& operator[](int i);
        int size();
    private:
        double* elem;
        int sz; //elem指向一个数组，该数组包含sz个double
}

double sqrt(double d) //sqrt()的定义
{

}
//Vector定义全部3个成员函数
Vector::Vector(int s) //构造函数的定义
:elem{new double[s]}, sz{s} //初始化成员
{
}
double& Vector::operator[](int i) //下标运算符的定义
{
    return elem[i];
}
int Vector::size() //size()的定义
{
    return sz;
}

//2.4.1 分离编译
//用户代码只有所用类型和函数的声明，定义则放置在分离的源文件里，并被分别编译
//把描述接口的声明放置在一个特定文件中

//Vector.h:
class Vector{
public:
    Vector(int s);
    double& operator[](int i);
    int size();
private:
    double* elem; //指向动态分配的数组
    int sz;
};
//这段声明被置于文件Vector.h中，称为头文件

//user.cpp:
#include "Vector.h" //获得Vector.h中声明的接口
#include<cmath> //获得标准库数学函数接口
using namespace std; //令std成员可见

//2.4.2 名字空间
namespace My_code{
    class complex{};
    complex sqrt(complex);
    int main();
}
int My_code::main()
{
    complex z;
    complex w = sqrt(z);
}
int main()
{
    return My_code::main();
}
//确保自定义名字不会和名字空间std中的标准库名字冲突
using namespace std; //获取标准库名字空间中名字的访问权，使用using

//2.4.3 错误处理
//异常
double& Vector::operator[](int i)
{
    if(i>=size())
        throw out_of_range("Vector::operator[]");
    return elem[i];
} //检测潜在越界错误并抛出一个out_of_range异常