#pragma once

// ================= ���� �۾� ================= 
// ä�� ������ view �ڵ�
static HWND g_hChatListView;

void InitializeChatListView(HWND hWnd);
void AddChatMessageToListView(char* message);
void DisplayChatList();
void ClearChatListView();