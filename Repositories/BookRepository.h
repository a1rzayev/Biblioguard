#include "../Models/User.h"
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "FileRepository.h"
#include <stdbool.h>
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
bool isCorrectLogin(char* username, char* password);
void setLastBookId();
void setLastUserId();
void setBooksCount();
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

void getBooks(){
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
            }
        }
        closedir(dir);
    }
    else
    {
        perror("");
        return;
    }
}

//initializator

void initBookSystem(){
    getLastBookId();
    getLastUserId();
    getBooksCount();
    getBooks();
}