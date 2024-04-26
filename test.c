#include <windows.h>
#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

// Structure to represent a book
typedef struct {
    char title[100];
    char author[100];
    char genre[50];
    float price;
    int quantity;
} Book;

// Global array to store books
Book books[MAX_BOOKS];
int numBooks = 0;

// Function to add a new book to the inventory
void addBook(const char* title, const char* author, const char* genre, float price, int quantity) {
    if (numBooks < MAX_BOOKS) {
        strcpy(books[numBooks].title, title);
        strcpy(books[numBooks].author, author);
        strcpy(books[numBooks].genre, genre);
        books[numBooks].price = price;
        books[numBooks].quantity = quantity;
        numBooks++;
    } else {
        printf("Maximum number of books reached!\n");
    }
}

// Function to list all available books
void listBooks(HWND hwnd) {
    char buffer[1000] = "";
    strcat(buffer, "Available Books:\n\n");
    for (int i = 0; i < numBooks; ++i) {
        char temp[100];
        sprintf(temp, "%d. %s by %s - %s - $%.2f - Quantity: %d\n", i + 1, books[i].title, books[i].author, books[i].genre, books[i].price, books[i].quantity);
        strcat(buffer, temp);
    }
    MessageBox(hwnd, buffer, "Book Inventory", MB_OK);
}

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE: {
            // Add some sample books to the inventory
            addBook("The Great Gatsby", "F. Scott Fitzgerald", "Classic", 9.99, 50);
            addBook("To Kill a Mockingbird", "Harper Lee", "Fiction", 8.50, 30);
            addBook("1984", "George Orwell", "Dystopian", 7.25, 40);

            // Create "List Books" button
            CreateWindow("BUTTON", "List Books", WS_VISIBLE | WS_CHILD, 50, 50, 100, 30, hwnd, (HMENU)1, NULL, NULL);
            // Create "Exit" button
            CreateWindow("BUTTON", "Exit", WS_VISIBLE | WS_CHILD, 50, 100, 100, 30, hwnd, (HMENU)2, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            switch (wmId) {
                case 1: // List books button clicked
                    listBooks(hwnd);
                    break;
                case 2: // Exit button clicked
                    PostQuitMessage(0);
                    break;
            }
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char* CLASS_NAME = "BookshopWindowClass";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Bookshop Management System",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
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
