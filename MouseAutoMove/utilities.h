#pragma once
#include <windows.h>

#define ID_TIMER    1

const wchar_t kClassName[] = L"Sample Window Class";	
const wchar_t kWindowName[] = L"Mouse Auto Move";

const int kTimerTime = 2000;

void RegisterWindow(HINSTANCE hinstance, WNDPROC wndproc);