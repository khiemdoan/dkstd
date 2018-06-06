// author:      Khiêm Đoàn Hoà (KhiemDH)
// github:      https://github.com/khiemdoan/dkstd
// created:     2016-03-19
// modified:    2018-06-06

#pragma once

#include "codecvt"
#include "algorithm"
#include "memory"
#include "stdexcept"
#include "locale"
#include "vector"
#include "list"
#include "numeric"
#include "sstream"

namespace dkstd
{
    std::wstring s2ws(std::string str);
    std::string ws2s(std::wstring wstr);

    namespace string
    {
        std::wstring s2ws(std::string str);
        std::string ws2s(std::wstring wstr);

        template<typename ...Args>
        std::string format(const std::string& format, Args ...args);
        template<typename ...Args>
        std::wstring format(const std::wstring& format, Args ...args);

        template<typename char_t>
        std::basic_string<char_t> to_lower(const std::basic_string<char_t>& sInput);
        template<typename char_t>
        std::basic_string<char_t> to_lower(const char_t* pInput);

        template<typename char_t>
        std::basic_string<char_t> to_upper(const std::basic_string<char_t> sInput);
        template<typename char_t>
        std::basic_string<char_t> to_upper(const char_t* pInput);

        template<typename char_t>
        int icompare(const std::basic_string<char_t> sL, const std::basic_string<char_t> sR);
        template<typename char_t>
        int icompare(const char_t* pL, const char_t* pR);

        template<typename char_t>
        std::size_t ifind(const std::basic_string<char_t> sStr, const std::basic_string<char_t> sSubStr, const std::size_t pos = 0);
        template<typename char_t>
        std::size_t ifind(const char_t* pStr, const char_t* pSubStr, const std::size_t pos = 0);

        template<typename char_t>
        std::size_t irfind(const std::basic_string<char_t> sStr, const std::basic_string<char_t> sSubStr, const std::size_t pos = std::basic_string<char_t>::npos);
        template<typename char_t>
        std::size_t irfind(const char_t* pStr, const char_t* pSubStr, const std::size_t pos = std::basic_string<char_t>::npos);

        template<typename char_t>
        std::basic_string<char_t> join(const std::vector<std::basic_string<char_t>>& vector, const std::basic_string<char_t>& delim);
        template<typename char_t>
        std::basic_string<char_t> join(const std::list<std::basic_string<char_t>>& list, const std::basic_string<char_t>& delim);

        template<typename char_t>
        std::vector<std::basic_string<char_t>> split(const std::basic_string<char_t>& s, const char_t delim);

        template<typename char_t>
        std::basic_string<char_t> ltrim(const std::basic_string<char_t>& str, const std::basic_string<char_t>& chars);
        template<typename char_t>
        std::basic_string<char_t> rtrim(const std::basic_string<char_t>& str, const std::basic_string<char_t>& chars);
        template<typename char_t>
        std::basic_string<char_t> trim(const std::basic_string<char_t>& str, const std::basic_string<char_t>& chars);

        template<typename char_t>
        std::basic_string<char_t> replace(std::basic_string<char_t> str, std::basic_string<char_t> old_value, std::basic_string<char_t> new_value);
        template<typename char_t>
        std::basic_string<char_t> replace(char_t *str, char_t *old_value, char_t *new_value);

        template<typename char_t>
        std::basic_string<char_t> replace_all(std::basic_string<char_t> str, std::basic_string<char_t> old_value, std::basic_string<char_t> new_value);
        template<typename char_t>
        std::basic_string<char_t> replace_all(char_t *str, char_t *old_value, char_t *new_value);
    }
}

// convert std::string to std::wstring
// KhiemDH - 2017-10-14
inline std::wstring dkstd::s2ws(std::string str)
{
    return dkstd::string::s2ws(str);
}

// convert std::wstring to std::string
// KhiemDH - 2017-10-14
inline std::string dkstd::ws2s(std::wstring wstr)
{
    return dkstd::string::ws2s(wstr);
}

// convert std::string to std::wstring
// KhiemDH - 2016-08-14
inline std::wstring dkstd::string::s2ws(std::string str)
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    std::wstring sOutput;
    try {
        sOutput = converter.from_bytes(str);
    }
    catch (const std::range_error &e) {}
    return sOutput;
}

// convert std::wstring to std::string
// KhiemDH - 2016-08-14
inline std::string dkstd::string::ws2s(std::wstring wstr)
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    std::string sOutput;
    try {
        sOutput = converter.to_bytes(wstr);
    }
    catch (const std::range_error &e) {}
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
template<typename char_t>
std::basic_string<char_t> dkstd::string::to_lower(const std::basic_string<char_t>& sInput)
{
    std::basic_string<char_t> sOutput;
    sOutput.resize(sInput.size());
    std::transform(sInput.begin(), sInput.end(), sOutput.begin(), ::tolower);
    return sOutput;
}

// convert to lower string
// KhiemDH - 2016-08-15
template<typename char_t>
std::basic_string<char_t> dkstd::string::to_lower(const char_t * pInput)
{
    std::basic_string<char_t> sInput(pInput);
    return dkstd::string::to_lower(sInput);
}

// convert to upper string
// KhiemDH - 2016-07-13
template<typename char_t>
std::basic_string<char_t> dkstd::string::to_upper(const std::basic_string<char_t> sInput)
{
    std::basic_string<char_t> sOutput;
    sOutput.resize(sInput.size());
    std::transform(sInput.begin(), sInput.end(), sOutput.begin(), ::toupper);
    return sOutput;
}

// convert to upper string
// KhiemDH - 2016-08-15
template<typename char_t>
std::basic_string<char_t> dkstd::string::to_upper(const char_t * pInput)
{
    std::basic_string<char_t> sInput(pInput);
    return dkstd::string::to_upper(sInput);
}

// case insensitive compare string
// KhiemDH - 2016-09-10
template<typename char_t>
int dkstd::string::icompare(const std::basic_string<char_t> sL, const std::basic_string<char_t> sR)
{
    std::basic_string<char_t> lowerLeftString = dkstd::string::to_lower(sL);
    std::basic_string<char_t> lowerRightString = dkstd::string::to_lower(sR);
    return lowerLeftString.compare(lowerRightString);
}

// case insensitive compare string
// KhiemDH - 2016-09-10
template<typename char_t>
int dkstd::string::icompare(const char_t * pL, const char_t * pR)
{
    std::basic_string<char_t> sL(pL);
    std::basic_string<char_t> sR(pR);
    return dkstd::string::icompare(sL, sR);
}

// case insensitive finds the first substring
// KhiemDH - 2016-10-29
template<typename char_t>
std::size_t dkstd::string::ifind(std::basic_string<char_t> sStr, std::basic_string<char_t> sSubStr, std::size_t pos)
{
    sStr = dkstd::string::to_lower(sStr);
    sSubStr = dkstd::string::to_lower(sSubStr);
    return sStr.find(sSubStr, pos);
}

// case insensitive finds the first substring
// KhiemDH - 2016-10-29
template<typename char_t>
std::size_t dkstd::string::ifind(const char_t * pStr, const char_t * pSubStr, const std::size_t pos)
{
    std::basic_string<char_t> sStr(pStr);
    std::basic_string<char_t> sSubStr(pSubStr);
    return dkstd::string::ifind(sStr, sSubStr, pos);
}

// case insensitive finds the last substring
// KhiemDH - 2016-10-29
template<typename char_t>
std::size_t dkstd::string::irfind(std::basic_string<char_t> sStr, std::basic_string<char_t> sSubStr, std::size_t pos)
{
    sStr = dkstd::string::to_lower(sStr);
    sSubStr = dkstd::string::to_lower(sSubStr);
    return sStr.rfind(sSubStr, pos);
}

// case insensitive finds the last substring
// KhiemDH - 2016-10-29
template<typename char_t>
std::size_t dkstd::string::irfind(const char_t * pStr, const char_t * pSubStr, const std::size_t pos)
{
    std::basic_string<char_t> sStr(pStr);
    std::basic_string<char_t> sSubStr(pSubStr);
    return dkstd::string::irfind(sStr, sSubStr, pos);
}

// join a vector of string to string
// KhiemDH - 2016-05-03
template<typename char_t>
std::basic_string<char_t> dkstd::string::join(const std::vector<std::basic_string<char_t>>& vector, const std::basic_string<char_t>& delim)
{
    if (vector.size() == 0)
        return std::basic_string<char_t>();

    return std::accumulate(
        std::next(vector.begin()),
        vector.end(),
        vector[0],
        [&](std::basic_string<char_t> a, std::basic_string<char_t> b)
        {
            return a + delim + b;
        }
    );
}

// join a list of string to string
// KhiemDH - 2016-05-03
template<typename char_t>
std::basic_string<char_t> dkstd::string::join(const std::list<std::basic_string<char_t>>& list, const std::basic_string<char_t>& delim)
{
    if (list.size() == 0)
        return std::basic_string<char_t>();

    return std::accumulate(
        std::next(list.begin()),
        list.end(),
        *list.begin(),
        [&](std::basic_string<char_t> a, std::basic_string<char_t> b)
        {
            return a + delim + b;
        }
    );
}

// split string to vector of string
// KhiemDH - 2017-09-22
template<typename char_t>
std::vector<std::basic_string<char_t>> dkstd::string::split(const std::basic_string<char_t>& s, const char_t delim)
{
    std::vector<std::basic_string<char_t>> v;
    std::basic_stringstream<char_t> ss;
    ss.str(s);
    std::basic_string<char_t> item;
    while (std::getline(ss, item, delim))
    {
        v.push_back(item);
    }
    return v;
}

// KhiemDH - 2017-09-23
template<typename char_t>
std::basic_string<char_t> dkstd::string::ltrim(const std::basic_string<char_t>& str, const std::basic_string<char_t>& chars)
{
    typename std::basic_string<char_t>::size_type npos = std::basic_string<char_t>::npos;
    typename std::basic_string<char_t>::size_type begin_trim = str.find_first_of(chars);
    typename std::basic_string<char_t>::size_type begin_content = str.find_first_not_of(chars);
    if (begin_trim == npos)
        return str;
    if (begin_content == npos)
        return std::basic_string<char_t>();
    typename std::basic_string<char_t>::size_type size = str.length();
    return str.substr(begin_content, size - begin_content);
}

// KhiemDH - 2017-09-23
template<typename char_t>
std::basic_string<char_t> dkstd::string::rtrim(const std::basic_string<char_t>& str, const std::basic_string<char_t>& chars)
{
    typename std::basic_string<char_t>::size_type npos = std::basic_string<char_t>::npos;
    typename std::basic_string<char_t>::size_type end_trim = str.find_last_of(chars);
    typename std::basic_string<char_t>::size_type end_content = str.find_last_not_of(chars);
    if (end_trim == npos)
        return str;
    if (end_content == npos)
        return std::basic_string<char_t>();
    return str.substr(0, end_content + 1);
}

// KhiemDH - 2017-09-23
template<typename char_t>
std::basic_string<char_t> dkstd::string::trim(const std::basic_string<char_t>& str, const std::basic_string<char_t>& chars)
{
    return rtrim(ltrim(str, chars), chars);
}

// KhiemDH - 2018-06-06
template<typename char_t>
std::basic_string<char_t> dkstd::string::replace(std::basic_string<char_t> str, std::basic_string<char_t> old_value, std::basic_string<char_t> new_value)
{
    if (old_value.empty())
        return str;
    typename std::basic_string<char_t>::size_type start_pos = str.find(old_value);
    if (start_pos == std::basic_string<char_t>::npos)
        return str;
    return str.replace(start_pos, old_value.length(), new_value);
}

// KhiemDH - 2018-06-06
template<typename char_t>
std::basic_string<char_t> dkstd::string::replace(char_t *str, char_t *old_value, char_t *new_value)
{
    return dkstd::string::replace(std::basic_string<char_t>(str), std::basic_string<char_t>(old_value), std::basic_string<char_t>(new_value));
}

// KhiemDH - 2018-06-06
template<typename char_t>
std::basic_string<char_t> dkstd::string::replace_all(std::basic_string<char_t> str, std::basic_string<char_t> old_value, std::basic_string<char_t> new_value)
{
    if (old_value.empty())
        return str;
    typename std::basic_string<char_t>::size_type start_pos = str.find(old_value, 0);
    for (; start_pos != std::basic_string<char_t>::npos; start_pos = str.find(old_value, start_pos))
    {
        str = str.replace(start_pos, old_value.length(), new_value);
    }
    return str;
}

// KhiemDH - 2018-06-06
template<typename char_t>
std::basic_string<char_t> dkstd::string::replace_all(char_t *str, char_t *old_value, char_t *new_value)
{
    return dkstd::string::replace_all(std::basic_string<char_t>(str), std::basic_string<char_t>(old_value), std::basic_string<char_t>(new_value));
}