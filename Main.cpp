#include "CmdLine.h"
#include "Dumper.h"
#include "Parser.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

int main (int argc, char const **argv)
{
    CmdLine cmdline(argc, argv);
    
    switch( cmdline.operation() ) {
        case DumpHeader:
            Dumper::dumpHeader(cmdline.output());
            break;
        
        case DumpResources:
            // [alias]=file
            std::map<std::string,std::string> files;
            files = Parser::parse(cmdline.input());
            
            std::string rp = cmdline.input();
            rp = rp.substr( 0, rp.find_last_of("/\\") );
            
            Dumper dump(cmdline.output(), files, rp);
            dump.dump();
            break;
    }
    
    return 0;
}
