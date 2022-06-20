// MouseAutoMove.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "utilities.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_TIMER:
    {
        POINT pt;
        RECT rc;
        GetWindowRect(hwnd, &rc);
        GetCursorPos(&pt);

        if (pt.x == rc.left && pt.y == rc.top) 
        {
            SetCursorPos(rc.right, rc.bottom);
        }
        else 
        {
            SetCursorPos(rc.left, rc.top);
        }
        
    }
    return 0;
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

int WINAPI wWinMain(_In_ HINSTANCE hinstance, _In_opt_ HINSTANCE, _In_ PWSTR p_cmd_line, _In_ int n_cmd_show)
{
    RegisterWindow(hinstance, WindowProc);

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        kClassName,                     // Window class
        kWindowName,                    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hinstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }


    SetTimer(hwnd, ID_TIMER, 5000, 0);


    ShowWindow(hwnd, n_cmd_show);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
