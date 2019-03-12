//
// FILE : WMP_Assignment1.h
// PROJECT : PROG2120 - Assignment #1
// PROGRAMMER : Attila Katona
// FIRST VERSION : 2018-09-12
// DESCRIPTION : This is the header file that keeps all the constants, defines, prototypes, global variables and all
//				 includes needed for wmp_assignment1
//

#pragma once
//Includes
#include <windows.h>

//Defines
#define IDC_MAIN_BUTTON		101		// Button identifier
#define IDC_MAIN_LISTBOX	102		// Edit box identifier
#define IDC_MAIN_LISTBOX2   103
#define FONT_TO_USE         18		// Set to 18 which is a font style
#define MAX_CHARACTERS      256

//Variables
HWND hListBox;
HWND hListBox2;
HWND hWndButton;
char buffer[MAX_CHARACTERS];
int indexInList;

//Protoypes
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
