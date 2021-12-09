#include <iostream>
using namespace std;

class A
{
public:
    A()
    {
        cout << "A" << endl;
    }
    A(const A &a)
    {
        cout << "AA" << endl;
    }
    virtual ~A()
    {
        cout << "Aggnai" << endl;
    }
};

class B : public A
{
public:
    B()
    {
        cout << "B" << endl;
    }
    ~B()
    {
        cout << "Bggggggg" << endl;
    }
};

int main()
{
    A *b = new B;
    A d = *b;
    delete b;
}