#ifndef __TCP_SOCKET__H__
#define __TCP_SOCKET__H__

#include  "define.h"
#include  "NetMgr.h"
#include  "lock.h"

//������define.h���������иĶ������±�������ļ�

//��������
#define   SOCKET_RCV        1
#define   SOCKET_SND        2

//ip��ַ��󳤶�
#define   IPADDRESS_MAX_LENGTH   (32)

//�������Ϸ�����
#define   TCPSOCKET_INVALID_INDEX  (~0)

//�����ص�����
#define   SEND_OVERLAPPED_LIMIT  (10)

class CNetMgr;
class CTCPSocket
{
	friend /*class*/ CNetMgr;

private:
	bool            bRecving_;                      //�Ƿ�������
	bool            bSending_;                      //�Ƿ������
	SOCKET          socket_;                        //�ͻ���socket
	CNetMgr        *pNetMgr_;                       //�������
	DWORD           dwIndex_;                       //�ͻ�������
	DWORD           dwRoundIndex_;                  //ѭ������
	sockaddr_in     addr_;                          //�ͻ��˵�ַ
	char            ipAddr_[IPADDRESS_MAX_LENGTH];  //�ͻ���IP
	BYTE            byLoseHeartBeatTimes_;          //δ�յ���������

	NETOVERLAPPED   SendOverLPData_;                //���ͽṹ
	NETOVERLAPPED   RecvOverLPData_;                //���սṹ
	char           *sendBuf_;                       //���ͻ���
	char           *recvBuf_;                       //���ջ���
	DWORD           dwSendLen_;                     //��ǰ���ͳ���
	DWORD           dwRecvLen_;                     //��ǰ���ճ���
	CLock           SingleLock_;                    //��

#ifdef IS_USE_CIRCLE_BUFFER
	char           *recvTmpBuf_;                    //���λ�����ʱbuf
	DWORD           m_dwRecvBegin;                  //���λ�������ʼ
	DWORD           m_dwRecvEnd;                    //���λ���������
#endif

	DWORD           dwTotalRecvLen_;                //���ջ����С
	DWORD           dwTotalSendLen_;                //���ͻ����С  

	bool            bIsListHaveData_;               //�Ƿ�������������
	CDoubleRingList<tagSData> List_;                //����buffer�������ݴ�����

public:
	CTCPSocket(DWORD dwIndex);
	virtual ~CTCPSocket();

private:
	bool IsValidRoundIndex(DWORD dwRoundIndex)const;
	void PushSendList(void* pSendData, DWORD dwSendLen);
	void SetIndex(DWORD dwIndex);

public:
	bool IsCanClose();
	void ResetData();
	void Attach(SOCKET soc, sockaddr_in &addr, DWORD dwRoundIndex);
	bool RecvData();
	bool SendDataOld(DWORD dwMainID, DWORD dwSubID, DWORD dwRoundIndex);                                    //������Ϣ������������
	bool SendDataOld(DWORD dwMainID, DWORD dwSubID, void* pMsgData, DWORD dwMsgLen, DWORD dwRoundIndex);    //������Ϣ���������ݼ����ݳ���
	bool SendDataOld(void* pAllMsgData, DWORD dwAllMsgLen, DWORD dwRoundIndex);                             //������Ϣ������������Ϣ����
	bool SendData(DWORD dwRoundIndex, void* pAllMsgData, DWORD dwAllMsgLen);                                //������Ϣ������������Ϣ����
	bool SendData(void* pAllMsgData, DWORD dwAllMsgLen);                                                    //��Ϣת��������������Ϣ����

	bool WSASendData();
	bool OnRecvComplete(DWORD dwRoundIndex);
#ifdef IS_USE_CIRCLE_BUFFER
	bool OnRecvCompleteCircle(DWORD dwRoundIndex);
#endif
	bool OnSendComplete(DWORD dwSendCount, NETOVERLAPPED* pNetOL);
	bool CloseSocket(DWORD dwRoundIndex);
	bool IsValidSocket();

	void     SetNetMgr(CNetMgr* pNetMgr);
	DWORD    GetIndex();
	DWORD    GetRoundIndex();
	ULLONG   GetConnectID();
	CNetMgr* GetNetMgr();
	inline   SOCKET GetSocket();
	BYTE     GetHeartBeatTimes();
	void     AddHeartBeatTimes();
	char*    GetIpAddress() const;
	CLock*   GetLock() const;
	void     SetRecvStatus(bool bRecving);
	void     SetSendStatus(bool bSending);
};

#endif
