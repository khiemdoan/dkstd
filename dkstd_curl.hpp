// author:      Khiêm Đoàn Hoà (KhiemDH)
// github:      https://github.com/khiemdoancrazy/dkstd
// created:     2016-08-04
// modified:    2016-08-05

#pragma once

#include "string"
#include "fstream"
#include "map"

#define CURL_STATICLIB
#include "libcurl/curl.h"

#ifdef _WIN32
#   ifdef _DEBUG
#       pragma comment (lib, "libcurl/libcurl_a_debug.lib")
#   else
#       pragma comment (lib, "libcurl/libcurl_a.lib")
#   endif
#endif

#include "dkstd_string.hpp"

namespace dkstd
{
    class curl
    {
    public:
        curl();
        curl(std::wstring sUrl);
        curl(std::string sUrl);
        ~curl();

        void set_url(std::wstring sUrl);
        void set_url(std::string sUrl);
        void add_header(std::wstring sName, std::wstring sValue);
        void add_header(std::string sName, std::string sValue);
        void add_data(std::wstring sField, std::wstring sValue);
        void add_data(std::string sField, std::string sValue);
        void add_file(std::wstring sField, std::wstring sFilePath);
        void add_file(std::string sField, std::string sFilePath);

        bool send_request();

        std::string get_content();
        bool download_to_file(std::wstring sFilePath);
        bool download_to_file(std::string sFilePath);
        std::string get_redirect();

    private:
        std::map<std::string, std::string>	m_mapHeaders;
        std::map<std::string, std::string>	m_mapData;
        std::map<std::string, std::string>	m_mapFiles;
        std::string         m_sUrl;
        std::string         m_sContent;
        std::string         m_sLocation;
        static size_t       m_nInstance;

        static size_t write_data(char * contents, size_t size, size_t nmemb, std::string * stream);
        static size_t write_file(char * contents, size_t size, size_t nmemb, std::ofstream * file);
    };
}
