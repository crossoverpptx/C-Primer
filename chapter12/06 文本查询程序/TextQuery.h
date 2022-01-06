#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <vector>
#include <map>
#include <set>
#include <memory>
#include <fstream>
#include <sstream>

using std::vector; using std::string; using std::map; using std::set;
using std::shared_ptr; using std::make_shared;
using std::ifstream; using std::ostream; using std::istringstream;
using std::endl;

class QueryResult; // Ϊ�˶��庯��query�ķ������ͣ���������Ǳ����

class TextQuery {
public:
	using line_no = vector<string>::size_type;
	TextQuery(ifstream&);
	QueryResult query(const string&) const;
private:
	shared_ptr<vector<string>> text; // �����ļ�
	map<string, shared_ptr<set<line_no>>> words_map; // ÿ�����ʵ������ڵ��кŵļ��ϵ�ӳ��
};

class QueryResult {
	friend ostream& print(ostream&, const QueryResult&);
public:
	QueryResult(shared_ptr<vector<string>> p, shared_ptr<set<TextQuery::line_no>> ln, string w, unsigned n) : text(p), lines(ln), sought(w), count(n) {}
private:
	shared_ptr<vector<string>> text; // �����ļ�
	shared_ptr<set<TextQuery::line_no>> lines; // ���ֵ��к�
	string sought; // ��ѯ����
	unsigned count = 0;
};

// constructors
TextQuery::TextQuery(ifstream& infile) : text(make_shared<vector<string>>()) {
	string line, word;
	for (size_t lineNumber = 1; getline(infile, line); ++lineNumber) { // ���ļ���ÿһ��
		text->push_back(line); // ��������ı�
		istringstream iss(line); // �����ı��ֽ�ɵ���
		while (iss >> word) { // ������ÿ������
			auto& lines = words_map[word]; // ������ʲ���words_map�У���֮Ϊ�±���words_map�����һ��
			if (!lines) // �����ǵ�һ�������������ʱ����ָ��Ϊ��
				lines = make_shared<set<line_no>>(); // ����һ���µ�set
			lines->insert(lineNumber); // �����кŲ���set��
		}
	}
}

// members
QueryResult TextQuery::query(const string& s) const {
	static auto notFound = make_shared<set<line_no>>();
	auto pos = words_map.find(s);
	if (pos == words_map.end())
		return { text, notFound, s, 0 };
	unsigned count = 0;
	string word;
	for (auto const& line : *text) {
		istringstream iss(line);
		while (iss >> word)
			if (word == s)
				++count;
	}
	return { text, pos->second, s, count };
}

// non-members
ostream& print(ostream& os, const QueryResult& result) {
	os << result.sought << " occurs " << result.count << ((result.count > 1) ? " times" : " time") << endl;
	for (auto const& n : *result.lines)
		os << "\t(line " << n << ") " << result.text->at(n - 1) << '\n';
	return os;
}

#endif
