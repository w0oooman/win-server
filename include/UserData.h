#ifndef __USER_DATA_H__
#define __USER_DATA_H__
#include "define.h"

class CUserData
{
public:
	DWORD  m_dwRoleID;        //���ID
	char   m_szAccountName[USER_NAME_MAX_LEN];  //����ʺ�
	char   m_szRoleName[USER_NAME_MAX_LEN];     //�����ɫ��
	char   m_szPassWord[USER_PWD_MAX_LEN];      //����
	DWORD  m_dwMoney;          //���
	DWORD  m_dwDiamond;        //��ʯ
	DWORD  m_dwPoint;          //���� 
public:
	CUserData()
	{
		Reset();
	}
	virtual ~CUserData()
	{

	}
	void Reset()
	{
		m_dwMoney = 0;
		m_dwDiamond = 0;
		m_dwPoint = 0;
		m_dwRoleID = 0;
		memset(m_szAccountName, 0, sizeof(m_szAccountName));
		memset(m_szRoleName, 0, sizeof(m_szRoleName));
		memset(m_szPassWord, 0, sizeof(m_szPassWord));
	}
};

#endif