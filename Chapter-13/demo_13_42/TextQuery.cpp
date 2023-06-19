#include <iostream>
#include <fstream>
#include <memory>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include "TextQuery.h"
#include "StrVec.h"

// 工具函数ctr大于1输出times, 否则输出time
std::string make_plural(size_t ctr, const std::string &word, const std::string &ending)
{
    return (ctr > 1) ? word + ending : word;
}

// 读取输入文件并建立单词到行号的映射
TextQuery::TextQuery(std::ifstream & is) : file(new StrVec())
{
    std::string text;
    while (std::getline(is, text))
    {
        file->push_back(text);         // 保存此行文本
        int n = file->size() - 1;      // 当前行号
        std::istringstream line(text); // 将行文本分解成单词
        std::string word;     
        while (line >> word)
        {
            // 如果单词不在wm中，以之为下标在wm中添加一项
            std::shared_ptr<std::set<line_no>> &lines = wm[word]; // lines 是一个shared_ptr
            if (!lines) // 在我们第一次遇到这个单词时，此指针为空 
                lines.reset(new std::set<line_no>); // 分配一个新的set
            lines->insert(n);
        }
    }
}

QueryResult TextQuery::query(const std::string & sought) const
{
	static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
	std::map<std::string, std::shared_ptr<std::set<line_no>>>::const_iterator loc = wm.find(sought);
	if(loc == wm.cend())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}

std::set<TextQuery::line_no>::iterator QueryResult::begin()
{
	return lines->begin();
}

std::set<TextQuery::line_no>::iterator QueryResult::end()
{
	return lines->end();
}

std::shared_ptr<StrVec> QueryResult::get_file()
{
	return file;
}

std::ostream & print(std::ostream &os, const QueryResult &qr)
{
    os << qr.word << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << std::endl;
    for (TextQuery::line_no num : *qr.lines)
        os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
    return os;
}