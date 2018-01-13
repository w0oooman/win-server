#ifndef __NETMGRC_H__
#define __NETMGRC_H__
#include "NetBase.h"
#include "lock.h"
#include "../include/NetMsg.h"
#include "../source/kernel/NetMgr.h"
#define CLIENT_SND_SIZE   2048
#define CLIENT_RCV_SIZE   1024*24
 
class CTCPSocket
{
public:
	CTCPSocket();
	virtual ~CTCPSocket();

public:
	bool SendData();
	bool RecvData();
};

class CNetMgrC:public CNetBase
{
private:
	CLock     SingleLock_;
	char     *szSendbuf_;     //��������buffer
	char     *recvBuf_;     //��������buffer
	DWORD     dwSendLen_;
	DWORD     dwRecvLen_;
	DWORD     dwCheckCode_;
	HANDLE    hEvent_;                         //�ȴ��¼�
	NETOVERLAPPED RecvOverLPData_;

public:
	CNetMgrC();
	virtual ~CNetMgrC();
private:
	CLock&   GetLock(){ return SingleLock_; }


public:
	bool Init(LPCTSTR lpIP,USHORT usPort);
	bool PrepareRecv();
	//bool Start();
	bool SendData(DWORD dwMainID,DWORD dwSubID);                                        //������Ϣ������������
	bool SendData(DWORD dwMainID, DWORD dwSubID, void* pMsgData, DWORD dwMsgLen);       //������Ϣ���������ݼ����ݳ���
	bool SendData(CNetMsgHead* pNetMsgHead, DWORD dwAllMsgLen);                         //������Ϣ������������Ϣ����
	bool CheckSendData();
	bool OnRecvComplete();
	bool OnNetMessage(char* pMsgData,DWORD dwMsgLen);
	static unsigned int __stdcall SendThread(void *pData);
	static unsigned int __stdcall RecvThread(void *pData);
};                                                  

#endif