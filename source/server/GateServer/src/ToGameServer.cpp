
#include "gateserver.h"


ToGameServer::ToGameServer(char const* fname, ThreadPool* proc, ThreadPool* comm)
: TcpServerApp(this, proc, comm), RPCMGR(this), _mut_game(),
_game_heap(1, 20), _game_list(NULL), _map_game()
{
	_mut_game.Create(false); _game_num = 0;

	// 开始监听
	IniFile inf(fname);
	IniSection& is = inf["ToGameServer"];
	cChar* ip = is["IP"]; uShort port = atoi(is["Port"]);

	// 启动 PING 线程

	SetPKParse(0, 2, 64 * 1024, 400); BeginWork(atoi(is["EnablePing"]));
	if (OpenListenSocket(port, ip) != 0)
		THROW_EXCP(excp, "ToGameServer listen failed");
}

ToGameServer::~ToGameServer() {ShutDown(12 * 1000);}

void ToGameServer::_add_game(GameServer* game)
{
	game->next = _game_list;
	_game_list = game;
	++ _game_num;
}

bool ToGameServer::_exist_game(char const* game)
{
	GameServer* curr = _game_list;
	bool exist = false;

	while (curr)
	{
		if (curr->gamename == game) {exist = true; break;}
		curr = curr->next;
	}

	return exist;
}

void ToGameServer::_del_game(GameServer* game)
{
	GameServer* curr = _game_list;
	GameServer* prev = 0;
	while (curr)
	{
		if (curr == game) break;
		prev = curr; curr = curr->next;
	}

	if (curr)
	{
		if (prev)
			prev->next = curr->next;
		else
			_game_list = curr->next;
		-- _game_num;
	}
}

bool ToGameServer::OnConnect(DataSocket* datasock) // 返回值:true-允许连接,false-不允许连接
{
	datasock->SetPointer(0);
	datasock->SetRecvBuf(64 * 1024);
	datasock->SetSendBuf(64 * 1024);
	LogLine l_line(g_gatelog);
	l_line<<newln<<"GameServer= ["<<datasock->GetPeerIP()<<"] 来了,Socket数目= "<<GetSockTotal()+1;
	//l_line<<newln<<"GameServer= ["<<datasock->GetPeerIP()<<"] come,Socket num= "<<GetSockTotal()+1;
	return true;
}

void ToGameServer::OnDisconnect(DataSocket* datasock, int reason) // reason值:0-本地程序正常退出；-3-网络被对方关闭；-1-Socket错误;-5-包长度超过限制。
{
	LogLine l_line(g_gatelog);
	l_line<<newln<<"GameServer= ["<<datasock->GetPeerIP()<<"] 走了,Socket数目= "<<GetSockTotal()+1<<",reason= "<<GetDisconnectErrText(reason).c_str();
	//l_line<<newln<<"GameServer= ["<<datasock->GetPeerIP()<<"] gone,Socket num= "<<GetSockTotal()+1<<",reason= "<<GetDisconnectErrText(reason).c_str();
	l_line<<endln;
	if(reason ==DS_SHUTDOWN || reason ==DS_DISCONN) return;
	GameServer* l_game = (GameServer *)(datasock->GetPointer());
	bool already_delete = false;
	if (l_game == NULL)
		return;

	// 从链表中删除此 GameServer
	_mut_game.lock();
	try
	{
		l_game = (GameServer *)(datasock->GetPointer());
		if (l_game != NULL)
		{
			l_line<<newln<<"删除掉 ["<<l_game->gamename.c_str()<<"]"<<endln;
			//l_line<<newln<<" delete ["<<l_game->gamename.c_str()<<"]"<<endln;
			_del_game(l_game);
			for (int i = 0; i < l_game->mapcnt; ++ i)
			{
				l_line<<newln<<"删除地图 ["<<l_game->maplist[i].c_str()<<"]"<<endln;
				//l_line<<newln<<"delete map ["<<l_game->maplist[i].c_str()<<"]"<<endln;
				_map_game.erase(l_game->maplist[i]);
			}
			l_game->mapcnt = 0;
			l_game->Free();
			datasock->SetPointer(NULL);
		}else
		{
			already_delete = true;
		}
	}catch (...)
	{
		l_line<<newln<<"Exception raised from OnDisconnect{从链表中删除此 GameServer}"<<endln;
		//l_line<<newln<<"Exception raised from OnDisconnect{delete GameServer from list}"<<endln;
	}
	_mut_game.unlock();

	if (already_delete) return;

	// 通知通过此GateServer连上此GameServer的所有用户：地图服务器故障
	RPacket retpk = g_gtsvr->gp_conn->get_playerlist();
	uShort ply_cnt = retpk.ReverseReadShort(); // 此GateServer上所有玩家个数

	Player* ply_addr; uLong db_id;
	Player** ply_array = new Player*[ply_cnt];
	uShort	l_notcount	=0;
	for (uShort i = 0; i < ply_cnt; ++ i)
	{
		ply_addr = (Player *)MakePointer(retpk.ReadLong());
		db_id = (uLong)retpk.ReadLong();
		if(l_game ==ply_addr->game)
		{
			ply_array[i -l_notcount] = ply_addr;
		}else
		{
			l_notcount	++;
			continue;
		}

		try
		{ // 二次确认
			uLong tmp_id = ply_addr->m_dbid;
			if (tmp_id != db_id) // 此角色已下线
				continue;
		}catch (...)		// 产生异常，标识此角色同样已不在线
		{
			continue;
		}

		try
		{
			g_gtsvr->cli_conn->post_mapcrash_msg(ply_addr); // 此用户仍然在线，发送地图服务器故障消息
		}catch (...)
		{
			continue;
		}

		continue;
	}

	ply_cnt	-=l_notcount;
	l_line<<newln<<"由于GameServer 故障，要通知 "<<ply_cnt<<" 个用户下线"<<endln;
	//l_line<<newln<<"becaulse GameServer trouble, notice "<<ply_cnt<<" user offline"<<endln;
	for (i = 0; i < ply_cnt; ++ i)
	{
		try			//立即断掉这条连接
		{
			l_line<<newln<<"由于GameServer 故障，主动断开与 ["<<ply_array[i]->m_datasock->GetPeerIP()<<"] 的连接"<<endln;
			//l_line<<newln<<"becaulse GameServer trouble, disconnect ["<<ply_array[i]->m_datasock->GetPeerIP()<<"] "<<endln;
			g_gtsvr->cli_conn->Disconnect(ply_array[i]->m_datasock,100,-29);
		}catch (...)
		{
		}
	}

	delete ply_array;
}

WPacket ToGameServer::OnServeCall(DataSocket* datasock, RPacket &in_para)
{
	/*
	GameServer* l_game = (GameServer *)(datasock->GetPointer());
	WPacket l_retpk = GetWPacket();
	uShort l_cmd = in_para.ReadCmd();

	return l_retpk;
	*/

	return NULL;
}

void ToGameServer::OnProcessData(DataSocket* datasock, RPacket &recvbuf)
{
	GameServer* l_game = (GameServer *)(datasock->GetPointer());

	uShort l_cmd = recvbuf.ReadCmd();
	//LG("ToGameServer", "-->l_cmd = %d\n", l_cmd);
	try
	{
		switch (l_cmd)
		{


		case CMD_MT_SPECTATEUPDATE:{
			//int userID = recvbuf.ReverseReadLong();
			//Player *l_ply = g_gtsvr->GetPlayerByID(userID);
			Player	*l_ply = (Player *)MakePointer(recvbuf.ReverseReadLong());
			if (l_ply){
				WPacket	l_wpk = WPacket(recvbuf).Duplicate();
				l_wpk.WriteCmd(CMD_MC_ENTERMAP);
				l_ply->m_datasock->SendData(l_wpk);
			}
			break;
		}
		case CMD_MT_SPECTATE:{
			//int userID = recvbuf.ReadLong();//user who is spectating
			//int spectatorID = recvbuf.ReadLong();//user being spectated
			bool hijack = recvbuf.ReadChar();
			bool lock = recvbuf.ReadChar();

			int specID = recvbuf.ReadLong();
			int targetID = recvbuf.ReadLong();

			Player	*l_ply = (Player *)MakePointer(specID);
			Player	*l_ply2 = (Player *)MakePointer(targetID);

			if (!l_ply){
				break;
			}

			if (!l_ply2 || l_ply == l_ply2){
				l_ply->StopSpectating();
			}else{
				l_ply->SetSpectating(l_ply2,hijack,lock);
			}
			
			break;
		}

		case CMD_MP_GM1SAY:
		case CMD_MP_DISCORD2PM:{
			g_gtsvr->gp_conn->SendData(g_gtsvr->gp_conn->get_datasock(), WPacket(recvbuf));
			break;
		}
		case CMD_MT_DISCORDLOGS:{
			GameServer* discord = g_gtsvr->gm_conn->find("Discord");
			if (discord){
				discord->m_datasock->SendData(WPacket(recvbuf));
			}
			break;
		}

		case CMD_MT_SAYFROMDISCORD:{
			//send this to all ingame players.
			WPacket l_wpk = GetWPacket();
			l_wpk.WriteCmd(CMD_PC_SAY2DIS);
			l_wpk.WriteString(recvbuf.ReadString());
			l_wpk.WriteString(recvbuf.ReadString());
			RPacket retpk = g_gtsvr->gp_conn->get_playerlist();
			uShort ply_cnt = retpk.ReverseReadShort();
			Player* ply_addr;
			for (uShort i = 0; i < ply_cnt; ++i){
				ply_addr = (Player *)MakePointer(retpk.ReadLong());
				retpk.ReadLong();
				ply_addr->m_datasock->SendData(l_wpk);
			}
			break;
		}
		case CMD_MT_LOGIN:
			MT_LOGIN(datasock, recvbuf);        
			break;
		case CMD_MT_SWITCHMAP:
			{
				RPacket	l_rpk		=recvbuf;
				uShort	l_aimnum	=l_rpk.ReverseReadShort();		//l_aimnum永远等于1

				Player *l_ply	=(Player *)MakePointer(l_rpk.ReverseReadLong());
				if(l_ply->m_dbid	!=l_rpk.ReverseReadLong())					//chaid
				{
					return;
				}
				uChar	l_return	=l_rpk.ReverseReadChar();
				recvbuf.DiscardLast(sizeof(uChar) +sizeof(uLong)*2*l_aimnum + sizeof(uShort));

				cChar	*l_srcmap	=l_rpk.ReadString();
				Long	lSrcMapCopyNO = l_rpk.ReadLong();
				//...
				uLong	l_srcx	=l_rpk.ReadLong();	//坐标
				uLong	l_srcy	=l_rpk.ReadLong();	//坐标

				cChar	*l_map	=l_rpk.ReadString();
				Long	lMapCopyNO = l_rpk.ReadLong();
				//...
				uLong	l_x	=l_rpk.ReadLong();	//坐标
				uLong	l_y	=l_rpk.ReadLong();	//坐标
				GameServer *l_game	=g_gtsvr->gm_conn->find(l_map);

				LogLine l_line(g_gatelog);
				if (l_game)
				{
					l_ply->game->m_plynum--;
					l_ply->game		=0;
					l_ply->gm_addr	=0;
					//l_line<<newln<<"客户端: "<<l_ply->m_datasock->GetPeerIP()<<":"<<l_ply->m_datasock->GetPeerPort()
					l_line<<newln<<"客户端: "<<l_ply->m_datasock->GetPeerIP()<<":"<<l_ply->m_datasock->GetPeerPort()
						//<<"	Switch到地图,Gate向["<<l_game->m_datasock->GetPeerIP()<<"]发送了EnterMap命令,dbid:"<<l_ply->m_dbid
						<<"	Switch到地图,Gate向["<<l_game->m_datasock->GetPeerIP()<<"]发送了EnterMap命令,dbid:"<<l_ply->m_dbid
						//<<uppercase<<hex<<",附带Gate地址:"<<MakeULong(l_ply)<<dec<<nouppercase<<endln;
						<<uppercase<<hex<<",附带Gate地址:"<<MakeULong(l_ply)<<dec<<nouppercase<<endln;
                    l_game->EnterMap(l_ply, l_ply->m_loginID,l_ply->m_dbid,l_ply->m_worldid, l_map, lMapCopyNO, l_x, l_y, 1,l_ply->m_sGarnerWiner);	//根据地图查找GameServer，然后请求GameServer以进入这个地图。
					l_game->m_plynum++;
				}else if(!l_return) //目标地图不可达，重新进入源地图
				{
					WPacket	l_wpk	=datasock->GetWPacket();
					l_wpk.WriteCmd(CMD_MC_SYSINFO);
					l_wpk.WriteString(dstring("[")<<l_map<<"]当前不可到达，请稍后再试！");
					//l_wpk.WriteString(dstring("[")<<l_map<<"] can't reach, pealse retry later!");
					l_ply->m_datasock->SendData(l_wpk);

					//l_line<<newln<<"客户端: "<<l_ply->m_datasock->GetPeerIP()<<":"<<l_ply->m_datasock->GetPeerPort()
					l_line<<newln<<"客户端: "<<l_ply->m_datasock->GetPeerIP()<<":"<<l_ply->m_datasock->GetPeerPort()
						//<<"	Switch回地图,Gate向["<<l_ply->game->m_datasock->GetPeerIP()<<"]发送了EnterMap命令,dbid:"<<l_ply->m_dbid
						<<"	Switch回地图,Gate向["<<l_ply->game->m_datasock->GetPeerIP()<<"]发送了EnterMap命令,dbid:"<<l_ply->m_dbid
						//<<uppercase<<hex<<",附带Gate地址:"<<MakeULong(l_ply)<<dec<<nouppercase<<endln;
						<<uppercase<<hex<<",附带Gate地址:"<<MakeULong(l_ply)<<dec<<nouppercase<<endln;
					l_ply->game->EnterMap(l_ply, l_ply->m_loginID,l_ply->m_dbid,l_ply->m_worldid, l_srcmap, lSrcMapCopyNO, l_srcx, l_srcy, 1,l_ply->m_sGarnerWiner);	//根据地图查找GameServer，然后请求GameServer以进入这个地图。
				}else
				{
					g_gtsvr->cli_conn->Disconnect(l_ply->m_datasock,0,-24);
				}

				//if(!l_game)						//目标地图不可达
				//{
				//	//char l_tmp[256];
				//	WPacket	l_wpk	=datasock->GetWPacket();
				//	l_wpk.WriteCmd(CMD_MC_SYSINFO);
				//	char l_sysinfo[256];
				//	strcpy(l_sysinfo,"[");
				//	strcat(l_sysinfo,l_map);
				//	strcat(l_sysinfo,"]当前不可到达，请稍后再试！");

				//	l_wpk.WriteString(l_sysinfo);
				//	l_ply->m_datasock->SendData(l_wpk);
				//}else if(l_game !=l_ply->game && l_game->m_plynum >1500)	//人数过多
				//{
				//	//char l_tmp[256];
				//	WPacket	l_wpk	=datasock->GetWPacket();
				//	l_wpk.WriteCmd(CMD_MC_SYSINFO);
				//	char l_sysinfo[256];
				//	strcpy(l_sysinfo,"[");
				//	strcat(l_sysinfo,l_map);
				//	strcat(l_sysinfo,"]所在服务器当前人数过多，请稍后再试！");

				//	l_wpk.WriteString(l_sysinfo);
				//	l_ply->m_datasock->SendData(l_wpk);
				//}else
				//{
				//	//char l_tmp[256];
				//	SwitchMap	*l_switch	=g_swmap.Get();
				//	l_switch->Init(l_ply,l_game,l_map,l_x,l_y);
				//	g_gtsvr->m_proc->AddTask(l_switch);
				//}
				break;
			}
		case CMD_MC_ENTERMAP:
			{
				RPacket	l_rpk		=recvbuf;
				uShort	l_aimnum	=l_rpk.ReverseReadShort();					//l_aimnum永远等于1

				Player	*l_ply	=(Player *)MakePointer(l_rpk.ReverseReadLong());
				uLong		l_dbid	=l_rpk.ReverseReadLong();
				LogLine l_line(g_gatelog);
				if(l_ply->m_dbid	!=l_dbid)					//chaid
				{
					//l_line<<newln<<"收到一个来自["<<datasock->GetPeerIP()<<"]的EnterMap命令,但和本地的DBID不一致：本地["<<l_ply->m_dbid<<"],远端["<<l_dbid<<"]"
					l_line<<newln<<"收到一个来自["<<datasock->GetPeerIP()<<"]的EnterMap命令,但和本地的DBID不一致：本地["<<l_ply->m_dbid<<"],远端["<<l_dbid<<"]"
						//<<uppercase<<hex<<",附带Gate地址:"<<MakeULong(l_ply)<<endln;
						<<uppercase<<hex<<",附带Gate地址:"<<MakeULong(l_ply)<<endln;
					return;
				}
				uShort	l_retcode	=l_rpk.ReadShort();
				if( l_retcode==ERR_SUCCESS)
				{
					l_ply->game			=l_game;
					l_ply->gm_addr		=l_rpk.ReverseReadLong();
					l_game->m_plynum	=l_rpk.ReverseReadLong();
					char	l_isSwitch	=l_rpk.ReverseReadChar();

					//l_line<<newln<<"客户端: "<<l_ply->m_datasock->GetPeerIP()<<":"<<l_ply->m_datasock->GetPeerPort()
					l_line<<newln<<"客户端: "<<l_ply->m_datasock->GetPeerIP()<<":"<<l_ply->m_datasock->GetPeerPort()
						//<<"	Gate收到了来自["<<datasock->GetPeerIP()<<"]成功EnterMap命令,附带的Game地址:"
						<<"	Gate收到了来自 ["<<datasock->GetPeerIP()<<"]成功EnterMap命令,附带的Game地址:"
						//<<uppercase<<hex<<l_ply->gm_addr<<",附带Gate地址:"<<MakeULong(l_ply)<<dec<<nouppercase<<endln;
						<<uppercase<<hex<<l_ply->gm_addr<<",附带Gate地址:"<<MakeULong(l_ply)<<dec<<nouppercase<<endln;

					recvbuf.DiscardLast(sizeof(uShort) + sizeof(uLong)*2*l_aimnum + sizeof(uLong)*2 +sizeof(uChar));

					l_ply->SendPacketToClient(recvbuf);

					/*
					if (l_ply->spectatorID == 0){
						g_gtsvr->cli_conn->SendData(l_ply->m_datasock, recvbuf);
						g_gtsvr->SendSpectatorPacket(l_ply, recvbuf);
					}*/
					{
						WPacket l_wpk	=GetWPacket();
						l_wpk.WriteCmd(CMD_MP_ENTERMAP);
						l_wpk.WriteChar(l_isSwitch);
						l_wpk.WriteLong(MakeULong(l_ply));
						l_wpk.WriteLong(l_ply->gp_addr);
						g_gtsvr->gp_conn->SendData(g_gtsvr->gp_conn->get_datasock(),l_wpk);

#ifdef CHAEXIT_ONTIME
						if( l_ply->m_exit != 0 )
						{
							WPacket l_wpk = datasock->GetWPacket();
							l_wpk.WriteCmd(CMD_TM_GOOUTMAP);
							l_wpk.WriteChar(1);
							l_wpk.WriteLong(MakeULong(l_ply));
							l_wpk.WriteLong(l_ply->gm_addr);			//附加GameServer上的地址
							g_gtsvr->gm_conn->SendData(l_game->m_datasock,l_wpk);
						}
#endif
					}
				}else
				{
					l_ply->m_status	=1;
					l_game->m_plynum--;
					//l_line<<newln<<"客户端: "<<l_ply->m_datasock->GetPeerIP()<<":"<<l_ply->m_datasock->GetPeerPort()
					l_line<<newln<<"客户端: "<<l_ply->m_datasock->GetPeerIP()<<":"<<l_ply->m_datasock->GetPeerPort()
						//<<"	Gate收到了来自["<<datasock->GetPeerIP()<<"]失败EnterMap命令,错误码:"
						<<"	Gate收到了来自 ["<<datasock->GetPeerIP()<<"]失败EnterMap命令,Error:"
						<<l_retcode<<endln;

					recvbuf.DiscardLast(sizeof(uShort) + sizeof(uLong)*2*l_aimnum);
					//g_gtsvr->cli_conn->SendData(l_ply->m_datasock,recvbuf);
					g_gtsvr->cli_conn->Disconnect(l_ply->m_datasock, 10, -33 );
				}
				break;
			}
#ifdef CHAEXIT_ONTIME
		case CMD_MC_STARTEXIT:
			{
				RPacket	l_rpk		=recvbuf;
				uShort	l_aimnum	=l_rpk.ReverseReadShort();					//l_aimnum永远等于1
				Player	*l_ply	=(Player *)MakePointer(l_rpk.ReverseReadLong());
				if( l_ply )
				{
					g_gtsvr->cli_conn->SendData(l_ply->m_datasock,recvbuf);
					//printf( "StartExit: id = %d\n", l_ply->m_actid );
				}
			}
			break;
		case CMD_MC_CANCELEXIT:
			{
				RPacket	l_rpk		=recvbuf;
				uShort	l_aimnum	=l_rpk.ReverseReadShort();					//l_aimnum永远等于1
				Player	*l_ply	=(Player *)MakePointer(l_rpk.ReverseReadLong());
				if( l_ply )
				{
					MutexArmor l_lockStat(l_ply->m_mtxstat);
					if( !l_ply->m_datasock->IsFree() && l_ply->m_exit != 3 )
					{
						l_ply->m_exit = 0;
						g_gtsvr->cli_conn->SendData(l_ply->m_datasock,recvbuf);
						//printf( "MC:CancelExit: id = %d\n", l_ply->m_actid );
						l_lockStat.unlock();
					}
				}
			}
			break;		
		case CMD_MT_PALYEREXIT:
			{
				uShort	l_aimnum	=recvbuf.ReverseReadShort();
				for(uShort i=0;i<l_aimnum;i++)
				{
					Player *l_ply	=(Player *)MakePointer(recvbuf.ReverseReadLong());
					if(l_ply && l_ply->m_dbid ==recvbuf.ReverseReadLong())
					{
						MutexArmor l_lockStat(l_ply->m_mtxstat);
						//printf( "PlayerExit id = %d, status = %d\n", l_ply->m_actid, l_ply->m_status );
						uLong	l_ulMilliseconds	=30*1000;
						if( l_ply->m_status == 2 && l_ply->m_exit == 1 ) // 选择角色
						{
							WPacket l_wpk = g_gtsvr->gp_conn->GetWPacket();
							l_wpk.WriteCmd(CMD_TP_ENDPLAY);
							l_wpk.WriteLong(MakeULong(l_ply));
							l_wpk.WriteLong(l_ply->gp_addr);
							l_wpk	=g_gtsvr->gp_conn->SyncCall(g_gtsvr->gp_conn->get_datasock(),l_wpk,l_ulMilliseconds);
							if(!l_wpk.HasData())
							{
								l_wpk	=datasock->GetWPacket();
								l_wpk.WriteCmd(CMD_MC_ENDPLAY);
								l_wpk.WriteShort(ERR_MC_NETEXCP);
								//SendData(datasock,l_wpk);
								g_gtsvr->cli_conn->SendData(l_ply->m_datasock,l_wpk);
							}else
							{
								//返回给Client
								l_wpk.WriteCmd(CMD_MC_ENDPLAY);
								//SendData(datasock,l_wpk);
								g_gtsvr->cli_conn->SendData(l_ply->m_datasock,l_wpk);
								l_ply->m_status	=1;//进入选角色画面状态
								l_ply->m_exit   =0;
								l_ply->m_dbid	=0;
								l_ply->m_worldid=0;
								if(RPacket(l_wpk).ReadShort() ==ERR_PT_KICKUSER)
								{
									Disconnect(l_ply->m_datasock,100,-25);
								}
							}
						}
						else if( l_ply->m_status == 2 && l_ply->m_exit == 2 ) // 登出释放资源
						{
							/*
							WPacket l_wpk = g_gtsvr->gp_conn->GetWPacket();
							l_wpk.WriteCmd( CMD_TP_PLAYEREXIT );
							l_wpk.WriteLong( l_ply->m_dbid );
							g_gtsvr->gp_conn->SendData( g_gtsvr->gp_conn->get_datasock(),l_wpk);
							*/
							WPacket l_wpk	=g_gtsvr->gp_conn->get_datasock()->GetWPacket();
							l_wpk.WriteCmd(CMD_TP_DISC);
							l_wpk.WriteLong(l_ply->m_actid);
							l_wpk.WriteLong(inet_addr(datasock->GetPeerIP()));
							l_wpk.WriteString(GetDisconnectErrText(datasock->GetDisconnectReason()?datasock->GetDisconnectReason():-27).c_str());
							g_gtsvr->gp_conn->SendData(g_gtsvr->gp_conn->get_datasock(),l_wpk);

							l_wpk	=g_gtsvr->gp_conn->get_datasock()->GetWPacket();
							l_wpk.WriteCmd(CMD_TP_USER_LOGOUT);
							l_wpk.WriteLong(MakeULong(l_ply));
							l_wpk.WriteLong(l_ply->gp_addr);
							l_ply->gp_addr	=0;
							RPacket l_retpk	=g_gtsvr->gp_conn->SyncCall(g_gtsvr->gp_conn->get_datasock(),l_wpk,l_ulMilliseconds);
							//printf( "PlayerExit 释放角色id = %d, status = %d\n", l_ply->m_actid, l_ply->m_status );
							g_gtsvr->cli_conn->Disconnect(l_ply->m_datasock,0,-23);	//－23错误码表示GameServer要求踢掉某人
							l_ply->Free();
						}
						l_lockStat.unlock();
					}
				}
				break;
			}
#endif
		case CMD_MT_KICKUSER:
			{
				uShort l_aimnum = recvbuf.ReverseReadShort();
				Player *l_ply = (Player *)MakePointer(recvbuf.ReverseReadLong());
				uLong b = recvbuf.ReverseReadLong();
				if(l_ply && l_ply->m_dbid == b)
				{
					g_gtsvr->cli_conn->Disconnect(l_ply->m_datasock,0,-23);
				}
				break;
			}
		case CMD_MT_MAPENTRY:
			{
				WPacket l_wpk0 = WPacket( recvbuf ).Duplicate();
				WPacket l_wpk = l_wpk0;

				RPacket	l_rpk = recvbuf;
				cChar	*l_map = l_rpk.ReadString();
				GameServer *l_game = g_gtsvr->gm_conn->find(l_map);			
				if( l_game )
				{
					l_wpk.WriteCmd( CMD_TM_MAPENTRY );
					g_gtsvr->gm_conn->SendData(l_game->m_datasock,l_wpk);
				}
				else
				{
					l_wpk.WriteCmd( CMD_TM_MAPENTRY_NOMAP );
					g_gtsvr->gm_conn->SendData(datasock,l_wpk);
				}
			}
			break;
		default:		// 缺省转发
			{
				if(l_cmd/500 == CMD_MC_BASE/500)
				{
					RPacket	l_rpk		=recvbuf;
					uShort	l_aimnum	=l_rpk.ReverseReadShort();
					recvbuf.DiscardLast(sizeof(uLong)*2*l_aimnum + sizeof(uShort));
					for(uShort i=0;i<l_aimnum;i++)
					{
						Player *l_ply	=(Player *)MakePointer(l_rpk.ReverseReadLong());
						if(l_ply->m_dbid ==l_rpk.ReverseReadLong())
						{
							l_ply->SendPacketToClient(recvbuf);
						//	l_ply->SendPacketToClient(l_rpk);
							/*
							if (l_ply->spectatorID == 0){
								g_gtsvr->cli_conn->SendData(l_ply->m_datasock, recvbuf);
								g_gtsvr->SendSpectatorPacket(l_ply, recvbuf);
							}
							*/
							


						}
					}
				}else if(l_cmd/500 == CMD_MP_BASE/500)
				{
					RPacket l_rpk		=recvbuf;
					uShort	l_aimnum	=l_rpk.ReverseReadShort();
					recvbuf.DiscardLast(sizeof(uLong)*2*l_aimnum + sizeof(uShort));
					if( l_aimnum > 0 )
					{
						WPacket l_wpk,l_wpk0 =WPacket(recvbuf).Duplicate();
						for(uShort i=0;i<l_aimnum;i++)
						{
							Player *l_ply	=(Player *)MakePointer(l_rpk.ReverseReadLong());
							if(l_ply->m_dbid ==l_rpk.ReverseReadLong())
							{
								l_wpk			=l_wpk0;
								l_wpk.WriteLong(MakeULong(l_ply));
								l_wpk.WriteLong(l_ply->gp_addr);
								g_gtsvr->gp_conn->SendData(g_gtsvr->gp_conn->get_datasock(),l_wpk);
							}
						}
					}
					else
					{
						WPacket l_wpk =WPacket(recvbuf).Duplicate();
						g_gtsvr->gp_conn->SendData(g_gtsvr->gp_conn->get_datasock(),l_wpk);
					}
				}else if(l_cmd/500 ==CMD_MM_BASE/500)
				{
					for(GameServer *l_game =_game_list;l_game;l_game =l_game ->next)
					{
						g_gtsvr->gm_conn->SendData(l_game->m_datasock,recvbuf);
					}
				}
				break;
			}
		}
	}
	catch(...)
	{
		LG("ToGameServerError", "l_cmd = %d\n", l_cmd);
	}
	//LG("ToGameServer", "<--l_cmd = %d\n", l_cmd);
}

void ToGameServer::MT_LOGIN(DataSocket* datasock, RPacket& rpk)
{
	cChar* gms_name = rpk.ReadString();
	cChar* map_list = rpk.ReadString();
	GameServer* gms = _game_heap.Get();
	WPacket retpk = GetWPacket();
	bool valid = true;
	int i;

	retpk.WriteCmd(CMD_TM_LOGIN_ACK);
	int cnt = Util_ResolveTextLine(map_list, gms->maplist, MAX_MAP, ';', 0);
	LogLine l_line(g_gatelog);
	l_line<<newln<<"收到GameServer ["<<gms_name<<"] 地图串["<<map_list<<"] 共["<<cnt<<"]个"<<endln;
	//l_line<<newln<<"收到GameServer ["<<gms_name<<"] 地图串 ["<<map_list<<"] 共 ["<<cnt<<"]个"<<endln;
	if (cnt <= 0)
	{ // MAP串语法有错
		l_line<<newln<<"地图串 ["<<map_list<<"] 存在语法错误，请以';'分隔"<<endln;
		//l_line<<newln<<"地图串 ["<<map_list<<"] 存在语法错误，请以 ';'分隔"<<endln;
		retpk.WriteShort(ERR_TM_MAPERR);
		datasock->SetPointer(NULL);
		gms->Free();
	}else
	{
		gms->gamename = gms_name;
		gms->mapcnt = cnt;

		_mut_game.lock();
		try
		{
			do
			{ // 首先检查 GameServer 名字是否已注册
				if (_exist_game(gms_name))
				{
					l_line<<newln<<"存在同名的GameServer: "<<gms_name<<endln;
					//l_line<<newln<<"the same name GameServer exsit: "<<gms_name<<endln;
					retpk.WriteShort(ERR_TM_OVERNAME);
					datasock->SetPointer(NULL);
					valid = false; break;
				}

				// 其次检查地图名是否会有重复的
				for (i = 0; i < cnt; ++ i)
				{
					if (find(gms->maplist[i].c_str()) != NULL)
					{
						l_line<<newln<<"存在同名的MAP: "<<gms->maplist[i].c_str()<<endln;
						//l_line<<newln<<"the same name MAP exsit: "<<gms->maplist[i].c_str()<<endln;
						retpk.WriteShort(ERR_TM_OVERMAP);
						datasock->SetPointer(NULL);
						valid = false;
						break;
					}
				}
			} while (false);

			if (valid)
			{ // 合法的 GameServer， 加入到表中
				_add_game(gms); // 添加到链表中
				l_line<<newln<<"添加GameServer ["<<gms_name<<"] 成功"<<endln;
				//l_line<<newln<<"add GameServer ["<<gms_name<<"] ok"<<endln;
				for (i = 0; i < cnt; ++ i) // 添加到 map 中
				{
					l_line<<newln<<"添加 ["<<gms_name<<"] 上的 ["<<gms->maplist[i].c_str()<<"] 地图成功"<<endln;
					//l_line<<newln<<"add ["<<gms_name<<"]  ["<<gms->maplist[i].c_str()<<"] map ok"<<endln;
					_map_game[gms->maplist[i]] = gms;
				}

				datasock->SetPointer(gms);
				gms->m_datasock	= datasock;
				retpk.WriteShort(ERR_SUCCESS);
				retpk.WriteString(g_gtsvr->gp_conn->_myself.c_str());
			}else
			{ // 非法的 GateServer
				gms->Free();
			}
		}
		catch (...)
		{
			l_line<<newln<<"Exception raised from MT_LOGIN{添加地图}"<<endln;
			//l_line<<newln<<"Exception raised from MT_LOGIN{add map}"<<endln;
		}
		_mut_game.unlock();

		//if (!valid) Disconnect(datasock);
	}

	SendData(datasock, retpk);
}

GameServer* ToGameServer::find(cChar* mapname)
{
	map<string, GameServer*>::iterator it = _map_game.find(mapname);
	if (it == _map_game.end())
	{
		LogLine l_line(g_gatelog);
		l_line<<newln<<"未找到 ["<<mapname<<"] 地图！！！";
		//l_line<<newln<<"not found ["<<mapname<<"] map!!!";
		return NULL;
	}else
		return (*it).second;
}

void GameServer::Initially()
{
	m_plynum	=0;
	gamename = ""; ip = ""; port = 0;
	m_datasock = NULL; next = NULL;
	mapcnt = 0;
}

void GameServer::Finally()
{
	m_plynum	=0;
	gamename = ""; ip = ""; port = 0;
	m_datasock = NULL; next = NULL;
	mapcnt = 0;
}

void GameServer::EnterMap(Player *ply,uLong actid, uLong dbid,uLong worldid,cChar *map, Long lMapCpyNO,uLong x,uLong y,char entertype,short swiner)
{
	WPacket l_wpk	=m_datasock->GetWPacket();
	l_wpk.WriteCmd(CMD_TM_ENTERMAP);
    l_wpk.WriteLong(actid);
	l_wpk.WriteString(ply->m_password);
	l_wpk.WriteLong(dbid);
	l_wpk.WriteLong(worldid);
	l_wpk.WriteString(map);
	l_wpk.WriteLong(lMapCpyNO);
	l_wpk.WriteLong(x);
	l_wpk.WriteLong(y);
	l_wpk.WriteChar(entertype);
	l_wpk.WriteLong(MakeULong(ply));		//第一次附加上自己的地址
	l_wpk.WriteShort(swiner);
	g_gtsvr->gm_conn->SendData(m_datasock,l_wpk);
	ply->SetMapName(map); // Chaos Blind
}
