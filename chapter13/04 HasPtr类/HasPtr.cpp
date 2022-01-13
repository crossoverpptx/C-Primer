#include <iostream>
#include <string>

using std::string; using std::ostream; using std::cout; using std::size_t;

class HasPtr {
	friend ostream& print(ostream&, const HasPtr&);
public:
	// string()������յ�string����󣬼ȿ��ַ���
	HasPtr(const string& s = string()) : ps(new string(s)), i(0), use(new size_t(1)) { } // constructor
	~HasPtr(); // ��������
	HasPtr(const HasPtr& rhs) : ps(rhs.ps), i(rhs.i), use(rhs.use) { ++* use; } // �������캯��
	HasPtr& operator=(const HasPtr&); // ���������
private:
	string* ps; // ps��һ��ָ�룬ָ��string����
	int i;
	size_t* use; // use��һ��ָ�룬ָ��size_t����
};

// ���������Ķ���
HasPtr::~HasPtr()
{
	if (-- * use == 0) {	// ������ü���Ϊ��0
		delete ps;			// �ͷ�string�ڴ�
		delete use;			// �ͷż������ڴ�
	}
}

// ��������صĶ���
HasPtr&
HasPtr::operator=(const HasPtr& rhs)
{
	++* rhs.use;			// �����Ҳ������������ü���
	if (-- * use == 0) {	// Ȼ��ݼ�����������ü���
		delete ps;			// ���û�������û�
		delete use;			// �ͷű��������ĳ�Ա
	}
	ps = rhs.ps;			// �����ݴ�rhs������������
	i = rhs.i;
	use = rhs.use;
	return *this;			// ���ر�����
}

// ��Ԫ�����Ķ���
ostream& print(ostream& os, const HasPtr& p)
{
	os << p.ps << ' ' << *p.ps << ' ' << *p.use;
	return os;
}

void func(const HasPtr& p)
{
	HasPtr temp;
	temp = p;
	cout << "p: ";
	print(cout, p) << '\n';;
	cout << "temp: ";
	print(cout, temp) << '\n';;
}

int main()
{
	cout << "HasPtr str1(\"copy me\"), str2;\n";
	HasPtr str1("copy me"), str2;
	cout << "str1: ";
	print(cout, str1) << '\n';
	cout << "str2: ";
	print(cout, str2) << '\n';

	cout << "\nstr2 = str1;\n";
	str2 = str1;
	cout << "str1: ";
	print(cout, str1) << '\n';
	cout << "str2: ";
	print(cout, str2) << '\n';

	cout << "\nfunc(str1);\n";
	func(str1);

	cout << "\nstr1: ";
	print(cout, str1) << '\n';
	cout << "str2: ";
	print(cout, str2) << '\n';
	return 0;
}
