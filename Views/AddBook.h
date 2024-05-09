#include "../Repositories/ViewRepository.h"

#pragma once

void ShowAddbookView(HWND hwnd) {
    AddbookTitleLabel = CreateWindow("STATIC", "Title:", WS_CHILD | WS_VISIBLE, 350, 280, 100, 20, hwnd, (HMENU)IDC_ADDBOOK_TITLE_LABEL, NULL, NULL);
    AddbookTitleInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 450, 280, 180, 20, hwnd, (HMENU)IDC_ADDBOOK_TITLE_EDIT, NULL, NULL);
    SendMessage(AddbookTitleInput, EM_SETLIMITTEXT, (WPARAM)50, 0);

    AddbookAuthorLabel = CreateWindow("STATIC", "Author:", WS_CHILD | WS_VISIBLE, 350, 320, 100, 20, hwnd, (HMENU)IDC_ADDBOOK_AUTHOR_LABEL, NULL, NULL);
    AddbookAuthorInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 450, 320, 180, 20, hwnd, (HMENU)IDC_ADDBOOK_AUTHOR_EDIT, NULL, NULL);
    SendMessage(AddbookAuthorInput, EM_SETLIMITTEXT, (WPARAM)50, 0);

    AddbookGenreLabel = CreateWindow("STATIC", "Genre:", WS_CHILD | WS_VISIBLE, 350, 360, 100, 20, hwnd, (HMENU)IDC_ADDBOOK_GENRE_LABEL, NULL, NULL);
    AddbookGenreInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 450, 360, 180, 20, hwnd, (HMENU)IDC_ADDBOOK_GENRE_EDIT, NULL, NULL);
    SendMessage(AddbookGenreInput, EM_SETLIMITTEXT, (WPARAM)25, 0);

    AddbookPriceLabel = CreateWindow("STATIC", "Price:", WS_CHILD | WS_VISIBLE, 350, 400, 100, 20, hwnd, (HMENU)IDC_ADDBOOK_PRICE_LABEL, NULL, NULL);
    AddbookPriceInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 450, 400, 180, 20, hwnd, (HMENU)IDC_ADDBOOK_PRICE_EDIT, NULL, NULL);
    SendMessage(AddbookPriceInput, EM_SETLIMITTEXT, (WPARAM)6, 0);

    AddbookQsaleLabel = CreateWindow("STATIC", "Quantity(sale):", WS_CHILD | WS_VISIBLE, 650, 280, 100, 40, hwnd, (HMENU)IDC_ADDBOOK_QSALE_LABEL, NULL, NULL);
    AddbookQsaleInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 280, 180, 40, hwnd, (HMENU)IDC_ADDBOOK_QSALE_EDIT, NULL, NULL);
    SendMessage(AddbookQsaleInput, EM_SETLIMITTEXT, (WPARAM)4, 0);

    AddbookQrentLabel = CreateWindow("STATIC", "Quantity(rent):", WS_CHILD | WS_VISIBLE, 650, 330, 100, 40, hwnd, (HMENU)IDC_ADDBOOK_QRENT_LABEL, NULL, NULL);
    AddbookQrentInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 330, 180, 40, hwnd, (HMENU)IDC_ADDBOOK_QRENT_EDIT, NULL, NULL);
    SendMessage(AddbookQrentInput, EM_SETLIMITTEXT, (WPARAM)4, 0);

    AddbookRdurationLabel = CreateWindow("STATIC", "Rental duration(days):", WS_CHILD | WS_VISIBLE, 650, 380, 100, 40, hwnd, (HMENU)IDC_ADDBOOK_RDURATION_LABEL, NULL, NULL);
    AddbookRdurationInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 380, 180, 40, hwnd, (HMENU)IDC_ADDBOOK_RDURATION_EDIT, NULL, NULL);
    SendMessage(AddbookRdurationInput, EM_SETLIMITTEXT, (WPARAM)4, 0);

    AddbookSubmitButton = CreateWindow("BUTTON", "Add book", WS_CHILD | WS_VISIBLE, 350, 440, 100, 20, hwnd, (HMENU)IDC_ADDBOOK_SUBMIT_BUTTON, NULL, NULL);
    AddbookToAdminButton = CreateWindow("BUTTON", "Back", WS_CHILD | WS_VISIBLE, 830, 440, 100, 20, hwnd, (HMENU)IDC_ADDBOOK_TOADMIN_BUTTON, NULL, NULL);
    
    SetWindowText(AddbookTitleInput, "");
    SetWindowText(AddbookAuthorInput, "");
    SetWindowText(AddbookGenreInput, "");
    SetWindowText(AddbookPriceInput, "");
    SetWindowText(AddbookQsaleInput, "");
    SetWindowText(AddbookQrentInput, "");
    SetWindowText(AddbookRdurationInput, "");
    UpdateWindow(hwnd);
}