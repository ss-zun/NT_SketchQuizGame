#pragma once
// ================= Ÿ�� �۾� ������ ��� ���� ���� �۾� ================= 

#define SERVERIP4_CHAR_UDP1 "235.7.8.18" // �׷� 1
#define SERVERIP4_CHAR_UDP2 "235.7.8.19" // �׷� 2
#define SERVERPORT 9000
#define BUFSIZE    256

#define CLIENTOUT 3001

#pragma region Ÿ��
#define TYPE_CHAT   5000
#define TYPE_ENTER    5001              // �޽��� Ÿ��: �������� ���->������ �̸� �˰� ����ä�ó�������
#define TYPE_NOTY     5002  // ����, ����, �� ���� �˸� �޽�
#define TYPE_START    5003
#define TYPE_SELECT   5004

#define SIZE_TOT 256                    // ���� ��Ŷ(��� + ������) ��ü ũ��
#define SIZE_DAT (SIZE_TOT-2*sizeof(int)) // ����� ������ ������ �κи��� ũ��

#define TYPE_ID		2000				// �޽��� Ÿ��: id (����)
#define TYPE_ID_RESULT 2001				// �޽��� Ƽ�� : id ���
#define TYPE_NOTICE		2002			// �޽��� Ÿ�� : ��������

#define WM_SOCKET (WM_USER+1)
#pragma endregion

// UDP �׷� ��ȣ
#define TYPE_GROUP_A		1000000
#define TYPE_GROUP_B		2000000

// UDP Ŭ�� ����
typedef struct _UDPINFO
{
	SOCKADDR_IN addr;
	int groupNum = 0;
	// ==== Ÿ�� ====
	char id_nickname[BUFSIZE];
	// ============== //
} UDPINFO;

// ���� ���� ������ ���� ����ü�� ����
typedef struct _SOCKETINFO
{
	SOCKET sock;
	char   buf[BUFSIZE + 1];
	int    recvbytes;
	// ===== Ÿ�� ====== 
	USHORT sin_port;	// ���� ��Ʈ ��ȣ
	IN_ADDR sin_addr;	// ���� ip �ּ� 
	char id_nickname_char[BUFSIZE]; // ����� �г��� char ����.
	_TCHAR id_nickname[BUFSIZE]; // ����� �г���
	int    score = 0;       // ���� �÷��� ����
	// ============== //
} SOCKETINFO;

// ���̾�α� ���ν���
INT_PTR CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

// ���� ���� ���� �Լ�
bool AddSocketInfoTCP(SOCKET sock);
bool AddSocketInfoUDP(SOCKADDR_IN addr, int groupNum, char* id_nickname);
void RemoveSocketInfo(SOCKET sock);
void addMessage(char* message);
SOCKETINFO* GetSocketInfo(SOCKET sock);

// �ش� Ŭ���̾�Ʈ�� �׷� ���� ��������
int GetGroupNumber(SOCKADDR_IN addr);


// ������ �޽��� ó�� �Լ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#pragma region Ÿ��
// ���� �޽��� ����
// sizeof(COMM_MSG) == 256
typedef struct _COMM_MSG
{
	int  type;
	int	 groupNum;
	char dummy[SIZE_DAT];
} COMM_MSG;

// �α����Ҷ� ID ����
// sizeof(DRAWLINE_MSG) == 256
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

// Ŭ���̾�Ʈ ���� �迭
static int nTotalSockets = 0;
static int nTotalUDPSockets = 0;
static SOCKETINFO* SocketInfoArray[FD_SETSIZE]; //TCP ������ �ִ� ����
static UDPINFO* UDPSocketInfoArray[FD_SETSIZE]; //UDP ������ �ִ� ����

static SOCKET listen_sock4;
static SOCKADDR_IN serveraddr;
static SOCKET socket_UDP;

//char* g_msgQueue[BUFSIZE];    // �޽��� ���� ť: ���� ��ȭ���� ǥ��. �� ���� ���� ������ �޽������� ��������.
//int head = 0, tail = 0;           // ���� ť �ε���
static MESSAGEQUEUE g_msgQueue;

typedef struct _MESSAGEQUEUE {
	char queue[BUFSIZE][100] = { NULL };         // �޽��� ���� ť: ���� ��ȭ���� ǥ��. �� ���� ���� ������ �޽������� ��������.
	int head = 0;                 // ���� ť �ε���
	int tail = 0;
} MESSAGEQUEUE;

typedef struct _CHAT_MSG
{
	int  type;
	int	 groupNum;
	char msg[SIZE_DAT];
} CHAT_MSG;
#pragma endregion