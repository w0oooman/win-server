#ifndef __DB_MANAMER__H__
#define __DB_MANAMER__H__
#include <vector>
#include "MysqlDBProcess.h"
#include "UserData.h"
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif
#include "..\3rd\redis-3.0\deps\hiredis\hiredis.h"
#ifdef __cplusplus
}
#endif

extern enum e_redis_name;

#define DB_COMMAND_LEN       512
#define DB_LOADREDIS_MAX     15000      //���ص�redis������û���

class CDBManager :public mysql::CQuery
{
private:
	redisContext *m_pRedisContext;
	char   m_command[DB_COMMAND_LEN];
	char   m_szAccountName[USER_NAME_MAX_LEN + 1];  //����ʺ�
	char   m_szRoleName[USER_NAME_MAX_LEN + 1];     //�����ɫ��
	char **m_key;

	CUserData      *m_pUserData;
	vector<string>  m_vecData;
public:
	CDBManager();
	virtual ~CDBManager();

private:
	void InitRedisName();
	bool BindUserInfo(QueryResult *qr, CUserData *pUserData, bool ismult = false);
	bool IsUserInRedis(DWORD dwUserID);
	bool VExecDB(QueryResult *qr, const char *format, va_list header, Arguments args = Arguments(0, 0));
	bool ExecDB(QueryResult *qr, const char *format, ...);

	/**********************************************************
	DB2Redis��Redis2Memory����CPlayer�ĳɶ���������࣬�ﵽ����Ŀ��
	************************************************************/
	//�������ݵ�redis
	void DB2Redis(CUserData *pUserData);
	//����redis���ݵ��ڴ�
	void Redis2Memory(CUserData *pUserData, DWORD dwUserID);
	void Redis2Memory(CUserData *pUserData, char *rolename);

	//��ȡ�û��ַ�����
	void GetUserStrData(redisReply* rp, char* pDestBuf, DWORD dwDestBufLen);

	//����redis����
private:
	//reidsд����(�󲿷ֲ�����hset��hdel��del��sadd�ȶ����Ե��ô˺���)
	bool redis_write(const char *format, va_list header);
	bool redis_write(const char *format, ...);

	bool redis_hset(const char *format, ...);
	bool redis_sadd(const char *format, ...);
	bool redis_del(const char *format, ...);
	bool redis_sismember(const char *format, ...);
	bool redis_hmset(const char *format, ...);

	redisReply* redis_spop(const char *format, ...);
	redisReply* redis_hget(const char *format, ...);
	redisReply* redis_sscan(const char *format, ...);
	redisReply* redis_hmget(const char *format, ...);

private:
	//update insert delete...
	bool UpdateDBData(const char *sql, ...);
	bool UpdateDBData(Arguments args, const char *sql, ...);

	//�������ݵ�redis
	CUserData *LoadUserData(DWORD dwUserID);
	CUserData *LoadUserData(char *rolename);
	CUserData *LoadUserDataByAccount(char *account);
	//�Ƴ�����
	void RemoveUserFromRedis(DWORD dwUserID);
	//ж������
	//nojudge:�ж��Ƿ���ڸ��û���false:��Ҫ�ж�,true:���жϣ�
	void UnLoadUserData(DWORD dwUserID, bool nojudge = false);

	//��ȡredis����������
	void GetRedisSetData(vector<string>* pVecData, char* pSetKey)
	{
		redisReply *rp = redis_sscan("sscan %s 0", pSetKey);

		while (rp)
		{
			int left = 0;
			if (REDIS_REPLY_ARRAY == rp->type && 2 == rp->elements)
			{
				redisReply *rp1 = rp->element[0]; //rp1->str is the itertor
				redisReply *rp2 = rp->element[1]; //rp2->element is the data
				if (REDIS_REPLY_STRING == rp1->type) left = atoi(rp1->str);

				int elements = rp2->elements;
				if (elements > 0)
				{
					for (int i = 0; i < elements; i++)
					{
						redisReply *rp_ele = rp2->element[i];

						switch (rp_ele->type)
						{
						case REDIS_REPLY_INTEGER:
						{
							char buf[20];
							memset(buf, 0, sizeof(buf));
							_i64toa(rp_ele->integer, buf, 10);
							pVecData->push_back(buf);
						}
							break;
						case REDIS_REPLY_STRING:
							pVecData->push_back(rp_ele->str);
							break;
						default:
							break;
						}
					}
				}
			}

			freeReplyObject(rp);

			//next iterator
			if (left > 0)
				rp = redis_sscan("sscan %s %d", pSetKey, left);
			else
				break;
		}
	}

public:
	bool InitRedis(char *ip, int port);

	//��������
	void LoadUserData();

	//�ط�����
	//quit:�Ƿ��ǹط�
	void SaveUserData(bool quit = false);

	//��������
	void SaveUserData(DWORD dwUserID, bool nojudge = false);

	//��ȡ��ɫ��
	char *GetUserName(DWORD dwUserID);
	//��ȡ�˺�
	char *GetUserAccount(DWORD dwUserID);
	//��ȡ�û�ID
	DWORD GetUserID(char *rolename);

	//��ȡ�û�����,redisû��������ݿ���
	CUserData *GetUserData(DWORD dwUserID);
	CUserData *GetUserData(char *rolename);

	bool GetRoleListByAccount(char* buffer, DWORD dwSize, char *account);
};

#define UPDATE_USER_DATA          "update UserInfo set money = %d, diamond = %d, point = %d, LastLoginTime = now() where RoleID = %d"
#define UPDATE_USER_DATA_BIND     "update UserInfo set money = ?,  diamond = ?,  point = ?   where RoleID = %d"

#endif