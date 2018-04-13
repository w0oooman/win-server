#ifndef __GATEWAY_SERVER_H__
#define __GATEWAY_SERVER_H__
#include "KernelMgr.h"
#include "NetMsg.h"
#include "IniParser.h"
class CGatewayServerLogic;
class CGatewayServerLogin;
struct CUserGateWayInfo;

/***********************************************************
*���ط�����,������ͻ���ͨ��,���ؾ��⡢ת���ͻ��������
***********************************************************/

///*final (VS2013��֧��)*/class CGatewayServer : public CKernelMgr, virtual public CNoInherit < CGatewayServer > //��Ҫ�̳д���
class CGatewayServer : public CKernelMgr
{
private:
	CGatewayServerLogic  *m_pGatewayServerLogic;
	CGatewayServerLogin  *m_pGatewayServerLogin;
private:
	unordered_map<ULLONG, CUserGateWayInfo*>  m_mapUserGWInfo;
public:
	CGatewayServer();
	~CGatewayServer();
public:
	virtual void OnEvent(int timerID, void *data);
	virtual void OnCloseConnect(ULLONG llConnectID);
public:
	bool  Init();
	bool  Start();

	CGatewayServerLogic* GetGatewayLogicPtr();
	CGatewayServerLogin* GetGatewayLoginPtr();

	//��Ϣ����(����false��رյ�ǰ����)
	bool  OnNormalMsgHandle(ULLONG llConnectID, const void* pData, DWORD dwSize);

	void  SetUserGateWayInfo(ULLONG llConnectID, CUserGateWayInfo* pUserGateWayInfo);
	CUserGateWayInfo* GetUserGateWayInfo(ULLONG llConnectID);
	void  RemoveUserGateWayInfo(ULLONG llConnectID);

	//�汾����
	void SendVersionError(ULLONG llConnectID);

	//�������ݵ��߼���
	bool SendData2LogicServer(ULLONG llConnectID, CNetMsgHead *pNetMsgHead, DWORD dwSize);
};



//�û������ط���Ϣ
struct CUserGateWayInfo
{
	WORD wServerIndex;      //�û���¼���߼���ID
};

#endif