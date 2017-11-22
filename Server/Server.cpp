// Server.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"



using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{	
	srand(time(0));
	unsigned short int magic_number;
	char str[5];
	char PCName[30], ClientName[30], Message[200];
	WSAData WSADat; // �������� WinSock (��������� ������� WSAStartup)
	sockaddr_in sin; // ��������(�����) ������������ ������
	SOCKET Sock, Client; // ��������� � ���������� ������

	WSAStartup(1.0, &WSADat); // ������������� WinSock
	// 0x0202 - ������ WinSock. ����� ���� 1.0, 1.1, 2.0, 2.2
	// WSADat - ���������, ���� ����� �������� ���. �������������
	gethostname(PCName, 30); // ��������� ����� �������� ��

	sin.sin_family = AF_INET; // ��� ������
	sin.sin_addr.s_addr = 0;  // IP-����� ������� (���� �������� ������� ����� 0)
	sin.sin_port = htons(2803); // ����� ����� �������
	Sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // �������� ������
	bind(Sock, (sockaddr*)&sin, sizeof(sin)); // ���������� ���������� ������ � ������� sin

	// ***** �������� �������
	cout << "Waiting for connection...\n";
	magic_number = 1000 + rand() % 101;
	
	sprintf_s(str, "%d", magic_number);

	listen(Sock, SOMAXCONN); // ������������� ������ �������� (��� ����������� �������)
	Client = accept(Sock, (sockaddr*)&sin, 0); // �������� �������
	
	
	recv(Client, ClientName, 30, 0); // ��������� ����� ���������� �������
	send(Client, PCName, strlen(PCName) + 1, 0); // �������� ����� ����� ���������� (�������)

	cout << "Client has connected:" << ClientName << endl;
	
	char comm;
	while (true){
		if (recv(Client, Message, 200, 0) != SOCKET_ERROR) comm = Message[0];
		switch (comm){
		case 'n':
			magic_number = 1000 + rand() % 101;
			sprintf_s(str, "%d", magic_number);
			break;
		case 'q':
			send(Client, str, strlen(str) + 1, 0);
			break;
		case 'e': {
			//�������� �������
			closesocket(Sock);
			closesocket(Client);
			WSACleanup();
			return 0;
		}
		default:
		{
				cout<<"\n"<<Message<<endl;
				int count = 0, countl = 0;
				char temp[4] ="";
				for (int i = 0; i < 4; i++)
				{
					if (str[i] == Message[i]){
						cout << str[i];
						count++;
					}
				}
				for (int i = 0; i < 4; i++)
				{
					for (int t = 0; t < 4; t++)
						if (str[i] == Message[t] && temp[i] != Message[t]){
							countl++;
							temp[i] = Message[t];
						}
				}
				cout << "\nTrue letter on position:" << count << endl;
				cout << "\nTrue letter:" << countl << endl;
				if (count == 4) send(Client, "Win!", 4, 0);
				else{
					char str[4];
					str[0] = count + '0';
					str[1] = ' ';
					str[2] = countl + '0';
					str[3] = 0;
					if (send(Client, str, 4, 0) != SOCKET_ERROR) cout << "Sent!" << endl;
					else cout<<"Error of sending!"<<endl;
				}
			}
			
		}
	}
}
