#include "includes.h"
#include "backend/Renderer/Renderer.h"
#include "backend/Menu/Menu.h"
DWORD dwOld_D3DRS_COLORWRITEENABLE;
IDirect3DVertexDeclaration9* vertDec;
IDirect3DVertexShader9* vertShader;

HRESULT __stdcall Hooks::Present( IDirect3DDevice9* pDevice, RECT* pRect1, const RECT* pRect2, HWND hWnd, const RGNDATA* pRGNData )
{
	IDirect3DVertexDeclaration9* vert_dec;
	if ( pDevice->GetVertexDeclaration( &vert_dec ) )
		return g_hooks.m_device.GetOldMethod<decltype( &Present )>( 17 )( pDevice, pRect1, pRect2, hWnd, pRGNData );

	IDirect3DVertexShader9* vert_shader;
	if ( pDevice->GetVertexShader( &vert_shader ) )
		return g_hooks.m_device.GetOldMethod<decltype( &Present )>( 17 )( pDevice, pRect1, pRect2, hWnd, pRGNData );


	// im not sue
	IDirect3DStateBlock9* PixelState = NULL;
	IDirect3DVertexDeclaration9* vertDec;
	IDirect3DVertexShader9* vertShader;

	pDevice->CreateStateBlock( D3DSBT_PIXELSTATE, &PixelState );
	pDevice->GetVertexDeclaration( &vertDec );
	pDevice->GetVertexShader( &vertShader );

	static auto wanted_ret_address = _ReturnAddress( );
	if ( _ReturnAddress( ) == wanted_ret_address )
	{


		Render::Draw->Init( pDevice );
		Render::Draw->Reset( );

		CMenu::get( ).Initialize( );
		CMenu::get( ).Draw( );
	}

	PixelState->Apply( );
	PixelState->Release( );

	pDevice->SetVertexDeclaration( vertDec );
	pDevice->SetVertexShader( vertShader );


	return g_hooks.m_device.GetOldMethod<decltype( &Present )>( 17 )( pDevice, pRect1, pRect2, hWnd, pRGNData );
}

HRESULT __stdcall Hooks::Reset( IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresentParameters )
{
	auto result = g_hooks.m_device.GetOldMethod<decltype( &Reset )>( 16 )( pDevice, pPresentParameters );
	return result;
}

LRESULT WINAPI Hooks::WndProc( HWND wnd, uint32_t msg, WPARAM wp, LPARAM lp ) {
	auto g = IdaLovesMe::Globals::Gui_Ctx;

	if ( msg == WM_DESTROY )
		PostQuitMessage( 0 );

	if ( msg == WM_KEYDOWN )
		if ( IdaLovesMe::Globals::Gui_Ctx )
			if ( wp == CMenu::get( ).Menu_key && ( g->MenuAlpha == 255 || g->MenuAlpha == 0 ) )
				CMenu::get( ).SetMenuOpened( !CMenu::get( ).IsMenuOpened( ) );

	if ( msg == WM_MOUSEWHEEL ) {
		if ( g )
			g->MouseWheel += GET_WHEEL_DELTA_WPARAM( wp ) > 0 ? +1.0f : -1.0f;
	}

	if ( CMenu::get( ).IsMenuOpened( ) ) {
		switch ( msg ) {
		case WM_LBUTTONDOWN:
			g_input.SetDown( VK_LBUTTON );
			break;

		case WM_LBUTTONUP:
			g_input.SetUp( VK_LBUTTON );
			break;

		case WM_RBUTTONDOWN:
			g_input.SetDown( VK_RBUTTON );
			break;

		case WM_RBUTTONUP:
			g_input.SetUp( VK_RBUTTON );
			break;

		case WM_MBUTTONDOWN:
			g_input.SetDown( VK_MBUTTON );
			break;

		case WM_MBUTTONUP:
			g_input.SetUp( VK_MBUTTON );
			break;

		case WM_XBUTTONDOWN:
			if ( GET_XBUTTON_WPARAM( wp ) == XBUTTON1 )
				g_input.SetDown( VK_XBUTTON1 );

			else if ( GET_XBUTTON_WPARAM( wp ) == XBUTTON2 )
				g_input.SetDown( VK_XBUTTON2 );

			break;

		case WM_XBUTTONUP:
			if ( GET_XBUTTON_WPARAM( wp ) == XBUTTON1 )
				g_input.SetUp( VK_XBUTTON1 );

			else if ( GET_XBUTTON_WPARAM( wp ) == XBUTTON2 )
				g_input.SetUp( VK_XBUTTON2 );

			break;

		case WM_KEYDOWN:
			if ( ( size_t )wp < g_input.m_keys.size( ) )
				g_input.SetDown( wp );

			break;

		case WM_KEYUP:
			if ( ( size_t )wp < g_input.m_keys.size( ) )
				g_input.SetUp( wp );

			break;

		case WM_SYSKEYDOWN:
			if ( wp == VK_MENU )
				g_input.SetDown( VK_MENU );

			break;

		case WM_SYSKEYUP:
			if ( wp == VK_MENU )
				g_input.SetUp( VK_MENU );

			break;

		case WM_CHAR:
			switch ( wp ) {
			case VK_BACK:
				if ( !g_input.m_buffer.empty( ) )
					g_input.m_buffer.pop_back( );
				break;

			case VK_ESCAPE:
			case VK_TAB:
			case VK_RETURN:
				break;

			default:
				if ( std::isdigit( static_cast< char >( wp ) ) )
					g_input.m_buffer += static_cast< char >( wp );

				break;
			}

			break;

		default:
			break;
		}


		if ( ( wp & VK_LBUTTON || wp & VK_RBUTTON ) && IdaLovesMe::ui::IsInsideWindow( ) )
			return true;

		if ( g && g->AwaitingInput )
			return true;
	}

	return g_winapi.CallWindowProcA( g_hooks.m_old_wndproc, wnd, msg, wp, lp );
}