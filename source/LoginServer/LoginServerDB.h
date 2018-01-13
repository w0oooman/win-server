#ifndef __LOGIN_SERVERDB_H__
#define __LOGIN_SERVERDB_H__
#include "KernelMgr.h"
#include "NetMsg.h"
class CLoginServer;

/***********************************************************
*��¼������,��DB������ͨ��(�������ע��/��¼��)
***********************************************************/

class CLoginServerDB : public CClientCKernelMgr
{
private:
	CLoginServer     *m_pLoginServer;
public:
	CLoginServerDB();
	virtual ~CLoginServerDB();
public:
	virtual void OnEvent(int timerID, void *data);

	//��Ϣ����
	virtual bool OnNetMessage(const void* pData, DWORD dwSize);


public:
	bool  Init();
	bool  Start();

	CLoginServer* GetLoginServerPtr();
	void  SetLoginServerPtr(CLoginServer *pLoginServer);
};

#endif