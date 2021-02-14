// Include the network headers
// Win32
#ifdef WIN32
	#include <winsock.h>
	#include <process.h>
// Everything else
#else
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
#endif

// Include the other necessary headers
#include <stddef.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

class NetServer
{
	public:
		NetServer();
		~NetServer();
		int Listen(int port);
		int ListenUDP(int port);
		char* lastError();

	private:
		static void ListenThread(void* args);

		SOCKET		_sSocket;	// Server socket
		SOCKADDR_IN	_iSockAddr;	// Socket address struct
		int			_protocol;	// Protocol (TCP or UDP)
		int			_lastErr;	// Error code
		HANDLE		_lThread;	// Server listener thread

		#ifdef WIN32
			WSADATA	_wsaData;	// Needed for winsock
		#endif
};