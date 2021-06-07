#pragma once
#include "UIGlobalVar.h"
#include "uipage.h"
#include "TableData.h"
#include <vector>
#include "UIList.h"
#include "UIForm.h"
#include "UIScroll.h"


namespace GUI
{
	typedef void(* MouseFUN)(CGuiData *pSender, int x, int y, DWORD key);  

	struct TeamProUnit //晋级队伍信息
	{
		char PromCapName[50];//队长名
		int  PromID;		 //队伍ID
		int  WinNum;		 //赢次数

		TeamProUnit()
		{
			memset(PromCapName,0,sizeof(PromCapName));
			PromID = 0;
			WinNum = 0;
		}
	};
	struct TeamRelUnit //复活队伍信息
	{
		char  RelCapName[50];//队长名
		int   Ballot;		 //复活票数
		int	  RelID;		 //队伍ID
		TeamRelUnit()
		{
			memset(RelCapName,0,sizeof(RelCapName));
			Ballot = 0;
			RelID = 0;
		}
	};

	//竞技场排行榜数据
	class AmphitheaterData 
	{
	public:
		AmphitheaterData();
		~AmphitheaterData();
	public:
		// add
		void AddTeamPro(const TeamProUnit* _tp);
		void AddTeamRel(const TeamRelUnit* _tr);
		// delete
		void DelTeamPro(int TeamID);
		void DelTeamRel(int TeamID);

		void DelTeamProAll();
		void DelTeamRelAll();
		// get
		TeamProUnit * GetTeamPro(int index);
		TeamRelUnit * GetTeamRel(int index);

		std::vector<TeamProUnit> GetTeamProList(){return TeamProList;}
		std::vector<TeamRelUnit> GetTeamRelList(){return TeamRelList;}


		// update
		void Update(){};

	private:
		std::vector<TeamProUnit> TeamProList;	// 晋级队伍数据表
		std::vector<TeamRelUnit> TeamRelList;	// 复活队伍数据表

	};

	//竞技场排行列表
	class CAmphitheaterList:public CList
	{
	public:
		CAmphitheaterList(CForm& frmOwn);
		CAmphitheaterList(const CAmphitheaterList&  p);
		CAmphitheaterList& operator =(const CAmphitheaterList& p);
		GUI_CLONE(CAmphitheaterList);//clone button

		virtual ~CAmphitheaterList();
		virtual void		Render();
		virtual void		Refresh();
	
		
		virtual bool MouseScroll( int nScroll );
		virtual bool MouseRun( int x, int y, DWORD key );
	

		CTextButton*	GetButton()			{ return _buttonPip;}
		//void SetCloneButtonPic();
		//static void MouseClick(CGuiData *pSender, int x, int y, DWORD key);

		void SetMouseFun(MouseFUN pf);

	public:
		CTextButton*		_button[20];

	protected:
		int             _nSelectIndex;  // 选择的行数
		bool            _IsShowUpgrade;

		int             _nUnitHeight, _nUnitWidth;   // 单元图片宽高
	private:
		int					_ButtonLen;
		CTextButton*		_buttonPip;
		

		static CAmphitheaterList* g_pAmphiList;

	};

	//竞技场排行榜框架
	class CAmphitheaterForm : public CUIInterface
	{
	public:
		static CAmphitheaterForm * m_pStaticAmphiForm;


	public:
		void RefreshAmphitheaterData(int index);//切换页面刷新数据
		void RefreshAmphitheaterData(AmphitheaterData& data);//写入数据

		static void ListMouseRun(CGuiData *pSender, int x, int y, DWORD key);

	public:
		void ShowAmphitheaterFrom( bool bShow = true );
	protected:
		virtual bool Init();
		virtual void CloseForm();
		virtual void LoadingCall();
		virtual void Clear();
		virtual void FrameMove(DWORD dwTime){};

	private:
		CForm       *frmNPCAmphitheater;

		CAmphitheaterList*		m_pSecPromotionList;                // 晋级栏
		CAmphitheaterList*		m_pSecReliveList;					// 复活栏
		AmphitheaterData        m_pAmphitheaterData;
		CTextButton		*		m_pSecExListbt;


		CPage*			listPage;

		void			RefreshUpgrade();
	private:
		static void		_evtPageIndexChange(CGuiData *pSender);

	};
}
