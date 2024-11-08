#include <stdio.h>

typedef char* string;

string strip(string str){
    size_t last = strlen(str) - 1;

    // get leading character
    while(isspace((unsigned char)*str)) str++;

    // get terminal character
    while(isspace(str[last])) last--;

    str[last] = '\0';
    return str;
}
