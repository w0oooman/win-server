#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "define.h"
#include "UserData.h"
#include "LogicServerLogin.h"
#include "SaveType.h"
extern CLogicServerLogin  *m_pLogicServerLogin;
extern CDSaveDataMsg *m_pSaveData;

class CPlayer
{
public:
	CPlayer();
	virtual ~CPlayer();
private:
	ULLONG m_llConnectID;     //�������ID

	bool   m_bIsWillRemove;   //�Ƿ��Ƴ����
	DWORD  m_dwCutTimer;      //�������ʱ��
public:
	CUserData  *m_pUserData;  //�û�����
public:
	inline DWORD  GetPlayerRoleID(){ return m_pUserData->m_dwRoleID; }
	inline char*  GetRoleName(){ return m_pUserData->m_szRoleName; }
	inline DWORD  GetRoleNameLen(){ return sizeof(m_pUserData->m_szRoleName); }

	inline ULLONG GetPlayerConnectID()const { return m_llConnectID; }
	inline DWORD  GetIsWillRemove()const { return m_bIsWillRemove; }
	inline DWORD  GetCutTime()const { return m_dwCutTimer; }

	inline void   SetPlayerConnectID(ULLONG llConnectID) { m_llConnectID = llConnectID; }
	inline void   SetIsWillRemove(bool bIsWillRemove) { m_bIsWillRemove = bIsWillRemove; }
	inline void   SetCutTime(DWORD dwCutTimer) { m_dwCutTimer = dwCutTimer; }

	void SetUserData(CUserData *pUserData);

	//���泣������(short/int/int64/�ṹ���)
	template<typename TYPE>
	void SaveData(short type, TYPE value)
	{
		m_pSaveData->m_dwID = GetPlayerRoleID();
		*(TYPE*)(m_pSaveData->m_szData) = value;
		m_pSaveData->m_shType = type;
		m_pLogicServerLogin->SendData(m_pSaveData, (DWORD)(&(((CDSaveDataMsg*)0)->m_szData))+sizeof(value));
	}
	//���� �ַ���/�ṹ�� ����
	void SaveData(short type, const void *pData, DWORD dwSize);
public:
	inline DWORD  GetPlayerPoint(){ return m_pUserData->m_dwPoint; }
	inline DWORD  SetPlayerPoint(DWORD dwPoint){ m_pUserData->m_dwPoint = dwPoint; SaveData(SAVE_POINT, dwPoint); }
};

#endif // !__PLAYER_H__
