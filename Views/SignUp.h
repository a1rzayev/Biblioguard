#include "ViewRepository.h"

#pragma once

void ShowSignupView(HWND hwnd) {
    HideLogInView();
    SignUpUsernameLabel = CreateWindow("STATIC", "Username:", WS_CHILD | WS_VISIBLE, 50, 150, 100, 20, hwnd, (HMENU)IDC_SIGNUP_USERNAME_LABEL, NULL, NULL);
    SignUpUsernameInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 150, 150, 20, hwnd, (HMENU)IDC_SIGNUP_USERNAME_EDIT, NULL, NULL);
    SignUpMailLabel = CreateWindow("STATIC", "Mail:", WS_CHILD | WS_VISIBLE, 50, 200, 100, 20, hwnd, (HMENU)IDC_SIGNUP_USERNAME_EDIT, NULL, NULL);
    SignUpMailInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 200, 150, 20, hwnd, (HMENU)IDC_SIGNUP_MAIL_EDIT, NULL, NULL);
    SignUpPasswordLabel = CreateWindow("STATIC", "Password:", WS_CHILD | WS_VISIBLE, 50, 250, 100, 20, hwnd, (HMENU)IDC_SIGNUP_PASSWORD_LABEL, NULL, NULL);
    SignUpUsernameInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 250, 150, 20, hwnd, (HMENU)IDC_SIGNUP_PASSWORD_EDIT, NULL, NULL);
    SignUpSubmitButton = CreateWindow("BUTTON", "SignUp", WS_CHILD | WS_VISIBLE, 100, 300, 100, 30, hwnd, (HMENU)IDC_SIGNUP_SUBMIT_BUTTON, NULL, NULL);
    SignUpToLoginButton = CreateWindow("BUTTON", " LogIn instead", WS_CHILD | WS_VISIBLE, 200, 300, 100, 30, hwnd, (HMENU)IDC_SIGNUP_TOLOGIN_BUTTON, NULL, NULL);
    

    ShowWindow(SignUpUsernameLabel, SW_SHOW);
    ShowWindow(SignUpUsernameInput, SW_SHOW);
    ShowWindow(SignUpMailLabel, SW_SHOW);
    ShowWindow(SignUpMailInput, SW_SHOW);
    ShowWindow(SignUpPasswordLabel, SW_SHOW);
    ShowWindow(SignUpPasswordInput, SW_SHOW);
    ShowWindow(SignUpToLoginButton, SW_SHOW);
    ShowWindow(SignUpSubmitButton, SW_SHOW);
    UpdateWindow(hwnd);
}