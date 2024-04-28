#include "ViewRepository.h"

#pragma once

void ShowAddbookView(HWND hwnd) {
    AddbookTitleLabel = CreateWindow("STATIC", "Title:", WS_CHILD | WS_VISIBLE, 350, 280, 100, 20, hwnd, (HMENU)IDC_ADDBOOK_TITLE_LABEL, NULL, NULL);
    AddbookTitleInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 450, 280, 180, 20, hwnd, (HMENU)IDC_ADDBOOK_TITLE_EDIT, NULL, NULL);
    AddbookAuthorLabel = CreateWindow("STATIC", "Author:", WS_CHILD | WS_VISIBLE, 350, 320, 100, 20, hwnd, (HMENU)IDC_ADDBOOK_AUTHOR_LABEL, NULL, NULL);
    AddbookAuthorInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 450, 320, 180, 20, hwnd, (HMENU)IDC_ADDBOOK_AUTHOR_EDIT, NULL, NULL);
    AddbookGenreLabel = CreateWindow("STATIC", "Genre:", WS_CHILD | WS_VISIBLE, 350, 360, 100, 20, hwnd, (HMENU)IDC_ADDBOOK_GENRE_LABEL, NULL, NULL);
    AddbookGenreInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 450, 360, 180, 20, hwnd, (HMENU)IDC_ADDBOOK_GENRE_EDIT, NULL, NULL);
    AddbookPriceLabel = CreateWindow("STATIC", "Price:", WS_CHILD | WS_VISIBLE, 350, 400, 100, 20, hwnd, (HMENU)IDC_ADDBOOK_PRICE_LABEL, NULL, NULL);
    AddbookPriceInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 450, 400, 180, 20, hwnd, (HMENU)IDC_ADDBOOK_PRICE_EDIT, NULL, NULL);
    
    AddbookQsaleLabel = CreateWindow("STATIC", "Quantity(sale):", WS_CHILD | WS_VISIBLE, 650, 280, 100, 40, hwnd, (HMENU)IDC_ADDBOOK_QSALE_LABEL, NULL, NULL);
    AddbookQsaleInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 280, 180, 40, hwnd, (HMENU)IDC_ADDBOOK_QSALE_EDIT, NULL, NULL);
    AddbookQrentLabel = CreateWindow("STATIC", "Quantity(rent):", WS_CHILD | WS_VISIBLE, 650, 330, 100, 40, hwnd, (HMENU)IDC_ADDBOOK_QRENT_LABEL, NULL, NULL);
    AddbookQrentInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 330, 180, 40, hwnd, (HMENU)IDC_ADDBOOK_QRENT_EDIT, NULL, NULL);
    AddbookRdurationLabel = CreateWindow("STATIC", "Rental duration(days):", WS_CHILD | WS_VISIBLE, 650, 380, 100, 40, hwnd, (HMENU)IDC_ADDBOOK_RDURATION_LABEL, NULL, NULL);
    AddbookRdurationInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 380, 180, 40, hwnd, (HMENU)IDC_ADDBOOK_RDURATION_EDIT, NULL, NULL);
    
    AddbookSubmitButton = CreateWindow("BUTTON", "Add book", WS_CHILD | WS_VISIBLE, 350, 440, 100, 20, hwnd, (HMENU)IDC_ADDBOOK_SUBMIT_BUTTON, NULL, NULL);
    AddbookToAdminButton = CreateWindow("BUTTON", "Back", WS_CHILD | WS_VISIBLE, 830, 440, 100, 20, hwnd, (HMENU)IDC_ADDBOOK_TOADMIN_BUTTON, NULL, NULL);
    
    UpdateWindow(hwnd);
}