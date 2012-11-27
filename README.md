Very Simple Resource Dumper
===========================

Dumps one .c and one .h files that can be used to compile resources into the binary executable.

It has a very simple api. Only one method:

    const char* getResource(const char* resource, unsigned long long *size);

Generate the .h file with:
    
    vsrd --header -o file_name.h
    
generate the .c file with
    
    vsrd input.crs -o output.c
    
Include the .h and compile/link with the .c to use the files like:

    unsigned long long resSize;
    const char* logo = getResource("/imgs/logo.png", &resSize);
    // use logo
    
The file describing the resources for this could look like:

    ! /imgs ;
    @ logo.png : path_to_file_in_disk/logo_file_name.png ;
    
See the test folder for more info.
