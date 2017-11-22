// Client.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	char PCName[30], ServerName[30], Message[200];
	char *IP = new char[16];
	WSAData WSADat; // �������� WinSock (��������� ������� WSAStartup)
	sockaddr_in sin; // ��������(�����) ������������ ������
	SOCKET Sock; // ���������� �����

	// ���� IP-������ �������
	cout<<"Enter server's IP: "<<endl;
	IP = "127.0.0.1";

	WSAStartup(0x0202, &WSADat); // ������������� WinSock
	// 0x0202 - ������ WinSock. ����� ���� 1.0, 1.1, 2.0, 2.2
	// WSADat - ���������, ���� ����� �������� ���. �������������
	gethostname(PCName, 30); // ��������� ����� �������� ��

	sin.sin_family = AF_INET; // ��� ������
	sin.sin_addr.s_addr = inet_addr(IP); // IP-����� ������� (���� �������� ������� ����� 0)
	sin.sin_port = htons(2803); // ����� ����� �������

	Sock = socket(AF_INET, SOCK_STREAM, 0); // �������� ������

	// ***** ����������� � �������
	cout<<"Connecting to server...\n";

	if (connect(Sock, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR) {
		cout<<"Connection error!\n";
		goto End;
	}
	send(Sock, PCName, strlen(PCName) + 1, 0); // �������� ����� ����� ���������� (�������)
	recv(Sock, ServerName, 30, 0); // ��������� ����� ���������� �������

	cout<<"Connected to"<<ServerName<<endl;


	while (true)
	{


		cout<<"\nEnter message: "<<endl;
		scanf_s("%199s", Message, 200);
		if (send(Sock, Message, strlen(Message) + 1, 0) != SOCKET_ERROR) cout<<"Sent!\n"<<endl;
		else cout<<"Error of sending!\n";
		if ( Message[0] != 'e' && Message[0] != 'n'){
			
			char *request = new char[4];
			if (recv(Sock, request, strlen(request)+1, 0) != SOCKET_ERROR) {
				for (int i = 0; i < 4; i++)
					cout << request[i];

			}
			else cout<<"Error of getting!\n";
		}

	
	}
End:

	// �������� ������� � ��������� ������ � WinSock
	closesocket(Sock);
	WSACleanup();
	_gettch();

}