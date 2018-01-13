#ifndef __LUA_MANAGER_H__
#define __LUA_MANAGER_H__
#include <vector>
#include "MainMgr.h"

extern "C"
{
#include "lua.h"
}

#define  LUA_DOFILE_INIT_FILE  ("Script/init.lua")

struct LUAEventData
{
	unsigned char type;
	lua_Number n;
	char *str;
};

class LUAEvent
{
public:
	int   m_interval;
	char *m_func;
	vector<LUAEventData*> m_para;
public:
	LUAEvent()
	{
		m_interval = 0;
		m_func = NULL;
		m_para.clear();
	}
	virtual ~LUAEvent()
	{
		int num = m_para.size();
		for (int i = 0; i < num; i++)
		{
			LUAEventData *pedata = m_para[i];
			switch (pedata->type)
			{

			case LUA_TSTRING:
				delete pedata->str;
				break;
			default:
				break;
			}
		}
		m_para.clear();
		delete m_func;
	}
};

class CLuaManager
{
public:
	CLuaManager();
	virtual ~CLuaManager();
private:
	lua_State   *m_ls;
	CMainMgr    *m_pMainMgr;
	int          m_nTimerID;
public:
	void LoadLua();
	void CloseLua();
	void Reset();
	void RefreshLua();
	void Init(CMainMgr *pMainMgr);
	inline lua_State *GetLuaState(){ return m_ls; }
public:
	void OnEvent(int timerID, void *data);
	int  dofile(const char* filename);
	void Register();
	void ServerStart();
	void ServerDown();
	static bool Call(lua_State *L, int stackPos);
	static bool CallFunc(lua_State *L, const char *name);
	bool ExecuteLuaFunc(const char *pFuncName,unsigned short wParaNum,...);
	int  AddEvent(int timerID, int interval, TimerCallBackFunc func = NULL, void *data = NULL, int type = CTimerMgr::CIRCLE);
	bool ClrEvent(int timerID);
	void DeleteTimerData(const void *data);
public:
	static bool OnLuaEvent(void *data);
public:
	//ȫ����ȡ���� ֱ�ӱ����ڱ���(�������ݿ�!)
	static int L_LoadTable(lua_State *L);//��ȡȫ�ֱ�
	static int L_SaveTable(lua_State *L);//����ȫ�ֱ�

	static int L_SetEvent(lua_State *L);//���ö�ʱ��
	static int L_ClrEvent(lua_State *L);//�����ʱ��
};

#endif