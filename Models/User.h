#include "Book.h"
#include <stdbool.h>

typedef struct
{
    int id;
    char nickname[20];
    char name[20];
    char surname[20];
    char password[30];
    float totalAmountPaid;
    Book* purchasedBooks[50]; 
    Book* rentedBooks[50];
    
} User;