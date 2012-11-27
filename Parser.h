#ifndef PARSER_H
#define PARSER_H

#include <map>
#include <string>

class Parser {
public:
    static std::map<std::string,std::string> parse(const char* file);
};

#endif
