#include "ViewRepository.h"
#include "../BookRepository.h"

#pragma once

int booksCount; // Total number of books
int visibleBooksCount; // Number of books visible at a time
int scrollPos = 0; // Current scroll position

void UpdateScrollBar(HWND hwnd) {
    SCROLLINFO si;
    // Calculate the maximum scroll range
    si.cbSize = sizeof(si);
    si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
    si.nMin = 0;
    si.nMax = booksCount - visibleBooksCount;
    si.nPage = visibleBooksCount;
    si.nPos = scrollPos;
    SetScrollInfo(AdminScrollbar, SB_CTL, &si, TRUE);
}

void InitializeBookLabels(HWND hwnd){
    int yPos = 50;
    for (int i = 0; i < MAX_BOOKS; ++i) {
        //if(books[i]) break;
        AdminBooksListLabel[i * 4] = CreateWindow("STATIC", books[i].author, WS_CHILD | WS_VISIBLE, 110, yPos, 150, BOOK_HEIGHT, hwnd,  (HMENU)(i * 4), NULL, NULL);
        AdminBooksListLabel[i * 4 + 1] = CreateWindow("STATIC", books[i].genre, WS_CHILD | WS_VISIBLE, 110, yPos + 40, 150, BOOK_HEIGHT, hwnd,  (HMENU)(i * 4 + 1), NULL, NULL);
        AdminBooksListLabel[i * 4 + 2] = CreateWindow("BUTTON", "Edit", WS_CHILD | WS_VISIBLE, 1044, yPos + 40, 50, BOOK_HEIGHT, hwnd, (HMENU)(i * 4 + 2), NULL, NULL);
        AdminBooksListLabel[i * 4 + 3] = CreateWindow("BUTTON", "X", WS_CHILD | WS_VISIBLE, 1094, yPos + 40, 50,  BOOK_HEIGHT, hwnd, (HMENU)(i * 4 + 3), NULL, NULL);
        yPos += 2 * BOOK_HEIGHT;
    }
}

void UpdateBookLabels(HWND hwnd) {
    int yPos =  -scrollPos * BOOK_HEIGHT; // Adjust yPos based on scroll position
    for (int i = 0; i < booksCount; ++i) {
        SetWindowPos(AdminBooksListLabel[i * 4], NULL, 110, yPos, 150, BOOK_HEIGHT, SWP_NOZORDER);
        SetWindowPos(AdminBooksListLabel[i * 4 + 1], NULL, 110, yPos + 40, 900, BOOK_HEIGHT, SWP_NOZORDER);
        SetWindowPos(AdminBooksListLabel[i * 4 + 2], NULL, 1044, yPos + 40, 50, BOOK_HEIGHT, SWP_NOZORDER);
        SetWindowPos(AdminBooksListLabel[i * 4 + 3], NULL, 1094, yPos + 40, 50, BOOK_HEIGHT, SWP_NOZORDER);
        yPos += 2 * BOOK_HEIGHT + 40;
    }
}

void ShowAdminView(HWND hwnd){
    HideLogInView(hwnd);
    InitializeBookLabels(hwnd);
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    visibleBooksCount = clientRect.bottom / BOOK_HEIGHT;
    AdminBooksLabel = CreateWindow("STATIC", "Books", WS_CHILD | WS_VISIBLE, 0, 0, 100, 40, hwnd, (HMENU)IDC_ADMIN_BOOKS_LABEL, NULL, NULL);
    AdminToAddButton = CreateWindow("BUTTON", "Add new book", WS_CHILD | WS_VISIBLE, 0, 600, 100, 40, hwnd, (HMENU)IDC_ADMIN_TOADD_BUTTON, NULL, NULL);
    AdminToLoginButton = CreateWindow("BUTTON", "Back to login", WS_CHILD | WS_VISIBLE, 0, 640, 100, 40, hwnd, (HMENU)IDC_ADMIN_TOLOGIN_BUTTON, NULL, NULL);
    AdminScrollbar = CreateWindow("SCROLLBAR", "", WS_CHILD | WS_VISIBLE | SBS_VERT,
                                        clientRect.right - SCROLLBAR_WIDTH, 0,
                                        SCROLLBAR_WIDTH, clientRect.bottom, hwnd, NULL,
                                        NULL, NULL);

    booksCount = MAX_BOOKS;
    UpdateScrollBar(hwnd);
    UpdateBookLabels(hwnd);
    UpdateWindow(hwnd);
}