#include "../Models/User.h"
#include <string.h>
#include <ctype.h>

#pragma once

#define MAX_BOOKS 100
#define MAX_USERS 100

Book books[MAX_BOOKS];
User users[MAX_USERS];

booksCount;
usersCount;

unsigned int lastBookId;
unsigned int lastUserId;

User* currentUser;

void initProject(){
    lastBookId = 0;
    lastUserId = 0;
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
// bool isAvailableTitle(char* title){
//     for (int i = 0; i < MAX_BOOKS; ++i) 
//         if(books[i].title == title) return false;
//     return true;
// }
char isCorrectBookInfo(char* title, char* author, char* genre, char* price,  char* qSale, char* qRent, char* rDuration){
    if(!strcmp(title, "") || !strcmp(author, "") || !strcmp(genre, "") || !strcmp(price, "") ||
       !strcmp(qSale, "") || !strcmp(qRent, "") || !strcmp(rDuration, "")) return 1;
    //else if(!isAvailableTitle(title)) return 2;
    else if(!isConvertibleToFloat(price) || !isConvertibleToUSInt(qSale) ||
            !isConvertibleToUSInt(qRent) || !isConvertibleToUSInt(rDuration)) return 3;
    return 0;
}


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


// adders
void AddBook(char* title, char* author, char* genre, float price, unsigned short int quantityForSale,
             unsigned short int quantityForRent, unsigned short int rentalDuration){
    Book newBook = {lastBookId, *title, *author, *genre, price, quantityForSale, quantityForRent, rentalDuration, 0};
    books[lastBookId] = newBook;
    lastBookId = lastBookId + 1;
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
                if(users[buyerId].purchasedBooks[j] != NULL){
                    users[buyerId].purchasedBooks[j] = &books[i];
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
                if(users[buyerId].purchasedBooks[j] != NULL) {
                    users[buyerId].purchasedBooks[j] = &books[i];
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