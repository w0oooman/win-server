#ifndef __DB_SERVER_H__
#define __DB_SERVER_H__
#include "KernelMgr.h"
#include "NetMsg.h"
#include "DBManager.h"

/***********************************************************
*���ݿ������
***********************************************************/

class CDBServer : public CKernelMgr
{
private:
	bool           m_bSuccess;   //�Ƿ��ʼ��/�����ɹ�
	CDBManager    *m_pDBmanager;
public:
	CDBServer();
	virtual ~CDBServer();
public:
	virtual void OnEvent(int timerID, void *data);

public:
	bool  Init(DWORD dwMaxCount, DWORD dwListenPort);
	bool  Start();

	//��Ϣ����(����false��رյ�ǰ����)
	bool  OnNormalMsgHandle(ULLONG llConnectID, const void* pData, DWORD dwSize);

	void  SaveData(CNetMsgHead *pNetMsgHead, DWORD dwSize);
};

#endif