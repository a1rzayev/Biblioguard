#include "../Models/User.h"
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "FileRepository.h"
#include <stdbool.h>

#pragma once

#define MAX_BOOKS 100
#define MAX_USERS 100

Book books[MAX_BOOKS];
User users[MAX_USERS];

unsigned int booksCount;
unsigned int usersCount;

unsigned int lastBookId;
unsigned int lastUserId;

User* currentUser;

unsigned int countNonNullBooks();
bool isSalable(unsigned int bookId);
bool isRentable(unsigned int bookId);
char isCorrectSignupInfo(char* username, char* name, char* surname, char* password);
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
void getLastBookId();
void getLastUserId();
void AddBook(char* title, char* author, char* genre, char* price, char* quantityForSale,
             char* quantityForRent, char* rentalDuration);
void SignUp(char* username, char* name, char* surname, char* password);
bool BuyBook(unsigned int buyerId, unsigned int bookId);
bool RentBook(unsigned int buyerId, unsigned int bookId);
void EditBook(unsigned int bookOrder, char* title, char* author, char* genre, float price, unsigned short int quantityForSale,
    unsigned short int quantityForRent, unsigned short int rentalDuration);
void DeleteBook(unsigned int bookOrder);


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

char isCorrectSignupInfo(char* username, char* name, char* surname, char* password){
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

void setLastUserId(){
    char lastIdS[10];
    itoa(lastUserId, lastIdS, 10);
    clearFile("C:/Biblioguard/lastUserId.txt");
    addToFile("C:/Biblioguard/lastUserId.txt", lastIdS);
}

// adders
void AddBook(char* title, char* author, char* genre, char* price, char* quantityForSale,
             char* quantityForRent, char* rentalDuration){
    Book newBook = {lastBookId, title, author, genre, atof(price), atoi(quantityForSale),
                    atoi(quantityForRent), atoi(rentalDuration), 0};
    books[lastBookId] = newBook;
    
    char lastBookIdStr[5];
    sprintf(lastBookIdStr, "%hu", lastBookId);

    char filename[50] = "C:/Biblioguard/Books/";
    strcat(filename, lastBookIdStr);
    strcat(filename, ".bin");
    //createFile(filename);
    
    //editBookFile(lastBookIdStr, title, author, genre, price, quantityForSale, quantityForRent, rentalDuration, "0");
    //editBookFileF(&newBook, filename);
    FILE* outfile = fopen(filename, "wb");
    fwrite(&newBook, sizeof(Book), 1, outfile);
    fclose(outfile); 
    lastBookId = lastBookId + 1;
    setLastBookId();
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
    readFile("C:/Biblioguard/lastBookId.txt", lastIdC);
    lastBookId = atoi(lastIdC);
    
}

void getLastUserId(){
    char lastIdC[5];
    readFile("C:/Biblioguard/lastUserId.txt", lastIdC);
    lastUserId = atoi(lastIdC);
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
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    const char *folderPath = "C:/Biblioguard/Books/*";
    int i = 0;

    hFind = FindFirstFile(folderPath, &findFileData);
    if (hFind != INVALID_HANDLE_VALUE) {
         while (FindNextFile(hFind, &findFileData) != 0){
            if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) {
                char filePath[50];
                snprintf(filePath, sizeof(filePath), "C:/Biblioguard/Books/%s", findFileData.cFileName);
                FILE *file = fopen(filePath, "rb");
                if (file != NULL) {
                    Book book;
                    //rewind(file);
                    fread(&book, sizeof(Book), 1, file);
                    books[i] = book;
                    fclose(file);
                    //printf("%s", books[i].title);
                    ++i;
                }
                else {
                    printf("Unable to open file: %s\n", filePath);
                }
                // books[i] = readBookFileF(filePath);
                // printf("%s", books[i].title);
                // ++i;
            }
        }
        FindClose(hFind);
    }
    else {
        printf("Unable to open directory: %s\n", folderPath);
    }
}

//initializator

void initBookSystem(){
    getLastBookId();
    getLastUserId();
    getBooks();
}