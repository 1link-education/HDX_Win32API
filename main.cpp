#include "control.h"
#include "student.h"

#include <windows.h>
#include <string>
#include <iostream>

#define MAX_STD 10

using namespace std;

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);		// declare windows procedure  

char szClassName[ ] = "WindowsWindow";								// make the class name into a global variable - not needed

int WINAPI WinMain(HINSTANCE hThisInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpszArgument,
					int nCmdShow)
{
	HWND hwnd;														// handle for window
	MSG messages;													// save messages to the app
	WNDCLASSEX wincl;												// data structure for the windowclass

	// window structure
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;							// called by windows
	wincl.style = CS_DBLCLKS;										// catch double-click
	wincl.cbSize = sizeof(WNDCLASSEX);

	// default icon and mouse-pointer
	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;										// no menu
	wincl.cbClsExtra = 0;											// no extra bytes after the window class
	wincl.cbWndExtra = 0;											// structure or the window instance
	wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;				// default colour as the background of the window

	// register the window class. if fail, quit the program
	if (!RegisterClassEx(&wincl))
		return 0;

	// if registered successful, create the program
	hwnd = CreateWindowEx(
		0,											// extended possibilities for variation
		szClassName,								// classname
		"AnhNV-StdManGUI with Windows API",			// title
		WS_OVERLAPPEDWINDOW,						// default window
		CW_USEDEFAULT,								// Windows (OS) decides the position
		CW_USEDEFAULT,								// where the window ends up on the screen
		460,										// width in pixel
		360,										// height in pixels
		HWND_DESKTOP,								// the window is a child-window to desktop
		NULL,										// no menu
		hThisInstance,								// program instance handler
		NULL										// no window creation data
		);
	
	ShowWindow(hwnd, nCmdShow);						// make the window visible

	// message loop until GetMessage() returns 0
	while(GetMessage(&messages, NULL, 0, 0))
	{		
		TranslateMessage(&messages);				// translate virtual-key messages to character messages		
		DispatchMessage(&messages);					// send message to WindowProcedure
	}

	return messages.wParam;				// the program return-value is 0 - The value that PostQuitMessage() gave
}

student *st = (struct student*) malloc(MAX_STD * sizeof(struct student));
struct student temp;
int n = 0;
int i;
int selected_row;
char buff[2];

// called by the Windows function DispatchMessage()
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	char text_name[50];
	char text_class[10];

	static HWND hList;
	
	switch(message)										// handle the messages
	{
		case WM_DESTROY:
			PostQuitMessage(0);							// send a WM_QUIT to the message queue
			break;
	
		case WM_CREATE:
			CreateWindow("edit", 0, WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 30, 210, 20, 
				hwnd, (HMENU) 1000, GetModuleHandle (NULL), NULL);

			CreateWindow("edit", 0, WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 60, 210, 20, 
				hwnd, (HMENU) 1001, GetModuleHandle (NULL), NULL);

			CreateWindow("button", "lick my ass", WS_CHILD | WS_VISIBLE, 330, 45, 90, 20, 
				hwnd, (HMENU) 1002, GetModuleHandle (NULL), NULL);

			CreateWindow("button", "show her boobs", WS_CHILD | WS_VISIBLE, 310, 130, 130, 20, 
				hwnd, (HMENU) 1003, GetModuleHandle (NULL), NULL);
			
			hList = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY, 20, 100, 280, 200, 
				hwnd, (HMENU) 1004, NULL, NULL);

			CreateWindow("button", "kick his balls", WS_CHILD | WS_VISIBLE, 310, 215, 130, 20, 
				hwnd, (HMENU) 1005, GetModuleHandle (NULL), NULL);

			break;
	
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			// lick my ass
			case 1002:				
					GetWindowText(GetDlgItem(hwnd, 1000), reinterpret_cast <char*> ((char *) text_name), 50);
					GetWindowText(GetDlgItem(hwnd, 1001), reinterpret_cast <char*> ((char *) text_class), 10);

					if((strcmp(text_name, "") == 0) || (strcmp(text_class, "") == 0))
					{
						MessageBox(hwnd, "Please fill in both [Name] and [Class]!", "My ass is too clean to lick Haha!", MB_OK);
					}
					else
					{
						n++;
						import_std(text_name, text_class, &st[n]);
						//MessageBox(hwnd, st[n].std_dat, "You brought my ass some shit?", MB_OK);						
						SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)st[n].std_dat);
					}					
					break;

			// show her boobs
			case 1003:
				hList = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY, 20, 100, 280, 200, hwnd, (HMENU) 1004, NULL, NULL);
				for(i = 1; i <= n; i++)
				{
					SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)st[i].std_dat);
				}
				break;

			// select ball to kick
			case 1004:
				if (HIWORD(wParam) == LBN_SELCHANGE) 
				{
					selected_row = (int)SendMessage(hList, LB_GETCURSEL, 0, 0);
				}
				break;

			// kick his balls
			case 1005:
				hList = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY, 20, 100, 280, 200, hwnd, (HMENU) 1004, NULL, NULL);
				for(i = 1; i < selected_row; i++)
				{
					SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)st[i].std_dat);
				}
				for(i = selected_row; i < n; i++)
				{
					temp = st[i];
					st[i] = st[i+1];
					st[i+1] = temp;
					SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)st[i].std_dat);
				}
				n--;

				//for(i = 1; i <= n; i++)
				//{
				//	SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)st[i].std_dat);
				//}
								
				//to prevent memory leak
				//memset((&st[n].c)+10/*size of c*/+1, 0, 76);
				break;
			}
			break;

		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hDC;
				char szStdName[] = "Name";
				char szStdClass[] = "Class";

				hDC=BeginPaint(hwnd, &ps);
				TextOut(hDC, 20, 30, szStdName, strlen(szStdName));
				TextOut(hDC, 20, 60, szStdClass, strlen(szStdClass));
				EndPaint(hwnd,&ps);
				return 0;
			}

		default:							
			return DefWindowProc (hwnd, message, wParam, lParam);		// for messages we don't deal with
		}

		return 0;
		//return DefWindowProc(hwnd, message, wParam, lParam);
}