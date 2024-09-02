#include "stdafx.h"

#pragma region  ����
// �׸���â ���̾�α׸� ����� ǥ���ϴ� �Լ�
void CreateAndShowDialog(HWND hWnd)
{
	g_hDialog = CreateDialog(g_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
	ShowWindow(g_hDialog, SW_SHOW);
	ShowWindow(hWnd, SW_HIDE);
}

void SelectPenColor(DRAW_DETAIL_INFORMATION* g_drawDetailInformation) {
	// ���� ��ȭ ���� ����
	CHOOSECOLOR cc = { sizeof(CHOOSECOLOR) };
	static COLORREF customColors[16] = { 0 }; // ����� ���� ����
	cc.hwndOwner = g_hDrawWnd;
	cc.lpCustColors = customColors;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	cc.rgbResult = g_drawDetailInformation->color;
	if (ChooseColor(&cc)) {
		g_drawDetailInformation->color = cc.rgbResult;
	}
}

void AddLineWidthOption(HWND hDlg) {
	// �׸� �߰�
	SendDlgItemMessage(hDlg, IDC_LINEWIDTH, CB_ADDSTRING, 0, (LPARAM)_T("���"));
	SendDlgItemMessage(hDlg, IDC_LINEWIDTH, CB_ADDSTRING, 0, (LPARAM)_T("����"));
	SendDlgItemMessage(hDlg, IDC_LINEWIDTH, CB_ADDSTRING, 0, (LPARAM)_T("����"));
	SendDlgItemMessage(hDlg, IDC_LINEWIDTH, CB_SETCURSEL, 0, 0); // �ʱ� ������ "���"
}

void SelectLineWidth(HWND hDlg, DRAW_DETAIL_INFORMATION* g_drawDetailInformation) {
	// Combo Box�� ������ ����Ǹ� �̺�Ʈ ó��
	int selectedIndex = SendDlgItemMessage(hDlg, IDC_LINEWIDTH, CB_GETCURSEL, 0, 0);
	switch (selectedIndex)
	{
	case 0: // "���" ����
		// ���� ���⸦ 1px�� ����
		g_drawDetailInformation->width = 1;
		break;
	case 1: // "����" ����
		// ���� ���⸦ 3px�� ����
		g_drawDetailInformation->width = 3;
		break;
	case 2: // "����" ����
		// ���� ���⸦ 5px�� ����
		g_drawDetailInformation->width = 5;
		break;
	}
}

// ����� ID �迭�� �� ����� �߰� �Լ�
void AddUser(_TCHAR* userIDs[], _TCHAR* newUserID) {
	if (numUsers < MAX_USERS) {
		userIDs[numUsers] = newUserID;
		numUsers++;
	}
}

// �����ϰ� ����� ���̵� �����ϴ� �Լ�
_TCHAR* SetRandomUserID(_TCHAR* userIDs[]) {
	// �õ尪 ����
	srand((unsigned)time(NULL));

	// ���� �ε��� ����
	int randomIndex = rand() % numUsers;

	// �������� ���õ� ����� ���̵� ��ȯ
	return userIDs[randomIndex];
}

void DisplayDrawingUserID(HWND hDlg, _TCHAR* userIDs) {
	HWND hStaticText = GetDlgItem(hDlg, IDC_DRAWINGTEXTID);
	if (hStaticText != NULL) {
		_TCHAR* drawingUserID = userIDs; // ���� ����� ���̵� ������
		if (drawingUserID != NULL) {
			SetWindowText(hStaticText, userIDs); // �ؽ�Ʈ ����
		}
		else {
			SetWindowText(hStaticText, _T("�α��θ���!"));
		}
	}
}
#pragma endregion

#pragma region Ÿ��
// ���� �ɼ� ���� �׸� �߰�
void AddFigureOption(HWND hDlg)
{
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("���찳"));
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("��"));
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("Ÿ��"));
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("�簢��"));
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("�ﰢ��"));
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("����"));
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("������"));
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("��"));
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("��ٸ���"));
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("����"));
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("����纯��"));
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("������"));
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("ȭ��ǥ"));
	/*SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("��¦"));
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("��Ʈ"));
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_ADDSTRING, 0, (LPARAM)_T("��ä��"));*/

	// �ʱ� ���� �ɼ��� "��"���� ���� 
	SendDlgItemMessage(hDlg, IDC_FIGURE, CB_SETCURSEL, 1, 0);
}

// �׸��� �ɼ� ����
void SelectFigureOption(HWND hDlg, int& g_currentSelectFigureOption)
{
	// ComboBox�� ������ ����Ǹ�, �̺�Ʈ ó��
	int selectedIndex = SendDlgItemMessage(hDlg, IDC_FIGURE, CB_GETCURSEL, 0, 0);
	switch (selectedIndex)
	{
		// "���찳" ��� ����
	case 0:
		g_currentSelectFigureOption = MODE_ERASE;
		break;
		// "��" ��� ����
	case 1:
		g_currentSelectFigureOption = MODE_LINE;
		break;
		// "Ÿ��" ��� ����
	case 2:
		g_currentSelectFigureOption = MODE_ELLIPSE;
		break;
		// "�簢��" ��� ����
	case 3:
		g_currentSelectFigureOption = MODE_RECTANGLE;
		break;
		// "�ﰢ��" ��� ����
	case 4:
		g_currentSelectFigureOption = MODE_TRIANGLE;
		break;
		// "����" ��� ����
	case 5:
		g_currentSelectFigureOption = MODE_STRAIGHT;
		break;
		// "������" ��� ����
	case 6:
		g_currentSelectFigureOption = MODE_PENTAGON;
		break;
		// "��" ��� ����
	case 7:
		g_currentSelectFigureOption = MODE_STAR;
		break;
		// "��ٸ���" ��� ����
	case 8:
		g_currentSelectFigureOption = MODE_TRAPEZOID;
		break;
		// "����" ��� ����
	case 9:
		g_currentSelectFigureOption = MODE_CHESTNUT;
		break;
		// "����纯��" ��� ����
	case 10:
		g_currentSelectFigureOption = MODE_PARALLELOGRAM;
		break;
		// "������" ��� ����
	case 11:
		g_currentSelectFigureOption = MODE_DIAMOND;
		break;
		// "ȭ��ǥ" ��� ����
	case 12:
		g_currentSelectFigureOption = MODE_ARROW;
		break;
		// "��¦" ��� ����
	case 13:
		g_currentSelectFigureOption = MODE_SPARKLE;
		break;
		// "��Ʈ" ��� ����
	case 14:
		g_currentSelectFigureOption = MODE_HEART;
		break;
		// "��ä��" ��� ����
	case 15:
		g_currentSelectFigureOption = MODE_FANSHAPE;
		break;
	}
}

// Ÿ�� �׸��� ���� ����
void DrawEllipseProcess(HWND hWnd, HDC& hDCMem, WPARAM wParam, LPARAM lParam, DRAW_DETAIL_INFORMATION drawDetailInformation)
{
	HDC hDC = GetDC(hWnd);
	HPEN hPen = CreatePen(PS_SOLID, drawDetailInformation.width, drawDetailInformation.color);
	// ������ DC�� Ÿ�� ���
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	// ������ ȭ�鿡 Ÿ���� 1���� �׸���
	DrawEllipseInHDC(hDC, wParam, lParam);

	SelectObject(hDC, hOldPen);
	hOldPen = (HPEN)SelectObject(hDCMem, hPen);

	// ��� ��Ʈ�ʿ� Ÿ���� 2���� �׸���
	DrawEllipseInHDC(hDCMem, wParam, lParam);

	SelectObject(hDCMem, hOldPen);

	// ȭ�� ��¿� DC�� Pen �ڵ� ����
	DeleteObject(hPen);
	ReleaseDC(hWnd, hDC);
}

// Ÿ���� Ư�� HDC�� �׸�
void DrawEllipseInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam)
{
	// �߽��� ã��
	int centerX = (LOWORD(wParam) + LOWORD(lParam)) / 2;
	int centerY = (HIWORD(wParam) + HIWORD(lParam)) / 2;

	// X,Y�� ���� �� ���� ���ϱ�
	int ellipseAxisX = centerX - LOWORD(wParam);
	int ellipseAxisY = centerY - HIWORD(wParam);

	// ����
	double angle;
	// ���� ��ġ
	int newX, newY;

	// ���� ��ġ
	int oldX = LOWORD(lParam);
	int oldY = centerY;

	// 1���� ȸ���ϸ鼭 Ÿ�� �׸���
	for (int i = 0; i <= 360; i++)
	{
		// Ÿ�� ���� ����
		angle = 2 * PI * i / 360;
		newX = centerX + ellipseAxisX * cos(angle);
		newY = centerY + ellipseAxisY * sin(angle);

		// ù ��°�� ���� ������ �����Ƿ� ����
		if (i != 0)
		{
			DrawLineInHDC(tHDC, MAKEWPARAM(oldX, oldY), MAKELPARAM(newX, newY));
		}

		// ���� ��ġ�� �ٽ� ���� ��ġ�� �ű�.
		oldX = newX;
		oldY = newY;
	}
}

// �� �׸��� ���� ����
void DrawLineProcess(HWND hWnd, HDC& hDCMem, WPARAM wParam, LPARAM lParam, DRAW_DETAIL_INFORMATION drawDetailInformation)
{
	HDC hDC = GetDC(hWnd);
	HPEN hPen = CreatePen(PS_SOLID, drawDetailInformation.width, drawDetailInformation.color);
	// ������ ȭ�鿡 ���� 1���� �׸���
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	DrawLineInHDC(hDC, wParam, lParam);
	SelectObject(hDC, hOldPen);
	// ��� ��Ʈ�ʿ� ���� 2���� �׸���
	hOldPen = (HPEN)SelectObject(hDCMem, hPen);
	DrawLineInHDC(hDCMem, wParam, lParam);
	SelectObject(hDCMem, hOldPen);
	// ȭ�� ��¿� DC�� Pen �ڵ� ����
	DeleteObject(hPen);
	ReleaseDC(hWnd, hDC);
}

// ���� Ư�� HDC�� �׸�
void DrawLineInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam)
{
	MoveToEx(tHDC, LOWORD(wParam), HIWORD(wParam), NULL);
	LineTo(tHDC, LOWORD(lParam), HIWORD(lParam));
}

// �ٰ��� �׸��� ���� ����
void DrawPolygonProcess(HWND hWnd, HDC& hDCMem, WPARAM wParam, LPARAM lParam, DRAW_DETAIL_INFORMATION drawDetailInformation, int type)
{
	HDC hDC = GetDC(hWnd);
	HPEN hPen = CreatePen(PS_SOLID, drawDetailInformation.width, drawDetailInformation.color);
	// ������ ȭ�鿡 �ٰ����� 1���� �׸���
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);
	DrawPolygonInHDC(hDC, wParam, lParam, type);
	SelectObject(hDC, hOldPen);
	// ��� ��Ʈ�ʿ� �ٰ����� 2���� �׸���
	hOldPen = (HPEN)SelectObject(hDCMem, hPen);
	DrawPolygonInHDC(hDCMem, wParam, lParam, type);
	SelectObject(hDCMem, hOldPen);
	// ȭ�� ��¿� DC�� Pen �ڵ� ����
	DeleteObject(hPen);
	ReleaseDC(hWnd, hDC);
}

// �簢���� Ư�� HDC�� �׸�
void DrawRectangleInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam)
{
	// ���۰� ����
	int startX = LOWORD(wParam);
	int startY = HIWORD(wParam);
	int endX = LOWORD(lParam);
	int endY = HIWORD(lParam);

	// �簢�� 4�� �׸���
	DrawLineInHDC(tHDC, MAKEWPARAM(startX, startY), MAKELPARAM(endX, startY));
	DrawLineInHDC(tHDC, MAKEWPARAM(endX, startY), MAKELPARAM(endX, endY));
	DrawLineInHDC(tHDC, MAKEWPARAM(endX, endY), MAKELPARAM(startX, endY));
	DrawLineInHDC(tHDC, MAKEWPARAM(startX, endY), MAKELPARAM(startX, startY));

}

// �ﰢ���� Ư�� HDC�� �׸�
void DrawTriangleInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam)
{
	// ���۰� ����
	int startX = LOWORD(wParam);
	int startY = HIWORD(wParam);
	int endX = LOWORD(lParam);
	int endY = HIWORD(lParam);

	// �ﰢ�� 3�� �׸���
	DrawLineInHDC(tHDC, MAKEWPARAM(startX, endY), MAKELPARAM(endX, endY));
	DrawLineInHDC(tHDC, MAKEWPARAM(endX, endY), MAKELPARAM((startX + endX) / 2, startY));
	DrawLineInHDC(tHDC, MAKEWPARAM((startX + endX) / 2, startY), MAKELPARAM(startX, endY));
}

// �ٰ����� Ư�� HDC�� �׸�
void DrawPolygonInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam, int type)
{
	switch (type)
	{
	case MODE_RECTANGLE:
		DrawRectangleInHDC(tHDC, wParam, lParam);
		break;

	case MODE_TRIANGLE:
		DrawTriangleInHDC(tHDC, wParam, lParam);
		break;

	case MODE_STRAIGHT:
		DrawStraightInHDC(tHDC, wParam, lParam);
		break;

	case MODE_PENTAGON:
		DrawPentagonInHDC(tHDC, wParam, lParam);
		break;

	case MODE_STAR:
		DrawStarInHDC(tHDC, wParam, lParam);
		break;

	case MODE_TRAPEZOID:
		DrawTrapezoidInHDC(tHDC, wParam, lParam);
		break;

	case MODE_CHESTNUT:
		DrawChestnutInHDC(tHDC, wParam, lParam);
		break;

	case MODE_PARALLELOGRAM:
		DrawParallelogramInHDC(tHDC, wParam, lParam);
		break;

	case MODE_DIAMOND:
		DrawDiamondInHDC(tHDC, wParam, lParam);
		break;

	case MODE_ARROW:
		DrawArrowInHDC(tHDC, wParam, lParam);
		break;

	case MODE_SPARKLE:
		DrawSparkleInHDC(tHDC, wParam, lParam);
		break;

	case MODE_HEART:
		DrawHeartInHDC(tHDC, wParam, lParam);
		break;

	case MODE_FANSHAPE:
		DrawFanshapeInHDC(tHDC, wParam, lParam);
		break;
	}
}

// ������ Ư�� HDC�� �׸�
void DrawStraightInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam)
{
	// ���۰� ����
	int startX = LOWORD(wParam);
	int startY = HIWORD(wParam);
	int endX = LOWORD(lParam);
	int endY = HIWORD(lParam);

	// ���� �׸���
	DrawLineInHDC(tHDC, MAKEWPARAM(startX, startY), MAKELPARAM(endX, endY));
}

// �������� Ư�� HDC�� �׸�
void DrawPentagonInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam)
{
	// ���۰� ����
	int startX = LOWORD(wParam);
	int startY = HIWORD(wParam);
	int endX = LOWORD(lParam);
	int endY = HIWORD(lParam);

	int centerX = (startX + endX) / 2;
	int centerY = (startY + endY) / 2;
	int radius = centerX - startX;

	int** positions;
	GetPositionByPoints(positions, 5, centerX, centerY, radius, 60);
	// ������ �׸���
	DrawLineInHDC(tHDC, MAKEWPARAM(positions[0][1], positions[0][0]), MAKELPARAM(positions[1][1], positions[1][0]));
	DrawLineInHDC(tHDC, MAKEWPARAM(positions[1][1], positions[1][0]), MAKELPARAM(positions[2][1], positions[2][0]));
	DrawLineInHDC(tHDC, MAKEWPARAM(positions[2][1], positions[2][0]), MAKELPARAM(positions[3][1], positions[3][0]));
	DrawLineInHDC(tHDC, MAKEWPARAM(positions[3][1], positions[3][0]), MAKELPARAM(positions[4][1], positions[4][0]));
	DrawLineInHDC(tHDC, MAKEWPARAM(positions[4][1], positions[4][0]), MAKELPARAM(positions[0][1], positions[0][0]));

	free(positions);
}

// ���� Ư�� HDC�� �׸�
void DrawStarInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam)
{
	// ���۰� ����
	int startX = LOWORD(wParam);
	int startY = HIWORD(wParam);
	int endX = LOWORD(lParam);
	int endY = HIWORD(lParam);

	int centerX = (startX + endX) / 2;
	int centerY = (startY + endY) / 2;
	int radius = centerX - startX;

	int** positions;
	GetPositionByPoints(positions, 5, centerX, centerY, radius, 60);
	// �� �׸���
	DrawLineInHDC(tHDC, MAKEWPARAM(positions[0][1], positions[0][0]), MAKELPARAM(positions[2][1], positions[2][0]));
	DrawLineInHDC(tHDC, MAKEWPARAM(positions[2][1], positions[2][0]), MAKELPARAM(positions[4][1], positions[4][0]));
	DrawLineInHDC(tHDC, MAKEWPARAM(positions[4][1], positions[4][0]), MAKELPARAM(positions[1][1], positions[1][0]));
	DrawLineInHDC(tHDC, MAKEWPARAM(positions[1][1], positions[1][0]), MAKELPARAM(positions[3][1], positions[3][0]));
	DrawLineInHDC(tHDC, MAKEWPARAM(positions[3][1], positions[3][0]), MAKELPARAM(positions[0][1], positions[0][0]));

	free(positions);
}

// ����Ʈ ������ ���� ���� ������ ��ġ�� ��ȯ
void GetPositionByPoints(int**& positions, int points, int centerX, int centerY, int radius, int revision)
{
	positions = (int**)malloc(points * sizeof(int*));

	for (int i = 0; i < points; i++)
	{
		positions[i] = (int*)malloc(2 * sizeof(int));
		positions[i][0] = centerY + radius * sin(2 * PI * (360 / points) * i / 360 + revision);
		positions[i][1] = centerX + radius * cos(2 * PI * (360 / points) * i / 360 + revision);
	}
}
// ��ٸ����� Ư�� HDC�� �׸�
void DrawTrapezoidInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam)
{
	// ���۰� ����
	int startX = LOWORD(wParam);
	int startY = HIWORD(wParam);
	int endX = LOWORD(lParam);
	int endY = HIWORD(lParam);

	// ��ٸ��� �׸���
	DrawLineInHDC(tHDC, MAKEWPARAM(startX + (endX - startX) / 4, startY), MAKELPARAM(startX + (endX - startX) / 4 * 3, startY));
	DrawLineInHDC(tHDC, MAKEWPARAM(startX + (endX - startX) / 4 * 3, startY), MAKELPARAM(endX, endY));
	DrawLineInHDC(tHDC, MAKEWPARAM(endX, endY), MAKELPARAM(startX, endY));
	DrawLineInHDC(tHDC, MAKEWPARAM(startX, endY), MAKELPARAM(startX + (endX - startX) / 4, startY));
}

// ������ Ư�� HDC�� �׸�
void DrawChestnutInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam)
{
	// ���۰� ����
	int startX = LOWORD(wParam);
	int startY = HIWORD(wParam);
	int endX = LOWORD(lParam);
	int endY = HIWORD(lParam);

	int centerX = (startX + endX) / 2;
	int centerY = (startY + endY) / 2;
	int radius = centerX - startX;

	int** positionsFar;
	int** positionsClose;
	GetPositionByPoints(positionsFar, 20, centerX, centerY, radius, 60);
	GetPositionByPoints(positionsClose, 20, centerX, centerY, radius / 4 * 3, 57);

	// ������ ������
	for (int i = 0; i < 19; i++)
	{
		DrawLineInHDC(tHDC, MAKEWPARAM(positionsFar[i][1], positionsFar[i][0]), MAKELPARAM(positionsClose[i][1], positionsClose[i][0]));
		DrawLineInHDC(tHDC, MAKEWPARAM(positionsClose[i][1], positionsClose[i][0]), MAKELPARAM(positionsFar[i + 1][1], positionsFar[i + 1][0]));
	}

	// ������
	DrawLineInHDC(tHDC, MAKEWPARAM(positionsFar[19][1], positionsFar[19][0]), MAKELPARAM(positionsClose[19][1], positionsClose[19][0]));
	DrawLineInHDC(tHDC, MAKEWPARAM(positionsClose[19][1], positionsClose[19][0]), MAKELPARAM(positionsFar[0][1], positionsFar[0][0]));

	free(positionsFar);
	free(positionsClose);
}

// ����纯���� Ư�� HDC�� �׸�
void DrawParallelogramInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam)
{
	// ���۰� ����
	int startX = LOWORD(wParam);
	int startY = HIWORD(wParam);
	int endX = LOWORD(lParam);
	int endY = HIWORD(lParam);

	// ����纯�� �׸���
	DrawLineInHDC(tHDC, MAKEWPARAM(startX + (endX - startX) / 4, startY), MAKELPARAM(endX, startY));
	DrawLineInHDC(tHDC, MAKEWPARAM(endX, startY), MAKELPARAM(startX + (endX - startX) / 4 * 3, endY));
	DrawLineInHDC(tHDC, MAKEWPARAM(startX + (endX - startX) / 4 * 3, endY), MAKELPARAM(startX, endY));
	DrawLineInHDC(tHDC, MAKEWPARAM(startX, endY), MAKELPARAM(startX + (endX - startX) / 4, startY));
}

// ������ Ư�� HDC�� �׸�
void DrawDiamondInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam)
{
	// ���۰� ����
	int startX = LOWORD(wParam);
	int startY = HIWORD(wParam);
	int endX = LOWORD(lParam);
	int endY = HIWORD(lParam);

	int centerX = (startX + endX) / 2;
	int centerY = (startY + endY) / 2;

	// ������ �׸���
	DrawLineInHDC(tHDC, MAKEWPARAM(centerX, startY), MAKELPARAM(endX, centerY));
	DrawLineInHDC(tHDC, MAKEWPARAM(endX, centerY), MAKELPARAM(centerX, endY));
	DrawLineInHDC(tHDC, MAKEWPARAM(centerX, endY), MAKELPARAM(startX, centerY));
	DrawLineInHDC(tHDC, MAKEWPARAM(startX, centerY), MAKELPARAM(centerX, startY));
}

// ȭ��ǥ�� Ư�� HDC�� �׸�
void DrawArrowInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam)
{
	// ���۰� ����
	int startX = LOWORD(wParam);
	int startY = HIWORD(wParam);
	int endX = LOWORD(lParam);
	int endY = HIWORD(lParam);

	int centerX = (startX + endX) / 2;
	int centerY = (startY + endY) / 2;

	// ȭ��ǥ �׸���
	DrawLineInHDC(tHDC, MAKEWPARAM(startX, startY + (endY - startY) / 4), MAKELPARAM(startX + (endX - startX) / 4 * 3, startY + (endY - startY) / 4));
	DrawLineInHDC(tHDC, MAKEWPARAM(startX + (endX - startX) / 4 * 3, startY + (endY - startY) / 4), MAKELPARAM(startX + (endX - startX) / 4 * 3, startY));
	DrawLineInHDC(tHDC, MAKEWPARAM(startX + (endX - startX) / 4 * 3, startY), MAKELPARAM(endX, centerY));
	DrawLineInHDC(tHDC, MAKEWPARAM(endX, centerY), MAKELPARAM(startX + (endX - startX) / 4 * 3, endY));
	DrawLineInHDC(tHDC, MAKEWPARAM(startX + (endX - startX) / 4 * 3, endY), MAKELPARAM(startX + (endX - startX) / 4 * 3, startY + (endY - startY) / 4 * 3));
	DrawLineInHDC(tHDC, MAKEWPARAM(startX + (endX - startX) / 4 * 3, startY + (endY - startY) / 4 * 3), MAKELPARAM(startX, startY + (endY - startY) / 4 * 3));
	DrawLineInHDC(tHDC, MAKEWPARAM(startX, startY + (endY - startY) / 4 * 3), MAKELPARAM(startX, startY + (endY - startY) / 4));
}

// ��¦�� Ư�� HDC�� �׸�
void DrawSparkleInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam)
{
	// ���۰� ����
	int startX = LOWORD(wParam);
	int startY = HIWORD(wParam);
	int endX = LOWORD(lParam);
	int endY = HIWORD(lParam);

	int centerX = (startX + endX) / 2;
	int centerY = (startY + endY) / 2;
	int radius = centerX - startX;

	int** positions;
	GetPositionByPoints(positions, 4, centerX, centerY, radius / 2, 15);

	// ��¦ �׸���
	DrawLineInHDC(tHDC, MAKEWPARAM(centerX, startY), MAKELPARAM(positions[3][1], positions[3][0]));
	DrawLineInHDC(tHDC, MAKEWPARAM(positions[3][1], positions[3][0]), MAKELPARAM(endX, centerY));
	DrawLineInHDC(tHDC, MAKEWPARAM(endX, centerY), MAKELPARAM(positions[0][1], positions[0][0]));
	DrawLineInHDC(tHDC, MAKEWPARAM(positions[0][1], positions[0][0]), MAKELPARAM(centerX, endY));
	DrawLineInHDC(tHDC, MAKEWPARAM(centerX, endY), MAKELPARAM(positions[1][1], positions[1][0]));
	DrawLineInHDC(tHDC, MAKEWPARAM(positions[1][1], positions[1][0]), MAKELPARAM(startX, centerY));
	DrawLineInHDC(tHDC, MAKEWPARAM(startX, centerY), MAKELPARAM(positions[2][1], positions[2][0]));
	DrawLineInHDC(tHDC, MAKEWPARAM(positions[2][1], positions[2][0]), MAKELPARAM(centerX, startY));

	free(positions);
}

// ��Ʈ�� Ư�� HDC�� �׸�
void DrawHeartInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam)
{
	// ���۰� ����
	int startX = LOWORD(wParam);
	int startY = HIWORD(wParam);
	int endX = LOWORD(lParam);
	int endY = HIWORD(lParam);

	int centerX = (startX + endX) / 2;
	int centerY = (startY + endY) / 2;
	int radius = (centerX - startX) / 2;

	// ��Ʈ �׸���
	DrawLineInHDC(tHDC, MAKEWPARAM(endX, centerY), MAKELPARAM(centerX, endY));
	DrawLineInHDC(tHDC, MAKEWPARAM(centerX, endY), MAKELPARAM(startX, centerY));

	// ���� ��ġ
	int oldX = startX;
	int oldY = centerY;

	int newX, newY, angle;

	// 1���� ȸ���ϸ鼭 �ݿ��� 2�� �׸���
	for (int i = 0; i <= 90; i++)
	{
		// Ÿ�� ���� ����
		angle = 2 * PI * i / 360;
		newX = (startX + radius) + radius * cos(angle);
		newY = centerY + radius * sin(angle);

		// ù ��°�� ���� ������ �����Ƿ� ����
		if (i != 0)
		{
			DrawLineInHDC(tHDC, MAKEWPARAM(oldX, oldY), MAKELPARAM(newX, newY));
			DrawLineInHDC(tHDC, MAKEWPARAM(oldX + radius * 2, oldY), MAKELPARAM(newX + radius * 2, newY));
		}

		// ���� ��ġ�� �ٽ� ���� ��ġ�� �ű�.
		oldX = newX;
		oldY = newY;
	}
}

// ��ä���� Ư�� HDC�� �׸�
void DrawFanshapeInHDC(HDC tHDC, WPARAM wParam, LPARAM lParam)
{
	// ���۰� ����
	int startX = LOWORD(wParam);
	int startY = HIWORD(wParam);
	int endX = LOWORD(lParam);
	int endY = HIWORD(lParam);

	int centerX = (startX + endX) / 2;
	int centerY = (startY + endY) / 2;
	int radius = sqrt((centerX - startX) * (centerX - startX) + (centerY - endY) * (centerY - endY));

	// ��ä�� �׸���
	DrawLineInHDC(tHDC, MAKEWPARAM(endX, centerY), MAKELPARAM(centerX, endY));
	DrawLineInHDC(tHDC, MAKEWPARAM(centerX, endY), MAKELPARAM(startX, centerY));

	// ���� ��ġ
	int oldX = startX;
	int oldY = centerY;

	int newX, newY, angle;

	// 1���� ȸ���ϸ鼭 �ݿ� �׸���
	for (int i = 0; i <= 45; i++)
	{
		// Ÿ�� ���� ����
		angle = 2 * PI * i / 360;
		newX = (startX + radius) + radius * cos(angle);
		newY = centerY + radius * sin(angle);

		// ù ��°�� ���� ������ �����Ƿ� ����
		if (i != 0)
		{
			DrawLineInHDC(tHDC, MAKEWPARAM(oldX, oldY), MAKELPARAM(newX, newY));
		}

		// ���� ��ġ�� �ٽ� ���� ��ġ�� �ű�.
		oldX = newX;
		oldY = newY;
	}
}

// ���� ���� ������ ���� �����
void ShapeDataInput(DRAWPOLYGON_MSG& drawpolygon_msg, int type, int startX, int startY, LPARAM lParam, DRAW_DETAIL_INFORMATION DDinfo)
{
	drawpolygon_msg.type = type;
	drawpolygon_msg.startX = startX;
	drawpolygon_msg.startY = startY;
	drawpolygon_msg.endX = LOWORD(lParam);
	drawpolygon_msg.endY = HIWORD(lParam);
	drawpolygon_msg.color = DDinfo.color;
	drawpolygon_msg.width = DDinfo.width;
}

// ���� ������ �޽��� ����
void SendMessageShapeData(HWND hDrawWnd, DRAWPOLYGON_MSG* DP_Msg, DRAW_DETAIL_INFORMATION& DDinfo, int WM_Drawtype)
{
	DDinfo.width = DP_Msg->width;
	DDinfo.color = DP_Msg->color;
	SendMessage(hDrawWnd, WM_Drawtype,
		MAKEWPARAM(DP_Msg->startX, DP_Msg->startY),
		MAKELPARAM(DP_Msg->endX, DP_Msg->endY));
}
#pragma endregion