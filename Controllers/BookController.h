#include "../Models/User.h"
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "FileController.h"
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

User* currentUser;

unsigned int editingBookOrder;

const char* BOOK_FORMAT_IN = "(%i, %[^,], %[^,], %[^,], %f, %hu, %hu, %hu, %hu)\n";
const char* BOOK_FORMAT_OUT = "(%i, %s, %s, %s, %f, %hu, %hu, %hu, %hu)\n";
const char* USER_FORMAT_IN = "(%i, %[^,], %[^,], %[^,], %[^,], %f, %i, %i)\n";
const char* USER_FORMAT_OUT = "(%i, %s, %s, %s, %s, %f, %i, %i)\n";

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
void getLastBookId();
void getLastUserId();
void getBooks();
void getUsers();
void getReports();
void AddBook(char* title, char* author, char* genre, const char* price,
             const char* quantityForSale, const char* quantityForRent, const char* rentalDuration);
void SignUp(char* username, char* name, char* surname, char* password);
bool BuyBook(unsigned int buyerId, unsigned int bookId);
bool RentBook(unsigned int buyerId, unsigned int bookId);
void EditBook(unsigned int bookOrder, char* title, char* author, char* genre, const char* price,
             const char* quantityForSale, const char* quantityForRent, const char* rentalDuration);
void DeleteBook(unsigned int bookOrder);
void SortBooksByPopularityD();
void SortBooksByPriceD();
void WriteBook(Book newBook);
void WriteUser(User newUser);

void SortBooksByPopularityD() { //selection sort for sorting books by popularity field
    int i, j, maxIndex;
    Book temp;
    if (booksCount <= 1) return;
    for (i = 0; i < booksCount - 1; ++i) {
        maxIndex = i;
        for (j = i + 1; j < booksCount; ++j) {
            if (books[j].popularity > books[maxIndex].popularity) {
                maxIndex = j;
            }
        }
        // Swap the found maximum element with the first element
        temp = books[maxIndex];
        books[maxIndex] = books[i];
        books[i] = temp;
    }
}

void SortBooksByPriceD() { //selection sort for sorting books by price field
    int i, j, maxIndex;
    Book temp;
    if (booksCount <= 1) return;
    for (i = 0; i < booksCount - 1; ++i) {
        maxIndex = i;
        for (j = i + 1; j < booksCount; ++j) {
            if (books[j].price > books[maxIndex].price) {
                maxIndex = j;
            }
        }
        // Swap the found maximum element with the first element
        temp = books[maxIndex];
        books[maxIndex] = books[i];
        books[i] = temp;
    }
}


//initializator
void initBookSystem(){
    getLastBookId();
    getLastUserId();
    getBooks();
    getUsers();
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
    for (int i = 0; i < usersCount; ++i) 
        if(!strcmp(users[i].username, username)) return false;
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


//login
bool isCorrectLogin(char* username, char* password){
    if(username == "admin") return false;
    for (int i = 0; i < usersCount; ++i) {
        printf("%s %s", username, password);
        if(!strcmp(users[i].username, username) && !strcmp(users[i].password, password)){
            currentUser = &users[i];
            return true;
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
              newBook.quantityForSale, newBook.quantityForRent, newBook.rentalDuration, newBook.popularity);
    fclose(file);
              

    ++lastBookId;
    ++booksCount;
    setLastBookId();
    //setBooksCount();

    char infoText[256] = "Book(id = ";
    strcat(infoText, lastBookIdStr);
    strcat(infoText, ") was added");
    strcat(infoText, "\n");
    // addToFile("C:/Biblioguard/logging.txt", infoText);
    file = fopen("C:/Biblioguard/logging.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, infoText);

    fclose(file);
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
    char rentFilename[50] = "C:/Biblioguard/UsersBooks/rentedBooks/";
    strcat(rentFilename, lastUserIdStr);
    strcat(rentFilename, ".dat");
    char buyFilename[50] = "C:/Biblioguard/UsersBooks/purchasedBooks/";
    strcat(buyFilename, lastUserIdStr);
    strcat(buyFilename, ".dat");

    FILE* file;
    fopen_s(&file, filename, "w+");
    fprintf_s(file, USER_FORMAT_OUT, lastUserId, username, name, surname, password, 0, 0, 0);
    fclose(file);
    
    fopen_s(&file, rentFilename, "w+");
    fclose(file);
    
    fopen_s(&file, buyFilename, "w+");
    fclose(file);

    ++lastUserId;
    ++usersCount;
    setLastUserId();

    
    char infoText[256] = "User(id = ";
    strcat(infoText, lastUserIdStr);
    strcat(infoText, ") was authorized");
    strcat(infoText, "\n");
    // addToFile("C:/Biblioguard/logging.txt", infoText);
    file = fopen("C:/Biblioguard/logging.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, infoText);

    fclose(file);
    //setUsersCount();
} 

void WriteBook(Book newBook){
    char bookIdStr[5];
    sprintf(bookIdStr, "%hu", newBook.id);
    char filename[50] = "C:/Biblioguard/Books/";
    strcat(filename, bookIdStr);
    strcat(filename, ".dat");

    FILE* file;
    fopen_s(&file, filename, "w+");
    fprintf_s(file, BOOK_FORMAT_OUT, newBook.id, newBook.title, newBook.author, newBook.genre, newBook.price,
              newBook.quantityForSale, newBook.quantityForRent, newBook.popularity);
    fclose(file);
}

void WriteUser(User newUser){
    char userIdStr[5];
    sprintf(userIdStr, "%hu", newUser.id);
    char filename[50] = "C:/Biblioguard/Users/";
    strcat(filename, userIdStr);
    strcat(filename, ".dat");

    FILE* file;
    fopen_s(&file, filename, "w+");
    fprintf_s(file, USER_FORMAT_OUT, newUser.id, newUser.username, newUser.name, newUser.surname,
              newUser.password, newUser.totalAmountPaid, newUser.purchasedCount, newUser.rentedCount);
    fclose(file);
}

// functions for user


bool BuyBook(unsigned int buyerId, unsigned int bookOrder){
    if(books[bookOrder].quantityForSale > 0) {
        books[bookOrder].quantityForSale--;
        users[buyerId].purchasedBooks[users[buyerId].purchasedCount] = books[bookOrder].id;
        users[buyerId].purchasedCount++;
        users[buyerId].totalAmountPaid += books[bookOrder].price;
        WriteBook(books[bookOrder]);
        WriteUser(users[buyerId]);

        char filePath[50];
        char userIdStr[5];
        sprintf(userIdStr, "%hu", users[buyerId].id);
        char idStr[5];
        sprintf(idStr, "%hu", books[bookOrder].id);
        strcat(filePath, "C:/Biblioguard/UsersBooks/purchasedBooks/");
        strcat(filePath, userIdStr);
        strcat(filePath, ".dat");
        addToFile(filePath, idStr);
        

        char* infoText = "User(id = ";
        strcat(infoText, users[buyerId].id);
        strcat(infoText, ") bought book(id = ");
        strcat(infoText, books[bookOrder].id);
        strcat(infoText, "\n");
        // addToFile("C:/Biblioguard/logging.txt", infoText);
        FILE *file = fopen("C:/Biblioguard/logging.txt", "a");
        if (file == NULL)
        {
            printf("Error opening file.\n");
            return false;
        }
        fprintf(file, infoText);

        fclose(file);
        printf("user(%i) bought a book(%i)", users[buyerId].id, books[bookOrder].id);
        return true;
    }
    return false;
}

bool RentBook(unsigned int buyerId, unsigned int bookOrder){
    if(books[bookOrder].quantityForRent > 0) {
        books[bookOrder].quantityForRent--;
        users[buyerId].rentedBooks[users[buyerId].rentedCount] = books[bookOrder].id;
        users[buyerId].rentedCount++;
        users[buyerId].totalAmountPaid += books[bookOrder].price;
        WriteBook(books[bookOrder]);
        WriteUser(users[buyerId]);

        char filePath[50];
        char userIdStr[5];
        sprintf(userIdStr, "%hu", users[buyerId].id);
        char idStr[5];
        sprintf(idStr, "%hu", books[bookOrder].id);
        strcat(filePath, "C:/Biblioguard/UsersBooks/rentedBooks/");
        strcat(filePath, userIdStr);
        strcat(filePath, ".dat");
        addToFile(filePath, idStr);


        char* infoText = "User(id = ";
        strcat(infoText, users[buyerId].id);
        strcat(infoText, ") rented book(id = ");
        strcat(infoText, books[bookOrder].id);
        strcat(infoText, "\n");
        FILE *file = fopen("C:/Biblioguard/logging.txt", "a");
        if (file == NULL)
        {
            printf("Error opening file.\n");
            return false;
        }
        fprintf(file, infoText);

        fclose(file);
        printf("user(%i) bought a book(%i)", users[buyerId].id, books[bookOrder].id);
        return true;
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

    FILE* file;
    fopen_s(&file, filename, "w+");
    fprintf_s(file, BOOK_FORMAT_OUT, books[bookOrder].id, title, author, genre, books[bookOrder].price,
            books[bookOrder].quantityForSale, books[bookOrder].quantityForRent, books[bookOrder].rentalDuration, books[bookOrder].popularity);
    fclose(file);
}

void DeleteBook(unsigned int bookOrder){
    char bookOrderStr[5];
    sprintf(bookOrderStr, "%hu", books[bookOrder].id);
    char filename[50] = "C:/Biblioguard/Books/";
    strcat(filename, bookOrderStr);
    strcat(filename, ".dat");
    
    for (int i = bookOrder; i < booksCount - 1; ++i){
        books[i] = books[i + 1];
    }
    --booksCount;

    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        if (errno == ENOENT) {
            printf("Error: File '%s' does not exist.\n", filename);
        } else if (errno == EACCES) {
            printf("Error: Permission denied to delete file '%s'.\n", filename);
        } else {
            printf("Error deleting file '%s': %s\n", filename, strerror(errno));
        }
    }
    // reports[reportsCount] = 
    // sprintf(bookOrderStr, "%hu", books[bookOrder].id);
    // addToFile("C:/Biblioguard/logging.txt", )
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

void getBooks(){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("C:/Biblioguard/Books")) != NULL)
    {
        //int i = 0;
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type == DT_REG)
            {
                printf("%s\n", ent->d_name);
                char filePath[50];
                snprintf(filePath, sizeof(filePath), "C:/Biblioguard/Books/%s", ent->d_name);
                char buffer[200];
                Book gottenbook;
                FILE *file;
                fopen_s(&file, filePath, "r");
                fgets(buffer, 200, file);
                while(!feof(file)){
                    sscanf(buffer, BOOK_FORMAT_IN, &gottenbook.id, &gottenbook.title, &gottenbook.author, &gottenbook.genre,
                        &gottenbook.price, &gottenbook.quantityForSale, &gottenbook.quantityForRent, &gottenbook.rentalDuration, &gottenbook.popularity);
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

void getReports(){
    reportsCount = 0;
    FILE *file = fopen("C:/Biblioguard/logging.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    while (fgets(reports[reportsCount], 100, file) != NULL) {
        reports[reportsCount][strcspn(reports[reportsCount], "\n")] = '\0';
        ++reportsCount;

        if (reportsCount >= MAX_REPORTS) {
            printf("Maximum number of lines reached.\n");
            break;
        }
    }
    fclose(file);
    printf("Lines read from file:\n");
    for (int i = 0; i < reportsCount; ++i) {
        printf("%s\n", reports[i]);
    }
}

void getUsers(){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("C:/Biblioguard/Users")) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type == DT_REG)
            {
                printf("%s\n", ent->d_name);
                char filePath[50];
                snprintf(filePath, sizeof(filePath), "C:/Biblioguard/Users/%s", ent->d_name);
                char buffer[200];
                User gottenuser;
                FILE *file;
                fopen_s(&file, filePath, "r");
                fgets(buffer, 200, file);
                while(!feof(file)){
                    sscanf(buffer, USER_FORMAT_IN, &gottenuser.id, &gottenuser.username, &gottenuser.name, &gottenuser.surname,
                           &gottenuser.password, &gottenuser.totalAmountPaid, &gottenuser.purchasedCount, &gottenuser.rentedCount); //, &gottenuser.purchasedBooks, &gottenuser.rentedBooks);
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
    if ((dir = opendir("C:/Biblioguard/UsersBooks/purchasedBooks")) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type == DT_REG)
            {
                printf("%s\n", ent->d_name);
                
                char filePath[50];
                snprintf(filePath, sizeof(filePath), "C:/Biblioguard/UsersBooks/purchasedBooks/%s", ent->d_name);
                
                char indexC[3];
                unsigned int index;
                int i = 0;
                while(ent->d_name[i] != '.'){
                    indexC[i] = ent->d_name[i];
                    ++i;                
                }
                index = atoi(indexC);
                char buffer[200];
                unsigned int purchasedBooks[100];
                unsigned int purchasedBooksIndexer = 0;
                unsigned int tempNumb;
                FILE *file;
                fopen_s(&file, filePath, "r");
                while (fscanf(file, "%d", &tempNumb) == 1)
                {
                    if (purchasedBooksIndexer >= 100)
                    {
                        printf("Error: Too many numbers in the file.\n");
                        fclose(file);
                        return;
                    }
                    users[index].purchasedBooks[purchasedBooksIndexer++] = tempNumb;
                }

                fclose(file);
            }
        }
        closedir(dir);
    }
    if ((dir = opendir("C:/Biblioguard/UsersBooks/rentedBooks")) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type == DT_REG)
            {
                printf("%s\n", ent->d_name);
                
                char filePath[50];
                snprintf(filePath, sizeof(filePath), "C:/Biblioguard/UsersBooks/rentedBooks/%s", ent->d_name);
                
                char indexC[3];
                unsigned int index;
                int i = 0;
                while(ent->d_name[i] != '.'){
                    indexC[i] = ent->d_name[i];
                    ++i;                
                }
                index = atoi(indexC);
                char buffer[200];
                unsigned int rentedBooks[100];
                unsigned int rentedBooksIndexer = 0;
                unsigned int tempNumb;
                FILE *file;
                fopen_s(&file, filePath, "r");
                while (fscanf(file, "%d", &tempNumb) == 1)
                {
                    if (rentedBooksIndexer >= 100)
                    {
                        printf("Error: Too many numbers in the file.\n");
                        fclose(file);
                        return;
                    }
                    users[index].rentedBooks[rentedBooksIndexer++] = tempNumb;
                }

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