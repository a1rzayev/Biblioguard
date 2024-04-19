#include "Book.h"

typedef struct User
{
    int Id;
    char Name[20];
    char Surname[20];
    char Password[30];
    Book books[256];
} User;