#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include "Log.h"
#include "define.h"

using namespace std;

#define WRITELEN           1024  //�浽�೤��дһ���ļ�
#define WRITETIME          3     //дһ���ļ���ʱ����
#define WRILELOG_TIMES     10    //д�ļ��ﵽ������ر�һ���ļ�

#define OUTEST_FOLDER "LOGS"     //������ļ�������


#include "lock.h"
CLock    g_lock;
#define  LOG_LOCK() CLockMgr lockMgr(&g_lock);
#define  LOG_UNLOCK()

//#define  LOG_LOCK()
//#define  LOG_UNLOCK()


const char* GetStringTime()
{
	static char buffer[64];

	SYSTEMTIME s;
	GetLocalTime(&s);

	sprintf_s(buffer, "%d-%02d-%02d %02d:%02d:%02d", s.wYear, s.wMonth, s.wDay, s.wHour, s.wMinute, s.wSecond);

	return buffer;
}

const char* GetStringDayTime()
{
	static char buffer[64];

	SYSTEMTIME s;
	GetLocalTime(&s);

	sprintf_s(buffer, "%s/��%d-%02d-%02d��", OUTEST_FOLDER, s.wYear, s.wMonth, s.wDay);

	return buffer;
}

class CFileHandle
{
private:
	int m_nWriteTimes;
private:
	ofstream   m_stream;
	char       m_file[MAX_PATH];
public:
	char        m_buf[LOG_MAXBUFFEREX];
	__int64     m_time;
	DWORD       m_len;
public:
	CFileHandle()
	{
		m_time = 0;
		m_len = 0;
		m_nWriteTimes = 0;
	}
	virtual ~CFileHandle()
	{
		if (m_stream.is_open())
		{
			if (m_len){
				WriteLog(true);
			}
			m_stream.close();
		}	
	}

public:
	void init(const char* filename, const char* dir)
	{
		//ʹ��dir : ����ʹ���ļ���
		//ʹ��folder: ÿ��ʹ���ļ���
		sprintf_s(m_file, sizeof(m_file), "%s/%s", dir, filename);
	}

	void open()
	{
		if (m_stream.is_open()){
			m_stream.close();
		}
		m_stream.open(m_file, ios::app);

#ifdef _MSC_VER
		SetLastError(0);//��183��-���ļ��Ѵ���ʱ���޷��������ļ�
#else
#endif
	}

	void Write()
	{
		m_stream << m_buf;
		m_stream.flush();
		m_len = 0;

		/*
		ע�⼸���������printf�Ľ��:
		Log("%d 20%% 100%%", 777); -> ���˺�:777 20% 100% -> ��ӡ���:777 20%
		Log("%d 20%%q100%%", 888); -> ���˺�:888 20%q100% -> ��ӡ���:888 20q100
		*/
		printf(m_buf);  //whb
	}

	BOOL WriteLog(bool bIsLogAll)
	{
		if (!m_stream.is_open())
		{
			open();
		}

		if (m_stream.is_open())
		{
			Write();
			if (++m_nWriteTimes >= WRILELOG_TIMES || bIsLogAll) //whb
			{
				m_nWriteTimes = 0;
				m_stream.close();
			}
		}
		return TRUE;
	}
};

class CFileHandleMgr
{
public:
	CFileHandleMgr(){
		//���м�¼�����Ŀ¼
		if (_access(OUTEST_FOLDER, 0) == -1)
		{
			if (0 != _mkdir(OUTEST_FOLDER))
			{
#ifdef _MSC_VER
				CreateDirectory(OUTEST_FOLDER, 0);
				GetLastError();
#endif
			}
		}

		const char* folder = GetStringDayTime();
		bool flag = true;
		if (_access(folder, 0) == -1)
		{
			if (0 != _mkdir(folder))
			{
#ifdef _MSC_VER
				CreateDirectory(folder, 0);
				GetLastError();
#endif
			}
		}

		m_log = new CFileHandle();
		m_log->init("log.txt", folder);

		m_thread = new CFileHandle();
		m_thread->init("thread.txt", folder);

		m_debug = new CFileHandle();
		m_debug->init("debug.txt", folder);

		m_db = new CFileHandle();
		m_db->init("db.txt", folder);

		m_dserver = new CFileHandle();
		m_dserver->init("dserver.txt", folder);

		m_dclient = new CFileHandle();
		m_dclient->init("dclient.txt", folder);
	}
	virtual ~CFileHandleMgr(){
		SAFE_DELETE(m_log);
		SAFE_DELETE(m_thread);
		SAFE_DELETE(m_debug);
		SAFE_DELETE(m_db);
		SAFE_DELETE(m_dserver);
		SAFE_DELETE(m_dclient);
	}
public:
	CFileHandle *m_log;    //����ĳ�ļ���
	CFileHandle *m_thread; //���߳�
	CFileHandle *m_debug;  //������һ���ļ�
	CFileHandle *m_db;
	CFileHandle *m_dserver;//�ֲ�ʽ �����
	CFileHandle *m_dclient;//�ֲ�ʽ �ͻ���
};

CFileHandleMgr __LogMgr;  //ȱ��:ռ�����޵�ջ�ڴ�!!
static char    __szFormatBuff[LOG_MAXBUFFER];

BOOL Log_Logic(CFileHandle *handle, const char* szFormat, va_list header, bool bIsLogAll)
{
	BOOL ret = FALSE;
	int lentemp = strlen("\r");
	DWORD &len = handle->m_len;
	time_t NowTime = ::time(0);

	if (NowTime >= handle->m_time + 1)
	{
		const char* temp = "=>";
		const char* timeptr = GetStringTime();
		int value = LOG_MAXBUFFER - len - lentemp * 3;
		sprintf_s(handle->m_buf + len, value > 0 ? value : 0, "%s%s\n", temp, timeptr);
		len += strlen(handle->m_buf + len);
		handle->m_time = NowTime;
	}

	//filter
	int nFormatLen = min(strlen(szFormat), LOG_MAXBUFFER - 1);
	memcpy(__szFormatBuff, szFormat, nFormatLen);
	__szFormatBuff[nFormatLen] = 0;
	//LogFilter((char*)__szFormatBuff, nFormatLen);

	int value = LOG_MAXBUFFER - len - lentemp * 3;
	//vsprintf_s(handle->m_buf + len, value > 0 ? value : 0, __szFormatBuff, header);
	//vsnprintf_s(handle->m_buf + len, value > 0 ? value : 0, _TRUNCATE, __szFormatBuff, header);
	/* ����ʹ��_vsnprintf����,������Ƿ�format����ʱ����������,��˲��õ���LogFilter.�������ԭ��!!ע:��Ԥ����_CRT_SECURE_NO_WARNINGS */ 
	_vsnprintf(handle->m_buf + len, value > 0 ? value : 0, __szFormatBuff, header);

	len = strlen(handle->m_buf);
	handle->m_buf[len] = '\n'; len += lentemp;
	handle->m_buf[len] = '\0';

	//if (NowTime >= handle->m_time + WRITETIME || len >= WRITELEN)  //����һ��ʱ�� �� ���ݵ���һ������ �ʹ�һ���ļ�  //whb
	{
		ret = handle->WriteLog(bIsLogAll);
	}

	return ret;
}

CFileHandle *GetHandleByType(char type)
{
	CFileHandle *handle = NULL;

	switch (type)
	{
	case LOG_NORMAL:
	{
		handle = __LogMgr.m_log;
	}break;
	case LOG_THREAD:
	{
		handle = __LogMgr.m_thread;
	}break;
	case LOG_DEBUG:
	{
		handle = __LogMgr.m_debug;
	}break;
	case LOG_DB:
	{
		handle = __LogMgr.m_db;
	}break;
	case LOG_DSERVER:
	{
		handle = __LogMgr.m_dserver;
	}break;
	case LOG_DCLIENT:
	{
		handle = __LogMgr.m_dclient;
	}break;
	default:
		break;
	}

	return handle;
}

//Ӧ��ע�����,����ʹ�õ��Ǳ䳤����,�����������֣�Log("%d 100%.", 10);
//�ᵼ�³������,Ӧ�ó�Log("%d 100%%.", 10);����ĳЩ���ش���ֵ���ѱ���
//�������,����mysql����ʱ���ش���"execute command denied to user 'sa'@'%' for"
//��ͬ�������,������Log�����ж����ַǷ����ͳһ�ж�,��������̫��,��������ʱ��
//mysql�н������⴦����?�Ժ���԰�LOG������һ�������ķ���������ʹ������Ҳ��
//Ӱ�������û�!!
BOOL Log(const char* szFormat, ...)
{
	va_list header;
	va_start(header, szFormat);
	BOOL ret = Log_Logic(__LogMgr.m_log, szFormat, header, false);
	va_end(header);

	return ret;
}

BOOL Log(char type, const char* szFormat, ...)
{
	CFileHandle *handle = GetHandleByType(type);
	if (!handle) return FALSE;
	BOOL ret;

	if (LOG_THREAD == type)
	{
		LOG_LOCK();

		va_list header;
		va_start(header, szFormat);
		ret = Log_Logic(handle, szFormat, header, false);
		va_end(header);

		LOG_UNLOCK();
	}
	else
	{
		va_list header;
		va_start(header, szFormat);
		ret = Log_Logic(handle, szFormat, header, false);
		va_end(header);
	}

	return ret;
}

//��������δ���������
BOOL LogAll()
{
	for (int i = LOG_NORMAL; i < LOG_MAX; i++)
	{
		CFileHandle *handle = GetHandleByType(i);
		if (!handle) continue;

		if (handle->m_len > 0)
			handle->m_time = 0;  //ȷ���˴�����������
		else
			continue;

		BOOL ret = Log_Logic(handle, "---------log all---------", (va_list)"", true);

		return ret;
	}

	return FALSE;
}


#define LOG_FILTER_STRING '*'
char LogFilterHandle(char* buffer, size_t index)
{
	char next = buffer[index];
	switch (next)
	{
	case 'd':
	case 's':
	case 'c':
	case 'f':
	case 'i':
	case 'o':
	case 'u':
	case 'x':
	case 'p':
	case 'a':
	case 'A':
	case 'C':
	case 'S':
	case 'X':
	case 'g':
	case 'G':
	case 'e':
	case 'E':
	case '%':
		break;
	default:
		buffer[index - 1] = LOG_FILTER_STRING;
		return 1;
		break;
	}

	return 0;
}

//���˵����Ϸ��ı䳤������"Log("%d,100%",1)"����ȷӦΪ"Log("%d,100%%",1)"��
//���˺���������Ϊ"Log("%d,100*",1)",���������vsprintf_s���ƽӿڴ�����.
//����ֻ��Ԥ����ʽ�������⵫�������������Log("%d%s",123);��˺�����ʱ����Ϊ��.
//��������,�������һ���ֽڵ�:%I64u��%.nf��%hs����δ����
void LogFilter(char* buffer, size_t size)
{
	if (size > 0)
	{
		int  i    = 0;
		char flag = 0;
		for (; i < size - 1; i++)
		{
			flag = 0;
			if (buffer[i] == '%')
			{
				flag = LogFilterHandle(buffer, ++i);
			}
		}

		if (i < size)
		{
			//������2���ַ���'%'
			if (1 == flag)
			{
				LogFilterHandle(buffer, i);
			}
			//���һ���ַ���'%'
			else if ('%' == buffer[i])
			{
				buffer[i] = LOG_FILTER_STRING;
			}
		}
	}
}



//%a       ��������ʮ���������ֺ�p - ���������ã�����
//%A����������������ʮ���������ֺ�p - �Ƿ����ã�����
//%c�������� һ���ַ�(char)
//% C           һ��ISO���ַ�
//%d���������з���ʮ��������(int)��%ld��%Ld������������(long), %hd����������Ρ�����
//%e����������������e - ������
//%E������������������ - ������
//%f�������� �����ȸ�����(Ĭ��float)��ʮ���Ƽ�������%.nf  ����n��ʾ��ȷ��С��λ��nλ.ʮ���Ƽ�����
//%g��������������ֵ��ͬ�Զ�ѡ��f��e��
//%G��������������ֵ��ͬ�Զ�ѡ��f��e.
//%i              �з���ʮ���������룥d��ͬ��
//%o���������޷��Ű˽�������
//%p������   ָ��
//%s�������� ��Ӧ�ַ���char*��%s == %hs == %hS ��� խ�ַ���
//%S             ��Ӧ���ַ���WCAHR*��%ws == %S ������ַ�����
//%u������   �޷���ʮ��������(unsigned int)
//% x��������ʹ��ʮ���������֣�f���޷���ʮ������������
//%X������   ʹ��ʮ���������֣�f���޷���ʮ����������
//%%������  ��ӡһ���ٷֺ�
//%I64d
//����INT64 ���� long long
//%I64u
//����UINT64 ���� unsigned long long
//%I64x
//����64λ16��������

//��%����ʾ��ʽ˵������ʼ���ţ�����ȱ�١�
//�� - ���� - ��ʾ������������ʡ�Ա�ʾ�Ҷ��������
//��0����0��ʾָ����λ��0, ��ʡ�Ա�ʾָ����λ���
//��m.n��mָ�������Ӧ�������������豸����ռ���ַ�����nָ���ȡ�����˵�������ʵ������С��λ����Ϊָ��nʱ�������ľ���Ϊn = 6λ��
//��l��h : l������ָlong�ͣ���ʵ��ָdouble�͡�h���ڽ����͵ĸ�ʽ�ַ�����Ϊshort��