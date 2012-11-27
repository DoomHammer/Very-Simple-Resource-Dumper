../vsrd resources.crs -o dumpedResources.c
../vsrd --header -o dumpedHeader.h

gcc *.c -o test
./test