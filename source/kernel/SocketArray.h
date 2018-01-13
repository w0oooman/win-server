#pragma  once

#include  "NetMgr.h"
#include  "TCPSocket.h"
class CTCPSocket;

class CSocketArray
{
private:
	UINT            nLimitCount_;            //��������
	UINT            nActiveCount_;           //��������
	UINT            nNowMaxCount_;           //��ǰ�������
	CTCPSocket    **ppTCPFixedSocketArray_;  //socket�̶�ָ������
	CTCPSocket    **ppTCPSocketArray_;       //socket�ָ������
	CTCPSocket    **ppTempTCPSocketArray_;   //socket��ʱ�ָ������
public:
	CSocketArray();
	virtual ~CSocketArray();
private:
	void         UnInit();
public:
	bool         Init(UINT nMaxCount);
	CTCPSocket*  GetFixedItem(UINT index);               //�̶���
	CTCPSocket*  GetActiveItem(UINT index);              //���
	UINT         GetActiveCount();
	CTCPSocket** GetTempActiveItemPPtrSet();             //��ȡ���ptr����
	int          GetFixIndex();
	CTCPSocket*  GetItem();
	bool         RemoveItem(CTCPSocket* pTCPSocket);
};