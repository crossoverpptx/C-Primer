#ifndef SCREEN_H
#define SCREEN_H

#include <string>

class Screen {
public:
	typedef std::string::size_type pos;
	//Ҳ���Եȼ۵�ʹ�����ͱ���
	//using pos = std::string::size_type;
	Screen() = default; //��ΪScreen����һ�����캯�������Ա������Ǳ����
	//cursor�������ڳ�ʼֵ��ʼ��Ϊ0
	Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht * wd, c) {}
	char get() const { return contents[cursor]; } //��ȡ��괦���ַ�����ʽ����
	inline char get(pos ht, pos wd) const; //��ʽ����
	Screen& move(pos r, pos c); //����֮����Ϊ����
	void some_member() const;
	Screen& set(char);
	Screen& set(pos, pos, char);
	//���ݶ����Ƿ���const������display����
	Screen& display(std::ostream& os) { do_display(os); return *this; }
	const Screen& display(std::ostream& os) const { do_display(os); return *this; }
private:
	pos cursor = 0;
	pos height = 0, width = 0;
	std::string contents;
	mutable size_t access_ctr; //��ʹ��һ��const������Ҳ�ܱ��޸�
	void do_display(std::ostream& os) const { os << contents; } //�ú���������ʾScreen������
};

inline Screen& Screen::move(pos r, pos c) {
	pos row = r * width; //�����е�λ��
	cursor = row + c; //�����ڽ�����ƶ���ָ������
	return *this; //����ֵ����ʽ���ض���
}

char Screen::get(pos r, pos c) const {
	pos row = r * width; //�����е�λ��
	return contents[row + c]; //���ظ����е��ַ�
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
