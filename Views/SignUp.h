#include "ViewRepository.h"

#pragma once

void ShowSignupView(HWND hwnd) {
    SignUpUsernameLabel = CreateWindow("STATIC", "Username:", WS_CHILD | WS_VISIBLE, 500, 300, 100, 20, hwnd, (HMENU)IDC_SIGNUP_USERNAME_LABEL, NULL, NULL);
    SignUpUsernameInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 600, 300, 180, 20, hwnd, (HMENU)IDC_SIGNUP_USERNAME_EDIT, NULL, NULL);
    SignUpMailLabel = CreateWindow("STATIC", "Mail:", WS_CHILD | WS_VISIBLE, 500, 340, 100, 20, hwnd, (HMENU)IDC_SIGNUP_MAIL_LABEL, NULL, NULL);
    SignUpMailInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 600, 340, 180, 20, hwnd, (HMENU)IDC_SIGNUP_MAIL_EDIT, NULL, NULL);
    SignUpPasswordLabel = CreateWindow("STATIC", "Password:", WS_CHILD | WS_VISIBLE, 500, 380, 100, 20, hwnd, (HMENU)IDC_SIGNUP_PASSWORD_LABEL, NULL, NULL);
    SignUpPasswordInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 600, 380, 180, 20, hwnd, (HMENU)IDC_SIGNUP_PASSWORD_EDIT, NULL, NULL);
    SignUpSubmitButton = CreateWindow("BUTTON", "SignUp", WS_CHILD | WS_VISIBLE, 500, 420, 100, 20, hwnd, (HMENU)IDC_SIGNUP_SUBMIT_BUTTON, NULL, NULL);
    SignUpToLoginButton = CreateWindow("BUTTON", " LogIn instead", WS_CHILD | WS_VISIBLE, 680, 420, 100, 20, hwnd, (HMENU)IDC_SIGNUP_TOLOGIN_BUTTON, NULL, NULL);
    
    UpdateWindow(hwnd);
}