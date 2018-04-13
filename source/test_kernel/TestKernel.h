#ifndef __TEST_KERNEL_H__
#define __TEST_KERNEL_H__
#include "KernelMgr.h"
#include "NetMsg.h"
#include "ServerRegister.h"


class CTestKernel : public CKernelMgr
{
public:
	CTestKernel();
	virtual ~CTestKernel();
public:
	virtual void OnEvent(int timerID, void *data);
	virtual void OnCloseConnect(ULLONG llConnectID);

public:
	bool  Init();
	bool  Start();

	//��Ϣ����(����false��رյ�ǰ����)
	bool  OnNormalMsgHandle(ULLONG llConnectID, const void* pData, DWORD dwSize);
};

#endif