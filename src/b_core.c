/*============================================================================*/
/*     ____    _        _    ____    _        _   _     _         __          */
/*    / __ \   \\      //   / __ \   \\      //  | |   / /       /  \         */
/*   / /  \_\   \\    //   / /  \_\   \\    //   | |  / /       / /\ \        */
/*  / /____      \\  //   / /____      \\  //    | | / /       / /  \ \       */
/*  |  ___ \      \\//    |  ___ \      \\//     | |/ /       / /____\ \      */
/*  | /   \ \      //     | /   \ \      //      |   |       / ________ \     */
/*  \ \___/ /     //      \ \___/ /     //       | |\ \     / /        \ \    */
/*   \_____/    _//        \_____/    _//        | | \ \   / /          \ \   */
/*             |_/                   |_/         |_|  \_\ /_/            \_\  */
/*                                                                            */
/*============================================================================*/
#include "b_render.h"
#include "b_core.h"
/*============================================================================*/
typedef struct
{
	HDC       hdc;
	HWND      hwnd ;
	HGLRC     hglrc;
	HINSTANCE hinst;
} bCore_Window;

/*============================================================================*/
bCore_Window *bCore_CreateWindow();
/*============================================================================*/
LRESULT WINAPI bCore_EventHandler(HWND, UINT, WPARAM, LPARAM);
/*============================================================================*/
bvoid bCore_WindowShow(bCore_Window *_window);
/*============================================================================*/
bvoid bCore_InitGL(bCore_Window *_window);
/*============================================================================*/
bvoid bCore_GetMessages();

/*============================================================================*/
bCore_Window *bCore_MainWindow = 0;
/*============================================================================*/
bbool bCore_DontStopMeNow = btrue;

/*============================================================================*/
bchar *bCore_Init()
{
	if(!bLog_Open(L"6y6yka Log.html"))
		bError(L"Log creation fail :-(");

	bCore_MainWindow = bCore_CreateWindow();

	bCore_InitGL(bCore_MainWindow);

	bCore_WindowShow(bCore_MainWindow);

	return 0;
}
/*============================================================================*/
/* bCore_Run                                                                  */
/*============================================================================*/
bvoid bCore_Run()
{
	// для начала обработаем все сообщения
	bCore_GetMessages();

	SwapBuffers(bCore_MainWindow->hdc);

	bRender_Clear();
}
/*============================================================================*/
bCore_Window *bCore_CreateWindow()
{
	bCore_Window *window;
	WNDCLASS wc;

	window = malloc(sizeof(bCore_Window));
	window->hinst = GetModuleHandle(0);

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)COLOR_GRAYTEXT;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_WARNING);
	wc.hInstance = window->hinst;
	wc.lpfnWndProc = bCore_EventHandler;
	wc.lpszClassName = L"6y6ykaEngine";
	wc.lpszMenuName = 0;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	window->hwnd = CreateWindow(L"6y6ykaEngine", L"Demo", WS_OVERLAPPEDWINDOW, 
							  0, 0, 800, 600, NULL, NULL, window->hinst, NULL);

	return window;
}
/*============================================================================*/
bvoid bCore_WindowShow(bCore_Window *_window)
{
	ShowWindow(_window->hwnd, SW_SHOW);
	UpdateWindow(_window->hwnd);
}
/*============================================================================*/
LRESULT WINAPI bCore_EventHandler(HWND _hwnd, UINT _message, WPARAM _wparam, LPARAM _lparam)
{
	switch(_message)
	{
	case WM_DESTROY:
	case WM_QUIT:
	case WM_CLOSE:
		bCore_DontStopMeNow = bfalse;
		break;

	case WM_SIZE:
		bRender_ResizeScreen(LOWORD(_lparam), HIWORD(_lparam));
		break;

	default:
		return DefWindowProc(_hwnd, _message, _wparam, _lparam);
	}

	return 0;
}
/*============================================================================*/
bvoid bCore_InitGL(bCore_Window *_window)
{
	int PixelFormat;
	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, PFD_TYPE_RGBA,           
		32,              
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		32,               
		0, 0,                 
		PFD_MAIN_PLANE,               
		0, 0, 0, 0                
	};

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_2D);

	_window->hdc = GetDC(_window->hwnd);
    PixelFormat = ChoosePixelFormat(_window->hdc, &pfd);
	SetPixelFormat(_window->hdc, PixelFormat, &pfd);
	_window->hglrc = wglCreateContext(_window->hdc);
	wglMakeCurrent(_window->hdc, _window->hglrc);
}
/*============================================================================*/
bvoid bCore_GetMessages()
{
	MSG msg;

	while(PeekMessage(&msg, bCore_MainWindow->hwnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
/*============================================================================*/
bbool bCore_Stop()
{
	return bCore_DontStopMeNow;
}
/*============================================================================*/
bchar *bCore_Quit()
{
	bLog_Close();
	free(bCore_MainWindow);

	return 0;
}