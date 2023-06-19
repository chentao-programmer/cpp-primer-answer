#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include<iostream>
#include<fstream>
#include<memory>
#include<set>
#include<map>
#include<string>
#include "StrVec.h" 

class QueryResult;

class TextQuery
{
public:
    using line_no = size_t;
	TextQuery(std::ifstream &);
	QueryResult query(const std::string &) const;
	TextQuery(const TextQuery & tq) = default;
	TextQuery & operator=(const TextQuery & tq) = default;
	~TextQuery() = default;

private:
    std::shared_ptr<StrVec> file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm; // 每个单词到它所在行号的集合的映射
};

class QueryResult
{
    friend std::ostream & print(std::ostream &, const QueryResult &);
public:
    QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p, std::shared_ptr<StrVec> f) : word(s), lines(p), file(f) { }
    std::set<TextQuery::line_no>::iterator begin();
    std::set<TextQuery::line_no>::iterator end();
    std::shared_ptr<StrVec> get_file();
    
private:
    std::string word; //查询的单词
    std::shared_ptr<std::set<TextQuery::line_no>> lines; // 出现的行号
    std::shared_ptr<StrVec> file; // 输入文件
};

#endif