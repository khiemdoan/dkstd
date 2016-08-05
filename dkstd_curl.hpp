// author:		Khiêm Đoàn Hoà
// created:		2016-08-04
// modified:	2016-08-05

#ifndef _DKSTD_CURL_
#define _DKSTD_CURL_

#include "string"
#include "fstream"
#include "map"

#define CURL_STATICLIB
#include "curl/curl.h"

#ifdef _WIN32
#pragma comment (lib, "curl/libcurl_a.lib")
#pragma comment (linker, "/NODEFAULTLIB:libcmt.lib")
#endif

#include "dkstd_string.hpp"

namespace dkstd
{
	class curl
	{
	public:
		curl();
		~curl();

		void set_url(std::wstring sUrl);
		void set_url(std::string sUrl);
		void add_header(std::wstring name, std::wstring value);
		void add_header(std::string name, std::string value);
		void add_data(std::wstring field, std::wstring value);
		void add_data(std::string field, std::string value);
		void add_file(std::wstring field, std::wstring file_path);
		void add_file(std::string field, std::string file_path);

		bool send_request();

		std::string get_content();
		bool download_to_file(std::wstring file_path);
		bool download_to_file(std::string file_path);
		std::string get_redirect();

	private:
		std::map<std::string, std::string>	m_mapHeaders;
		std::map<std::string, std::string>	m_mapData;
		std::map<std::string, std::string>	m_mapFiles;
		std::string			m_sUrl;
		std::string			m_sContent;
		std::string			m_sLocation;
		static size_t		m_nInstance;

		static size_t write_data(char * contents, size_t size, size_t nmemb, std::string * stream);
		static size_t write_file(char * contents, size_t size, size_t nmemb, std::ofstream * file);
	};
}

size_t dkstd::curl::m_nInstance = 0;

inline dkstd::curl::curl()
{
	if (m_nInstance == 0) {
		curl_global_init(CURL_GLOBAL_ALL);
		m_nInstance++;
	}
}

inline dkstd::curl::~curl()
{
	if (m_nInstance == 1) {
		curl_global_cleanup();
	}
	m_nInstance--;
}

inline void dkstd::curl::set_url(std::wstring sUrl)
{
	return this->set_url(dkstd::ws2s(sUrl));
}

inline void dkstd::curl::set_url(std::string sUrl)
{
	m_sUrl = sUrl;
}

inline void dkstd::curl::add_header(std::wstring name, std::wstring value)
{
	return this->add_header(dkstd::ws2s(name), dkstd::ws2s(value));
}

inline void dkstd::curl::add_header(std::string name, std::string value)
{
	m_mapHeaders[name] = value;
}

inline void dkstd::curl::add_data(std::wstring field, std::wstring value)
{
	return this->add_data(dkstd::ws2s(field), dkstd::ws2s(value));
}

inline void dkstd::curl::add_data(std::string field, std::string value)
{
	m_mapData[field] = value;
}

inline void dkstd::curl::add_file(std::wstring field, std::wstring file_path)
{
	return this->add_file(dkstd::ws2s(field), dkstd::ws2s(file_path));
}

inline void dkstd::curl::add_file(std::string field, std::string file_path)
{
	m_mapFiles[field] = file_path;
}

inline bool dkstd::curl::send_request()
{
	CURL					*curl_handle = nullptr;
	CURLcode				res = CURLE_OK;
	
	struct curl_slist		*chunk = NULL;
	struct curl_httppost	*post = NULL;
	struct curl_httppost	*last = NULL;

	bool					bReturn = false;

	curl_handle = curl_easy_init();
	m_sLocation = "";

	// header
	for (auto header : m_mapHeaders) {
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

inline std::string dkstd::curl::get_content()
{
	return m_sContent;
}

inline bool dkstd::curl::download_to_file(std::wstring file_path)
{
	bool		bReturn = false;
	bool		bRequest = false;

	bRequest = send_request();
	std::ofstream file(file_path, std::fstream::out | std::fstream::binary);
	if (bRequest == true && file.good() == true) {

		file << m_sContent;
		m_sContent = "";
		file.close();
		bReturn = true;
	}

	return bReturn;
}

inline bool dkstd::curl::download_to_file(std::string file_path)
{
	return download_to_file(dkstd::s2ws(file_path));
}

inline std::string dkstd::curl::get_redirect()
{
	return m_sLocation;
}

inline size_t dkstd::curl::write_data(char * contents, size_t size, size_t nmemb, std::string * stream)
{
	size_t realsize = size * nmemb;
	stream->append(contents, realsize);
	return realsize;
}

inline size_t dkstd::curl::write_file(char * contents, size_t size, size_t nmemb, std::ofstream * file)
{
	size_t realsize = size * nmemb;
	if (file->good() == true) {
		file->write(contents, realsize);
	}
	return realsize;
}

#endif // !_DKSTD_CURL_