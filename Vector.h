class Vector{
public:
    Vector(int s);
    double& operator[](int i);
    int size();
private:
    double* elem; //指向动态分配的数组
    int sz;
};