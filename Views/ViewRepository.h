#include <windows.h>

#pragma once

#define MAIN 1

#define MAX_BOOKS 100
#define BOOK_HEIGHT 30
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
#define IDC_ADMIN_EDIT_ID0 10000
#define IDC_ADMIN_DELETE_ID0 20000
#define IDC_ADMIN_TITLE_ID0 30000
#define IDC_ADMIN_DESCRIPTION_ID0 40000


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

//admin elements
HWND AdminBooksLabel;
HWND AdminBooksListLabel[MAX_BOOKS * 4];
HWND AdminScrollbar;
HWND AdminToLoginButton;
HWND AdminToAddButton;

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



//hiders
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
    UpdateWindow(hwnd);
}
