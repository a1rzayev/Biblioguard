#include "Book.h"

typedef struct
{
    unsigned int id;
    char username[20];
    char name[20];
    char surname[20];
    char password[20];
    float totalAmountPaid;
    unsigned int purchasedCount;
    unsigned int rentedCount;
    Book purchasedBooks[100]; 
    Book rentedBooks[100];
} User;