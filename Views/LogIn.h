#include "ViewRepository.h"

#pragma once

void ShowLoginPage(HWND hwnd) {
    LogInUsernameLabel = CreateWindow("STATIC", "Username:", WS_CHILD | WS_VISIBLE, 50, 150, 100, 20, hwnd, (HMENU)IDC_LOGIN_USERNAME_LABEL, NULL, NULL);
    LogInUsernameInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 150, 150, 20, hwnd, (HMENU)IDC_LOGIN_USERNAME_EDIT, NULL, NULL);
    LogInPasswordLabel = CreateWindow("STATIC", "Password:", WS_CHILD | WS_VISIBLE, 50, 200, 100, 20, hwnd, (HMENU)IDC_LOGIN_PASSWORD_LABEL, NULL, NULL);
    LogInPasswordInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 150, 200, 150, 20, hwnd, (HMENU)IDC_LOGIN_PASSWORD_EDIT, NULL, NULL);
    LogInConfirmButton = CreateWindow("BUTTON", "LogIn", WS_CHILD | WS_VISIBLE, 100, 300, 100, 30, hwnd, (HMENU)IDC_LOGIN_SUBMIT_BUTTON, NULL, NULL);
    LogInToSignupButton = CreateWindow("BUTTON", "Signup instead", WS_CHILD | WS_VISIBLE, 200, 300, 100, 30, hwnd, (HMENU)IDC_LOGIN_TOSIGNUP_BUTTON, NULL, NULL);
    hideSignUpView();

    // Show the login page controls
    ShowWindow(LogInUsernameLabel, SW_SHOW);
    ShowWindow(LogInUsernameInput, SW_SHOW);
    ShowWindow(LogInPasswordLabel, SW_SHOW);
    ShowWindow(LogInPasswordInput, SW_SHOW);
    ShowWindow(LogInToSignupButton, SW_SHOW);
    ShowWindow(LogInConfirmButton, SW_SHOW);
    UpdateWindow(hwnd);
}