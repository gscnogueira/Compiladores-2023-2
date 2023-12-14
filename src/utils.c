#include "utils.h"
#include <stdio.h>
#include <libgen.h>
#include <string.h>

const char* get_output_file_name(char* input_file_name){
    const char* file_name = basename(input_file_name);

    char* extension;

    extension = strrchr(file_name,'.');

    if (extension)
        strcpy(extension +1, "tm");
    else
        strcat (input_file_name, ".tm");


    return file_name;
}
