#include "Views/LogIn.h"
#include <stdio.h>
#include "Views/SignUp.h"
#include "Views/Admin.h"
#include <string.h>
#include "Views/Home.h"



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Biblioguard";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

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


    ShowLoginView(hwnd); // Show login page initially

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
                printf("edit button %d clicked!\n", buttonIndex);
            }
            else if (buttonID >= IDC_ADMIN_DELETE_ID0 && buttonID <= IDC_ADMIN_DELETE_ID0 + MAX_BOOKS - 1) {
                int buttonIndex = buttonID - IDC_ADMIN_DELETE_ID0;
                printf("delete button %d clicked!\n", buttonIndex);
            }
            switch (LOWORD(wParam)) {
                case IDC_SIGNUP_TOLOGIN_BUTTON:     
                    HideSignupView(hwnd);
                    ShowLoginView(hwnd);
                    break;
                case IDC_LOGIN_TOSIGNUP_BUTTON:
                    // char username1[256];
                    // char password1[256];
                    // HWND username1Edit = GetDlgItem(hwnd, IDC_LOGIN_USERNAME_EDIT);
                    // HWND password1Edit = GetDlgItem(hwnd, IDC_LOGIN_PASSWORD_EDIT);
                    // GetWindowText(username1Edit, username1, sizeof(username1));
                    // GetWindowText(password1Edit, password1, sizeof(password1));
                    // MessageBox(hwnd, username1, password1, MB_OK | MB_ICONINFORMATION);
                    // SetWindowText(username1Edit, "");
                    // SetWindowText(password1Edit, "");
                    HideLoginView(hwnd);
                    ShowSignupView(hwnd);
                    break;
                case IDC_SIGNUP_SUBMIT_BUTTON:
                    break;
                case IDC_LOGIN_SUBMIT_BUTTON:
                    char username[256];
                    char password[256];
                    GetWindowText(LogInUsernameInput, username, sizeof(username));
                    GetWindowText(LogInPasswordInput, password, sizeof(password));
                    if(!strcmp(username, "admin") && !strcmp(password, "admin123")) {
                        HideLoginView(hwnd);
                        ShowAdminView(hwnd);
                    }
                    else MessageBox(hwnd, username, password, MB_OK | MB_ICONINFORMATION);
                    break;
                case IDC_ADMIN_TOLOGIN_BUTTON:
                    HideAdminView(hwnd);
                    ShowLoginView(hwnd);
                    break;
                //case 
            }
            break;
        case WM_VSCROLL: 
            // Process scrollbar messages
            SCROLLINFO si;
            si.cbSize = sizeof(si);
            si.fMask = SIF_ALL;
            GetScrollInfo(AdminScrollbar, SB_CTL, &si);
            int nScrollPos = si.nPos;

            switch (LOWORD(wParam)) {
                case SB_TOP:
                    nScrollPos = 0;
                    break;
                case SB_BOTTOM:
                    nScrollPos = booksCount - visibleBooksCount;
                    break;
                case SB_LINEUP:
                    nScrollPos = max(0, nScrollPos - 1);
                    break;
                case SB_LINEDOWN:
                    nScrollPos = min(booksCount - visibleBooksCount, nScrollPos + 1);
                    break;
                case SB_PAGEUP:
                    nScrollPos = max(0, nScrollPos - visibleBooksCount);
                    break;
                case SB_PAGEDOWN:
                    nScrollPos = min(booksCount - visibleBooksCount, nScrollPos + visibleBooksCount);
                    break;
                case SB_THUMBTRACK:
                    nScrollPos = si.nTrackPos;
                    break;
            }

            if (nScrollPos != si.nPos) {
                SetScrollPos(AdminScrollbar, SB_CTL, nScrollPos, TRUE);
                scrollPos = nScrollPos;
                UpdateBookLabels(hwnd);
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