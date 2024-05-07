#include <windows.h>
#include <stdio.h>

void createFile(const char* filename, const char* text){
    FILE *file = fopen(filename, "r");
    if (file == NULL || fgetc(file) == EOF) {
        file = fopen(filename, "w");
        if (file == NULL) {
            printf("Error opening file for writing.\n");
            return;
        }
        fprintf(file, text);
        printf("Text written to file successfully.\n");
    }
    else 
        printf("File is not empty.\n");
    fclose(file);
}

void clearFile(const char* filename){
    FILE* file = fopen(filename, "w");
    if (file != NULL) fclose(file);
}

void addToFile(const char* filename, char* text){
    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fputs(text, file);
        fputs("\n", file);
        fclose(file);
    }
}

void setLastId(const char* filename, unsigned int* lastId){
    FILE* file = fopen(filename, "r");
    char* text;
    if(file != NULL){
        fgets(text,10, file);
    }
}

void editBookFileF(Book* book, char* filename)
{
    clearFile(filename);

    FILE* outfile = fopen(filename, "wb");
    fwrite(&book, sizeof(Book), 1, outfile);
    fclose(outfile);      
}

Book readBookFileF(char* filename)
{
    Book book;
    FILE* infile = fopen(filename, "wb+");
    fread(&book, sizeof(Book), 1, infile);
    fclose(infile);
    return book;      
}

void editFile(const char* filename){
    clearFile(filename);
}

size_t readTextFromFile(const char *filename, char *buffer, size_t bufferSize) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    size_t bytesRead = fread(buffer, 1, bufferSize - 1, file); 
    buffer[bytesRead] = '\0'; 
    fclose(file);
    return bytesRead;
}

char* readFile(const char *filename) {
    char* container;
    FILE *file = fopen(filename, "r"); 
    if (file != NULL) {
        fgets(container, sizeof(container), file);
        fclose(file);
        return container;
    } 
    else {
        printf("Error opening file: %s\n", filename);
    }
}



void initFileSystem(){
    CreateDirectoryA("C:/Biblioguard", NULL);
    CreateDirectoryA("C:/Biblioguard/Books", NULL);
    CreateDirectoryA("C:/Biblioguard/Users", NULL);
    createFile("C:/Biblioguard/booksCount.txt", "0");
    createFile("C:/Biblioguard/lastBookId.txt", "0");
    createFile("C:/Biblioguard/lastUserId.txt", "0");

} 

