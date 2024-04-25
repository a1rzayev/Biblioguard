#include <windows.h>

#pragma once

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


//hiders
void hideLogInView(){
    ShowWindow(LogInUsernameLabel, SW_HIDE);
    ShowWindow(LogInUsernameInput, SW_HIDE);
    ShowWindow(LogInPasswordLabel, SW_HIDE);
    ShowWindow(LogInPasswordInput, SW_HIDE);
    ShowWindow(LogInToSignupButton, SW_HIDE);
    ShowWindow(LogInConfirmButton, SW_HIDE);
}

void hideSignUpView(){
    ShowWindow(SignUpUsernameLabel, SW_HIDE);
    ShowWindow(SignUpUsernameInput, SW_HIDE);
    ShowWindow(SignUpMailLabel, SW_HIDE);
    ShowWindow(SignUpMailInput, SW_HIDE);
    ShowWindow(SignUpPasswordLabel, SW_HIDE);
    ShowWindow(SignUpPasswordInput, SW_HIDE);
    ShowWindow(SignUpToLoginButton, SW_HIDE);
    ShowWindow(SignUpSubmitButton, SW_HIDE);
}
