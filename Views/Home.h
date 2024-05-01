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
    for (int i = 0; i < homeBooksCount; ++i) {
        HomeBooksListLabel[i * 4] = CreateWindow("STATIC", books[i].author, WS_CHILD | WS_VISIBLE, 110, yPos, 150, BOOK_HEIGHT, hwnd, (HMENU)(IDC_HOME_TITLE_ID0 + i), NULL, NULL);
        HomeBooksListLabel[i * 4 + 1] = CreateWindow("STATIC", books[i].genre, WS_CHILD | WS_VISIBLE, 110, yPos + 40, 1000, BOOK_HEIGHT, hwnd,  (HMENU)(IDC_HOME_DESCRIPTION_ID0 + i), NULL, NULL);
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
    homeBooksCount = MAX_BOOKS;

    InitializeHomeBookLabels(hwnd);
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    homeVisibleBooksCount = clientRect.bottom / BOOK_HEIGHT;
    HomeBooksLabel = CreateWindow("STATIC", "Books", WS_CHILD | WS_VISIBLE, 0, 0, 100, 40, hwnd, (HMENU)IDC_HOME_BOOKS_LABEL, NULL, NULL);
    HomeToUserbooksButton = CreateWindow("BUTTON", "My books", WS_CHILD | WS_VISIBLE, 0, 600, 100, 40, hwnd, (HMENU)IDC_HOME_TOUSERBOOKS_BUTTON, NULL, NULL);
    HomeToLoginButton = CreateWindow("BUTTON", "Back to login", WS_CHILD | WS_VISIBLE, 0, 640, 100, 40, hwnd, (HMENU)IDC_HOME_TOLOGIN_BUTTON, NULL, NULL);
    HomeScrollbar = CreateWindow("SCROLLBAR", "", WS_CHILD | WS_VISIBLE | SBS_VERT, clientRect.right - SCROLLBAR_WIDTH, 0, SCROLLBAR_WIDTH, clientRect.bottom, hwnd,  (HMENU)IDC_HOME_SCROLLBAR, NULL, NULL);

    UpdateHomeScrollBar(hwnd);
    UpdateHomeBookLabels(hwnd);
    UpdateWindow(hwnd);
}