#ifndef __LOGIN_SERVER_LOGIC_H__
#define __LOGIN_SERVER_LOGIC_H__
#include "KernelMgr.h"
#include "NetMsg.h"
#include "ServerRegister.h"
#include "LoginServer.h"
class CLoginServer;

/***********************************************************
*��¼�����������,���߼�������ͨ��
***********************************************************/

class CLoginServerLogic : public CKernelMgr
{
private:
	CLoginServer     *m_pLoginServer;
	CServerRegister  *m_pServerRegister;
public:
	CLoginServerLogic();
	virtual ~CLoginServerLogic();
public:
	virtual void OnEvent(int timerID, void *data);
	virtual void OnCloseConnect(ULLONG llConnectID);

public:
	bool  Init();
	bool  Start();

	//��Ϣ����(����false��رյ�ǰ����)
	bool  OnNormalMsgHandle(ULLONG llConnectID, const void* pData, DWORD dwSize);
	void  SetLoginServerPtr(CLoginServer *pLoginServer);

	bool  SendDataByIndex(WORD wServerIndex, CNetMsgHead* pAllMsgData, DWORD dwAllMsgLen);
	void  SendData2LogicServer(WORD wServerIndex, CNetMsgHead *pNetMsgHead, DWORD dwSize);
};

#endif