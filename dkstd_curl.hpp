// author:      Khiêm Đoàn Hoà
// created:     2016-08-04
// modified:    2016-08-05

#ifndef _DKSTD_CURL_
#define _DKSTD_CURL_

#include "string"
#include "fstream"
#include "map"

#define CURL_STATICLIB
#include "curl/curl.h"

#ifdef _WIN32
#pragma comment (linker, "/NODEFAULTLIB:libcmt.lib")
#ifdef _DEBUG
#pragma comment (lib, "curl/libcurl_a_debug.lib")
#else
#pragma comment (lib, "curl/libcurl_a.lib")
#endif
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

size_t dkstd::curl::m_nInstance = 0;

// constructor - no parameter
// KhiemDH - 2016-08-05
inline dkstd::curl::curl()
{
    if (m_nInstance == 0) {
        curl_global_init(CURL_GLOBAL_ALL);
        m_nInstance++;
    }
}

// constructor - wstring parameter
// KhiemDH - 2016-08-05
inline dkstd::curl::curl(std::wstring sUrl)
{
    curl(dkstd::ws2s(sUrl));
}

// constructor - string parameter
// KhiemDH - 2016-08-05
inline dkstd::curl::curl(std::string sUrl)
{
    curl();
    m_sUrl = sUrl;
}

// destructor
// KhiemDH - 2016-08-05
inline dkstd::curl::~curl()
{
    if (m_nInstance == 1) {
        curl_global_cleanup();
    }
    m_nInstance--;
}

// set url for request - wstring parameter
// KhiemDH - 2016-08-05
inline void dkstd::curl::set_url(std::wstring sUrl)
{
    return this->set_url(dkstd::ws2s(sUrl));
}

// set url for request - string parameter
// KhiemDH - 2016-08-05
inline void dkstd::curl::set_url(std::string sUrl)
{
    m_sUrl = sUrl;
}

// add a header for request - wstring parameters
// parameters: header name, header vallue
// KhiemDH - 2016-08-05
inline void dkstd::curl::add_header(std::wstring sName, std::wstring sValue)
{
    return this->add_header(dkstd::ws2s(sName), dkstd::ws2s(sValue));
}

// add a header for request - string parameters
// parameters: header name, header vallue
// KhiemDH - 2016-08-05
inline void dkstd::curl::add_header(std::string sName, std::string sValue)
{
    m_mapHeaders[sName] = sValue;
}

// add a form data for request - wstring parameters
// parameters: field name, value
// KhiemDH - 2016-08-05
inline void dkstd::curl::add_data(std::wstring sField, std::wstring sValue)
{
    return this->add_data(dkstd::ws2s(sField), dkstd::ws2s(sValue));
}

// add a form data for request - string parameters
// parameters: field name, value
// KhiemDH - 2016-08-05
inline void dkstd::curl::add_data(std::string sField, std::string sValue)
{
    m_mapData[sField] = sValue;
}

// add a file form data for request - wstring parameters
// parameters: field name, file path
// KhiemDH - 2016-08-05
inline void dkstd::curl::add_file(std::wstring sField, std::wstring sFilePath)
{
    return this->add_file(dkstd::ws2s(sField), dkstd::ws2s(sFilePath));
}

// add a file form data for request - string parameters
// parameters: field name, file path
// KhiemDH - 2016-08-05
inline void dkstd::curl::add_file(std::string sField, std::string sFilePath)
{
    m_mapFiles[sField] = sFilePath;
}

// send request
// KhiemDH - 2016-08-05
inline bool dkstd::curl::send_request()
{
    CURL                    *curl_handle = nullptr;
    CURLcode                res = CURLE_OK;

    struct curl_slist       *chunk = NULL;
    struct curl_httppost    *post = NULL;
    struct curl_httppost    *last = NULL;

    bool                    bReturn = false;

    curl_handle = curl_easy_init();
    m_sLocation = "";

    // header
    for (const std::pair<std::string, std::string>& header : m_mapHeaders) {
        std::string s = header.first + ":" + header.second;
        chunk = curl_slist_append(chunk, s.c_str());
    }

    // data
    for (auto i : m_mapData) {
        curl_formadd(&post, &last, CURLFORM_COPYNAME, i.first.c_str(),
				CURLFORM_COPYCONTENTS, i.second.c_str(), CURLFORM_END);
    }

    // file
    for (auto i : m_mapFiles) {
        curl_formadd(&post, &last, CURLFORM_COPYNAME, i.first.c_str(),
                CURLFORM_FILE, i.second.c_str(), CURLFORM_END);
    }

    curl_easy_setopt(curl_handle, CURLOPT_URL, m_sUrl.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, chunk);
    curl_easy_setopt(curl_handle, CURLOPT_HTTPPOST, post);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &m_sContent);

    res = curl_easy_perform(curl_handle);
    if (res == CURLE_OK) {
        bReturn = true;
    }

    char *location;
    res = curl_easy_getinfo(curl_handle, CURLINFO_REDIRECT_URL, &location);
    if ((res == CURLE_OK) && location) {
        m_sLocation = location;
    }

    curl_formfree(post);
    curl_slist_free_all(chunk);
    curl_easy_cleanup(curl_handle);

    return bReturn;
}

// get content return after send request
// KhiemDH - 2016-08-05
inline std::string dkstd::curl::get_content()
{
    return m_sContent;
}

// download content to file - wstring parameter
// parameter - file path
// KhiemDH - 2016-08-05
inline bool dkstd::curl::download_to_file(std::wstring sFilePath)
{
    bool bReturn = false;
    bool bRequest = false;

    bRequest = send_request();
    std::ofstream file(sFilePath, std::fstream::out | std::fstream::binary);
    if (bRequest && file.good()) {
        file << m_sContent;
        m_sContent = "";
        file.close();
        bReturn = true;
    }

    return bReturn;
}

// download content to file - string parameter
// parameter - file path
// KhiemDH - 2016-08-05
inline bool dkstd::curl::download_to_file(std::string sFilePath)
{
    return download_to_file(dkstd::s2ws(sFilePath));
}

// get redirect
// KhiemDH - 2016-08-05
inline std::string dkstd::curl::get_redirect()
{
    return m_sLocation;
}

// write data to std::string
// KhiemDH - 2016-08-05
inline size_t dkstd::curl::write_data(char * contents, size_t size, size_t nmemb, std::string * stream)
{
    size_t realsize = size * nmemb;
    stream->append(contents, realsize);
    return realsize;
}

// write data to std::ofstream
// KhiemDH - 2016-08-05
inline size_t dkstd::curl::write_file(char * contents, size_t size, size_t nmemb, std::ofstream * file)
{
    size_t realsize = size * nmemb;
    if (file->good() == true) {
        file->write(contents, realsize);
    }
    return realsize;
}

#endif // !_DKSTD_CURL_