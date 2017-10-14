// author:      Khiêm Đoàn Hoà (KhiemDH)
// github:      https://github.com/khiemdoan/dkstd
// created:     2017-10-14
// modified:    2017-10-14

#pragma once

#include "ctime"
#include "string"
#include "iomanip"
#include "sstream"
#include "thread"

#ifdef _WIN32
#   include "windows.h"
#endif

namespace dkstd
{
    namespace time
    {
        std::time_t get_time();
        std::tm get_localtime();
        std::tm get_localtime(std::time_t time);

        std::wstring get_time_as_string(std::wstring format = L"%Y-%m-%dT%H:%M:%S");
        std::wstring get_time_as_filename(std::wstring name = L"", std::wstring ext = L"");
        std::wstring time_to_string(std::time_t time, std::wstring format = L"%Y-%m-%dT%H:%M:%S");

        void sleep_for_milliseconds(unsigned long milliseconds);
        void sleep_for_seconds(unsigned long seconds);
        void sleep_for_minutes(unsigned long minutes);

#ifdef _WIN32
        std::time_t filetime_to_timet(const FILETIME& ft);
#endif
    }
}

// Get current calendar time
// KhiemDH - 2017-10-14
std::time_t dkstd::time::get_time()
{
    std::time_t time = std::time(nullptr);;
    return time;
}

// Get current calendar time as std::tm type
// KhiemDH - 2017-10-14
std::tm dkstd::time::get_localtime()
{
    std::time_t time = dkstd::time::get_time();
    return dkstd::time::get_localtime(time);
}

// Convert std::time_t to std::tm
// KhiemDH - 2017-10-14
std::tm dkstd::time::get_localtime(std::time_t time)
{
    std::tm tm = { 0 };
    localtime_s(&tm, &time);
    return tm;
}

// Use custom format to get string time
// KhiemDH - 2017-10-14
std::wstring dkstd::time::get_time_as_string(std::wstring format)
{
    std::time_t time = dkstd::time::get_time();
    return dkstd::time::time_to_string(time, format);
}

// Get string to name a file with time
// KhiemDH - 2017-10-14
std::wstring dkstd::time::get_time_as_filename(std::wstring name, std::wstring ext)
{
    std::wstring format = L"%Y_%m_%d_%H_%M_%S";
    if (name.length())
        format = name + L"_" + format;
    if (ext.length())
        format = format + L"." + ext;
    return dkstd::time::get_time_as_string(format);
}

// format time to string
// KhiemDH - 2017-10-14
std::wstring dkstd::time::time_to_string(std::time_t time, std::wstring format)
{
    std::tm tm_buf = { 0 };
    std::wstringstream ss;

    localtime_s(&tm_buf, &time);
    ss << std::put_time(&tm_buf, format.c_str());

    return ss.str();
}

// sleep thread in milliseconds
// KhiemDH - 2017-10-14
void dkstd::time::sleep_for_milliseconds(unsigned long milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// sleep thread in seconds
// KhiemDH - 2017-10-14
void dkstd::time::sleep_for_seconds(unsigned long seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

// sleep thread in minutes
// KhiemDH - 2017-10-14
void dkstd::time::sleep_for_minutes(unsigned long minutes)
{
    std::this_thread::sleep_for(std::chrono::minutes(minutes));
}

#ifdef _WIN32
// convert FILETIME type to time_t type
// use for Windows only
// KhiemDH - 2017-10-14
std::time_t dkstd::time::filetime_to_timet(const FILETIME & ft)
{
    ULARGE_INTEGER ull = { 0 };
    ull.LowPart = ft.dwLowDateTime;
    ull.HighPart = ft.dwHighDateTime;
    return ull.QuadPart / 10000000ULL - 11644473600ULL;
}
#endif
