#pragma once
#include <string>

class ClipboardControl
{
public:
	enum System
	{
		Unsupported = 0,
		Windows = 1
	};

	ClipboardControl();
	ClipboardControl(System currentSystem);
	~ClipboardControl();

	std::wstring getClipboard();
	bool setClipboard(std::wstring value);

private:
	std::wstring getClipboardWindows();
	bool setClipboardWindows(std::wstring value);

	System mCurrentSystem;
};

