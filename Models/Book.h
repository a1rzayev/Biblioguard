typedef struct
{
    unsigned int id;
    char title[50];
    char author[25];
    char genre[25];
    float price;
    unsigned short int quantityForSale; 
    unsigned short int quantityForRent;
    unsigned short int rentalDuration;
    unsigned short int popularity;
} Book;
