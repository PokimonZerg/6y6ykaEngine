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
#include "b_pch.h"
#include "b_file.h"
/*============================================================================*/
bbool bFile_CheckBOM(bFile *_file, bFile_UnicodeType _type);
/*============================================================================*/
/* bFile                                                                      */
/*============================================================================*/
struct bFile
{
#ifdef B_WINDOWS
	HANDLE file_handle;
#endif /* _B_WINDOWS */
};
/*============================================================================*/
/* bFile_Open                                                                 */
/*============================================================================*/
bFile *bFile_Open(bchar *_name, bFile_Mode _rw)
{
	bFile *file;
	DWORD RW, CR;

	if(_rw == bFile_R) 
		RW = GENERIC_READ;
	else if(_rw == bFile_W)
		RW = GENERIC_WRITE;
	else
		RW = GENERIC_READ | GENERIC_WRITE;

	if(_rw == bFile_R) 
		CR = OPEN_EXISTING;
	else if(_rw == bFile_W)
		CR = CREATE_ALWAYS;
	else
		CR = OPEN_ALWAYS;

	file = malloc(sizeof(bFile));

	file->file_handle = CreateFile
		(
		_name, 
		RW,
		FILE_SHARE_READ,
		NULL,
		CR,
		FILE_ATTRIBUTE_NORMAL,
		NULL 
		);

	if(file->file_handle == INVALID_HANDLE_VALUE)
	{
		bLog_Print(L"Mega file error", bLog_Normal);
		free(file);
		return 0;
	}

	return file;
}
/*============================================================================*/
/* bFile_Read                                                                 */
/*============================================================================*/
bbool bFile_Read (bFile *_file, bvoid *_buffer, buint _size)
{
	buint fake;

	return ReadFile(_file->file_handle, _buffer, _size, &fake, NULL);
}
/*============================================================================*/
/* bFile_ReadText                                                             */
/*============================================================================*/
bchar *bFile_ReadText(bFile *_file, bFile_UnicodeType _type)
{
	bchar *buffer;
	DWORD size, real_size = 0;

	if(!bFile_CheckBOM(_file, _type))
		return 0;

	size = bFile_Size(_file);
	buffer = malloc(size + sizeof(bchar));

	if(!ReadFile(_file->file_handle, buffer, size, &real_size, NULL))
	{
		free(buffer);
		return 0;
	}

	buffer[real_size / sizeof(bchar)] = L'\0';

	return buffer;
}
/*============================================================================*/
/* bFile_Write                                                                */
/*============================================================================*/
bbool bFile_Write(bFile *_file, bvoid *_buffer, buint _size)
{
	buint fake;

	return WriteFile(_file->file_handle, _buffer, _size, &fake, NULL);
}
/*============================================================================*/
/* bFile_WriteBOM                                                             */
/*============================================================================*/
bbool bFile_WriteBOM(bFile *_file, bFile_UnicodeType _type)
{
	bubyte UTF8[3]  = {239, 187, 191};
	bubyte UTF16[2] = {255, 254};
	bubyte UTF32[4] = {255, 254, 0, 0};
	bvoid *buf;
	buint  size;

	if(_type == bFile_UTF8)
	{
		buf  = UTF8;
		size = sizeof(UTF8);
	}
	else if(_type == bFile_UTF16)
	{
		buf = UTF16;
		size = sizeof(UTF16);
	}
	else
	{
		buf = UTF32;
		size = sizeof(UTF32);
	}

	return bFile_Write(_file, buf, size);
}
/*============================================================================*/
/* bFile_Close                                                                */
/*============================================================================*/
bbool bFile_Close(bFile *_file)
{
	CloseHandle(_file->file_handle);
	free(_file);

	return btrue;
}
/*============================================================================*/
/* bFile_Clear                                                                */
/*============================================================================*/
bbool bFile_Clear(bFile *_file)
{
	return SetEndOfFile(_file->file_handle);
}
/*============================================================================*/
/* bFile_Size                                                                 */
/*============================================================================*/
buint bFile_Size(bFile *_file)
{
	return GetFileSize(_file->file_handle, NULL);
}
/*============================================================================*/
/* bFile_CheckBOM                                                             */
/*============================================================================*/
bbool bFile_CheckBOM(bFile *_file, bFile_UnicodeType _type)
{
	bubyte UTF8 [3] = {239, 187, 191 };
	bubyte UTF16[2] = {255, 254      };
	bubyte UTF32[4] = {255, 254, 0, 0};
	bubyte buffer[4];

	if(_type == bFile_UTF8)
	{
		if(!bFile_Read(_file, buffer, sizeof(UTF8)))
			return bfalse;
		if(memcmp(UTF8, buffer, sizeof(UTF8)) == 0)
			return btrue;
	}
	
	if(_type == bFile_UTF16)
	{
		if(!bFile_Read(_file, buffer, sizeof(UTF16)))
			return bfalse;
		if(memcmp(UTF16, buffer, sizeof(UTF16)) == 0)
			return btrue;
	}

	if(_type == bFile_UTF32)
	{
		if(!bFile_Read(_file, buffer, sizeof(UTF32)))
			return bfalse;
		if(memcmp(UTF32, buffer, sizeof(UTF32)) == 0)
			return btrue;
	}

	return bfalse;
}