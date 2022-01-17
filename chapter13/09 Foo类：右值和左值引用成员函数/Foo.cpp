#include <algorithm>
#include <iostream>
#include <vector>

using std::vector; using std::ostream; using std::cout;

class Foo {
public:
	Foo() = default;
	Foo(const vector<int>& v) : data(v) { }		// ���캯��
	Foo(const Foo& rhs) : data(rhs.data) { }	// �������캯��
	Foo& operator=(const Foo&)&;	// ֻ������޸ĵ���ֵ��ֵ
	Foo sorted()&&;					// �����ڿɸı����ֵ
	Foo sorted() const&;			// �������κ����͵�Foo
	vector<int>::iterator begin() { return data.begin(); }
	vector<int>::iterator end() { return data.end(); }
	vector<int>::const_iterator begin() const { return data.cbegin(); }
	vector<int>::const_iterator end() const { return data.cend(); }
public:
	vector<int> data;
};

Foo&
Foo::operator=(const Foo& rhs)&
{
	auto newdata = rhs.data;
	data = newdata;
	return *this;
}

// ��������const����һ����ֵ������������Ƕ����ܶ������ԭַ����
Foo
Foo::sorted() const&
{
	cout << "sorted() const &\n";
	return Foo(*this).sorted(); // ret is rvalue
}

// ������Ϊ��ֵ����˿���ԭַ����
Foo
Foo::sorted()&&
{
	cout << "sorted() &&\n";
	sort(data.begin(), data.end());
	return *this;
}

Foo retVal()
{
	Foo ret({ 453, 345, 3, 123, 56, 73 });
	return ret;
}

Foo& retFoo()
{
	static Foo ret({ 453, 345, 3, 123, 56, 73 });
	return ret;
}

ostream& print(ostream& os, const Foo& someFoo)
{
	for (const auto& elem : someFoo)
		os << elem << ' ';
	return os;
}

int main()
{
	print(cout, retVal().sorted()) << '\n';
	print(cout, retFoo().sorted()) << '\n';
	return 0;
}
