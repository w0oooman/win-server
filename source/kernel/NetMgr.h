#ifndef __NETMGR_H__
#define __NETMGR_H__
#include  "NetBase.h"
#include  "define.h"
#include  "KernelDefine.h"
#include  "lock.h"
#include  "TimerMgr.h"
#include  "QueueMsg.h"
#include  "IKernelMgr.h"
#include  "KernelMgr.h"

class IKernelMgr;
class CClientCKernelMgr;
class CSocketArray;
class CTCPSocket;

struct OverLappedStruct
{
	OVERLAPPED    overlapped;
	WSABUF        wsabuf;
	unsigned char type;
	unsigned char issendbuff;
	DWORD         roundindex;
};
typedef struct OverLappedStruct NETOVERLAPPED;

typedef struct tagSendData
{
	DWORD len;
	DWORD nowpos;
	char *buf;
}
tagSData;

class CNetMgr :public CNetBase
{
private:
	CSocketArray    *SocketArray_;
	CLock            SockArrayLock_;   //sock������

	DWORD            dwMaxCount_;      //�������
	DWORD            dwListenPort_;    //�����˿�
	DWORD            dwThreadNum_;     //�շ��߳���
	DWORD            dwRoundIndex_;    //ѭ������

	HANDLE           hThreadEvent_;    //�߳��¼�
	HANDLE          *phRSThreadHandle_;           //�շ��߳̾��
	HANDLE           hHeartBeatThreadHandle_;     //�����߳̾��

	HANDLE           hRSIOCP_;         //����/������ȫ�˿�
	UINT             hAcceptThread_;   //�����߳̾��
	UINT             hRSThread_;       //�շ��߳̾��
	IKernelMgr     *pKernelMgr_;       //�ں˹�����
	bool             bIsRunning_;      //�Ƿ��˳�
	bool             bIsSpecialClient_;//�Ƿ�Ϊ����ͻ�������

	DWORD            dwTotalRecvLen_;  //���ջ����С
	DWORD            dwTotalSendLen_;  //���ͻ����С

	CLockFreeMgr    *pQueueBatchMsg_;  //Ⱥ������

public:
	CNetMgr();
	virtual ~CNetMgr();

private:
	CTCPSocket*       NewSocket();                            //����һ���ͻ���ʵ��
	bool              DeleteSocket(CTCPSocket* pTCPSocket);   //����һ���ͻ���ʵ��
	UINT              GetFixArrayIndex();
	CTCPSocket*       GetFixedItem(UINT index);               //�̶���
	CTCPSocket*       GetActiveItem(UINT index);              //���
	CSocketArray*     GetSocketArray();
	CLock&            GetSocketArrayLock();

public:
	bool              Init(DWORD dwMaxCount, DWORD dwListenPort,IKernelMgr* pKernelMgr);
	bool              Start();
	void              SetBuffLen(DWORD dwRecvLen, DWORD dwSendLen);  //���û���
	void              CloseSocket(CTCPSocket* pTCPSocket, DWORD dwRoundIndex);
	void              CloseSocket(ULLONG llConnectID);
	bool              OnNetMessage(ULLONG llConnectID, const char* pData, DWORD dwSize);
	DWORD             GetRoundIndex();
	CLockFreeMgr*     GetBatchQueue();
	DWORD             GetMaxCount();
	bool              IsSpecialClient();
	void              SetIsSpecialClient(bool bIsSpecialClient);


	bool SendDataOld(DWORD dwIndex, DWORD dwMainID, DWORD dwSubID, DWORD dwRoundIndex);                                      //������Ϣ������������
	bool SendDataOld(DWORD dwIndex, void* pAllMsgData, DWORD dwAllMsgLen, DWORD dwRoundIndex);                               //������Ϣ������������
	bool SendDataOld(DWORD dwIndex, DWORD dwMainID, DWORD dwSubID, void* pMsgData, DWORD dwMsgLen, DWORD dwRoundIndex);      //������Ϣ���������ݼ����ݳ���
	bool SendData(ULLONG llConnectID, void* pAllMsgData, DWORD dwAllMsgLen);                                                 //������Ϣ������������Ϣ����
	bool SendData(void* pAllMsgData, DWORD dwAllMsgLen);                                                                     //��Ϣת��
	bool SendBatchDataOld(DWORD dwMainID, DWORD dwSubID, void* pMsgData, DWORD dwMsgLen);                                    //Ⱥ����Ϣ
	bool SendBatchData(void* pMsgData, DWORD dwMsgLen);                                                               //Ⱥ����Ϣ

	static unsigned int __stdcall AcceptThread(void* pData);       //�����߳�
	static unsigned int __stdcall RSThread(void* pData);           //����/���� �߳�
	static unsigned int __stdcall HeartBeatThread(void* pData);    //�����߳�
};


#include "CommonList.h"
//�ͻ��˹�����
class CClientNetMgr:public CNetBase
{
public:
	CClientNetMgr();
	virtual ~CClientNetMgr();
private:
	char     *recvBuf_;                      //��������buffer
	char     *sendBuf_;                      //��������buffer
	DWORD     dwCheckCode_;
	HANDLE    hEvent_;                         //�ȴ��¼�
	HANDLE    hRSThreadHandle_;                //�շ��߳̾��
	HANDLE    hRSIOCP_;
	bool      bIsRunning_;                     //�Ƿ��˳�
	bool      bSending_;                       //�Ƿ�������
	bool      bIsNetCuted_;                    //�����Ƿ�Ͽ�/δ����


	CClientCKernelMgr *pKernelMgr_;            //�ں˹�����
	NETOVERLAPPED      SendOverLPData_;        //���ͽṹ
	NETOVERLAPPED      RecvOverLPData_;        //���սṹ

	DWORD     dwRecvLen_;                      //��ǰ���ճ���
	DWORD     dwSendLen_;                      //��ǰ���ͳ���
	DWORD     dwTotalRecvLen_;                 //���ջ����С
	DWORD     dwTotalSendLen_;                 //���ͻ����С   

	CLock     SendLock_;                       //������
	CLock     RecvLock_;                       //������
	CLock     NetCutedLock_;                   //��������Ͽ���־����

	bool      bIsListHaveData_;                //�Ƿ�������������
	CDoubleRingList<tagSData> List_;           //����buffer�������ݴ�����

private:
	bool PrepareRecv();
	bool OnRecvCompleteOld(DWORD dwTransNum);
	bool OnRecvComplete(DWORD dwTransNum);
	bool OnSendComplete(DWORD dwSendCount, NETOVERLAPPED* pNetOL);
	static unsigned int __stdcall RSThread(void *pData);
	bool WSASendData();
	void PushSendList(void* pSendData, DWORD dwSendLen);

public:
	virtual void CloseSocket();
public:
	bool   ReConnect();                          //����
	inline HANDLE GetEvent();
	IKernelMgr *GetKernelMgr();
	HANDLE GetIOCPHandle();

public:
	bool Init(LPCTSTR lpIP, USHORT usPort, CClientCKernelMgr *pKernelMgr);
	bool Start();
	void ResetData();
	bool SendDataOld(DWORD dwMainID, DWORD dwSubID);                                        //������Ϣ������������
	bool SendDataOld(DWORD dwMainID, DWORD dwSubID, void* pMsgData, DWORD dwMsgLen);        //������Ϣ���������ݼ����ݳ���
	bool SendDataOld(void* pAllMsgData, DWORD dwAllMsgLen);                                 //������Ϣ������������Ϣ����
	bool SendData(void* pAllMsgData, DWORD dwAllMsgLen);                                    //������Ϣ������������Ϣ����
	bool CheckSendData();
	void SetBuffLen(DWORD dwRecvLen, DWORD dwSendLen);
	void SetNetCutedStatus(bool bIsNetCuted);
	bool IsNetCuted();  //�����Ƿ�Ͽ�

};


#endif