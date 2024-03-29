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
#include "b_core.h"
#include "b_render.h"
#include "b_lisp.h"
/*============================================================================*/
double test(double x, double y)
{
	return x + y;
}
/*============================================================================*/
/* main                                                                       */
/*============================================================================*/
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	bLisp_Script *s;
	bchar *e;

	bCore_Init();
	
	s = bLisp_Open(L"#include \"hello.blisp\"", &e);

	if(!s)
		bError(e);

	bLisp_RegisterFunction(s, bCore_Run, bvoid (*)());
	bLisp_RegisterFunction(s, bCore_Stop, bbool (*)());
	bLisp_RegisterFunction(s, bRender_DrawCube, bvoid (*)());
	
	if(e = bLisp_Run(s))
			MessageBox(0, e, L"runtime", MB_OK);
	
	bLisp_Close(s);

	bCore_Quit();

	_ASSERTE(_CrtCheckMemory());
	_ASSERTE(!_CrtDumpMemoryLeaks());

	return 0;
}