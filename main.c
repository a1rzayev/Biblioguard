#include "Views/LogIn.h"
#include <stdio.h>
#include "Views/SignUp.h"
#include "Views/Admin.h"
#include <string.h>
#include "Views/Home.h"
#include "BookRepository.h"
#include "Views/AddBook.h"
#include "Views/EditBook.h"
#include "Views/UserBooks.h"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Biblioguard";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);
    //HICON icon = LoadIcon(NULL, IDI_QUESTION);
    //HDC hdc;
    //DrawIcon(hdc, 10, 20, icon); 

    HWND hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        wc.lpszClassName,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        return 0;
    }
    SetClassLongPtr(hwnd, GCLP_HICON, (LONG_PTR) LoadIcon(hInstance, MAKEINTRESOURCE(480))); 
    // HICON hIcon = (HICON)LoadImage(hInstance, "icon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    // SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    // SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);



    ShowLoginView(hwnd); // show login page initially

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_COMMAND:
            int buttonID = LOWORD(wParam);
            if (buttonID >= IDC_ADMIN_EDIT_ID0 && buttonID <= IDC_ADMIN_EDIT_ID0 + MAX_BOOKS - 1) {
                int buttonIndex = buttonID - IDC_ADMIN_EDIT_ID0;
                HideAdminView(hwnd);
                ShowEditView(hwnd, buttonIndex);
                printf("edit button %d clicked!\n", buttonIndex);

            }
            else if (buttonID >= IDC_ADMIN_DELETE_ID0 && buttonID <= IDC_ADMIN_DELETE_ID0 + MAX_BOOKS - 1) {
                int buttonIndex = buttonID - IDC_ADMIN_DELETE_ID0;
                printf("delete button %d clicked!\n", buttonIndex);
            }

            switch (LOWORD(wParam)) {
                //edit lifetime
                case IDC_EDIT_TOADMIN_BUTTON:
                    HideEditView(hwnd);
                    ShowAdminView(hwnd);
                    break;
                //signup lifetime   
                case IDC_LOGIN_TOSIGNUP_BUTTON:
                    HideLoginView(hwnd);
                    ShowSignupView(hwnd);
                    break;
                case IDC_SIGNUP_SUBMIT_BUTTON:
                    char usernameS[20];
                    char nameS[20];
                    char surnameS[20];
                    char passwordS[20];
                    GetWindowText(SignUpUsernameInput, usernameS, sizeof(usernameS));
                    GetWindowText(SignUpNameInput, nameS, sizeof(nameS));
                    GetWindowText(SignUpSurnameInput, surnameS, sizeof(surnameS));
                    GetWindowText(SignUpPasswordInput, passwordS, sizeof(passwordS));
                    
                    if(!isAvailableUsername(usernameS) || !strcmp(usernameS, "admin")) 
                        MessageBox(hwnd, "This username is already taken", "Error!", MB_OK | MB_ICONERROR);
                    else if(!strcmp(usernameS, "") || !strcmp(nameS, "") || !strcmp(surnameS, "") || !strcmp(passwordS, ""))
                        MessageBox(hwnd, "Fill all spaces", "Error!", MB_OK | MB_ICONERROR);
                    else {
                        SignUp(usernameS, nameS, surnameS, passwordS);
                        HideSignupView(hwnd);
                        ShowHomeView(hwnd);
                    }
                    break;
                case IDC_SIGNUP_TOLOGIN_BUTTON:     
                    HideSignupView(hwnd);
                    ShowLoginView(hwnd);
                    break;

                //admin lifetime
                case IDC_LOGIN_SUBMIT_BUTTON:
                    char usernameL[20];
                    char passwordL[20];
                    GetWindowText(LogInUsernameInput, usernameL, sizeof(usernameL));
                    GetWindowText(LogInPasswordInput, passwordL, sizeof(passwordL));
                    if(!strcmp(usernameL, "admin") && !strcmp(passwordL, "admin123")) {
                        HideLoginView(hwnd);
                        ShowAdminView(hwnd);
                    }
                    else if(isCorrectLogin(usernameL, passwordL)){
                        HideLoginView(hwnd);
                        ShowHomeView(hwnd);
                    }
                    else MessageBox(hwnd, "Wrong username or password", "Error!", MB_OK | MB_ICONERROR);
                    break;      
                
                case IDC_ADMIN_TOLOGIN_BUTTON:
                    HideAdminView(hwnd);
                    currentUser = NULL;
                    ShowLoginView(hwnd);
                    break;

                //addbook lifetime
                case IDC_ADMIN_TOADD_BUTTON:
                    HideAdminView(hwnd);
                    ShowAddbookView(hwnd);
                    break;
                case IDC_ADDBOOK_SUBMIT_BUTTON:
                    // char titleA[50];
                    // char authorA[50];
                    // GetWindowText(LogInUsernameInput, titleA, sizeof(titleA));
                    // GetWindowText(LogInPasswordInput, authorA, sizeof(authorA));
                    // if(!strcmp(usernameL, "admin") && !strcmp(passwordL, "admin123")) {
                    //     //AddBook();
                    //     HideAddbookView(hwnd);
                    //     ShowAdminView(hwnd);
                    // }
                    // else MessageBox(hwnd, "Wrong info", "Error!", MB_OK | MB_ICONERROR);
                    break;
                case IDC_ADDBOOK_TOADMIN_BUTTON:
                    HideAddbookView(hwnd);
                    ShowAdminView(hwnd);
                    break;
                case IDC_HOME_TOLOGIN_BUTTON:
                    HideHomeView(hwnd);
                    ShowLoginView(hwnd);
                    break;
                case IDC_HOME_TOUSERBOOKS_BUTTON:
                    HideHomeView(hwnd);
                    ShowUserbooksView(hwnd);
                    break;
                case IDC_USERBOOKS_TOHOME_BUTTON:
                    HideUserbooksView(hwnd);
                    ShowHomeView(hwnd);
                    break;
            }
            break;
        case WM_VSCROLL: 
            // process scrollbar messages
            SCROLLINFO adminSi;
            adminSi.cbSize = sizeof(adminSi);
            adminSi.fMask = SIF_ALL;
            GetScrollInfo(AdminScrollbar, SB_CTL, &adminSi);
            int AdminScrollPos = adminSi.nPos;

            SCROLLINFO userbooksSi;
            userbooksSi.cbSize = sizeof(userbooksSi);
            userbooksSi.fMask = SIF_ALL;
            GetScrollInfo(UserbooksScrollbar, SB_CTL, &userbooksSi);
            int UserbooksScrollPos = userbooksSi.nPos;

            SCROLLINFO homeSi;
            homeSi.cbSize = sizeof(homeSi);
            homeSi.fMask = SIF_ALL;
            GetScrollInfo(HomeScrollbar, SB_CTL, &homeSi);
            int HomeScrollPos = homeSi.nPos;


            switch (LOWORD(wParam)) {
                case SB_TOP:
                    AdminScrollPos = 0;
                    break;
                case SB_BOTTOM:
                    AdminScrollPos = adminBooksCount - adminVisibleBooksCount;
                    break;
                case SB_LINEUP:
                    AdminScrollPos = max(0, AdminScrollPos - 1);
                    break;
                case SB_LINEDOWN:
                    AdminScrollPos = min(adminBooksCount - adminVisibleBooksCount, AdminScrollPos + 1);
                    break;
                case SB_PAGEUP:
                    AdminScrollPos = max(0, AdminScrollPos - adminVisibleBooksCount);
                    break;
                case SB_PAGEDOWN:
                    AdminScrollPos = min(adminBooksCount - adminVisibleBooksCount, AdminScrollPos + adminVisibleBooksCount);
                    break;
                case SB_THUMBTRACK:
                    AdminScrollPos = adminSi.nTrackPos;
                    break;
            }

            if (AdminScrollPos != adminSi.nPos) {
                SetScrollPos(AdminScrollbar, SB_CTL, AdminScrollPos, TRUE);
                adminScrollPos = AdminScrollPos;
                UpdateAdminBookLabels(hwnd);
            }





            switch (LOWORD(wParam)) {
                case SB_TOP:
                    UserbooksScrollbar = 0;
                    break;
                case SB_BOTTOM:
                    UserbooksScrollbar = userbooksBooksCount - userbooksVisibleBooksCount;
                    break;
                case SB_LINEUP:
                    UserbooksScrollbar = max(0, UserbooksScrollPos - 1);
                    break;
                case SB_LINEDOWN:
                    UserbooksScrollbar = min(userbooksBooksCount - userbooksVisibleBooksCount, UserbooksScrollPos + 1);
                    break;
                case SB_PAGEUP:
                    UserbooksScrollbar = max(0, UserbooksScrollPos - userbooksVisibleBooksCount);
                    break;
                case SB_PAGEDOWN:
                    UserbooksScrollbar = min(userbooksBooksCount - userbooksVisibleBooksCount, UserbooksScrollPos + userbooksVisibleBooksCount);
                    break;
                case SB_THUMBTRACK:
                    UserbooksScrollbar = userbooksSi.nTrackPos;
                    break;
            }
            if (UserbooksScrollPos != userbooksSi.nPos) {
                SetScrollPos(UserbooksScrollbar, SB_CTL, UserbooksScrollPos, TRUE);
                userbooksScrollPos = UserbooksScrollPos;
                UpdateUserbooksBookLabels(hwnd);
            }



            switch (LOWORD(wParam)) {
                case SB_TOP:
                    HomeScrollbar = 0;
                    break;
                case SB_BOTTOM:
                    HomeScrollbar = homeBooksCount - homeVisibleBooksCount;
                    break;
                case SB_LINEUP:
                    HomeScrollbar = max(0, HomeScrollPos - 1);
                    break;
                case SB_LINEDOWN:
                    HomeScrollbar = min(homeBooksCount - homeVisibleBooksCount, HomeScrollPos + 1);
                    break;
                case SB_PAGEUP:
                    HomeScrollbar = max(0, HomeScrollPos - homeVisibleBooksCount);
                    break;
                case SB_PAGEDOWN:
                    HomeScrollbar = min(homeBooksCount - homeVisibleBooksCount, HomeScrollPos + homeVisibleBooksCount);
                    break;
                case SB_THUMBTRACK:
                    HomeScrollbar = homeSi.nTrackPos;
                    break;
            }
            if (HomeScrollPos != homeSi.nPos) {
                SetScrollPos(HomeScrollbar, SB_CTL, HomeScrollPos, TRUE);
                homeScrollPos = HomeScrollPos;
                UpdateHomeBookLabels(hwnd);
            }
            
            break;
        case WM_GETMINMAXINFO: {
            MINMAXINFO* lpMMI = (MINMAXINFO*)lParam;
            lpMMI->ptMaxTrackSize.x = 1280;
            lpMMI->ptMaxTrackSize.y = 720;
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
