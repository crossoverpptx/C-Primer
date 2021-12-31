#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string>& elimDups(std::vector<std::string>& words) {
    //���ֵ�������words���Ա�����ظ�����
    sort(words.begin(), words.end());
    //unique�������뷶Χ��ʹ��ÿ������ֻ����һ��
    //�����ڷ�Χ��ǰ��������ָ���ظ�����֮��һ��λ�õĵ�����
    auto end_unique = unique(words.begin(), words.end());
    //ʹ����������eraseɾ���ظ�����
    words.erase(end_unique, words.end());
    return words;
}

bool isShorter(const std::string& s1, const std::string& s2) {
    return s1.size() < s2.size();
}

int main() {
    std::vector<std::string> words{ "the", "quick", "red", "fox", "jumps",
                                    "over", "the", "slow", "red", "turtle" };
    elimDups(words);
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << "\n";

    stable_sort(words.begin(), words.end(), isShorter);
    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << "\n";

    return 0;
}
