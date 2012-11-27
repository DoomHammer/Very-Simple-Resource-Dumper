#ifndef DUMPER_H
#define DUMPER_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>

class Dumper {
public:
    static void dumpHeader(const char* file);
    
    Dumper(const char* dst_file, std::map<std::string,std::string> files, std::string relative_path);
    ~Dumper();
    
    void dump();
    
protected:
    std::ofstream dst;
    std::string relative_path;
    std::map<std::string,std::string> files;
    
    std::string toHEX(unsigned char c);
    void fileDump(std::ifstream &src, std::ofstream &dst);
};

#endif
