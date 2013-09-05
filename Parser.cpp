#include "Parser.h"

#include <iostream>
#include <fstream>
#include <streambuf>

enum Command {
    C_ALIAS,
    C_FILE,
    C_PATH,

    C_COMMENT
};

std::map<std::string, std::string> parse(const char *file)
{
    if ( strcmp(file, "") == 0 ) {
        std::cout << "No input file specified\n";
        exit(-1);
    }

    std::ifstream inputFile(file);
    if ( !inputFile.is_open() ) {
        std::cout << "could not open specified input\n";
        exit(-1);
    }

    std::string str;

    inputFile.seekg(0, std::ios::end);
    str.reserve( inputFile.tellg() );
    inputFile.seekg(0, std::ios::beg);

    str.assign( ( std::istreambuf_iterator<char> (inputFile) ), std::istreambuf_iterator<char> () );

    const char *acceptedChars = "abcdefghijklmnopqrstuvxzwyABCDEFGHIJKLMNOPQRSTUVXZWY0123456789/._-\0";

    std::string path  = "";
    std::string buf   = "";
    std::string alias = "";
    Command     cmd   = C_PATH;

    std::map<std::string, std::string> resources;

    const char *c;
    for ( size_t i = 0; i < str.size(); ++i ) {
        c = str.c_str() + i;

        // verify if we have a command
        switch ( *c ) {
            case '!':
                cmd = C_PATH;
                buf = "";
                continue;
                break;

            case '@':
                cmd = C_ALIAS;
                buf = "";
                continue;

            case ':':
                if ( cmd == C_ALIAS ) {
                    alias = buf;
                    buf   = "";
                    cmd   = C_FILE;
                }
                continue;

            case '#':
                cmd = C_COMMENT;
                buf = "";
                continue;

            case ';':
                if ( cmd == C_PATH ) {
                    path = buf;
                    if ( path == "/" ) {
                        path = "";
                    }
                    if ( path.c_str()[0] != '/' ) {
                        path = "/" + path;
                    }
                } else if ( cmd == C_FILE ) {
                    resources[path + '/' + alias] = buf;
                } else if ( cmd == C_COMMENT ) {
                } else {
                    std::cout << "malformed file";
                    exit(-1);
                }
                buf = "";
                cmd = C_COMMENT;
                continue;
        }

        // if it's not a command, verify it it's an acceptable char
        const char *a = acceptedChars;
        while ( *a != '\0' ) {
            if ( *c == *a ) {
                buf += *a;
                break;
            }
            a++;
        }
    }

    return resources;
}
