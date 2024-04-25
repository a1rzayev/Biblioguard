#include "Book.h"
#include <stdbool.h>

typedef struct
{
    int id;
    char nickname[20];
    char name[20];
    char surname[20];
    char password[30];
    bool is_admin;
    Book books[256];
} User;