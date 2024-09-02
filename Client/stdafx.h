#pragma once

/*���� ���*/
#include "Winsock.h"
#include "PrjClient.h"

#include "Drawing.h"

#pragma region Ÿ��
#include <stdlib.h>
#include "Home.h"
#include "Login.h"
#include "Home_Notice.h"
#include "Home_Pass.h"
#include "math.h"
#include "socket.h"
#include "Ranking.h"
#include "Chatting.h"
#include "Game.h"
#include <time.h>
#pragma endregion

/*���ҽ�*/
#include "resource.h" // �׸��� ���̾�α�â

/*�ĺ���*/
#define SERVERIP4_CHAR_UDP1 "235.7.8.18" // UDP ����1 (����)
#define SERVERIP4_CHAR_UDP2 "235.7.8.19" // UDP ����2 (����)
#define SERVERIP4_CHAR   "127.0.0.1" //��ε�ĳ��Ʈ ��� �ּ� �� ���� ip char ���� (����)
#define SERVERIP4  _T("127.0.0.1")
#define SERVERIP6  _T("::1")
#define SERVERPORT  9000

/* ������ ���� ���� ���� */
static HINSTANCE     g_hInstance;     // ���α׷� �ν��Ͻ� �ڵ�
static HWND          g_hBtnSendFile;  // [���� ����] ��ư
static HWND          g_hBtnSendMsg;   // [�޽��� ����] ��ư
static HWND          g_hEditStatus;   // ���� �޽��� ��� ����
static HWND          g_hBtnErasePic;  // [�׸� �����] ��ư
static HWND          g_hDrawWnd;      // �׸��� �׸� ������

static HWND			 g_hMainWindow;   // ó�� ������â �ڵ�
static HWND			 g_hDialog;       // �׸��� ���̾�α� �ڵ�
static HWND			 g_hBtnPenColor;  // [���� ����] ��ư
static HWND			 g_hLineWidth;    // �� ���� �޺��ڽ�
static HWND			 g_hDrawingTextId;   // �׸� �׸��� ��� ���̵�
static HWND			 g_hDrawingText;     // �׸� �׸��� ��� �ȳ� ����

#pragma region Ÿ��
// ä�� ���� ����
static HWND          g_hRankDlg;      // ��ŷ ���̾�α� �ڵ�
static HWND          g_hChattingDlg;  // ä�� ���̾�α� �ڵ�
static HWND          g_hTimerStatus;  // Ÿ�̸� ����
static HWND          g_hWordStatus;   // ���þ� ����
static int           g_gameScore;     // ���� ����
extern _TCHAR* messageQueue[10];      // �޽��� ť(���߿� ���� Ŭ���̾�Ʈ���� ���� ä�� ���� ǥ��
static HWND          g_hDrawDlg;

// ���� ���� ����
static int roundNum = -1;   //������ ���� ����. ���þ� �迭�� �ε��� ���ҵ� �Ѵ�.
static int countdown = 30;
static const _TCHAR* quizWord[5] = { _T(""), _T("���"), _T("�ٳ���"), _T("����"),_T("������") };   // ���þ� �迭
static int maxRound = 5;
static BOOL isGameOver = FALSE;
static BOOL isOwner = FALSE;  // ������ ���� Ŭ���̾�Ʈ�� ��� isOwner�� TRUE�̴�. ������ ���ߴ� ����� ��� FALSE.
static int score = 0;


static char NICKNAME_CHAR[256];
#pragma endregion

/* ��� ���� ���� ���� */
static volatile bool g_isIPv6;        // IPv4 or IPv6 �ּ�
static char          g_ipaddr[64];    // ���� IP �ּ�(���ڿ�)
static int           g_port;          // ���� ��Ʈ ��ȣ
static volatile bool g_isUDP;         // TCP or UDP ��������
static HANDLE        g_hClientThread; // ������ �ڵ�
static volatile bool g_bCommStarted;  // ��� ���� ����
static SOCKET        g_sock;          // Ŭ���̾�Ʈ ����
static HANDLE        g_hReadEvent;    // �̺�Ʈ �ڵ�(1)
static HANDLE        g_hWriteEvent;   // �̺�Ʈ �ڵ�(2)

/* �޽��� ���� ���� ���� */
static CHAT_MSG      g_chatmsg;       // ä�� �޽���
static DRAWLINE_MSG  g_drawlinemsg;   // �� �׸��� �޽���
static int           g_drawcolor;     // �� �׸��� ����
static ERASEPIC_MSG  g_erasepicmsg;   // �׸� ����� �޽���

static int			 g_lineWidth;     // �� �׸��� ����


#pragma region Ÿ��
/* ���� (2000������) */
static SOCKET        g_tcpSock;          // Ŭ���̾�Ʈ ���� TCP

// �α��� ����� ���� ���
#define ID_LOGIN_BUTTON			2000	// �α��� ��ư
#define ID_ID_INPUT				2001	//�α��� input
#define ID_DUPLICATION_BUTTON	2002	// �ߺ� Ȯ�� ��ư
#define ID_BACKHOME_BUTTON		2003	// ���ư��� ��ư

// �α��� ���� ���� ����
extern _TCHAR		ID_NICKNAME[256];	// ���� ����� ���̵� ��������
extern HANDLE LoginProcessClientThread; // �α��� ���μ��� ������, stdafx.h ���Ͽ� ���� �ּҿ� �����ϱ� ����
extern int g_isDup;

// Ȩ ����� ���� ���
#define ID_CHANNEL_A_BUTTON		2500	// ä�� A ��ư ( TCP)
#define ID_CHANNEL_B_BUTTON		2501	// ä�� B ��ư ( UDP1)
#define ID_CHANNEL_RANDOM_BUTTON 2502	// ���� ���� ��ư (UDP2)
#define ID_NOTICE_BUTTON		2506	// ���� ���� ��ư

// Ȩ ���� ���� ����
extern _TCHAR		ID_NOTICE_TEXT[256];	// �������� ����
extern _TCHAR		ID_NOTICE_INPUT_TEXT[256];	// �������� �Է� ����

// Ȩ ä�� ���� ���� ���� �� ���
#define CHANNEL_TCP				0		// TCP ä��
#define CHANNEL_UDP1			1		// UDP ä�� 1
#define CHANNEL_UDP2			2		// UDP ä�� 2
extern int			channel;				//ä��. (0 : top, 1(udp1) �Ǵ� 2(udp2)�� �ִ�.) 

// Ȩ �������� ����� ���� ��� (2600~ )
#define ID_NOTICE_INPUT			2600	// Ȩ �������� �Է� input
#define ID_OK_BUTTON			2601	// Ȯ�� ��ư
#define ID_CANCLE_BUTTON		2602	// ��� ��ư

// Ȩ �������� ��й�ȣ ����� ���� ��� (2700 ~)
#define ID_PASSWORD_INPUT		2700	// ��й�ȣ �Է� input

// ������ ���� ���� ����
static HWND			hwndLogin;			// �α��� ������ (2000..)
static HWND			hwndHome;			// Ȩ ȭ�� ������ (2500..)
static HWND			hwndHome_Pass;		// �������� ��й�ȣ ������
static HWND			hwndHome_Notice;	// �������� �Է� ������

// ======= ��ȣ =========
#define TYPE_DRAWELLIPSE			4000		// �޽��� Ÿ�� : Ÿ�� �׸���
#define TYPE_DRAWRECTANGLE			4001		// �޽��� Ÿ�� : �簢�� �׸���
#define TYPE_DRAWTRIANGLE			4002		// �޽��� Ÿ�� : �ﰢ�� �׸���
#define TYPE_DRAWSTRAIGHT			4003		// �޽��� Ÿ�� : ���� �׸���
#define TYPE_DRAWPENTAGON			4004		// �޽��� Ÿ�� : ������ �׸���
#define TYPE_DRAWSTAR				4005		// �޽��� Ÿ�� : �� �׸���
#define TYPE_DRAWTRAPEZOID			4006		// �޽��� Ÿ�� : ��ٸ��� �׸���
#define TYPE_DRAWCHESTNUT			4007		// �޽��� Ÿ�� : ���� �׸���
#define TYPE_DRAWPARALLELOGRAM		4008		// �޽��� Ÿ�� : ����纯�� �׸���
#define TYPE_DRAWDIAMOND			4009		// �޽��� Ÿ�� : ������ �׸���
#define TYPE_DRAWARROW				4010		// �޽��� Ÿ�� : ȭ��ǥ �׸���
#define TYPE_DRAWSPARKLE			4011		// �޽��� Ÿ�� : ��¦ �׸���
#define TYPE_DRAWHEART				4012		// �޽��� Ÿ�� : ��Ʈ �׸���
#define TYPE_DRAWFANSHAPE			4013		// �޽��� Ÿ�� : ��ä�� �׸���

#define WM_DRAWELLIPSE			(WM_USER+3)		// Ÿ�� �׸��� ������ �޽���
#define WM_ERASEALITTLE			(WM_USER+4)		// Ư�� �κ� ���� ����� ������ �޽���
#define WM_DRAWRECTANGLE		(WM_USER+5)		// �簢�� �׸��� ������ �޽���
#define WM_DRAWTRIAGNGLE		(WM_USER+6)		// �ﰢ�� �׸��� ������ �޽���
#define WM_DRAWSTRAIGHT			(WM_USER+7)		// ���� �׸��� ������ �޽���
#define WM_DRAWPENTAGON			(WM_USER+8)		// ������ �׸��� ������ �޽���
#define WM_DRAWSTAR				(WM_USER+9)		// �� �׸��� ������ �޽���
#define WM_DRAWTRAPEZOID		(WM_USER+10)	// ��ٸ��� �׸��� ������ �޽���
#define WM_DRAWCHESTNUT			(WM_USER+11)	// ���� �׸��� ������ �޽���
#define WM_DRAWPARALLELOGRAM	(WM_USER+12)	// ����纯�� �׸��� ������ �޽���
#define WM_DRAWDIAMOND			(WM_USER+13)	// ������ �׸��� ������ �޽���
#define WM_DRAWARROW			(WM_USER+14)	// ȭ��ǥ �׸��� ������ �޽���
#define WM_DRAWSPARKLE			(WM_USER+15)	// ��¦ �׸��� ������ �޽���
#define WM_DRAWHEART			(WM_USER+16)	// ��Ʈ �׸��� ������ �޽���
#define WM_DRAWFANSHAPE			(WM_USER+17)	// ��ä�� �׸��� ������ �޽���

// �׸��� ��� ����
#define MODE_ERASE			4500
#define MODE_LINE			4501
#define MODE_ELLIPSE		4502
#define MODE_RECTANGLE		4503
#define MODE_TRIANGLE		4504
#define MODE_STRAIGHT		4505
#define MODE_PENTAGON		4506
#define MODE_STAR			4507
#define MODE_TRAPEZOID		4508
#define MODE_CHESTNUT		4509
#define MODE_PARALLELOGRAM	4510
#define MODE_DIAMOND		4511
#define MODE_ARROW			4512
#define MODE_SPARKLE		4513	
#define MODE_HEART			4514
#define MODE_FANSHAPE		4515	

// UDP �׷� ��ȣ
#define TYPE_GROUP_A		1000000
#define TYPE_GROUP_B		2000000

// ���� �׸��� ��� ���� ����
static int g_currentSelectFigureMode = MODE_LINE;

// ���� �����κ��� �������� �׸��� ���� ���� ����
static DRAW_DETAIL_INFORMATION g_serverDrawDetailInformation;

// ���� Ŭ���̾�Ʈ�� ������ �׸��� ���� ���� ����
static DRAW_DETAIL_INFORMATION g_clientDrawDetailInformation;

// ���찳 ��� �����ϱ� �� Ŭ���̾�Ʈ�� ���������� ������ ����
static int g_lastSelectColor = RGB(255, 0, 0);

// ���� ��尡 "���찳" ������� Ȯ���ϰ� �� ���� �����ϵ��� ����
static bool g_isBeforeModeErase = false;

static HWND g_hFigureSelect; // �׸� ���� �����ϴ� �κ�

static DRAWELLIPSE_MSG g_drawellipsemsg; // Ÿ�� �׸��� �޽���

static DRAWPOLYGON_MSG  g_drawpolygonmsg;   // �ٰ��� �׸��� �޽���

static SOCKADDR_IN serveraddr; // ���� �ּ�

static int g_UDPGroupNum = 0; // UDP �׷� ����
#pragma endregion