#include "StdAfx.h"
#include "uiLotteryform.h"
#include "uiformmgr.h"
#include "uiform.h"
#include "uilabel.h"
#include "uimemo.h"
#include "uitextbutton.h"
#include "scene.h"
#include "uiitemcommand.h"
#include "uifastcommand.h"
#include "forgerecord.h"
#include "gameapp.h"
#include "uigoodsgrid.h"
#include "uiequipform.h"
#include "packetcmd.h"
#include "character.h"
#include "UIBoxform.h"
#include "packetCmd.h"
#include "StoneSet.h"
#include "GameApp.h"
#include "UIProgressBar.h"
#include "WorldScene.h"
#include "UIList.h"
#include "StringLib.h"

using namespace GUI;

static int         g_nForgeIndex  =-1;

//---------------------------------------------------------------------------
// class CLotteryMgr
//---------------------------------------------------------------------------
bool CLotteryMgr::Init()
{
	CFormMgr &mgr = CFormMgr::s_Mgr;
	//初始化npc对话表单
	frmNPCLottery  = mgr.Find("frmNPCLottery" );
	if ( !frmNPCLottery )
	{	
		LG("gui", RES_STRING(CL_LANGUAGE_MATCH_560));
		return false;
	}

	frmNPCLottery->evtEntrustMouseEvent = _MainMouseEvent;
	frmNPCLottery->evtClose = _OnClose;

	// 装备栏
	char szBuf[32];
	for (int i(0); i<ITEM_NUM; i++)
	{
		_snprintf_s( szBuf, _countof( szBuf ), _TRUNCATE,  "cmdNoItem%d", i);
		cmdNoItem[i] = dynamic_cast<COneCommand*>(frmNPCLottery->Find(szBuf));
		
		if( cmdNoItem[i]->GetDrag() )
		{
			cmdNoItem[i]->GetDrag()->evtMouseDragBegin = _DragBeforeEvt;
		}

		if (!cmdNoItem[i]) 
			return Error(RES_STRING(CL_LANGUAGE_MATCH_561), frmNPCLottery->GetName(), szBuf);
	}
	cmdNoItem[IITEM_NO1]->evtBeforeAccept = _DragEvtNo1;
	cmdNoItem[IITEM_NO2]->evtBeforeAccept = _DragEvtNo2;
	cmdNoItem[IITEM_NO3]->evtBeforeAccept = _DragEvtNo3;
	cmdNoItem[IITEM_NO4]->evtBeforeAccept = _DragEvtNo4;
	cmdNoItem[IITEM_NO5]->evtBeforeAccept = _DragEvtNo5;
	cmdNoItem[IITEM_NO6]->evtBeforeAccept = _DragEvtNo6;

	cmdLotteryItem = dynamic_cast<COneCommand*>(frmNPCLottery->Find("cmdLotteryItem"));
	cmdLotteryItem->evtBeforeAccept = _DragEvtLottery;
	
	labLotteryIssue = dynamic_cast<CLabelEx*>(frmNPCLottery->Find("labLotteryIssue"));
	labLotteryID = dynamic_cast<CLabelEx*>(frmNPCLottery->Find("labLotteryID"));
	labLotteryDate = dynamic_cast<CLabelEx*>(frmNPCLottery->Find("labLotteryDate"));

	btnYes = dynamic_cast<CTextButton*>(frmNPCLottery->Find("btnLotteryYes"));
	if( !btnYes ) 
		return Error(RES_STRING(CL_LANGUAGE_MATCH_561), frmNPCLottery->GetName(), "btnLotteryYes");

	btnYes->SetIsEnabled(false); 
	return true;
}

//---------------------------------------------------------------------------
void CLotteryMgr::CloseForm()
{
}

//---------------------------------------------------------------------------
void CLotteryMgr::ShowLottery(bool bShow)
{
	Clear();

	if (bShow)
	{
		frmNPCLottery->SetPos(150, 150);
		frmNPCLottery->Reset();
		frmNPCLottery->Refresh();
		frmNPCLottery->Show();

		//同时打开玩家的装备栏
		int x = frmNPCLottery->GetX() + frmNPCLottery->GetWidth();
		int y = frmNPCLottery->GetY();
		g_stUIEquip.GetItemForm()->SetPos(x, y);
		g_stUIEquip.GetItemForm()->Refresh();

		if (!(m_isOldEquipFormShow = g_stUIEquip.GetItemForm()->GetIsShow()))
		{
			g_stUIEquip.GetItemForm()->Show();
		}
	}
	else
	{
		frmNPCLottery->Close();
		g_stUIEquip.GetItemForm()->SetIsShow(m_isOldEquipFormShow);
	}

	return;
}

//---------------------------------------------------------------------------
int  CLotteryMgr::GetForgeComIndex(COneCommand* oneCommand)
{
	for (int i(0); i<ITEM_NUM; i++)
		if (cmdNoItem[i] == oneCommand)
			return i;
	return -1;
}

//---------------------------------------------------------------------------
void CLotteryMgr::Clear()
{
	ClearUI();

	ClearItem();
}

//---------------------------------------------------------------------------
void CLotteryMgr::ClearUI()
{
	btnYes->SetIsEnabled(false);
}

//---------------------------------------------------------------------------
void CLotteryMgr::ClearItem()
{
	for (int i(0); i<ITEM_NUM; ++i)
	{
		PopItem(i);
	}

	PopLottery();
}

//---------------------------------------------------------------------------
bool CLotteryMgr::SendLotteryProtocol()
{
	stNetItemLotteryAsk kNetItemLotteryeAsk;
	
	kNetItemLotteryeAsk.SGroup[0].sCellNum = 1;		// 始终是1
	kNetItemLotteryeAsk.SGroup[0].pCell = new SLotteryCell::SCell[1];
	kNetItemLotteryeAsk.SGroup[0].pCell[0].sNum = 1;
	kNetItemLotteryeAsk.SGroup[0].pCell[0].sPosID = m_iLotteryPos;

	for (int i = 0; i<ITEM_NUM; ++i)
	{
		kNetItemLotteryeAsk.SGroup[i+1].sCellNum = 1;		// 始终是1
		kNetItemLotteryeAsk.SGroup[i+1].pCell = new SLotteryCell::SCell[1];
		kNetItemLotteryeAsk.SGroup[i+1].pCell[0].sNum = 1;
		kNetItemLotteryeAsk.SGroup[i+1].pCell[0].sPosID = m_iLotteryItemPos[i];
	}
	CS_ItemLotteryAsk(true, &kNetItemLotteryeAsk);

	// 不用删除，他放到SLotteryCell的析构函数里了
	/*
	for (int i = 0; i<ITEM_NUM; ++i)
	{
		delete[] kNetItemLotteryeAsk.SGroup[i].pCell;	
	}*/

	return true;

}

//---------------------------------------------------------------------------
void CLotteryMgr::LotterySuccess(long lChaID)
{
	if( !CGameApp::GetCurScene() ) return;

	CCharacter* pCha = CGameApp::GetCurScene()->SearchByID( lChaID );
	if( !pCha ) return;

	if( pCha->IsMainCha() )
		this->ShowLottery(false);
}

//---------------------------------------------------------------------------
void CLotteryMgr::LotteryFailed(long lChaID)
{
	if( !CGameApp::GetCurScene() ) return;

	CCharacter* pCha = CGameApp::GetCurScene()->SearchByID( lChaID );
	if( !pCha ) return;

	if( pCha->IsMainCha() )
		this->ShowLottery(false);
}

void CLotteryMgr::LotteryOther(long lChaID)
{
	this->ShowLottery(false);
}


//---------------------------------------------------------------------------
// Callback Function
//---------------------------------------------------------------------------
void CLotteryMgr::_MainMouseEvent(CCompent *pSender, int nMsgType, int x, int y, DWORD dwKey)
{
	string name = pSender->GetName();
	if( name=="btnClose"  || name == "btnLotteryNo" )  
	{ 
		return;
	}
	else if( name == g_stUILottery.btnYes->GetName() ) 
	{
		g_stUILottery.btnYes->SetIsEnabled(false);

		g_stUILottery.SendLotteryProtocol();
	}

	return;
}

//---------------------------------------------------------------------------
void CLotteryMgr::_DragEvtNo(int index, CGuiData *pSender,CCommandObj* pItem,bool& isAccept)
{
	if(g_stUILottery.m_iLotteryPos == NO_USE)
	{
		//g_pGameApp->MsgBox("请先选择彩票！");
		g_pGameApp->MsgBox(RES_STRING(CL_UILOTTERYFORM_CPP_00001));
		return;
	}

	if (!g_stUILottery.IsValidDragSource())
		return;

	CItemCommand* pItemCommand =  dynamic_cast<CItemCommand*>(pItem);
	if( !pItemCommand) return;
	if( !(pItemCommand->GetIsValid())) return;

	//Add by sunny.sun 20080612 for change ball
	//Begin
	CItemCommand* pItemChangeNo = (CItemCommand*)g_stUILottery.cmdNoItem[index]->GetCommand();
	if(pItemChangeNo)
	{
		//g_pGameApp->MsgBox("不可重新替换号码球！");
		g_pGameApp->MsgBox(RES_STRING(CL_UILOTTERYFORM_CPP_00003));
		return ;	
	}

	if (g_stUILottery.IsNo(*pItemCommand))
	{
		g_stUILottery.PushItem(index, *pItemCommand);
		g_stUILottery.SetLotteryUI();
	}
	else
	{
		//g_pGameApp->MsgBox("所选的不是号码球，请重新选择！");
		g_pGameApp->MsgBox(RES_STRING(CL_UILOTTERYFORM_CPP_00002));
	}
	CItemRecord* pItemRecord = pItemCommand->GetItemInfo();
	
	if( pItemRecord->lID == 5839  )
	{
		for(int i(0); i < ITEM_NUM ;i++)
		{	
			//CItemRecord* pItemRecord = pItemCommand->GetItemInfo();
			CItemCommand* pItemNo = (CItemCommand*)g_stUILottery.cmdNoItem[i]->GetCommand();
			if(pItemNo)
			{
				if( pItemNo->GetItemInfo()->lID == 5839)
				{	
					//g_pGameApp->MsgBox("只能放置一个X球！");
					g_pGameApp->MsgBox(RES_STRING(CL_UILOTTERYFORM_CPP_00004));
					return ;
				}
			}
		}
	}
	g_stUILottery.PushItem(index, *pItemCommand);
	g_stUILottery.SetLotteryUI();
	//End

	//

	//

	for (int i(0); i<ITEM_NUM; ++i)
	{
		if(g_stUILottery.m_iLotteryItemPos[i] == NO_USE)
			return;
	}

	g_stUILottery.btnYes->SetIsEnabled(true);
}

//---------------------------------------------------------------------------
void CLotteryMgr::_DragEvtNo1(CGuiData *pSender,CCommandObj* pItem,bool& isAccept)
{
	_DragEvtNo(IITEM_NO1, pSender, pItem, isAccept);
}

//---------------------------------------------------------------------------
void CLotteryMgr::_DragEvtNo2(CGuiData *pSender,CCommandObj* pItem,bool& isAccept)
{
	_DragEvtNo(IITEM_NO2, pSender, pItem, isAccept);
}

//---------------------------------------------------------------------------
void CLotteryMgr::_DragEvtNo3(CGuiData *pSender,CCommandObj* pItem,bool& isAccept)
{
	_DragEvtNo(IITEM_NO3, pSender, pItem, isAccept);
}

//---------------------------------------------------------------------------
void CLotteryMgr::_DragEvtNo4(CGuiData *pSender,CCommandObj* pItem,bool& isAccept)
{
	_DragEvtNo(IITEM_NO4, pSender, pItem, isAccept);
}

//---------------------------------------------------------------------------
void CLotteryMgr::_DragEvtNo5(CGuiData *pSender,CCommandObj* pItem,bool& isAccept)
{
	_DragEvtNo(IITEM_NO5, pSender, pItem, isAccept);
}

//---------------------------------------------------------------------------
void CLotteryMgr::_DragEvtNo6(CGuiData *pSender,CCommandObj* pItem,bool& isAccept)
{
	_DragEvtNo(IITEM_NO6, pSender, pItem, isAccept);
}

//---------------------------------------------------------------------------
void CLotteryMgr::_DragEvtLottery(CGuiData *pSender,CCommandObj* pItem,bool& isAccept)
{
	if (!g_stUILottery.IsValidDragSource())
		return;

	CItemCommand* pItemCommand =  dynamic_cast<CItemCommand*>(pItem);
	if( !pItemCommand) return;
	if( !(pItemCommand->GetIsValid())) return;

	if (g_stUILottery.IsLottery(*pItemCommand))
	{
		CItemRecord* pItemRecord = pItemCommand->GetItemInfo();
		SItemGrid* pItemGrid = &pItemCommand->GetData();

		if( (float((short)pItemGrid->sInstAttr[0][1]) / 1000) > 0)
		{	
			//g_pGameApp->MsgBox("此彩票已填过！");
			g_pGameApp->MsgBox(RES_STRING(CL_UILOTTERYFORM_CPP_00005));
			return;
		}
		g_stUILottery.PushLottery(*pItemCommand);
		g_stUILottery.SetLotteryUI();
	}
	else
	{
		//g_pGameApp->MsgBox("必需放置彩票！");
		g_pGameApp->MsgBox(RES_STRING(CL_UILOTTERYFORM_CPP_00006));
	}
	return;
}

//---------------------------------------------------------------------------
void CLotteryMgr::_evtConfirmEvent(CCompent *pSender, int nMsgType, int x, int y, DWORD dwKey)
{
	if (g_stUILottery.m_isConfirm = nMsgType != CForm::mrYes)
			CS_ItemLotteryAnswer( false );
}

//---------------------------------------------------------------------------
void CLotteryMgr::_OnClose(CForm* pForm, bool& IsClose)
{
	g_stUILottery.Clear();

	CS_ItemLotteryAsk(false);

}

void CLotteryMgr::_DragBeforeEvt(CGuiData *pSender, int x, int y, DWORD key)
{
	if( pSender->GetDrag() ) 
		pSender->GetDrag()->Reset();
}

//---------------------------------------------------------------------------
// Help Function
//---------------------------------------------------------------------------
bool CLotteryMgr::IsNo(CItemCommand& rItem)
{
	CItemRecord* pItemRecord = rItem.GetItemInfo();

	if (pItemRecord) 
		return pItemRecord->sType == NO_TYPE;

	return false;
}

bool CLotteryMgr::IsLottery(CItemCommand& rItem)
{
	CItemRecord* pItemRecord = rItem.GetItemInfo();

	if (pItemRecord) 
		return pItemRecord->sType == LOTTERY_TYPE;

	return false;
}

bool CLotteryMgr::IsValidDragSource()
{
	CGoodsGrid* pGood = dynamic_cast<CGoodsGrid*>(CDrag::GetParent());
	if( pGood == g_stUIEquip.GetGoodsGrid() ) return true;

	return false;
}


//---------------------------------------------------------------------------
void CLotteryMgr::PushItem(int iIndex, CItemCommand& rItem)
{
	// 记录Item在物品栏中的位置
	m_iLotteryItemPos[iIndex] = g_stUIEquip.GetGoodsGrid()->GetDragIndex();
	// 将Item相应的物品栏灰调
	rItem.SetIsValid(false);

	// 将创建的Item放入Cmd中，这里用new将会在PopItem()中删除
	CItemCommand* pItemCmd = new CItemCommand(rItem);
	pItemCmd->SetIsValid(true);
	cmdNoItem[iIndex]->AddCommand(pItemCmd);

	return;
}

void CLotteryMgr::PushLottery(CItemCommand& rItem)
{
	// 记录Item在物品栏中的位置
	m_iLotteryPos = g_stUIEquip.GetGoodsGrid()->GetDragIndex();
	// 将Item相应的物品栏灰调
	rItem.SetIsValid(false);

	// 将创建的Item放入Cmd中，这里用new将会在PopItem()中删除
	CItemCommand* pItemCmd = new CItemCommand(rItem);
	pItemCmd->SetIsValid(true);
	cmdLotteryItem->AddCommand(pItemCmd);

	return;
}

//---------------------------------------------------------------------------
void CLotteryMgr::PopItem(int iIndex)
{
	// 删除Cmd中的Item，该Item会在PushItem()中由new生成
	CItemCommand* pItemCommand = dynamic_cast<CItemCommand*>(cmdNoItem[iIndex]->GetCommand());

	if (pItemCommand)
		cmdNoItem[iIndex]->DelCommand();	// 该函数将删除delete Item

	// 将Item相应的物品栏灰调
	CCommandObj* pItem = g_stUIEquip.GetGoodsGrid()->GetItem(m_iLotteryItemPos[iIndex]);

	if (pItem)
	{
		pItem->SetIsValid(true);
	}

	// 记录Item在物品栏中的位置
	m_iLotteryItemPos[iIndex] = NO_USE;

	this->SetLotteryUI();

	return;
}

void CLotteryMgr::PopLottery()
{
	// 删除Cmd中的Item，该Item会在PushItem()中由new生成
	CItemCommand* pItemCommand = dynamic_cast<CItemCommand*>(cmdLotteryItem->GetCommand());

	if (pItemCommand)
		cmdLotteryItem->DelCommand();	// 该函数将删除delete Item

	// 将Item相应的物品栏灰调
	CCommandObj* pItem = g_stUIEquip.GetGoodsGrid()->GetItem(m_iLotteryPos);

	if (pItem)
	{
		pItem->SetIsValid(true);
	}

	// 记录Item在物品栏中的位置
	m_iLotteryPos = NO_USE;

	this->SetLotteryUI();

	return;
}



//---------------------------------------------------------------------------
void CLotteryMgr::SetLotteryUI()
{
	// 彩票期号：	XXX
	// 彩票ID：		服务器ID(XX)彩票期号(XXX)彩票序号(XXXXXX)
	// 彩票日期：	2008年05月15日 16点35分
	// 彩票号码：	1 2 3 4 5 X
	//

	CItemCommand* pItemCommand = dynamic_cast<CItemCommand*>(cmdLotteryItem->GetCommand());
	
	if (!pItemCommand)
		return;

	CItemRecord* pItemRecord = pItemCommand->GetItemInfo();
	
	if (!pItemRecord)
		return;

	SItemGrid* pItemGrid = &pItemCommand->GetData();

	if(!pItemGrid)
		return;

	int i = pItemGrid->sNum;
	
	///*
	//真红之剑      +5
	//插槽一      3级        红宝石     
	//插槽二      无         
	//插槽三     ——         ——
	//精炼加成    攻击+18    专注+79    闪避+99
	//附加加成     —— 
	//宝石效果     攻击+2      专注+1 
	//*/

	//char szBuf[64];
	//if (cmdForgeItem[EQUIP]->GetCommand())
	//{
	//	// 武器的描述
	//	CItemCommand* pItemCommand =  
	//		dynamic_cast<CItemCommand*>(cmdForgeItem[EQUIP]->GetCommand());
	//	if (!pItemCommand)
	//		return;
	//	CItemRecord* pItemRecord = pItemCommand->GetItemInfo();
	//	if (!pItemRecord)
	//		return;

	//	SItemForge rItemForgeInfo = pItemCommand->GetForgeInfo();

	//	string sEquipState("");
	//	// 武器名
	//	CItemRow* pItem = lstForgeItemState->GetItems()->GetItem(0);
	//	if (pItem)
	//	{
	//		sEquipState = pItemRecord->szName;
	//		sEquipState += "  +";
	//		sEquipState += itoa(rItemForgeInfo.nLevel,szBuf, 10);
	//		pItem->GetBegin()->SetString(sEquipState.c_str());
	//	}

	//	// 武器插槽一
	//	pItem = lstForgeItemState->GetItems()->GetItem(1);
	//	if (pItem)
	//	{
	//		sEquipState = RES_STRING(CL_LANGUAGE_MATCH_835);
	//		if (rItemForgeInfo.nHoleNum < 1)
	//			sEquipState += "--  --\n";
	//		else
	//		{
	//			if (rItemForgeInfo.nStoneNum < 1)
	//			{
	//				sEquipState += RES_STRING(CL_LANGUAGE_MATCH_836);
	//			}
	//			else
	//			{
	//				sEquipState += itoa(rItemForgeInfo.nStoneLevel[0], szBuf, 10);
	//				sEquipState += RES_STRING(CL_LANGUAGE_MATCH_837);
	//				sEquipState += rItemForgeInfo.pStoneInfo[0]->szDataName;
	//				sEquipState += "\n";
	//			}
	//		}
	//		pItem->GetBegin()->SetString(sEquipState.c_str());
	//	}

	//	// 武器插槽二
	//	pItem = lstForgeItemState->GetItems()->GetItem(2);
	//	if (pItem)
	//	{
	//		sEquipState = RES_STRING(CL_LANGUAGE_MATCH_838);
	//		if (rItemForgeInfo.nHoleNum < 2)
	//			sEquipState += "--  --\n";
	//		else
	//		{
	//			if (rItemForgeInfo.nStoneNum < 2)
	//			{
	//				sEquipState += RES_STRING(CL_LANGUAGE_MATCH_836);
	//			}
	//			else
	//			{
	//				sEquipState += itoa(rItemForgeInfo.nStoneLevel[1], szBuf, 10);
	//				sEquipState += RES_STRING(CL_LANGUAGE_MATCH_837);
	//				sEquipState += rItemForgeInfo.pStoneInfo[1]->szDataName;
	//				sEquipState += "\n";
	//			}
	//		}
	//		pItem->GetBegin()->SetString(sEquipState.c_str());
	//	}

	//	// 武器插槽三
	//	pItem = lstForgeItemState->GetItems()->GetItem(3);
	//	if (pItem)
	//	{
	//		sEquipState = RES_STRING(CL_LANGUAGE_MATCH_839);
	//		if (rItemForgeInfo.nHoleNum < 3)
	//			sEquipState += "--  --\n";
	//		else
	//		{
	//			if (rItemForgeInfo.nStoneNum < 3)
	//			{
	//				sEquipState += RES_STRING(CL_LANGUAGE_MATCH_836);
	//			}
	//			else
	//			{
	//				sEquipState += itoa(rItemForgeInfo.nStoneLevel[2], szBuf, 10);
	//				sEquipState += RES_STRING(CL_LANGUAGE_MATCH_837);
	//				sEquipState += rItemForgeInfo.pStoneInfo[2]->szDataName;
	//				sEquipState += "\n";
	//			}
	//		}
	//		pItem->GetBegin()->SetString(sEquipState.c_str());
	//	}

	//	// 武器精炼加成
	//	pItem = lstForgeItemState->GetItems()->GetItem(4);
	//	if (pItem)
	//	{
	//		sEquipState = RES_STRING(CL_LANGUAGE_MATCH_840);
	//		for (int i(0); i<rItemForgeInfo.nStoneNum; ++i)
	//		{
	//			sEquipState += rItemForgeInfo.szStoneHint[i];	
	//			sEquipState += "  ";
	//		}
	//		if (sEquipState == RES_STRING(CL_LANGUAGE_MATCH_840))
	//			sEquipState += "--";

	//		pItem->GetBegin()->SetString(sEquipState.c_str());
	//	}


	//	// 武器精炼加成
	//	pItem = lstForgeItemState->GetItems()->GetItem(5);
	//	if (pItem)
	//	{
	//		string sEquipState = RES_STRING(CL_LANGUAGE_MATCH_841);

	//		pItem->GetBegin()->SetString(sEquipState.c_str());
	//	}
	//}
	//else
	//{
	//	CItemRow* pItem;
	//	for (int i(0); i<6; ++i)
	//	{
	//		pItem = lstForgeItemState->GetItems()->GetItem(i);
	//		if (pItem)
	//			pItem->GetBegin()->SetString("");
	//	}

	//}

	////		宝石效果     攻击+2      专注+1 
	//if (!m_isMilling)
	//{
	//	if (cmdForgeItem[GEN_STONE]->GetCommand())
	//	{
	//		CItemCommand* pItemCommand =  
	//			dynamic_cast<CItemCommand*>(cmdForgeItem[GEN_STONE]->GetCommand());
	//		if (!pItemCommand)
	//			return;

	//		CItemRow* pItem;
	//		pItem = lstForgeItemState->GetItems()->GetItem(6);
	//		if (pItem)
	//		{
	//			string sEquipState = RES_STRING(CL_LANGUAGE_MATCH_842) + pItemCommand->GetStoneHint(1);
	//			pItem->GetBegin()->SetString(sEquipState.c_str());
	//		}
	//	}
	//	else
	//	{
	//		CItemRow* pItem;
	//		pItem = lstForgeItemState->GetItems()->GetItem(6);
	//		if (pItem)
	//		{
	//			pItem->GetBegin()->SetString("");
	//		}
	//	}



	//}
	//	// 其他UI设置

	//if (cmdForgeItem[EQUIP]->GetCommand() 
	//	&& cmdForgeItem[GEN_STONE]->GetCommand() 
	//	&& cmdForgeItem[FORGE_STONE]->GetCommand())
	//{
	//	labForgeGold->SetCaption(StringSplitNum(m_isMilling ? CalMillingMoney() : CalForgeMoney()));
	//	assert(btnYes);
	//	btnYes->SetIsEnabled(true);
	//}
	//else
	//{
	//	labForgeGold->SetCaption("");
	//	assert(btnYes);
	//	btnYes->SetIsEnabled(false);
	//}


}

//---------------------------------------------------------------------------
long CLotteryMgr::CalLotteryMoney()
{
	//CItemCommand* pItemCommand =  
	//			dynamic_cast<CItemCommand*>(cmdForgeItem[EQUIP]->GetCommand());

	//SItemForge rItemForgeInfo = pItemCommand->GetForgeInfo();
	//if (rItemForgeInfo.IsForge)
	//{
	//	return ((long)((rItemForgeInfo.nLevel + 1)) * FORGE_PER_LEVEL_MONEY);
	//}
	return 0;

}

