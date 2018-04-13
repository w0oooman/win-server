#ifndef  __KERNELDEFINE__H__
#define  __KERNELDEFINE__H__

#define WIN32_LEAN_AND_MEAN
#include  <windows.h>
#include  "Log.h"

#ifdef  KERNEL_EXPORTS
#define KERNEL_ENGINE_CLASS __declspec(dllexport)
#else
#define KERNEL_ENGINE_CLASS __declspec(dllimport)
#endif


//��ǰsocket����
#define   SOCKET_TYPE    SOCK_STREAM
//�������ݵ���󳤶ȵ�λ��
#define   MAX_LENGTH_DATA       5
//���ͻ�ÿ�δӻ�������ȡ����󳤶�
#define   MAX_MESSAGE_LENGTH    2048
//���������
#define   MAX_SEND_LIMIT  (1024*32)

//��ͨ�ͻ�������ʱ:�������������buffer
#define   SND_SIZE        (1024*4)
//��ͨ�ͻ�������ʱ:�������������buffer
#define   RCV_SIZE        (1024*8)  //��buf���û��λ�����ʱ�������2�Ĵη�

//�ͻ������ӷ����ʱ:����˷������buffer
#define   SND_SIZE_SPECIAL  (1024*256)
//�ͻ������ӷ����ʱ:����˽������buffer
#define   RCV_SIZE_SPECIAL  (1024*256)  //��buf���û��λ�����ʱ�������2�Ĵη�

//��������Ϊ�ͻ���ʱ:BUFFER��С
#define   CLIENT_SND_SIZE   (1024*128)
#define   CLIENT_RCV_SIZE   (1024*512)

//��Ϣ������
#define   MESSAGE_CHECK_CODE     (150808)

#define   WHEEL_TIMER_LOCK  //ʱ������

//�������ʱ����(��)
#define   HEART_BEAT_TEST_TIME   (15)
//������ⳬʱ����(����������Ͽ�����)
#define   HEART_BEAT_CUT_TIMES   (3)

#define   CLIENT_RECONNECT_TIME  (5)           //�ͻ�������ʱ��(��)


//������������(һ����2����!!)
#define   NORMAL_QUEUE_LIMIT_SIZE  (1024*512) //��ͨ����
#define   BATCH_QUEUE_LIMIT_SIZE   (1024*32)  //Ⱥ������(����tai��!)
#define   DB_QUEUE_LIMIT_SIZE      (1024*16)  //���ݿ����
#define   TIMER_QUEUE_LIMIT_SIZE   256        //��ʱ������

#define   CLIENT_NORMAL_QUEUE_SIZE 128        //�ͻ��˶��д�С



//#if (SOCKET_TYPE==SOCK_STREAM)
//    #define SOCKET_CONNEECT_OK
//#endif

#ifdef   WHEEL_TIMER_LOCK
typedef struct tagWheelTimer
{
	int   timerID;
	void *func;
	void *data;
	int   type;
} tagWheelTimer;
#endif

typedef void(*TimerCallBackFunc)(void *);


////////////////////////////////////
////////������Ϣ////////////////////
////////////////////////////////////

#define  QMD_NORMAL_DATA        1         //��ȡ����
#define  QMD_DB_DATA            2         //���ݿ����
#define  QMD_TIMER_DATA         3         //��ʱ������
#define  QMD_DELETE_TIMERDATA   4         //�����ʱ������
#define  QMD_CLOSE_SOCKET       5         //�ر�����
#define  QMD_BATCH_DATA         6         //Ⱥ������


#endif