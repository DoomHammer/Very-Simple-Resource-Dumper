#ifndef DUMPER_H
#define DUMPER_H

#include <map>
#include <string>

void dumpHeader(const char *file);
void dumpC(const char *dst_file, std::map<std::string, std::string> files, std::string relative_path);
#endif
