#include <iostream>
using namespace std;

struct A
{
    int x;
    int y[3];
    void print()
    {
        cout << "x " << x << endl;
        cout << "y " << y[0] << " " << y[1] << " " << y[2] << endl;
    }
};

int main()
{
    A a{1, {1, 2, 3}};
    A b = a;
    a.print();
    b.print();
    a.y[1] = 8;
    a.print();
    b.print();
}
