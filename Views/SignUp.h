#include "../Controllers/ViewController.h"

#pragma once

//shows signup view
void ShowSignupView(HWND hwnd);





void ShowSignupView(HWND hwnd) {
    SignUpUsernameLabel = CreateWindow("STATIC", "Username:", WS_CHILD | WS_VISIBLE, 500, 280, 100, 20, hwnd, (HMENU)IDC_SIGNUP_USERNAME_LABEL, NULL, NULL);
    SignUpUsernameInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 600, 280, 180, 20, hwnd, (HMENU)IDC_SIGNUP_USERNAME_EDIT, NULL, NULL);
    SendMessage(SignUpUsernameInput, EM_SETLIMITTEXT, (WPARAM)20, 0);

    SignUpNameLabel = CreateWindow("STATIC", "Name:", WS_CHILD | WS_VISIBLE, 500, 320, 100, 20, hwnd, (HMENU)IDC_SIGNUP_NAME_LABEL, NULL, NULL);
    SignUpNameInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 600, 320, 180, 20, hwnd, (HMENU)IDC_SIGNUP_NAME_EDIT, NULL, NULL);
    SendMessage(SignUpNameInput, EM_SETLIMITTEXT, (WPARAM)20, 0);

    SignUpSurnameLabel = CreateWindow("STATIC", "Surname:", WS_CHILD | WS_VISIBLE, 500, 360, 100, 20, hwnd, (HMENU)IDC_SIGNUP_SURNAME_LABEL, NULL, NULL);
    SignUpSurnameInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 600, 360, 180, 20, hwnd, (HMENU)IDC_SIGNUP_SURNAME_EDIT, NULL, NULL);
    SendMessage(SignUpSurnameInput, EM_SETLIMITTEXT, (WPARAM)20, 0);

    SignUpPasswordLabel = CreateWindow("STATIC", "Password:", WS_CHILD | WS_VISIBLE, 500, 400, 100, 20, hwnd, (HMENU)IDC_SIGNUP_PASSWORD_LABEL, NULL, NULL);
    SignUpPasswordInput = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 600, 400, 180, 20, hwnd, (HMENU)IDC_SIGNUP_PASSWORD_EDIT, NULL, NULL);
    SendMessage(SignUpPasswordInput, EM_SETLIMITTEXT, (WPARAM)20, 0);

    SignUpSubmitButton = CreateWindow("BUTTON", "SignUp", WS_CHILD | WS_VISIBLE, 500, 440, 100, 20, hwnd, (HMENU)IDC_SIGNUP_SUBMIT_BUTTON, NULL, NULL);
    SignUpToLoginButton = CreateWindow("BUTTON", " LogIn instead", WS_CHILD | WS_VISIBLE, 680, 440, 100, 20, hwnd, (HMENU)IDC_SIGNUP_TOLOGIN_BUTTON, NULL, NULL);
    
    SetWindowText(SignUpUsernameInput, "");
    SetWindowText(SignUpNameInput, "");
    SetWindowText(SignUpSurnameInput, "");
    SetWindowText(SignUpPasswordInput, "");
    UpdateWindow(hwnd);
}