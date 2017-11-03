#ifndef __LOG_H__
#define __LOG_H__


#define WIN32_LEAN_AND_MEAN		// �� Windows ͷ���ų�����ʹ�õ�����
//#define _WIN32_WINNT 0x400

// Windows ͷ�ļ���
#include <windows.h>
#include <windowsx.h>

// C ����ʱͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: �ڴ˴����ó���Ҫ��ĸ���ͷ
#include <commctrl.h>
#include <mmsystem.h>
#include <shlwapi.h>

#include <crtdbg.h>
#include <Shellapi.h>

#include <iostream>
#include <fstream>

#define LOG_MAXBUFFER      2048  //LOG��buf��󳤶�
#define LOG_MAXBUFFEREX    (LOG_MAXBUFFER + 10)

enum LOG_TYPE
{
	LOG_NORMAL = 0,
	LOG_THREAD,
	LOG_DEBUG,
	LOG_DB,
	LOG_DSERVER,//�ֲ�ʽ�����
	LOG_DCLIENT,//�ֲ�ʽ�ͻ���

	LOG_MAX,
};

/*
** �������ļ�����û�п��Ƕ��̻߳���,����д��ĳ���ļ�
** ʱӦ���ڵ��̻߳�����!!!����Ӧʹ��LOG_THREAD����
*/
extern BOOL Log(const char* szFormat, ...);             //��LOG_NORMAL��ʽ����
extern BOOL Log(char type, const char* szFormat, ...);  //ָ����������
extern BOOL LogAll();                                   //����������������


/* ���˵����Ϸ��ı䳤������"Log("%d,100%",1)"����ȷӦΪ"Log("%d,100%%",1)"��
** ���˺���������Ϊ"Log("%d,100*",1)",���������vsprintf_s���ƽӿڴ�����.
** ����ֻ��Ԥ����ʽ�������⵫�������������Log("%d%s",123);��˺�����ʱ����Ϊ��.
*/
extern void LogFilter(char* buffer, size_t size);      


#endif