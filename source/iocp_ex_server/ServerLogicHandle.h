#ifndef __SERVER_LOGIC_HANDLE__H__
#define __SERVER_LOGIC_HANDLE__H__
#include "MainMgr.h"
#include "PlayerMgr.h"

class CMainMgr;
class CPlayerMgr;

#define  TIMER_DELAY_REMOVE_PLAYER_TIME (10*1000)

//��Ϸ�������߼�����
class CServerLogicHandle
{
public:
	CServerLogicHandle();
	virtual ~CServerLogicHandle();
private:
	CMainMgr     *m_pMainMgr;
	CPlayerMgr   *m_pPlayerMgr;        //��ҹ���ӿ�
public:
	bool  Init(CMainMgr *pMainMgr);
	bool  OnMsgHandle(ULLONG llConnectID, const void* pData, DWORD dwSize);
	//��ʱ���¼�
	void  OnEvent(int timerID, void *data);
	//�Ƴ����
	void  OnCloseConnect(ULLONG llConnectID);
public:
	//��¼���.byResult:0 �ɹ�; > 0 ʧ�ܴ�����
	void OnLoginComplete(ULLONG llConnectID, BYTE byResult, CPlayer *pPlayer);
};

#endif