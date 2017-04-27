// author:      Khiêm Đoàn Hoà
// created:     2017-04-26
// modified:    2017-04-26
// https://github.com/khiemdoancrazy/dkstd

#pragma once

#include "windows.h"
#include "string"
#include "vector"
#include "memory"

#pragma comment (lib, "Advapi32.lib")

namespace dkstd
{
	namespace registry
	{
		/* HKEY_CURRENT_USER */
		bool Read_HKCU_Key(std::wstring sKey, std::wstring sValue, DWORD & dwNumber);
		bool Set_HKCU_Key(std::wstring sKey, std::wstring sValue, DWORD & dwNumber);

		bool Read_HKCU_Key(std::wstring sKey, std::wstring sValue, std::wstring & sData);
		bool Set_HKCU_Key(std::wstring sKey, std::wstring sValue, std::wstring & sData);

		bool Read_HKCU_Key(std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data);
		bool Set_HKCU_Key(std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data);

		/* HKEY_LOCAL_MACHINE */
		bool Read_HKLM_Key(std::wstring sKey, std::wstring sValue, DWORD & dwNumber);
		bool Set_HKLM_Key(std::wstring sKey, std::wstring sValue, DWORD & dwNumber);

		bool Read_HKLM_Key(std::wstring sKey, std::wstring sValue, std::wstring & sData);
		bool Set_HKLM_Key(std::wstring sKey, std::wstring sValue, std::wstring & sData);

		bool Read_HKLM_Key(std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data);
		bool Set_HKLM_Key(std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data);

		/* Any key */
		bool ReadKey(HKEY hRootKey, std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data);
		bool SetKey(HKEY hRootKey, std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data);

		class registry_exception : public std::exception {};
	};
}
