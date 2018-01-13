#ifndef __NETERROR_H__
#define __NETERROR_H__
#include  <string>
#include  "define.h"
using namespace std;

class KERNEL_ENGINE_CLASS CNetErr
{
private:
	string m_strErrorinfo;
public:
	//�Լ����ɴ���
	CNetErr(string strErrorinfo);
	//���Զ����ɴ���
	CNetErr(string strErrorinfo, bool bIsJoin);
	//�Զ����ɴ���
	CNetErr();
	virtual ~CNetErr();
private:
	int  GetErrorID();
	void SetErrorinfo();
public:
	string GetErrText(){ return m_strErrorinfo; }
	operator string();
	operator char*();

};

#endif