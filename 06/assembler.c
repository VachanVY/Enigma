#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


typedef char* string;

#ifdef _WIN32
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

int main(int argc, string argv[]){
    printf("\n");
    string fname = "06\\test_assembler\\Add.asm";
    FILE *file = fopen(fname, "r");

    if(file == NULL){
        perror("Error opening file");
        return 1;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    unsigned long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file content
    string file_content = malloc(file_size + 1);
    if (file_content == NULL){
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }

    // Read the file content into the string
    fread(file_content, 1, file_size, file);
    file_content[file_size] = '\0'; // Null-terminate the string

    fclose(file);
    printf("%s\n\n", file_content);

    // Convert to array of strings with "\n" as seperator
    string *lines = NULL;
    size_t lines_count = 0;
    string token = strtok(file_content, "\n");

    while (token != NULL) {
        lines = realloc(lines, sizeof(string) * (lines_count + 1));
        if (lines == NULL) {
            perror("Error reallocating memory");
            free(file_content);
            return 1;
        }
        lines[lines_count] = token;
        lines_count++;
        token = strtok(NULL, "\n");
    }

    // Print each line to verify
    for (size_t i = 0; i < lines_count; i++) {
        printf("Line %zu: %s\n", i, lines[i]);
    }

    free(lines);
    free(file_content);
}

string strip(string str){
    size_t last = strlen(str) - 1;

    // get leading character
    while(isspace((unsigned char)*str)) str++;

    // get terminal character
    while(isspace(str[last])) last--;

    str[last] = '\0';
    return str;
}

// input: Array of strings | output: prepro lines
void parse(string *lines, size_t string_length){
    string* prepro_lines = NULL;
    string line;
    int line_count = 0, var_start = 16;

    for(int i=0; i<string_length; i++){
        line = lines[i];
                
    }

}

// get machine code // __call__
// input: string
string* assembler(string* preprocessed){

}

// handle A-Instruction
string handle_a_instruction(string line){

}


// handle C-Instruction
string handle_c_instruction(string line){

}

// get binary form
string get_binary_form(unsigned int uint, int num_bits){

}

// dest comp jump symbols table
