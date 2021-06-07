#include "StdAfx.h"
#include "uiAmphitheaterForm.h"
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
#include "packetcmd.h"
#include "character.h"
#include "UIBoxform.h"
#include "packetCmd.h"
#include "GameApp.h"
#include "UIProgressBar.h"
#include "WorldScene.h"
#include "UIList.h"
#include "StringLib.h"
#include "UIScroll.h"
#include "uiequipform.h"

using namespace GUI;
CAmphitheaterForm * CAmphitheaterForm::m_pStaticAmphiForm = NULL;
/////////////////////////////////////////////
//          竞技场排行榜数据
////////////////////////////////////////////
AmphitheaterData::AmphitheaterData()
{


}

AmphitheaterData::~AmphitheaterData()
{
	if(!TeamProList.empty())
		TeamProList.clear();
	if(!TeamRelList.empty())
		TeamRelList.clear();
}

void AmphitheaterData::AddTeamPro(const TeamProUnit * _tp )
{
	TeamProList.push_back(*_tp);
}

//添加元素
void AmphitheaterData::AddTeamRel(const TeamRelUnit * _tr )
{
	TeamRelList.push_back(*_tr);
}
//根据teamid删除晋级元素
void AmphitheaterData::DelTeamPro(int TeamID)
{
	std::vector<TeamProUnit>::iterator it = TeamProList.begin();
	for(;it!= TeamProList.end();)
	{
		if((*it).PromID == TeamID)
		{
			it =TeamProList.erase(it);
			continue;
		}
		it++;
	}
}
//根据teamid删除复活元素
void AmphitheaterData::DelTeamRel(int TeamID)
{
	std::vector<TeamRelUnit>::iterator it = TeamRelList.begin();
	for(;it!= TeamRelList.end();)
	{
		if((*it).RelID == TeamID)
		{
			it =TeamRelList.erase(it);
			continue;
		}
		it++;
	}

}
//清空元素
void AmphitheaterData::DelTeamProAll()
{
	if(!TeamProList.empty())
		TeamProList.clear();

}

void AmphitheaterData::DelTeamRelAll()
{
	if(!TeamRelList.empty())
		TeamRelList.clear();
}

//根据链表位置返回链表内容
TeamProUnit * AmphitheaterData::GetTeamPro(int index)
{
	std::vector<TeamProUnit>::iterator ProIt = TeamProList.begin();
	for(int i = 0 ;i < (int)TeamProList.size();i++)
	{
		if( i == index )
		{
			return &(*ProIt);
		}
		ProIt++;
	}
	return NULL;
}

//根据list位置获取复活信息
TeamRelUnit * AmphitheaterData::GetTeamRel(int index)
{

	std::vector<TeamRelUnit>::iterator RelIt = TeamRelList.begin();

	for(int i = 0 ;i< (int)TeamRelList.size();i++)
	{
		if( i == index )
		{
			return &(*RelIt);
		}
		RelIt++;
	}
	return NULL;
}

/////////////////////////////////////////////////////////////
//
//CAmphitheaterList
//
/////////////////////////////////////////////////////////////

CAmphitheaterList* CAmphitheaterList::g_pAmphiList = NULL;

CAmphitheaterList::CAmphitheaterList(CForm& frmOwn):CList(frmOwn),_ButtonLen(10)
{
	_buttonPip = new CTextButton(frmOwn);
	_buttonPip->SetIsShow(false);

	for(int i=0;i<_ButtonLen;i++)
	{
		_button[i] = NULL;
	}
	g_pAmphiList = this;
	_dwSelectColor = 0xffff0000;
}

CAmphitheaterList::CAmphitheaterList(const CAmphitheaterList&  p):CList(p)
{

	_buttonPip = dynamic_cast<CTextButton*>(p._buttonPip->Clone());
	for(int i=0;i<p._ButtonLen;i++)
		_button[i] = dynamic_cast<CTextButton*>(p._buttonPip->Clone());
	_dwSelectColor = 0xffff0000 ;

}
CAmphitheaterList& CAmphitheaterList::operator =(const CAmphitheaterList& p)
{
	return *this;
}


void CAmphitheaterList::Render()
{
	CList::Render();

	for(int i=0;i<_ButtonLen;i++)
	{
		if(_button[i]&&_button[i]->GetIsShow()) _button[i]->Render();
	}
}

//投票按钮处理
void CAmphitheaterList::SetMouseFun(MouseFUN pf)
{
	if(_buttonPip)
	{
		// 因为_buttonPip pos size 更新的比较迟，所以复制button在 这复制
		int nshow = GetItems()->GetCurShowCount();
		for(int i=0;i<_ButtonLen;i++)
		{
			if(!_button[i])
			{
				_button[i] =  dynamic_cast<CTextButton*>(_buttonPip->Clone());
				_button[i]->SetPos(_buttonPip->GetLeft(),_buttonPip->GetTop()+_nRowHeight*i);

				*_button[i]->GetImage() = *(_buttonPip->GetImage()); 
				if(i>nshow-1)
					_button[i]->SetIsShow(false);
				else
					_button[i]->SetIsShow(true);

				//事件处理提取到外面处理 SetMouseFun()
				//_button[i]->evtMouseClick = MouseClick;
				_button[i]->Refresh();
			}
			else
			{
				if( i>nshow-1 )
					_button[i]->SetIsShow(false);
				else
					_button[i]->SetIsShow(true);
			}
		}

	}

	if(_buttonPip)
	{
		for(int i=0;i<_ButtonLen;i++)
		{
			if(_button[i])
			{
				_button[i]->evtMouseClick = pf;
			}
		}
	}
}
bool CAmphitheaterList::MouseRun( int x, int y, DWORD key )
{

	bool _IsMouseIn = CList::MouseRun(x,y,key);
	if( InRect( x, y ) )
	{
		for(int i=0;i<_ButtonLen;i++)
		{
			if(_button[i])
			{
				if( _button[i]->MouseRun(x,y,key) )
					return true;
			}
		}
	}

	return _IsMouseIn;
}

//刷新链表
void CAmphitheaterList::Refresh()
{
	CList::Refresh();
	for(int i=0;i<_ButtonLen;i++)
	{
		if(_button[i] == NULL)
			return;
		_button[i]->Refresh();
	}

}

CAmphitheaterList::~CAmphitheaterList()
{

	for(int i=0;i<_ButtonLen;i++)
	{
		if(_button[i])
		{
			delete _button[i];
			_button[i] = NULL;
		}

	}
	delete _buttonPip;
}

//滚动时处理按钮的出现
bool CAmphitheaterList::MouseScroll( int nScroll )
{
	bool b = CList::MouseScroll(nScroll);

	int nshow =GetItems()->GetCurShowCount();
	
	for(int i=0;i<_ButtonLen;i++)
	{
		if(_button[i])
		{
			if(i>nshow-1)
			{
				_button[i]->SetIsShow(false);
			}else
			{
				_button[i]->SetIsShow(true);
			}
		}
	}
	return  b;	
}


//////////////////////////////////////////////////////////////////////////////////////////////////
//
// CAmphitheaterForm
//
//////////////////////////////////////////////////////////////////////////////////////////////////

//竞技场界面初始化
bool CAmphitheaterForm::Init()
{
	CForm *frmMain800 = _FindForm("frmMain800");

	frmNPCAmphitheater = _FindForm("frmNPCAmphitheater");

	if( !frmNPCAmphitheater ) return false;	

	m_pSecPromotionList = dynamic_cast<CAmphitheaterList*>( frmNPCAmphitheater->Find("SecPromotionList") );
	if(!m_pSecPromotionList) return false;


	m_pSecReliveList = dynamic_cast<CAmphitheaterList*>( frmNPCAmphitheater->Find("SecReliveList") );
	if(!m_pSecReliveList) return false;


	listPage = dynamic_cast<CPage*>(frmNPCAmphitheater->Find("pgeAmphitheater"));
	assert(listPage != NULL);
	listPage->evtSelectPage = _evtPageIndexChange;
	m_pStaticAmphiForm = this;

	return true;
}
//投票按钮响应
void CAmphitheaterForm::ListMouseRun(CGuiData *pSender, int x, int y, DWORD key)
{
	int ID = 6068;
	int IdNum = g_stUIEquip.GetItemCount(ID);
	if( IdNum <= 0 )
	{
		g_pGameApp->MsgBox( RES_STRING(CL_UIAMPHITHEATERFORM_CPP_00001) );
		return;
	}
	else
	{
		int i=0;
		for(;i<20;i++)
		{
			if(pSender == (CGuiData*)(m_pStaticAmphiForm->m_pSecReliveList->_button[i]))
			{
				CSelectItem* item =m_pStaticAmphiForm->m_pSecReliveList->GetItems()->GetSelect();
				int index = item->GetIndex(); 
				int ReID = 0;
				TeamRelUnit * data2 = m_pStaticAmphiForm->m_pAmphitheaterData.GetTeamRel(index);
				ReID = data2->RelID;
				int Relbattlo = data2->Ballot;
				CS_ItemAmphitheaterAsk(true,ReID);
				m_pStaticAmphiForm->m_pSecReliveList->GetItems()->Clear();
				m_pStaticAmphiForm->m_pSecReliveList->Refresh();
				break;
			}
		}
	}
}


void CAmphitheaterForm::CloseForm()
{
	frmNPCAmphitheater->Hide();
}

void CAmphitheaterForm::Clear()
{

}

void CAmphitheaterForm::LoadingCall()
{

}

//切换页面
void CAmphitheaterForm::_evtPageIndexChange(CGuiData *pSender)
{
	int index = g_stUIAmphitheater.listPage->GetIndex();
	if(index == 0) 
	{
		m_pStaticAmphiForm->m_pSecPromotionList->GetItems()->Clear() ;
		m_pStaticAmphiForm->m_pSecPromotionList->Refresh();
		m_pStaticAmphiForm->RefreshAmphitheaterData(0);
	}
	else if(index == 1)
	{
		m_pStaticAmphiForm->m_pSecReliveList->GetItems()->Clear() ;
		m_pStaticAmphiForm->m_pSecReliveList->Refresh();
		m_pStaticAmphiForm->RefreshAmphitheaterData(1);
	}
	g_stUIAmphitheater.ShowAmphitheaterFrom(true);
}

//排行榜显示
void CAmphitheaterForm::ShowAmphitheaterFrom(bool bShow)
{
	if(bShow)
	{
		m_pStaticAmphiForm->m_pSecPromotionList->GetItems()->Clear() ;
		m_pStaticAmphiForm->m_pSecPromotionList->Refresh();
		m_pStaticAmphiForm->RefreshAmphitheaterData(0);

		m_pStaticAmphiForm->m_pSecReliveList->GetItems()->Clear() ;
		m_pStaticAmphiForm->m_pSecReliveList->Refresh();
		m_pStaticAmphiForm->RefreshAmphitheaterData(1);

		m_pSecReliveList->SetMouseFun(ListMouseRun);
	}
	frmNPCAmphitheater->SetIsShow(bShow);

}

//将数据写入链表
void CAmphitheaterForm::RefreshAmphitheaterData(AmphitheaterData &data)
{
	m_pStaticAmphiForm->m_pAmphitheaterData.DelTeamProAll();
	m_pStaticAmphiForm->m_pAmphitheaterData.DelTeamRelAll();

	std::vector<TeamProUnit> data1 = data.GetTeamProList();
	std::vector<TeamRelUnit> data2 = data.GetTeamRelList();

	for(int i=0;i<(int)data1.size();i++)
	{
		m_pStaticAmphiForm->m_pAmphitheaterData.AddTeamPro(&data1[i]);	
	}

	for(int i=0;i<(int)data2.size();i++)
	{
		m_pStaticAmphiForm->m_pAmphitheaterData.AddTeamRel(&data2[i]);	
	}

	m_pStaticAmphiForm->m_pSecPromotionList->Refresh();
	m_pStaticAmphiForm->RefreshAmphitheaterData(0);
	m_pStaticAmphiForm->RefreshAmphitheaterData(1);				
	m_pStaticAmphiForm->m_pSecReliveList->Refresh();

}

//根据页面刷新链表数据
void CAmphitheaterForm::RefreshAmphitheaterData(int index)
{
	std::vector<TeamProUnit> Prolist = m_pAmphitheaterData.GetTeamProList();
	std::vector<TeamRelUnit> Rellist = m_pAmphitheaterData.GetTeamRelList();
	std::vector<TeamProUnit>::iterator ProIt = Prolist.begin();
	std::vector<TeamRelUnit>::iterator RelIt = Rellist.begin();
	switch(index)
	{
	case 0:
		{
			if(m_pSecPromotionList)
			{
				for(;ProIt != Prolist.end();ProIt++)
				{
					char id[32];
					std::string strName(ProIt->PromCapName);
					while (  strName.length() < 16 )
					{
						strName += " ";
					}
					_snprintf_s(id,_countof( id ), _TRUNCATE,"%d",ProIt->PromID);
					strName +=id;
					m_pSecPromotionList->Add(strName.c_str());
					m_pSecPromotionList->Refresh();
				}
			}
		}
		break;
	case 1:
		{

			if(m_pSecReliveList)
			{
				for(;RelIt != Rellist.end();RelIt++)
				{
					char ballot[32];
					std::string strName(RelIt->RelCapName);
					while (  strName.length() < 16 )
					{
						strName += " ";
					}
					
					_snprintf_s(ballot, _countof( ballot ), _TRUNCATE,"%d",RelIt->Ballot);
					strName +=ballot;
					m_pSecReliveList->Add(strName.c_str());
					m_pSecReliveList->Refresh();
				}
			}
		}
		break;
	default:
		break;
	}
}

