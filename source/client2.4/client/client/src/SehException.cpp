#include "stdafx.h"
#include "SehException.h"
#include "CallStack.h"
#include "GameErrorReport.h"
#include "LEResManger.h"

#include <sstream>
#pragma warning(disable:4311) //type cast warning
#pragma warning(disable:4312) //warning C4312: 'type cast' : conversion from 'DWORD' to 'void *' of greater size

//----------------------------------------------------------------------------
// Structure Definitions
//----------------------------------------------------------------------------


////////////////////////////////////////////////////////////////////////////////
// 系统异常出现时的回调函数
// 针对不同的异常，抛出一个 C++ 类型的异常
void SehExceptionBase::TransFunc(unsigned int u, EXCEPTION_POINTERS* pExp)
{
	DWORD& ExceptionCode = pExp->ExceptionRecord->ExceptionCode;
	std::string msg = SehExceptionBase::name(ExceptionCode);
	switch(ExceptionCode)
	{
	case EXCEPTION_ACCESS_VIOLATION:	throw SehExceptionAccessViolation(pExp, msg);	break;
	case EXCEPTION_INT_DIVIDE_BY_ZERO: 	throw SehExceptionDivideByZero(pExp, msg); 		break;
	case EXCEPTION_INVALID_HANDLE :		throw SehExceptionInvalidHandle(pExp, msg);		break;
	default:							throw SehExceptionBase(pExp, msg);				break;
	}
}

LONG WINAPI UnExcept(
	EXCEPTION_POINTERS* pExceptionPointers) ///< Pointer to information about the exception
{
	string info = "Unhandle Exception\n";
	AddCallingFunctionName(info, 2); //2:跳过UnExcept函数地址
	ErrorReport(info.c_str());
	return EXCEPTION_EXECUTE_HANDLER;
}

void WINAPI InvalidParameterHandler(const wchar_t* expression,
							   const wchar_t* function, 
							   const wchar_t* file, 
							   unsigned int line, 
							   uintptr_t pReserved)
{
	string info = "Invalid Parameter\n";
	AddCallingFunctionName(info, 2); //2:跳过InvalidParameterHandler函数地址

	// 只记录不弹出报错框
	try
	{
		ErrorLog(info.c_str());
	}
	catch(...)
	{

	}
}

void SehExceptionBase::InitializeSehTranslator()
{
	::SetUnhandledExceptionFilter(UnExcept);
	::_set_invalid_parameter_handler((_invalid_parameter_handler)InvalidParameterHandler);
	_set_se_translator( TransFunc );
	::SetErrorLogFunc(GameErrorLog);
	::SetErrorReportFunc(GameErrorReport);
	ResMgr.SetErrorLogFunc(GameErrorLog);
	ResMgr.SetErrorReportFunc(GameErrorReport);
	::GameErrorClear();
}

string SehExceptionBase::name(DWORD code)
{
	switch (code)
	{
	case EXCEPTION_ACCESS_VIOLATION :			return "Access Violation";
	case EXCEPTION_DATATYPE_MISALIGNMENT :		return "Datatype Misalignment";
	case EXCEPTION_BREAKPOINT :					return "Breakpoint";
	case EXCEPTION_SINGLE_STEP :				return "Single Step";
	case EXCEPTION_ARRAY_BOUNDS_EXCEEDED :		return "Array Bounds Exceeded";
	case EXCEPTION_FLT_DENORMAL_OPERAND :		return "Float Denormal Operand";
	case EXCEPTION_FLT_DIVIDE_BY_ZERO :			return "Float Divide by Zero";
	case EXCEPTION_FLT_INEXACT_RESULT :			return "Float Inexact Result";
	case EXCEPTION_FLT_INVALID_OPERATION :		return "Float Invalid Operation";
	case EXCEPTION_FLT_OVERFLOW :				return "Float Overflow";
	case EXCEPTION_FLT_STACK_CHECK :			return "Float Stack Check";
	case EXCEPTION_FLT_UNDERFLOW :				return "Float Underflow";
	case EXCEPTION_INT_DIVIDE_BY_ZERO :			return "Integer Divide by Zero";
	case EXCEPTION_INT_OVERFLOW :				return "Integer Overflow";
	case EXCEPTION_PRIV_INSTRUCTION :			return "Privileged Instruction";
	case EXCEPTION_IN_PAGE_ERROR :				return "In Page Error";
	case EXCEPTION_ILLEGAL_INSTRUCTION :		return "Illegal Instruction";
	case EXCEPTION_NONCONTINUABLE_EXCEPTION :	return "Noncontinuable Exception";
	case EXCEPTION_STACK_OVERFLOW :				return "Stack Overflow";
	case EXCEPTION_INVALID_DISPOSITION :		return "Invalid Disposition";
	case EXCEPTION_GUARD_PAGE :					return "Guard Page";
	case EXCEPTION_INVALID_HANDLE :				return "Invalid Handle";
	case 0xE06D7363 :							return "Microsoft C++ Exception";
	default :
		{
			stringstream text;
			text << "Unknown SEH-Exception" << code;
			return text.str();
		}
	};
}

#define MAX_LINE 8
#define PER_LINE 16
string  MyDump(char* szTitle, void *buffer, int n)
{
	unsigned char *pBuf = (unsigned char *)buffer;

	const size_t dstsize = 80+MAX_LINE*(PER_LINE*3+PER_LINE+1)+1;
	char bytes[dstsize] = {0};
	char* p = bytes;
	_snprintf_s(p, dstsize, _TRUNCATE, "Dump:%s(%08x)\n", szTitle, (DWORD)pBuf);
	if( pBuf==0 )
		return "";
	p+= strlen(p);
	char chr[30];
	int line = 0;
	int x = 0;
	char asc[PER_LINE+1];
	do
	{
		unsigned char c = pBuf[line*PER_LINE+x];

		_snprintf_s(chr, _countof(chr), _TRUNCATE, "%02X ", c);
		memcpy(p, chr, 3);
		p += 3;

		if( c >= 32 && c<128 )
			asc[x] = c;
		else
			asc[x] = '.';

		x ++;
		if( x==PER_LINE )
		{
			memcpy(p, asc, PER_LINE);
			p += PER_LINE;
			*(p++) = '\n';
			x = 0;
			line++;
			if( line==MAX_LINE )
				break;
		}
		else if( line*PER_LINE+x == n ) //没写锟斤拷一锟斤拷
		{
			memset(p, ' ', (PER_LINE-x)*3);
			p += (PER_LINE-x)*3;
			memcpy(p, asc, x);
			p[x] = '\n';
			break;
		}
	}
	while(1);
	return bytes;
} 

string SehExceptionBase::GetRegisterInfo()
{
	string str;
	char tim[256] = {0};
	_snprintf_s(tim,sizeof(tim),_TRUNCATE, "%s\n", m_what.c_str());
	str = tim;
	_snprintf_s(tim,sizeof(tim),_TRUNCATE, "\
   EIP=0x%08x  EBP=0x%08x  ESP=0x%08x  EFL=0x%08x\n\
   EAX=0x%08x  EBX=0x%08x  ECX=0x%08x  EDX=0x%08x\n\
   ESI=0x%08x  EDI=0x%08x  CTF=0x%08x\n\n",
    m_ContextRecord.Eip, m_ContextRecord.Ebp, m_ContextRecord.Esp, m_ContextRecord.EFlags, 
    m_ContextRecord.Eax, m_ContextRecord.Ebx, m_ContextRecord.Ecx, m_ContextRecord.Edx,
    m_ContextRecord.Esi, m_ContextRecord.Edi, m_ContextRecord.ContextFlags);
	str += tim;
	if( m_ContextRecord.Esp )
		str += MyDump("ESP", (void*)(m_ContextRecord.Esp), 256);
	return str;
}
