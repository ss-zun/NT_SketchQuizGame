#pragma once

// ================= 개인 작업 ================= 
// 채팅 데이터 view 핸들
static HWND g_hChatListView;

void InitializeChatListView(HWND hWnd);
void AddChatMessageToListView(char* message);
void DisplayChatList();
void ClearChatListView();