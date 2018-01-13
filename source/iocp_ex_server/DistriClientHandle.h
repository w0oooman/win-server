#ifndef __DISTRI_CLIENT_HANDLE__H__
#define __DISTRI_CLIENT_HANDLE__H__
#include "MainMgr.h"

class CClientMainMgr;

//�ֲ�ʽ�ͻ���
class CDistriClientHandle :public CClientCKernelMgr, virtual public CNoInherit < CDistriClientHandle >
{
public:
	CDistriClientHandle();
	virtual ~CDistriClientHandle();
public:
	bool  Init(LPCTSTR lpIP, USHORT usPort);
	bool  Start();
	//��Ϣ����
	bool  OnNetMessage(const void* pData, DWORD dwSize);
	//��ʱ����Ϣ
	virtual void OnEvent(int timerID, void *data);
};

#endif