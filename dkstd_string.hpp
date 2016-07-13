
// author: Khiêm Đoàn Hoà
// created: 2016-03-19
// modified: 2016-07-13

#ifndef _DKSTD_STRING_
#define _DKSTD_STRING_

#include "string"
#include "codecvt"
#include "algorithm"
#include "memory"

namespace dkstd {

	std::wstring s2ws(std::string str);
	std::string ws2s(std::wstring wstr);

	namespace string {

		template<typename charT>
		std::basic_string<charT> to_lower(std::basic_string<charT> sInput);
		template<typename charT>
		std::basic_string<charT> to_lower(charT* pInput);

		template<typename charT>
		std::basic_string<charT> to_upper(std::basic_string<charT> sInput);
		template<typename charT>
		std::basic_string<charT> to_upper(charT* pInput);
	}	
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

// convert to lower string
// KhiemDH - 2016-07-13
template<typename charT>
inline std::basic_string<charT> dkstd::string::to_lower(std::basic_string<charT> sInput)
{
	std::basic_string<charT> sOutput;
	sOutput.resize(sInput.size());
	std::transform(sInput.begin(), sInput.end(), sOutput.begin(), ::tolower);
	return sOutput;
}

// convert to lower string
// KhiemDH - 2016-07-13
template<typename charT>
inline std::basic_string<charT> dkstd::string::to_lower(charT * pInput)
{
	std::basic_string<charT> sInput(pInput);
	std::basic_string<charT> sOutput;
	sOutput.resize(sInput.size());
	std::transform(sInput.begin(), sInput.end(), sOutput.begin(), ::tolower);
	return sOutput;
}

// convert to upper string
// KhiemDH - 2016-07-13
template<typename charT>
inline std::basic_string<charT> dkstd::string::to_upper(std::basic_string<charT> sInput)
{
	std::basic_string<charT> sOutput;
	sOutput.resize(sInput.size());
	std::transform(sInput.begin(), sInput.end(), sOutput.begin(), ::toupper);
	return sOutput;
}

// convert to upper string
// KhiemDH - 2016-07-13
template<typename charT>
inline std::basic_string<charT> dkstd::string::to_upper(charT * pInput)
{
	std::basic_string<charT> sInput(pInput);
	std::basic_string<charT> sOutput;
	sOutput.resize(sInput.size());
	std::transform(sInput.begin(), sInput.end(), sOutput.begin(), ::toupper);
	return sOutput;
}

#endif // !_DK_STRING_H_