#ifndef  __MSGDEFINE__H__
#define  __MSGDEFINE__H__
#include "KernelMsg.h"
#include "UserData.h"

//���������
#define  MAX_CLIENT_NUM        300

//����������
#define SERVER_CONFIG "../server.ini"
#define TEST_SERVER_CONFIG "./server.ini"

#define  GATESERVER_PORT           (8890)                      //���ط������˿�
#define  DISTRI_GATE_LOGIN_PORT    (GATESERVER_PORT+1)         //���ط�S-��¼��C �˿�
#define  DISTRI_GATE_LOGIC_PORT    (DISTRI_GATE_LOGIN_PORT+1)  //���ط�S-�߼���C �˿�
#define  DISTRI_DB_LOGIN_PORT      (DISTRI_GATE_LOGIC_PORT+1)  //DB��S-��¼��C �˿�
#define  DISTRI_LOGIN_LOGIC_PORT   (DISTRI_DB_LOGIN_PORT+1)    //��¼��S-��Ϸ��C �˿�

//�ʺų���
#define  ACCOUNT_LEN       32
//���볤��
#define  PASSWORD_LEN      32
//��ɫ������
#define  ROLENAME_LEN      32
//��ɫ�б���
#define  ROLELIST_LEN      128


///////////////////////////////////////////////
////////////////����Э�鶨��///////////////////
///////////////////////////////////////////////

//=============================================================================================
//�û���¼�ɹ�,���û����ݷ��͵��߼���
class CDUserData2LogicMsg : public CNetMsgHead
{
public:
	WORD      m_wServerIndex;
	CUserData m_UserData;
	CDUserData2LogicMsg() : CNetMsgHead(CNetMsgHead::NETMSG_USERDATA_2LOGIC)
	{
		size_ = sizeof(CDUserData2LogicMsg);
	}
	virtual ~CDUserData2LogicMsg(){}
};
//.............................................................................................

//=============================================================================================
//ǰ��˰汾��һ��
class CDVersionErrorMsg : public CNetMsgHead
{
public:
	CDVersionErrorMsg() : CNetMsgHead(CNetMsgHead::NETMSG_VERSION_UNSAME)
	{
		size_ = sizeof(CDVersionErrorMsg);
	}
	virtual ~CDVersionErrorMsg(){}
};
//.............................................................................................

//=============================================================================================
//��������
class CDSaveDataMsg : public CNetMsgHead
{
public:
	DWORD  m_dwID;    //��ɫID/���ID��
	short  m_shType;
	char   m_szData[1 << 16];
	CDSaveDataMsg() : CNetMsgHead(CNetMsgHead::NETMSG_SAVE_DATA)
	{
		size_ = sizeof(CDVersionErrorMsg);
	}
	virtual ~CDSaveDataMsg(){}
};
//.............................................................................................

//=============================================================================================
//ע���ʺ�-����
class CURegisterMsg : public CNetMsgHead
{
public:
	char m_account[ACCOUNT_LEN];
	char m_password[PASSWORD_LEN];
	CURegisterMsg() : CNetMsgHead(CNetMsgHead::NETMSG_USER_REGISTER)
	{
		memset(m_account,0,sizeof(m_account));
		memset(m_password, 0, sizeof(m_password));
		size_ = sizeof(CURegisterMsg);
	}
	~CURegisterMsg(){}
};

//ע���ʺ�-����
class CDRegisterMsg : public CNetMsgHead
{
public:
	WORD  m_wRes;
	CDRegisterMsg() : CNetMsgHead(CNetMsgHead::NETMSG_USER_REGISTER)
	{
		size_ = sizeof(CDRegisterMsg);
	}
	virtual ~CDRegisterMsg(){}
	enum 
	{
		REG_SUCCESS = 1,//ע��ɹ�
		REG_EXIST,//�ʺ��Ѿ�����
		REG_ACCOUNT_SHORT,//�ʺ�̫��
		REG_ACCOUNT_LONG,//�ʺŹ���
		REG_PWD_SHORT,//����̫��
		REG_PWD_LONG,//�������
	};
};
//.............................................................................................

//=============================================================================================
//��¼/��ȡ��ɫ�б�
class CULoginMsg : public CNetMsgHead
{
public:
	WORD m_wServerIndex; //��¼�ķ�������
	char m_account[ACCOUNT_LEN];
	char m_password[PASSWORD_LEN];
	CULoginMsg() :CNetMsgHead(CNetMsgHead::NETMSG_USER_LOGIN)
	{
		memset(m_account, 0, sizeof(m_account));
		memset(m_password, 0, sizeof(m_password));
		size_ = sizeof(CULoginMsg);
	}
	virtual ~CULoginMsg(){}
};

//��¼/��ȡ��ɫ�б�
class CDLoginMsg : public CNetMsgHead
{
public:
	WORD  m_wServerIndex;
	WORD  m_wRes;
	char  m_szRoleList[ROLELIST_LEN];
	CDLoginMsg() : CNetMsgHead(CNetMsgHead::NETMSG_USER_LOGIN)
	{
		memset(m_szRoleList, 0, sizeof(m_szRoleList));
		size_ = sizeof(CDLoginMsg);
	}
	~CDLoginMsg(){}
	enum
	{
		LOGIN_UNKNOW = 0,//δ֪����
		LOGIN_SUCCESS,//��¼�ɹ�
		LOGIN_ONLINE,//�Ѿ���¼
        LOGIN_ACCOUNT_ERR,//�ʺŲ�����
		LOGIN_PWD_ERR,//�������
	};
};
//.............................................................................................

//=============================================================================================
//����-����
class CUEnterMsg : public CNetMsgHead
{
public:
	WORD  m_wServerIndex;
	char  m_rolename[ROLENAME_LEN];
	CUEnterMsg() : CNetMsgHead(CNetMsgHead::NETMSG_USER_ENTER)
	{
		memset(m_rolename, 0, sizeof(m_rolename));
	}
	virtual ~CUEnterMsg(){}
};

//����-����
class CDEnterMsg : public CNetMsgHead
{
public:
	WORD  m_wServerIndex;
	WORD  m_wRes;
	CDEnterMsg() : CNetMsgHead(CNetMsgHead::NETMSG_USER_ENTER)
	{
		size_ = sizeof(CDEnterMsg);
	}
	~CDEnterMsg(){}
	enum
	{
		ENTER_SUCCESS = 1,
		ENTER_NOTEXIST= 2, //��ɫ������
	};
};
//.............................................................................................

//=============================================================================================
//����
class CUChatMsg : public CNetMsgHead
{
public:
	CUChatMsg() : CNetMsgHead(CNetMsgHead::NETMSG_USER_CHAT)
	{
		size_ = sizeof(CUChatMsg);
	}
	virtual ~CUChatMsg(){}
};
//.............................................................................................

//=============================================================================================
//�û�����
class CDUserOfflineMsg : public CNetMsgHead
{
public:
	CDUserOfflineMsg() : CNetMsgHead(CNetMsgHead::NETMSG_USER_OFFLINE){ }
	virtual ~CDUserOfflineMsg(){}
};

//.............................................................................................

//=============================================================================================
//����ʹ��
class CTestMsg : public CNetMsgHead
{
public:
	char buf[200];
	CTestMsg() : CNetMsgHead(CNetMsgHead::NETMSG_MY_TEST){ memset(buf, 0, sizeof(buf)); }
	virtual ~CTestMsg(){}
};

//.............................................................................................









//��ID
enum EnumMainID
{
	mmd_connect_success = 1,         //���ӳɹ� ������Կ
	mmd_server_full = 2,             //����������
	mmd_heart_beat = 3,              //�������

	//�������Ϣ��Ҫ��!!!
	mmd_player_register = 21,        //ע��
	mmd_player_login = 22,           //��¼
	mmd_player_offline = 23,         //����
	mmd_message_test = 100,          //�Լ�����
};

//��ID
//��¼
enum EnumSub_Login
{
	smd_login_success = 0,
	smd_login_syserror = 1,     //ϵͳ����
	smd_login_acount_err = 2,   //�ʺŲ�����
	smd_login_pwd_err = 3,      //�������
};


//���ݿ����
enum DBHandle
{
	db_player_register = 1,
	db_player_login = 2,
	db_get_login_times = 100,          //��ȡ��¼����
};





//��ID
//enum class MainID :unsigned int
//{
//	mmd_connect_success = 1,
//	mmd_server_full = 2,
//};
//���沿�ַ���cpp�ļ�
//bool operator == (MainID e, int a){
//	return (MainID)a == e;
//}
//bool operator == (int a, MainID e){
//	return (MainID)a == e;
//}
//
//bool operator > (MainID e, int a){
//	return e > (MainID)a;
//}
//bool operator > (int a, MainID e){
//	return (MainID)a > e;
//}

#endif
