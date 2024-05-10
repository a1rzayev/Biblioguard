#include "../Controllers/ViewController.h"
#include "../Controllers/BookController.h"

#pragma once

int userbooksBooksCount;
int userbooksVisibleBooksCount;
int userbooksScrollPos = 0; 

void UpdateUserbooksScrollBar(HWND hwnd) {
    SCROLLINFO userbooksSi;
    userbooksSi.cbSize = sizeof(userbooksSi);
    userbooksSi.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    userbooksSi.nMin = 0;
    userbooksSi.nMax = 3 * userbooksBooksCount - 2 * userbooksVisibleBooksCount;
    userbooksSi.nPage = userbooksVisibleBooksCount;
    userbooksSi.nPos = userbooksScrollPos;
    SetScrollInfo(UserbooksScrollbar, SB_CTL, &userbooksSi, TRUE);
}

void InitializeUserbooksBookLabels(HWND hwnd){
    int yPos = 50;
    for (int i = 0; i < userbooksBooksCount; ++i) {
        UserbooksPurchasedListLabel[i * 3] = CreateWindow("STATIC", books[i].author, WS_CHILD | WS_VISIBLE, 110, yPos, 150, BOOK_HEIGHT, hwnd, (HMENU)(IDC_USERBOOKS_PURCHASED_TITLE_ID0 + i), NULL, NULL);
        UserbooksPurchasedListLabel[i * 3 + 1] = CreateWindow("STATIC", books[i].genre, WS_CHILD | WS_VISIBLE, 110, yPos + 40, 400, BOOK_HEIGHT, hwnd,  (HMENU)(IDC_USERBOOKS_PURCHASED_DESCRIPTION_ID0 + i), NULL, NULL);
        UserbooksPurchasedListLabel[i * 3 + 2] = CreateWindow("BUTTON", "X", WS_CHILD | WS_VISIBLE, 510, yPos + 40, 30, BOOK_HEIGHT, hwnd, (HMENU)(IDC_USERBOOKS_PURCHASED_DELETE_ID0 + i), NULL, NULL);
        
        UserbooksRentedListLabel[i * 3] = CreateWindow("STATIC", books[i].author, WS_CHILD | WS_VISIBLE, 750, yPos, 150, BOOK_HEIGHT, hwnd, (HMENU)(IDC_USERBOOKS_RENTED_TITLE_ID0 + i), NULL, NULL);
        UserbooksRentedListLabel[i * 3 + 1] = CreateWindow("STATIC", books[i].genre, WS_CHILD | WS_VISIBLE, 750, yPos + 40, 400, BOOK_HEIGHT, hwnd,  (HMENU)(IDC_USERBOOKS_RENTED_DESCRIPTION_ID0 + i), NULL, NULL);
        UserbooksRentedListLabel[i * 3 + 2] = CreateWindow("BUTTON", "X", WS_CHILD | WS_VISIBLE, 1150, yPos + 40, 30, BOOK_HEIGHT, hwnd, (HMENU)(IDC_USERBOOKS_RENTED_DELETE_ID0 + i), NULL, NULL);
        
        yPos += 2 * BOOK_HEIGHT;
    }
}

void UpdateUserbooksBookLabels(HWND hwnd) {
    int yPos =  -userbooksScrollPos * BOOK_HEIGHT;
    for (int i = 0; i < userbooksBooksCount; ++i) {
        SetWindowPos(UserbooksPurchasedListLabel[i * 3], NULL, 110, yPos, 150, BOOK_HEIGHT, SWP_NOZORDER);
        SetWindowPos(UserbooksPurchasedListLabel[i * 3 + 1], NULL, 110, yPos + 40, 400, BOOK_HEIGHT, SWP_NOZORDER);
        SetWindowPos(UserbooksPurchasedListLabel[i * 3 + 2], NULL, 510, yPos + 40, 30, BOOK_HEIGHT, SWP_NOZORDER);

        SetWindowPos(UserbooksRentedListLabel[i * 3], NULL, 750, yPos, 150, BOOK_HEIGHT, SWP_NOZORDER);
        SetWindowPos(UserbooksRentedListLabel[i * 3 + 1], NULL, 750, yPos + 40, 400, BOOK_HEIGHT, SWP_NOZORDER);
        SetWindowPos(UserbooksRentedListLabel[i * 3 + 2], NULL, 1150, yPos + 40, 30, BOOK_HEIGHT, SWP_NOZORDER);
        yPos += 2 * BOOK_HEIGHT + 40;
    }
}

void ShowUserbooksView(HWND hwnd){
    userbooksBooksCount = MAX_BOOKS;

    InitializeUserbooksBookLabels(hwnd);
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    userbooksVisibleBooksCount = clientRect.bottom / BOOK_HEIGHT;
    UserbooksPurchasedLabel = CreateWindow("STATIC", "Purchased books", WS_CHILD | WS_VISIBLE, 0, 0, 100, 40, hwnd, (HMENU)IDC_USERBOOKS_PURCHASED_LABEL, NULL, NULL);
    UserbooksRentedLabel = CreateWindow("STATIC", "Rented books", WS_CHILD | WS_VISIBLE, 640, 0, 100, 40, hwnd, (HMENU)IDC_USERBOOKS_RENTED_LABEL, NULL, NULL);
    UserbooksToHomeButton = CreateWindow("BUTTON", "Back to home", WS_CHILD | WS_VISIBLE, 0, 640, 100, 40, hwnd, (HMENU)IDC_USERBOOKS_TOHOME_BUTTON, NULL, NULL);
    UserbooksScrollbar = CreateWindow("SCROLLBAR", "", WS_CHILD | WS_VISIBLE | SBS_VERT, clientRect.right - SCROLLBAR_WIDTH, 0, SCROLLBAR_WIDTH, clientRect.bottom, hwnd, (HMENU)IDC_USERBOOKS_SCROLLBAR, NULL, NULL);

    UpdateUserbooksScrollBar(hwnd);
    UpdateUserbooksBookLabels(hwnd);
    UpdateWindow(hwnd);
}