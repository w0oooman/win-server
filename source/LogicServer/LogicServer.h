#ifndef __LOGIC_SERVER_H__
#define __LOGIC_SERVER_H__
#include "KernelMgr.h"
#include "NetMsg.h"
#include "PlayerMgr.h"

class CLogicServerLogin;

/***********************************************************
*�߼�������,�����ط�����ͨ��(���������Ϣ)����DBServerͨ��
***********************************************************/

class CLogicServer : public CClientCKernelMgr
{
private:
	//CLogicServerLogin  *m_pLogicServerLogin;
	CPlayerMgr         *m_pPlayerMgr;
public:
	CLogicServer();
	virtual ~CLogicServer();
private:
	bool UseLua();
	void DeleteTimerData(const void *data);
public:
	virtual void OnEvent(int timerID, void *data);

	//��Ϣ����(����false��رյ�ǰ����)
	virtual bool OnNetMessage(const void* pData, DWORD dwSize);

public:
	bool  Init();
	bool  Start();
	bool  SendBatchData(const void* pAllMsgData, DWORD dwAllMsgLen);
	void  UserData2Logic(CDUserData2LogicMsg *pUserData2Logic);
	void  OnCloseConnect(ULLONG llConnectID);
	void  ResetScript();
};

#endif