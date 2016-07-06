
// author: Khiêm Đoàn Hoà
// created: 2016-03-19
// modified: 2016-07-06

#ifndef _DKSTD_STRING_
#define _DKSTD_STRING_

#include "string"
#include "codecvt"

namespace dkstd {

	// convert std::string to std::wstring
	std::wstring s2ws(std::string str);

	// convert std::wstring to std::string
	std::string ws2s(std::wstring wstr);
}

// convert std::string to std::wstring
// KhiemDH - 2016-07-06
inline std::wstring dkstd::s2ws(std::string str)
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	return converter.from_bytes(str);
}

// convert std::wstring to std::string
// KhiemDH - 2016-07-06
inline std::string dkstd::ws2s(std::wstring wstr)
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	return converter.to_bytes(wstr);
}

#endif // !_DK_STRING_H_