#include "UtfConverter.h"

	std::string ToUtf8(const std::wstring & wstr)
	{
		std::string res;
		utf8::utf16to8(wstr.begin(), wstr.end(), std::back_inserter(res));
		return res;
	}

	std::string ToUtf8(const wchar_t * str)
	{
		return ToUtf8(std::wstring(str));
	}

	std::wstring FromUtf8(const std::string & str)
	{
		std::wstring res;
		utf8::utf8to16(str.begin(), str.end(), std::back_inserter(res));
		return res;
	}