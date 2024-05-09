#include <windows.h>

#pragma once

#define MAIN 1

#define MAX_BOOKS 100
#define MAX_REPORTS 1000
#define BOOK_HEIGHT 30
#define REPORT_HEIGHT 30
#define SCROLLBAR_WIDTH 20

//login codes
#define IDC_LOGIN_USERNAME_LABEL 101
#define IDC_LOGIN_PASSWORD_LABEL 103 
#define IDC_LOGIN_USERNAME_EDIT 104
#define IDC_LOGIN_PASSWORD_EDIT 105
#define IDC_LOGIN_SUBMIT_BUTTON 106
#define IDC_LOGIN_TOSIGNUP_BUTTON 107


//signup codes
#define IDC_SIGNUP_USERNAME_LABEL 201
#define IDC_SIGNUP_NAME_LABEL 202
#define IDC_SIGNUP_PASSWORD_LABEL 203 
#define IDC_SIGNUP_USERNAME_EDIT 204
#define IDC_SIGNUP_NAME_EDIT 205
#define IDC_SIGNUP_PASSWORD_EDIT 206
#define IDC_SIGNUP_SUBMIT_BUTTON 207    
#define IDC_SIGNUP_TOLOGIN_BUTTON 208
#define IDC_SIGNUP_SURNAME_LABEL 209
#define IDC_SIGNUP_SURNAME_EDIT 210


//admin codes
#define IDC_ADMIN_BOOKS_LABEL 301
#define IDC_ADMIN_SCROLLBAR 302
#define IDC_ADMIN_TOLOGIN_BUTTON 303
#define IDC_ADMIN_TOADD_BUTTON 304
#define IDC_ADMIN_TOREPORT_BUTTON 305
#define IDC_ADMIN_EDIT_ID0 1000
#define IDC_ADMIN_DELETE_ID0 21000
#define IDC_ADMIN_TITLE_ID0 3000
#define IDC_ADMIN_DESCRIPTION_ID0 4000

//report codes
#define IDC_REPORT_LABEL 601
#define IDC_REPORT_SCROLLBAR 602
#define IDC_REPORT_TOADMIN_BUTTON 603
#define IDC_REPORT_INFO_ID0 6000


//userbooks codes
#define IDC_USERBOOKS_PURCHASED_LABEL 801
#define IDC_USERBOOKS_RENTED_LABEL 802
#define IDC_USERBOOKS_SCROLLBAR 803
#define IDC_USERBOOKS_TOHOME_BUTTON 804
#define IDC_USERBOOKS_PURCHASED_DELETE_ID0 9000
#define IDC_USERBOOKS_RENTED_DELETE_ID0 10000
#define IDC_USERBOOKS_PURCHASED_TITLE_ID0 11000
#define IDC_USERBOOKS_RENTED_TITLE_ID0 12000
#define IDC_USERBOOKS_PURCHASED_DESCRIPTION_ID0 13000
#define IDC_USERBOOKS_RENTED_DESCRIPTION_ID0 14000


//addbook codes 
#define IDC_ADDBOOK_TITLE_LABEL 401
#define IDC_ADDBOOK_AUTHOR_LABEL 402
#define IDC_ADDBOOK_GENRE_LABEL 403
#define IDC_ADDBOOK_PRICE_LABEL 404
#define IDC_ADDBOOK_QSALE_LABEL 405
#define IDC_ADDBOOK_QRENT_LABEL 406
#define IDC_ADDBOOK_RDURATION_LABEL 407
#define IDC_ADDBOOK_TITLE_EDIT 408
#define IDC_ADDBOOK_AUTHOR_EDIT 409
#define IDC_ADDBOOK_GENRE_EDIT 410
#define IDC_ADDBOOK_PRICE_EDIT 411
#define IDC_ADDBOOK_QSALE_EDIT 412
#define IDC_ADDBOOK_QRENT_EDIT 413
#define IDC_ADDBOOK_RDURATION_EDIT 414
#define IDC_ADDBOOK_SUBMIT_BUTTON 415
#define IDC_ADDBOOK_TOADMIN_BUTTON 416


//edit codes 
#define IDC_EDIT_TITLE_LABEL 501
#define IDC_EDIT_AUTHOR_LABEL 502
#define IDC_EDIT_GENRE_LABEL 503
#define IDC_EDIT_PRICE_LABEL 504
#define IDC_EDIT_QSALE_LABEL 505
#define IDC_EDIT_QRENT_LABEL 506
#define IDC_EDIT_RDURATION_LABEL 507
#define IDC_EDIT_TITLE_EDIT 508
#define IDC_EDIT_AUTHOR_EDIT 509
#define IDC_EDIT_GENRE_EDIT 510
#define IDC_EDIT_PRICE_EDIT 511
#define IDC_EDIT_QSALE_EDIT 512
#define IDC_EDIT_QRENT_EDIT 513
#define IDC_EDIT_RDURATION_EDIT 514
#define IDC_EDIT_SUBMIT_BUTTON 515
#define IDC_EDIT_TOADMIN_BUTTON 516


//home codes
#define IDC_HOME_BOOKS_LABEL 901
#define IDC_HOME_SCROLLBAR 902
#define IDC_HOME_TOLOGIN_BUTTON 903
#define IDC_HOME_TOUSERBOOKS_BUTTON 904
#define IDC_HOME_BUY_ID0 5000
#define IDC_HOME_RENT_ID0 6000
#define IDC_HOME_TITLE_ID0 7000
#define IDC_HOME_DESCRIPTION_ID0 7000


//login elements
HWND LogInUsernameLabel; 
HWND LogInUsernameInput;
HWND LogInPasswordLabel; 
HWND LogInPasswordInput;
HWND LogInToSignupButton; 
HWND LogInConfirmButton; 

//signup elements
HWND SignUpUsernameLabel; 
HWND SignUpUsernameInput; 
HWND SignUpNameLabel; 
HWND SignUpNameInput; 
HWND SignUpSurnameLabel; 
HWND SignUpSurnameInput; 
HWND SignUpPasswordLabel; 
HWND SignUpPasswordInput; 
HWND SignUpToLoginButton; 
HWND SignUpSubmitButton; 

//report elements
HWND ReportLabel;
HWND ReportListLabel[MAX_REPORTS];
HWND ReportScrollbar;
HWND ReportToAdminButton;

//admin elements
HWND AdminBooksLabel;
HWND AdminBooksListLabel[MAX_BOOKS * 4];
HWND AdminScrollbar;
HWND AdminToLoginButton;
HWND AdminToAddButton;
HWND AdminToReportButton;

//userbooks elements
HWND UserbooksPurchasedLabel;
HWND UserbooksRentedLabel;
HWND UserbooksPurchasedListLabel[MAX_BOOKS * 3];
HWND UserbooksRentedListLabel[MAX_BOOKS * 3];
HWND UserbooksScrollbar;
HWND UserbooksToHomeButton;

//home elements
HWND HomeBooksLabel;
HWND HomeBooksListLabel[MAX_BOOKS * 4];
HWND HomeScrollbar;
HWND HomeToLoginButton;
HWND HomeToUserbooksButton;

//addbook elements
HWND AddbookTitleLabel;
HWND AddbookTitleInput;
HWND AddbookAuthorLabel;
HWND AddbookAuthorInput;
HWND AddbookGenreLabel;
HWND AddbookGenreInput;
HWND AddbookPriceLabel;
HWND AddbookPriceInput;
HWND AddbookQsaleLabel;
HWND AddbookQsaleInput;
HWND AddbookQrentLabel;
HWND AddbookQrentInput;
HWND AddbookRdurationLabel;
HWND AddbookRdurationInput;
HWND AddbookSubmitButton;
HWND AddbookToAdminButton;

//edit elements
HWND EditTitleLabel;
HWND EditTitleInput;
HWND EditAuthorLabel;
HWND EditAuthorInput;
HWND EditGenreLabel;
HWND EditGenreInput;
HWND EditPriceLabel;
HWND EditPriceInput;
HWND EditQsaleLabel;
HWND EditQsaleInput;
HWND EditQrentLabel;
HWND EditQrentInput;
HWND EditRdurationLabel;
HWND EditRdurationInput;
HWND EditSubmitButton;
HWND EditToAdminButton;



//hiders
void HideEditView(HWND hwnd){
    ShowWindow(EditTitleLabel, SW_HIDE);
    ShowWindow(EditTitleInput, SW_HIDE);
    ShowWindow(EditAuthorLabel, SW_HIDE);
    ShowWindow(EditAuthorInput, SW_HIDE);
    ShowWindow(EditGenreLabel, SW_HIDE);
    ShowWindow(EditGenreInput, SW_HIDE);
    ShowWindow(EditPriceLabel, SW_HIDE);
    ShowWindow(EditPriceInput, SW_HIDE);
    ShowWindow(EditQsaleLabel, SW_HIDE);
    ShowWindow(EditQsaleInput, SW_HIDE);
    ShowWindow(EditQrentLabel, SW_HIDE);
    ShowWindow(EditQrentInput, SW_HIDE);
    ShowWindow(EditRdurationLabel, SW_HIDE);
    ShowWindow(EditRdurationInput, SW_HIDE);
    ShowWindow(EditSubmitButton, SW_HIDE);
    ShowWindow(EditToAdminButton, SW_HIDE);
    UpdateWindow(hwnd);
}


void HideAddbookView(HWND hwnd){
    ShowWindow(AddbookTitleLabel, SW_HIDE);
    ShowWindow(AddbookTitleInput, SW_HIDE);
    ShowWindow(AddbookAuthorLabel, SW_HIDE);
    ShowWindow(AddbookAuthorInput, SW_HIDE);
    ShowWindow(AddbookGenreLabel, SW_HIDE);
    ShowWindow(AddbookGenreInput, SW_HIDE);
    ShowWindow(AddbookPriceLabel, SW_HIDE);
    ShowWindow(AddbookPriceInput, SW_HIDE);
    ShowWindow(AddbookQsaleLabel, SW_HIDE);
    ShowWindow(AddbookQsaleInput, SW_HIDE);
    ShowWindow(AddbookQrentLabel, SW_HIDE);
    ShowWindow(AddbookQrentInput, SW_HIDE);
    ShowWindow(AddbookRdurationLabel, SW_HIDE);
    ShowWindow(AddbookRdurationInput, SW_HIDE);
    ShowWindow(AddbookSubmitButton, SW_HIDE);
    ShowWindow(AddbookToAdminButton, SW_HIDE);
    UpdateWindow(hwnd);
}


void HideLoginView(HWND hwnd){
    ShowWindow(LogInUsernameLabel, SW_HIDE);
    ShowWindow(LogInUsernameInput, SW_HIDE);
    ShowWindow(LogInPasswordLabel, SW_HIDE);
    ShowWindow(LogInPasswordInput, SW_HIDE);
    ShowWindow(LogInToSignupButton, SW_HIDE);
    ShowWindow(LogInConfirmButton, SW_HIDE);
}

void HideSignupView(HWND hwnd){
    ShowWindow(SignUpUsernameLabel, SW_HIDE);
    ShowWindow(SignUpUsernameInput, SW_HIDE);
    ShowWindow(SignUpNameLabel, SW_HIDE);
    ShowWindow(SignUpNameInput, SW_HIDE);
    ShowWindow(SignUpSurnameLabel, SW_HIDE);
    ShowWindow(SignUpSurnameInput, SW_HIDE);
    ShowWindow(SignUpPasswordLabel, SW_HIDE);
    ShowWindow(SignUpPasswordInput, SW_HIDE);
    ShowWindow(SignUpToLoginButton, SW_HIDE);
    ShowWindow(SignUpSubmitButton, SW_HIDE);
    UpdateWindow(hwnd);
}

void HideAdminBooksList(HWND hwnd){
    for (int i = 0; i < MAX_BOOKS; ++i) {       
        ShowWindow(AdminBooksListLabel[i * 4], SW_HIDE);
        ShowWindow(AdminBooksListLabel[i * 4 + 1], SW_HIDE);
        ShowWindow(AdminBooksListLabel[i * 4 + 2], SW_HIDE);
        ShowWindow(AdminBooksListLabel[i * 4 + 3], SW_HIDE);
    }
}

void HideAdminView(HWND hwnd){
    HideAdminBooksList(hwnd);
    ShowWindow(AdminBooksLabel, SW_HIDE);
    ShowWindow(AdminScrollbar, SW_HIDE);
    ShowWindow(AdminToLoginButton, SW_HIDE);
    ShowWindow(AdminToAddButton, SW_HIDE);
    ShowWindow(AdminToReportButton, SW_HIDE);
    UpdateWindow(hwnd);
}



void HideReportList(HWND hwnd){
    for (int i = 0; i < MAX_REPORTS; ++i) {       
        ShowWindow(ReportListLabel[i], SW_HIDE);
    }
}

void HideReportView(HWND hwnd){
    HideReportList(hwnd);
    ShowWindow(ReportLabel, SW_HIDE);
    ShowWindow(ReportScrollbar, SW_HIDE);
    ShowWindow(ReportToAdminButton, SW_HIDE);
    UpdateWindow(hwnd);
}


void HideHomeBooksList(HWND hwnd){
    for (int i = 0; i < MAX_BOOKS; ++i) {       
        ShowWindow(HomeBooksListLabel[i * 4], SW_HIDE);
        ShowWindow(HomeBooksListLabel[i * 4 + 1], SW_HIDE);
        ShowWindow(HomeBooksListLabel[i * 4 + 2], SW_HIDE);
        ShowWindow(HomeBooksListLabel[i * 4 + 3], SW_HIDE);
    }
}

void HideHomeView(HWND hwnd){
    HideHomeBooksList(hwnd);
    ShowWindow(HomeBooksLabel, SW_HIDE);
    ShowWindow(HomeScrollbar, SW_HIDE);
    ShowWindow(HomeToLoginButton, SW_HIDE);
    ShowWindow(HomeToUserbooksButton, SW_HIDE);
    UpdateWindow(hwnd);
}






void HideUserbooksPurchasedList(HWND hwnd){
    for (int i = 0; i < MAX_BOOKS; ++i) {       
        ShowWindow(UserbooksPurchasedListLabel[i * 3], SW_HIDE);
        ShowWindow(UserbooksPurchasedListLabel[i * 3 + 1], SW_HIDE);
        ShowWindow(UserbooksPurchasedListLabel[i * 3 + 2], SW_HIDE);
    }
}

void HideUserbooksRentedList(HWND hwnd){
    for (int i = 0; i < MAX_BOOKS; ++i) {       
        ShowWindow(UserbooksRentedListLabel[i * 3], SW_HIDE);
        ShowWindow(UserbooksRentedListLabel[i * 3 + 1], SW_HIDE);
        ShowWindow(UserbooksRentedListLabel[i * 3 + 2], SW_HIDE);
    }
}

void HideUserbooksView(HWND hwnd){
    HideUserbooksPurchasedList(hwnd);
    HideUserbooksRentedList(hwnd);
    ShowWindow(UserbooksPurchasedLabel, SW_HIDE);
    ShowWindow(UserbooksRentedLabel, SW_HIDE);
    ShowWindow(UserbooksScrollbar, SW_HIDE);
    ShowWindow(UserbooksToHomeButton, SW_HIDE);
    UpdateWindow(hwnd);
}
