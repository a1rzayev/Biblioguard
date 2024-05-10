#include "../Repositories/ViewRepository.h"
#include "../Repositories/BookRepository.h"

#pragma once

int homeBooksCount;
int homeVisibleBooksCount;
int homeScrollPos = 0; 

void UpdateHomeScrollBar(HWND hwnd) {
    SCROLLINFO homeSi;
    homeSi.cbSize = sizeof(homeSi);
    homeSi.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    homeSi.nMin = 0;
    homeSi.nMax = 4 * homeBooksCount - 3 * homeVisibleBooksCount;
    homeSi.nPage = homeVisibleBooksCount;
    homeSi.nPos = homeScrollPos;
    SetScrollInfo(HomeScrollbar, SB_CTL, &homeSi, TRUE);
}

void InitializeHomeBookLabels(HWND hwnd){
    int yPos = 50;
    char title[256];
    char priceChar[6];
    char quantitySChar[4];
    char quantityRChar[4];
    char rentalDChar[4];
    char popularityChar[4];
    char info[256];
    for (int i = 0; i < homeBooksCount; ++i) {
        strcpy(info, "");
        strcpy(title, books[i].title);

        strcat(info, "Author: ");
        strcat(info, books[i].author);

        strcat(info, " Genre: ");
        strcat(info, books[i].genre);

        snprintf(priceChar, 7, " %f", books[i].price);
        strcat(info, priceChar);
        strcat(info, "$ (S:");
        snprintf(quantitySChar, 4, " %hu", books[i].quantityForSale);
        strcat(info, quantitySChar);
        strcat(info, " R:");
        snprintf(quantityRChar, 4, " %hu", books[i].quantityForRent);
        strcat(info, quantityRChar);
        strcat(info, "[");
        snprintf(rentalDChar, 4, " %hu", books[i].rentalDuration);
        strcat(info, rentalDChar);
        strcat(info, " days]) Popularity: ");
        snprintf(popularityChar, 4, " %hu", books[i].popularity);
        strcat(info, popularityChar);

        HomeBooksListLabel[i * 4] = CreateWindow("STATIC", books[i].title, WS_CHILD | WS_VISIBLE, 110, yPos, 150, BOOK_HEIGHT, hwnd, (HMENU)(IDC_HOME_TITLE_ID0 + i), NULL, NULL);
        HomeBooksListLabel[i * 4 + 1] = CreateWindow("STATIC", info, WS_CHILD | WS_VISIBLE, 110, yPos + 40, 1000, BOOK_HEIGHT, hwnd,  (HMENU)(IDC_HOME_DESCRIPTION_ID0 + i), NULL, NULL);
        HomeBooksListLabel[i * 4 + 2] = CreateWindow("BUTTON", "Rent", WS_CHILD | WS_VISIBLE, 1110, yPos + 40, 50, BOOK_HEIGHT, hwnd, (HMENU)(IDC_HOME_BUY_ID0 + i), NULL, NULL);
        HomeBooksListLabel[i * 4 + 3] = CreateWindow("BUTTON", "Buy", WS_CHILD | WS_VISIBLE, 1160, yPos + 40, 50,  BOOK_HEIGHT, hwnd, (HMENU)(IDC_HOME_RENT_ID0 + i), NULL, NULL);
        yPos += 2 * BOOK_HEIGHT;
    }
}

void UpdateHomeBookLabels(HWND hwnd) {
    int yPos =  -homeScrollPos * BOOK_HEIGHT;
    for (int i = 0; i < homeBooksCount; ++i) {
        SetWindowPos(HomeBooksListLabel[i * 4], NULL, 110, yPos, 150, BOOK_HEIGHT, SWP_NOZORDER);
        SetWindowPos(HomeBooksListLabel[i * 4 + 1], NULL, 110, yPos + 40, 1000, BOOK_HEIGHT, SWP_NOZORDER);
        SetWindowPos(HomeBooksListLabel[i * 4 + 2], NULL, 1110, yPos + 40, 50, BOOK_HEIGHT, SWP_NOZORDER);
        SetWindowPos(HomeBooksListLabel[i * 4 + 3], NULL, 1160, yPos + 40, 50, BOOK_HEIGHT, SWP_NOZORDER);
        yPos += 2 * BOOK_HEIGHT + 40;
    }
}

void ShowHomeView(HWND hwnd){
    homeBooksCount = booksCount;

    InitializeHomeBookLabels(hwnd);
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    homeVisibleBooksCount = clientRect.bottom / BOOK_HEIGHT;
    HomePriceSortButton = CreateWindow("BUTTON", "Sort(price)", WS_CHILD | WS_VISIBLE, 0, 480, 100, 40, hwnd, (HMENU)IDC_HOME_PRICESORT_BUTTON, NULL, NULL);
    HomePopularitySortButton = CreateWindow("BUTTON", "Sort(popularity)", WS_CHILD | WS_VISIBLE, 0, 520, 100, 40, hwnd, (HMENU)IDC_HOME_POPULARITYSORT_BUTTON, NULL, NULL);
    
    HomeBooksLabel = CreateWindow("STATIC", "Books", WS_CHILD | WS_VISIBLE, 0, 0, 100, 40, hwnd, (HMENU)IDC_HOME_BOOKS_LABEL, NULL, NULL);
    HomeToUserbooksButton = CreateWindow("BUTTON", "My books", WS_CHILD | WS_VISIBLE, 0, 600, 100, 40, hwnd, (HMENU)IDC_HOME_TOUSERBOOKS_BUTTON, NULL, NULL);
    HomeToLoginButton = CreateWindow("BUTTON", "Back to login", WS_CHILD | WS_VISIBLE, 0, 640, 100, 40, hwnd, (HMENU)IDC_HOME_TOLOGIN_BUTTON, NULL, NULL);
    HomeScrollbar = CreateWindow("SCROLLBAR", "", WS_CHILD | WS_VISIBLE | SBS_VERT, clientRect.right - SCROLLBAR_WIDTH, 0, SCROLLBAR_WIDTH, clientRect.bottom, hwnd,  (HMENU)IDC_HOME_SCROLLBAR, NULL, NULL);

    UpdateHomeScrollBar(hwnd);
    UpdateHomeBookLabels(hwnd);
    UpdateWindow(hwnd);
}