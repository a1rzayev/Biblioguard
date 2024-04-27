typedef struct
{
    int id;
    char title[50];
    char author[50];
    char genre[25];
    float price;
    int quantityForRent;
    int quantityForSale; 
    int rentalDuration;
    unsigned int popularity; //from 0 to 100
} Book;
