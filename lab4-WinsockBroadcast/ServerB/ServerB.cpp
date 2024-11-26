#include <iostream>
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
#pragma warning( disable: 4566)

using namespace std;

string SetErrorMsgText(string msgText, int code);
string GetErrorMsgText(int code);

int main()
{
	SetConsoleCP(1521);
	SetConsoleOutputCP(1521);
	WSADATA wsaData;
	SOCKET sS;
	char name[10] = "Hello";
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup: ", WSAGetLastError());
		if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("socket: ", WSAGetLastError());
		SOCKADDR_IN clnt;
		int flen = sizeof(clnt);
		if (GetRequestFromClient(name, 2000, (sockaddr*)&clnt, &flen))
		{
			PutAnswerToClient(name, (sockaddr*)&clnt, &flen);
		}

	}
	catch (string errorMsgText)
	{
		cout << errorMsgText << "\n";
	}
	return 0;
}

bool GetRequestFromClient(char* name, short port, sockaddr* from, int* flen)
{
	char ibuf[50];
	int ld = 0;
	if ((ld = recvfrom(sS, ibuf, sizeof(ibuf), NULL, from, flen)) == SOCKET_ERROR)
		throw SetErrorMsgText("requestsFun recvfrom: ", WSAGetLastError());
	else
	{
		if (name == ibuf)
		{
			return true;
		}
		if (ld == WSAETIMEDOUT)
		{
			return false;
		}
	}
}

bool PutAnswerToClient(char* name, sockaddr* to, int* lto)
{
	char obuf[50];
	int lo = 0;
	if ((lo = sendto(sS, obuf, strlen(obuf), NULL, to, sizeof(to))) == SOCKET_ERROR)
		throw SetErrorMsgText("sendto: ", WSAGetLastError());
	else
	{

	}
}

string SetErrorMsgText(string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
}

// gets WSAErrorCode and returns explanation
string GetErrorMsgText(int code)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string msgText;
	switch (code)
	{
	case WSAEINTR: msgText = "Работа функции прервана"; break;
	case WSAEACCES: msgText = "Разрешение отвергнуто"; break;
	case WSAEFAULT: msgText = "Ошибочный адрес"; break;
	case WSAEINVAL: msgText = "Ошибка в аргументе"; break;
	case WSAEMFILE: msgText = "Слишком много файлов открыто"; break;
	case WSAEWOULDBLOCK: msgText = "Ресурс временно недоступен"; break;
	case WSAEINPROGRESS: msgText = "Операция в процессе развития"; break;
	case WSAEALREADY: msgText = "Операция уже выполняется"; break;
	case WSAENOTSOCK: msgText = "Сокет задан неправильно"; break;
	case WSAEDESTADDRREQ: msgText = "Требуется адрес расположения"; break;
	case WSAEMSGSIZE: msgText = "Сообщение слишком длинное"; break;
	case WSAEPROTOTYPE: msgText = "Неправильный тип протокола для сокета"; break;
	case WSAENOPROTOOPT: msgText = "Ошибка в опции протокола"; break;
	case WSAEPROTONOSUPPORT: msgText = "Протокол не поддерживается"; break;
	case WSAESOCKTNOSUPPORT: msgText = "Тип сокета не поддерживается"; break;
	case WSAEOPNOTSUPP: msgText = "Операция не поддерживается"; break;
	case WSAEPFNOSUPPORT: msgText = "Тип протоколов не поддерживается"; break;
	case WSAEAFNOSUPPORT: msgText = "Тип адресов не поддерживается протоколом"; break;
	case WSAEADDRINUSE: msgText = "Адрес уже используется"; break;
	case WSAEADDRNOTAVAIL: msgText = "Запрошенный адрес не может быть использован"; break;
	case WSAENETDOWN: msgText = "Сеть отключена"; break;
	case WSAENETUNREACH: msgText = "Сеть не достижима"; break;
	case WSAENETRESET: msgText = "Сеть разорвала соединение"; break;
	case WSAECONNABORTED: msgText = "Программный отказ связи"; break;
	case WSAECONNRESET: msgText = "Связь восстановлена"; break;
	case WSAENOBUFS: msgText = "Не хватает памяти для буферов"; break;
	case WSAEISCONN: msgText = "Сокет уже подключен"; break;
	case WSAENOTCONN: msgText = "Сокет не подключен"; break;
	case WSAESHUTDOWN: msgText = "Нельзя выполнить send: сокет завершил работу"; break;
	case WSAETIMEDOUT: msgText = "Закончился отведенный интервал времени"; break;
	case WSAECONNREFUSED: msgText = "Соединение отклонено"; break;
	case WSAEHOSTDOWN: msgText = "Хост в неработоспособном состоянии"; break;
	case WSAEHOSTUNREACH: msgText = "Нет маршрута для хоста"; break;
	case WSAEPROCLIM: msgText = "Слишком много процессов"; break;
	case WSASYSNOTREADY: msgText = "Сеть не доступна"; break;
	case WSAVERNOTSUPPORTED: msgText = "Данная версия недоступна"; break;
	case WSANOTINITIALISED: msgText = "Не выполнена инициализация WS2_32.DLL"; break;
	case WSAEDISCON: msgText = "Выполняется отключение"; break;
	case WSATYPE_NOT_FOUND: msgText = "Класс не найден"; break;
	case WSAHOST_NOT_FOUND: msgText = "Хост не найден"; break;
	case WSATRY_AGAIN: msgText = "Неавторизированный хост не найден "; break;
	case WSANO_RECOVERY: msgText = "Неопределенная ошибка"; break;
	case WSANO_DATA: msgText = "Нет записи запрошенного типа"; break;
	case WSA_INVALID_HANDLE: msgText = "Указанный дескриптор события  с ошибкой"; break;
	case WSA_INVALID_PARAMETER: msgText = "Один или более параметров с ошибкой"; break;
	case WSA_IO_INCOMPLETE: msgText = "Объект ввода-вывода не в сигнальном состоянии"; break;
	case WSA_IO_PENDING: msgText = "Операция завершится позже"; break;
	case WSA_NOT_ENOUGH_MEMORY: msgText = "Не достаточно памяти"; break;
	case WSA_OPERATION_ABORTED: msgText = "Операция отвергнута"; break;
	case WSAEINVALIDPROCTABLE: msgText = "Ошибочный сервис"; break;
	case WSAEINVALIDPROVIDER: msgText = "Ошибка в версии сервиса"; break;
	case WSAEPROVIDERFAILEDINIT: msgText = "Невозможно инициализировать сервис"; break;
	case WSASYSCALLFAILURE: msgText = "Аварийное завершение системного вызова"; break;
	default: msgText = "Error"; break;
	}
	return msgText;
}