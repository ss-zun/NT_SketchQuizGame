#include "stdafx.h"

// ================= ���� �۾� ================= 
void InitializeChatListView(HWND hWnd) {
    g_hChatListView = CreateWindowEx(0, WC_LISTVIEW, _T("Chat Data"),
        WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
        220, 10, 350, 240, hWnd, NULL, NULL, NULL);

    // ù ��° �� �߰�
    LVCOLUMN lvc1;
    lvc1.mask = LVCF_TEXT | LVCF_WIDTH;
    lvc1.cx = 350;  // ù ��° ���� �ʺ� ����
    lvc1.pszText = (LPWSTR)_T("Chat Data"); 
    ListView_InsertColumn(g_hChatListView, 0, &lvc1);
}

void AddChatMessageToListView(char* message) {
    LVITEM lvItem = { 0 };
    lvItem.mask = LVIF_TEXT | LVIF_PARAM;
    lvItem.iItem = 0;
    lvItem.iSubItem = 0;

    // ���ڿ��� ���� ���
    int length = strlen(message) + 1;

    // �ʿ��� ���۸� �Ҵ��ϰ� ���ڿ��� ���̵� ���ڿ��� ��ȯ
    wchar_t* portStrW = (wchar_t*)malloc(length * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, 0, message, -1, portStrW, length);

    lvItem.pszText = portStrW;

    ListView_InsertItem(g_hChatListView, &lvItem);
    DisplayChatList();
}

// ä�� ������ ����� ������ â�� ǥ��
void DisplayChatList() {
    // ä�� �����Ͱ� ����Ǿ��� �� ȣ���Ͽ� ����Ʈ �並 ������Ʈ�մϴ�.
    ListView_RedrawItems(g_hChatListView, 0, ListView_GetItemCount(g_hChatListView) - 1);
    UpdateWindow(g_hChatListView);
}

void ClearChatListView() {
    ListView_DeleteAllItems(g_hChatListView);
    DisplayChatList();
}