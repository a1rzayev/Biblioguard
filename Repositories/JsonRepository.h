// //#include "../cjson/cJSON.h"
// //#include <stdio.h>
// //#include <stdlib.h>
// //#include <string.h>
// //#include "../Models/Book.h"
// // // Function to serialize a Book struct to JSON
// // char *serializeBookToJson(const Book *book) {
// //     cJSON *root = cJSON_CreateObject();
// //     cJSON_AddNumberToObject(root, "id", book->id);
// //     cJSON_AddStringToObject(root, "title", book->title);
// //     cJSON_AddStringToObject(root, "author", book->author);
// //     cJSON_AddStringToObject(root, "genre", book->genre);
// //     cJSON_AddNumberToObject(root, "price", book->price);
// //     cJSON_AddNumberToObject(root, "quantityForSale", book->quantityForSale);
// //     cJSON_AddNumberToObject(root, "quantityForRent", book->quantityForRent);
// //     cJSON_AddNumberToObject(root, "rentalDuration", book->rentalDuration);
// //     cJSON_AddNumberToObject(root, "popularity", book->popularity);

// //     char *jsonStr = cJSON_PrintUnformatted(root);
// //     cJSON_Delete(root);

// //     return jsonStr;
// // }

// // // Function to deserialize JSON to a Book struct
// // Book deserializeJsonToBook(const char *jsonStr) {
// //     Book book;

// //     cJSON *root = cJSON_Parse(jsonStr);
// //     if (root == NULL) {
// //         fprintf(stderr, "Error parsing JSON: %s\n", cJSON_GetErrorPtr());
// //         exit(EXIT_FAILURE);
// //     }

// //     cJSON *id = cJSON_GetObjectItem(root, "id");
// //     cJSON *title = cJSON_GetObjectItem(root, "title");
// //     cJSON *author = cJSON_GetObjectItem(root, "author");
// //     cJSON *genre = cJSON_GetObjectItem(root, "genre");
// //     cJSON *price = cJSON_GetObjectItem(root, "price");
// //     cJSON *quantityForSale = cJSON_GetObjectItem(root, "quantityForSale");
// //     cJSON *quantityForRent = cJSON_GetObjectItem(root, "quantityForRent");
// //     cJSON *rentalDuration = cJSON_GetObjectItem(root, "rentalDuration");
// //     cJSON *popularity = cJSON_GetObjectItem(root, "popularity");

// //     book.id = id->valueint;
// //     strcpy(book.title, title->valuestring);
// //     strcpy(book.author, author->valuestring);
// //     strcpy(book.genre, genre->valuestring);
// //     book.price = (float)price->valuedouble;
// //     book.quantityForSale = quantityForSale->valueint;
// //     book.quantityForRent = quantityForRent->valueint;
// //     book.rentalDuration = rentalDuration->valueint;
// //     book.popularity = popularity->valueint;

// //     cJSON_Delete(root);

// //     return book;
// // }

// // void serializeBooks(Book books[], int numBooks, char* filename) {
// //     FILE *fp = fopen(filename, "wb");
// //     if (fp == NULL) {
// //         printf("Error opening file for writing.\n");
// //         return;
// //     }
// //     fwrite(&numBooks, sizeof(int), 1, fp); // Write the number of books
// //     fwrite(books, sizeof(Book), numBooks, fp); // Write the array of books
// //     fclose(fp);
// // }

// // void deserializeBooks(Book books[], int *numBooks, char* filename) {
// //     FILE *fp = fopen(filename, "rb");
// //     if (fp == NULL) {
// //         printf("Error opening file for reading.\n");
// //         return;
// //     }
// //     fread(numBooks, sizeof(int), 1, fp); // Read the number of books
// //     fread(books, sizeof(Book), *numBooks, fp); // Read the array of books
// //     fclose(fp);
// // }

// // int main() {
// //     // Sample Book object
// //     Book book = {123, "The Great Gatsby", "F. Scott Fitzgerald", "Fiction", 19.99,
// //                  100, 50, 7, 10};

// //     // Serialize the Book object to JSON
// //     char *jsonStr = serializeBookToJson(&book);
// //     printf("Serialized JSON:\n%s\n", jsonStr);

// //     // Deserialize JSON to a Book object
// //     Book deserializedBook = deserializeJsonToBook(jsonStr);

// //     // Display deserialized Book object
// //     printf("\nDeserialized Book:\n");
// //     printf("ID: %u\n", deserializedBook.id);
// //     printf("Title: %s\n", deserializedBook.title);
// //     printf("Author: %s\n", deserializedBook.author);
// //     printf("Genre: %s\n", deserializedBook.genre);
// //     printf("Price: %.2f\n", deserializedBook.price);
// //     printf("Quantity For Sale: %hu\n", deserializedBook.quantityForSale);
// //     printf("Quantity For Rent: %hu\n", deserializedBook.quantityForRent);
// //     printf("Rental Duration: %hu days\n", deserializedBook.rentalDuration);
// //     printf("Popularity: %hu\n", deserializedBook.popularity);

// //     // Free the memory allocated for the JSON string
// //     free(jsonStr);

// //     return 0;
// // }


// void deserializeJsonToBooks(char* jsonStr, Book* books, unsigned int *numBooks) {
//     cJSON *root = cJSON_Parse(jsonStr); // Parse JSON string

//     *numBooks = (unsigned int)cJSON_GetArraySize(root); // Get the number of books

//     for (int i = 0; i < *numBooks; i++) {
//         cJSON *bookObj = cJSON_GetArrayItem(root, i); // Get the JSON object for each book
//         books[i].id = cJSON_GetObjectItem(bookObj, "id")->valueint;
//         strcpy(books[i].title, cJSON_GetObjectItem(bookObj, "title")->valuestring);
//         strcpy(books[i].author, cJSON_GetObjectItem(bookObj, "author")->valuestring);
//         strcpy(books[i].genre, cJSON_GetObjectItem(bookObj, "genre")->valuestring);
//         books[i].price = cJSON_GetObjectItem(bookObj, "price")->valuedouble;
//         books[i].quantityForSale = cJSON_GetObjectItem(bookObj, "quantityForSale")->valueint;
//         books[i].quantityForRent = cJSON_GetObjectItem(bookObj, "quantityForRent")->valueint;
//         books[i].rentalDuration = cJSON_GetObjectItem(bookObj, "rentalDuration")->valueint;
//         books[i].popularity = cJSON_GetObjectItem(bookObj, "popularity")->valueint;
//     }

//     cJSON_Delete(root); // Free cJSON objects
// }

// char* serializeBooksToJson(Book books[], int numBooks) {
//     cJSON *root = cJSON_CreateArray(); // Create a JSON array

//     for (int i = 0; i < numBooks; i++) {
//         cJSON *bookObj = cJSON_CreateObject(); // Create a JSON object for each book
//         cJSON_AddNumberToObject(bookObj, "id", books[i].id);
//         cJSON_AddStringToObject(bookObj, "title", books[i].title);
//         cJSON_AddStringToObject(bookObj, "author", books[i].author);
//         cJSON_AddStringToObject(bookObj, "genre", books[i].genre);
//         cJSON_AddNumberToObject(bookObj, "price", books[i].price);
//         cJSON_AddNumberToObject(bookObj, "quantityForSale", books[i].quantityForSale);
//         cJSON_AddNumberToObject(bookObj, "quantityForRent", books[i].quantityForRent);
//         cJSON_AddNumberToObject(bookObj, "rentalDuration", books[i].rentalDuration);
//         cJSON_AddNumberToObject(bookObj, "popularity", books[i].popularity);

//         cJSON_AddItemToArray(root, bookObj); // Add book object to the array
//     }

//     char *jsonStr = cJSON_Print(root); // Convert cJSON object to JSON string
//     cJSON_Delete(root); // Free cJSON objects

//     return jsonStr;
// }
