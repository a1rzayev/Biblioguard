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
#define IDC_SIGNUP_MAIL_LABEL 202
#define IDC_SIGNUP_PASSWORD_LABEL 203 
#define IDC_SIGNUP_USERNAME_EDIT 204
#define IDC_SIGNUP_MAIL_EDIT 205
#define IDC_SIGNUP_PASSWORD_EDIT 206
#define IDC_SIGNUP_SUBMIT_BUTTON 207    
#define IDC_SIGNUP_TOLOGIN_BUTTON 208


//admin codes
#define IDC_ADMIN_BOOKS_LABEL 301
#define IDC_ADMIN_SCROLLBAR 302
#define IDC_ADMIN_TOLOGIN_BUTTON 303
#define IDC_ADMIN_TOADD_BUTTON 304
#define IDC_ADMIN_EDIT_ID0 10000
#define IDC_ADMIN_DELETE_ID0 20000
#define IDC_ADMIN_TITLE_ID0 30000
#define IDC_ADMIN_DESCRIPTION_ID0 40000

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
HWND SignUpMailLabel; 
HWND SignUpMailInput; 
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

//hiders
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
    ShowWindow(SignUpMailLabel, SW_HIDE);
    ShowWindow(SignUpMailInput, SW_HIDE);
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
