#include "utilities.h"


void RegisterWindow(HINSTANCE hinstance, WNDPROC wndproc)
{

	WNDCLASS wc = { };
	wc.lpfnWndProc = wndproc;
	wc.hInstance = hinstance;
	wc.lpszClassName = kClassName;

	RegisterClass(&wc);
}