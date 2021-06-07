#include "stdafx.h"

#include "flashplayer.h"
#include "gameapp.h"

#pragma comment(lib, "comsuppw.lib")

//////////////////////////////////////////////////////////////////////////
// Interfaces imported from flash.ocx
#pragma pack(push, 8)

#include <comdef.h>

namespace ShockwaveFlashObjects 
{
	//
	// Forward references and typedefs
	//

	struct __declspec(uuid("d27cdb6b-ae6d-11cf-96b8-444553540000"))
		/* LIBID */ __ShockwaveFlashObjects;
	struct __declspec(uuid("d27cdb6c-ae6d-11cf-96b8-444553540000"))
		/* dual interface */ ShockwaveFlashObjects::IShockwaveFlash;
	struct __declspec(uuid("d27cdb6d-ae6d-11cf-96b8-444553540000"))
		/* dispinterface */ _IShockwaveFlashEvents;
	struct /* coclass */ ShockwaveFlash;
	struct /* coclass */ FlashProp;
	struct __declspec(uuid("d27cdb70-ae6d-11cf-96b8-444553540000"))
		/* interface */ IFlashFactory;
	struct __declspec(uuid("d27cdb72-ae6d-11cf-96b8-444553540000"))
		/* interface */ IFlashObjectInterface;
	struct __declspec(uuid("a6ef9860-c720-11d0-9337-00a0c90dcaa9"))
		/* interface */ IDispatchEx;
	struct /* coclass */ FlashObjectInterface;

	//
	// Smart pointer typedef declarations
	//

	_COM_SMARTPTR_TYPEDEF(IShockwaveFlash, __uuidof(IShockwaveFlash));
	_COM_SMARTPTR_TYPEDEF(_IShockwaveFlashEvents, __uuidof(_IShockwaveFlashEvents));
	_COM_SMARTPTR_TYPEDEF(IFlashFactory, __uuidof(IFlashFactory));
	_COM_SMARTPTR_TYPEDEF(IDispatchEx, __uuidof(IDispatchEx));
	_COM_SMARTPTR_TYPEDEF(IFlashObjectInterface, __uuidof(IFlashObjectInterface));

	//
	// Type library items
	//

	struct __declspec(uuid("d27cdb6c-ae6d-11cf-96b8-444553540000"))
		ShockwaveFlashObjects::IShockwaveFlash : IDispatch
	{
		//
		// Property data
		//

		__declspec(property(get=GetStacking,put=PutStacking))
			_bstr_t Stacking;
		__declspec(property(get=GetWMode,put=PutWMode))
			_bstr_t WMode;
		__declspec(property(get=GetMovie,put=PutMovie))
			_bstr_t Movie;
		__declspec(property(get=GetSAlign,put=PutSAlign))
			_bstr_t SAlign;
		__declspec(property(get=GetMenu,put=PutMenu))
			VARIANT_BOOL Menu;
		__declspec(property(get=GetQuality,put=PutQuality))
			int Quality;
		__declspec(property(get=GetLoop,put=PutLoop))
			VARIANT_BOOL Loop;
		__declspec(property(get=GetFrameNum,put=PutFrameNum))
			long FrameNum;
		__declspec(property(get=GetBase,put=PutBase))
			_bstr_t Base;
		__declspec(property(get=Getscale,put=Putscale))
			_bstr_t scale;
		__declspec(property(get=GetDeviceFont,put=PutDeviceFont))
			VARIANT_BOOL DeviceFont;
		__declspec(property(get=GetEmbedMovie,put=PutEmbedMovie))
			VARIANT_BOOL EmbedMovie;
		__declspec(property(get=GetBGColor,put=PutBGColor))
			_bstr_t BGColor;
		__declspec(property(get=GetQuality2,put=PutQuality2))
			_bstr_t Quality2;
		__declspec(property(get=GetReadyState))
			long ReadyState;
		__declspec(property(get=GetScaleMode,put=PutScaleMode))
			int ScaleMode;
		__declspec(property(get=GetAlignMode,put=PutAlignMode))
			int AlignMode;
		__declspec(property(get=GetBackgroundColor,put=PutBackgroundColor))
			long BackgroundColor;
		__declspec(property(get=GetTotalFrames))
			long TotalFrames;
		__declspec(property(get=GetPlaying,put=PutPlaying))
			VARIANT_BOOL Playing;
		__declspec(property(get=GetSWRemote,put=PutSWRemote))
			_bstr_t SWRemote;

		//
		// Raw methods provided by interface
		//

		virtual HRESULT __stdcall get_ReadyState (
			/*[out,retval]*/ long * thestate ) = 0;
			virtual HRESULT __stdcall get_TotalFrames (
			/*[out,retval]*/ long * numframes ) = 0;
			virtual HRESULT __stdcall get_Playing (
			/*[out,retval]*/ VARIANT_BOOL * Playing ) = 0;
			virtual HRESULT __stdcall put_Playing (
			/*[in]*/ VARIANT_BOOL Playing ) = 0;
			virtual HRESULT __stdcall get_Quality (
			/*[out,retval]*/ int * Quality ) = 0;
			virtual HRESULT __stdcall put_Quality (
			/*[in]*/ int Quality ) = 0;
			virtual HRESULT __stdcall get_ScaleMode (
			/*[out,retval]*/ int * scale ) = 0;
			virtual HRESULT __stdcall put_ScaleMode (
			/*[in]*/ int scale ) = 0;
			virtual HRESULT __stdcall get_AlignMode (
			/*[out,retval]*/ int * align ) = 0;
			virtual HRESULT __stdcall put_AlignMode (
			/*[in]*/ int align ) = 0;
			virtual HRESULT __stdcall get_BackgroundColor (
			/*[out,retval]*/ long * color ) = 0;
			virtual HRESULT __stdcall put_BackgroundColor (
			/*[in]*/ long color ) = 0;
			virtual HRESULT __stdcall get_Loop (
			/*[out,retval]*/ VARIANT_BOOL * Loop ) = 0;
			virtual HRESULT __stdcall put_Loop (
			/*[in]*/ VARIANT_BOOL Loop ) = 0;
			virtual HRESULT __stdcall get_Movie (
			/*[out,retval]*/ BSTR * path ) = 0;
			virtual HRESULT __stdcall put_Movie (
			/*[in]*/ BSTR path ) = 0;
			virtual HRESULT __stdcall get_FrameNum (
			/*[out,retval]*/ long * FrameNum ) = 0;
			virtual HRESULT __stdcall put_FrameNum (
			/*[in]*/ long FrameNum ) = 0;
			virtual HRESULT __stdcall SetZoomRect (
			/*[in]*/ long left,
			/*[in]*/ long top,
			/*[in]*/ long right,
			/*[in]*/ long bottom ) = 0;
			virtual HRESULT __stdcall Zoom (
			/*[in]*/ int factor ) = 0;
			virtual HRESULT __stdcall Pan (
			/*[in]*/ long x,
			/*[in]*/ long y,
			/*[in]*/ int mode ) = 0;
			virtual HRESULT __stdcall Play ( ) = 0;
		virtual HRESULT __stdcall Stop ( ) = 0;
		virtual HRESULT __stdcall Back ( ) = 0;
		virtual HRESULT __stdcall Forward ( ) = 0;
		virtual HRESULT __stdcall Rewind ( ) = 0;
		virtual HRESULT __stdcall StopPlay ( ) = 0;
		virtual HRESULT __stdcall GotoFrame (
			/*[in]*/ long FrameNum ) = 0;
			virtual HRESULT __stdcall CurrentFrame (
			/*[out,retval]*/ long * FrameNum ) = 0;
			virtual HRESULT __stdcall IsPlaying (
			/*[out,retval]*/ VARIANT_BOOL * Playing ) = 0;
			virtual HRESULT __stdcall PercentLoaded (
			/*[out,retval]*/ long * __MIDL_0011 ) = 0;
			virtual HRESULT __stdcall FrameLoaded (
			/*[in]*/ long FrameNum,
			/*[out,retval]*/ VARIANT_BOOL * loaded ) = 0;
			virtual HRESULT __stdcall FlashVersion (
			/*[out,retval]*/ long * version ) = 0;
			virtual HRESULT __stdcall get_WMode (
			/*[out,retval]*/ BSTR * pVal ) = 0;
			virtual HRESULT __stdcall put_WMode (
			/*[in]*/ BSTR pVal ) = 0;
			virtual HRESULT __stdcall get_SAlign (
			/*[out,retval]*/ BSTR * pVal ) = 0;
			virtual HRESULT __stdcall put_SAlign (
			/*[in]*/ BSTR pVal ) = 0;
			virtual HRESULT __stdcall get_Menu (
			/*[out,retval]*/ VARIANT_BOOL * pVal ) = 0;
			virtual HRESULT __stdcall put_Menu (
			/*[in]*/ VARIANT_BOOL pVal ) = 0;
			virtual HRESULT __stdcall get_Base (
			/*[out,retval]*/ BSTR * pVal ) = 0;
			virtual HRESULT __stdcall put_Base (
			/*[in]*/ BSTR pVal ) = 0;
			virtual HRESULT __stdcall get_scale (
			/*[out,retval]*/ BSTR * pVal ) = 0;
			virtual HRESULT __stdcall put_scale (
			/*[in]*/ BSTR pVal ) = 0;
			virtual HRESULT __stdcall get_DeviceFont (
			/*[out,retval]*/ VARIANT_BOOL * pVal ) = 0;
			virtual HRESULT __stdcall put_DeviceFont (
			/*[in]*/ VARIANT_BOOL pVal ) = 0;
			virtual HRESULT __stdcall get_EmbedMovie (
			/*[out,retval]*/ VARIANT_BOOL * pVal ) = 0;
			virtual HRESULT __stdcall put_EmbedMovie (
			/*[in]*/ VARIANT_BOOL pVal ) = 0;
			virtual HRESULT __stdcall get_BGColor (
			/*[out,retval]*/ BSTR * pVal ) = 0;
			virtual HRESULT __stdcall put_BGColor (
			/*[in]*/ BSTR pVal ) = 0;
			virtual HRESULT __stdcall get_Quality2 (
			/*[out,retval]*/ BSTR * pVal ) = 0;
			virtual HRESULT __stdcall put_Quality2 (
			/*[in]*/ BSTR pVal ) = 0;
			virtual HRESULT __stdcall LoadMovie (
			/*[in]*/ int layer,
			/*[in]*/ BSTR url ) = 0;
			virtual HRESULT __stdcall TGotoFrame (
			/*[in]*/ BSTR target,
			/*[in]*/ long FrameNum ) = 0;
			virtual HRESULT __stdcall TGotoLabel (
			/*[in]*/ BSTR target,
			/*[in]*/ BSTR label ) = 0;
			virtual HRESULT __stdcall TCurrentFrame (
			/*[in]*/ BSTR target,
			/*[out,retval]*/ long * FrameNum ) = 0;
			virtual HRESULT __stdcall TCurrentLabel (
			/*[in]*/ BSTR target,
			/*[out,retval]*/ BSTR * pVal ) = 0;
			virtual HRESULT __stdcall TPlay (
			/*[in]*/ BSTR target ) = 0;
			virtual HRESULT __stdcall TStopPlay (
			/*[in]*/ BSTR target ) = 0;
			virtual HRESULT __stdcall SetVariable (
			/*[in]*/ BSTR name,
			/*[in]*/ BSTR value ) = 0;
			virtual HRESULT __stdcall GetVariable (
			/*[in]*/ BSTR name,
			/*[out,retval]*/ BSTR * pVal ) = 0;
			virtual HRESULT __stdcall TSetProperty (
			/*[in]*/ BSTR target,
			/*[in]*/ int property,
			/*[in]*/ BSTR value ) = 0;
			virtual HRESULT __stdcall TGetProperty (
			/*[in]*/ BSTR target,
			/*[in]*/ int property,
			/*[out,retval]*/ BSTR * pVal ) = 0;
			virtual HRESULT __stdcall TCallFrame (
			/*[in]*/ BSTR target,
			/*[in]*/ int FrameNum ) = 0;
			virtual HRESULT __stdcall TCallLabel (
			/*[in]*/ BSTR target,
			/*[in]*/ BSTR label ) = 0;
			virtual HRESULT __stdcall TSetPropertyNum (
			/*[in]*/ BSTR target,
			/*[in]*/ int property,
			/*[in]*/ double value ) = 0;
			virtual HRESULT __stdcall TGetPropertyNum (
			/*[in]*/ BSTR target,
			/*[in]*/ int property,
			/*[out,retval]*/ double * pVal ) = 0;
			virtual HRESULT __stdcall get_SWRemote (
			/*[out,retval]*/ BSTR * pVal ) = 0;
			virtual HRESULT __stdcall put_SWRemote (
			/*[in]*/ BSTR pVal ) = 0;
			virtual HRESULT __stdcall get_Stacking (
			/*[out,retval]*/ BSTR * pVal ) = 0;
			virtual HRESULT __stdcall put_Stacking (
			/*[in]*/ BSTR pVal ) = 0;
	};

	struct __declspec(uuid("d27cdb6d-ae6d-11cf-96b8-444553540000"))
_IShockwaveFlashEvents : IDispatch
	{
		//
		// Wrapper methods for error-handling
		//

		// Methods:
		HRESULT OnReadyStateChange (
			long newState );
		HRESULT OnProgress (
			long percentDone );
		HRESULT FSCommand (
			_bstr_t command,
			_bstr_t args );
	};

	struct __declspec(uuid("d27cdb6e-ae6d-11cf-96b8-444553540000"))
		ShockwaveFlash;
	// [ default ] interface ShockwaveFlashObjects::IShockwaveFlash
	// [ default, source ] dispinterface _IShockwaveFlashEvents

	struct __declspec(uuid("1171a62f-05d2-11d1-83fc-00a0c9089c5a"))
		FlashProp;
	// [ default ] interface IUnknown

	struct __declspec(uuid("d27cdb70-ae6d-11cf-96b8-444553540000"))
IFlashFactory : IUnknown
	{};

	struct __declspec(uuid("a6ef9860-c720-11d0-9337-00a0c90dcaa9"))
IDispatchEx : IDispatch
	{
		//
		// Wrapper methods for error-handling
		//

		HRESULT GetDispID (
			_bstr_t bstrName,
			unsigned long grfdex,
			long * pid );
		HRESULT RemoteInvokeEx (
			long id,
			unsigned long lcid,
			unsigned long dwFlags,
		struct DISPPARAMS * pdp,
			VARIANT * pvarRes,
		struct EXCEPINFO * pei,
		struct IServiceProvider * pspCaller,
			unsigned int cvarRefArg,
			unsigned int * rgiRefArg,
			VARIANT * rgvarRefArg );
		HRESULT DeleteMemberByName (
			_bstr_t bstrName,
			unsigned long grfdex );
		HRESULT DeleteMemberByDispID (
			long id );
		HRESULT GetMemberProperties (
			long id,
			unsigned long grfdexFetch,
			unsigned long * pgrfdex );
		HRESULT GetMemberName (
			long id,
			BSTR * pbstrName );
		HRESULT GetNextDispID (
			unsigned long grfdex,
			long id,
			long * pid );
		HRESULT GetNameSpaceParent (
			IUnknown * * ppunk );

		//
		// Raw methods provided by interface
		//

		virtual HRESULT __stdcall raw_GetDispID (
			/*[in]*/ BSTR bstrName,
			/*[in]*/ unsigned long grfdex,
			/*[out]*/ long * pid ) = 0;
			virtual HRESULT __stdcall raw_RemoteInvokeEx (
			/*[in]*/ long id,
			/*[in]*/ unsigned long lcid,
			/*[in]*/ unsigned long dwFlags,
		/*[in]*/ struct DISPPARAMS * pdp,
			/*[out]*/ VARIANT * pvarRes,
		/*[out]*/ struct EXCEPINFO * pei,
		/*[in]*/ struct IServiceProvider * pspCaller,
			/*[in]*/ unsigned int cvarRefArg,
			/*[in]*/ unsigned int * rgiRefArg,
			/*[in,out]*/ VARIANT * rgvarRefArg ) = 0;
			virtual HRESULT __stdcall raw_DeleteMemberByName (
			/*[in]*/ BSTR bstrName,
			/*[in]*/ unsigned long grfdex ) = 0;
			virtual HRESULT __stdcall raw_DeleteMemberByDispID (
			/*[in]*/ long id ) = 0;
			virtual HRESULT __stdcall raw_GetMemberProperties (
			/*[in]*/ long id,
			/*[in]*/ unsigned long grfdexFetch,
			/*[out]*/ unsigned long * pgrfdex ) = 0;
			virtual HRESULT __stdcall raw_GetMemberName (
			/*[in]*/ long id,
			/*[out]*/ BSTR * pbstrName ) = 0;
			virtual HRESULT __stdcall raw_GetNextDispID (
			/*[in]*/ unsigned long grfdex,
			/*[in]*/ long id,
			/*[out]*/ long * pid ) = 0;
			virtual HRESULT __stdcall raw_GetNameSpaceParent (
			/*[out]*/ IUnknown * * ppunk ) = 0;
	};

	struct __declspec(uuid("d27cdb72-ae6d-11cf-96b8-444553540000"))
IFlashObjectInterface : IDispatchEx
	{};

	struct __declspec(uuid("d27cdb71-ae6d-11cf-96b8-444553540000"))
		FlashObjectInterface;
	// [ default ] interface IFlashObjectInterface

} // namespace ShockwaveFlashObjects

#pragma pack(pop)

// FlashSink - Receives flash events   
class FlashSink : public ShockwaveFlashObjects::_IShockwaveFlashEvents
{
public:	
	LPCONNECTIONPOINT		mConnectionPoint;	
	DWORD					mCookie;
	int						mRefCount;
	CFlashPlayer*			m_pFlashPlayer;

public:
	FlashSink()
	{		
		mCookie = 0;
		mConnectionPoint = NULL;
		mRefCount = 0;
		m_pFlashPlayer = NULL;		
	}

	virtual ~FlashSink()
	{
		m_pFlashPlayer->m_nCOMCount--;
	}

	HRESULT Init(CFlashPlayer* pScene)
	{
		m_pFlashPlayer = pScene;
		m_pFlashPlayer->m_nCOMCount++;

		HRESULT aResult = NOERROR;
		LPCONNECTIONPOINTCONTAINER aConnectionPoint = NULL;

		if ((m_pFlashPlayer->m_pShockwaveFlash->QueryInterface(IID_IConnectionPointContainer, (void**) &aConnectionPoint) == S_OK) &&
			(aConnectionPoint->FindConnectionPoint(__uuidof(ShockwaveFlashObjects::_IShockwaveFlashEvents), &mConnectionPoint) == S_OK))			
		{
			IDispatch* aDispatch = NULL;
			QueryInterface(__uuidof(IDispatch), (void**) &aDispatch);
			if (aDispatch != NULL)
			{
				aResult = mConnectionPoint->Advise((LPUNKNOWN)aDispatch, &mCookie);
				aDispatch->Release();
			}
		}

		if (aConnectionPoint != NULL) 
			aConnectionPoint->Release();

		return aResult;
	}

	HRESULT Shutdown()
	{
		HRESULT aResult = S_OK;

		if (mConnectionPoint)
		{
			if (mCookie)
			{
				aResult = mConnectionPoint->Unadvise(mCookie);
				mCookie = 0;
			}

			mConnectionPoint->Release();
			mConnectionPoint = NULL;
		}

		return aResult;
	}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID* ppv)
	{
		*ppv = NULL;

		if (riid == IID_IUnknown)
		{
			*ppv = (LPUNKNOWN)this;
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IDispatch)
		{
			*ppv = (IDispatch*)this;
			AddRef();
			return S_OK;
		}
		else if (riid == __uuidof(ShockwaveFlashObjects::_IShockwaveFlashEvents))
		{
			*ppv = (ShockwaveFlashObjects::_IShockwaveFlashEvents*) this;
			AddRef();
			return S_OK;
		}
		else
		{   
			return E_NOTIMPL;
		}
	}

	ULONG STDMETHODCALLTYPE AddRef()
	{  
		return ++mRefCount;
	}

	ULONG STDMETHODCALLTYPE Release()
	{  
		int aRefCount = --mRefCount;
		if (aRefCount == 0)		
			delete this;		

		return aRefCount;
	}

	// IDispatch method
	virtual HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT* pctinfo)
	{ return E_NOTIMPL; }

	virtual HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo)
	{
		return E_NOTIMPL; 
	}

	virtual HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames,
		UINT cNames, LCID lcid,DISPID* rgDispId)
	{
		return E_NOTIMPL; 
	}

	virtual HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid,
		WORD wFlags, DISPPARAMS __RPC_FAR *pDispParams, VARIANT __RPC_FAR *pVarResult,
		::EXCEPINFO __RPC_FAR *pExcepInfo, UINT __RPC_FAR *puArgErr)
	{
		switch(dispIdMember)
		{
		case 0x7a6:			
			break;
		case 0x96:			
			if ((pDispParams->cArgs == 2) &&
				(pDispParams->rgvarg[0].vt == VT_BSTR) &&
				(pDispParams->rgvarg[1].vt == VT_BSTR))
			{
				FSCommand(pDispParams->rgvarg[1].bstrVal, pDispParams->rgvarg[0].bstrVal);
			}
			break;
		case DISPID_READYSTATECHANGE:					
			break;
		default:			
			return DISP_E_MEMBERNOTFOUND;
		} 

		return NOERROR;
	}

	HRESULT OnReadyStateChange (long newState)
	{	
		return S_OK;
	}

	HRESULT OnProgress(long percentDone )
	{		
		return S_OK;
	}

	virtual HRESULT FSCommand( _bstr_t command, _bstr_t args )
	{
		if( m_pFlashPlayer )
		{
			char* szParam1 = ( char* ) command;
			char* szParam2 = ( char* ) args;
			m_pFlashPlayer->FSCommand( szParam1, szParam2 );
		}
		
		return S_OK;
	}	
};

using namespace ShockwaveFlashObjects;

// ControlSite - container that holds the flash control
class ControlSite : 	
	public IOleInPlaceSiteWindowless, 
	public IOleClientSite	
{
public:
	int						mRefCount;
	CFlashPlayer*			m_pFlashPlayer;

public:
	ControlSite()
	{		
		mRefCount = 0;		
		m_pFlashPlayer = NULL;
	}	

	virtual ~ControlSite()
	{
		if( m_pFlashPlayer != NULL )
			m_pFlashPlayer->m_nCOMCount--;
	}

	void Init( CFlashPlayer* theFlashPlayer )
	{
		m_pFlashPlayer = theFlashPlayer;
		m_pFlashPlayer->m_nCOMCount++;
	}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID* ppv)
	{
		*ppv = NULL;

		if (riid == IID_IUnknown)
		{
			*ppv = (IUnknown*) (IOleWindow*) this;
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IOleWindow)
		{
			*ppv = (IOleWindow*)this;
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IOleInPlaceSite)
		{
			*ppv = (IOleInPlaceSite*)this;
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IOleInPlaceSiteEx)
		{
			*ppv = (IOleInPlaceSiteEx*)this;
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IOleInPlaceSiteWindowless)
		{
			*ppv = (IOleInPlaceSiteWindowless*)this;
			AddRef();
			return S_OK;
		}
		else if (riid == IID_IOleClientSite)
		{
			*ppv = (IOleClientSite*)this;
			AddRef();
			return S_OK;
		}
		else if (riid == __uuidof(ShockwaveFlashObjects::_IShockwaveFlashEvents))
		{
			*ppv = (ShockwaveFlashObjects::_IShockwaveFlashEvents*) this;
			AddRef();
			return S_OK;
		}
		else
		{   
			return E_NOTIMPL;
		}
	}

	ULONG STDMETHODCALLTYPE AddRef()
	{  
		return ++mRefCount;
	}

	ULONG STDMETHODCALLTYPE Release()
	{  
		int aRefCount = --mRefCount;
		if (aRefCount == 0)		
			delete this;		

		return aRefCount;
	}

	//////////////////////////////////////////////////////////////////////////	

	virtual HRESULT  STDMETHODCALLTYPE SaveObject(void)
	{
		return S_OK;
	}

	virtual HRESULT  STDMETHODCALLTYPE GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker,IMoniker** ppmk )
	{
		*ppmk = NULL;
		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE GetContainer(IOleContainer ** theContainerP)
	{
		//return QueryInterface(__uuidof(IOleContainer), (void**) theContainerP);				
		return E_NOINTERFACE;
	}


	virtual HRESULT  STDMETHODCALLTYPE ShowObject(void)
	{
		return E_NOTIMPL;
	}

	virtual HRESULT  STDMETHODCALLTYPE OnShowWindow(BOOL)
	{
		return E_NOTIMPL;
	}

	virtual HRESULT  STDMETHODCALLTYPE RequestNewObjectLayout(void)
	{
		return E_NOTIMPL;
	}
	//		


	HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(/* [in] */ BOOL fEnterMode)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetWindow(/* [out] */ HWND __RPC_FAR* theWnndow)
	{
		return E_FAIL;

		//*theWnndow = NULL;
		//*theWnndow = GMiniAtureApp->mHWnd;
		//return S_OK;
	}

	HRESULT STDMETHODCALLTYPE CanInPlaceActivate(void)
	{
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE OnInPlaceActivate(void)
	{		
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE OnUIActivate(void)
	{		
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE GetWindowContext(/* [out] */ IOleInPlaceFrame __RPC_FAR *__RPC_FAR *ppFrame, /* [out] */ IOleInPlaceUIWindow __RPC_FAR *__RPC_FAR *ppDoc, /* [out] */ LPRECT lprcPosRect, /* [out] */ LPRECT lprcClipRect, /* [out][in] */ LPOLEINPLACEFRAMEINFO lpFrameInfo)
	{
		RECT rect;
		m_pFlashPlayer->GetRECT( &rect );

		*lprcPosRect = rect;
		*lprcClipRect = rect;

		*ppFrame = NULL;
		QueryInterface(__uuidof(IOleInPlaceFrame), (void**) ppFrame);		
		*ppDoc = NULL;

		lpFrameInfo->fMDIApp = FALSE;
		lpFrameInfo->hwndFrame = NULL;
		lpFrameInfo->haccel = NULL;
		lpFrameInfo->cAccelEntries = 0;

		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE Scroll(/* [in] */ SIZE scrollExtant)
	{
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE OnUIDeactivate(/* [in] */ BOOL fUndoable)
	{		
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate(void)
	{	
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE DiscardUndoState(void)
	{
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE DeactivateAndUndo(void)
	{
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE OnPosRectChange(/* [in] */ LPCRECT lprcPosRect)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE OnInPlaceActivateEx(/* [out] */ BOOL __RPC_FAR *pfNoRedraw, /* [in] */ DWORD dwFlags)
	{		
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE OnInPlaceDeactivateEx(/* [in] */ BOOL fNoRedraw)
	{		
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE RequestUIActivate(void)
	{
		return S_FALSE;
	}


	HRESULT STDMETHODCALLTYPE CanWindowlessActivate(void)
	{
		// Allow windowless activation?
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE GetCapture(void)
	{
		// TODO capture the mouse for the object
		return S_FALSE;
	}


	HRESULT STDMETHODCALLTYPE SetCapture(/* [in] */ BOOL fCapture)
	{
		// TODO capture the mouse for the object
		return S_FALSE;
	}


	HRESULT STDMETHODCALLTYPE GetFocus(void)
	{
		return S_OK;
	}


	HRESULT STDMETHODCALLTYPE SetFocus(/* [in] */ BOOL fFocus)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE GetDC(/* [in] */ LPCRECT pRect, /* [in] */ DWORD grfFlags, /* [out] */ HDC __RPC_FAR *phDC)
	{		
		return E_INVALIDARG;		
	}


	HRESULT STDMETHODCALLTYPE ReleaseDC(/* [in] */ HDC hDC)
	{
		return E_INVALIDARG;
	}

	HRESULT STDMETHODCALLTYPE InvalidateRect( /* [in] */ LPCRECT pRect, /* [in] */ BOOL fErase )
	{	
		if( pRect == NULL )
		{
			m_pFlashPlayer->GetRECT( &m_pFlashPlayer->m_FlashDirtyRect );
			m_pFlashPlayer->m_bFlashDirty = true;
		}
		else if( !m_pFlashPlayer->m_bFlashDirty )
		{
			m_pFlashPlayer->m_FlashDirtyRect = *pRect;
			m_pFlashPlayer->m_bFlashDirty = TRUE;
		}
		else
			UnionRect( &m_pFlashPlayer->m_FlashDirtyRect, &m_pFlashPlayer->m_FlashDirtyRect, pRect );	
		
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE InvalidateRgn( /* [in] */ HRGN hRGN, /* [in] */ BOOL fErase )
	{	
		m_pFlashPlayer->GetRECT( &m_pFlashPlayer->m_FlashDirtyRect );
		m_pFlashPlayer->m_bFlashDirty = TRUE;
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE ScrollRect(/* [in] */ INT dx, /* [in] */ INT dy, /* [in] */ LPCRECT pRectScroll, /* [in] */ LPCRECT pRectClip)
	{
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE AdjustRect(/* [out][in] */ LPRECT prc)
	{
		if (prc == NULL)
		{
			return E_INVALIDARG;
		}

		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE OnDefWindowMessage(/* [in] */ UINT msg, /* [in] */ WPARAM wParam, /* [in] */ LPARAM lParam, /* [out] */ LRESULT __RPC_FAR *plResult)
	{
		return S_FALSE;
	}
};

CHAR* GetFlashDir( int UpLayers )
{
	assert( UpLayers > 0 );

	static CHAR	FlashDir[MAX_PATH] = { 0 };
	if( FlashDir[0] )
		return FlashDir;

	if( !GetModuleFileName( NULL, FlashDir, MAX_PATH ) )
	{
		MessageBox( 0, "Failed calling GetModuleFileName", "Error", MB_OK );
		return NULL;
	}

	//size_t length = strlen( FlashDir );
	for( size_t length = strlen( FlashDir ); length > 3; length -- )
	{
		if( FlashDir[length - 1] == '\\' || FlashDir[length - 1] == '/' )
		{
			if( -- UpLayers == 0 )
			{
				FlashDir[length - 1] = 0;
				break;
			}

		}
	}

	return FlashDir;
}

const CLSID CLSID_ShockwaveFlash =
{ 0xD27CDB6E, 0xAE6D, 0x11cf, {0x96, 0xB8, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00} };

typedef HRESULT ( __stdcall *DllGetClassObjectFunc )( REFCLSID rclsid, REFIID riid, LPVOID* ppv );

CFlashPlayer::CFlashPlayer()
{
	m_hWnd					= g_pGameApp->GetHWND();
	m_bWindowed				= TRUE;

	m_lpDD					= NULL;
	m_lpPrimarySurface		= NULL;
	m_lpSecondarySurface	= NULL;
	m_lpBackgroundSurface	= NULL;
	m_lpFlashBuffer			= NULL;

	m_hFlashOCX			= NULL;
	m_pOleObject		= NULL;
	m_pShockwaveFlash	= NULL;
	m_pObjectWindowless	= NULL;
	m_pControlSite		= NULL;
	m_pFlashSink		= NULL;
	m_nCOMCount			= 0;

	m_bFlashDirty = TRUE;
	m_FlashStartX	= 0;
	m_FlashStartY	= 0;
	m_FlashWidth	= 0;
	m_FlashHeight	= 0;

	//	m_bFlashLostFocus	= g_pGameClientShell->IsFlashNeedPause();	
	m_FlashState		= STATE_CLOSE;
	m_bAutoPause		= TRUE;
}

CFlashPlayer::~CFlashPlayer()
{
	if( m_pObjectWindowless )
		m_pObjectWindowless->Release();

	if( m_pShockwaveFlash )
		m_pShockwaveFlash->Release();

	if( m_pFlashSink )
	{
		m_pFlashSink->Shutdown();
		m_pFlashSink->Release();
	}

	if( m_pOleObject )
		m_pOleObject->Close( OLECLOSE_NOSAVE );

	if( m_pOleObject )
		m_pOleObject->Release();	

	if( m_pControlSite )
		m_pControlSite->Release();

	// Make sure all our COM objects were actually destroyed
	assert( m_nCOMCount == 0 );

	if( m_hFlashOCX )
	{
		FreeLibrary( m_hFlashOCX );
		m_hFlashOCX = NULL;
	}

	SAFE_RELEASE( m_lpFlashBuffer );
	SAFE_RELEASE( m_lpBackgroundSurface );
	SAFE_RELEASE( m_lpSecondarySurface );
	SAFE_RELEASE( m_lpPrimarySurface );

	SAFE_RELEASE( m_lpDD );
}

VOID CFlashPlayer::Init()
{
	CoInitialize( NULL );

	m_pControlSite = new ControlSite();
	m_pControlSite->AddRef();	
	m_pControlSite->Init( this );

	m_hFlashOCX = LoadLibrary( "flash9f.ocx" );
	if( m_hFlashOCX )
	{
		IClassFactory* pClassFactory = NULL;
		DllGetClassObjectFunc pDllGetClassObjectFunc = ( DllGetClassObjectFunc ) GetProcAddress( m_hFlashOCX, "DllGetClassObject" );
		pDllGetClassObjectFunc( CLSID_ShockwaveFlash, IID_IClassFactory, ( void** ) &pClassFactory );
		pClassFactory->CreateInstance( NULL, IID_IOleObject, ( void** ) &m_pOleObject );
		pClassFactory->Release();	
	}
	else
		CoCreateInstance( CLSID_ShockwaveFlash, NULL, CLSCTX_INPROC_SERVER, IID_IOleObject, ( void** ) &m_pOleObject );

	IOleClientSite* pClientSite = NULL;
	m_pControlSite->QueryInterface( __uuidof( IOleClientSite ), ( void** ) &pClientSite );
	m_pOleObject->SetClientSite( pClientSite );	

	m_pOleObject->QueryInterface( __uuidof( IShockwaveFlash ), ( LPVOID* ) &m_pShockwaveFlash );
	_bstr_t string = "Transparent";
	m_pShockwaveFlash->put_WMode( string );

	m_pOleObject->DoVerb( OLEIVERB_INPLACEACTIVATE, NULL, pClientSite, 0, NULL, NULL );
	pClientSite->Release();	

	m_pOleObject->QueryInterface( __uuidof( IOleInPlaceObjectWindowless ), ( LPVOID* ) &m_pObjectWindowless );

	m_pFlashSink = new FlashSink();
	m_pFlashSink->AddRef();	
	m_pFlashSink->Init( this );

	if( !m_lpDD )
	{
		// DDraw stuff begins here
		BOOL Succeed = SUCCEEDED( DirectDrawCreateEx( NULL, ( VOID** ) &m_lpDD, IID_IDirectDraw7, NULL ) );
		assert( Succeed );

		// Set cooperative level
		Succeed = SUCCEEDED( m_lpDD->SetCooperativeLevel( m_hWnd, DDSCL_NORMAL ) );
		assert( Succeed );

		// Create the primary surface
		DDSURFACEDESC2 ddsd;
		ZeroMemory( &ddsd, sizeof( ddsd ) );
		ddsd.dwSize         = sizeof( ddsd );
		ddsd.dwFlags        = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		Succeed = SUCCEEDED( m_lpDD->CreateSurface( &ddsd, &m_lpPrimarySurface, NULL ) );
		assert( Succeed );

		ZeroMemory( &ddsd, sizeof( ddsd ) );
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
		ddsd.dwWidth = g_pGameApp->GetWindowWidth();
		ddsd.dwHeight = g_pGameApp->GetWindowHeight();
		Succeed = SUCCEEDED( m_lpDD->CreateSurface( &ddsd, &m_lpSecondarySurface, NULL ) );
		assert( Succeed );

		LPDIRECTDRAWCLIPPER lpDrawClipper;
		Succeed = SUCCEEDED( m_lpDD->CreateClipper( 0, &lpDrawClipper, NULL ) );
		assert( Succeed );
		Succeed = SUCCEEDED( lpDrawClipper->SetHWnd( 0, m_hWnd ) );
		assert( Succeed );
		Succeed = SUCCEEDED( m_lpPrimarySurface->SetClipper( lpDrawClipper ) );
		assert( Succeed );
		lpDrawClipper->Release();

		UpdateBounds();
	}
}

VOID CFlashPlayer::Activate( BOOL bActive )
{
	if( bActive )
	{
		if( !m_lpFlashBuffer )
			ResizeFlashZone( ( g_pGameApp->GetWindowWidth() - 634 ) / 2, 
			( g_pGameApp->GetWindowHeight() - 476 ) / 2, 634, 476, FALSE );
	}
	else
		CloseFlash();
}

VOID CFlashPlayer::Update()
{
	if( m_bAutoPause )
	{
	//	if( g_pGameClientShell->IsFlashNeedPause() )
		{
			if( !m_bFlashLostFocus )
			{
				Pause();
				m_bFlashLostFocus = TRUE;
			}

			return;
		}
/*	else
		{
			if( m_bFlashLostFocus )
			{
				Unpause();
				m_bFlashLostFocus = FALSE;
			}
		}*/
	}

	if( m_FlashState == STATE_PLAYING )
	{
		VARIANT_BOOL bPlaying = 0;
		m_pShockwaveFlash->IsPlaying( &bPlaying );	
		if( !bPlaying )
		{
			m_FlashState = STATE_STOPPED;
//			SendCommand( CMD_FLASH, 0, 0 );
		}
	}
}

VOID CFlashPlayer::Paint()
{
	PAINTSTRUCT PS;
	HDC hDC = BeginPaint( m_hWnd, &PS );
	HBRUSH B = (HBRUSH)COLOR_MENU;
	RECT Rect;
	GetClientRect( m_hWnd, &Rect );
	FillRect( hDC, &Rect, B );

	if( m_bFlashDirty )
	{
		IViewObject* pViewObject = NULL;
		m_pShockwaveFlash->QueryInterface( IID_IViewObject, ( LPVOID* ) &pViewObject );
		if( pViewObject != NULL )
		{
			RECTL rect = { 0, 0, m_FlashWidth, m_FlashHeight };

			HRGN aRgn = CreateRectRgn(m_FlashDirtyRect.left - m_FlashStartX, m_FlashDirtyRect.top - m_FlashStartY, 
				m_FlashDirtyRect.left + m_FlashDirtyRect.right - m_FlashStartX, 
				m_FlashDirtyRect.top + m_FlashDirtyRect.bottom - m_FlashStartY);
			SelectClipRgn(hDC, aRgn);
			DeleteObject(aRgn);

			pViewObject->Draw( DVASPECT_CONTENT, -1, NULL, NULL, NULL, hDC, &rect, NULL, NULL, TRUE );

			pViewObject->Release();
		}
	}

	EndPaint( m_hWnd, &PS );
}

HRESULT	CFlashPlayer::CreateBackgroundSurface( const char* Filename )
{
	if( m_lpDD == NULL || Filename == NULL )
		 return E_INVALIDARG;

	char szFilename[_MAX_PATH] = { 0 };
	const char* dir = GetFlashDir( 2 );
	//sprintf( szFilename, "%s\\flash\\%s", dir, Filename );
	_snprintf_s( szFilename,sizeof(szFilename),_TRUNCATE, "%s\\flash\\%s", dir, Filename );
	HBITMAP hBitmap = ( HBITMAP ) LoadImage( GetModuleHandle( NULL ), szFilename, IMAGE_BITMAP,
		800, 600, LR_CREATEDIBSECTION );
	if( !hBitmap )
	{
		hBitmap = ( HBITMAP ) LoadImage( NULL, szFilename, IMAGE_BITMAP, 
			800, 600, LR_LOADFROMFILE | LR_CREATEDIBSECTION );
	}
	if( !hBitmap )
		return E_FAIL;

	BITMAP Bitmap;
	GetObject( hBitmap, sizeof( Bitmap ), &Bitmap );

	DDSURFACEDESC2 ddsd;
	ZeroMemory( &ddsd, sizeof( ddsd ) );
	ddsd.dwSize			= sizeof( ddsd );
	ddsd.dwFlags		= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth        = g_pGameApp->GetWindowWidth();
	ddsd.dwHeight       = g_pGameApp->GetWindowHeight();

	HDC hDCImage = CreateCompatibleDC( NULL );
	SelectObject( hDCImage, hBitmap );

	if( FAILED( m_lpDD->CreateSurface( &ddsd, &m_lpBackgroundSurface, NULL ) ) )
	{
		DeleteDC( hDCImage );
		return E_FAIL;
	}

	HDC hDirectDrawDC;
	m_lpBackgroundSurface->GetDC( &hDirectDrawDC );

	StretchBlt( hDirectDrawDC, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hDCImage, 
		0, 0, 800, 600, SRCCOPY );

	m_lpBackgroundSurface->ReleaseDC( hDirectDrawDC );

	DeleteDC( hDCImage );

	return S_OK;
}

VOID CFlashPlayer::Render()
{
	// Erase the background
	DDBLTFX ddbltfx;
	ZeroMemory( &ddbltfx, sizeof(ddbltfx) );
	ddbltfx.dwSize      = sizeof(ddbltfx);
	ddbltfx.dwFillColor = 0xFF000000;

	m_lpSecondarySurface->Blt( NULL, NULL, NULL, DDBLT_COLORFILL, &ddbltfx );

	if( m_lpBackgroundSurface )
		m_lpSecondarySurface->BltFast( 0, 0, m_lpBackgroundSurface, NULL, 0 );

	if( m_lpFlashBuffer )
	{
		if( m_bFlashDirty )
		{
			HDC hDC = NULL;
			if( m_lpFlashBuffer->GetDC( &hDC ) != S_OK )
				return;	

			IViewObject* pViewObject = NULL;
			m_pShockwaveFlash->QueryInterface( IID_IViewObject, ( LPVOID* ) &pViewObject );
			if( pViewObject != NULL )
			{
				RECTL rect = { 0, 0, m_FlashWidth, m_FlashHeight };

				IntersectClipRect( hDC, m_FlashDirtyRect.left - m_FlashStartX, m_FlashDirtyRect.top - m_FlashStartY, 
					m_FlashDirtyRect.right - m_FlashStartX, 
					m_FlashDirtyRect.bottom - m_FlashStartY );

				pViewObject->Draw( DVASPECT_CONTENT, 1, NULL, NULL, NULL, hDC, &rect, NULL, NULL, 0 );

				pViewObject->Release();
			}

			m_lpFlashBuffer->ReleaseDC( hDC );

			m_bFlashDirty = FALSE;
		}

		m_lpSecondarySurface->BltFast( m_FlashStartX, m_FlashStartY, m_lpFlashBuffer, NULL, 0 );
	}

	while( TRUE )
	{
		HRESULT hr;
		if( m_bWindowed )
			hr = m_lpPrimarySurface->Blt( &m_WindowRect, m_lpSecondarySurface, NULL, DDBLT_WAIT, NULL );
		else
			hr = m_lpPrimarySurface->Flip( NULL, 0 );

		if( hr == DDERR_SURFACELOST )
		{
			m_lpPrimarySurface->Restore();
			m_lpSecondarySurface->Restore();
		}

		if( hr != DDERR_WASSTILLDRAWING )
			break;
	}
}

VOID CFlashPlayer::SetupFlash( const char* SWFFile )
{
	assert( SWFFile );

	CloseFlash();

	ResizeFlashZone( ( g_pGameApp->GetWindowWidth() - 634 ) / 2, 
		( g_pGameApp->GetWindowHeight() - 476 ) / 2, 634, 476 );

	char szFilename[_MAX_PATH] = { 0 };
	const char* dir = GetFlashDir( 2 );
	//sprintf( szFilename, "%s\\flash\\%s", dir, SWFFile );
	_snprintf_s( szFilename,sizeof(szFilename),_TRUNCATE, "%s\\flash\\%s", dir, SWFFile );

	_bstr_t bstr( szFilename );		
	m_pShockwaveFlash->put_Movie( bstr ); // you have to change the path here
	GotoFrame( 0 , FALSE );

	m_FlashState = STATE_STOPPED;
}

VOID CFlashPlayer::CloseFlash()
{
	if ( m_pShockwaveFlash && m_FlashState != STATE_CLOSE )
		m_pShockwaveFlash->put_Playing( FALSE );

	SAFE_RELEASE( m_lpFlashBuffer );
	m_FlashState = STATE_CLOSE;
}

VOID CFlashPlayer::ResizeFlashZone( INT X, INT Y, INT Width, INT Height, BOOL CreateSurf )
{
	FLOAT xStart = ( FLOAT ) X, yStart = ( FLOAT ) Y;
	FLOAT xEnd = ( FLOAT ) ( X + Width ), yEnd = ( FLOAT ) ( Y + Height );

	if( !CreateSurf )
		return;

	SAFE_RELEASE( m_lpFlashBuffer );

	DDSURFACEDESC2 ddsd;
	// Create a DirectDrawSurface for this bitmap
	ZeroMemory( &ddsd, sizeof( ddsd ) );
	ddsd.dwSize         = sizeof( ddsd );
	ddsd.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth        = Width;
	ddsd.dwHeight       = Height;

	// Create the DDraw surface
	BOOL Succeed = SUCCEEDED( m_lpDD->CreateSurface( &ddsd, &m_lpFlashBuffer, NULL ) );
	assert( Succeed );

	if( m_FlashStartX == X && m_FlashStartY == Y && m_FlashWidth == Width && m_FlashHeight == Height )
		return;

	m_FlashStartX	= X;
	m_FlashStartY	= Y;
	m_FlashWidth	= Width;
	m_FlashHeight	= Height;

	IOleInPlaceObject* pInPlaceObject = NULL;	
	m_pOleObject->QueryInterface( __uuidof( IOleInPlaceObject ), ( LPVOID* ) &pInPlaceObject );			
	if( pInPlaceObject )
	{
		RECT rect;
		GetRECT( &rect );
		pInPlaceObject->SetObjectRects( &rect, &rect );
		pInPlaceObject->Release();
	}

	m_FlashDirtyRect.left	= X;
	m_FlashDirtyRect.top	= Y;
	m_FlashDirtyRect.right	= X + Width;
	m_FlashDirtyRect.bottom	= Y + Height;
}

VOID CFlashPlayer::Play()
{
	if( IsPlaying() || m_FlashState == STATE_CLOSE )
		return;

	if( m_pShockwaveFlash )
		m_pShockwaveFlash->Play();

	m_FlashState = STATE_PLAYING;
}

VOID CFlashPlayer::Forward()
{
	if( m_pShockwaveFlash )
	{
		m_pShockwaveFlash->Forward();
		m_pShockwaveFlash->Play();
	}
}

VOID CFlashPlayer::Back()
{
	if( m_pShockwaveFlash )
	{
		m_pShockwaveFlash->Back();
		m_pShockwaveFlash->Play();
	}
}

VOID CFlashPlayer::Rewind()
{
	if( m_pShockwaveFlash )
	{
		m_pShockwaveFlash->Rewind();
		m_pShockwaveFlash->Play();
	}
}

BOOL CFlashPlayer::IsPlaying()
{
	VARIANT_BOOL bPlaying = 0;
	if( m_pShockwaveFlash )
		m_pShockwaveFlash->IsPlaying( &bPlaying );

	return bPlaying != 0;
}

VOID CFlashPlayer::Pause()
{	
	if( m_FlashState != STATE_STOPPED )
		m_FlashState = STATE_IDLE;

	if ( m_pShockwaveFlash && m_FlashState != STATE_STOPPED )
		m_pShockwaveFlash->StopPlay();
}

VOID CFlashPlayer::Unpause()
{
	if( m_pShockwaveFlash && m_FlashState != STATE_STOPPED )
	{
		m_FlashState = STATE_PLAYING;
		m_pShockwaveFlash->Play();
	}
}

LONG CFlashPlayer::GetTotalFrames()
{
	LONG Index = -1;
	if( m_pShockwaveFlash )
		m_pShockwaveFlash->get_TotalFrames( &Index );

	return Index;
}

LONG CFlashPlayer::GetCurrentFrame()
{	
	LONG Index = -1;
	if( m_pShockwaveFlash )
		m_pShockwaveFlash->CurrentFrame( &Index );

	return Index;
}

VOID CFlashPlayer::GotoFrame( INT Index, BOOL bPlay )
{
	if( m_pShockwaveFlash )
	{
		m_pShockwaveFlash->GotoFrame( Index );

		if( bPlay )
		{
			m_pShockwaveFlash->Play();
			m_FlashState = STATE_PLAYING;
		}
	}
}

VOID CFlashPlayer::CallFrame( const CHAR* Target, INT FrameNum )
{
	if( m_pShockwaveFlash )
		m_pShockwaveFlash->TCallFrame( _bstr_t( Target ), FrameNum );
}

VOID CFlashPlayer::SetVariable( const CHAR* Name, const CHAR* Variable )
{
	if( m_pShockwaveFlash )
		m_pShockwaveFlash->SetVariable( _bstr_t( Name ), _bstr_t( Variable ) );
}

const CHAR* CFlashPlayer::GetVariable( const CHAR* Name )
{
	BSTR Variable = L"";
	if( m_pShockwaveFlash )
		m_pShockwaveFlash->GetVariable(_bstr_t( Name ), &Variable );

	return ( const CHAR* ) _bstr_t( Variable );
}

const CHAR* CFlashPlayer::GetCurrentLabel( const CHAR* Target )
{
	BSTR Label = L"";
	if( m_pShockwaveFlash )
		m_pShockwaveFlash->TCurrentLabel( _bstr_t( Target ), &Label );

	return ( const CHAR* ) _bstr_t( Label );
}

VOID CFlashPlayer::CallLabel( const CHAR* target, const CHAR* Label )
{
	if( m_pShockwaveFlash )
		m_pShockwaveFlash->TCallLabel( _bstr_t( target ), _bstr_t( Label ) );
}

VOID CFlashPlayer::SetQuality( int Quality )
{
	static CHAR* pszQualityNames[3] = { "Low", "Medium", "High" };
	_bstr_t bstr = pszQualityNames[Quality];
	m_pShockwaveFlash->put_Quality2( bstr );
}

DOUBLE CFlashPlayer::GetFlashVersion()
{
	CoInitialize( NULL );

	IOleObject* pOleObject = NULL;
	if( FAILED( CoCreateInstance( CLSID_ShockwaveFlash, NULL, CLSCTX_INPROC_SERVER, IID_IOleObject, ( void** ) &pOleObject ) ) )
		return 0.0;	

	IShockwaveFlash* pShockwaveFlash = NULL;
	if( FAILED( pOleObject->QueryInterface( __uuidof( IShockwaveFlash ), ( LPVOID* ) &pShockwaveFlash ) ) )
		return 0.0;

	LONG version = 0;
	pShockwaveFlash->FlashVersion( &version );

	pShockwaveFlash->Release();
	pOleObject->Release();

	return version / 65536.0;
}

VOID CFlashPlayer::OnMouseMove( INT X, INT Y )
{
	LRESULT result;
	m_pObjectWindowless->OnWindowMessage( WM_MOUSEMOVE, 0, MAKELPARAM( X, Y ), &result );
}

VOID CFlashPlayer::OnLButtonDown( INT X, INT Y )
{
	LRESULT result;
	m_pObjectWindowless->OnWindowMessage( WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM( X, Y ), &result );
}

VOID CFlashPlayer::OnLButtonUp( INT X, INT Y )
{
	LRESULT result;
	m_pObjectWindowless->OnWindowMessage( WM_LBUTTONUP, 0, MAKELPARAM( X, Y ), &result );
}

VOID CFlashPlayer::GetRECT( LPRECT rect )
{
	rect->left		= m_FlashStartX;
	rect->top		= m_FlashStartY;
	rect->right		= m_FlashStartX + m_FlashWidth;
	rect->bottom	= m_FlashStartY + m_FlashHeight;
}

VOID CFlashPlayer::MessageProc( UINT message, WPARAM wParam, LPARAM lParam )
{
	if( m_pObjectWindowless )
	{
		LRESULT result = S_OK;
		if( message == WM_SETCURSOR || message == WM_KEYDOWN || message == WM_KEYUP || message == WM_CHAR ||
			message == WM_MOUSEMOVE || message == WM_LBUTTONDOWN || message == WM_LBUTTONUP || 
			message == WM_LBUTTONDBLCLK || message == WM_RBUTTONDOWN || message == WM_RBUTTONUP || 
			message == WM_RBUTTONDBLCLK || message == WM_MBUTTONDOWN || message == WM_MBUTTONUP || 
			message == WM_MBUTTONDBLCLK /*|| message == WM_MOUSEWHEEL*/ )
			m_pObjectWindowless->OnWindowMessage( message, wParam, lParam, &result );
		else if( message == WM_MOVE || message == WM_SIZE )
			UpdateBounds();
	}
}

VOID CFlashPlayer::UpdateBounds()
{
	if( m_bWindowed )
	{
		GetClientRect( m_hWnd, &m_WindowRect );
		ClientToScreen( m_hWnd, ( POINT* ) &m_WindowRect );
		ClientToScreen( m_hWnd, ( POINT* ) &m_WindowRect + 1 );
	}
	else
		SetRect( &m_WindowRect, 0, 0, GetSystemMetrics( SM_CXSCREEN ), GetSystemMetrics( SM_CYSCREEN ) );
}
