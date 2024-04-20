#include "Book.h"
#include <stdbool.h>

typedef struct User
{
    int Id;
    char Name[20];
    char Surname[20];
    char Password[30];
    bool is_admin;
    Book books[256];
} User;