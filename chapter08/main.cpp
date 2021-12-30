#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ifstream; //���ļ���ȡ����
using std::istringstream; //��string��ȡ����
using std::ostringstream; //��stringд������
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::isdigit; //�ж�һ���ַ��Ƿ���ʮ��������

struct PersonInfo {
    string name;
    vector<string> phones;
};

bool valid(const string& str) {
    return isdigit(str[0]);
}

string format(const string& str) {
    return str.substr(0, 3) + "-" + str.substr(3, 3) + "-" + str.substr(6);
}

int main() {
    ifstream ifs("phonenumbers.txt");
    if (!ifs) {
        cerr << "no phone numbers?" << endl;
        return -1;
    }

    string line, word; //�ֱ𱣴����������һ�к͵���
    vector<PersonInfo> people; //����������������м�¼
    istringstream record; //��ȡ�����ݵļ�¼
    while (getline(ifs, line)) { //���ն˽���һ���ַ������������ַ���line��   
        PersonInfo info;
        record.clear(); //���record
        record.str(line);
        record >> info.name;
        while (record >> word)
            info.phones.push_back(word);
        people.push_back(info);
    }

    for (const auto& entry : people) {
        ostringstream formatted, badNums;
        for (const auto& nums : entry.phones) //��֤����
            if (!valid(nums)) 
                badNums << " " << nums;
            else 
                formatted << " " << format(nums);
        if (badNums.str().empty())
            cout << entry.name << " " << formatted.str() << endl;
        else
            cerr << "input error: " << entry.name << " invalid number(s) " << badNums.str() << endl;
    }

    return 0;
}
