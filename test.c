#include <windows.h>

#define ID_EDIT_BUTTON 101
#define ID_DELETE_BUTTON 102

// Global variables
HWND g_hListView;
HWND g_hEditButton;
HWND g_hDeleteButton;

// Dummy book data structure
typedef struct {
    int id;
    const char* title;
    const char* author;
} Book;

// Array of dummy book data
Book g_books[] = {
    {1, "Book 1", "Author 1"},
    {2, "Book 2", "Author 2"},
    {3, "Book 3", "Author 3"}
};

// Function to initialize list view with book data
void InitListView(HWND hwndParent) {
    // Create list view
    g_hListView = CreateWindowEx(0, "LISTBOX", "", WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
                                 10, 10, 300, 200, hwndParent, NULL, NULL, NULL);

    // Add book titles to list view
    for (int i = 0; i < sizeof(g_books) / sizeof(g_books[0]); ++i) {
        SendMessage(g_hListView, LB_ADDSTRING, 0, (LPARAM)g_books[i].title);
    }
}

// Function to handle button click events
void OnButtonClick(HWND hwnd, WPARAM wParam) {
    switch (LOWORD(wParam)) {
        case ID_EDIT_BUTTON: {
            // Get the selected item index
            int selectedIndex = SendMessage(g_hListView, LB_GETCURSEL, 0, 0);
            if (selectedIndex != LB_ERR) {
                // Get the selected book information
                char title[100], author[100];
                SendMessage(g_hListView, LB_GETTEXT, selectedIndex, (LPARAM)title);
                for (int i = 0; i < sizeof(g_books) / sizeof(g_books[0]); ++i) {
                    if (!strcmp(title, g_books[i].title)) {
                        strcpy(author, g_books[i].author);
                        break;
                    }
                }

                // Open the edit window with the selected book information
                MessageBox(hwnd, "Edit selected book:\nTitle:", title, MB_OK | MB_ICONINFORMATION);
            }
            break;
        }
        case ID_DELETE_BUTTON:
            // Handle delete button click
            break;
    }
}

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            // Create list view
            InitListView(hwnd);

            // Create edit button
            g_hEditButton = CreateWindow("BUTTON", "Edit", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                          320, 20, 80, 30, hwnd, (HMENU)ID_EDIT_BUTTON, NULL, NULL);

            // Create delete button
            g_hDeleteButton = CreateWindow("BUTTON", "Delete", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                                            320, 70, 80, 30, hwnd, (HMENU)ID_DELETE_BUTTON, NULL, NULL);
            break;
        }
        case WM_COMMAND:
            OnButtonClick(hwnd, wParam);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char* CLASS_NAME = "MainWindowClass";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Book List",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 450, 300,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
