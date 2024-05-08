#include "../Repositories/ViewRepository.h"
#include "../Repositories/BookRepository.h"

#pragma once

int adminBooksCount;
int adminVisibleBooksCount;
int adminScrollPos = 0; 

void UpdateAdminScrollBar(HWND hwnd) {
    SCROLLINFO adminSi;
    adminSi.cbSize = sizeof(adminSi);
    adminSi.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    adminSi.nMin = 0;
    adminSi.nMax = 4 * adminBooksCount - 3 * adminVisibleBooksCount;
    adminSi.nPage = adminVisibleBooksCount;
    adminSi.nPos = adminScrollPos;
    SetScrollInfo(AdminScrollbar, SB_CTL, &adminSi, TRUE);
}

void InitializeAdminBookLabels(HWND hwnd){
    int yPos = 50;
    char title[50];
    char priceChar[6];
    char quantitySChar[4];
    char quantityRChar[4];
    char rentalDChar[4];
    char popularityChar[4];
    char info[256];
    for (int i = 0; i < adminBooksCount; ++i) {
        strcpy(info, "");
        strcpy(title, "");

        strcat(title, books[i].title);
        strcat(info, "Author:");
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

        snprintf(priceChar, 5, " %hu", books[i].quantityForSale);
        AdminBooksListLabel[i * 4] = CreateWindow("STATIC", title, WS_CHILD | WS_VISIBLE, 110, yPos, 150, BOOK_HEIGHT, hwnd, (HMENU)(IDC_ADMIN_TITLE_ID0 + i), NULL, NULL);
        AdminBooksListLabel[i * 4 + 1] = CreateWindow("STATIC", info, WS_CHILD | WS_VISIBLE, 110, yPos + 40, 1000, BOOK_HEIGHT, hwnd, (HMENU)(IDC_ADMIN_DESCRIPTION_ID0 + i), NULL, NULL);
        AdminBooksListLabel[i * 4 + 2] = CreateWindow("BUTTON", "Edit", WS_CHILD | WS_VISIBLE, 1110, yPos + 40, 50, BOOK_HEIGHT, hwnd, (HMENU)(IDC_ADMIN_EDIT_ID0 + i), NULL, NULL);
        AdminBooksListLabel[i * 4 + 3] = CreateWindow("BUTTON", "X", WS_CHILD | WS_VISIBLE, 1160, yPos + 40, 50,  BOOK_HEIGHT, hwnd, (HMENU)(IDC_ADMIN_DELETE_ID0 + i), NULL, NULL);
        yPos += 2 * BOOK_HEIGHT;
    }
}

void UpdateAdminBookLabels(HWND hwnd) {
    int yPos =  -adminScrollPos * BOOK_HEIGHT;
    for (int i = 0; i < adminBooksCount; ++i) {
        SetWindowPos(AdminBooksListLabel[i * 4], NULL, 110, yPos, 150, BOOK_HEIGHT, SWP_NOZORDER);
        SetWindowPos(AdminBooksListLabel[i * 4 + 1], NULL, 110, yPos + 40, 1000, BOOK_HEIGHT, SWP_NOZORDER);
        SetWindowPos(AdminBooksListLabel[i * 4 + 2], NULL, 1110, yPos + 40, 50, BOOK_HEIGHT, SWP_NOZORDER);
        SetWindowPos(AdminBooksListLabel[i * 4 + 3], NULL, 1160, yPos + 40, 50, BOOK_HEIGHT, SWP_NOZORDER);
        yPos += 2 * BOOK_HEIGHT + 40;
    }
}

void UpdateAdminView(HWND hwnd){
    UpdateAdminScrollBar(hwnd);
    UpdateAdminBookLabels(hwnd);
    UpdateWindow(hwnd);
}

void ShowAdminView(HWND hwnd){
    adminBooksCount = booksCount;

    InitializeAdminBookLabels(hwnd);
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    adminVisibleBooksCount = clientRect.bottom / BOOK_HEIGHT;
    AdminBooksLabel = CreateWindow("STATIC", "Books", WS_CHILD | WS_VISIBLE, 0, 0, 100, 40, hwnd, (HMENU)IDC_ADMIN_BOOKS_LABEL, NULL, NULL);
    AdminToAddButton = CreateWindow("BUTTON", "Add new book", WS_CHILD | WS_VISIBLE, 0, 600, 100, 40, hwnd, (HMENU)IDC_ADMIN_TOADD_BUTTON, NULL, NULL);
    AdminToLoginButton = CreateWindow("BUTTON", "Back to login", WS_CHILD | WS_VISIBLE, 0, 640, 100, 40, hwnd, (HMENU)IDC_ADMIN_TOLOGIN_BUTTON, NULL, NULL);
    AdminScrollbar = CreateWindow("SCROLLBAR", "", WS_CHILD | WS_VISIBLE | SBS_VERT, clientRect.right - SCROLLBAR_WIDTH, 0, SCROLLBAR_WIDTH, clientRect.bottom, hwnd,  (HMENU)IDC_ADMIN_SCROLLBAR, NULL, NULL);

    UpdateAdminView(hwnd);
}