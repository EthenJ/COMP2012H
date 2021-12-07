#include <iostream>
using namespace std;

class A
{
public:
    int a;
    int b;
    void print()
    {
        // cout << a << " " << b << " " << c << endl;
        cout << a << " " << b << " " << endl;
    }
    A(const int &c) {}
    A(const int &a, const int &b) : a(a), b(b) { cout << "hh" << endl; }
    // private:
    //     int c = 5;
};

int main()
{
    A a{1, 2};
    a.print();
}