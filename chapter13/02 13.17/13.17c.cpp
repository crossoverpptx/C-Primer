#include <iostream>

struct Numbered {
	Numbered() { ++mysn; }
	unsigned mysn = 0;
};

void f(const Numbered &s) {
	std::cout << s.mysn << '\n'; 
}

int main()
{
	Numbered a, b = a, c = b;
	f(a);
	f(b);
	f(c);
	return 0;
}

// output
// 1
// 1
// 1