#include "include\lib.hpp"
HWND globalMainWindow;
HMENU hMenu;
HashTree<Transaction> tree;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void AddMenus(HWND);
void Message(const char* msg) {
    MessageBoxA(0, msg, "Message", MB_OK);
}
void Error(const char* msg) {
    MessageBoxA(0, msg, "Error", MB_OK | MB_ICONERROR);
}
bool fileread=false;
// Function to read a file and create a hash tree
// This is a placeholder function
// You can implement the actual file reading and hash tree creation logic here
const char* fileName ;
void drawTree(HDC hdc);
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
            switch (wParam) {
                case 1: 
                {OPENFILENAMEA ofn={sizeof(OPENFILENAMEA)}; 
                    char szFile[MAX_PATH]={};

                    ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
                    ofn.lpstrFileTitle = "Search for the file";
                    ofn.nMaxFile=sizeof(szFile);
                    ofn.lpstrFile = szFile;
                    bool rez=GetOpenFileNameA(&ofn);
                    if(rez){
                    // Check if the file was selected
                    fileName = ofn.lpstrFile;
                    // Open the file and read its contents
                    fileread=true;
                    tree = readFileAndCreateHashTree(fileName);
                    InvalidateRect(hwnd, NULL,TRUE); // Invalidate the window to trigger a repaint
                    UpdateWindow(hwnd);
                    }
                    else {
                        // Handle the case when no file was selected
                        Message("No file selected");
                    }
                }
                break;
        
                case 2: // File -> Exit
                    {
                    PostQuitMessage(0);
                    }
                    break;
            
            break;
        }
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                // Drawing code here
                HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
                FillRect(hdc, &ps.rcPaint, hBrush);
                if (fileread) // Check if the file has been read
                {
                // Create a hash tree from the file
                drawTree(hdc);
                }
                //Fill the background with white color
                
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
void AddMenus(HWND hwnd){
    hMenu = CreateMenu();
    AppendMenuA(hMenu, MF_STRING, 1, "Open");
    AppendMenuA(hMenu, MF_STRING, 2, "Exit");
    SetMenu(hwnd, hMenu);
}
void drawNode(HDC hdc, HashTreeNode<Transaction>* node, int x, int y, int horizontalSpacing, int verticalSpacing) {
    if (node == nullptr) {
        return;
    }

    // 1. Draw the current node (e.g., a rectangle and its hash)
    RECT nodeRect = {x - 20, y - 10, x + 20, y + 10}; // Example rectangle dimensions
    FrameRect(hdc, &nodeRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
    std::string hashedval(std::to_string(hashFunction(node->data)));
    DrawTextA(hdc, hashedval.c_str(), hashedval.length(), &nodeRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 2. Calculate positions for left and right children
    int leftChildX = x - horizontalSpacing / 2;
    int rightChildX = x + horizontalSpacing / 2;
    int childY = y + verticalSpacing;
    int newHorizontalSpacing = horizontalSpacing / 2; // Adjust spacing for deeper levels

    // 3. Draw the left child and the connecting line
    if (node->left != nullptr) {
        MoveToEx(hdc, x, y + 10, NULL); // Connect from the bottom of the current node
        LineTo(hdc, leftChildX, childY - 10); // To the top of the left child
        drawNode(hdc, node->left, leftChildX, childY, newHorizontalSpacing, verticalSpacing);
    }

    // 4. Draw the right child and the connecting line
    if (node->right != nullptr) {
        MoveToEx(hdc, x, y + 10, NULL); // Connect from the bottom of the current node
        LineTo(hdc, rightChildX, childY - 10); // To the top of the right child
        drawNode(hdc, node->right, rightChildX, childY, newHorizontalSpacing, verticalSpacing);
    }
}

void drawTree(HDC hdc) {
    // Implement drawing logic for the hash tree
    // This is a placeholder function
    RECT rect;
    GetClientRect(globalMainWindow, &rect);
    // Fill the background with white color
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    FillRect(hdc, &rect, hBrush);
    TextOutA(hdc, 10, 10, "Hash Tree", 9);
    // Draw the hash tree nodes
    // You can use the tree object to access the hash tree and draw its nodes
    // For example, you can use a recursive function to traverse the tree and draw each node    
    // This is a simple example of drawing the root node
    HashTreeNode<Transaction> *R =tree.getRoot();
    HashTreeNode<Transaction> *Rleft=R->left;
    HashTreeNode<Transaction> *Rright=R->right;
    // Draw the left subtree
    if (R != nullptr) {
        int initialX = rect.right / 2; // Center the root horizontally
        int initialY = 50;             // Start the root at a certain vertical position
        int initialHorizontalSpacing = rect.right / 2; // Initial horizontal spacing
        int verticalSpacing = 60;                     // Vertical spacing between levels
        drawNode(hdc, R, initialX, initialY, initialHorizontalSpacing, verticalSpacing);
    }
    else{
        TextOutA(hdc,40,50,"Tree is empty",9);
    }
}
