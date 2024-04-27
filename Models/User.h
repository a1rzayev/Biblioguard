#include "Book.h"
#include <stdbool.h>

typedef struct
{
    unsigned int id;
    char username[20];
    char name[20];
    char surname[20];
    char password[30];
    float totalAmountPaid;
    Book* purchasedBooks[100]; 
    Book* rentedBooks[100];
} User;