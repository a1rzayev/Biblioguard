#include "../Controllers/ViewController.h"
#include "../Controllers/BookController.h"

#pragma once

//used to define scroll-info
int userbooksBooksCount;
int userbooksVisibleBooksCount;
int userbooksScrollPos = 0; 

//updates scrollbar
void UpdateUserbooksScrollBar(HWND hwnd);
//initializes rented books list
void InitializeUserbooksBookLabelsR(HWND hwnd);
//initializes purchased books list
void InitializeUserbooksBookLabelsB(HWND hwnd);
//updates rented books list
void UpdateUserbooksBookLabelsR(HWND hwnd);
//updates purchased books list
void UpdateUserbooksBookLabelsB(HWND hwnd);
//shows userbooks view
void ShowUserbooksView(HWND hwnd);





void UpdateUserbooksScrollBar(HWND hwnd) {
    SCROLLINFO userbooksSi;
    userbooksSi.cbSize = sizeof(userbooksSi);
    userbooksSi.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    userbooksSi.nMin = 0;
    userbooksSi.nMax = 2 * userbooksBooksCount -  userbooksVisibleBooksCount;
    userbooksSi.nPage = userbooksVisibleBooksCount;
    userbooksSi.nPos = userbooksScrollPos;
    SetScrollInfo(UserbooksScrollbar, SB_CTL, &userbooksSi, TRUE);
}

void InitializeUserbooksBookLabelsR(HWND hwnd){
    int yPos = 50;
    char title[256];
    char priceChar[6];
    char rentalDChar[4];
    char popularityChar[4];
    char infoR[256];
    for (int i = 0; i < currentUser->rentedCount; ++i) {
        strcpy(infoR, "");
        strcpy(title, currentUser->rentedBooks[i].title);
        strcat(infoR, "Author: ");
        strcat(infoR, currentUser->rentedBooks[i].author);
        strcat(infoR, " Genre: ");
        strcat(infoR, currentUser->rentedBooks[i].genre);
        snprintf(priceChar, 7, " %f", currentUser->rentedBooks[i].price);
        strcat(infoR, priceChar);
        strcat(infoR, "$");
        strcat(infoR, "[Expires in ");
        snprintf(rentalDChar, 4, " %hu", currentUser->rentedBooks[i].rentalDuration);
        strcat(infoR, rentalDChar);
        strcat(infoR, " days]) Popularity: ");
        snprintf(popularityChar, 4, " %hu", currentUser->rentedBooks[i].popularity);
        strcat(infoR, popularityChar);
        UserbooksRentedListLabel[i * 2] = CreateWindow("STATIC", currentUser->rentedBooks[i].title, WS_CHILD | WS_VISIBLE, 750, yPos, 150, BOOK_HEIGHT, hwnd, (HMENU)(IDC_USERBOOKS_RENTED_TITLE_ID0 + i), NULL, NULL);
        UserbooksRentedListLabel[i * 2 + 1] = CreateWindow("STATIC", infoR, WS_CHILD | WS_VISIBLE, 750, yPos + 40, 400, BOOK_HEIGHT, hwnd,  (HMENU)(IDC_USERBOOKS_RENTED_DESCRIPTION_ID0 + i), NULL, NULL);

        yPos += 2 * BOOK_HEIGHT;
    }
}

void InitializeUserbooksBookLabelsB(HWND hwnd){
    int yPos = 50;
    char title[256];
    char priceChar[6];
    char rentalDChar[4];
    char popularityChar[4];
    char infoB[256];
    for (int i = 0; i < currentUser->purchasedCount; ++i) {
        strcpy(infoB, "");
        strcpy(title, currentUser->purchasedBooks[i].title);
        strcat(infoB, "Author: ");
        strcat(infoB, currentUser->purchasedBooks[i].author);
        strcat(infoB, " Genre: ");
        strcat(infoB, currentUser->purchasedBooks[i].genre);
        snprintf(priceChar, 7, " %f", currentUser->purchasedBooks[i].price);
        strcat(infoB, priceChar);
        strcat(infoB, "$");
        strcat(infoB, " Popularity: ");
        snprintf(popularityChar, 4, " %hu", currentUser->purchasedBooks[i].popularity);
        strcat(infoB, popularityChar);
        UserbooksPurchasedListLabel[i * 2] = CreateWindow("STATIC", currentUser->purchasedBooks[i].title, WS_CHILD | WS_VISIBLE, 110, yPos, 150, BOOK_HEIGHT, hwnd, (HMENU)(IDC_USERBOOKS_PURCHASED_TITLE_ID0 + i), NULL, NULL);
        UserbooksPurchasedListLabel[i * 2 + 1] = CreateWindow("STATIC", infoB, WS_CHILD | WS_VISIBLE, 110, yPos + 40, 400, BOOK_HEIGHT, hwnd,  (HMENU)(IDC_USERBOOKS_PURCHASED_DESCRIPTION_ID0 + i), NULL, NULL);
        
        yPos += 2 * BOOK_HEIGHT;
    }
}

void UpdateUserbooksBookLabelsR(HWND hwnd) {
    int yPos =  -userbooksScrollPos * BOOK_HEIGHT;
    for (int i = 0; i < currentUser->rentedCount; ++i) {
        SetWindowPos(UserbooksRentedListLabel[i * 2], NULL, 750, yPos, 150, BOOK_HEIGHT, SWP_NOZORDER);
        SetWindowPos(UserbooksRentedListLabel[i * 2 + 1], NULL, 750, yPos + 40, 400, BOOK_HEIGHT, SWP_NOZORDER);
        yPos += 2 * BOOK_HEIGHT + 40;
    }
}

void UpdateUserbooksBookLabelsB(HWND hwnd) {
    int yPos =  -userbooksScrollPos * BOOK_HEIGHT;
    for (int i = 0; i < currentUser->purchasedCount; ++i) {
        SetWindowPos(UserbooksPurchasedListLabel[i * 2], NULL, 110, yPos, 150, BOOK_HEIGHT, SWP_NOZORDER);
        SetWindowPos(UserbooksPurchasedListLabel[i * 2 + 1], NULL, 110, yPos + 40, 400, BOOK_HEIGHT, SWP_NOZORDER);
        yPos += 2 * BOOK_HEIGHT + 40;
    }
}

void ShowUserbooksView(HWND hwnd){
    if(currentUser->purchasedCount >= currentUser->rentedCount)
        userbooksBooksCount = currentUser->purchasedCount;
    else
        userbooksBooksCount = currentUser->rentedCount;

    InitializeUserbooksBookLabelsR(hwnd);
    InitializeUserbooksBookLabelsB(hwnd);
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    userbooksVisibleBooksCount = clientRect.bottom / BOOK_HEIGHT;
    UserbooksPurchasedLabel = CreateWindow("STATIC", "Purchased books", WS_CHILD | WS_VISIBLE, 0, 0, 100, 40, hwnd, (HMENU)IDC_USERBOOKS_PURCHASED_LABEL, NULL, NULL);
    UserbooksRentedLabel = CreateWindow("STATIC", "Rented books", WS_CHILD | WS_VISIBLE, 640, 0, 100, 40, hwnd, (HMENU)IDC_USERBOOKS_RENTED_LABEL, NULL, NULL);
    UserbooksToHomeButton = CreateWindow("BUTTON", "Back to home", WS_CHILD | WS_VISIBLE, 0, 640, 100, 40, hwnd, (HMENU)IDC_USERBOOKS_TOHOME_BUTTON, NULL, NULL);
    UserbooksScrollbar = CreateWindow("SCROLLBAR", "", WS_CHILD | WS_VISIBLE | SBS_VERT, clientRect.right - SCROLLBAR_WIDTH, 0, SCROLLBAR_WIDTH, clientRect.bottom, hwnd, (HMENU)IDC_USERBOOKS_SCROLLBAR, NULL, NULL);

    UpdateUserbooksScrollBar(hwnd);
    UpdateUserbooksBookLabelsR(hwnd);
    UpdateUserbooksBookLabelsB(hwnd);
    UpdateWindow(hwnd);
}