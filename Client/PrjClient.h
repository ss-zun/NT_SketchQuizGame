#pragma once

#pragma region ����
#define TYPE_DRAWLINE 1001              // �޽��� Ÿ��: �� �׸���
#define TYPE_ERASEPIC 1002              // �޽��� Ÿ��: �׸� �����

#define WM_DRAWLINE (WM_USER+1)         // ����� ���� ������ �޽���(1)
#define WM_ERASEPIC (WM_USER+2)         // ����� ���� ������ �޽���(2)

#define SIZE_TOT 256                    // ���� ��Ŷ(��� + ������) ��ü ũ��
#define SIZE_DAT (SIZE_TOT- 2*sizeof(int)) // ����� ������ ������ �κи��� ũ��

// ���� �޽��� ����
// sizeof(COMM_MSG) == 256
typedef struct _COMM_MSG
{
	int  type;
	int	 groupNum;
	char dummy[SIZE_DAT];
} COMM_MSG;

// ä�� �޽��� ����
// sizeof(CHAT_MSG) == 256
typedef struct _CHAT_MSG
{
	int  type;
	int	 groupNum;
	char msg[SIZE_DAT];
} CHAT_MSG;

// �� �׸��� �޽��� ����
// sizeof(DRAWLINE_MSG) == 256
typedef struct _DRAWLINE_MSG
{
	int  type;
	int	 groupNum;
	int  width;
	int  color;
	int  x0, y0;
	int  x1, y1;
	char dummy[SIZE_TOT - 8 * sizeof(int)];
} DRAWLINE_MSG;

// �׸� ����� �޽��� ����
// sizeof(ERASEPIC_MSG) == 256
typedef struct _ERASEPIC_MSG
{
	int  type;
	int	 groupNum;
	char dummy[SIZE_DAT];
} ERASEPIC_MSG;

// ���� ������(ùȭ��) ���ν���
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// ��ȭ����(�׸���) ���ν���
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
// �ڽ� ������ ���ν���
LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);

// ���� ��� ������ �Լ�
DWORD WINAPI ClientMain(LPVOID arg);
DWORD WINAPI ReadThread(LPVOID arg);
DWORD WINAPI WriteThread(LPVOID arg);
#pragma endregion

#pragma region Ÿ��
#define TYPE_CHAT     5000              // �޽��� Ÿ��: ä��
#define TYPE_ENTER    5001              // �޽��� Ÿ��: �������� ���->������ �̸� �˰� ����ä�ó�������
#define TYPE_NOTY     5002  // ����, ����, �� ���� �˸� �޽��� ���
#define TYPE_START    5003
#define TYPE_SELECT   5004

#define TYPE_ID			2000				// �޽��� Ÿ��: id (����)
#define TYPE_ID_RESULT	2001				// �޽��� Ƽ�� : id ���
#define TYPE_NOTICE		2002				// �޽��� Ÿ�� : ��������

typedef struct _MESSAGEQUEUE {
	int type;
	char queue[10][20] = { NULL };         // �޽��� ���� ť: ���� ��ȭ���� ǥ��. �� ���� ���� ������ �޽������� ��������.
	int head = 0;                 // ���� ť �ε���
	int tail = 0;
} MESSAGEQUEUE;

// �α����Ҷ� ID ����
typedef struct ID
{
	int  type;		// �α����Ҷ� ID ����
	char msg[SIZE_DAT];	// id ����
} ID_MSG;

// �α��� ��ư ������ ���� �����Ҷ� ID ��� ���� ����
typedef struct ID_RESULT
{
	int  type;		// '�α���' ��ư �������� ID ����
	char msg[SIZE_DAT];	// id ����
} ID_RESULT_MSG;

// �������� ���� ����
typedef struct NOTICE
{
	int  type;		// �������� Ÿ�� (2002)
	char msg[SIZE_DAT];	// �������� ����
} NOTICE_MSG;

// ����Ʈ ��Ʈ�� ��� �Լ�
void DisplayText(const char* fmt, ...);
// ���� ���� ��ư onClick()�Լ�
void btnGameStart_click();
#pragma endregion
