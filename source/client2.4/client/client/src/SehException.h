#ifndef __SEH_EXCEPTION_H
#define __SEH_EXCEPTION_H
#include <windows.h>
#include <string>
using namespace std;
////////////////////////////////////////////////////////////////////////////////
class SehExceptionBase : public std::exception
{
public:
	SehExceptionBase (const PEXCEPTION_POINTERS pExp, std::string what )
		: m_ExceptionRecord(*pExp->ExceptionRecord),
		m_ContextRecord(*pExp->ContextRecord),
		m_what(what){};
	~SehExceptionBase() throw(){} ;

	virtual const char* what() const throw()
	{
		return m_what.c_str();
	}

	virtual DWORD GetExceptionCode() const throw()
	{
		return m_ExceptionRecord.ExceptionCode;
	}

	virtual const EXCEPTION_RECORD& GetExceptionRecord() const throw()
	{
		return m_ExceptionRecord;
	}

	virtual const CONTEXT& GetContext() const throw()
	{
		return m_ContextRecord;
	}

	// 初始化函数
	static void InitializeSehTranslator();
	// 系统异常出现时的回调函数
	static void		TransFunc(unsigned int u, EXCEPTION_POINTERS* pExp);
	static string	name(DWORD code);

	string GetRegisterInfo();

protected:
	std::string m_what;
	EXCEPTION_RECORD m_ExceptionRecord;
	CONTEXT m_ContextRecord;
};

////////////////////////////////////////////////////////////////////////////////
// 系统异常被转换后的 C++ 类型的异常, 后续扩充
////////////////////////////////////////////////////////////////////////////////
class SehExceptionAccessViolation : public SehExceptionBase
{
public:
	SehExceptionAccessViolation (const PEXCEPTION_POINTERS pExp, std::string what)
		: SehExceptionBase(pExp, what) {};
	~SehExceptionAccessViolation() throw(){};
};
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class SehExceptionDivideByZero : public SehExceptionBase
{
public:
	SehExceptionDivideByZero (const PEXCEPTION_POINTERS pExp, std::string what)
		: SehExceptionBase(pExp, what) {};
	~SehExceptionDivideByZero() throw(){};
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
class SehExceptionInvalidHandle : public SehExceptionBase
{
public:
	SehExceptionInvalidHandle (const PEXCEPTION_POINTERS pExp, std::string what)
		: SehExceptionBase(pExp, what) {};
	~SehExceptionInvalidHandle() throw(){};
};

#endif