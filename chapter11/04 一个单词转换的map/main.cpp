#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <map>

using std::string;
using std::ifstream;

std::map<string, string> buildMap(ifstream& map_file)
{
    std::map<string, string> trans_map; //����ת������
    //for (string key, value; map_file >> key && getline(map_file, value); )
    //    if (value.size() > 1) 
    //        trans_map[key] = value.substr(1).substr(0, value.find_last_not_of(' '));
    //return trans_map;
    string key; //Ҫת���ĵ���
    string value; //�滻�������
    //��ȡ��һ�����ʴ���key�У�����ʣ������ ����value
    while (map_file >> key && getline(map_file, value))
        if (value.size() > 1)
            trans_map[key] = value.substr(1);
        else
            throw std::runtime_error("no rule for " + key);
    return trans_map;
}

const string& transform(const string& s, const std::map<string, string>& m)
{
    auto map_it = m.find(s);
    return map_it == m.cend() ? s : map_it->second;
}

void word_transform(ifstream& map_file, ifstream& input)
{
    auto trans_map = buildMap(map_file); 
    //for (string text; getline(input, text); ) {
    //    std::istringstream iss(text);
    //    for (string word; iss >> word; )
    //        std::cout << transform(word, trans_map) << " ";
    //    std::cout << std::endl;
    //}
    string text; //���������е�ÿһ��
    while (getline(input, text)) { //��ȡһ������
        std::istringstream stream(text); //��ȡÿ������
        string word;
        bool firstword = true; //�����Ƿ��ӡ�ո�
        while(stream >> word) {
            if (firstword)
                firstword = false;
            else
                std::cout << " "; //�ڵ��ʼ��ӡһ���ո�
            std::cout << transform(word, trans_map); //��ӡ���
        }
        std::cout << "\n";
    }
}

int main()
{
    ifstream ifs_map("word_transformation_bad.txt"), ifs_content("given_to_transform.txt");
    if (ifs_map && ifs_content) 
        word_transform(ifs_map, ifs_content);
    else 
        std::cerr << "can't find the documents." << std::endl;
}
