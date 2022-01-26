#include <iostream>
#include <vector>
#include <list>

template <typename InputIt, typename T>
InputIt myfind(InputIt first, InputIt last, const T& v)
{
	for (; first != last; ++first)
	{
		if (*first == v)
			return first;
	}
	return last;
}

int main()
{
	std::vector<int> ivec = { 1, 45, 92, 73, 34, 48 };
	std::list<int> ilist = { 1, 45, 92, 73, 34, 48 };

	auto v_it = myfind(ivec.begin(), ivec.end(), 100);
	auto l_it = myfind(ilist.begin(), ilist.end(), 73);

	if (v_it != ivec.end())
		std::cout << *v_it << '\n';
	if (l_it != ilist.end())
		std::cout << *l_it << '\n';
	return 0;
}
