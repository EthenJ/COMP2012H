#include <iostream>
using namespace std;

template <typename T1, typename T2>
class Pair
{
    template <typename T3, typename T4> // 不加这个直接ggnai
    // template <typename T1, typename T2>
    friend ostream &operator<<(ostream &os, const Pair<T3, T4> &p);
    // {
    //     os << p.value1 << ": " << p.value2;
    //     return os;
    // }

public:
    Pair(T1 v1, T2 v2) : value1(v1), value2(v2){};

private:
    T1 value1;
    T2 value2;
};

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const Pair<T1, T2> &p)
{
    os << p.value1 << ": " << p.value2;
    return os;
}

int main()
{
    Pair<int, char> p(10, 'c');
    cout << p; // 没有这个就不会gg奶
    return 0;
}