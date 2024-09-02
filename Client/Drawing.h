#pragma once

#pragma region ����
#define MAX_USERS 10 // �ִ� ����� ��
static int			numUsers; // ���� ����� ��
static _TCHAR* userIDs[MAX_USERS];
static _TCHAR* drawingUserID;

// ��ȭ ���ڸ� ����� ǥ���ϴ� �Լ�
void CreateAndShowDialog(HWND hWnd);
void SelectPenColor(DRAW_DETAIL_INFORMATION* g_drawDetailInformation);
void AddLineWidthOption(HWND hDlg);
void SelectLineWidth(HWND hDlg, DRAW_DETAIL_INFORMATION* g_drawDetailInformation);
void AddUser(_TCHAR* userIDs[], _TCHAR* newUserID);
_TCHAR* SetRandomUserID(_TCHAR* userIDs[]);
void DisplayDrawingUserID(HWND hDlg, _TCHAR* userIDs);
#pragma endregion


#pragma region Ÿ��
#define PI	3.1416

// Ÿ��
// sizeof(DRAWELLIPSE_MSG) == 256
typedef struct _DRAWELLIPSE_MSG
{
	int  type;
	int	 groupNum;
	int	 width;
	int  color;
	int  x0, y0;
	int  x1, y1;
	char dummy[SIZE_TOT - 8 * sizeof(int)];
} DRAWELLIPSE_MSG;

// �ٰ���
typedef struct _DRAWPOLYGON_MSG
{
	int type;
	int	groupNum;
	int width;
	int color;
	int startX, startY;
	int endX, endY;
	char dummy[SIZE_TOT - 8 * sizeof(int)];
} DRAWPOLYGON_MSG;

// �׸� ���� ������ ���� ����ü
typedef struct _DRAW_DETAIL_INFORMATION
{
	int width = 1;	// ����
	int color = RGB(255, 0, 0);	// ����
} DRAW_DETAIL_INFORMATION;

// ���� �ɼ� ���� �׸� �߰�
void AddFigureOption(HWND hDlg);

// �׸��� �ɼ� ����
void SelectFigureOption(HWND hDlg, int& g_currentSelectFigureOption);

// Ÿ�� �׸��� ���� ����
void DrawEllipseProcess(HWND hWnd, HDC& hDCMem, WPARAM wParam, LPARAM lParam, DRAW_DETAIL_INFORMATION drawDetailInformation);

// Ÿ���� Ư�� HDC�� �׸�
void DrawEllipseInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam);

// �� �׸��� ���� ����
void DrawLineProcess(HWND hWnd, HDC& hDCMem, WPARAM wParam, LPARAM lParam, DRAW_DETAIL_INFORMATION drawDetailInformation);

// ���� Ư�� HDC�� �׸�
void DrawLineInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam);

// �ٰ��� �׸��� ���� ����
void DrawPolygonProcess(HWND hWnd, HDC& hDCMem, WPARAM wParam, LPARAM lParam, DRAW_DETAIL_INFORMATION drawDetailInformation, int type);

// �簢���� Ư�� HDC�� �׸�
void DrawRectangleInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam);

// �ﰢ���� Ư�� HDC�� �׸�
void DrawTriangleInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam);

// �ٰ����� Ư�� HDC�� �׸�
void DrawPolygonInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam, int type);

// ������ Ư�� HDC�� �׸�
void DrawStraightInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam);

// �������� Ư�� HDC�� �׸�
void DrawPentagonInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam);

// ���� Ư�� HDC�� �׸�
void DrawStarInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam);

// ����Ʈ ������ ���� ���� ������ ��ġ�� ��ȯ
void GetPositionByPoints(int**& positions, int points, int centerX, int centerY, int radius, int revision);

// ��ٸ����� Ư�� HDC�� �׸�
void DrawTrapezoidInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam);

// ������ Ư�� HDC�� �׸�
void DrawChestnutInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam);

// ����纯���� Ư�� HDC�� �׸�
void DrawParallelogramInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam);

// ������ Ư�� HDC�� �׸�
void DrawDiamondInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam);

// ȭ��ǥ�� Ư�� HDC�� �׸�
void DrawArrowInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam);

// ��¦�� Ư�� HDC�� �׸�
void DrawSparkleInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam);

// ��Ʈ�� Ư�� HDC�� �׸�
void DrawHeartInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam);

// ��ä���� Ư�� HDC�� �׸�
void DrawFanshapeInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam);

// ���� ���� ������ ���� �����
void ShapeDataInput(DRAWPOLYGON_MSG& drawpolygon_msg, int type, int startX, int startY, LPARAM lParam, DRAW_DETAIL_INFORMATION DDinfo);

// ���� ������ �޽��� ����
void SendMessageShapeData(HWND hDrawWnd, DRAWPOLYGON_MSG* DP_Msg, DRAW_DETAIL_INFORMATION& DDinfo, int WM_Drawtype);
#pragma endregion