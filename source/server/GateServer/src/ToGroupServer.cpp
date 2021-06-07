
#include "gateserver.h"
dbc::cuShort g_version =103;

long ConnectGroupServer::Process()
{
	T_B
	_tgps->m_calltotal++;

	DataSocket* datasock = NULL;
	while (!GetExitFlag() && !_tgps->m_atexit)
	{        
		if (_tgps->_connected)
		{
			// Add by lark.li 2008119 begin
			if(_tgps->IsSync() && g_gtsvr)
			{
				Player	*l_ply	=0;
				RunChainGetArmor<Player> l(g_gtsvr->m_plylst);
				WPacket pk = _tgps->GetWPacket();
				pk.WriteCmd(CMD_TP_SYNC_PLYLST);

				int ply_cnt = g_gtsvr->m_plylst.GetTotal();		//总数
				pk.WriteLong(ply_cnt);
				pk.WriteString(_tgps->_myself.c_str());			//gateserver的名字
				Player** ply_array = new Player*[ply_cnt];

				int i = 0;
				for(l_ply =g_gtsvr->m_plylst.GetNextItem();l_ply;l_ply =g_gtsvr->m_plylst.GetNextItem())
				{
					uLong test = MakeULong(l_ply);
					pk.WriteLong(MakeULong(l_ply)); // 附加上在GateServer上的内存地址
					pk.WriteLong(l_ply->m_loginID);
					pk.WriteLong(l_ply->m_actid);

					ply_array[i++] = l_ply;
				}

				RPacket retpk = _tgps->SyncCall(_tgps->get_datasock(), pk);
				int err = retpk.ReadShort();

				if (!retpk.HasData() || err == ERR_PT_LOGFAIL)
				{
					Sleep(5000);
					_tgps->Disconnect(_tgps->get_datasock());
					// 失败了
				}
				else
				{
					int num = retpk.ReadShort();

					if(num != ply_cnt)
					{
						Sleep(5000);
						_tgps->Disconnect(_tgps->get_datasock());
						// 失败了
					}
					else
					{
						for(int i =0;i<num;i++)
						{
							if(retpk.ReadShort() == 1)
							{
								uLong test = retpk.ReadLong();;
								ply_array[i]->gp_addr = test;
							}
						}
					}

					_tgps->SetSync(false);
				}

				delete[] ply_array;

			}
			// End

			// 已经连接上
			Sleep(1000);
		}else
		{
			// 未连接或连接断掉，重新连!
			LogLine l_line(g_gateconnect);
			//l_line<<newln<<"连接GroupServer开始..."<<endln;
			l_line<<newln<<RES_STRING(GS_TOGROUPSERVER_CPP_00001)<<endln;
			datasock = _tgps->Connect(_tgps->_gs.ip.c_str(), _tgps->_gs.port);
			if (datasock == NULL)
			{
				LogLine l_line(g_gateconnect);
				//l_line<<newln<<"连接GroupServer失败，等待5秒后自动重连..."<<endln;
				l_line<<newln<<RES_STRING(GS_TOGROUPSERVER_CPP_00002)<<endln;
				Sleep(5000);
				continue;
			}else
			{
				// 登录到 GroupServer
				WPacket pk = _tgps->GetWPacket();
				pk.WriteCmd(CMD_TP_LOGIN);
				pk.WriteShort(g_version);
				pk.WriteString(_tgps->_myself.c_str());

				RPacket retpk = _tgps->SyncCall(datasock, pk);
				int err = retpk.ReadShort();
				if (!retpk.HasData() || err == ERR_PT_LOGFAIL)
				{
					LogLine l_line(g_gateconnect);
					//l_line<<newln<<"登录GroupServer失败，可能是GateServer数量太多,等待5秒钟后自动重连..."<<endln;
					l_line<<newln<<RES_STRING(GS_TOGROUPSERVER_CPP_00003)<<endln;
					datasock = NULL;
					Sleep(5000);
					_tgps->Disconnect(datasock);
				}else
				{
					LogLine l_line(g_gateconnect);
					//l_line<<newln<<"登录GroupServer成功!"<<endln;
					l_line<<newln<<RES_STRING(GS_TOGROUPSERVER_CPP_00004)<<endln;
					_tgps->_gs.datasock = datasock;
					_tgps->_connected = true;

					// Add by lark.li 20081119 begin
					_tgps->SetSync();
					// End

					datasock = NULL;
				}
			}
		}
	}

	T_FINAL

	return 0;
}
Task	*ConnectGroupServer::Lastly()
{
	--(_tgps->m_calltotal);
	return Task::Lastly();
}

ToGroupServer::ToGroupServer(char const* fname, ThreadPool* proc, ThreadPool* comm)
: TcpClientApp(this, proc, comm), RPCMGR(this), _gs(), _connected(false),m_atexit(0),m_calltotal(0),
_myself()
{
	IniFile inf(fname);
	IniSection& is = inf["GroupServer"];
	_myself = inf["Main"]["Name"];
	_gs.ip = is["IP"];
	_gs.port = atoi(is["Port"]);

	// 启动 PING 线程

	SetPKParse(0, 2, 64 * 1024, 400);
	BeginWork(atoi(is["EnablePing"]));

	//++m_calltotal;
	//proc->AddTask(new ConnectGroupServer(this));
}

ToGroupServer::~ToGroupServer()
{
	m_atexit	=1;
	while(m_calltotal)
	{
		Sleep(1);
	}
	ShutDown(12 * 1000);
}

bool ToGroupServer::OnConnect(DataSocket* datasock) //返回值:true-允许连接,false-不允许连接
{
	datasock->SetRecvBuf(64 * 1024);
	datasock->SetSendBuf(64 * 1024);
	LogLine l_line(g_gateconnect);
	l_line<<newln<<"连接上GroupServer: "<<datasock->GetPeerIP()<<",Socket数目:"<<GetSockTotal()+1;
	//l_line<<newln<<"connect GroupServer: "<<datasock->GetPeerIP()<<",Socket num:"<<GetSockTotal()+1;
	return true;
}

void ToGroupServer::OnDisconnect(DataSocket* datasock, int reason) //reason值:0-本地程序正常退出；-3-网络被对方关闭；-1-Socket错误;-5-包长度超过限制。
{ // 激活 ConnnectGroupServer 线程
	LogLine l_line(g_gateconnect);
	l_line<<newln<<"与GroupServer的网络连接中断,Socket数目: "<<GetSockTotal()<<",reason ="<<GetDisconnectErrText(reason).c_str()<<"，立即重连..."<<endln;
	//l_line<<newln<<"disconnection with GroupServer,Socket num: "<<GetSockTotal()<<",reason ="<<GetDisconnectErrText(reason).c_str()<<", reconnecting..."<<endln;

	if (!g_appexit) {_connected = false;}
}

WPacket ToGroupServer::OnServeCall(DataSocket* datasock, RPacket &in_para)
{
	uShort l_cmd = in_para.ReadCmd();
	WPacket retpk = GetWPacket();

	switch (l_cmd)
	{
	case 0:
	default:
		break;
	}

	return retpk;
}

void ToGroupServer::OnProcessData(DataSocket* datasock, RPacket &recvbuf)
{
	uShort	l_cmd	=recvbuf.ReadCmd();
	//LG("ToGroupServer", "-->l_cmd = %d\n", l_cmd);
	try
	{
		printf("===================To GroupServer===========================\n");
		printf("packet: %d\n", l_cmd);
		printf("buffer size: %d\n", recvbuf.Size());
		printf("packet data len: %d\n", recvbuf.GetDataLen());
		printf("packet pkt len: %d\n", recvbuf.GetPktLen());
		printf("packet content: %s\n", (char*)recvbuf.GetBuffer());
		
		switch(l_cmd)
		{
		//case CMD_PM_GARNER2_UPDATE:
		//	{
		//		//忽略CMD_PM_GARNER2_UPDATE消息
		//	}
		//	break;
		case CMD_PM_GUILDCIRCLECOLOUR:
		case CMD_MM_DO_STRING:{
			for (GameServer *l_game = g_gtsvr->gm_conn->_game_list; l_game; l_game = l_game->next){
				g_gtsvr->gm_conn->SendData(l_game->m_datasock, recvbuf);
			}
			break;
		}
		case CMD_PM_PM2DISCORD:
		case CMD_PM_PMNOTONLINE:{
			GameServer* discord = g_gtsvr->gm_conn->find("Discord");
			if (discord){
				discord->m_datasock->SendData(WPacket(recvbuf));
			}
			break;
		}

		case CMD_PM_TEAM:
			{
				for(GameServer *l_game =g_gtsvr->gm_conn->_game_list;l_game;l_game =l_game->next)
				{
					g_gtsvr->gm_conn->SendData(l_game->m_datasock,recvbuf);
				}
#if 0
				WPacket l_wpk	=WPacket(recvbuf).Duplicate();
				recvbuf.ReadChar();
				char	l_count	=recvbuf.ReadChar();

				for(int i=0;i<l_count;i++)
				{
					if(_myself !=recvbuf.ReadString())
					{
						recvbuf.ReadLong();
						recvbuf.ReadLong();
					}else
					{
						Player * l_ply =reinterpret_cast<Player *>(MakePointer(recvbuf.ReadLong()));
						if(recvbuf.ReadLong() ==l_ply->m_worldid)
						{
							WPacket l_wpk1	=l_wpk;
							l_wpk1.WriteLong(MakeULong(l_ply));
							l_wpk1.WriteLong(l_ply->gm_addr);
							l_ply->game->m_datasock->SendData(l_wpk1);
						}
					}
				}
#endif
				break;
			}
		case CMD_AP_KICKUSER:
#ifdef CHAEXIT_ONTIME
			{
				uShort	l_aimnum	=recvbuf.ReverseReadShort();
				Player *l_ply		=(Player *)MakePointer(recvbuf.ReverseReadLong());
				//printf( "踢掉此人，帐号服务器因为有重复登陆。%d\n", l_ply->m_actid );
				if(l_ply && l_ply->gp_addr ==recvbuf.ReverseReadLong())
				{
					LogLine l_line(g_gatelog);
					//l_line<<newln<<"收到GroupServer的T人包并且T掉,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
					l_line<<newln<<"收到GroupServer的T人包并且T掉,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
					g_gtsvr->cli_conn->Disconnect(l_ply->m_datasock,0,-21);
				}else if(l_ply)
				{
					LogLine l_line(g_gatelog);
					//l_line<<newln<<"收到GroupServer的T人包但没T掉,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
					l_line<<newln<<"收到GroupServer的T人包但没T掉,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
				}			
				break;
			}
#endif
		case CMD_PT_KICKUSER:
			{
				uShort	l_aimnum	=recvbuf.ReverseReadShort();
				Player *l_ply		=(Player *)MakePointer(recvbuf.ReverseReadLong());
				if(l_ply && l_ply->gp_addr ==recvbuf.ReverseReadLong())
				{
					LogLine l_line(g_gatelog);
					//l_line<<newln<<"收到GroupServer的T人包并且T掉,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
					l_line<<newln<<"收到GroupServer的T人包并且T掉,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
					g_gtsvr->cli_conn->Disconnect(l_ply->m_datasock,0,-21);
				}else if(l_ply)
				{
					LogLine l_line(g_gatelog);
					//l_line<<newln<<"收到GroupServer的T人包但没T掉,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
					l_line<<newln<<"GroupServer 踢人, but can't kick person,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
				}
				break;
			}
		case CMD_PT_DEL_ESTOPUSER:
			{
				//printf( "CMD_PT_DEL_ESTOPUSER" );
				uShort	l_aimnum	=recvbuf.ReverseReadShort();
				Player *l_ply		=(Player *)MakePointer(recvbuf.ReverseReadLong());
				if(l_ply && l_ply->gp_addr ==recvbuf.ReverseReadLong())
				{
					LogLine l_line(g_gatelog);
					l_line<<newln<<"收到GroupServer的解除禁言包，操作成功,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
					//l_line<<newln<<"GroupServer del estop user,operator success,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
					l_ply->m_estop = false;
				}
				else if(l_ply)
				{
					LogLine l_line(g_gatelog);
					l_line<<newln<<"收到GroupServer的解除禁言包但没解掉,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
					//l_line<<newln<<"GroupServer del estop user, but can't operator success,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
				}
			}
			break;
		case CMD_PT_ESTOPUSER:
			{
				//printf( "CMD_PT_ESTOPUSER" );
				uShort	l_aimnum	=recvbuf.ReverseReadShort();
				Player *l_ply		=(Player *)MakePointer(recvbuf.ReverseReadLong());
				if(l_ply && l_ply->gp_addr ==recvbuf.ReverseReadLong())
				{
					LogLine l_line(g_gatelog);
					l_line<<newln<<"收到GroupServer的禁言包，操作成功,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
					//l_line<<newln<<"GroupServer del estop user,operator success,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
					l_ply->m_estop = true;
				}
				else if(l_ply)
				{
					LogLine l_line(g_gatelog);
					l_line<<newln<<"收到GroupServer的禁言包但没禁掉,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
					//l_line<<newln<<"GroupServer del estop user, but can't operator success,l_ply->m_dbid ="<<l_ply->m_dbid<<endln;
				}
			}
			break;
		case CMD_MC_SYSINFO:
			l_cmd	=CMD_PC_BASE;
		default:	//缺省转发
			{
				if(l_cmd/500 == CMD_PC_BASE/500)
				{
					RPacket	l_rpk		=recvbuf;
					uShort	l_aimnum	=l_rpk.ReverseReadShort();
					recvbuf.DiscardLast(sizeof(uLong)*2*l_aimnum + sizeof(uShort));
					Player *l_ply		=0;
					for(uShort i=0;i<l_aimnum;i++)
					{
						l_ply	=(Player *)MakePointer(l_rpk.ReverseReadLong());
						if(l_ply->gp_addr ==l_rpk.ReverseReadLong())
						{
							l_ply->SendPacketToClient(recvbuf);
							/*
							if (l_ply->spectatorID == 0){
								g_gtsvr->cli_conn->SendData(l_ply->m_datasock, recvbuf);
								g_gtsvr->SendSpectatorPacket(l_ply, recvbuf);
							}*/
						}else
						{
							l_ply		=0;
						}
					}
					if(l_cmd == CMD_PC_CHANGE_PERSONINFO && l_ply)
					{
						WPacket	l_wpk	=recvbuf;
						l_wpk.WriteCmd(CMD_TM_CHANGE_PERSONINFO);
						l_wpk.WriteLong(MakeULong(l_ply));
						l_wpk.WriteLong(l_ply->gm_addr);	//附加上在GameServer上的内存地址
						g_gtsvr->gm_conn->SendData(l_ply->game->m_datasock ,l_wpk);
						break;
					}
					if(l_cmd == CMD_PC_PING && l_ply)
					{
						l_ply->m_pingtime	=GetTickCount();
						break;
					}
				}else if(l_cmd/500 == CMD_PM_BASE/500)
				{
					RPacket	l_rpk		=recvbuf;
					uShort	l_aimnum	=l_rpk.ReverseReadShort();
					recvbuf.DiscardLast(sizeof(uLong)*2*l_aimnum + sizeof(uShort));
					if(!l_aimnum)
					{
						WPacket	l_wpk	=WPacket(recvbuf).Duplicate();
						l_wpk.WriteLong(0);
						for(GameServer *l_game =g_gtsvr->gm_conn->_game_list;l_game;l_game =l_game ->next)
						{
							g_gtsvr->gm_conn->SendData(l_game->m_datasock,l_wpk);
						}
					}else
					{
						WPacket l_wpk,l_wpk0 =WPacket(recvbuf).Duplicate();
						for(uShort i=0;i<l_aimnum;i++)
						{
							Player *l_ply	=(Player *)MakePointer(l_rpk.ReverseReadLong());
							if(l_ply->gp_addr ==l_rpk.ReverseReadLong() && l_ply->game)
							{
								l_wpk =l_wpk0;
								l_wpk.WriteLong(MakeULong(l_ply));
								l_wpk.WriteLong(l_ply->gm_addr);
								g_gtsvr->gm_conn->SendData(l_ply->game->m_datasock ,l_wpk);
							}
						}
					}
				}
				break;
			}
		}
	}
	catch(...)
	{
		LG("ToGroupServerError", "l_cmd = %d\n", l_cmd);
	}
	//LG("ToGroupServer", "<--l_cmd = %d\n", l_cmd);
}

// 从 GroupServer 上得到所有用户列表
RPacket ToGroupServer::get_playerlist()
{
	WPacket pk = GetWPacket();
	pk.WriteCmd(CMD_TP_REQPLYLST);

	return SyncCall(_gs.datasock, pk);
}
