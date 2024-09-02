#include "stdafx.h"

// ========== UDP�� Ÿ��, TCP�� ���� ==========

// �ش� byte��ŭ �ޱ�
int recvn(SOCKET s, char* buf, int len, int flags, SOCKADDR_IN serveraddr, bool bIsUDP)
{
	int received;
	char* ptr = buf;
	int left = len;


	while (left > 0) 
	{
		// UDP ������� ������ �ޱ�
		if (bIsUDP)
		{
			int serveraddrLen = sizeof(serveraddr);
			received = recvfrom(s, ptr, left, flags, (SOCKADDR*)&serveraddr, &serveraddrLen);

		}
		// TCP ������� ������ �ޱ�
		else
		{
			received = recv(s, ptr, left, flags);
		}
		if (received == SOCKET_ERROR)
		{
			return SOCKET_ERROR;
		}
		else if (received == 0)
		{
			break;
		}

		left -= received;
		ptr += received;
	}

	return (len - left);
}

// �ش� byte��ŭ ������
int sendn(SOCKET s, char* buf, int len, int flags, SOCKADDR_IN serveraddr, bool bIsUDP)
{
	int received;
	char* ptr = buf;
	int left = len;
	while (left > 0) 
	{
		// UDP ������� ������ ������
		if (bIsUDP)
		{
			received = sendto(s, buf, left, flags, (SOCKADDR*)&serveraddr, sizeof(serveraddr));
		}
		// TCP ������� ������ �ޱ�
		else
		{
			received = send(s, ptr, left, flags);
		}
		if (received == SOCKET_ERROR)
		{
			return SOCKET_ERROR;
		}
		else if (received == 0)
		{
			break;
		}

		left -= received;
		ptr += received;
	}

	return (len - left);
}

#pragma region Ÿ��
// ���� ũ�� : ���� ũ�⸦ �˷��ִ� �޽��� ����
void sendMsgLen(SOCKET s, int len, SOCKADDR_IN serveraddr, bool bIsUDP)
{
	// g_sock�� static���� ��������������, �Ű����� ���� ����ϸ�, ���� �Ѿ���� ����.
	int retval;
	retval = sendn(s, (char*)&len, sizeof(int), 0, serveraddr, bIsUDP);
	if (retval == SOCKET_ERROR)
	{
		err_display("sendMsgSize()");
	}
}
#pragma endregion