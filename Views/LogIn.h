#include "../Repositories/ViewRepository.h"
#include "../Repositories/BookRepository.h"

#pragma once


void ShowLoginView(HWND hwnd) {
    LogInUsernameLabel = CreateWindow("STATIC", "Username:", WS_CHILD | WS_VISIBLE, 500, 300, 100, 20, hwnd, (HMENU)IDC_LOGIN_USERNAME_LABEL, NULL, NULL);
    LogInUsernameInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 600, 300, 180, 20, hwnd, (HMENU)IDC_LOGIN_USERNAME_EDIT, NULL, NULL);
    SendMessage(LogInUsernameInput, EM_SETLIMITTEXT, (WPARAM)20, 0);

    LogInPasswordLabel = CreateWindow("STATIC", "Password:", WS_CHILD | WS_VISIBLE, 500, 340, 100, 20, hwnd, (HMENU)IDC_LOGIN_PASSWORD_LABEL, NULL, NULL);
    LogInPasswordInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_PASSWORD, 600, 340, 180, 20, hwnd, (HMENU)IDC_LOGIN_PASSWORD_EDIT, NULL, NULL);
    SendMessage(LogInPasswordInput, EM_SETLIMITTEXT, (WPARAM)20, 0);

    LogInConfirmButton = CreateWindow("BUTTON", "LogIn", WS_CHILD | WS_VISIBLE, 500, 380, 100, 20, hwnd, (HMENU)IDC_LOGIN_SUBMIT_BUTTON, NULL, NULL);
    LogInToSignupButton = CreateWindow("BUTTON", "Signup instead", WS_CHILD | WS_VISIBLE, 680, 380, 100, 20, hwnd, (HMENU)IDC_LOGIN_TOSIGNUP_BUTTON, NULL, NULL);
    
    SetWindowText(LogInUsernameInput, "");
    SetWindowText(LogInPasswordInput, "");
    UpdateWindow(hwnd);
}