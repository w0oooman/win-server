
#pragma once

#pragma once

#pragma region Input Buffer SAL 1 compatibility macros

#pragma endregion Input Buffer SAL 1 compatibility macros

#pragma once

#pragma pack(push,8)

#pragma once

#pragma pack(push,8)

typedef __w64 unsigned int   uintptr_t;

typedef char *  va_list;

#pragma pack(pop)

typedef __w64 unsigned int   size_t;

typedef size_t rsize_t;

typedef __w64 int            intptr_t;

typedef __w64 int            ptrdiff_t;

typedef unsigned short wchar_t;

typedef unsigned short wint_t;
typedef unsigned short wctype_t;

typedef int errno_t;

typedef __w64 long __time32_t;

typedef __int64 __time64_t;

typedef __time64_t time_t;

__declspec(dllimport) void __cdecl _invalid_parameter_noinfo(void);
__declspec(dllimport) __declspec(noreturn) void __cdecl _invalid_parameter_noinfo_noreturn(void);

__declspec(dllimport) __declspec(noreturn)
void __cdecl _invoke_watson(const wchar_t *, const wchar_t *, const wchar_t *, unsigned int, uintptr_t);

struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct * pthreadlocinfo;
typedef struct threadmbcinfostruct * pthreadmbcinfo;
struct __lc_time_data;

typedef struct localeinfo_struct
{
	pthreadlocinfo locinfo;
	pthreadmbcinfo mbcinfo;
} _locale_tstruct, *_locale_t;

typedef struct localerefcount {
	char *locale;
	wchar_t *wlocale;
	int *refcount;
	int *wrefcount;
} locrefcount;

typedef struct threadlocaleinfostruct {
	int refcount;
	unsigned int lc_codepage;
	unsigned int lc_collate_cp;
	unsigned int lc_time_cp;
	locrefcount lc_category[6];
	int lc_clike;
	int mb_cur_max;
	int * lconv_intl_refcount;
	int * lconv_num_refcount;
	int * lconv_mon_refcount;
	struct lconv * lconv;
	int * ctype1_refcount;
	unsigned short * ctype1;
	const unsigned short * pctype;
	const unsigned char * pclmap;
	const unsigned char * pcumap;
	struct __lc_time_data * lc_time_curr;
	wchar_t * locale_name[6];
} threadlocinfo;

#pragma pack(pop)

void __declspec(dllimport) __cdecl _vacopy(va_list *, va_list);

#pragma once

__declspec(dllimport) extern int * __cdecl _errno(void);

errno_t __cdecl _set_errno(int _Value);
errno_t __cdecl _get_errno(int * _Value);

__declspec(dllimport) extern unsigned long  __cdecl __threadid(void);

__declspec(dllimport) extern uintptr_t __cdecl __threadhandle(void);

#pragma once

typedef struct lua_State lua_State;

typedef double lua_Number;

typedef long long lua_Integer;

typedef unsigned long long lua_Unsigned;

typedef ptrdiff_t lua_KContext;

typedef int(*lua_CFunction) (lua_State *L);

typedef int(*lua_KFunction) (lua_State *L, int status, lua_KContext ctx);

typedef const char * (*lua_Reader) (lua_State *L, void *ud, size_t *sz);

typedef int(*lua_Writer) (lua_State *L, const void *p, size_t sz, void *ud);

typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);

extern const char lua_ident[];

extern lua_State *(lua_newstate)(lua_Alloc f, void *ud);
extern void       (lua_close)(lua_State *L);
extern lua_State *(lua_newthread)(lua_State *L);

extern lua_CFunction(lua_atpanic) (lua_State *L, lua_CFunction panicf);

extern const lua_Number *(lua_version)(lua_State *L);

extern int   (lua_absindex)(lua_State *L, int idx);
extern int   (lua_gettop)(lua_State *L);
extern void  (lua_settop)(lua_State *L, int idx);
extern void  (lua_pushvalue)(lua_State *L, int idx);
extern void  (lua_rotate)(lua_State *L, int idx, int n);
extern void  (lua_copy)(lua_State *L, int fromidx, int toidx);
extern int   (lua_checkstack)(lua_State *L, int n);

extern void  (lua_xmove)(lua_State *from, lua_State *to, int n);

extern int             (lua_isnumber)(lua_State *L, int idx);
extern int             (lua_isstring)(lua_State *L, int idx);
extern int             (lua_iscfunction)(lua_State *L, int idx);
extern int             (lua_isinteger)(lua_State *L, int idx);
extern int             (lua_isuserdata)(lua_State *L, int idx);
extern int             (lua_type)(lua_State *L, int idx);
extern const char     *(lua_typename)(lua_State *L, int tp);

extern lua_Number(lua_tonumberx) (lua_State *L, int idx, int *isnum);
extern lua_Integer(lua_tointegerx) (lua_State *L, int idx, int *isnum);
extern int             (lua_toboolean)(lua_State *L, int idx);
extern const char     *(lua_tolstring)(lua_State *L, int idx, size_t *len);
extern size_t(lua_rawlen) (lua_State *L, int idx);
extern lua_CFunction(lua_tocfunction) (lua_State *L, int idx);
extern void	       *(lua_touserdata)(lua_State *L, int idx);
extern lua_State      *(lua_tothread)(lua_State *L, int idx);
extern const void     *(lua_topointer)(lua_State *L, int idx);

extern void  (lua_arith)(lua_State *L, int op);

extern int   (lua_rawequal)(lua_State *L, int idx1, int idx2);
extern int   (lua_compare)(lua_State *L, int idx1, int idx2, int op);

extern void        (lua_pushnil)(lua_State *L);
extern void        (lua_pushnumber)(lua_State *L, lua_Number n);
extern void        (lua_pushinteger)(lua_State *L, lua_Integer n);
extern const char *(lua_pushlstring)(lua_State *L, const char *s, size_t len);
extern const char *(lua_pushstring)(lua_State *L, const char *s);
extern const char *(lua_pushvfstring)(lua_State *L, const char *fmt,
	va_list argp);
extern const char *(lua_pushfstring)(lua_State *L, const char *fmt, ...);
extern void  (lua_pushcclosure)(lua_State *L, lua_CFunction fn, int n);
extern void  (lua_pushboolean)(lua_State *L, int b);
extern void  (lua_pushlightuserdata)(lua_State *L, void *p);
extern int   (lua_pushthread)(lua_State *L);

extern int (lua_getglobal)(lua_State *L, const char *name);
extern int (lua_gettable)(lua_State *L, int idx);
extern int (lua_getfield)(lua_State *L, int idx, const char *k);
extern int (lua_geti)(lua_State *L, int idx, lua_Integer n);
extern int (lua_rawget)(lua_State *L, int idx);
extern int (lua_rawgeti)(lua_State *L, int idx, lua_Integer n);
extern int (lua_rawgetp)(lua_State *L, int idx, const void *p);

extern void  (lua_createtable)(lua_State *L, int narr, int nrec);
extern void *(lua_newuserdata)(lua_State *L, size_t sz);
extern int   (lua_getmetatable)(lua_State *L, int objindex);
extern int  (lua_getuservalue)(lua_State *L, int idx);

extern void  (lua_setglobal)(lua_State *L, const char *name);
extern void  (lua_settable)(lua_State *L, int idx);
extern void  (lua_setfield)(lua_State *L, int idx, const char *k);
extern void  (lua_seti)(lua_State *L, int idx, lua_Integer n);
extern void  (lua_rawset)(lua_State *L, int idx);
extern void  (lua_rawseti)(lua_State *L, int idx, lua_Integer n);
extern void  (lua_rawsetp)(lua_State *L, int idx, const void *p);
extern int   (lua_setmetatable)(lua_State *L, int objindex);
extern void  (lua_setuservalue)(lua_State *L, int idx);

extern void  (lua_callk)(lua_State *L, int nargs, int nresults,
	lua_KContext ctx, lua_KFunction k);

extern int   (lua_pcallk)(lua_State *L, int nargs, int nresults, int errfunc,
	lua_KContext ctx, lua_KFunction k);

extern int   (lua_load)(lua_State *L, lua_Reader reader, void *dt,
	const char *chunkname, const char *mode);

extern int (lua_dump)(lua_State *L, lua_Writer writer, void *data, int strip);

extern int  (lua_yieldk)(lua_State *L, int nresults, lua_KContext ctx,
	lua_KFunction k);
extern int  (lua_resume)(lua_State *L, lua_State *from, int narg);
extern int  (lua_status)(lua_State *L);
extern int (lua_isyieldable)(lua_State *L);

extern int (lua_gc)(lua_State *L, int what, int data);

extern int   (lua_error)(lua_State *L);

extern int   (lua_next)(lua_State *L, int idx);

extern void  (lua_concat)(lua_State *L, int n);
extern void  (lua_len)(lua_State *L, int idx);

extern size_t(lua_stringtonumber) (lua_State *L, const char *s);

extern lua_Alloc(lua_getallocf) (lua_State *L, void **ud);
extern void      (lua_setallocf)(lua_State *L, lua_Alloc f, void *ud);

typedef struct lua_Debug lua_Debug;

typedef void(*lua_Hook) (lua_State *L, lua_Debug *ar);

extern int (lua_getstack)(lua_State *L, int level, lua_Debug *ar);
extern int (lua_getinfo)(lua_State *L, const char *what, lua_Debug *ar);
extern const char *(lua_getlocal)(lua_State *L, const lua_Debug *ar, int n);
extern const char *(lua_setlocal)(lua_State *L, const lua_Debug *ar, int n);
extern const char *(lua_getupvalue)(lua_State *L, int funcindex, int n);
extern const char *(lua_setupvalue)(lua_State *L, int funcindex, int n);

extern void *(lua_upvalueid)(lua_State *L, int fidx, int n);
extern void  (lua_upvaluejoin)(lua_State *L, int fidx1, int n1,
	int fidx2, int n2);

extern void (lua_sethook)(lua_State *L, lua_Hook func, int mask, int count);
extern lua_Hook(lua_gethook) (lua_State *L);
extern int (lua_gethookmask)(lua_State *L);
extern int (lua_gethookcount)(lua_State *L);

struct lua_Debug {
	int event;
	const char *name;
	const char *namewhat;
	const char *what;
	const char *source;
	int currentline;
	int linedefined;
	int lastlinedefined;
	unsigned char nups;
	unsigned char nparams;
	char isvararg;
	char istailcall;
	char short_src[60];

	struct CallInfo *i_ci;
};

#pragma once

#pragma pack(push,8)

struct _iobuf {
	char *_ptr;
	int   _cnt;
	char *_base;
	int   _flag;
	int   _file;
	int   _charbuf;
	int   _bufsiz;
	char *_tmpfname;
};
typedef struct _iobuf FILE;

__declspec(dllimport) FILE * __cdecl __iob_func(void);

typedef __int64 fpos_t;

__declspec(dllimport) int __cdecl _filbuf(FILE * _File);
__declspec(dllimport) int __cdecl _flsbuf(int _Ch, FILE * _File);

__declspec(dllimport) FILE * __cdecl _fsopen(const char * _Filename, const char * _Mode, int _ShFlag);

__declspec(dllimport) void __cdecl clearerr(FILE * _File);

__declspec(dllimport) errno_t __cdecl clearerr_s(FILE * _File);

__declspec(dllimport) int __cdecl fclose(FILE * _File);
__declspec(dllimport) int __cdecl _fcloseall(void);

__declspec(dllimport) FILE * __cdecl _fdopen(int _FileHandle, const char * _Mode);

__declspec(dllimport) int __cdecl feof(FILE * _File);
__declspec(dllimport) int __cdecl ferror(FILE * _File);
__declspec(dllimport) int __cdecl fflush(FILE * _File);
__declspec(dllimport) int __cdecl fgetc(FILE * _File);
__declspec(dllimport) int __cdecl _fgetchar(void);
__declspec(dllimport) int __cdecl fgetpos(FILE * _File, fpos_t * _Pos);
__declspec(dllimport) char * __cdecl fgets(char * _Buf, int _MaxCount, FILE * _File);

__declspec(dllimport) int __cdecl _fileno(FILE * _File);

__declspec(dllimport) char * __cdecl _tempnam(const char * _DirName, const char * _FilePrefix);

__declspec(dllimport) int __cdecl _flushall(void);
__declspec(dllimport) FILE * __cdecl fopen(const char * _Filename, const char * _Mode);

__declspec(dllimport) errno_t __cdecl fopen_s(FILE ** _File, const char * _Filename, const char * _Mode);

__declspec(dllimport) int __cdecl fprintf(FILE * _File, const char * _Format, ...);

__declspec(dllimport) int __cdecl fprintf_s(FILE * _File, const char * _Format, ...);

__declspec(dllimport) int __cdecl fputc(int _Ch, FILE * _File);
__declspec(dllimport) int __cdecl _fputchar(int _Ch);
__declspec(dllimport) int __cdecl fputs(const char * _Str, FILE * _File);
__declspec(dllimport) size_t __cdecl fread(void * _DstBuf, size_t _ElementSize, size_t _Count, FILE * _File);

__declspec(dllimport) size_t __cdecl fread_s(void * _DstBuf, size_t _DstSize, size_t _ElementSize, size_t _Count, FILE * _File);

__declspec(dllimport) FILE * __cdecl freopen(const char * _Filename, const char * _Mode, FILE * _File);

__declspec(dllimport) errno_t __cdecl freopen_s(FILE ** _File, const char * _Filename, const char * _Mode, FILE * _OldFile);

__declspec(dllimport) int __cdecl fscanf(FILE * _File, const char * _Format, ...);
__declspec(dllimport) int __cdecl _fscanf_l(FILE * _File, const char * _Format, _locale_t _Locale, ...);
#pragma warning(push)
#pragma warning(disable:6530)

__declspec(dllimport) int __cdecl fscanf_s(FILE * _File, const char * _Format, ...);

__declspec(dllimport) int __cdecl _fscanf_s_l(FILE * _File, const char * _Format, _locale_t _Locale, ...);
#pragma warning(pop)
__declspec(dllimport) int __cdecl fsetpos(FILE * _File, const fpos_t * _Pos);
__declspec(dllimport) int __cdecl fseek(FILE * _File, long _Offset, int _Origin);
__declspec(dllimport) long __cdecl ftell(FILE * _File);

__declspec(dllimport) int __cdecl _fseeki64(FILE * _File, __int64 _Offset, int _Origin);
__declspec(dllimport) __int64 __cdecl _ftelli64(FILE * _File);

__declspec(dllimport) size_t __cdecl fwrite(const void * _Str, size_t _Size, size_t _Count, FILE * _File);
__declspec(dllimport) int __cdecl getc(FILE * _File);
__declspec(dllimport) int __cdecl getchar(void);
__declspec(dllimport) int __cdecl _getmaxstdio(void);

__declspec(dllimport) char * __cdecl gets_s(char * _Buf, rsize_t _Size);

__declspec(dllimport) char * __cdecl gets(char *_Buffer);
int __cdecl _getw(FILE * _File);

__declspec(dllimport) void __cdecl perror(const char * _ErrMsg);

__declspec(dllimport) int __cdecl _pclose(FILE * _File);
__declspec(dllimport) FILE * __cdecl _popen(const char * _Command, const char * _Mode);

__declspec(dllimport) int __cdecl printf(const char * _Format, ...);

__declspec(dllimport) int __cdecl printf_s(const char * _Format, ...);

__declspec(dllimport) int __cdecl putc(int _Ch, FILE * _File);
__declspec(dllimport) int __cdecl putchar(int _Ch);
__declspec(dllimport) int __cdecl puts(const char * _Str);
__declspec(dllimport) int __cdecl _putw(int _Word, FILE * _File);

__declspec(dllimport) int __cdecl remove(const char * _Filename);
__declspec(dllimport) int __cdecl rename(const char * _OldFilename, const char * _NewFilename);
__declspec(dllimport) int __cdecl _unlink(const char * _Filename);

__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_unlink" ". See online help for details.")) __declspec(dllimport) int __cdecl unlink(const char * _Filename);

__declspec(dllimport) void __cdecl rewind(FILE * _File);
__declspec(dllimport) int __cdecl _rmtmp(void);
__declspec(dllimport) int __cdecl scanf(const char * _Format, ...);
__declspec(dllimport) int __cdecl _scanf_l(const char * _Format, _locale_t _Locale, ...);
#pragma warning(push)
#pragma warning(disable:6530)

__declspec(dllimport) int __cdecl scanf_s(const char * _Format, ...);

__declspec(dllimport) int __cdecl _scanf_s_l(const char * _Format, _locale_t _Locale, ...);
#pragma warning(pop)
__declspec(dllimport) void __cdecl setbuf(FILE * _File, char * _Buffer);
__declspec(dllimport) int __cdecl _setmaxstdio(int _Max);
__declspec(dllimport) unsigned int __cdecl _set_output_format(unsigned int _Format);
__declspec(dllimport) unsigned int __cdecl _get_output_format(void);
__declspec(dllimport) int __cdecl setvbuf(FILE * _File, char * _Buf, int _Mode, size_t _Size);
__declspec(dllimport) int __cdecl _snprintf_s(char * _DstBuf, size_t _SizeInBytes, size_t _MaxCount, const char * _Format, ...);

__declspec(dllimport) int __cdecl sprintf_s(char * _DstBuf, size_t _SizeInBytes, const char * _Format, ...);

__declspec(dllimport) int __cdecl _scprintf(const char * _Format, ...);
__declspec(dllimport) int __cdecl sscanf(const char * _Src, const char * _Format, ...);
__declspec(dllimport) int __cdecl _sscanf_l(const char * _Src, const char * _Format, _locale_t _Locale, ...);
#pragma warning(push)
#pragma warning(disable:6530)

__declspec(dllimport) int __cdecl sscanf_s(const char * _Src, const char * _Format, ...);

__declspec(dllimport) int __cdecl _sscanf_s_l(const char * _Src, const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _snscanf(const char * _Src, size_t _MaxCount, const char * _Format, ...);
__declspec(dllimport) int __cdecl _snscanf_l(const char * _Src, size_t _MaxCount, const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _snscanf_s(const char * _Src, size_t _MaxCount, const char * _Format, ...);
__declspec(dllimport) int __cdecl _snscanf_s_l(const char * _Src, size_t _MaxCount, const char * _Format, _locale_t _Locale, ...);
#pragma warning(pop)
__declspec(dllimport) FILE * __cdecl tmpfile(void);

__declspec(dllimport) errno_t __cdecl tmpfile_s(FILE ** _File);
__declspec(dllimport) errno_t __cdecl tmpnam_s(char * _Buf, rsize_t _Size);

__declspec(dllimport) char * __cdecl tmpnam(char *_Buffer);
__declspec(dllimport) int __cdecl ungetc(int _Ch, FILE * _File);
__declspec(dllimport) int __cdecl vfprintf(FILE * _File, const char * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl vfscanf(FILE * _File, const char * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl vfprintf_s(FILE * _File, const char * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl vfscanf_s(FILE * _File, const char * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl vprintf(const char * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl vscanf(const char * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl vprintf_s(const char * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl vscanf_s(const char * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl vsnprintf(char * _DstBuf, size_t _MaxCount, const char * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl vsnprintf_s(char * _DstBuf, size_t _DstSize, size_t _MaxCount, const char * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl _vsnprintf_s(char * _DstBuf, size_t _SizeInBytes, size_t _MaxCount, const char * _Format, va_list _ArgList);

#pragma warning(push)
#pragma warning(disable:4793)
__declspec(dllimport) int __cdecl _snprintf(char *_Dest, size_t _Count, const char * _Format, ...);
__declspec(dllimport) int __cdecl _vsnprintf(char *_Dest, size_t _Count, const char * _Format, va_list _Args);
#pragma warning(pop)

__declspec(dllimport) int __cdecl vsprintf_s(char * _DstBuf, size_t _SizeInBytes, const char * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl vsscanf_s(const char * _Src, const char * _Format, va_list _ArgList);

#pragma warning(push)
#pragma warning(disable:4793)
__declspec(dllimport) int __cdecl sprintf(char *_Dest, const char * _Format, ...);
__declspec(dllimport) int __cdecl vsprintf(char *_Dest, const char * _Format, va_list _Args);
__declspec(dllimport) int __cdecl vsscanf(const char * _srcBuf, const char * _Format, va_list _ArgList);
#pragma warning(pop)
__declspec(dllimport) int __cdecl _vscprintf(const char * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl _snprintf_c(char * _DstBuf, size_t _MaxCount, const char * _Format, ...);
__declspec(dllimport) int __cdecl _vsnprintf_c(char *_DstBuf, size_t _MaxCount, const char * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl _fprintf_p(FILE * _File, const char * _Format, ...);
__declspec(dllimport) int __cdecl _printf_p(const char * _Format, ...);
__declspec(dllimport) int __cdecl _sprintf_p(char * _Dst, size_t _MaxCount, const char * _Format, ...);
__declspec(dllimport) int __cdecl _vfprintf_p(FILE * _File, const char * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl _vprintf_p(const char * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl _vsprintf_p(char * _Dst, size_t _MaxCount, const char * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl _scprintf_p(const char * _Format, ...);
__declspec(dllimport) int __cdecl _vscprintf_p(const char * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl _set_printf_count_output(int _Value);
__declspec(dllimport) int __cdecl _get_printf_count_output(void);

__declspec(dllimport) int __cdecl _printf_l(const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _printf_p_l(const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _printf_s_l(const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _vprintf_l(const char * _Format, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl _vprintf_p_l(const char * _Format, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl _vprintf_s_l(const char * _Format, _locale_t _Locale, va_list _ArgList);

__declspec(dllimport) int __cdecl _fprintf_l(FILE * _File, const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _fprintf_p_l(FILE * _File, const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _fprintf_s_l(FILE * _File, const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _vfprintf_l(FILE * _File, const char * _Format, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl _vfprintf_p_l(FILE * _File, const char * _Format, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl _vfprintf_s_l(FILE * _File, const char * _Format, _locale_t _Locale, va_list _ArgList);

__declspec(dllimport) int __cdecl _sprintf_l(char * _DstBuf, const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _sprintf_p_l(char * _DstBuf, size_t _MaxCount, const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _sprintf_s_l(char * _DstBuf, size_t _DstSize, const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _vsprintf_l(char * _DstBuf, const char * _Format, _locale_t, va_list _ArgList);
__declspec(dllimport) int __cdecl _vsprintf_p_l(char * _DstBuf, size_t _MaxCount, const char* _Format, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl _vsprintf_s_l(char * _DstBuf, size_t _DstSize, const char * _Format, _locale_t _Locale, va_list _ArgList);

__declspec(dllimport) int __cdecl _scprintf_l(const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _scprintf_p_l(const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _vscprintf_l(const char * _Format, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl _vscprintf_p_l(const char * _Format, _locale_t _Locale, va_list _ArgList);

__declspec(dllimport) int __cdecl _snprintf_l(char * _DstBuf, size_t _MaxCount, const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _snprintf_c_l(char * _DstBuf, size_t _MaxCount, const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _snprintf_s_l(char * _DstBuf, size_t _DstSize, size_t _MaxCount, const char * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _vsnprintf_l(char * _DstBuf, size_t _MaxCount, const char * _Format, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl _vsnprintf_c_l(char * _DstBuf, size_t _MaxCount, const char *, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl _vsnprintf_s_l(char * _DstBuf, size_t _DstSize, size_t _MaxCount, const char* _Format, _locale_t _Locale, va_list _ArgList);

__declspec(dllimport) FILE * __cdecl _wfsopen(const wchar_t * _Filename, const wchar_t * _Mode, int _ShFlag);

__declspec(dllimport) wint_t __cdecl fgetwc(FILE * _File);
__declspec(dllimport) wint_t __cdecl _fgetwchar(void);
__declspec(dllimport) wint_t __cdecl fputwc(wchar_t _Ch, FILE * _File);
__declspec(dllimport) wint_t __cdecl _fputwchar(wchar_t _Ch);
__declspec(dllimport) wint_t __cdecl getwc(FILE * _File);
__declspec(dllimport) wint_t __cdecl getwchar(void);
__declspec(dllimport) wint_t __cdecl putwc(wchar_t _Ch, FILE * _File);
__declspec(dllimport) wint_t __cdecl putwchar(wchar_t _Ch);
__declspec(dllimport) wint_t __cdecl ungetwc(wint_t _Ch, FILE * _File);

__declspec(dllimport) wchar_t * __cdecl fgetws(wchar_t * _Dst, int _SizeInWords, FILE * _File);
__declspec(dllimport) int __cdecl fputws(const wchar_t * _Str, FILE * _File);
__declspec(dllimport) wchar_t * __cdecl _getws_s(wchar_t * _Str, size_t _SizeInWords);

__declspec(dllimport) wchar_t * __cdecl _getws(wchar_t *_String);
__declspec(dllimport) int __cdecl _putws(const wchar_t * _Str);

__declspec(dllimport) int __cdecl fwprintf(FILE * _File, const wchar_t * _Format, ...);

__declspec(dllimport) int __cdecl fwprintf_s(FILE * _File, const wchar_t * _Format, ...);

__declspec(dllimport) int __cdecl wprintf(const wchar_t * _Format, ...);

__declspec(dllimport) int __cdecl wprintf_s(const wchar_t * _Format, ...);

__declspec(dllimport) int __cdecl _scwprintf(const wchar_t * _Format, ...);
__declspec(dllimport) int __cdecl vfwprintf(FILE * _File, const wchar_t * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl vfwscanf(FILE * _File, const wchar_t * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl vfwprintf_s(FILE * _File, const wchar_t * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl vfwscanf_s(FILE * _File, const wchar_t * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl vwprintf(const wchar_t * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl vwscanf(const wchar_t * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl vwprintf_s(const wchar_t * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl vwscanf_s(const wchar_t * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl swprintf_s(wchar_t * _Dst, size_t _SizeInWords, const wchar_t * _Format, ...);

__declspec(dllimport) int __cdecl vswprintf_s(wchar_t * _Dst, size_t _SizeInWords, const wchar_t * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl vswscanf_s(const wchar_t * _Src, const wchar_t * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl vswscanf(const wchar_t * _srcBuf, const wchar_t * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl _swprintf_c(wchar_t * _DstBuf, size_t _SizeInWords, const wchar_t * _Format, ...);
__declspec(dllimport) int __cdecl _vswprintf_c(wchar_t * _DstBuf, size_t _SizeInWords, const wchar_t * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl _snwprintf_s(wchar_t * _DstBuf, size_t _SizeInWords, size_t _MaxCount, const wchar_t * _Format, ...);

__declspec(dllimport) int __cdecl _vsnwprintf_s(wchar_t * _DstBuf, size_t _SizeInWords, size_t _MaxCount, const wchar_t * _Format, va_list _ArgList);

#pragma warning(push)
#pragma warning(disable:4793)
__declspec(dllimport) int __cdecl _snwprintf(wchar_t *_Dest, size_t _Count, const wchar_t * _Format, ...);
__declspec(dllimport) int __cdecl _vsnwprintf(wchar_t *_Dest, size_t _Count, const wchar_t * _Format, va_list _Args);
#pragma warning(pop)

__declspec(dllimport) int __cdecl _fwprintf_p(FILE * _File, const wchar_t * _Format, ...);
__declspec(dllimport) int __cdecl _wprintf_p(const wchar_t * _Format, ...);
__declspec(dllimport) int __cdecl _vfwprintf_p(FILE * _File, const wchar_t * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl _vwprintf_p(const wchar_t * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl _swprintf_p(wchar_t * _DstBuf, size_t _MaxCount, const wchar_t * _Format, ...);
__declspec(dllimport) int __cdecl _vswprintf_p(wchar_t * _DstBuf, size_t _MaxCount, const wchar_t * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl _scwprintf_p(const wchar_t * _Format, ...);
__declspec(dllimport) int __cdecl _vscwprintf_p(const wchar_t * _Format, va_list _ArgList);

__declspec(dllimport) int __cdecl _wprintf_l(const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _wprintf_p_l(const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _wprintf_s_l(const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _vwprintf_l(const wchar_t * _Format, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl _vwprintf_p_l(const wchar_t * _Format, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl _vwprintf_s_l(const wchar_t * _Format, _locale_t _Locale, va_list _ArgList);

__declspec(dllimport) int __cdecl _fwprintf_l(FILE * _File, const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _fwprintf_p_l(FILE * _File, const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _fwprintf_s_l(FILE * _File, const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _vfwprintf_l(FILE * _File, const wchar_t * _Format, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl _vfwprintf_p_l(FILE * _File, const wchar_t * _Format, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl _vfwprintf_s_l(FILE * _File, const wchar_t * _Format, _locale_t _Locale, va_list _ArgList);

__declspec(dllimport) int __cdecl _swprintf_c_l(wchar_t * _DstBuf, size_t _MaxCount, const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _swprintf_p_l(wchar_t * _DstBuf, size_t _MaxCount, const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _swprintf_s_l(wchar_t * _DstBuf, size_t _DstSize, const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _vswprintf_c_l(wchar_t * _DstBuf, size_t _MaxCount, const wchar_t * _Format, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl _vswprintf_p_l(wchar_t * _DstBuf, size_t _MaxCount, const wchar_t * _Format, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl _vswprintf_s_l(wchar_t * _DstBuf, size_t _DstSize, const wchar_t * _Format, _locale_t _Locale, va_list _ArgList);

__declspec(dllimport) int __cdecl _scwprintf_l(const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _scwprintf_p_l(const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _vscwprintf_p_l(const wchar_t * _Format, _locale_t _Locale, va_list _ArgList);

__declspec(dllimport) int __cdecl _snwprintf_l(wchar_t * _DstBuf, size_t _MaxCount, const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _snwprintf_s_l(wchar_t * _DstBuf, size_t _DstSize, size_t _MaxCount, const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _vsnwprintf_l(wchar_t * _DstBuf, size_t _MaxCount, const wchar_t * _Format, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl _vsnwprintf_s_l(wchar_t * _DstBuf, size_t _DstSize, size_t _MaxCount, const wchar_t * _Format, _locale_t _Locale, va_list _ArgList);

#pragma warning(push)
#pragma warning(disable:4141 4996 4793)
__declspec(deprecated("swprintf has been changed to conform with the ISO C standard, adding an extra character count parameter. To use traditional Microsoft swprintf, set _CRT_NON_CONFORMING_SWPRINTFS.")) __declspec(dllimport) int __cdecl _swprintf(wchar_t *_Dest, const wchar_t * _Format, ...);
__declspec(deprecated("swprintf has been changed to conform with the ISO C standard, adding an extra character count parameter. To use traditional Microsoft swprintf, set _CRT_NON_CONFORMING_SWPRINTFS.")) __declspec(dllimport) int __cdecl _vswprintf(wchar_t *_Dest, const wchar_t * _Format, va_list _Args);
__declspec(deprecated("swprintf has been changed to conform with the ISO C standard, adding an extra character count parameter. To use traditional Microsoft swprintf, set _CRT_NON_CONFORMING_SWPRINTFS.")) __declspec(dllimport) int __cdecl __swprintf_l(wchar_t *_Dest, const wchar_t * _Format, _locale_t _Plocinfo, ...);
__declspec(deprecated("swprintf has been changed to conform with the ISO C standard, adding an extra character count parameter. To use traditional Microsoft swprintf, set _CRT_NON_CONFORMING_SWPRINTFS.")) __declspec(dllimport) int __cdecl __vswprintf_l(wchar_t *_Dest, const wchar_t * _Format, _locale_t _Plocinfo, va_list _Args);
#pragma warning(pop)

#pragma once

#pragma warning( push )
#pragma warning( disable : 4793 4412 )
static __inline int swprintf(wchar_t * _String, size_t _Count, const wchar_t * _Format, ...)
{
	va_list _Arglist;
	int _Ret;
	(_Arglist = (va_list)(&(_Format)) + ((sizeof(_Format) + sizeof(int) - 1) & ~(sizeof(int) - 1)));
	_Ret = _vswprintf_c_l(_String, _Count, _Format, ((void *)0), _Arglist);
	(_Arglist = (va_list)0);
	return _Ret;
}
#pragma warning( pop )

#pragma warning( push )
#pragma warning( disable : 4412 )
static __inline int __cdecl vswprintf(wchar_t * _String, size_t _Count, const wchar_t * _Format, va_list _Ap)
{
	return _vswprintf_c_l(_String, _Count, _Format, ((void *)0), _Ap);
}
#pragma warning( pop )

#pragma warning( push )
#pragma warning( disable : 4793 4412 )
static __inline int _swprintf_l(wchar_t * _String, size_t _Count, const wchar_t * _Format, _locale_t _Plocinfo, ...)
{
	va_list _Arglist;
	int _Ret;
	(_Arglist = (va_list)(&(_Plocinfo)) + ((sizeof(_Plocinfo) + sizeof(int) - 1) & ~(sizeof(int) - 1)));
	_Ret = _vswprintf_c_l(_String, _Count, _Format, _Plocinfo, _Arglist);
	(_Arglist = (va_list)0);
	return _Ret;
}
#pragma warning( pop )

#pragma warning( push )
#pragma warning( disable : 4412 )
static __inline int __cdecl _vswprintf_l(wchar_t * _String, size_t _Count, const wchar_t * _Format, _locale_t _Plocinfo, va_list _Ap)
{
	return _vswprintf_c_l(_String, _Count, _Format, _Plocinfo, _Ap);
}
#pragma warning( pop )

__declspec(dllimport) wchar_t * __cdecl _wtempnam(const wchar_t * _Directory, const wchar_t * _FilePrefix);

__declspec(dllimport) int __cdecl _vscwprintf(const wchar_t * _Format, va_list _ArgList);
__declspec(dllimport) int __cdecl _vscwprintf_l(const wchar_t * _Format, _locale_t _Locale, va_list _ArgList);
__declspec(dllimport) int __cdecl fwscanf(FILE * _File, const wchar_t * _Format, ...);
__declspec(dllimport) int __cdecl _fwscanf_l(FILE * _File, const wchar_t * _Format, _locale_t _Locale, ...);
#pragma warning(push)
#pragma warning(disable:6530)

__declspec(dllimport) int __cdecl fwscanf_s(FILE * _File, const wchar_t * _Format, ...);

__declspec(dllimport) int __cdecl _fwscanf_s_l(FILE * _File, const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl swscanf(const wchar_t * _Src, const wchar_t * _Format, ...);
__declspec(dllimport) int __cdecl _swscanf_l(const wchar_t * _Src, const wchar_t * _Format, _locale_t _Locale, ...);

__declspec(dllimport) int __cdecl swscanf_s(const wchar_t *_Src, const wchar_t * _Format, ...);

__declspec(dllimport) int __cdecl _swscanf_s_l(const wchar_t * _Src, const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _snwscanf(const wchar_t * _Src, size_t _MaxCount, const wchar_t * _Format, ...);
__declspec(dllimport) int __cdecl _snwscanf_l(const wchar_t * _Src, size_t _MaxCount, const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl _snwscanf_s(const wchar_t * _Src, size_t _MaxCount, const wchar_t * _Format, ...);
__declspec(dllimport) int __cdecl _snwscanf_s_l(const wchar_t * _Src, size_t _MaxCount, const wchar_t * _Format, _locale_t _Locale, ...);
__declspec(dllimport) int __cdecl wscanf(const wchar_t * _Format, ...);
__declspec(dllimport) int __cdecl _wscanf_l(const wchar_t * _Format, _locale_t _Locale, ...);

__declspec(dllimport) int __cdecl wscanf_s(const wchar_t * _Format, ...);

__declspec(dllimport) int __cdecl _wscanf_s_l(const wchar_t * _Format, _locale_t _Locale, ...);
#pragma warning(pop)

__declspec(dllimport) FILE * __cdecl _wfdopen(int _FileHandle, const wchar_t * _Mode);
__declspec(dllimport) FILE * __cdecl _wfopen(const wchar_t * _Filename, const wchar_t * _Mode);
__declspec(dllimport) errno_t __cdecl _wfopen_s(FILE ** _File, const wchar_t * _Filename, const wchar_t * _Mode);
__declspec(dllimport) FILE * __cdecl _wfreopen(const wchar_t * _Filename, const wchar_t * _Mode, FILE * _OldFile);
__declspec(dllimport) errno_t __cdecl _wfreopen_s(FILE ** _File, const wchar_t * _Filename, const wchar_t * _Mode, FILE * _OldFile);

__declspec(dllimport) void __cdecl _wperror(const wchar_t * _ErrMsg);

__declspec(dllimport) FILE * __cdecl _wpopen(const wchar_t *_Command, const wchar_t * _Mode);

__declspec(dllimport) int __cdecl _wremove(const wchar_t * _Filename);
__declspec(dllimport) errno_t __cdecl _wtmpnam_s(wchar_t * _DstBuf, size_t _SizeInWords);

__declspec(dllimport) wchar_t * __cdecl _wtmpnam(wchar_t *_Buffer);

__declspec(dllimport) wint_t __cdecl _fgetwc_nolock(FILE * _File);
__declspec(dllimport) wint_t __cdecl _fputwc_nolock(wchar_t _Ch, FILE * _File);
__declspec(dllimport) wint_t __cdecl _ungetwc_nolock(wint_t _Ch, FILE * _File);

__declspec(dllimport) void __cdecl _lock_file(FILE * _File);
__declspec(dllimport) void __cdecl _unlock_file(FILE * _File);

__declspec(dllimport) int __cdecl _fclose_nolock(FILE * _File);
__declspec(dllimport) int __cdecl _fflush_nolock(FILE * _File);
__declspec(dllimport) size_t __cdecl _fread_nolock(void * _DstBuf, size_t _ElementSize, size_t _Count, FILE * _File);
__declspec(dllimport) size_t __cdecl _fread_nolock_s(void * _DstBuf, size_t _DstSize, size_t _ElementSize, size_t _Count, FILE * _File);
__declspec(dllimport) int __cdecl _fseek_nolock(FILE * _File, long _Offset, int _Origin);
__declspec(dllimport) long __cdecl _ftell_nolock(FILE * _File);
__declspec(dllimport) int __cdecl _fseeki64_nolock(FILE * _File, __int64 _Offset, int _Origin);
__declspec(dllimport) __int64 __cdecl _ftelli64_nolock(FILE * _File);
__declspec(dllimport) size_t __cdecl _fwrite_nolock(const void * _DstBuf, size_t _Size, size_t _Count, FILE * _File);
__declspec(dllimport) int __cdecl _ungetc_nolock(int _Ch, FILE * _File);

__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_tempnam" ". See online help for details.")) __declspec(dllimport) char * __cdecl tempnam(const char * _Directory, const char * _FilePrefix);

__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_fcloseall" ". See online help for details.")) __declspec(dllimport) int __cdecl fcloseall(void);
__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_fdopen" ". See online help for details.")) __declspec(dllimport) FILE * __cdecl fdopen(int _FileHandle, const char * _Format);
__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_fgetchar" ". See online help for details.")) __declspec(dllimport) int __cdecl fgetchar(void);
__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_fileno" ". See online help for details.")) __declspec(dllimport) int __cdecl fileno(FILE * _File);
__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_flushall" ". See online help for details.")) __declspec(dllimport) int __cdecl flushall(void);
__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_fputchar" ". See online help for details.")) __declspec(dllimport) int __cdecl fputchar(int _Ch);
__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_getw" ". See online help for details.")) __declspec(dllimport) int __cdecl getw(FILE * _File);
__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_putw" ". See online help for details.")) __declspec(dllimport) int __cdecl putw(int _Ch, FILE * _File);
__declspec(deprecated("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: " "_rmtmp" ". See online help for details.")) __declspec(dllimport) int __cdecl rmtmp(void);

#pragma pack(pop)

typedef struct luaL_Reg {
	const char *name;
	lua_CFunction func;
} luaL_Reg;

extern void (luaL_checkversion_)(lua_State *L, lua_Number ver, size_t sz);

extern int (luaL_getmetafield)(lua_State *L, int obj, const char *e);
extern int (luaL_callmeta)(lua_State *L, int obj, const char *e);
extern const char *(luaL_tolstring)(lua_State *L, int idx, size_t *len);
extern int (luaL_argerror)(lua_State *L, int arg, const char *extramsg);
extern const char *(luaL_checklstring)(lua_State *L, int arg,
	size_t *l);
extern const char *(luaL_optlstring)(lua_State *L, int arg,
	const char *def, size_t *l);
extern lua_Number(luaL_checknumber) (lua_State *L, int arg);
extern lua_Number(luaL_optnumber) (lua_State *L, int arg, lua_Number def);

extern lua_Integer(luaL_checkinteger) (lua_State *L, int arg);
extern lua_Integer(luaL_optinteger) (lua_State *L, int arg,
	lua_Integer def);

extern void (luaL_checkstack)(lua_State *L, int sz, const char *msg);
extern void (luaL_checktype)(lua_State *L, int arg, int t);
extern void (luaL_checkany)(lua_State *L, int arg);

extern int   (luaL_newmetatable)(lua_State *L, const char *tname);
extern void  (luaL_setmetatable)(lua_State *L, const char *tname);
extern void *(luaL_testudata)(lua_State *L, int ud, const char *tname);
extern void *(luaL_checkudata)(lua_State *L, int ud, const char *tname);

extern void (luaL_where)(lua_State *L, int lvl);
extern int (luaL_error)(lua_State *L, const char *fmt, ...);

extern int (luaL_checkoption)(lua_State *L, int arg, const char *def,
	const char *const lst[]);

extern int (luaL_fileresult)(lua_State *L, int stat, const char *fname);
extern int (luaL_execresult)(lua_State *L, int stat);

extern int (luaL_ref)(lua_State *L, int t);
extern void (luaL_unref)(lua_State *L, int t, int ref);

extern int (luaL_loadfilex)(lua_State *L, const char *filename,
	const char *mode);

extern int (luaL_loadbufferx)(lua_State *L, const char *buff, size_t sz,
	const char *name, const char *mode);
extern int (luaL_loadstring)(lua_State *L, const char *s);

extern lua_State *(luaL_newstate)(void);

extern lua_Integer(luaL_len) (lua_State *L, int idx);

extern const char *(luaL_gsub)(lua_State *L, const char *s, const char *p,
	const char *r);

extern void (luaL_setfuncs)(lua_State *L, const luaL_Reg *l, int nup);

extern int (luaL_getsubtable)(lua_State *L, int idx, const char *fname);

extern void (luaL_traceback)(lua_State *L, lua_State *L1,
	const char *msg, int level);

extern void (luaL_requiref)(lua_State *L, const char *modname,
	lua_CFunction openf, int glb);

typedef struct luaL_Buffer {
	char *b;
	size_t size;
	size_t n;
	lua_State *L;
	char initb[8192];
} luaL_Buffer;

extern void (luaL_buffinit)(lua_State *L, luaL_Buffer *B);
extern char *(luaL_prepbuffsize)(luaL_Buffer *B, size_t sz);
extern void (luaL_addlstring)(luaL_Buffer *B, const char *s, size_t l);
extern void (luaL_addstring)(luaL_Buffer *B, const char *s);
extern void (luaL_addvalue)(luaL_Buffer *B);
extern void (luaL_pushresult)(luaL_Buffer *B);
extern void (luaL_pushresultsize)(luaL_Buffer *B, size_t sz);
extern char *(luaL_buffinitsize)(lua_State *L, luaL_Buffer *B, size_t sz);

typedef struct luaL_Stream {
	FILE *f;
	lua_CFunction closef;
} luaL_Stream;

extern int (luaopen_base)(lua_State *L);

extern int (luaopen_coroutine)(lua_State *L);

extern int (luaopen_table)(lua_State *L);

extern int (luaopen_io)(lua_State *L);

extern int (luaopen_os)(lua_State *L);

extern int (luaopen_string)(lua_State *L);

extern int (luaopen_utf8)(lua_State *L);

extern int (luaopen_bit32)(lua_State *L);

extern int (luaopen_math)(lua_State *L);

extern int (luaopen_debug)(lua_State *L);

extern int (luaopen_package)(lua_State *L);

extern void (luaL_openlibs)(lua_State *L);

extern int luaopen_bit32(lua_State *L) {
	return luaL_error(L, "library 'bit32' has been deprecated");
}

