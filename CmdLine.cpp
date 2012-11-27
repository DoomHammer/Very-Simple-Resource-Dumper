#include "CmdLine.h"

#include <iostream>

CmdLine::CmdLine(int argc, const char** argv)
{
    if ( argc == 1 ) {
        std::cout << "\nUsage: " << argv[0] << " [-t] [input_file] [-o output_file]\n" <<
                     "\t-o         file to be writen to. WILL BE OVERRIDEN. If not given defaults to stdout\n" <<
                     "\t--header   create a header file to be used in your project.\n" <<
                     "\tinput_file resources definition file\n\n";
        exit(0);
    }
    
    this->m_inputFile  = "none";
    this->m_outputFile = "stdout";
    this->m_operation  = DumpResources;
    
    const char* c;
    for(int i = 1; i < argc; ++i) {
        c = argv[i];
        
        if ( strcmp(c, "--header") == 0 ) {
            this->m_operation = DumpHeader;
            continue;
        }
        
        if ( strcmp(c, "-o") == 0 ) {
            if ( i+1 >= argc ) {
                std::cerr << "Ouput file expected, nothing given.\n";
                exit(-1);
            }
            
            this->m_outputFile = argv[++i];
            continue;
        }
        
        this->m_inputFile = c;
    }
}
