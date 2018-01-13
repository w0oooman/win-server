#ifndef  __INI_PARSER_H__
#define  __INI_PARSER_H__
#include <fstream>
#define  INI_STRING_LEN  128

class CIniParser
{
private:
	char          *m_szFileName;
	std::fstream   m_fstream;
	char          *m_szFormatStr;
	//char           m_szFormatStr[INI_STRING_LEN];
public:
	CIniParser();
	virtual ~CIniParser();
private:
	char* __cdecl FormatStr(const char* format, ...);
	bool  Open();
	int   GetLine(char* buff, int bytes);      //��ȡһ��,���ض�ȡ�ֽ���,bytes:����ȡ�ֽ�
	bool  Judge(const char* line, int bytes, char character);
	bool  IsNotes(const char* line, int bytes);//�Ƿ���ע��#
	bool  IsSection(const char* line, int bytes);
	bool  IsSection(const char* line, const char* section, int bytes);
	bool  IsKey(const char* line, int bytes);                  //�ж�ĳ���Ƿ���key
	char* GetKey(char* line, const char* key, int bytes);//�ҵ�section��,�ж�ĳ���Ƿ���Ҫ�ҵ�key
	int   GetOneString(const char* line, int bytes, char* outbuf, int outlen); // ��ȡһ���ַ���
	char* GetData(const char* section, const char* key, char* buffer, int bufsize);
public:
	char* GetLastError();
	bool  Open(const char* szFileName);
	void  Close();
	char* GetIniString(const char* section, const char* key, char* buffer, int bufsize, char* default = "");
	int   GetIniInt(const char* section, const char* key, int default = 0);
};

#endif