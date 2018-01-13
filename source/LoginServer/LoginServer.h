#ifndef __LOGIN_SERVER_H__
#define __LOGIN_SERVER_H__
#include "KernelMgr.h"
#include "NetMsg.h"
#include "LoginServerLogic.h"
#include "LoginServerDB.h"

class CLoginServerDB;
class CLoginServerLogic;

/***********************************************************
*��¼������,�����ط�����ͨ��(�������ע��/��¼��)
***********************************************************/

///*final (VS2013��֧��)*/class CGatewayServer : public CKernelMgr, virtual public CNoInherit < CGatewayServer > //��Ҫ�̳д���
class CLoginServer : public CClientCKernelMgr
{
private:
	CLoginServerDB      *m_pLoginServerDB;
	CLoginServerLogic   *m_pLoginServerLogic;
public:
	CLoginServer();
	virtual ~CLoginServer();
public:
	virtual void OnEvent(int timerID, void *data);

	//��Ϣ����(����false��رյ�ǰ����)
	virtual bool OnNetMessage(const void* pData, DWORD dwSize);

public:
	bool  Init(LPCTSTR lpIP, USHORT usPort);
	bool  Start();
	bool  OnUserRegister(ULLONG llConnectID, CNetMsgHead* pNetMsgHead, DWORD dwSize);
	bool  OnUserLogin(ULLONG llConnectID, CNetMsgHead* pNetMsgHead, DWORD dwSize);
	bool  OnUserEnter(ULLONG llConnectID, CNetMsgHead* pNetMsgHead, DWORD dwSize);
	bool  OnUserOffline(ULLONG llConnectID, CNetMsgHead* pNetMsgHead, DWORD dwSize);

	inline CLoginServerLogic* GetLoginServerLogicPtr(){ return m_pLoginServerLogic; }
	inline CLoginServerDB* GetLoginServerDBPtr(){ return m_pLoginServerDB; }
};

#endif