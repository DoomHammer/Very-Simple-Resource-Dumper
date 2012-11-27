..\vsrd.exe resources.crs -o dumpedResources.c
..\vsrd.exe --header -o dumpedHeader.h

mingw32-gcc *.c -o test.exe
.\test.exe