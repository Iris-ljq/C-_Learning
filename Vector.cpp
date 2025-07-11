#include"Vector.h"
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