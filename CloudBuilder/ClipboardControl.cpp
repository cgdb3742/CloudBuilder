#include <Windows.h>
#include "ClipboardControl.h"


ClipboardControl::ClipboardControl():
	mCurrentSystem(System::Unsupported)
{
}

ClipboardControl::ClipboardControl(System currentSystem):
	mCurrentSystem(currentSystem)
{
}


ClipboardControl::~ClipboardControl()
{
}

std::wstring ClipboardControl::getClipboard()
{
	switch (mCurrentSystem)
	{
	case System::Windows : return getClipboardWindows();
	}

	return L"ERROR_UNSUPPORTED_SYSTEM";
}

bool ClipboardControl::setClipboard(std::wstring value)
{
	switch (mCurrentSystem)
	{
	case System::Windows: return setClipboardWindows(value);
	}

	return false;
}

//From https://stackoverflow.com/questions/14762456/getclipboarddatacf-text
std::wstring ClipboardControl::getClipboardWindows()
{
	// Try opening the clipboard
	if (!OpenClipboard(nullptr))
	{
		// error
		return L"ERROR_OPEN_CLIPBOARD";
	}

	// Get handle of clipboard object for ANSI text
	HANDLE hData = GetClipboardData(CF_UNICODETEXT);
	if (hData == nullptr)
	{
		// error
		return L"ERROR_GET_CLIPBOARD_DATA";
	}

	// Lock the handle to get the actual text pointer
	wchar_t * pszText = static_cast<wchar_t*>(GlobalLock(hData));
	if (pszText == nullptr)
	{
		// error
		return L"ERROR_GLOBAL_LOCK";
	}

	// Save text in a string class instance
	std::wstring text(pszText);

	// Release the lock
	GlobalUnlock(hData);

	// Release the clipboard
	CloseClipboard();

	return text;
}

//From https://stackoverflow.com/questions/1264137/how-to-copy-string-to-clipboard-in-c
bool ClipboardControl::setClipboardWindows(std::wstring value)
{
	//const size_t len = strlen(value.c_str()) + 1;
	const size_t len = wcslen(value.c_str()) + 1;
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), value.c_str(), len);

	GlobalUnlock(hMem);

	if (!OpenClipboard(0))
	{
		return false;
	}

	EmptyClipboard();
	SetClipboardData(CF_UNICODETEXT, hMem);
	CloseClipboard();

	return true;
}
