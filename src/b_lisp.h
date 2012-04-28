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
#ifndef _B_LISP_H_
#define _B_LISP_H_
/*============================================================================*/
#include "b_pch.h"
/*============================================================================*/
enum bLisp_TypeClass
{
	bLisp_IntType,
	bLisp_FloatType,
	bLisp_StringType,
	bLisp_LambdaType,
	bLisp_NativeType,
	bLisp_DataType,
	bLisp_ListType,
	bLisp_VoidType
};
/*============================================================================*/
typedef struct bLisp_Script bLisp_Script;
/*============================================================================*/
bLisp_Script *bLisp_Open(bchar *_code, bchar **_error);
/*============================================================================*/
bLisp_Script *bLisp_OpenFile(bchar *_filename);
/*============================================================================*/
bbool bLisp_WriteFile(bLisp_Script *_script, bchar *_filename);
/*============================================================================*/
bbool bLisp_Close(bLisp_Script *_script);
/*============================================================================*/
bchar *bLisp_Run(bLisp_Script *_script);
/*============================================================================*/
bvoid bLisp_RegisterFunction(bLisp_Script *_script, enum bLisp_TypeClass _rt,
	                         bchar *_name, bvoid *_ptr, buint _arg_num, ...);
/*============================================================================*/
#endif /* _B_LISP_H_ */