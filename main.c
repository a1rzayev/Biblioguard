#include "Views/LogIn.h"
#include "Views/SignUp.h"
#include "Views/Admin.h"
#include <string.h>
#include "Views/Home.h"
#include "Controllers/BookController.h"
#include "Views/AddBook.h"
#include "Views/EditBook.h"
#include "Views/UserBooks.h"
#include "Views/Report.h"





//realizes all event-listeners, exception-handlers
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//main function. creates window, initially starts login-view create message listener(to check each step) 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);





int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    initFileSystem();
    initBookSystem();

    //initialize window 
    WNDCLASS wc = {0}; 
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Biblioguard";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    //show window
    HWND hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        wc.lpszClassName,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
        NULL, NULL, hInstance, NULL);
    if (hwnd == NULL) 
        return 0;
    
    //show login page initially
    ShowLoginView(hwnd);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    //get messages(button-click, text-regocnization and etc.)
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
            //handles dynamic buttons(edit, delete, rent, buy). each book has their own button
            unsigned int buttonIndex = 0;
            unsigned int buttonID = LOWORD(wParam);
            
            //checks dynamic delete buttons
            if (buttonID >= IDC_ADMIN_DELETE_ID0 && buttonID <= IDC_ADMIN_DELETE_ID0 + MAX_BOOKS - 1) {
                unsigned int deleteButtonIndex = buttonID - IDC_ADMIN_DELETE_ID0;
                DeleteBook(deleteButtonIndex);
                HideAdminView(hwnd);
                ShowAdminView(hwnd);
            }
            //checks dynamic edit buttons
            else if (buttonID >= IDC_ADMIN_EDIT_ID0 && buttonID <= IDC_ADMIN_EDIT_ID0 + MAX_BOOKS - 1) {
                unsigned int editButtonIndex = buttonID - IDC_ADMIN_EDIT_ID0 ;
                editingBookOrder = editButtonIndex;
                HideAdminView(hwnd);
                ShowEditView(hwnd, editButtonIndex);
            }
            //checks dynamic rent buttons
            else if (buttonID >= IDC_HOME_RENT_ID0 && buttonID <= IDC_HOME_RENT_ID0 + MAX_BOOKS - 1) {
                unsigned int rentButtonIndex = buttonID - IDC_HOME_RENT_ID0;
                if (RentBook(currentUser->id, rentButtonIndex)) {
                    HideHomeView(hwnd);
                    ShowHomeView(hwnd);
                }
                else MessageBox(hwnd, "Not enough books to rent", "Error!", MB_OK | MB_ICONERROR);
            }
            //checks dynamic buy buttons
            else if (buttonID >= IDC_HOME_BUY_ID0 && buttonID <= IDC_HOME_BUY_ID0 + MAX_BOOKS - 1) {
                unsigned int buyButtonIndex = buttonID - IDC_HOME_BUY_ID0;
                if (BuyBook(currentUser->id, buyButtonIndex)) {
                    HideHomeView(hwnd);
                    ShowHomeView(hwnd);
                }
                else MessageBox(hwnd, "Not enough books to buy", "Error!", MB_OK | MB_ICONERROR);
            }

            //handles constant buttons(that have static value)
            switch (buttonID) {
                //edit events
                case IDC_EDIT_TOADMIN_BUTTON:
                    HideEditView(hwnd);
                    ShowAdminView(hwnd);
                    break;
                case IDC_EDIT_SUBMIT_BUTTON:
                    char titleE[51];
                    char authorE[26];
                    char genreE[26];
                    char priceCharE[10];
                    char quantitySCharE[5];
                    char quantityRCharE[5];
                    char rentalDCharE[5];
                    GetWindowText(EditTitleInput, titleE, sizeof(titleE));
                    GetWindowText(EditAuthorInput, authorE, sizeof(authorE));
                    GetWindowText(EditGenreInput, genreE, sizeof(genreE));
                    GetWindowText(EditPriceInput, priceCharE, sizeof(priceCharE));
                    GetWindowText(EditQsaleInput, quantitySCharE, sizeof(quantitySCharE));
                    GetWindowText(EditQrentInput, quantityRCharE, sizeof(quantityRCharE));
                    GetWindowText(EditRdurationInput, rentalDCharE, sizeof(rentalDCharE));

                    char resultE = isCorrectBookInfo(titleE, authorE, genreE, priceCharE,
                                                    quantitySCharE, quantityRCharE, rentalDCharE);

                    if(resultE == 1)
                        MessageBox(hwnd, "Fill all spaces", "Error!", MB_OK | MB_ICONERROR);
                    else if(resultE == 3)
                        MessageBox(hwnd, "Write correct numbers", "Error!", MB_OK | MB_ICONERROR);
                    else {
                        EditBook(editingBookOrder, titleE, authorE, genreE, priceCharE, quantitySCharE, quantityRCharE, rentalDCharE);
                        HideEditView(hwnd);
                        ShowAdminView(hwnd);
                    }
                    break;
                
                //report events
                case IDC_REPORT_TOADMIN_BUTTON:
                    HideReportView(hwnd);
                    ShowAdminView(hwnd);
                    break;

                //signup events   
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

                //login events
                case IDC_LOGIN_TOSIGNUP_BUTTON:
                    HideLoginView(hwnd);
                    ShowSignupView(hwnd);
                    break;
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

                //admin events    
                case IDC_ADMIN_TOREPORT_BUTTON:
                    getReports();
                    HideAdminView(hwnd);
                    ShowReportView(hwnd);
                    break;     
                case IDC_ADMIN_PRICESORT_BUTTON:
                    SortBooksByPriceD();
                    HideAdminView(hwnd);
                    ShowAdminView(hwnd);
                    break;
                case IDC_ADMIN_POPULARITYSORT_BUTTON:
                    SortBooksByPopularityD();
                    HideAdminView(hwnd);
                    ShowAdminView(hwnd);
                    break;
                case IDC_ADMIN_TOLOGIN_BUTTON:
                    HideAdminView(hwnd);
                    ShowLoginView(hwnd);
                    break;
                case IDC_ADMIN_TOADD_BUTTON:
                    HideAdminView(hwnd);
                    ShowAddbookView(hwnd);
                    break;

                //addbook events
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

                //home events
                case IDC_HOME_TOLOGIN_BUTTON:
                    HideHomeView(hwnd);
                    ShowLoginView(hwnd);
                    break;
                case IDC_HOME_PRICESORT_BUTTON:
                    SortBooksByPriceD();
                    HideHomeView(hwnd);
                    ShowHomeView(hwnd);
                    break;
                case IDC_HOME_POPULARITYSORT_BUTTON:
                    SortBooksByPopularityD();
                    HideHomeView(hwnd);
                    ShowHomeView(hwnd);
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
            //scrollbar calculations for admin view
            if ((HWND)lParam == AdminScrollbar) {
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

            //scrollbar calculations for userbooks view
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
                    UpdateUserbooksBookLabelsR(hwnd);
                    UpdateUserbooksBookLabelsB(hwnd);
                }

                break;
            }

            //scrollbar calculations for home view
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
            //scrollbar calculations for report view
            else if ((HWND)lParam == ReportScrollbar) {
                SCROLLINFO reportSi;
                reportSi.cbSize = sizeof(reportSi);
                reportSi.fMask = SIF_ALL;
                GetScrollInfo(ReportScrollbar, SB_CTL, &reportSi);
                int ReportScrollPos = reportSi.nPos;

                switch (LOWORD(wParam)) {
                    case SB_TOP:
                        ReportScrollPos = 0;
                        break;
                    case SB_BOTTOM:
                        ReportScrollPos = reportsShownCount - reportVisiblesCount;
                        break;
                    case SB_LINEUP:
                        ReportScrollPos = max(0, ReportScrollPos - 1);
                        break;
                    case SB_LINEDOWN:
                        ReportScrollPos = min(reportsShownCount - reportVisiblesCount, ReportScrollPos + 1);
                        break;
                    case SB_PAGEUP:
                        ReportScrollPos = max(0, ReportScrollPos - reportVisiblesCount);
                        break;
                    case SB_PAGEDOWN:
                        ReportScrollPos = min(reportsShownCount - reportVisiblesCount, ReportScrollPos + reportVisiblesCount);
                        break;
                    case SB_THUMBTRACK:
                        ReportScrollPos = reportSi.nTrackPos;
                        break;
                }
                if (ReportScrollPos != reportSi.nPos) {
                    SetScrollPos(ReportScrollbar, SB_CTL, ReportScrollPos, TRUE);
                    reportScrollPos = ReportScrollPos;
                    UpdateHomeBookLabels(hwnd);
                }
                break;
            }
            
            break;
        //set sized of the window
        case WM_GETMINMAXINFO: {
            MINMAXINFO* lpMMI = (MINMAXINFO*)lParam;
            lpMMI->ptMaxTrackSize.x = 1280;
            lpMMI->ptMaxTrackSize.y = 720;
            lpMMI->ptMinTrackSize.x = 1280;
            lpMMI->ptMinTrackSize.y = 720;
            break;
        }
        //destructor of the application
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        //returns default window if there is an error
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}