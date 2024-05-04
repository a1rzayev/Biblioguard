#include <windows.h>
#include <stdio.h>

// void createDirectory(const char* dirDestination) {
//     if (CreateDirectory(dirDestination, NULL) != 0)
//         printf("Directory '%s' created successfully.\n", dirDestination);
// }
void createFile(const char* filename){
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        file = fopen(filename, "w");
        if (file != NULL) fclose(file);
    } 
    else fclose(file);
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

void editBookFile(char* bookId, char* title, char* author, char* genre,
                  char* price,  char* qSale, char* qRent, char* rDuration, char* population)
{
    char filename[50] = "C:/Biblioguard/Books/";
    strcat(filename, bookId);
    strcat(filename, ".txt");
    clearFile(filename);
    addToFile(filename, bookId);
    addToFile(filename, title);
    addToFile(filename, author);
    addToFile(filename, genre);
    addToFile(filename, price);
    addToFile(filename, qSale);
    addToFile(filename, qRent);
    addToFile(filename, rDuration);                 
}

void editFile(const char* filename){
    clearFile(filename);
}

void readFile(const char *filename, char* container) {
    FILE *file = fopen(filename, "r"); 
    if (file != NULL) {
        fgets(container, sizeof(container), file);
        fclose(file);
    } 
    else {
        printf("Error opening file: %s\n", filename);
    }
}

// void readEachLine(const char* filename, char* buffer){
//     FILE *file = fopen(filename, "r");

//     if (file != NULL) {
//         char buffer[256];
//         while (fgets(buffer, sizeof(buffer), file) != NULL) {
//             printf("%s", buffer);
//         }
//         fclose(file);
//     } else {
//         printf("Ошибка открытия файла!\n");
//     }

// }

void initFileSystem(){
    CreateDirectoryA("C:/Biblioguard", NULL);
    CreateDirectoryA("C:/Biblioguard/Books", NULL);
    CreateDirectoryA("C:/Biblioguard/Users", NULL);
    createFile("C:/Biblioguard/lastBookId.txt");
    createFile("C:/Biblioguard/lastUserId.txt");


    //editBookFile( "2", "hello", "pilim", "kishi", "2324.3", "3", "32", "23");
} 

