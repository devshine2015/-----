#pragma once


class CTomService
{
public:
	CTomService(void);
	~CTomService(void);

	bool InitService();													//初始化Tom服务系统
	bool VerifyLoginMember(const char* lpszUserName, const char* lpszMD5PSW);		//true:正确 false:错误
	void ReportMemberCounts(int nCounts);								//向Tom报告在线玩家数量
	bool IsEnable();													//返回是否启用了Tom服务系统
	//enum eState{eState_AllowLogin, eState_LoginLocked};
	//eState CheckMemberState(const char* lpszUserName);


private:
#ifndef NOAUTHDLL
	typedef void (*GameOnline)(int); 
	typedef bool (*UserAttest)(char* lpszUserName, char* lpszMD5PSW);
	UserAttest  pUserAttestFun;
	GameOnline  pGameOnlineFun;
#else
	bool pUserAttestFun(char* lpszUserName, char* lpszMD5PSW);
	void pGameOnlineFun(int);
#endif
	

private:
	HMODULE m_hTomMod;
	bool m_bEnableService;

	//key=用户名，data=下线Tick时刻（0代表在线）
	//map<const char*, DWORD> m_mapUserState;
};
