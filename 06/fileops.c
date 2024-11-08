#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char* string;

string* readlines(){
    string fname = "06\\test_assembler\\Add.asm";
    FILE *file = fopen(fname, "r");

    if(file == NULL){
        perror("Error opening file");
        return (string*)NULL;
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
        return (string*)NULL;
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
            return (string*)NULL;
        }
        lines[lines_count] = token;
        lines_count++;
        token = strtok(NULL, "\n");
    }
    free(file_content);
    return lines;
}

int main(){
    
}