#ifndef _GATESERVER_H_
#define _GATESERVER_H_

#include <iostream>
#include <map>
#include <time.h>
#include <dstring.h>
#include <datasocket.h>
#include <threadpool.h>
#include <commrpc.h>
#include <point.h>
#include <inifile.h>
#include <gamecommon.h>
#include <prealloc.h>
#include <ntservice.h>
#include <LogStream.h>
#include <algo.h>

#include "i18n.h"		//Add by lark.li 20080130

// Add by lark.li 20080731 begin
#include "pi_Memory.h"
#include "pi_Alloc.h"
// End

using namespace std;
using namespace dbc;

// 计时退出机制宏切换
//#define CHAEXIT_ONTIME

// 关于 Client 连接部分＝＝＝＝＝＝＝＝＝＝
struct Player;
class ToClient : public TcpServerApp, public RPCMGR
{
	friend class TransmitCall;
public:
    ToClient(char const* fname, ThreadPool* proc, ThreadPool* comm);
    ~ToClient();

    void post_mapcrash_msg(Player* ply);
	dstring			GetDisconnectErrText(int reason);
	void SetMaxCon(uShort maxcon){m_maxcon	=maxcon;}
	uShort GetMaxCon(){return m_maxcon;}
    void CM_LOGIN(DataSocket* datasock, RPacket& recvbuf);
	WPacket CM_LOGOUT(DataSocket* datasock, RPacket& recvbuf);
	WPacket CM_DISCONN(DataSocket* datasock, RPacket& recvbuf);
	void CM_BGNPLAY(DataSocket* datasock, RPacket& recvbuf);
	void CM_ENDPLAY(DataSocket* datasock, RPacket& recvbuf);
	void CM_NEWCHA(DataSocket* datasock, RPacket& recvbuf);
	void CM_REGISTER(DataSocket* datasock, RPacket& recvbuf);
	void CP_CHANGEPASS(DataSocket* datasock, RPacket& recvbuf);
	void CM_DELCHA(DataSocket* datasock, RPacket& recvbuf);
	void CM_CREATE_PASSWORD2(DataSocket* datasock, RPacket& recvbuf);
	void CM_UPDATE_PASSWORD2(DataSocket* datasock, RPacket& recvbuf);
	void CM_OPERGUILDBANK(DataSocket* datasock, RPacket& recvbuf);
	uShort GetVersion() { return m_version; }
	int GetCallTotal() { return m_calltotal; }

	uShort GetCheckSpan(){return m_checkSpan;}
	uShort GetCheckWaring(){return m_checkWaring;}
	uShort GetCheckError(){return m_checkError;}

	void	SetCheckSpan(uShort checkSpan);
	void	SetCheckWaring(uShort checkWaring);
	void	SetCheckError(uShort checkError);

private:
	bool		 DoCommand(DataSocket* datasock, cChar *cmdline);
    virtual bool OnConnect(DataSocket* datasock); // 返回值:true-允许连接,false-不允许连接
    virtual void OnConnected(DataSocket* datasock);
    virtual void OnDisconnect(DataSocket* datasock, int reason);
    virtual void OnProcessData(DataSocket* datasock, RPacket &recvbuf);
    virtual WPacket OnServeCall(DataSocket* datasock, RPacket &in_para);
	virtual bool OnSendBlock(DataSocket	*datasock){return false;}

    // communication encryption
    virtual void OnEncrypt(DataSocket *datasock,char *ciphertext,const char *text,uLong &len);
    virtual void OnDecrypt(DataSocket *datasock,char *ciphertext,uLong &len);

	InterLockedLong	m_atexit,m_calltotal;
	volatile uShort m_maxcon;
	uShort m_version;
    int _comm_enc; // 加密算法索引

	volatile uShort	m_checkSpan;
	volatile uShort	m_checkWaring;
	volatile uShort	m_checkError;

	IMPLEMENT_CDELETE(ToClient)
};

// 关于 GameServer 连接部分＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
class ToGameServer;

#define MAX_MAP 100
#define MAX_GAM 100
struct GameServer : public PreAllocStru
{
    friend class PreAllocHeap<GameServer>;

private:
    GameServer(uLong Size) : PreAllocStru(Size),
        m_datasock(NULL), next(NULL) {}
    ~GameServer()
        {if (m_datasock != NULL) {m_datasock->SetPointer(NULL); m_datasock = NULL;}}
    GameServer(GameServer const&) : PreAllocStru(1) {}
    GameServer& operator =(GameServer const&) {}
    void Initially();
    void Finally();
public:
	void EnterMap(Player *ply,uLong actid, uLong dbid,uLong worldid,cChar *map, Long lMapCpyNO,uLong x,uLong y,char entertype,short swiner);	//角色chaid进入本服务器的地图map中的位置(x,y) winer指定角色是否是乱斗之王。
public:
	InterLockedLong m_plynum;
    string gamename;
    string ip;
    uShort port;
    DataSocket* m_datasock;
    GameServer* next;
    string maplist[MAX_MAP];
    uShort mapcnt;
};

class ToGameServer : public TcpServerApp, public RPCMGR
{
	friend class ToGroupServer;
public:
    ToGameServer(char const* fname, ThreadPool* proc, ThreadPool* comm);
    ~ToGameServer();

    GameServer* find(cChar* mapname);
	GameServer* GetGameList() { return _game_list; }

private:
    virtual bool OnConnect(DataSocket* datasock); //返回值:true-允许连接,false-不允许连接
    virtual void OnDisconnect(DataSocket* datasock, int reason);
    virtual	WPacket OnServeCall(DataSocket* datasock, RPacket &in_para);
    virtual void OnProcessData(DataSocket* datasock, RPacket &recvbuf);

    PreAllocHeap<GameServer> _game_heap; // GameServer 描述对象堆
    void MT_LOGIN(DataSocket* datasock, RPacket& recvbuf); // GameServer 登录 GateServer

    GameServer* _game_list; // 存储 GameServer 描述对象的链表
    short _game_num;
    void _add_game(GameServer* game);
    bool _exist_game(char const* game);
    void _del_game(GameServer* game);
    map<string, GameServer*> _map_game; // 从地图名对应 GameServer 描述对象
    Mutex _mut_game;

	IMPLEMENT_CDELETE(ToGameServer)
};

// 关于 GroupServer 连接部分＝＝＝＝＝＝＝＝＝＝
class ToGroupServer;
class ConnectGroupServer : public Task
{
public:
    ConnectGroupServer(ToGroupServer* tgts) {_tgps = tgts; _timeout = 3000;}
private:
    virtual long Process();
	virtual Task*Lastly();

    ToGroupServer* _tgps;
    DWORD _timeout;
};

struct GroupServer
{
    GroupServer() : datasock(NULL), next(NULL) {}
    string ip; uShort port;
    DataSocket* datasock;
    GroupServer* next;
};

class ToGroupServer : public TcpClientApp, public RPCMGR
{
    friend class ConnectGroupServer;
	friend void ToGameServer::MT_LOGIN(DataSocket* datasock, RPacket& rpk);
public:
    ToGroupServer(char const* fname, ThreadPool* proc, ThreadPool* comm);
    ~ToGroupServer();

    DataSocket* get_datasock() const {return _gs.datasock;}
    RPacket get_playerlist();
	
	int GetCallTotal() { return m_calltotal; }

	// Add by lark.li 20081119 begin
	bool	IsSync() { return m_bSync; }
	void	SetSync(bool sync=true) { m_bSync = sync; }
	// End

	// 准备好
	bool	IsReady() {  return (!m_bSync && _connected); }

private:
    virtual bool OnConnect(DataSocket* datasock); // 返回值:true-允许连接,false-不允许连接
    virtual void OnDisconnect(DataSocket* datasock, int reason);
    virtual void OnProcessData(DataSocket* datasock, RPacket &recvbuf);
    virtual WPacket OnServeCall(DataSocket* datasock, RPacket &in_para);
    
	InterLockedLong	m_atexit,m_calltotal;

	string _myself; // GateServer自己的名字
    GroupServer _gs;
    bool volatile _connected;

	// Add by lark.li 20081119 begin
    bool volatile m_bSync;
	// End

	IMPLEMENT_CDELETE(ToGroupServer)
};
// GateServer 自身部分＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
struct Player : public PreAllocStru , public RunBiDirectItem<Player>
{
    friend class PreAllocHeap<Player>;
	friend class DelayLogout;
public:
    bool InitReference(DataSocket* datasock);
	void Free(){PreAllocStru::Free();}

	// Add by lark.li 20081119 begin
	bool BeginRun();
	bool EndRun();
	//End


	//add by Billy
	void SetSpectating(Player* ply, bool hijack = false, bool lock = false);
	void AddSpectator(Player* ply);
	void RemoveSpectator(Player* ply);
	void UpdateSpectated();
	void StopSpectating();
	void StopSpectators();
	void SendPacketToClient(WPacket pkt);
	void SendPacketToGameServer(WPacket pkt);
	void SendPacketToGroupServer(WPacket pkt);

	vector<Player*> spectators;
	Player* spectating;
	bool isSpectated;
	bool hijack;
	bool islocked;
	bool haslocked;

	// End

	char	m_chapstr[20];
	char	m_password[ROLE_MAXSIZE_PASSWORD2+1];
	char	m_szSendKey[4];
	char	m_szRecvKey[4];




	uLong	volatile	m_actid;
    uLong   volatile    m_loginID;
    uLong	volatile	m_dbid;		// 当前角色的数据库ID
	uLong	volatile	m_worldid;	// 当前角色的内存唯一ID
	uLong	volatile	m_pingtime;
    uInt	volatile	comm_key_len; // 通讯密钥长度
    char	comm_textkey[12]; // GateServer 与 Client 之间加密通讯的密钥
    InterLockedLong gm_addr; // GameServer 上 Player 对象的指针
    InterLockedLong gp_addr; // GroupServer 上 Player 对象的指针
    DataSocket* volatile m_datasock; // 此 Player 的 GateServer <-> Client 连接
    GameServer* volatile game; // 此 Player 当前所在的 GameServer 描述对象
    volatile bool enc; // 是否加密通信数据

	// 是否禁言
	uLong	volatile m_lestoptick;
	bool	volatile m_estop;
	short	volatile m_sGarnerWiner;

	struct
	{
		Mutex				m_mtxstat;					//0:锁定m_status;
		volatile char		m_status;					//0:无效;1.选角色期间;2.玩游戏中.
		volatile char		m_exit;						//0:无效；1.角色正在请求计时退出中，准备进入选人界面；2.角色正在请求计时退出中，要断线退出游戏。
	};

	dbc::dstring m_chamap;
	void		SetMapName(dbc::cChar *cszName) {m_chamap = cszName;}
	const char*	GetMapName(void) {return m_chamap.c_str();}

private:
    Player(uLong Size) : PreAllocStru(Size),
        m_datasock(NULL), game(NULL), gm_addr(0), gp_addr(0), m_dbid(0),m_worldid(0),m_status(0),m_sGarnerWiner(0)
	{m_mtxstat.Create(false);}
    ~Player()
        {if (m_datasock != NULL) {m_datasock->SetPointer(NULL); m_datasock = NULL;}}
    Player(Player const&) : PreAllocStru(1) {}
    Player& operator =(Player const&) {}
    void Initially(); void Finally();
};
class TransmitCall :public PreAllocTask
{
public:
	TransmitCall(uLong size):PreAllocTask(size){};
	void Init(DataSocket* datasock, RPacket &recvbuf){m_datasock	=datasock;m_recvbuf	=recvbuf;}
	long Process();

	DataSocket* m_datasock;
	RPacket		m_recvbuf;
};
class GateServer
{
public:
    GateServer(char const* fname);
    ~GateServer();
	void RunLoop(); // 主循环
	ThreadPool	*m_clproc,*m_clcomm,*m_gpcomm,*m_gpproc,*m_gmcomm;
    ToGroupServer* gp_conn; // 同GroupServer的连接对象（主动重连机制）
    ToGameServer* gm_conn; // 同GameServer的连接对象（被动）
    ToClient* cli_conn; // 同Client的连接对象（被动）
	Mutex	_mtxother;

    PreAllocHeap<Player>		player_heap; // 玩家对象堆

	// Add by lark.li 20081119 begin
	RunBiDirectChain<Player> 	m_plylst;	// 玩家连表
	// End

	PreAllocHeap<TransmitCall>	m_tch;

	IMPLEMENT_CDELETE(GateServer)
};
extern GateServer* g_gtsvr;
extern bool volatile g_appexit;

class CUdpManage;
class CUdpServer;
class GateServerApp:public NTService
{
public:
	GateServerApp();

	void ServiceStart();
	void ServiceStop();
	virtual cChar *SetSvcName()const	{return "GateServer";	}
	virtual cChar *SetDispName()const	{return "[Kop Online]Gate Server";	}//显示名缺省等于服务名
	virtual bool CanPaused()const		{return true;};	//缺省支持暂停和继续操作

	int		GetShowMin()				{ return _nShowMin;		}
	int		GetShowMax()				{ return _nShowMax;		}
	void	SetShowRange( int min, int max )	{ _nShowMin=min; _nShowMax=max;		}

	
private:	// 用于在未连接前，客户端通过udp获得游戏统计信息Jerry 2006-1-10
	CUdpManage*	_pUdpManage;
	static void _NotifySocketNumEvent( CUdpManage* pManage, CUdpServer* pUdpServer, const char* szClientIP, unsigned int nClientPort, const char* pData, int len );
	static int	_nShowMin;	
	static int	_nShowMax;	
};

extern LogStream g_gateerr;
extern LogStream g_gatelog;
extern LogStream g_chkattack;
extern LogStream g_gateconnect;
//extern LogStream g_gatepacket;
extern GateServerApp* g_app;
extern BYTE g_wpe;
extern BYTE g_ddos;
extern uShort g_wpeversion;
extern HANDLE hConsole;
extern InterLockedLong g_exit;

#define C_PRINT(s, ...) \
	SetConsoleTextAttribute(hConsole, 14); \
	printf(s, __VA_ARGS__); \
	SetConsoleTextAttribute(hConsole, 10);

#define C_TITLE(s) \
	char szPID[32]; \
	_snprintf_s(szPID,sizeof(szPID),_TRUNCATE, "%d", GetCurrentProcessId()); \
	std::string strConsoleT; \
	strConsoleT += "[PID:"; \
	strConsoleT += szPID; \
	strConsoleT += "]"; \
	strConsoleT += s; \
	SetConsoleTitle(strConsoleT.c_str());

extern CResourceBundleManage g_ResourceBundleManage; //Add by lark.li 20080130

#endif // _GATESERVER_H_
