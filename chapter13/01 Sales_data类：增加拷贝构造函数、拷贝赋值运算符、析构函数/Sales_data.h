#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>

class Sales_data {
	//ΪSales_data�ķǳ�Ա������������Ԫ����
	friend Sales_data add(const Sales_data&, const Sales_data&);
	friend std::istream& read(std::istream&, Sales_data&);
	friend std::ostream& print(std::ostream&, const Sales_data&);
public:
	//�����Ĺ��캯��
	Sales_data() = default;
	Sales_data(const std::string& s) : bookNo(s) {}
	Sales_data(const std::string& s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p * n) {}
	Sales_data(std::istream&);
	// ��ϳɵĿ������캯���ȼ۵Ŀ������캯��������
	Sales_data(const Sales_data&);
	//�³�Ա������Sales_data����Ĳ���
	std::string isbn() const { return bookNo; }	//������Ա����
	Sales_data& combine(const Sales_data&);
	// �ȼ��ںϳɿ�����ֵ�����
	Sales_data& operator=(const Sales_data&);
	// ��Ա�ᱻ�Զ����٣�����֮�ⲻ��Ҫ����������
	~Sales_data() {}
private:
	double avg_price() const;
	//���ݳ�Ա��2.6.1�ڣ�Page64�����û�иı�
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

//���캯���Ķ���
Sales_data::Sales_data(std::istream& is) {
	read(is, *this);
}

// ��Sales_data�ĺϳɵĿ������캯���ȼ�
Sales_data::Sales_data(const Sales_data& orig) :
	bookNo(orig.bookNo),			// ʹ��string�Ŀ������캯��
	units_sold(orig.units_sold),	// ����orig.units_sold
	revenue(orig.revenue)			// ����orig.revenue
	{}								// �պ�����


//Sales_data�ӿڵĵķǳ�Ա��ɲ��ֵ�����
Sales_data add(const Sales_data&, const Sales_data&);
std::istream& read(std::istream&, Sales_data&);
std::ostream& print(std::ostream&, const Sales_data&);

//Sales_data�ӿڵĵķǳ�Ա��ɲ��ֵĶ���
Sales_data add(const Sales_data& lhs, const Sales_data& rhs) {
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

std::istream& read(std::istream& is, Sales_data& item) {
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}

std::ostream& print(std::ostream& os, const Sales_data& item) {
	os << item.isbn() << " " << item.units_sold << " "
		<< item.revenue << " " << item.avg_price();
	return os;
}

//Sales_data�ĳ�Ա�����Ķ���
Sales_data& Sales_data::combine(const Sales_data& rhs) {
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

double Sales_data::avg_price() const {
	if (units_sold)
		return revenue / units_sold;
	else
		return 0;
}

// �ȼ��ںϳɿ�����ֵ�����
Sales_data& Sales_data::operator=(const Sales_data& rhs) {
	bookNo = rhs.bookNo;			// ����string::operator=
	units_sold = rhs.units_sold;	// ʹ�����õ�int��ֵ
	revenue = rhs.revenue;			// ʹ�����õ�double��ֵ
	return *this;					// ����һ���˶��������
}

#endif
