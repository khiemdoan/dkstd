// author:		Khiêm Đoàn Hoà
// created:		2016-03-19
// modified:	2016-07-27

#ifndef _DKSTD_STRING_
#define _DKSTD_STRING_

#include "string"
#include "codecvt"
#include "algorithm"
#include "memory"

namespace dkstd {

	std::wstring s2ws(std::string str);
	std::string ws2s(std::wstring wstr);

	template<typename ...Args>
	std::string format_string(const std::string& format, Args ...args);
	template<typename ...Args>
	std::wstring format_string(const std::wstring& format, Args ...args);

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

// format string
// KhiemDH - 2016-07-27
template<typename ...Args>
inline std::string dkstd::format_string(const std::string & format, Args ...args)
{
	size_t size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;	// Extra space for '\0'
	std::unique_ptr<char[]> buf(new char[size]);
	std::snprintf(buf.get(), size, format.c_str(), args...);
	return std::string(buf.get(), buf.get() + size - 1);							// We don't want the '\0' inside
}

// format string
// KhiemDH - 2016-07-27
template<typename ...Args>
inline std::wstring dkstd::format_string(const std::wstring & format, Args ...args)
{
	size_t size = std::swprintf(nullptr, 0, format.c_str(), args...) + 1;	// Extra space for '\0'
	std::unique_ptr<wchar_t[]> buf(new wchar_t[size]);
	std::swprintf(buf.get(), size, format.c_str(), args...);
	return std::wstring(buf.get(), buf.get() + size - 1);					// We don't want the '\0' inside
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

#endif // !_DKSTD_STRING_