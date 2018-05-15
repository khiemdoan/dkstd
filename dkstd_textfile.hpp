// author:      Khiêm Đoàn Hoà (KhiemDH)
// github:      https://github.com/khiemdoan/dkstd
// created:     2016-07-06
// modified:    2018-05-15

#pragma once

#include "fstream"
#include "vector"
#include "dkstd_string.hpp"

namespace dkstd
{

    // textfile is used to read and write file by utf-8
    // KhiemDH - 2016-07-06
    class textfile
    {
    public:
        textfile() {};
        textfile(std::string sFilePath);
        textfile(std::wstring sFilePath);
        textfile(std::string sFilePath, std::ios::openmode mode);
        textfile(std::wstring sFilePath, std::ios::openmode mode);
        ~textfile();

        void    open(std::string sFilePath);
        void    open(std::wstring sFilePath);
        void    open(std::string sFilePath, std::ios::openmode mode);
        void    open(std::wstring sFilePath, std::ios::openmode mode);
        void    close();

        template<typename ...Args>
        bool write_line(std::string sFormat, Args ...args);
        template<typename ...Args>
        bool write_line(std::wstring sFormat, Args ...args);

        std::vector<std::wstring>   get_all_lines();

        void clear();

    private:
        std::fstream        m_file;
        std::ios::openmode  m_mode = std::fstream::in | std::fstream::out | std::fstream::app;
#ifdef _WIN32
        std::wstring        m_sFilePath;
#else
        std::string         m_sFilePath;
#endif
    };
}

// constructor with file path
// KhiemDH - 2016-07-06
inline dkstd::textfile::textfile(std::string sFilePath)
{
    this->open(sFilePath);
}

// constructor with file path
// KhiemDH - 2016-07-06
inline dkstd::textfile::textfile(std::wstring sFilePath)
{
    this->open(sFilePath);
}

// constructor with file path and open mode
// KhiemDH - 2016-09-24
inline dkstd::textfile::textfile(std::string sFilePath, std::ios::openmode mode)
{
    this->open(sFilePath, mode);
}

// constructor with file path and open mode
// KhiemDH - 2016-09-24
inline dkstd::textfile::textfile(std::wstring sFilePath, std::ios::openmode mode)
{
    this->open(sFilePath, mode);
}

// destructor
// KhiemDH - 2016-07-06
inline dkstd::textfile::~textfile()
{
    this->close();
}

// open file
// KhiemDH - 2016-09-24
inline void dkstd::textfile::open(std::string sFilePath)
{
    this->open(sFilePath, std::fstream::in | std::fstream::out | std::fstream::app);
}

// open file
// KhiemDH - 2016-09-24
inline void dkstd::textfile::open(std::wstring sFilePath)
{
    this->open(sFilePath, std::fstream::in | std::fstream::out | std::fstream::app);
}

// open file with custom mode
// KhiemDH - 2016-09-24
inline void dkstd::textfile::open(std::string sFilePath, std::ios::openmode mode)
{
#ifdef _WIN32
    this->open(dkstd::s2ws(sFilePath), mode);
#else
    this->close();
    m_file.open(sFilePath, mode);
    m_sFilePath = sFilePath;
    m_mode = mode;
#endif
}

// open file with custom mode
// KhiemDH - 2016-09-24
inline void dkstd::textfile::open(std::wstring sFilePath, std::ios::openmode mode)
{
#ifdef _WIN32
    this->close();
    m_file.open(sFilePath, mode);
    m_sFilePath = sFilePath;
    m_mode = mode;
#else
    this->open(dkstd::ws2s(sFilePath), mode);
#endif
}

// close file
// KhiemDH - 2016-08-15
inline void dkstd::textfile::close()
{
    if (m_file.is_open())
    {
        m_file.close();
    }
}

// write a line to end file
// input: UTF-8 string
// KhiemDH - 2018-05-15
template<typename ...Args>
inline bool dkstd::textfile::write_line(std::string sFormat, Args ...args)
{
    if (m_file.good())
    {
        std::string sContent = dkstd::string::format(sFormat, args...);
        m_file.seekp(0, std::fstream::end);
        if (m_file.tellg() != 0)
        {
            sContent = "\n" + sContent;
        }
        m_file << sContent;
        m_file.flush();
        m_file.clear();     // clear the error flag
        return true;
    }
    return false;
}

// write a line to end file
// input: Unicode string
// KhiemDH - 2017-10-16
template<typename ...Args>
inline bool dkstd::textfile::write_line(std::wstring sFormat, Args ...args)
{
    std::wstring sContent = dkstd::string::format(sFormat, args...);
    return this->write_line(dkstd::ws2s(sContent));
}

// read file to std::vector
// KhiemDH - 2018-05-15
inline std::vector<std::wstring> dkstd::textfile::get_all_lines()
{
    std::vector<std::wstring>   vectorContents;

    if (m_file.good())
    {
        m_file.seekg(0, std::fstream::end);
        if (m_file.tellg() > 0)
        {
            m_file.seekg(0, std::fstream::beg);
            while (!m_file.eof())
            {
                std::string sLine;
                std::getline(m_file, sLine);
                if (sLine.length() > 0 && sLine.back() == '\r')
                {
                    sLine.pop_back();
                }
                vectorContents.emplace_back(dkstd::s2ws(sLine));
            }
        }
        m_file.clear();
    }

    return vectorContents;
}

// clear text in file
inline void dkstd::textfile::clear()
{
    this->close();
    m_file.open(m_sFilePath, std::fstream::out | std::fstream::trunc);
    this->close();
    this->open(m_sFilePath, m_mode);
}
