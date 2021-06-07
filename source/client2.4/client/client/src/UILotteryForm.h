#pragma once
#include "UIGlobalVar.h"

namespace GUI
{

// 设置彩票
class CLotteryMgr : public CUIInterface
{
public:
	void		ShowLottery(bool bShow = true);
	int			GetForgeComIndex(COneCommand* oneCommand);
	void		Clear();

	void		LotterySuccess(long lChaID);
	void		LotteryFailed(long lChaID);
	void		LotteryOther(long lChaID);

protected:
	virtual bool Init();
	virtual void CloseForm();

	bool        SendLotteryProtocol();

private:
	static void _MainMouseEvent(CCompent *pSender, int nMsgType, int x, int y, DWORD dwKey);
	
	static void _DragEvtNo(int index, CGuiData *pSender,CCommandObj* pItem,bool& isAccept);

	static void _DragEvtNo1(CGuiData *pSender,CCommandObj* pItem,bool& isAccept);
	static void _DragEvtNo2(CGuiData *pSender,CCommandObj* pItem,bool& isAccept);
	static void _DragEvtNo3(CGuiData *pSender,CCommandObj* pItem,bool& isAccept);
	static void _DragEvtNo4(CGuiData *pSender,CCommandObj* pItem,bool& isAccept);
	static void _DragEvtNo5(CGuiData *pSender,CCommandObj* pItem,bool& isAccept);
	static void _DragEvtNo6(CGuiData *pSender,CCommandObj* pItem,bool& isAccept);

	static void _DragEvtLottery(CGuiData *pSender,CCommandObj* pItem,bool& isAccept);
	
	static void _DragBeforeEvt(CGuiData *pSender, int x, int y, DWORD key);
	

	static void _evtConfirmEvent(CCompent *pSender, int nMsgType, int x, int y, DWORD dwKey);
	static void _OnClose(CForm* pForm, bool& IsClose);


private:
	void		ClearUI();
	void		ClearItem();

	bool		IsNo(CItemCommand& rItem);
	bool		IsLottery(CItemCommand& rItem);
	bool		IsValidDragSource();

    void		PushItem(int iIndex, CItemCommand& rItem);
	void		PopItem(int iIndex);
   
	void		PushLottery(CItemCommand& rItem);
	void		PopLottery();

	void		SetLotteryUI();

	long		CalLotteryMoney();

private:
	enum {
		IITEM_NO1 = 0,
		IITEM_NO2 = 1,
		IITEM_NO3 = 2,
		IITEM_NO4 = 3,
		IITEM_NO5 = 4,
		IITEM_NO6 = 5,
		ITEM_NUM = 6,
	};

	CForm       *frmNPCLottery;				// 彩票设定界面

	COneCommand *cmdNoItem[ITEM_NUM];
	COneCommand *cmdLotteryItem;

	CTextButton *btnYes;
	CLabelEx    *labLotteryIssue;
	CLabelEx    *labLotteryID;
	CLabelEx    *labLotteryDate;

	static const int NO_USE = -1;

	int			m_iLotteryItemPos[ITEM_NUM];
	int			m_iLotteryPos;

	bool		m_isOldEquipFormShow;
	bool		m_isConfirm;

	static const int LOTTERY_TYPE = 75;
	static const int NO_TYPE = 76;
};

}

