#include <ddraw.h>

struct IOleObject;
struct IOleInPlaceObjectWindowless;

namespace ShockwaveFlashObjects
{
	struct IShockwaveFlash;
}

class FlashSink;
class ControlSite;

class CFlashPlayer
{
public:
	VOID	GetRECT( LPRECT rect );
	VOID	UpdateBounds();
	VOID	SetupFlash( const CHAR* SWFFile );
	VOID	GotoFrame( INT Index, BOOL bPlay = TRUE );
	LONG	GetTotalFrames();

	virtual VOID	FSCommand( char* szParam1, char* szParam2 ) {}

protected:
	CFlashPlayer();
	virtual ~CFlashPlayer();

	VOID		Init();
	HRESULT		CreateBackgroundSurface( const char* Filename );
	VOID		Activate( BOOL bActive );
	VOID		Update();
	VOID		Render();
	VOID		Paint();

	VOID		ResizeFlashZone( INT X, INT Y, INT Width, INT Height, BOOL CreateSurf = TRUE );
	VOID		CloseFlash();
	VOID		Play();
	VOID		Forward();
	VOID		Back();
	VOID		Rewind();
	BOOL		IsPlaying();
	VOID		Pause();
	VOID		Unpause();
	LONG		GetCurrentFrame();
	VOID		CallFrame( const CHAR* Target, INT FrameNum );
	VOID		SetVariable( const CHAR* Name, const CHAR* Variable );
	const CHAR*	GetVariable( const CHAR* Name );
	const CHAR* GetCurrentLabel( const CHAR* Target );
	VOID		CallLabel( const CHAR* Target, const CHAR* Label );
	VOID		SetQuality( INT Quality );
	DOUBLE		GetFlashVersion();

	VOID		OnMouseMove( INT X, INT Y );
	VOID		OnLButtonDown( INT X, INT Y );
	VOID		OnLButtonUp( INT X, INT Y );
	VOID		MessageProc( UINT message, WPARAM wParam, LPARAM lParam );

public:
	enum
	{
		STATE_IDLE,
		STATE_PLAYING,
		STATE_STOPPED,
		STATE_CLOSE
	};

	HMODULE									m_hFlashOCX;
	IOleObject*								m_pOleObject;
	ShockwaveFlashObjects::IShockwaveFlash* m_pShockwaveFlash;
	IOleInPlaceObjectWindowless*			m_pObjectWindowless;
	ControlSite*							m_pControlSite;
	FlashSink*								m_pFlashSink;
	INT										m_nCOMCount;

	RECT									m_FlashDirtyRect;
	BOOL									m_bFlashDirty;

protected:
	HWND					m_hWnd;
	RECT					m_WindowRect;
	BOOL					m_bWindowed;
	LPDIRECTDRAW7			m_lpDD;
	LPDIRECTDRAWSURFACE7	m_lpPrimarySurface,
							m_lpSecondarySurface,
							m_lpBackgroundSurface,
							m_lpFlashBuffer;

	INT						m_FlashStartX;
	INT						m_FlashStartY;
	INT						m_FlashWidth;
	INT						m_FlashHeight;

	BOOL					m_bFlashLostFocus;
	INT						m_FlashState;
	BOOL					m_bAutoPause;
};