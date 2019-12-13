#include "bhvclient.h"
std::string BHVClient::result = "0";
BHVClient::BHVClient() {
}	

void BHVClient::sendMessage(std::string data_string) {
	const char* data = data_string.c_str();
	WSADATA wsaData;
	int iResult = 0;
	int iFamily = AF_INET;
	int iType = SOCK_STREAM;
	int iProtocol = IPPROTO_TCP;
	SOCKET sock = INVALID_SOCKET;
	
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		wprintf(L"WSAStartup failed: %d\n", iResult);
		return;
	}

	sock = socket(iFamily, iType, iProtocol);
	if (sock == INVALID_SOCKET)
		wprintf(L"socket function failed with error = %d\n", WSAGetLastError());
	else {
		wprintf(L"socket function succeeded\n");
		sockaddr_in clientService;
		clientService.sin_family = AF_INET;
		clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
		clientService.sin_port = htons(PORT);
		iResult = connect(sock, (SOCKADDR *)&clientService, sizeof(clientService));
		if (iResult == SOCKET_ERROR) {
			wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
			iResult = closesocket(sock);
			if (iResult == SOCKET_ERROR)
				wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return;
		}
		send(sock, data, strlen(data), 0);
		char buf[BUFLEN] = { 0 };
		recv(sock, buf, sizeof(buf), 0);
		if (iResult == SOCKET_ERROR) {
			printf("read failed: %d\n", WSAGetLastError());
			closesocket(sock);
			WSACleanup();
			return;
		}

		iResult = closesocket(sock);
		if (iResult == SOCKET_ERROR) {
			wprintf(L"closesocket failed with error = %d\n", WSAGetLastError());
			WSACleanup();
			return;
		}
		wprintf(L"Socket worked!\n");
		result = std::string(buf, std::find(buf, buf + BUFLEN, '\0'));
		
	}

	WSACleanup();
}
