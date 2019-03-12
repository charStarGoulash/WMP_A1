//
// FILE : WMP_Assignment1.cpp
// PROJECT : PROG2120 - Assignment #1
// PROGRAMMER : Attila Katona
// FIRST VERSION : 2018-09-12
// DESCRIPTION : This program will display two list boxes and a "move" button. The Left list box will display some
//				 names with each name on a seperate line. The button will be disabled until a name on the left
//				 is selected by the cursor. The "move" button will enable when a name is selected. If the user presses
//				 the button, the name will be moved from the left list box to the right list box and the name will be
//				 removed from the left list box.
//

#include "WMP_Assignment1.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	//Below is the atrributes associated with the drawing of the main window
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(WNDCLASSEX));
	wClass.cbClsExtra = NULL;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = CreateSolidBrush(RGB(200, 0, 0));
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hIcon = NULL;
	wClass.hIconSm = NULL;
	wClass.hInstance = hInst;
	wClass.lpfnWndProc = (WNDPROC)WinProc;
	wClass.lpszClassName = "Window Class";
	wClass.lpszMenuName = NULL;
	wClass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wClass))
	{
		int nResult = GetLastError();
		MessageBox(NULL,
			"Window class creation failed\r\n",
			"Window Class Failed",
			MB_ICONERROR);
	}
	//Below are the attributes associated with creating the main window for the app
	HWND hWnd = CreateWindowEx(NULL,
		"Window Class",
		"Attila Katona: Assignment 01", //Here is where the name is changed that is shown in the title bar
		WS_OVERLAPPEDWINDOW,
		200,
		200,
		640,
		480,
		NULL,
		NULL,
		hInst,
		NULL);

	//Error checking done below- MAking sure the window was properly built 
	if (!hWnd)
	{
		int nResult = GetLastError();

		MessageBox(NULL,
			"Window creation failed\r\n",
			"Window Creation Failed",
			MB_ICONERROR);
	}

	ShowWindow(hWnd, nShowCmd);//This function makes the window be displayed

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	//Below is where the messages are recieved by the program and translated to the appropriate functions for us
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		// Create a Listbox
		// Notice that the structure of the listbox creation is very similar to the EDIT example
		hListBox = CreateWindowEx(WS_EX_CLIENTEDGE,
			"LISTBOX",
			"",
			WS_CHILD | WS_VISIBLE | LBS_NOTIFY,
			50,
			100,
			125,
			200,
			hWnd,
			(HMENU)IDC_MAIN_LISTBOX,
			GetModuleHandle(NULL),
			NULL);
		HGDIOBJ hfDefault = GetStockObject(FONT_TO_USE);
		SendMessage(hListBox,
			WM_SETFONT,
			(WPARAM)hfDefault,
			MAKELPARAM(FALSE, 0));

		//Create second list box
		hListBox2 = CreateWindowEx(WS_EX_CLIENTEDGE,
			"LISTBOX",
			"",
			WS_CHILD | WS_VISIBLE,
			449,
			100,
			125,
			200,
			hWnd,
			(HMENU)IDC_MAIN_LISTBOX2,
			GetModuleHandle(NULL),
			NULL);

		//Below I am adding strings to the listbox on the left
		SendMessage(hListBox,
			LB_ADDSTRING,
			NULL,
			(LPARAM)"John Smith");
		SendMessage(hListBox,
			LB_ADDSTRING,
			NULL,
			(LPARAM)"Mark Ryan");
		SendMessage(hListBox,
			LB_ADDSTRING,
			NULL,
			(LPARAM)"Jerry Hayes");
		SendMessage(hListBox,
			LB_ADDSTRING,
			NULL,
			(LPARAM)"Anthony Hodgins");
		SendMessage(hListBox,
			LB_ADDSTRING,
			NULL,
			(LPARAM)"Bart Simpson");

		// Create a push button
		hWndButton = CreateWindowEx(NULL,
			"BUTTON",
			"Move",
			WS_TABSTOP | WS_VISIBLE | WS_DISABLED |
			WS_CHILD | BS_DEFPUSHBUTTON,
			250,
			180,
			100,
			24,
			hWnd,
			(HMENU)IDC_MAIN_BUTTON,
			GetModuleHandle(NULL),
			NULL);
		SendMessage(hWndButton,
			WM_SETFONT,
			(WPARAM)hfDefault,
			MAKELPARAM(FALSE, 0));
	}
	break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case IDC_MAIN_LISTBOX:
			{
				switch (HIWORD(wParam))
				{
					case LB_GETSEL: //Getting the selection message if something is selected in the list box
					{
						// Since a Listbox has several lines of text, you must first determine if
						// a line of text was selected. This is done with the LB_GETCURSEL command.
						// If nothing is selected, then the return value is LB_ERR, otherwise, the 
						// index (zero based) is returned.

						/*indexInList = (int)SendMessage(hListBox,
							LB_GETCURSEL,
							(WPARAM)0,
							(LPARAM)0);*/

						// If there was something selected, then we get it (using LB_GETTEXT) and
						// display it with the the MessageBox method.
						//if (indexInList != LB_ERR)
						//{
							EnableWindow(hWndButton, true);
						//}
						/*else
						{
							EnableWindow(hWndButton, false);
						}*/
					}
				}
				break;
			}
			case IDC_MAIN_BUTTON:
			{
				SendMessage(hListBox,
					LB_GETTEXT,
					indexInList,
					reinterpret_cast<LPARAM>(buffer));

				SendMessage(hListBox2,
					LB_ADDSTRING,
					NULL,
					(LPARAM)buffer);

				SendMessage(hListBox,
					LB_DELETESTRING,
					indexInList,
					(LPARAM)buffer);

				EnableWindow(hWndButton, false);
			}
			break;
		}
		break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}