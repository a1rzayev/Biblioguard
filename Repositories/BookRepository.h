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
#define MAX_REPORTS 1000


//usable variables
Book books[MAX_BOOKS];
User users[MAX_USERS];
char reports[MAX_REPORTS][100];


unsigned int booksCount = 0;
unsigned int usersCount = 0;
unsigned int reportsCount = 0;
unsigned int lastBookId = 0;
unsigned int lastUserId = 0;

unsigned int editingBookOrder;

User* currentUser;

const char* BOOK_FORMAT_IN = "(%i, %[^,], %[^,], %[^,], %f, %hu, %hu, %hu)\n";
const char* BOOK_FORMAT_OUT = "(%i, %s, %s, %s, %f, %hu, %hu, %hu)\n";
const char* USER_FORMAT_IN = "(%i, %[^,], %[^,], %[^,], %[^,], %f)\n";
const char* USER_FORMAT_OUT = "(%i, %s, %s, %s, %s, %f)\n";

//declarations of functions
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
// void setUsersCount();
// void setBooksCount();
void getLastBookId();
void getLastUserId();
// void getBooksCount();
// void getUsersCount();
void getBooks();
void getUsers();
void AddBook(char* title, char* author, char* genre, const char* price,
             const char* quantityForSale, const char* quantityForRent, const char* rentalDuration);
void SignUp(char* username, char* name, char* surname, char* password);
bool BuyBook(unsigned int buyerId, unsigned int bookId);
bool RentBook(unsigned int buyerId, unsigned int bookId);
void EditBook(unsigned int bookOrder, char* title, char* author, char* genre, const char* price,
             const char* quantityForSale, const char* quantityForRent, const char* rentalDuration);
void DeleteBook(unsigned int bookOrder);



//initializator
void initBookSystem(){
    getLastBookId();
    getLastUserId();
    //getBooksCount();
    getBooks();
    //getUsers();
}



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

// void setBooksCount(){
//     char booksCountS[10];
//     itoa(booksCount, booksCountS, 10);
//     clearFile("C:/Biblioguard/booksCount.txt");
//     addToFile("C:/Biblioguard/booksCount.txt", booksCountS);
// }

// void setUsersCount(){
//     char usersCountS[10];
//     itoa(usersCount, usersCountS, 10);
//     clearFile("C:/Biblioguard/usersCount.txt");
//     addToFile("C:/Biblioguard/usersCount.txt", usersCountS);
// }

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
    books[booksCount] = newBook;
    
    char lastBookIdStr[5];
    sprintf(lastBookIdStr, "%hu", lastBookId);
    char filename[50] = "C:/Biblioguard/Books/";
    strcat(filename, lastBookIdStr);
    strcat(filename, ".dat");

    FILE* file;
    fopen_s(&file, filename, "w+");
    fprintf_s(file, BOOK_FORMAT_OUT, lastBookId, title, author, genre, newBook.price,
              newBook.quantityForSale, newBook.quantityForRent, newBook.popularity);
    fclose(file);
              

    ++lastBookId;
    ++booksCount;
    setLastBookId();
    //setBooksCount();
}

void SignUp(char* username, char* name, char* surname, char* password){
    User newUser= {lastUserId, "", "", "", "", 0};
    strncpy(newUser.username, username, sizeof(newUser.username));
    strncpy(newUser.name, name, sizeof(newUser.name));
    strncpy(newUser.surname, surname, sizeof(newUser.surname));
    strncpy(newUser.password, password, sizeof(newUser.password));
    users[usersCount] = newUser;
    currentUser = &users[lastUserId];
    
    char lastUserIdStr[5];
    sprintf(lastUserIdStr, "%hu", lastUserId);
    char filename[50] = "C:/Biblioguard/Users/";
    strcat(filename, lastUserIdStr);
    strcat(filename, ".dat");

    FILE* file;
    fopen_s(&file, filename, "w+");
    fprintf_s(file, USER_FORMAT_OUT, lastUserId, username, name, surname, password, 0);
    fclose(file);

    ++lastUserId;
    ++usersCount;
    setLastUserId();
    //setUsersCount();
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
void EditBook(unsigned int bookOrder, char* title, char* author, char* genre, const char* price,
             const char* quantityForSale, const char* quantityForRent, const char* rentalDuration){
    Book editedBook = {books[bookOrder].id, "", "", "", atof(price), atoi(quantityForSale),
                    atoi(quantityForRent), atoi(rentalDuration), 0};
    strncpy(editedBook.title, title, sizeof(editedBook.title));
    strncpy(editedBook.author, author, sizeof(editedBook.author));
    strncpy(editedBook.genre, genre, sizeof(editedBook.genre));
    books[bookOrder] = editedBook;

    char bookOrderStr[5];
    sprintf(bookOrderStr, "%hu", books[bookOrder].id);
    char filename[50] = "C:/Biblioguard/Books/";
    strcat(filename, bookOrderStr);
    strcat(filename, ".dat");

    //clearFile(filename);
    FILE* file;
    fopen_s(&file, filename, "w+");
    fprintf_s(file, BOOK_FORMAT_OUT, books[bookOrder].id, title, author, genre, books[bookOrder].price,
              books[bookOrder].quantityForSale, books[bookOrder].quantityForRent, books[bookOrder].popularity);
    fclose(file);
}

void DeleteBook(unsigned int bookOrder){
    //unsigned int count = countNonNullBooks();

    char bookOrderStr[5];
    sprintf(bookOrderStr, "%hu", books[bookOrder].id);
    char filename[50] = "C:/Biblioguard/Books/";
    strcat(filename, bookOrderStr);
    strcat(filename, ".dat");
    
    for (int i = bookOrder; i < booksCount - 1; ++i){
        books[i] = books[i + 1];
    }
    --booksCount;
    //setBooksCount();

    // Attempt to delete the file
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        // Print error message with more details
        if (errno == ENOENT) {
            printf("Error: File '%s' does not exist.\n", filename);
        } else if (errno == EACCES) {
            printf("Error: Permission denied to delete file '%s'.\n", filename);
        } else {
            printf("Error deleting file '%s': %s\n", filename, strerror(errno));
        }
    }
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

// void getBooksCount(){
//     char booksCountC[5];
//     readTextFromFile("C:/Biblioguard/booksCount.txt", booksCountC, 5);
//     booksCount = atoi(booksCountC);
// }

// void getUsersCount(){
//     char usersCountC[5];
//     readTextFromFile("C:/Biblioguard/usersCount.txt", usersCountC, 5);
//     usersCount = atoi(usersCountC);
// }

void getBooks(){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("C:\\Biblioguard\\Books")) != NULL)
    {
        //int i = 0;
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
                books[booksCount] = gottenbook;
                ++booksCount;
                fclose(file);
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




void getUsers(){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("C:\\Biblioguard\\Users")) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type == DT_REG)
            {
                printf("%s\n", ent->d_name);
                char filePath[50];
                snprintf(filePath, sizeof(filePath), "C:\\Biblioguard\\Users\\%s", ent->d_name);
                char buffer[200];
                User gottenuser;
                FILE *file;
                fopen_s(&file, filePath, "r");
                fgets(buffer, 200, file);
                while(!feof(file)){
                    sscanf(buffer, USER_FORMAT_IN, &gottenuser.id, &gottenuser.username, &gottenuser.name, &gottenuser.surname,
                           &gottenuser.password, &gottenuser.totalAmountPaid); //, &gottenuser.purchasedBooks, &gottenuser.rentedBooks);
                    fgets(buffer, 200, file);
                    //FILE *file = fopen(filePath, "rb");
                    // if (file != NULL)
                    // {
                    //     // Read the entire structure from the file
                    //     // fread(&gottenuser, sizeof(User), 1, file);
                    //     // fclose(file);
                    //     sscanf(buffer, USER_FORMAT_IN, &gottenuser.id, &gottenuser.username, &gottenuser.name, &gottenuser.surname,
                    //            &gottenuser.password, &gottenuser.totalAmountPaid);//, &gottenuser.purchasedBooks, &gottenuser.rentedBooks);
                    //     fgets(buffer, 200, file);
                    // }
                    // else
                    // {
                    //     printf("Error opening file for reading.\n");
                    // }
                } 
                users[usersCount] = gottenuser;
                ++usersCount;
                fclose(file);
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