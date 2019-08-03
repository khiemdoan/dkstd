// author:      Khiêm Đoàn Hoà (KhiemDH)
// github:      https://github.com/khiemdoan/dkstd
// created:     2019-07-30
// modified:    2019-08-03

#pragma once

#include <string>
#include <vector>
#include <list>
#include <set>
#include <sstream>
#include <iomanip>

#include "dkstd_string.hpp"

namespace dkstd
{
    namespace bytes
    {
        template<typename char_t>
        std::basic_string<char_t> to_hex_string(const std::vector<uint8_t>& data);

        template<typename char_t>
        std::basic_string<char_t> to_hex_string(const std::list<uint8_t>& data);

        template<typename char_t>
        std::basic_string<char_t> to_hex_string(const std::string& data);

        std::vector<uint8_t> from_hex_string(const std::string& hex);
        std::vector<uint8_t> from_hex_wstring(const std::wstring& hex);
    }
}

// KhiemDH - 2019-08-03
template<typename char_t>
inline std::basic_string<char_t> dkstd::bytes::to_hex_string(const std::vector<uint8_t>& data)
{
    std::basic_stringstream<char_t> ss;
    for (const uint8_t& byte : data)
    {
        ss << std::setfill<char_t>('0') << std::setw(2) << std::hex << (uint16_t)byte;
    }
    return ss.str();
}

// KhiemDH - 2019-08-03
template<typename char_t>
inline std::basic_string<char_t> dkstd::bytes::to_hex_string(const std::list<uint8_t>& data)
{
    std::basic_stringstream<char_t> ss;
    for (const uint8_t& byte : data)
    {
        ss << std::setfill<char_t>('0') << std::setw(2) << std::hex << (uint16_t)byte;
    }
    return ss.str();
}

// KhiemDH - 2019-08-03
template<typename char_t>
inline std::basic_string<char_t> dkstd::bytes::to_hex_string(const std::string& data)
{
    std::basic_stringstream<char_t> ss;
    for (const uint8_t& byte : data)
    {
        ss << std::setfill<char_t>('0') << std::setw(2) << std::hex << (uint16_t)byte;
    }
    return ss.str();
}

// KhiemDH - 2019-07-30
inline std::vector<uint8_t> dkstd::bytes::from_hex_string(const std::string& hex)
{
    std::vector<uint8_t> data;
    std::set<uint8_t> vocabs = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a',
        'b', 'c', 'd', 'e', 'f' };
    for (size_t i = 0; i < hex.length(); i += 2)
    {
        std::string subhex = hex.substr(i, 2);
        if (vocabs.count(std::tolower(subhex.at(0))) == 0 || vocabs.count(std::tolower(subhex.at(1))) == 0)
            break;
        uint8_t byte = (std::uint8_t)std::strtoul(subhex.c_str(), nullptr, 16);
        data.emplace_back(byte);
    }
    return data;
}

// KhiemDH - 2019-07-30
inline std::vector<uint8_t> dkstd::bytes::from_hex_wstring(const std::wstring& hex)
{
    std::vector<uint8_t> data;
    std::set<uint16_t> vocabs = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a',
        'b', 'c', 'd', 'e', 'f' };
    for (size_t i = 0; i < hex.length(); i += 2)
    {
        const std::wstring wsubhex = hex.substr(i, 2);
        if (vocabs.count(std::tolower(wsubhex.at(0))) == 0 || vocabs.count(std::tolower(wsubhex.at(1))) == 0)
            break;
        std::string subhex = dkstd::string::ws2s(wsubhex);
        uint8_t byte = (std::uint8_t)std::strtoul(subhex.c_str(), nullptr, 16);
        data.emplace_back(byte);
    }
    return data;
}
