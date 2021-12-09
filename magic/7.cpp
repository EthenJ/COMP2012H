class Base
{
};
class Derived : protected Base
{
};
int main()
{
    Derived d;
    Base &bRef = d; // 'Base' is an inaccessible base of 'Derived'
}