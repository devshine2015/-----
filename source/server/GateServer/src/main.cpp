// main.cpp : Defines the entry point for the console application.
//

#include "gateserver.h"
_DBC_USING;

BYTE g_wpe = 0;
BYTE g_ddos = 0;
uShort g_wpeversion = NULL;
HANDLE hConsole = NULL;

//#pragma init_seg( lib )
pi_LeakReporter pi_leakReporter("gatememleak.log");
CResourceBundleManage g_ResourceBundleManage("GateServer.loc"); //Add by lark.li 20080130

//#include <ExceptionUtil.h>

int main(int argc, char* argv[])
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	C_PRINT("GateServer 1.38 (by: Sheep Squad)\n");
	C_PRINT("GateServer 1.38 (ÓÅ»¯by: ÉÏ¹Ùè¤è¤)\n");
	C_TITLE("GateServer.exe")
	SEHTranslator translator;

	T_B

	const char* file_cfg = "GateServer.cfg";
	IniFile inf(file_cfg);
	try
	{
		g_wpe = atoi(inf["ToClient"]["WpeProtection"]);
		string v = inf["ToClient"]["WpeVersion"];
		g_wpeversion = (uShort)strtoul(v.c_str(), NULL, 16);
		g_ddos = atoi(inf["ToClient"]["DDoSProtection"]);
	}
	catch (...)
	{
		g_wpe = 0;
		g_ddos = 0;
	}

	// Add by lark.li 20080731 begin
	pi_Memory m;
	m.startMonitor(1);
	// End

	::SetLGDir("logfile/log");

	GateServerApp app;
	app.ServiceStart();	
	g_gtsvr->RunLoop();
	app.ServiceStop();

	// Add by lark.li 20080731 begin
	m.stopMonitor();
	m.wait();
	// End

	T_FINAL
	return 0;
}