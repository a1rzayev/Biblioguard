#include "Models/User.h"

#pragma once

#define MAX_BOOKS 100
#define MAX_USERS 100

Book books[MAX_BOOKS];
User users[MAX_USERS];

unsigned int lastBookId;
unsigned int lastUserId;

User currentUser;

void initProject(){
    lastBookId = 0;
    lastUserId = 0;
}


// checkers(boolean types)
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



// adders
void AddBook(char title, char author, char genre, float price, unsigned short int quantityForSale,
             unsigned short int quantityForRent, unsigned short int rentalDuration){
    Book newBook = {lastBookId, title, author, genre, price, quantityForSale, quantityForRent, rentalDuration, 0};
    books[lastBookId] = newBook;
    lastBookId = lastBookId + 1;
}
void AddUser(char nickname, char name, char surname, char password, float totalAmountPaid){
    User newUser= {lastUserId, nickname, name, surname, password, totalAmountPaid};
    users[lastUserId] = newUser;
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
void EditBook(unsigned int bookId, char* title, char author, char genre, float price, unsigned short int quantityForSale,
             unsigned short int quantityForRent, unsigned short int rentalDuration){
    for (int i = 0; i < MAX_BOOKS; ++i) {
        if(books[i].id == bookId) {
            strcpy(books[bookId].title, title);
            strcpy(books[bookId].author, author);
            strcpy(books[bookId].genre, genre);
            books[bookId].price = price;
            books[bookId].quantityForSale = quantityForSale;
            books[bookId].quantityForRent = quantityForRent;
            books[bookId].rentalDuration = rentalDuration;
        }
    }
}