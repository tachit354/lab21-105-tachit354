#include <windows.h>
#include <stdio.h>
#include<cstdlib>
using namespace std;

HWND textfeild, Plus, Minus, Multiply, Divide, TextBox1, TextBox2;
char textNumber1[100];
char textNumber2[100];
char t[100];
double x,y,z;
char *endptr;


/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE:

			textfeild = CreateWindow("STATIC", "Please input two numbers", WS_BORDER | WS_CHILD | WS_VISIBLE,20,20,200,20,hwnd,NULL,NULL,NULL);
			TextBox1 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE,40,50,160,20,hwnd,NULL,NULL,NULL);
			TextBox2 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE,40,80,160,20,hwnd,NULL,NULL,NULL);

			Plus = CreateWindow("BUTTON", "+", WS_BORDER | WS_CHILD | WS_VISIBLE,50,105,30,30,hwnd,(HMENU) 1,NULL,NULL);
			Minus = CreateWindow("BUTTON", "-", WS_BORDER | WS_CHILD | WS_VISIBLE,85,105,30,30,hwnd,(HMENU) 2,NULL,NULL);
			Multiply = CreateWindow("BUTTON", "*", WS_BORDER | WS_CHILD | WS_VISIBLE,120,105,30,30,hwnd,(HMENU) 3,NULL,NULL);
			Divide = CreateWindow("BUTTON", "/", WS_BORDER | WS_CHILD | WS_VISIBLE,155,105,30,30,hwnd,(HMENU) 4,NULL,NULL);

		break;

		case WM_COMMAND: {
			switch (LOWORD(wParam)){
				case 1: 
					GetWindowText(TextBox1, &textNumber1[0], 100);
					GetWindowText(TextBox2, &textNumber2[0], 100);

					x = strtod(textNumber1, &endptr);
					y = strtod(textNumber2, &endptr);
					z = x+y;
					sprintf(t, "%f", z);
					::MessageBox(hwnd, t, "Result",MB_OK);

				break;	
				
				case 2:
					GetWindowText(TextBox1, &textNumber1[0], 100);
					GetWindowText(TextBox2, &textNumber2[0], 100);

					x = strtod(textNumber1, &endptr);
					y = strtod(textNumber2, &endptr);
					z = x-y;
					sprintf(t, "%f", z);
					::MessageBox(hwnd, t, "Result",MB_OK);

				break;

				case 3:
					GetWindowText(TextBox1, &textNumber1[0], 100);
					GetWindowText(TextBox2, &textNumber2[0], 100);

					x = strtod(textNumber1, &endptr);
					y = strtod(textNumber2, &endptr);
					z = x*y;
					sprintf(t, "%f", z);
					::MessageBox(hwnd, t, "Result",MB_OK);

				break;

				case 4:
					GetWindowText(TextBox1, &textNumber1[0], 100);
					GetWindowText(TextBox2, &textNumber2[0], 100);

					x = strtod(textNumber1, &endptr);
					y = strtod(textNumber2, &endptr);
					z = x/y;
					sprintf(t, "%f", z);
					if(y == 0){
						::MessageBox(hwnd, "Error", "Result",MB_OK);
					}else ::MessageBox(hwnd, t, "Result",MB_OK);
				break;
			}
		break;
		}

		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(51, 225, 225));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_SYSMENU|WS_VISIBLE,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	DeleteObject(wc.hbrBackground);
	return msg.wParam;
}
