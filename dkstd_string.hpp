// author:      Khiêm Đoàn Hoà
// created:     2016-03-19
// modified:    2017-05-03
// https://github.com/khiemdoancrazy/dkstd

#pragma once

#include "codecvt"
#include "algorithm"
#include "memory"
#include "stdexcept"
#include "locale"
#include "vector"
#include "list"
#include "numeric"

namespace dkstd
{
    std::wstring s2ws(std::string str);
    std::string ws2s(std::wstring wstr);

    namespace string
    {
        template<typename ...Args>
        std::string format(const std::string& format, Args ...args);
        template<typename ...Args>
        std::wstring format(const std::wstring& format, Args ...args);

        template<typename charT>
        std::basic_string<charT> to_lower(std::basic_string<charT> sInput);
        template<typename charT>
        std::basic_string<charT> to_lower(charT* pInput);

        template<typename charT>
        std::basic_string<charT> to_upper(std::basic_string<charT> sInput);
        template<typename charT>
        std::basic_string<charT> to_upper(charT* pInput);

        template<typename charT>
        int icompare(std::basic_string<charT> sL, std::basic_string<charT> sR);
        template<typename charT>
        int icompare(charT* pL, charT* pR);

        template<typename charT>
        std::size_t ifind(std::basic_string<charT> sStr, std::basic_string<charT> sSubStr, std::size_t pos = 0);
        template<typename charT>
        std::size_t ifind(charT* pStr, charT* pSubStr, std::size_t pos = 0);

        template<typename charT>
        std::size_t irfind(std::basic_string<charT> sStr, std::basic_string<charT> sSubStr, std::size_t pos = std::basic_string<charT>::npos);
        template<typename charT>
        std::size_t irfind(charT* pStr, charT* pSubStr, std::size_t pos = std::basic_string<charT>::npos);

		template<typename charT>
		std::basic_string<charT> join(const std::vector<std::basic_string<charT>>& vector, const std::basic_string<charT>& delim);
		template<typename charT>
		std::basic_string<charT> join(const std::list<std::basic_string<charT>>& list, const std::basic_string<charT>& delim);
    }
}

// convert std::string to std::wstring
// KhiemDH - 2016-08-14
inline std::wstring dkstd::s2ws(std::string str)
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    std::wstring sOutput;
    try {
        sOutput = converter.from_bytes(str);
    }
    catch (const std::range_error e) {}
    return sOutput;
}

// convert std::wstring to std::string
// KhiemDH - 2016-08-14
inline std::string dkstd::ws2s(std::wstring wstr)
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    std::string sOutput;
    try {
        sOutput = converter.to_bytes(wstr);
    }
    catch (const std::range_error e) {}
    return sOutput;
}

// format string
// KhiemDH - 2017-04-30
template<typename ...Args>
std::string dkstd::string::format(const std::string & format, Args ...args)
{
    std::string sReturn;
    int size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;      // Extra space for '\0'
    std::unique_ptr<char[]> buf = std::make_unique<char[]>(size);
    size = std::snprintf(buf.get(), size, format.c_str(), args...);
    if (size > 0)
    {
        sReturn = std::string(buf.get(), size);
    }
    return sReturn;
}

// format string
// KhiemDH - 2017-04-30
template<typename ...Args>
std::wstring dkstd::string::format(const std::wstring & format, Args ...args)
{
    std::wstring sReturn;
    int size = std::swprintf(nullptr, 0, format.c_str(), args...) + 1;      // Extra space for '\0'
    std::unique_ptr<wchar_t[]> buf = std::make_unique<wchar_t[]>(size);
    size = std::swprintf(buf.get(), size, format.c_str(), args...);
    if (size > 0)
    {
        sReturn = std::wstring(buf.get(), size);
    }
    return sReturn;
}

// convert to lower string
// KhiemDH - 2016-07-13
template<typename charT>
std::basic_string<charT> dkstd::string::to_lower(std::basic_string<charT> sInput)
{
    std::basic_string<charT> sOutput;
    sOutput.resize(sInput.size());
    std::transform(sInput.begin(), sInput.end(), sOutput.begin(), ::tolower);
    return sOutput;
}

// convert to lower string
// KhiemDH - 2016-08-15
template<typename charT>
std::basic_string<charT> dkstd::string::to_lower(charT * pInput)
{
    std::basic_string<charT> sInput(pInput);
    return dkstd::string::to_lower(sInput);
}

// convert to upper string
// KhiemDH - 2016-07-13
template<typename charT>
std::basic_string<charT> dkstd::string::to_upper(std::basic_string<charT> sInput)
{
    std::basic_string<charT> sOutput;
    sOutput.resize(sInput.size());
    std::transform(sInput.begin(), sInput.end(), sOutput.begin(), ::toupper);
    return sOutput;
}

// convert to upper string
// KhiemDH - 2016-08-15
template<typename charT>
std::basic_string<charT> dkstd::string::to_upper(charT * pInput)
{
    std::basic_string<charT> sInput(pInput);
    return dkstd::string::to_upper(sInput);
}

// case insensitive compare string
// KhiemDH - 2016-09-10
template<typename charT>
int dkstd::string::icompare(std::basic_string<charT> sL, std::basic_string<charT> sR)
{
    sL = dkstd::string::to_lower(sL);
    sR = dkstd::string::to_lower(sR);
    return sL.compare(sR);
}

// case insensitive compare string
// KhiemDH - 2016-09-10
template<typename charT>
int dkstd::string::icompare(charT * pL, charT * pR)
{
    std::basic_string<charT> sL(pL);
    std::basic_string<charT> sR(pR);
    return dkstd::string::icompare(sL, sR);
}

// case insensitive finds the first substring
// KhiemDH - 2016-10-29
template<typename charT>
std::size_t dkstd::string::ifind(std::basic_string<charT> sStr, std::basic_string<charT> sSubStr, std::size_t pos)
{
    sStr = dkstd::string::to_lower(sStr);
    sSubStr = dkstd::string::to_lower(sSubStr);
    return sStr.find(sSubStr, pos);
}

// case insensitive finds the first substring
// KhiemDH - 2016-10-29
template<typename charT>
std::size_t dkstd::string::ifind(charT * pStr, charT * pSubStr, std::size_t pos)
{
    std::basic_string<charT> sStr(pStr);
    std::basic_string<charT> sSubStr(pSubStr);
    return dkstd::string::ifind(sStr, sSubStr, pos);
}

// case insensitive finds the last substring
// KhiemDH - 2016-10-29
template<typename charT>
std::size_t dkstd::string::irfind(std::basic_string<charT> sStr, std::basic_string<charT> sSubStr, std::size_t pos)
{
    sStr = dkstd::string::to_lower(sStr);
    sSubStr = dkstd::string::to_lower(sSubStr);
    return sStr.rfind(sSubStr, pos);
}

// case insensitive finds the last substring
// KhiemDH - 2016-10-29
template<typename charT>
std::size_t dkstd::string::irfind(charT * pStr, charT * pSubStr, std::size_t pos)
{
    std::basic_string<charT> sStr(pStr);
    std::basic_string<charT> sSubStr(pSubStr);
    return dkstd::string::irfind(sStr, sSubStr, pos);
}

// join a vector of string to string
// KhiemDH - 2016-05-03
template<typename charT>
std::basic_string<charT> dkstd::string::join(const std::vector<std::basic_string<charT>>& vector, const std::basic_string<charT>& delim)
{
    if (vector.size() == 0)
        return std::basic_string<charT>();

    return std::accumulate(
        std::next(vector.begin()),
        vector.end(),
        vector[0],
        [&](std::basic_string<charT> a, std::basic_string<charT> b)
        {
            return a + delim + b;
        }
    );
}

// join a list of string to string
// KhiemDH - 2016-05-03
template<typename charT>
std::basic_string<charT> dkstd::string::join(const std::list<std::basic_string<charT>>& list, const std::basic_string<charT>& delim)
{
    if (list.size() == 0)
        return std::basic_string<charT>();

    return std::accumulate(
        std::next(list.begin()),
        list.end(),
        *list.begin(),
        [&](std::basic_string<charT> a, std::basic_string<charT> b)
        {
            return a + delim + b;
        }
    );
}
