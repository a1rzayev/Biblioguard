#include "Models/User.h"

Book books[1000];
User users[1000];

int book_id;
int user_id;

User currentUser;

void initProject(){
    book_id = 0;
    user_id = 0;
}

void AddBook(char title, char author, char genre, int quantity){
    Book new_book = {book_id, title, author, genre, quantity};
    books[book_id] = new_book;
    book_id = book_id + 1;
} 

void AddUser(char nickname, char name, char surname, char password, bool is_admin){
    User new_user= {user_id, nickname, name, surname, password, is_admin};
    users[user_id] = new_user;
    user_id = user_id + 1;
} 