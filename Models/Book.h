typedef struct
{
    unsigned int id;
    char title[50];
    char author[50];
    char genre[20];
    float price;
    unsigned short int quantityForSale; 
    unsigned short int quantityForRent;
    unsigned short int rentalDuration;
    unsigned short int popularity;
} Book;
