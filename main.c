#include "Views/LogIn.h"
#include "Views/SignUp.h"
//#include "Views/Home.h"



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
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        return 0;
    }


    ShowLoginPage(hwnd); // Show login page initially

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
            switch (LOWORD(wParam)) {
                case IDC_SIGNUP_TOLOGIN_BUTTON:
                    ShowLoginPage(hwnd);
                    break;
                case IDC_LOGIN_TOSIGNUP_BUTTON:
                    ShowSignupPage(hwnd);
                    break;
                case IDC_SIGNUP_SUBMIT_BUTTON:
                    MessageBox(hwnd, "SIGNED UP!", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
                case IDC_LOGIN_SUBMIT_BUTTON:
                    MessageBox(hwnd, "LOGGED IN!", "Info", MB_OK | MB_ICONINFORMATION);
                    break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}