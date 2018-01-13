#ifndef __KERNEL_MSG_H__
#define __KERNEL_MSG_H__
#include <windows.h>

//////**********�ṹ**************/////
//old��Ϣͷ
struct NetMsgHead
{
	DWORD    dwSize;      //��Ϣ����
	DWORD    dwMainID;    //����ϢID
	DWORD    dwSubID;     //����ϢID
	DWORD    dwReserve;   //�����ֽ�
};

//new��Ϣͷ
class CNetMsgHead
{
public:
	WORD     size_;       //���ݳ���
	WORD     protocol_;   //Э��
	DWORD    reserve1_;   //�����ֽ�1
	DWORD    reserve2_;   //�����ֽ�2
public:
	CNetMsgHead(WORD protocol){ protocol_ = protocol; }
	virtual ~CNetMsgHead(){}
public:
	enum
	{
		NETMSG_GET_SERVERLIST = 1,       //��ȡ�������б�
		NETMSG_SERVER_REGISTER,          //�ڲ�������ע��
		NETMSG_USERDATA_2LOGIC,          //�û���¼�ɹ�,���û����ݷ��͵��߼���
		NETMSG_SAVE_DATA,                //��������

		NETMSG_HEART_BEAT = 100,         //����
		NETMSG_CONNECT_SUCESS,           //���ӳɹ�
		NETMSG_SERVER_FULL,              //����������
		NETMSG_VERSION_UNSAME,           //ǰ��˰汾��һ��
		NETMSG_USER_REGISTER,            //ע��
		NETMSG_USER_LOGIN,               //��¼/��ȡ��ɫ�б�
		NETMSG_USER_ENTER,               //�û�����
		NETMSG_USER_OFFLINE,             //�û�����
		NETMSG_USER_MOVE,                //�ƶ���Ϣ
		NETMSG_USER_CHAT,                //������Ϣ
		NETMSG_USER_BATTLE,              //ս����Ϣ
		NETMSG_SEND_SCRIPT,              //�ű���Ϣ

		NETMSG_MY_TEST = 1000, //����
	};
};

//=============================================================================================
//���ӳɹ�
class CDConnectSuccessMsg :public CNetMsgHead
{
public:
	DWORD m_dwKey;//��Կ
	CDConnectSuccessMsg() :CNetMsgHead(CNetMsgHead::NETMSG_CONNECT_SUCESS)
	{

	}
	virtual ~CDConnectSuccessMsg(){};
};
//.............................................................................................

struct Byte_Sum
{
	LONGLONG llByteSum;
};



#endif