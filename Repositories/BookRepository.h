#include "../Models/User.h"
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "FileRepository.h"
#include <stdbool.h>
//#include <cjson/cJSON.h>
#include <sqlite3.h>
#include "../Libraries/dirent.h"
#pragma once

#define MAX_BOOKS 100
#define MAX_USERS 100

Book books[MAX_BOOKS];
User users[MAX_USERS];

unsigned int booksCount = 0;
unsigned int usersCount = 0;

unsigned int lastBookId = 0;
unsigned int lastUserId = 0;

User* currentUser;


const char* BOOK_FORMAT_IN = "(%i, %[^,], %[^,], %[^,], %f, %hu, %hu, %hu)\n";
const char* BOOK_FORMAT_OUT = "(%i, %s, %s, %s, %f, %hu, %hu, %hu)\n";

unsigned int countNonNullBooks();
bool isSalable(unsigned int bookId);
bool isRentable(unsigned int bookId);
char isCorrectSignupInfo(char* username, const char* name, const char* surname, const char* password);
bool isConvertibleToFloat(char* str);
bool isConvertibleToUSInt(char* str);
bool isConvertibleToUInt(char* str);
bool isEmptyBook(Book book);
char isCorrectBookInfo(char* title, char* author, char* genre, char* price,  char* qSale, char* qRent, char* rDuration);
// float convertToFloat(char str);
// float convertToUSInt(char str);
// float convertToUInt(char str);
bool isCorrectLogin(char* username, char* password);
void setLastBookId();
void setLastUserId();
void setBooksCount();
// Book *read_data(char *filename, unsigned int *total);
// bool write_data(char *filename, Book *data, unsigned int total);
void getLastBookId();
void getLastUserId();
void getBooksCount();
void AddBook(char* title, char* author, char* genre, const char* price,
             const char* quantityForSale, const char* quantityForRent, const char* rentalDuration);
void SignUp(char* username, char* name, char* surname, char* password);
bool BuyBook(unsigned int buyerId, unsigned int bookId);
bool RentBook(unsigned int buyerId, unsigned int bookId);
void EditBook(unsigned int bookOrder, char* title, char* author, char* genre, float price, unsigned short int quantityForSale,
    unsigned short int quantityForRent, unsigned short int rentalDuration);
void DeleteBook(unsigned int bookOrder);

//void deserializeJsonToBooks(char* jsonStr, Book* books, unsigned int *numBooks);
//char* serializeBooksToJson(Book books[], unsigned int numBooks);

// checkers

//books
bool isSalable(unsigned int bookId){
    for (int i = 0; i < MAX_BOOKS; ++i) {
        if(books[i].id == bookId) {
            if(books[i].quantityForSale > 0) return true;
            return false;
        }
    }
}

bool isRentable(unsigned int bookId){
    for (int i = 0; i < MAX_BOOKS; ++i) {
        if(books[i].id == bookId) {
            if(books[i].quantityForRent > 0) return true;
            return false;
        }
    }
}

unsigned int countNonNullBooks() {
    int count = 0;
    for (int i = 0; i < MAX_BOOKS; ++i) {
        if (books[i].title != "") ++count;
    }
    return count;
}

bool isEmptyBook(Book book) {
    return (book.title == NULL);
}

//signup
bool isAvailableUsername(char* username){
    for (int i = 0; i < MAX_USERS; ++i) 
        if(users[i].username == username) return false;
    return true;
}

char isCorrectSignupInfo(char* username, const char* name, const char* surname, const char* password){
    if(!strcmp(username, "") || !strcmp(name, "") || !strcmp(surname, "") || !strcmp(password, "")) return 1;
    else if(!isAvailableUsername(username) || !strcmp(username, "admin")) return 2;
    return 0;
}

//addbook & edit
bool isConvertibleToFloat(char* str){
    char *endptr;
    float num = strtod(str, &endptr);
    if (*endptr == '\0') return true;
    return false;
}

bool isConvertibleToUSInt(char* str){
    char *endptr;
    float num = strtod(str, &endptr);
    if (*endptr == '\0' && fmod(num, 1) == 0 && num >= 0 && num <= USHRT_MAX) {
        unsigned short int usnum = (unsigned short int) num;
        return true;
    } 
    return false;
}

bool isConvertibleToUInt(char* str){
    char *endptr;
    float num = strtod(str, &endptr);
    if (*endptr == '\0' && fmod(num, 1) == 0 && num >= 0 && num <= UINT_MAX) {
        unsigned int unum = (unsigned int) num;
        return true;
    } 
    return false;
}

char isCorrectBookInfo(char* title, char* author, char* genre, char* price,  char* qSale, char* qRent, char* rDuration){
    if(!strcmp(title, "") || !strcmp(author, "") || !strcmp(genre, "") || !strcmp(price, "") ||
       !strcmp(qSale, "") || !strcmp(qRent, "") || !strcmp(rDuration, "")) return 1;
    //else if(!isAvailableTitle(title)) return 2;
    else if(!isConvertibleToFloat(price) || !isConvertibleToUSInt(qSale) ||
            !isConvertibleToUSInt(qRent) || !isConvertibleToUSInt(rDuration)) return 3;
    return 0;
}

//converters
// float convertToFloat(char* str){
//     char *endptr;
//     return strtod(str, &endptr);
// }
// float convertToUSINT(char str){
//     char *endptr;
//     float num = strtod(str, &endptr);
//     return (unsigned short int) num;
// }
// float convertToUINT(char str){
//     char *endptr;
//     float num = strtod(str, &endptr);
//     return (unsigned int) num;
// }



//login
bool isCorrectLogin(char* username, char* password){
    if(username == "admin") return false;
    for (int i = 0; i < MAX_USERS; ++i) {
        if(users[i].username == username && users[i].password == password){
            return true;
            currentUser = &users[i];
        }
    }
    return false;
}


// setters
void setLastBookId(){
    char lastIdS[10];
    itoa(lastBookId, lastIdS, 10);
    clearFile("C:/Biblioguard/lastBookId.txt");
    addToFile("C:/Biblioguard/lastBookId.txt", lastIdS);
}

void setBooksCount(){
    char booksCountS[10];
    itoa(booksCount, booksCountS, 10);
    clearFile("C:/Biblioguard/booksCount.txt");
    addToFile("C:/Biblioguard/booksCount.txt", booksCountS);
}

void setLastUserId(){
    char lastIdS[10];
    itoa(lastUserId, lastIdS, 10);
    clearFile("C:/Biblioguard/lastUserId.txt");
    addToFile("C:/Biblioguard/lastUserId.txt", lastIdS);
}

// adders
// void AddBook(char* title, char* author, char* genre, const char* price,
//              const char* quantityForSale, const char* quantityForRent, const char* rentalDuration){
//     Book newBook = {lastBookId, title, author, genre, atof(price), atoi(quantityForSale),
//                     atoi(quantityForRent), atoi(rentalDuration), 0};
//                     //strcpy(message, ptr);
//     books[lastBookId] = newBook;
//     char lastBookIdStr[5];
//     sprintf(lastBookIdStr, "%hu", lastBookId);
//     char filename[50] = "C:/Biblioguard/Books/";
//     strcat(filename, lastBookIdStr);
//     strcat(filename, ".dat");
//     //createFile(filename);
//     //editBookFile(lastBookIdStr, title, author, genre, price, quantityForSale, quantityForRent, rentalDuration, "0");
//     //editBookFileF(&newBook, filename);
//     // FILE* outfile = fopen(filename, "wb");
//     // fwrite(&newBook, sizeof(Book), 1, outfile);
//     // fclose(outfile); 
//     // lastBookId = lastBookId + 1;
//     // setLastBookId();
//     // FILE *file = fopen("C:/Biblioguard/books.bin", "wb");
//     // if (file == NULL) {
//     //     printf("Error opening file for writing.\n");
//     //     return 1;
//     // }
//     // fwrite(&books, sizeof(Book), booksCount, file);
//     // fclose(file);
//     // printf("Data written to file successfully.\n");
//     // char *booksJson = serializeBooksToJson(books, booksCount);
//     // clearFile("C:/Biblioguard/books.json");
//     // addToFile("C:/Biblioguard/books.json", booksJson);
//     ++lastBookId;
//     ++booksCount;
//     setLastBookId();
//     setBooksCount();
//     FILE* file;
//     fopen_s(&file, filename, "w+");
//     fprintf_s(file, BOOK_FORMAT_OUT, newBook.id, newBook.title,
//                                          newBook.title, newBook.title,
//                                          newBook.price, newBook.quantityForSale,
//                                          newBook.quantityForRent, newBook.popularity);
//     // write_data("C:/Biblioguard/books.bin", books, booksCount);
// }

void AddBook(char* title, char* author, char* genre, const char* price,
             const char* quantityForSale, const char* quantityForRent, const char* rentalDuration){
    Book newBook = {lastBookId, "", "", "", atof(price), atoi(quantityForSale),
                    atoi(quantityForRent), atoi(rentalDuration), 0};
    strncpy(newBook.title, title, sizeof(newBook.title));
    strncpy(newBook.author, author, sizeof(newBook.author));
    strncpy(newBook.genre, genre, sizeof(newBook.genre));
    books[lastBookId] = newBook;
    
    char lastBookIdStr[5];
    sprintf(lastBookIdStr, "%hu", lastBookId);
    char filename[50] = "C:/Biblioguard/Books/";
    strcat(filename, lastBookIdStr);
    strcat(filename, ".dat");

    FILE* file;
    fopen_s(&file, filename, "w+");
    fprintf_s(file, BOOK_FORMAT_OUT, lastBookId, title, author, genre, newBook.price,
              newBook.quantityForSale, newBook.quantityForRent, newBook.popularity);
              

    ++lastBookId;
    ++booksCount;
    setLastBookId();
    setBooksCount();
}

void SignUp(char* username, char* name, char* surname, char* password){
    User newUser= {lastUserId, *username, *name, *surname, *password, 0};
    users[lastUserId] = newUser;
    currentUser = &users[lastUserId];
    lastUserId = lastUserId + 1;
} 


// functions for user
bool BuyBook(unsigned int buyerId, unsigned int bookId){
    for (int i = 0; i < MAX_BOOKS; ++i) {
        if(books[i].id == bookId) {
            for(int j = 0; j < MAX_BOOKS; ++j) {
                if(users[buyerId].purchasedBooks[j] != -1){
                    users[buyerId].purchasedBooks[j] = books[i].id;
                    --books[j].quantityForSale;
                    return true;
                }
            }
        }
    }
    return false;
}

bool RentBook(unsigned int buyerId, unsigned int bookId){
    for (int i = 0; i < MAX_BOOKS; ++i) {
        if(books[i].id == bookId) {
            for(int j = 0; j < MAX_BOOKS; ++j) {
                if(users[buyerId].purchasedBooks[j] != -1) {
                    users[buyerId].purchasedBooks[j] = books[i].id;
                    --books[j].quantityForRent;
                    return true;
                }
            }
        }
    }
    return false;
}


// editors
void EditBook(unsigned int bookOrder, char* title, char* author, char* genre, float price, unsigned short int quantityForSale,
    unsigned short int quantityForRent, unsigned short int rentalDuration){
    strcpy(books[bookOrder].title, title);
    strcpy(books[bookOrder].author, author);
    strcpy(books[bookOrder].genre, genre);
    books[bookOrder].price = price;
    books[bookOrder].quantityForSale = quantityForSale;
    books[bookOrder].quantityForRent = quantityForRent;
    books[bookOrder].rentalDuration = rentalDuration;
}

void DeleteBook(unsigned int bookOrder){
    unsigned int count = countNonNullBooks();
    for (int i = bookOrder; i < count - 1; ++i) books[i] = books[i + 1];
}


// getters
void getLastBookId(){
    char lastIdC[5];
    readTextFromFile("C:/Biblioguard/lastBookId.txt", lastIdC, 5);
    lastBookId = atoi(lastIdC);
    
}

void getLastUserId(){
    char lastIdC[5];
    readTextFromFile("C:/Biblioguard/lastUserId.txt", lastIdC, 5);
    lastUserId = atoi(lastIdC);
}

void getBooksCount(){
    char booksCountC[5];
    readTextFromFile("C:/Biblioguard/booksCount.txt", booksCountC, 5);
    booksCount = atoi(booksCountC);
}

// void printFileContent(const char *filename) {
//     FILE *file = fopen(filename, "r");
//     if (file != NULL) {
//         char line[50];
//         printf("Contents of %s:\n", filename);
//         while (fgets(line, sizeof(line), file) != NULL) {
//             printf("%s", line);
//         }
//         fclose(file);
//     }
//      else {
//         printf("Unable to open file: %s\n", filename);
//     }
//}

// void getBookContent(const char *filename) {
//     FILE *file = fopen(filename, "r");
//     if (file != NULL) {
//         char line[9][50];
//         int i = 0;
//         for(i = 0; i < 9; ++i)
//             fgets(line[i], sizeof(line), file);
//         for (i = 0; i < MAX_BOOKS; ++i) {
//             if (isEmptyBook(books[i])) {
//                 books[i].id = atoi(line[0]);
//                 books[i].title = line[1];
//                 books[i].author = line[2];
//                 books[i].genre = line[3];
//                 books[i].price = atof(line[4]);
//                 books[i].quantityForSale = atoi(line[5]);
//                 books[i].quantityForRent = atoi(line[6]);
//                 books[i].rentalDuration = atoi(line[7]);
//                 books[i].popularity = atoi(line[8]);
//                 break;
//             }
//         }        
//         fclose(file);
//     }
//      else {
//         printf("Unable to open file: %s\n", filename);
//     }
// }


void getBooks(){
    // WIN32_FIND_DATA findFileData;
    // HANDLE hFind;
    // const char *folderPath = "C:/Biblioguard/Books/*";
    // int i = 0;
    // hFind = FindFirstFile(folderPath, &findFileData);
    // if (hFind != INVALID_HANDLE_VALUE) {
    //      while (FindNextFile(hFind, &findFileData) != 0){
    //         if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) {
    //             char filePath[50];
    //             snprintf(filePath, sizeof(filePath), "C:/Biblioguard/Books/%s", findFileData.cFileName);
    //             FILE *file;
    //             Book gottenbook;
    //             fopen_s(&file, filePath, "w+");
    //             fscanf_s(file, BOOK_FORMAT_IN, &gottenbook.id, &gottenbook.title, gottenbook.author, gottenbook.genre,
    //                     gottenbook.price, &gottenbook.quantityForSale, &gottenbook.quantityForRent, &gottenbook.popularity);
    //             books[i] = gottenbook;
    //             ++i;
    //             // books[i] = readBookFileF(filePath);
    //             // printf("%s", books[i].title);
    //             // ++i;
    //         }
    //     }
    //     FindClose(hFind);
    // }
    // else printf("Unable to open directory: %s\n", folderPath);
    // WIN32_FIND_DATA findFileData;
    // HANDLE hFind;
        // // Specify the directory path
    // LPCWSTR directoryPath = L"C:\\Biblioguard\\Books\\"; // Replace this with your directory path
    // // Concatenate the directory path with the search pattern
    // wchar_t searchPath[MAX_PATH];
    // wcscpy_s(searchPath, MAX_PATH, directoryPath);
    // wcscat_s(searchPath, MAX_PATH, L"*");
    // // Find the first file in the directory
    // hFind = FindFirstFile(searchPath, &findFileData);
    // if (hFind == INVALID_HANDLE_VALUE) {
    //     printf("No files found in the directory.\n");
    //     return;
    // }
    // int i = 0;
    // // Iterate through all the files in the directory
    //  while (FindNextFile(hFind, &findFileData) != 0){
    //     if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
    //         printf("File: %ls\n", findFileData.cFileName);
    //         char filePath[50];
    //         snprintf(filePath, sizeof(filePath), "C:\\Biblioguard\\Books\\%s", findFileData.cFileName);
    //         FILE *file;
    //         Book gottenbook;
    //         fopen_s(&file, filePath, "w+");
    //         fscanf_s(file, BOOK_FORMAT_IN, &gottenbook.id, &gottenbook.title, gottenbook.author, gottenbook.genre,
    //                  gottenbook.price, &gottenbook.quantityForSale, &gottenbook.quantityForRent, &gottenbook.popularity);
    //         books[i] = gottenbook;
    //         ++i;
    //     }
    // }
    // // Close the search handle
    // FindClose(hFind);

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("C:\\Biblioguard\\Books")) != NULL)
    {
        int i = 0;
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type == DT_REG)
            {
                printf("%s\n", ent->d_name);
                char filePath[50];
                snprintf(filePath, sizeof(filePath), "C:\\Biblioguard\\Books\\%s", ent->d_name);
                char buffer[200];
                Book gottenbook;
                FILE *file;
                fopen_s(&file, filePath, "r");
                fgets(buffer, 200, file);
                while(!feof(file)){
                    sscanf(buffer, BOOK_FORMAT_IN, &gottenbook.id, &gottenbook.title, &gottenbook.author, &gottenbook.genre,
                         &gottenbook.price, &gottenbook.quantityForSale, &gottenbook.quantityForRent, &gottenbook.popularity);
                    fgets(buffer, 200, file);
                } 
                books[i] = gottenbook;
                ++i;
                // fscanf_s(file, BOOK_FORMAT_IN, &gottenbook.id, &gottenbook.title, &gottenbook.author, &gottenbook.genre,
                //          &gottenbook.price, &gottenbook.quantityForSale, &gottenbook.quantityForRent, &gottenbook.popularity);
                // books[i] = gottenbook;
                // ++i;
            }
        }
        closedir(dir);
    }
    else
    {
        /* could not open directory */
        perror("");
        return;
    }

}
    // Open the file for reading in binary mode
    // FILE *file = fopen("C:/Biblioguard/books.bin", "rb");
    // if (file == NULL) {
    //     printf("Error opening file for reading.\n");
    //     return 1;
    // }
    // fread(&books, sizeof(Book), booksCount, file);
    // fclose(file);
    // printf("Data read from file:\n");
        // char *booksJson;
    // readFile("C:/Biblioguard/books.json", booksJson);
    // deserializeJsonToBooks(booksJson, books, &booksCount);
    // for (int i = 0; i < booksCount; ++i)
    //     printf("Id %d: Title: %s, Genre: %d\n", books[i].id, books[i].title, books[i].genre);

    // Book *gottenbooks;
    // gottenbooks = read_data("C:/Biblioguard/books.bin", &booksCount);

//initializator

void initBookSystem(){
    getLastBookId();
    getLastUserId();
    getBooksCount();
    getBooks();
}

// void deserializeJsonToBooks(char* jsonStr, Book* books, unsigned int *numBooks) {
//     cJSON *root = cJSON_Parse(jsonStr); // Parse JSON string
//     *numBooks = (unsigned int)cJSON_GetArraySize(root); // Get the number of books
//     for (int i = 0; i < *numBooks; i++) {
//         cJSON *bookObj = cJSON_GetArrayItem(root, i); // Get the JSON object for each book
//         books[i].id = cJSON_GetObjectItem(bookObj, "id")->valueint;
//         strcpy(books[i].title, cJSON_GetObjectItem(bookObj, "title")->valuestring);
//         strcpy(books[i].author, cJSON_GetObjectItem(bookObj, "author")->valuestring);
//         strcpy(books[i].genre, cJSON_GetObjectItem(bookObj, "genre")->valuestring);
//         books[i].price = cJSON_GetObjectItem(bookObj, "price")->valuedouble;
//         books[i].quantityForSale = cJSON_GetObjectItem(bookObj, "quantityForSale")->valueint;
//         books[i].quantityForRent = cJSON_GetObjectItem(bookObj, "quantityForRent")->valueint;
//         books[i].rentalDuration = cJSON_GetObjectItem(bookObj, "rentalDuration")->valueint;
//         books[i].popularity = cJSON_GetObjectItem(bookObj, "popularity")->valueint;
//     }
//     cJSON_Delete(root); // Free cJSON objects
// }
// char* serializeBooksToJson(Book books[], unsigned int numBooks) {
//     cJSON *root = cJSON_CreateArray(); // Create a JSON array
//     for (int i = 0; i < numBooks; i++) {
//         cJSON *bookObj = cJSON_CreateObject(); // Create a JSON object for each book
//         cJSON_AddNumberToObject(bookObj, "id", books[i].id);
//         cJSON_AddStringToObject(bookObj, "title", books[i].title);
//         cJSON_AddStringToObject(bookObj, "author", books[i].author);
//         cJSON_AddStringToObject(bookObj, "genre", books[i].genre);
//         cJSON_AddNumberToObject(bookObj, "price", books[i].price);
//         cJSON_AddNumberToObject(bookObj, "quantityForSale", books[i].quantityForSale);
//         cJSON_AddNumberToObject(bookObj, "quantityForRent", books[i].quantityForRent);
//         cJSON_AddNumberToObject(bookObj, "rentalDuration", books[i].rentalDuration);
//         cJSON_AddNumberToObject(bookObj, "popularity", books[i].popularity);
//         cJSON_AddItemToArray(root, bookObj); // Add book object to the array
//     }
//     char *jsonStr = cJSON_Print(root); // Convert cJSON object to JSON string
//     cJSON_Delete(root); // Free cJSON objects
//     return jsonStr;
// }

bool write_data(char *filename, Book *data, unsigned int total) {
  FILE *file;
  file = fopen(filename, "wb");
  if (file == NULL) return false;
  if (fwrite(&total, sizeof(int), 1, file) != 1)
    return false;
  if (fwrite(data, sizeof(Book), total, file) != total)
    return false;
  if (fclose(file) == EOF) return false; 
  return true;
}

Book *read_data(char *filename, unsigned int *total) {
    FILE *file;
    file = fopen(filename, "rb");
    if (file == NULL)
        return NULL;
    if (fread(total, sizeof(unsigned int), 1, file) != 1)
        return NULL;
    Book *data = malloc(sizeof(Book) * *total);
    if (fread(data, sizeof(Book), *total, file) != *total) {
        free(data);
        return NULL;
    }
    if (fclose(file) == EOF) {
        free(data);
        return NULL;
    }
    return data;
}