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
#include "b_file.h"
#include "b_log.h"
/*============================================================================*/
#define bLog_Logo \
    L"____    _        _    ____    _        _   _     _         __</br>\
/ __ \\   \\\\      //   / __ \\   \\\\      //  | |   / /       /  \\</br>\
/ /  \\_\\   \\\\    //   / /  \\_\\   \\\\    //   | |  / /       / /\\ \\</br>\
/ /____      \\\\  //   / /____      \\\\  //    | | / /       / /  \\ \\</br>\
 |  ___ \\      \\\\//    |  ___ \\      \\\\//     | |/ /       / /____\\ \\</br>\
  | /   \\ \\      //     | /   \\ \\      //      |   |       / ________ \\</br>\
   \\ \\___/ /     //      \\ \\___/ /     //       | |\\ \\     / /        \\ \\</br>\
     \\_____/    _//        \\_____/    _//        | | \\ \\   / /          \\ \\</br>\
                |_/                   |_/         |_|  \\_\\ /_/            \\_\\"
/*============================================================================*/
bFile *bLog_File = 0;
/*============================================================================*/
/* bLog_Open                                                                  */
/*============================================================================*/
bbool bLog_Open(bchar *_file_name)
{
	bchar      text[1024], time_text[32];
	bint       size                     ;
	time_t     current_time             ;
	struct tm *local_time               ;


	bLog_File = bFile_Open(_file_name, bFile_W);

	if(!bLog_File || !_file_name)
		return bfalse;

	bFile_WriteBOM(bLog_File, bFile_UTF16);
	size = swprintf(text, 1024, L"<html><head><title>6y6yka Engine</title><head>\
			 <body style=\"background-color : SkyBlue\"><center><H1><pre>%s</pre></H1></center><table align=center>",
			 bLog_Logo);

	if(size == -1)
		return bfalse;

	bFile_Write(bLog_File, text, size * sizeof(bchar));

	current_time = time(0);
	local_time = localtime(&current_time);
	wcsftime(time_text, 128, L"Logging started: %x.", local_time);

	bLog_Print(time_text, bLog_Normal);

	return btrue;
}
/*============================================================================*/
/* bLog_Print                                                                 */
/*============================================================================*/
bbool bLog_Print(bchar *_text, bLog_MessageType _type)
{
	bchar      text[1024], time_text[32];
	bint       size;
	bchar     *color;
	time_t     current_time;
	struct tm *local_time;

	if(!bLog_File || !_text)
		return bfalse;
	
	current_time = time(0);
	local_time = localtime(&current_time);
	wcsftime(time_text, 32, L"%H:%M:%S", local_time);

	if(_type == bLog_Normal)
		color = L"LawnGreen";
	else if(_type == bLog_Warning)
		color = L"Gold";
	else
		color = L"FireBrick";

	size = swprintf(text, 1024,
		L"<tr width = 800px style = \"border : 1px solid blue; background-color : %s\">\
		 <td style = \"border : 1px solid blue\" width = 100px align = center>\
		 <font face=\"Courier New\" size=\"5\"><b>%s</b></font></td>\
		<td width = 700px style = \"border : 1px solid blue\">\
		<font size = \"5\" face = \"Courier New\"><b><pre>%s</pre></b></font></td></tr>",
		color,
		time_text,
		_text);

	if(size == -1)
		return bfalse;

	bFile_Write(bLog_File, text, size * sizeof(bchar));

	return btrue;
}
/*============================================================================*/
/* bLog_Close                                                                 */
/*============================================================================*/
bbool bLog_Close()
{
	if(!bLog_File)
		return bfalse;

	bLog_Print(L"Logging ended. Goodbye!", bLog_Normal);

	bFile_Write(bLog_File, L"</table></body></html>",
		        sizeof(L"</table></body></html>") - sizeof(bchar));

	bFile_Close(bLog_File);
	bLog_File = 0;

	return btrue;
}
/*============================================================================*/
/* bLog_Exist                                                                 */
/*============================================================================*/
bbool bLog_Exist()
{
	return bLog_File != 0;
}