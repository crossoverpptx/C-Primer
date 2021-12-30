#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>

struct Sales_data {
	//�³�Ա������Sales_data����Ĳ���
	std::string isbn() const { return bookNo; }	//������Ա����
	Sales_data& combine(const Sales_data&);
	double avg_price() const;
	//���ݳ�Ա��2.6.1�ڣ�Page64�����û�иı�
	std::string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

//Sales_data�ķǳ�Ա�ӿں���
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream& print(std::ostream&, const Sales_data&);
std::istream& read(std::istream&, Sales_data&);

//Sales_data�ķǳ�Ա�ӿں�������
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

Sales_data add(const Sales_data& lhs, const Sales_data& rhs) {
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

//Sales_data�ĳ�Ա��������
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

#endif
