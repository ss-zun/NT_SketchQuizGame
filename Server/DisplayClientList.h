#pragma once

// ================= ���� �۾� ================= 
// Ŭ���̾�Ʈ ��� view �ڵ�
static HWND g_hListView;

void InitializeListView(HWND hWnd);
void AddClientToListView(int port, _TCHAR* id, SOCKET sock);
void DisplayClientList();
void RemoveClientFromListView(int port);