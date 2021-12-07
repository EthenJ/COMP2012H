class Base
{
};

class Derived : protected Base
{
};

int main()
{
    Base *b = new Derived;
    // gg nai
    // 2.cpp:11:19: error: 'Base' is an inaccessible base of 'Derived'
    return 0;
}