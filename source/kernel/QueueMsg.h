#ifndef __QUEUEMSG_H__
#define __QUEUEMSG_H__
#include  "lock.h"
#pragma warning(1:4519)

//��ͨ˫���������
template<typename TYPE, typename ARG_TYPE = const TYPE&>
class CQueueList
{
protected:
	struct CNode
	{
		CNode* pPrev;
		CNode* pNext;
		TYPE   data;
	};
	CNode*     m_pNodeHead;
	CNode*     m_pNodeTail;
	DWORD      m_dwCount;

public:
	CQueueList();
	~CQueueList();
public:
	DWORD  GetCount() const;
	void   Clear();

	//����CNode
	bool  PUSHTail(ARG_TYPE newElement);

	//�ͷ�CNode(delete CNode)
	TYPE  POPHead();

	//����һ���ڵ�
	void  AddTail(void *node);

	//�ͷ�CNode(��delete CNode)
	void* RemoveHead();

	//����CNode
	TYPE  operator[](const DWORD key);
};







struct tagQueueData
{
	BYTE           byQueueType;   //��������
	WORD           wDBType;       //���ݿ�����
	DWORD          dwSize;        //pQueueData��С

	ULLONG         llConnectID;   //����ID
	const void    *pData;         //Դ����ָ��

	char           pQueueData[];  //��������
};


//���л���
class CQueueBase
{
protected:
	HANDLE                                    QueueIOCP_;      //���ж˿�
public:
	CQueueBase();
	virtual ~CQueueBase();
	void    SetLimitSize(DWORD dwLimitSize);
	void    SetQueueIOCP(HANDLE hIOCP);
protected:
	tagQueueData*   AddData(ULLONG llConnectID, const void* pData, DWORD dwSize, BYTE byQueueType, WORD wDBType = 0);
	tagQueueData*   AddDataOld(DWORD dwMainID, DWORD dwSubID, const void* pData, DWORD dwSize, BYTE byQueueType);
	tagQueueData*   AddData(const void* pData, DWORD dwSize, BYTE byQueueType);
	tagQueueData*   AddData(ULLONG llConnectID, BYTE byQueueType);
};


//��Ϣ����
class CQueueMsg:public CQueueBase
{
private:
	CLock                                     QueueLock_;      //������
	CQueueList<tagQueueData*, tagQueueData*>  QueueList_;      //���б�
public:
	CQueueMsg();
	~CQueueMsg();
	bool   AddData(ULLONG llConnectID, const void* pData, DWORD dwSize, BYTE byQueueType, WORD wDBType = 0);
	bool   AddDataOld(DWORD dwMainID, DWORD dwSubID, const void* pData, DWORD dwSize, BYTE byQueueType);
	bool   AddData(const void* pData, DWORD dwSize, BYTE byQueueType);
	bool   AddData(ULLONG llConnectID, BYTE byQueueType);
	bool   GetData(tagQueueData* pData, DWORD dwSize);
};


/************************************************************************/
/* �����м�һ��������ƣ���ֹ�û����⹥������ɷ��������г����������ڴ���������
   ������Խ��Խ�࣬��������û��޷��������������ձ�����
*/
/************************************************************************/

//��������
class CLockFreeQueue
{
public:
	DWORD   dwHead_;
	DWORD   dwTail_;
	DWORD   dwSize_;
	void    **ppBuf_;
public:
	CLockFreeQueue(DWORD dwSize);
	~CLockFreeQueue();
};

class CLockFreeMgr:public CQueueBase
{
private:
	CLock            QueueLock_;                                 //������
	DWORD            dwLimitSize_;                               //��������
	CLockFreeQueue  *pLockFreeQueue_;                            //���нṹ

public:
	CLockFreeMgr();
	~CLockFreeMgr();
private:
	bool   PUSHBack(void *data);
	void*  POPFront();
public:
	void   SetLimitSize(DWORD dwLimitSize);
	bool   AddData(ULLONG llConnectID, const void* pData, DWORD dwSize, BYTE byQueueType, WORD wDBType = 0);
	bool   AddDataOld(DWORD dwMainID, DWORD dwSubID, const void* pData, DWORD dwSize, BYTE byQueueType);
	bool   AddData(const void* pData, DWORD dwSize, BYTE byQueueType);
	bool   AddData(ULLONG llConnectID, BYTE byQueueType);
	bool   GetData(tagQueueData* pData, DWORD dwSize);
};

#endif