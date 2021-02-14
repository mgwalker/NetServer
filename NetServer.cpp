#include "NetServer.h"

NetServer::NetServer()
{
	#ifdef __NS_VERBOSE
		printf("(VERBOSE MODE) SERVER: Constructor\n");
	#endif
	this->_protocol	= SOCK_STREAM;
	this->_lastErr	= 0;
}

NetServer::~NetServer()
{
	#ifdef __NS_VERBOSE
		printf("(VERBOSE MODE) SERVER: Destructor");
	#endif
	closesocket(this->_sSocket);
}

int NetServer::Listen(int port)
{
	#ifdef WIN32
		#ifdef __NS_VERBOSE
			printf("(VERBOSE MODE) SERVER: WSA Startup\n");
		#endif
		if(WSAStartup(MAKEWORD(1,1), &this->_wsaData) != 0)
		{
			this->_lastErr = 300;
			return 300;
		}
	#endif

	// Create the listener socket
	#ifdef __NS_VERBOSE
		printf("(VERBOSE MODE) SERVER: Create socket\n");
	#endif
	if((this->_sSocket = socket(AF_INET, this->_protocol, 0)) == INVALID_SOCKET)
	{
		this->_lastErr = 301;
		return 301;
	}

	// Set the socket options
	char yes = 1;
	#ifdef __NS_VERBOSE
		printf("(VERBOSE MODE) SERVER: Set socket options\n");
	#endif
	if(setsockopt(this->_sSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(char)) == -1)
	{
		this->_lastErr = 302;
		return 302;
	}

	// Clear the socket address structure
	memset(&this->_iSockAddr, 0, sizeof(this->_iSockAddr));

	// Set the socket family to internet
	// Set the socket to listen on the port specified
	// Bind to whatever address is available
	this->_iSockAddr.sin_family = AF_INET;
	this->_iSockAddr.sin_port   = htons(port);
	this->_iSockAddr.sin_addr.s_addr = INADDR_ANY;

	// Bind the socket
	#ifdef _NW_VERBOSE
		printf("(VERBOSE MODE) SERVER: Bind socket\n");
	#endif
	if(bind(this->_sSocket, (SOCKADDR*)&this->_iSockAddr, sizeof(SOCKADDR)) == -1)
	{
		this->_lastErr = 303;
		return 303;
	}

	// Begin listening
	#ifdef _NW_VERBOSE
		printf("(VERBOSE MODE) SERVER: Socket listen\n");
	#endif
	if(listen(this->_sSocket, 2) == -1)
	{
		this->_lastErr = 304;
		return 304;
	}

	// Start the listener thread
	this->_lThread = (HANDLE)_beginthread(&NetServer::ListenThread, 0, (void*)&this->_sSocket);

	// All good, return 0
	return 0;
}

void NetServer::ListenThread(void* args)
{
	#ifdef __NS_VERBOSE
		printf("(VERBOSE MODE) SERVER: Listener thread started.\n");
	#endif

	SOCKET		srv = *(SOCKET*)args;	// Server socket
	SOCKET		_inS;					// Incoming socket
	SOCKADDR_IN	_inA;					// Incoming socket address struct
	int			sze = sizeof(SOCKADDR_IN);

	// Clear the incoming struct
	memset(&_inA, 0, sze);

	// Accept connections while there are no errors
	while((inS = accept(srv, (SOCKADDR*)&_inA, &sze)) != -1)
	{
		#ifdef
			printf("(VERBOSE MODE) SERVER: Got a connection.\n");
		#endif


	}

	// There was an error.  Stop listening.
	#ifdef
		printf("(VERBOSE MODE) SERVER: Listener thread exitting.\n");
	#endif
}

int NetServer::ListenUDP(int port)
{
	this->_protocol = SOCK_DGRAM;
	return this->Listen(port);
}

char* NetServer::lastError()
{
    return "Err";	
}