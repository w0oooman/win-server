#ifndef __LOCK__H__
#define __LOCK__H__

#ifdef _MSC_VER
#include <WinSock2.h>
#else
#include <atomic.h>
#endif
#include "define.h"
#include "KernelDefine.h"

class KERNEL_ENGINE_CLASS CLock
{
private:
#ifdef _MSC_VER
	CRITICAL_SECTION  cs_;
#else
#endif

public:
	CLock();
	virtual ~CLock();

	//����
	inline void Lock();

	//������,�ɽ��뷵��true
	inline bool TryLock();

	inline void UnLock();
};        

class KERNEL_ENGINE_CLASS CLockMgr
{
private:
	UINT    nLockCount_;
	CLock*  pLock_;
public:
	/*bAutoΪ�����Զ�����Lock(),����Ҫ��������Lock()
	  ������ʱ����bAutoֵΪ����,���ͷ�������Ϊ0����
	  ����UnLock().
	*/
	CLockMgr(CLock* pLock, bool bAuto = true);
	virtual ~CLockMgr();
	void Lock();
	void UnLock();
};

#endif