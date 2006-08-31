
/* $Id$
 *
 * PROJECT:         ReactOS user32.dll
 * FILE:            lib/user32/windows/clipboard.c
 * PURPOSE:         Input
 * PROGRAMMER:      Casper S. Hornstrup (chorns@users.sourceforge.net)
 * UPDATE HISTORY:
 *      09-05-2001  CSH  Created
 */

/* INCLUDES ******************************************************************/

#include <user32.h>

#include <wine/debug.h>

/* FUNCTIONS *****************************************************************/

/*
 * @implemented
 */
BOOL STDCALL
OpenClipboard(HWND hWndNewOwner)
{
   return NtUserOpenClipboard(hWndNewOwner, 0);
}

/*
 * @implemented
 */
BOOL STDCALL
CloseClipboard(VOID)
{
   return NtUserCloseClipboard();
}

/*
 * @implemented
 */
INT STDCALL
CountClipboardFormats(VOID)
{
   return NtUserCountClipboardFormats();
}

/*
 * @implemented
 */
BOOL STDCALL
EmptyClipboard(VOID)
{
   return NtUserEmptyClipboard();
}

/*
 * @implemented
 */
UINT STDCALL
EnumClipboardFormats(UINT format)
{
   return NtUserEnumClipboardFormats(format);
}

/*
 * @implemented
 */
HANDLE STDCALL
GetClipboardData(UINT uFormat)
{
   return NtUserGetClipboardData(uFormat, 0);
}

/*
 * @implemented
 */
INT STDCALL
GetClipboardFormatNameA(UINT format, LPSTR lpszFormatName, int cchMaxCount)
{
   LPWSTR lpBuffer;
   UNICODE_STRING FormatName;
   INT Length;

   lpBuffer = HEAP_alloc(cchMaxCount * sizeof(WCHAR));
   if (!lpBuffer)
   {
      SetLastError(ERROR_OUTOFMEMORY);
      return 0;
   }

   FormatName.Length = 0;
   FormatName.MaximumLength = cchMaxCount * sizeof(WCHAR);
   FormatName.Buffer = lpBuffer;

   Length = NtUserGetClipboardFormatName(format, &FormatName, cchMaxCount);
   DPRINT("GetClipboardFormatNameA(%x): %S\n", format, lpBuffer);
   HEAP_strcpyWtoA(lpszFormatName, lpBuffer, Length);
   HEAP_free(lpBuffer);
   DPRINT("GetClipboardFormatNameA(%x): returning %s\n", format, lpszFormatName);

   return Length;
}

/*
 * @implemented
 */
INT STDCALL
GetClipboardFormatNameW(UINT format, LPWSTR lpszFormatName, INT cchMaxCount)
{
   UNICODE_STRING FormatName;
   ULONG Ret;

   FormatName.Length = 0;
   FormatName.MaximumLength = cchMaxCount * sizeof(WCHAR);
   FormatName.Buffer = (PWSTR)lpszFormatName;
   Ret = NtUserGetClipboardFormatName(format, &FormatName, cchMaxCount);
   DPRINT("GetClipboardFormatNameW(%x): returning %S\n", format, lpszFormatName);
   return Ret;
}

/*
 * @implemented
 */
HWND STDCALL
GetClipboardOwner(VOID)
{
   return NtUserGetClipboardOwner();
}

/*
 * @implemented
 */
DWORD STDCALL
GetClipboardSequenceNumber(VOID)
{
   return NtUserGetClipboardSequenceNumber();
}

/*
 * @implemented
 */
HWND STDCALL
GetClipboardViewer(VOID)
{
   return NtUserGetClipboardViewer();
}

/*
 * @implemented
 */
HWND STDCALL
GetOpenClipboardWindow(VOID)
{
   return NtUserGetOpenClipboardWindow();
}

/*
 * @implemented
 */
INT STDCALL
GetPriorityClipboardFormat(UINT *paFormatPriorityList, INT cFormats)
{
   return NtUserGetPriorityClipboardFormat(paFormatPriorityList, cFormats);
}

/*
 * @implemented
 */
BOOL STDCALL
IsClipboardFormatAvailable(UINT format)
{
   return NtUserIsClipboardFormatAvailable(format);
}

/*
 * @implemented
 */
UINT STDCALL
RegisterClipboardFormatA(LPCSTR lpszFormat)
{
   ULONG Ret = RegisterWindowMessageA(lpszFormat);
   DPRINT("RegisterClipboardFormatA(%s) - %x\n", lpszFormat, Ret);
   return Ret;
}

/*
 * @implemented
 */
UINT STDCALL
RegisterClipboardFormatW(LPCWSTR lpszFormat)
{
   ULONG Ret = RegisterWindowMessageW(lpszFormat);
   DPRINT("RegisterClipboardFormatW(%S) - %x\n", lpszFormat, Ret);
   return Ret;
}

/*
 * @implemented
 */
HANDLE STDCALL
SetClipboardData(UINT uFormat, HANDLE hMem)
{
   return NtUserSetClipboardData(uFormat, hMem, 0);
}

/*
 * @implemented
 */
HWND STDCALL
SetClipboardViewer(HWND hWndNewViewer)
{
   return NtUserSetClipboardViewer(hWndNewViewer);
}

/*
 * @implemented
 */
BOOL STDCALL
ChangeClipboardChain(HWND hWndRemove, HWND hWndNewNext)
{
   return NtUserChangeClipboardChain(hWndRemove, hWndNewNext);
}
