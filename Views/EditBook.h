#include "ViewRepository.h"
#include "../BookRepository.h"

#pragma once

void ShowEditView(HWND hwnd, unsigned int id) {
    
    SetWindowText(EditTitleInput, "");
    SetWindowText(EditAuthorInput, "");
    SetWindowText(EditGenreInput, "");
    SetWindowText(EditPriceInput, "");
    SetWindowText(EditQsaleInput, "");
    SetWindowText(EditQrentInput, "");
    SetWindowText(EditRdurationInput, "");

    char priceChar[5];
    char quantitySChar[4];
    char quantityRChar[4];
    char rentalDChar[4];
    sprintf(priceChar, "%.2f", books[id].price); 
    sprintf(quantitySChar, "%d", books[id].quantityForSale); 
    sprintf(quantityRChar, "%d", books[id].quantityForRent); 
    sprintf(rentalDChar, "%d", books[id].rentalDuration); 

    EditTitleLabel = CreateWindow("STATIC", "Title:", WS_CHILD | WS_VISIBLE, 350, 280, 100, 20, hwnd, (HMENU)IDC_EDIT_TITLE_LABEL, NULL, NULL);
    EditTitleInput = CreateWindow("EDIT", books[id].title, WS_CHILD | WS_VISIBLE | WS_BORDER, 450, 280, 180, 20, hwnd, (HMENU)IDC_EDIT_TITLE_EDIT, NULL, NULL);
    SendMessage(EditTitleInput, EM_SETLIMITTEXT, (WPARAM)50, 0);
    

    EditAuthorLabel = CreateWindow("STATIC", "Author:", WS_CHILD | WS_VISIBLE, 350, 320, 100, 20, hwnd, (HMENU)IDC_EDIT_AUTHOR_LABEL, NULL, NULL);
    EditAuthorInput = CreateWindow("EDIT", books[id].author, WS_CHILD | WS_VISIBLE | WS_BORDER, 450, 320, 180, 20, hwnd, (HMENU)IDC_EDIT_AUTHOR_EDIT, NULL, NULL);
    SendMessage(EditAuthorInput, EM_SETLIMITTEXT, (WPARAM)50, 0);

    EditGenreLabel = CreateWindow("STATIC", "Genre:", WS_CHILD | WS_VISIBLE, 350, 360, 100, 20, hwnd, (HMENU)IDC_EDIT_GENRE_LABEL, NULL, NULL);
    EditGenreInput = CreateWindow("EDIT", books[id].genre, WS_CHILD | WS_VISIBLE | WS_BORDER, 450, 360, 180, 20, hwnd, (HMENU)IDC_EDIT_GENRE_EDIT, NULL, NULL);
    SendMessage(EditGenreInput, EM_SETLIMITTEXT, (WPARAM)25, 0);

    EditPriceLabel = CreateWindow("STATIC", "Price:", WS_CHILD | WS_VISIBLE, 350, 400, 100, 20, hwnd, (HMENU)IDC_EDIT_PRICE_LABEL, NULL, NULL);
    EditPriceInput = CreateWindow("EDIT", priceChar, WS_CHILD | WS_VISIBLE | WS_BORDER, 450, 400, 180, 20, hwnd, (HMENU)IDC_EDIT_PRICE_EDIT, NULL, NULL);
    SendMessage(EditPriceInput, EM_SETLIMITTEXT, (WPARAM)5, 0);

    EditQsaleLabel = CreateWindow("STATIC", "Quantity(sale):", WS_CHILD | WS_VISIBLE, 650, 280, 100, 40, hwnd, (HMENU)IDC_EDIT_QSALE_LABEL, NULL, NULL);
    EditQsaleInput = CreateWindow("EDIT", quantitySChar, WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 280, 180, 40, hwnd, (HMENU)IDC_EDIT_QSALE_EDIT, NULL, NULL);
    SendMessage(EditQsaleInput, EM_SETLIMITTEXT, (WPARAM)4, 0);
    
    EditQrentLabel = CreateWindow("STATIC", "Quantity(rent):", WS_CHILD | WS_VISIBLE, 650, 330, 100, 40, hwnd, (HMENU)IDC_EDIT_QRENT_LABEL, NULL, NULL);
    EditQrentInput = CreateWindow("EDIT", quantityRChar, WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 330, 180, 40, hwnd, (HMENU)IDC_EDIT_QRENT_EDIT, NULL, NULL);
    SendMessage(EditQrentInput, EM_SETLIMITTEXT, (WPARAM)4, 0);
    
    EditRdurationLabel = CreateWindow("STATIC", "Rental duration(days):", WS_CHILD | WS_VISIBLE, 650, 380, 100, 40, hwnd, (HMENU)IDC_EDIT_RDURATION_LABEL, NULL, NULL);
    EditRdurationInput = CreateWindow("EDIT", rentalDChar, WS_CHILD | WS_VISIBLE | WS_BORDER, 750, 380, 180, 40, hwnd, (HMENU)IDC_EDIT_RDURATION_EDIT, NULL, NULL);
    SendMessage(EditRdurationInput, EM_SETLIMITTEXT, (WPARAM)4, 0);

    EditSubmitButton = CreateWindow("BUTTON", "Edit book", WS_CHILD | WS_VISIBLE, 350, 440, 100, 20, hwnd, (HMENU)IDC_EDIT_SUBMIT_BUTTON, NULL, NULL);
    EditToAdminButton = CreateWindow("BUTTON", "Back", WS_CHILD | WS_VISIBLE, 830, 440, 100, 20, hwnd, (HMENU)IDC_EDIT_TOADMIN_BUTTON, NULL, NULL);
    
    UpdateWindow(hwnd);
}