#ifndef SCREEN_H
#define SCREEN_H

#include <string>

class Screen {
public:
	typedef std::string::size_type pos;
	//也可以等价地使用类型别名
	//using pos = std::string::size_type;
	Screen() = default; //因为Screen有另一个构造函数，所以本函数是必需的
	//cursor被其类内初始值初始化为0
	Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht * wd, c) {}
	char get() const { return contents[cursor]; } //读取光标处的字符，隐式内联
	inline char get(pos ht, pos wd) const; //显式内联
	Screen& move(pos r, pos c); //能在之后被设为内联
	void some_member() const;
	Screen& set(char);
	Screen& set(pos, pos, char);
	//根据对象是否是const重载了display函数
	Screen& display(std::ostream& os) { do_display(os); return *this; }
	const Screen& display(std::ostream& os) const { do_display(os); return *this; }
private:
	pos cursor = 0;
	pos height = 0, width = 0;
	std::string contents;
	mutable size_t access_ctr; //即使在一个const对象内也能被修改
	void do_display(std::ostream& os) const { os << contents; } //该函数负责显示Screen的内容
};

inline Screen& Screen::move(pos r, pos c) {
	pos row = r * width; //计算行的位置
	cursor = row + c; //在行内将光标移动到指定的列
	return *this; //以左值的形式返回对象
}

char Screen::get(pos r, pos c) const {
	pos row = r * width; //计算行的位置
	return contents[row + c]; //返回给定列的字符
}

void Screen::some_member() const {
	++access_ctr;
}

inline Screen& Screen::set(char c) {
	contents[cursor] = c;
	return *this;
}

inline Screen& Screen::set(pos r, pos col, char ch) {
	contents[r * width + col] = ch;
	return *this;
}

#endif
