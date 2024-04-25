#include "ViewRepository.h"
#include "../BookRepository.h"

#pragma once

void ShowAdminView(HWND hwnd){
    HideSignUpView();
    HideLogInView();
    AdminBooksLabel = CreateWindow("STATIC", "Books", WS_CHILD | WS_VISIBLE, 0, 0, 100, 40, hwnd, (HMENU)IDC_ADMIN_BOOKS_LABEL, NULL, NULL);
    int yPos = 50;
    for (int i = 0; i < MAX_BOOKS; ++i) {

        AdminBooksListLabel[i * 2] = CreateWindow("STATIC", books[i].author, WS_CHILD | WS_VISIBLE, 10, yPos, 150, 20, hwnd, NULL, NULL, NULL);
        AdminBooksListLabel[i * 2 + 1] = CreateWindow("STATIC", books[i].genre, WS_CHILD | WS_VISIBLE, 200, yPos, 150, 20, hwnd, NULL, NULL, NULL);
        yPos += 30;
    }
    ShowWindow(AdminBooksLabel, SW_SHOW);
    UpdateWindow(hwnd);
}