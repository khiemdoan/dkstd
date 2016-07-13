
// author: Khiêm Đoàn Hoà
// created: 2016-07-06
// modified: 2016-07-06

#ifndef _DKSTD_TEXTFILE_
#define _DKSTD_TEXTFILE_

#include "fstream"
#include "vector"
#include "dkstd_string.hpp"

namespace dkstd {

	// textfile is used to read and write file by utf-8
	// KhiemDH - 2016-07-06
	class textfile
	{
	public:
		textfile() {};
		textfile(std::string sFilePath);
		textfile(std::wstring sFilePath);
		~textfile();

		void	open(std::string sFilePath);
		void	open(std::wstring sFilePath);
		void	close();
		
		void	write_line(std::string sContent);
		void	write_line(std::wstring sContent);

		std::vector<std::wstring>	get_all_lines();

	private:
		std::fstream	m_file;
	};
}

// constructor
// KhiemDH - 2016-07-06
inline dkstd::textfile::textfile(std::string sFilePath)
{
	this->open(sFilePath);
}

// constructor
// KhiemDH - 2016-07-06
inline dkstd::textfile::textfile(std::wstring sFilePath)
{
	this->open(sFilePath);
}

// destructor
// KhiemDH - 2016-07-06
inline dkstd::textfile::~textfile()
{
	this->close();
}

// open file
// KhiemDH - 2016-07-06
inline void dkstd::textfile::open(std::string sFilePath)
{
	this->open(dkstd::s2ws(sFilePath));
}

// open file
// KhiemDH - 2016-07-06
inline void dkstd::textfile::open(std::wstring sFilePath)
{
	this->close();
	m_file.open(sFilePath, std::fstream::in | std::fstream::out | std::fstream::app);
}

// close file
// KhiemDH - 2016-07-06
inline void dkstd::textfile::close()
{
	if (m_file.is_open() == true) {
		m_file.close();
	}
}

// write a line to end file
// input: ANSI string
// KhiemDH - 2016-07-06
inline void dkstd::textfile::write_line(std::string sContent)
{
	if (m_file.good() == true) {
		m_file.seekp(0, std::fstream::end);
		if (m_file.tellg() != std::streampos::fpos(0)) {
			sContent = "\n" + sContent;
		}
		m_file << sContent;
		m_file.clear();		// clear the error flag
	}
}

// write a line to end file
// input: Unicode string
// KhiemDH - 2016-07-06
inline void dkstd::textfile::write_line(std::wstring sContent)
{
	this->write_line(dkstd::ws2s(sContent));
}

// read file to std::vector
// KhiemDH - 2016-07-06
inline std::vector<std::wstring> dkstd::textfile::get_all_lines()
{
	std::string		sLine;
	std::vector<std::wstring>	vectorContents;

	if (m_file.good() == true) {
		m_file.seekg(0, std::fstream::beg);
		while (m_file.eof() == false) {
			std::getline(m_file, sLine);
			vectorContents.push_back(dkstd::s2ws(sLine));
		}
		m_file.clear();
	}

	return vectorContents;
}

#endif // !_DKSTD_TEXTFILE_