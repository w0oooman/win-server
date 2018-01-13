#ifndef __MAINMGR_H__
#define __MAINMGR_H__
#include "KernelMgr.h"
#include "SqlServerHandle.h"
#include "singleton.h"
#include "NetMsg.h"
#include "ServerLogicHandle.h"
#include "MySqlHandle.h"
#include "DistriServerHandle.h"

//#define  _USE_MYSQL_  //_USE_SQLSERVER_

class CKernelMgr;
class CSqlServerHandle;
class CServerLogicHandle;
class CMySqlHandle;
class CDistriServerHandle;


//��������������
//��Ҫ�̳д���
/*final (VS2013��֧��)*/class CMainMgr :public CKernelMgr, virtual public CNoInherit < CMainMgr >
{
public:
	CMainMgr();
	virtual ~CMainMgr();
private:
	//CKernelMgr * pKernelMgr_;    //�ں˹�����
	CSqlServerHandle         *m_pSqlServer;        //���ݿ�ӿ�
	CMySqlHandle             *m_pMySql;            //���ݿ�ӿ�
	CServerLogicHandle       *m_pServerLogic;      //�������߼�
	CDistriServerHandle      *m_pDServerHandle;    //�ֲ�ʽ�����
public:
	virtual void OnEvent(int timerID, void *data);

	//�ͷ��������
	virtual void OnCloseConnect(ULLONG llConnectID);
	virtual void DeleteTimerData(const void *data);
public:
	bool  Init(DWORD dwMaxCount, DWORD dwListenPort);
	bool  Start();

	bool  UseSqlServer();
	bool  UseMySql();
	bool  UseLua();

	//�ֲ�ʽ�����
	bool  InitDistri(DWORD dwMaxCount, DWORD dwListenPort);
	bool  StartDistri();

	//��ͨ��Ϣ����
	bool  OnNormalMsgHandleOld(NetMsgHead* pMsgHead, const void* pData, DWORD dwIndex, DWORD dwRoundIndex);
	bool OnNormalMsgHandle(ULLONG llConnectID, const void* pData, DWORD dwSize);
	//���ݿ���Ϣ����
	bool  OnDBMsghandle(ULLONG llConnectID, const void* pData, DWORD dwSize, WORD wDBType);

	//���¼��ؽű�
	void ResetScript();
public:
	inline  CSqlServerHandle* GetSqlServerPtr(){ return m_pSqlServer; }
	inline  CMySqlHandle* GetMySqlPtr(){ return m_pMySql; }
	inline  CServerLogicHandle* GetServerLogicHandlePtr(){ return m_pServerLogic; }
};


#endif