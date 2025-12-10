// ADG Widget.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ADG Widget.h"
#include <string>
using namespace std;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
// --- Calculator Globals ---
HWND hCalcInput = NULL;
HWND hCalcOutput = NULL;
HWND hCalcName = NULL;
HWND hCalcSubmit_Name = NULL;
HWND hCalcAdd = NULL;
HWND hCalcSub = NULL;
HWND hCalcMul = NULL;
HWND hCalcDiv = NULL;
HWND hCalcEq = NULL;
HWND hMEM_Active = NULL;
HWND hMEM_New = NULL;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ADGWIDGET, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ADGWIDGET));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ADGWIDGET));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ADGWIDGET);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_CREATE)
    {
        // Create calculator input box
        hCalcName = CreateWindowW(L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            20, 90, 150, 25,
            hWnd, (HMENU)2001, hInst, NULL);

        // Create calculator output box
        hCalcOutput = CreateWindowW(L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY,
            20, 55, 150, 25,
            hWnd, (HMENU)2002, hInst, NULL);

        hCalcInput = CreateWindowW(L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            20, 20, 150, 25,
            hWnd, (HMENU)2010, hInst, NULL);

        // Add buttons (+, -, *, /)
        hCalcAdd = CreateWindowW(L"BUTTON", L"+",
            WS_CHILD | WS_VISIBLE,
            20, 125, 30, 30,
            hWnd, (HMENU)2107, hInst, NULL);

        hCalcSub = CreateWindowW(L"BUTTON", L"-",
            WS_CHILD | WS_VISIBLE,
            55, 125, 30, 30,
            hWnd, (HMENU)2102, hInst, NULL);

        hCalcMul = CreateWindowW(L"BUTTON", L"*",
            WS_CHILD | WS_VISIBLE,
            90, 125, 30, 30,
            hWnd, (HMENU)2103, hInst, NULL);

        hMEM_Active = CreateWindowW(L"BUTTON", L"Active",
            WS_CHILD | WS_VISIBLE,
            125, 125, 30, 30,
            hWnd, (HMENU)2104, hInst, NULL);
        hMEM_New = CreateWindowW(L"BUTTON", L"New Member",
            WS_CHILD | WS_VISIBLE,
            160, 125, 30, 30,
            hWnd, (HMENU)2105, hInst, NULL);
        hCalcSubmit_Name = CreateWindowW(L"BUTTON", L"Submit",
            WS_CHILD | WS_VISIBLE,
            195, 125, 70, 30,
            hWnd, (HMENU)2101, hInst, NULL);

    }

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
                // --- Calculator Button Logic ---
            case 2101: // +
            case 2102: // -
            case 2103: // *
            case 2104: // /
            case 2105: // =
            {
                wchar_t buffer[256];
                GetWindowTextW(hCalcName, buffer, 256);
                std::wstring wide_s(buffer);
                
                //double value = _wtof(ws.c_str());

                string stored;
                wchar_t out[256];
                GetWindowTextW(hCalcOutput, out, 256);
                stored = _wtof(out);

                //double result = store;

                switch (wmId)
                {
                case 2101: wide_s;/*result = stored + value; */ break;
                case 2102: result = stored - value; break;
                case 2103: result = stored * value; break;
                case 2104:
                    if (value != 0 && value > 0) result = stored / value;
                    else MessageBoxW(hWnd, L"Cannot divide by zero!", L"Error", MB_OK);
                    break;
                //case 2105:swprintf_s(out, 256, L"%g", result);
                //    SetWindowTextW(hCalcOutput, out);
                }
            

                swprintf_s(out, 256, L"%g", wide_s);
                SetWindowTextW(hCalcOutput, out);
            }
            break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
