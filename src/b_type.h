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
#ifndef _B_TYPE_H_
#define _B_TYPE_H_
/*============================================================================*/
#include <wchar.h>
#include "b_define.h"
/*============================================================================*/
/* bool                                                                       */
/*============================================================================*/
typedef enum {bfalse, btrue} bbool;
/*============================================================================*/
/* ����������� ����.                                                          */
/*============================================================================*/
typedef char    bbyte ;
typedef short   bshort;
typedef int     bint  ;

typedef unsigned char    bubyte ;
typedef unsigned short   bushort;
typedef unsigned int     buint  ;

typedef double bdouble;
typedef float  bfloat ;
/*============================================================================*/
/* void                                                                       */
/*============================================================================*/
typedef void bvoid;
/*============================================================================*/
/* long                                                                       */
/*============================================================================*/
#ifdef B_VISUAL_STUDIO
typedef __int64          blong ;
typedef unsigned __int64 bulong;
#else
typedef long          blong;
typedef unsigned long bulong;
#endif /* B_VISUAL_STUDIO */
/*============================================================================*/
/* ������.                                                                    */
/*============================================================================*/
#ifdef B_UNICODE
typedef wchar_t bchar;
#else
typedef char    bchar;
#endif /* B_UNICODE */
/*============================================================================*/
#endif /* _B_TYPE_H_ */