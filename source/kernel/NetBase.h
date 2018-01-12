#ifndef __NETBASE_H__
#define __NETBASE_H__
#ifdef _MSC_VER
#include <WinSock2.h>
#else
#include<sys/socket.h>
#endif
#include  "NetError.h"

/* �Ƿ�ʹ�û���buff */
//#define   IS_USE_CIRCLE_BUFFER

extern bool WSAInit();
extern bool WSAUnInit();

class CNetBase
{
private:
	SOCKET       m_socket;
	sockaddr_in  m_sockaddr;
public:
	CNetBase();
	virtual ~CNetBase();
protected:
	struct tagThreadData
	{
		HANDLE    event;
		HANDLE    iocp;
		void     *netmgr;
		void     *data;
	};
private:
	void SetRecvSendBuf(SOCKET nSocket, DWORD *dwRecvBuf, DWORD *dwSendBuf);    //���ý���/����buffer
protected:
	/*inline*/  void  SetSockAddr(sockaddr_in &addr);
public:
	virtual void CloseSocket();
public:
	bool  CreateSocket();
	bool  Bind(DWORD dwPort);
	bool  Listen();
	bool  Accept();
	bool  Connect();
	void  ShutDown(int how);

	/*inline*/ SOCKET GetSocket();

	//true:�Ϸ�
	/*inline */bool IsValidSocket();
};                                                

#endif