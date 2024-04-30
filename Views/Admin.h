#include "ViewRepository.h"
#include "../BookRepository.h"

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
    for (int i = 0; i < adminBooksCount; ++i) {
        AdminBooksListLabel[i * 4] = CreateWindow("STATIC", books[i].author, WS_CHILD | WS_VISIBLE, 110, yPos, 150, BOOK_HEIGHT, hwnd, (HMENU)(IDC_ADMIN_TITLE_ID0 + i), NULL, NULL);
        AdminBooksListLabel[i * 4 + 1] = CreateWindow("STATIC", books[i].genre, WS_CHILD | WS_VISIBLE, 110, yPos + 40, 1000, BOOK_HEIGHT, hwnd,  (HMENU)(IDC_ADMIN_DESCRIPTION_ID0 + i), NULL, NULL);
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

void ShowAdminView(HWND hwnd){
    adminBooksCount = MAX_BOOKS;

    InitializeAdminBookLabels(hwnd);
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    adminVisibleBooksCount = clientRect.bottom / BOOK_HEIGHT;
    AdminBooksLabel = CreateWindow("STATIC", "Books", WS_CHILD | WS_VISIBLE, 0, 0, 100, 40, hwnd, (HMENU)IDC_ADMIN_BOOKS_LABEL, NULL, NULL);
    AdminToAddButton = CreateWindow("BUTTON", "Add new book", WS_CHILD | WS_VISIBLE, 0, 600, 100, 40, hwnd, (HMENU)IDC_ADMIN_TOADD_BUTTON, NULL, NULL);
    AdminToLoginButton = CreateWindow("BUTTON", "Back to login", WS_CHILD | WS_VISIBLE, 0, 640, 100, 40, hwnd, (HMENU)IDC_ADMIN_TOLOGIN_BUTTON, NULL, NULL);
    AdminScrollbar = CreateWindow("SCROLLBAR", "", WS_CHILD | WS_VISIBLE | SBS_VERT, clientRect.right - SCROLLBAR_WIDTH, 0, SCROLLBAR_WIDTH, clientRect.bottom, hwnd,  (HMENU)IDC_ADMIN_SCROLLBAR, NULL, NULL);

    UpdateAdminScrollBar(hwnd);
    UpdateAdminBookLabels(hwnd);
    UpdateWindow(hwnd);
}