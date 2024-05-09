#include "Book.h"

typedef struct
{
    unsigned int id;
    char username[20];
    char name[20];
    char surname[20];
    char password[20];
    float totalAmountPaid;
    unsigned int purchasedBooks[100]; 
    unsigned int rentedBooks[100];
} User;