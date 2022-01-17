#include <iostream>
#include <string>
#include <map> 
#include <functional> 

using std::string; using std::map; using std::cout; using std::function; using std::minus; using std::cin; using std::endl;

// ��ͨ����
int add(int i, int j) { return i + j; }
// lambda�������һ��δ�����ĺ���������
auto mod = [](int i, int j) { return i % j; };
// ����������
struct Div { 
    int operator ()(int i, int j) const { return i / j; } 
};

auto binops = map<string, function<int(int, int)>>
{
    { "+", add },                               // function pointer 
    { "-", minus<int>() },                 // library functor 
    { "/", Div() },                             // user-defined functor 
    { "*", [](int i, int j) { return i * j; } },  // unnamed lambda 
    { "%", mod }                                // named lambda object 
};


int main()
{
    while (cout << "Pls enter as: num operator num :\n", true)
    {
        int lhs, rhs;
        string op;
        cin >> lhs >> op >> rhs;
        cout << binops[op](lhs, rhs) << endl;
    }

    return 0;
}
