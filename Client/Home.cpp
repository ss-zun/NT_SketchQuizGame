#include "stdafx.h"



// Ȩ â�� ����� ǥ���ϴ� �Լ�
void CreateAndShowWindow_Home(HWND hWnd)
{
	// Ȩ â ����
	hwndHome = CreateWindow(_T("MainWindowClass"), _T("���� ȭ��"), WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, NULL, NULL, g_hInstance, NULL);
	ShowWindow(hwndHome, SW_SHOW);
}
