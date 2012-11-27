#include "Dumper.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::string IntToStdString(unsigned long long n)
{
    std::stringstream ss;
    ss << n;
    return ss.str();
}

void Dumper::dumpHeader(const char* file)
{
    std::ostream* out;
    if ( strcmp(file, "stdout") == 0 ) {
        out = &std::cout;
    } else {
        out = new std::ofstream(file, std::ios::out | std::ios::trunc);
    }
    
    *out << "#ifndef RESOURCES_H\n"
            "#define RESOURCES_H\n\n"
            "const char* getResource(const char* resource, unsigned long long *size);\n\n"
            "#endif" << std::endl;
    
    if ( strcmp(file, "stdout") != 0 ) {
        ((std::ofstream*)out)->close();
        delete out;
    }
}

Dumper::Dumper(const char* dst_file, std::map<std::string,std::string> files, std::string relative_path)
{
    dst.open(dst_file, std::ios::binary | std::ios::out );
    if ( !dst.is_open() ) {
        std::cout << "Could not open destination file." << std::endl;
        exit(-1);
    }
    this->files = files;
    this->relative_path = relative_path;
}

Dumper::~Dumper()
{
    dst.close();
}

void Dumper::fileDump(std::ifstream &src, std::ofstream &dst)
{
    int size = sizeof(char) * 1024 * 1024;
    int rsize = 0;
    char* buff = (char*) malloc( size );
    
    char* hb = (char*) malloc( sizeof(char)*3 );
    std::string hex = "";
    int count = 1;
    while ( !src.eof() ) {
        src.read(buff, size);
        rsize = src.gcount();
        
        for(size_t i = 0; i < rsize; ++i) {
            sprintf(hb, "%X", (unsigned char)buff[i]);
            hex += "0x";
            hex += strlen(hb) == 1 ? "0" : "";
            hex += hb;
            hex += ", ";
            
            if ( count % 16 == 0 )
                hex += "\n";
            count++;
        }
        dst << hex;
        hex = "";
    }
    
    free(buff);
    free(hb);
}

void Dumper::dump()
{
    dst << "#include <string.h>\n\n";
    std::string retriever = "";
    
    std::map<std::string,std::string>::iterator it;
    unsigned i = 0;
    for ( it = files.begin() ; it != files.end(); it++ ) {
        std::string alias = (*it).first;
        std::string file  = (*it).second;
        
        std::ifstream f((relative_path + '/' + file).c_str(), std::ios::binary | std::ios::ate );
        if ( !f.is_open() ) {
            f.open(file.c_str(), std::ios::binary | std::ios::ate );
            if ( !f.is_open() ) {
                std::cout << "Could not open file " << file << std::endl;
                continue;
            }
        }
        
        unsigned long long fsize = f.tellg();
        f.seekg (0, std::ios::beg);
        
        std::string varName = "_VSRCResourceFile" + IntToStdString(i);
        
        retriever += "\tif ( strcmp(resource, \"" + alias + "\") == 0 ) {\n" +
                     "\t\t*size = " + IntToStdString(fsize) + ";\n" +
                     "\t\treturn " + varName + ";\n" +
                     "\t}\n\n";
        
        dst << "static const char " + varName + "[] = {\n";
        fileDump( f, dst );
        dst << "\n};\n\n";
        
        f.close();
        i++;
    }
    
    dst << "const char* getResource(const char* resource, unsigned long long *size)\n{\n";
    dst << retriever;
    dst << "\t*size = 0;\n\treturn NULL;";
    dst << "\n}\n";
}

std::string Dumper::toHEX(unsigned char c)
{
    char* hb = (char*) malloc( sizeof(char) * 3 );
    
    sprintf(hb, "%X", c);
    
    std::string hex = "0x";
    hex += strlen(hb) == 1 ? "0" : "";
    hex += hb;
    
    free(hb);
    
    return hex;
}
