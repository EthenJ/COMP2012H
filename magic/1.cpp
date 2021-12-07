#include <iostream>
using namespace std;

class A
{
protected:
    int a;
    int b;
    int c;

public:
    A() : a(1), b(2), c(3) {}
    ~A() = default;
    void set(const int &a, const int &b, const int &c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    virtual void print()
    {
        cout << "a " << a << "  b " << b << "  c " << c << endl;
    }
};

class AA : public A
{
private:
    int c;
    int d;

public:
    AA() : c(4), d(5) {}
    ~AA() = default;
    void set(const int &a, const int &b, const int &c, const int &d)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }

    void print()
    {
        cout << "a " << a << "  b " << b << "  c " << c << "  d " << d << endl;
    }
};

int main()
{
    A a;
    AA aa;
    a.set(8, 9, 4); // c ??
    aa.set(5, 6, 7, 8);
    a = aa;
    a.print();
}