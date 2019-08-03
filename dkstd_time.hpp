// author:      Khiêm Đoàn Hoà (KhiemDH)
// github:      https://github.com/khiemdoan/dkstd
// created:     2017-10-14
// modified:    2019-08-03

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
        class timedelta
        {
        public:
            timedelta(short days = 0, short hours = 0, short minutes = 0, short seconds = 0);
            short days = 0, hours = 0, minutes = 0, seconds = 0;
        };

        std::time_t get_time() noexcept;
        std::tm get_localtime() noexcept;
        std::tm get_localtime(std::time_t time) noexcept;

        std::wstring get_time_as_string(std::wstring format = L"%Y-%m-%dT%H:%M:%S");
        std::wstring get_time_as_filename(std::wstring name = L"", std::wstring ext = L"");
        std::wstring time_to_string(std::time_t time, std::wstring format = L"%Y-%m-%dT%H:%M:%S");
        std::time_t string_to_time(std::wstring str, std::wstring format = L"%Y-%m-%dT%H:%M:%S");

        void sleep_for_milliseconds(unsigned long milliseconds);
        void sleep_for_seconds(unsigned long seconds);
        void sleep_for_minutes(unsigned long minutes);
        void sleep_for_hours(unsigned long hours);

        std::time_t add_time(std::time_t time, timedelta delta) noexcept;

#ifdef _WIN32
        std::time_t filetime_to_timet(const FILETIME& ft) noexcept;
#endif
    }
}

// KhiemDH - 2019-07-05
inline dkstd::time::timedelta::timedelta(short days, short hours, short minutes, short seconds)
{
    this->days = days;
    this->hours = hours;
    this->minutes = minutes;
    this->seconds = seconds;
}

// Get current calendar time
// KhiemDH - 2017-10-14
inline std::time_t dkstd::time::get_time() noexcept
{
    return std::time(nullptr);;
}

// Get current calendar time as std::tm type
// KhiemDH - 2017-10-14
inline std::tm dkstd::time::get_localtime() noexcept
{
    const std::time_t time = dkstd::time::get_time();
    return dkstd::time::get_localtime(time);
}

// Convert std::time_t to std::tm
// KhiemDH - 2019-08-03
inline std::tm dkstd::time::get_localtime(std::time_t time) noexcept
{
    std::tm tm = { 0 };
    tm.tm_mday = 1;
#ifdef _WIN32
    localtime_s(&tm, &time);
#else
    localtime_r(&time, &tm);
#endif

    if (errno != 0)
    {
        tm = { 0 };
        tm.tm_mday = 1;
    }

    return tm;
}

// Use custom format to get string time
// KhiemDH - 2017-10-14
inline std::wstring dkstd::time::get_time_as_string(std::wstring format)
{
    const std::time_t time = dkstd::time::get_time();
    return dkstd::time::time_to_string(time, format);
}

// Get string to name a file with time
// KhiemDH - 2017-10-14
inline std::wstring dkstd::time::get_time_as_filename(std::wstring name, std::wstring ext)
{
    std::wstring format = L"%Y_%m_%d_%H_%M_%S";
    if (name.length())
        format = name + L"_" + format;
    if (ext.length())
        format = format + L"." + ext;
    return dkstd::time::get_time_as_string(format);
}

// format time to string
// KhiemDH - 2019-08-03
inline std::wstring dkstd::time::time_to_string(std::time_t time, std::wstring format)
{
    std::tm tm = get_localtime(time);
    std::wstringstream ss;
    ss << std::put_time(&tm, format.c_str());
    return ss.str();
}

// convert std::string to std::time_t
// return -1 if fail
// KhiemDH - 2017-10-16
inline std::time_t dkstd::time::string_to_time(std::wstring str, std::wstring format)
{
    std::wstringstream ss;
    std::tm tm_buf = { 0 };
    ss << str;
    ss >> std::get_time(&tm_buf, format.c_str());
    return std::mktime(&tm_buf);
}

// sleep thread in milliseconds
// KhiemDH - 2017-10-14
inline void dkstd::time::sleep_for_milliseconds(unsigned long milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// sleep thread in seconds
// KhiemDH - 2017-10-14
inline void dkstd::time::sleep_for_seconds(unsigned long seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

// sleep thread in minutes
// KhiemDH - 2017-10-14
inline void dkstd::time::sleep_for_minutes(unsigned long minutes)
{
    std::this_thread::sleep_for(std::chrono::minutes(minutes));
}

// sleep thread in hours
// KhiemDH - 2019-06-27
inline void dkstd::time::sleep_for_hours(unsigned long hours)
{
    std::this_thread::sleep_for(std::chrono::hours(hours));
}

// KhiemDH - 2019-07-05
// Add or subtract time
// std::time_t now = dkstd::time::get_time();
// dkstd::time::timedelta delta = dkstd::time::timedelta(-1);
// std::time_t yesterday = dkstd::time::add_time(now, delta);
inline std::time_t dkstd::time::add_time(std::time_t time, timedelta delta) noexcept
{
    std::time_t delta_in_number = (std::time_t)delta.days * 24 * 60 * 60;
    delta_in_number += (std::time_t)delta.hours * 60 * 60;
    delta_in_number += (std::time_t)delta.minutes * 60;
    delta_in_number += delta.seconds;
    return time + delta_in_number;
}

#ifdef _WIN32
// convert FILETIME type to time_t type
// use for Windows only
// KhiemDH - 2017-10-14
inline std::time_t dkstd::time::filetime_to_timet(const FILETIME & ft) noexcept
{
    ULARGE_INTEGER ull = { 0 };
    ull.LowPart = ft.dwLowDateTime;
    ull.HighPart = ft.dwHighDateTime;
    return ull.QuadPart / 10000000ULL - 11644473600ULL;
}
#endif
