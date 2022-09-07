// MouseAutoMove.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "utilities.h"

bool pos = false;

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

        TextOut(hdc, 10, 10, TEXT("Double tap Space bar to exit!"), strlen("Double tap Space bar to exit!"));

        ReleaseDC(hwnd, hdc);

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

        if (pos) 
        {
            //SetCursorPos(rc.right, rc.bottom); 
            
            // long --> 0 ~ 65,535
            // 
            INPUT Inputs[5] = { 0 };

            // Mouse move to middle
            int nMaxWindowWidth = GetSystemMetrics(SM_CXMAXIMIZED);    
            int nMaxWindowHeight = GetSystemMetrics(SM_CYMAXIMIZED);
            int nDx = ((double)(rc.right)/2 + rc.left) / nMaxWindowWidth * 65535;
            int nDy = ((double)(rc.bottom)/2 + rc.top) / nMaxWindowHeight * 65535;

            Inputs[0].type = INPUT_MOUSE;
            Inputs[0].mi.dx = nDx;//rc.right; // desired X coordinate
            Inputs[0].mi.dy = nDy;//rc.bottom; // desired Y coordinate
            Inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;

            // Mouse left click -> noreact
            Inputs[1].type = INPUT_MOUSE;
            Inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

            Inputs[2].type = INPUT_MOUSE;
            Inputs[2].mi.dwFlags = MOUSEEVENTF_LEFTUP;


            // Keyboard press -> noreact
            Inputs[3].type = INPUT_KEYBOARD;
            Inputs[3].ki.wVk = 0x41; //"A" key
            //VK_SPACE to test

            Inputs[4].type = INPUT_KEYBOARD;
            Inputs[4].ki.wVk = 0x41;
            Inputs[4].ki.dwFlags = KEYEVENTF_KEYUP;

            SendInput(5, Inputs, sizeof(INPUT));
            pos = !pos;
        }
        else 
        {
            //SetCursorPos(rc.left, rc.top);
            int nMaxWindowWidth = GetSystemMetrics(SM_CXMAXIMIZED);
            int nMaxWindowHeight = GetSystemMetrics(SM_CYMAXIMIZED);
            int nDx = (double)(rc.left) / nMaxWindowWidth * 65535;
            int nDy = (double)(rc.top) / nMaxWindowHeight * 65535;

            INPUT Inputs[1] = { 0 };

            // Mouse move
            Inputs[0].type = INPUT_MOUSE;
            Inputs[0].mi.dx = nDx;//rc.right; // desired X coordinate
            Inputs[0].mi.dy = nDy;//rc.bottom; // desired Y coordinate
            Inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;

            SendInput(1, Inputs, sizeof(INPUT));
            pos = !pos;
        }
        
    }

    case WM_KEYDOWN:
    {
        if (wparam == VK_SPACE)
        {
            int res = MessageBox(nullptr, TEXT("You ensure want to stop it?"), TEXT("Exit"), MB_YESNO);

            if (res == IDYES)
            {
                DestroyWindow(hwnd);
            }
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

    SetTimer(hwnd, ID_TIMER, kTimerTime, 0);
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


