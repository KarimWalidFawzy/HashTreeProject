#include "include/lib.hpp"
/**
 * 
 */
HWND globalMainWindow;
HMENU hMenu;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void AddMenus(HWND);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "MainWindowClass";
    RegisterClassA(&wc);
    globalMainWindow = CreateWindowExA(
        0,
        "MainWindowClass",
        "Hash Tree Example",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );
    // Create a hash tree
    if (globalMainWindow == NULL)
    {
        return 0;
    }
    ShowWindow(globalMainWindow, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            AddMenus(hwnd);
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 1: // File -> Open
                    // Handle file open
                    break;
                case 2: // File -> Exit
                    PostQuitMessage(0);
                    break;
            }
            break;
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                // Drawing code here

                EndPaint(hwnd, &ps);
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcA(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
void AddMenus(HWND hwnd) {
    hMenu = CreateMenu();
    HMENU hFileMenu = CreatePopupMenu();
    AppendMenuA(hFileMenu, MF_STRING, 1, "Open");
    AppendMenuA(hFileMenu, MF_STRING, 2, "Exit");
    AppendMenuA(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
    SetMenu(hwnd, hMenu);
}
void drawTree(HDC hdc, HashTree<int>* tree) {
    // Implement drawing logic for the hash tree
    // This is a placeholder function
    using namespace Gdiplus;
    GdiplusStartupInput gdiplusStartupInput;
    TextOutA(hdc, 10, 10, "Hash Tree", 9);
}