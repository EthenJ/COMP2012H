#include <iostream>
using namespace std;

template <int x>
int function()
{
    return x;
}

int main()
{
    for (int i = 0; i < 20; i++)
    {
        cout << function<i>() << endl;
    }
//    int i = 3;
//     cout << function<i>() << endl;
}