#pragma once

std::string ToUtf8(const std::wstring & wstr);
std::string ToUtf8(const wchar_t* str);
std::wstring FromUtf8(const std::string & str);
