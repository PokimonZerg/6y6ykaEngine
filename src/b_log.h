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
#ifndef _B_LOG_H_
#define _B_LOG_H_
/*============================================================================*/
#include "b_pch.h"
/*============================================================================*/
typedef enum
{
	bLog_Normal,
	bLog_Warning,
	bLog_Error
} bLog_MessageType;
/*============================================================================*/
bbool bLog_Open(bchar *_file_name);
/*============================================================================*/
bbool bLog_Print(bchar *_text, bLog_MessageType _type);
/*============================================================================*/
bbool bLog_Close();
/*============================================================================*/
bbool bLog_Exist();
/*============================================================================*/
#endif /* _B_LOG_H_ */