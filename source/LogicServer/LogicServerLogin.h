#ifndef __LOGIC_SERVER_LOGIN_H__
#define __LOGIC_SERVER_LOGIN_H__
#include "KernelMgr.h"
#include "NetMsg.h"
class CLogicServer;

/***********************************************************
*�߼�������,���¼������ͨ��
***********************************************************/

class CLogicServerLogin : public CClientCKernelMgr
{
private:
	CLogicServer   *m_pLogicServer;
public:
	CLogicServerLogin();
	virtual ~CLogicServerLogin();
public:
	virtual void OnEvent(int timerID, void *data);

	//��Ϣ����(����false��رյ�ǰ����)
	virtual bool OnNetMessage(const void* pData, DWORD dwSize);


public:
	bool  Init(LPCTSTR lpIP, USHORT usPort);
	bool  Start();
	void  SetLogicServerPtr(CLogicServer *pLogicServer);
	void  OnCloseConnect(ULLONG llConnectID);

};

#endif