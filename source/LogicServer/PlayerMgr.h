#ifndef __PLAYER_MGR_H__
#define __PLAYER_MGR_H__
#include <unordered_map>
#include "lock.h"
#include "Player.h"
#define  TIMER_DELAY_REMOVE_PLAYER_TIME (10*60*1000)

using namespace std;

//һ���߳�add/remove ��һ���߳�get,��Ҫ����
class CPlayerMgr
{
public:
	CPlayerMgr();
	virtual ~CPlayerMgr();
private:
	bool         m_bIsDelayRemove;    //�Ƿ��ӳ��Ƴ�
	CLock        m_lockPlayerMgr;     //��ҹ�����
	time_t       m_tCleanTime;        //����ʱ��


	//key=���ID��value=����� ָ��
	std::unordered_map<DWORD, CPlayer*> m_mapPlayerRoleID;

	//key=����ID��value=����� ָ��
	std::unordered_map<ULLONG, CPlayer*> m_mapPlayerConnectID;

private:
	//����Ƿ����
	CPlayer* IsExistPlayer(DWORD dwRoleID);
	CPlayer* IsExistPlayer(ULLONG llConnectID);

public:
	bool Init();
	inline DWORD  GetIsDelayRemove()const { return m_bIsDelayRemove; }
	inline void   SetIsDelayRemove(bool bIsDelayRemove) { m_bIsDelayRemove = bIsDelayRemove; }

	//�������
	int  AddPlayer(DWORD dwRoleID, CPlayer *pPlayer);
	int  AddPlayer(ULLONG llConnectID, CPlayer *pPlayer);
	int  AddPlayer(CPlayer *pPlayer);

	//ɾ�����
	bool RemovePlayer(DWORD dwRoleID);
	bool RemovePlayer(ULLONG llConnectID);
	bool RemovePlayer(CPlayer *pPlayer);

	//��ȡ�������
	CPlayer* GetPlayerDataByPlayerID(DWORD dwRoleID);
	CPlayer* GetPlayerDataByConnectID(ULLONG llConnectID);
	CPlayer* GetPlayerDataByRoleName(char* pRoleName);

	//��ɨ����
	void CleanPlayerData();
};

#endif // !__PLAYER_MGR_H__
