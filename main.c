#include "Views/LogIn.h"
#include "Views/SignUp.h"
#include "Views/Admin.h"
#include <string.h>
#include "Views/Home.h"
#include "Repositories/BookRepository.h"
#include "Views/AddBook.h"
#include "Views/EditBook.h"
#include "Views/UserBooks.h"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    initFileSystem();
    initBookSystem();

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
    SetClassLongPtr(hwnd, GCLP_HICON, (LONG_PTR) LoadIcon(hInstance, MAKEINTRESOURCE(480))); 



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
                case IDC_EDIT_SUBMIT_BUTTON:
                    char titleE[50];
                    char authorE[50];
                    char genreE[20];
                    char priceCharE[5];
                    char quantitySCharE[4];
                    char quantityRCharE[4];
                    char rentalDCharE[4];
                    GetWindowText(EditTitleInput, titleE, sizeof(titleE));
                    GetWindowText(EditAuthorInput, authorE, sizeof(authorE));
                    GetWindowText(EditGenreInput, genreE, sizeof(genreE));
                    GetWindowText(EditPriceInput, priceCharE, sizeof(priceCharE));
                    GetWindowText(EditQsaleInput, quantitySCharE, sizeof(quantitySCharE));
                    GetWindowText(EditQrentInput, quantityRCharE, sizeof(quantityRCharE));
                    GetWindowText(EditRdurationInput, rentalDCharE, sizeof(rentalDCharE));

                    char resultE = isCorrectBookInfo(titleE, authorE, genreE, priceCharE,
                                                    quantitySCharE, quantityRCharE, rentalDCharE);

                    //if(resultE == 2)
                    //    MessageBox(hwnd, "This title is already taken", "Error!", MB_OK | MB_ICONERROR);
                    if(resultE == 1)
                        MessageBox(hwnd, "Fill all spaces", "Error!", MB_OK | MB_ICONERROR);
                    else if(resultE == 3)
                        MessageBox(hwnd, "Write correct numbers", "Error!", MB_OK | MB_ICONERROR);
                    else {
                        //Addbook(usernameS, nameS, surnameS, passwordS);
                        HideEditView(hwnd);
                        ShowAdminView(hwnd);
                    }
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

                    char resultS = isCorrectSignupInfo(usernameS, nameS, surnameS, passwordS);
                    
                    if(resultS == 2)
                        MessageBox(hwnd, "This username is already taken", "Error!", MB_OK | MB_ICONERROR);
                    else if(resultS == 1)
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
                    char titleA[51];
                    char authorA[26];
                    char genreA[26];
                    char priceCharA[10];
                    char quantitySCharA[5];
                    char quantityRCharA[5];
                    char rentalDCharA[5];
            
                    GetWindowText(AddbookTitleInput, titleA, sizeof(titleA));
                    GetWindowText(AddbookAuthorInput, authorA, sizeof(authorA));
                    GetWindowText(AddbookGenreInput, genreA, sizeof(genreA));
                    GetWindowText(AddbookPriceInput, priceCharA, sizeof(priceCharA));
                    GetWindowText(AddbookQsaleInput, quantitySCharA, sizeof(quantitySCharA));
                    GetWindowText(AddbookQrentInput, quantityRCharA, sizeof(quantityRCharA));
                    GetWindowText(AddbookRdurationInput, rentalDCharA, sizeof(rentalDCharA));

                    char resultA = isCorrectBookInfo(titleA, authorA, genreA, priceCharA,
                                                    quantitySCharA, quantityRCharA, rentalDCharA);
                    
                    if(resultA == 2)
                        MessageBox(hwnd, "This title is already taken", "Error!", MB_OK | MB_ICONERROR);
                    else if(resultA == 1)
                        MessageBox(hwnd, "Fill all spaces", "Error!", MB_OK | MB_ICONERROR);
                    else if(resultA == 3)
                        MessageBox(hwnd, "Write correct numbers", "Error!", MB_OK | MB_ICONERROR);
                    else {
                        AddBook(titleA, authorA, genreA, priceCharA, quantitySCharA, quantityRCharA, rentalDCharA);
                        HideAddbookView(hwnd);
                        ShowAdminView(hwnd);
                    }
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
            if ((HWND)lParam == AdminScrollbar) {
            case IDC_ADMIN_SCROLLBAR:
                SCROLLINFO adminSi;
                adminSi.cbSize = sizeof(adminSi);
                adminSi.fMask = SIF_ALL;
                GetScrollInfo(AdminScrollbar, SB_CTL, &adminSi);
                int AdminScrollPos = adminSi.nPos;

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

                break;
            }
            else if ((HWND)lParam == UserbooksScrollbar) {
                SCROLLINFO userbooksSi;
                userbooksSi.cbSize = sizeof(userbooksSi);
                userbooksSi.fMask = SIF_ALL;
                GetScrollInfo(UserbooksScrollbar, SB_CTL, &userbooksSi);
                int UserbooksScrollPos = userbooksSi.nPos;

                switch (LOWORD(wParam)) {
                case SB_TOP:
                    UserbooksScrollPos = 0;
                    break;
                case SB_BOTTOM:
                    UserbooksScrollPos = userbooksBooksCount - userbooksVisibleBooksCount;
                    break;
                case SB_LINEUP:
                    UserbooksScrollPos = max(0, UserbooksScrollPos - 1);
                    break;
                case SB_LINEDOWN:
                    UserbooksScrollPos = min(userbooksBooksCount - userbooksVisibleBooksCount, UserbooksScrollPos + 1);
                    break;
                case SB_PAGEUP:
                    UserbooksScrollPos = max(0, UserbooksScrollPos - userbooksVisibleBooksCount);
                    break;
                case SB_PAGEDOWN:
                    UserbooksScrollPos = min(userbooksBooksCount - userbooksVisibleBooksCount, UserbooksScrollPos + userbooksVisibleBooksCount);
                    break;
                case SB_THUMBTRACK:
                    UserbooksScrollPos = userbooksSi.nTrackPos;
                    break;
                }
                if (UserbooksScrollPos != userbooksSi.nPos) {
                    SetScrollPos(UserbooksScrollbar, SB_CTL, UserbooksScrollPos, TRUE);
                    userbooksScrollPos = UserbooksScrollPos;
                    UpdateUserbooksBookLabels(hwnd);
                }

                break;
            }

            else if ((HWND)lParam == HomeScrollbar) {
                SCROLLINFO homeSi;
                homeSi.cbSize = sizeof(homeSi);
                homeSi.fMask = SIF_ALL;
                GetScrollInfo(HomeScrollbar, SB_CTL, &homeSi);
                int HomeScrollPos = homeSi.nPos;

                switch (LOWORD(wParam)) {
                    case SB_TOP:
                        HomeScrollPos = 0;
                        break;
                    case SB_BOTTOM:
                        HomeScrollPos = homeBooksCount - homeVisibleBooksCount;
                        break;
                    case SB_LINEUP:
                        HomeScrollPos = max(0, HomeScrollPos - 1);
                        break;
                    case SB_LINEDOWN:
                        HomeScrollPos = min(homeBooksCount - homeVisibleBooksCount, HomeScrollPos + 1);
                        break;
                    case SB_PAGEUP:
                        HomeScrollPos = max(0, HomeScrollPos - homeVisibleBooksCount);
                        break;
                    case SB_PAGEDOWN:
                        HomeScrollPos = min(homeBooksCount - homeVisibleBooksCount, HomeScrollPos + homeVisibleBooksCount);
                        break;
                    case SB_THUMBTRACK:
                        HomeScrollPos = homeSi.nTrackPos;
                        break;
                }
                if (HomeScrollPos != homeSi.nPos) {
                    SetScrollPos(HomeScrollbar, SB_CTL, HomeScrollPos, TRUE);
                    homeScrollPos = HomeScrollPos;
                    UpdateHomeBookLabels(hwnd);
                }
                break;
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
