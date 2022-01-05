#pragma once

#include <vector>
#include <map>
#include <set>
#include <memory>
#include <fstream>
#include <sstream>


class QueryResult;

class TextQuery {
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&) const;
private:
	std::shared_ptr<std::vector<std::string>> text;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> words_map;
};

class QueryResult {
	friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	QueryResult(std::shared_ptr<std::vector<std::string>> p,
		std::shared_ptr<std::set<TextQuery::line_no>> ln,
		std::string w, unsigned n) :
		text(p), lines(ln), sought(w), count(n) {}
private:
	std::shared_ptr<std::vector<std::string>> text;
	std::shared_ptr<std::set<TextQuery::line_no>> lines;
	std::string sought;
	unsigned count = 0;
};

// constructors
TextQuery::TextQuery(std::ifstream& infile) :
	text(std::make_shared<std::vector<std::string>>())
{
	std::string line, word;
	for (size_t lineNumber = 1; getline(infile, line); ++lineNumber) {
		text->push_back(line);
		std::istringstream iss(line);
		while (iss >> word) {
			auto& lines = words_map[word];
			if (!lines)
				lines = std::make_shared<std::set<line_no>>();
			lines->insert(lineNumber);
		}
	}
}

// members
QueryResult TextQuery::query(const std::string& s) const
{
	static auto notFound = std::make_shared<std::set<line_no>>();
	auto pos = words_map.find(s);
	if (pos == words_map.end())
		return { text, notFound, s, 0 };
	unsigned count = 0;
	std::string word;
	for (auto const& line : *text) {
		std::istringstream iss(line);
		while (iss >> word)
			if (word == s)
				++count;
	}
	return { text, pos->second, s, count };
}

// non-members
std::ostream& print(std::ostream& os, const QueryResult& result)
{
	os << result.sought << " occurs " << result.count 
	   << ((result.count > 1) ? " times" : " time") << std::endl;
	for (auto const& n : *result.lines)
		os << "\t(line " << n << ") " << result.text->at(n - 1) << '\n';
	return os;
}
