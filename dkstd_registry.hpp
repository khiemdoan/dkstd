// author:      Khiêm Đoàn Hoà (KhiemDH)
// github:      https://github.com/khiemdoan/dkstd
// created:     2017-04-26
// modified:    2017-04-26

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

// KhiemDH - 2017-04-26
inline bool dkstd::registry::Read_HKCU_Key(std::wstring sKey, std::wstring sValue, DWORD & dwNumber)
{
    std::vector<uint8_t> buffer;
    if (dkstd::registry::Read_HKCU_Key(sKey, sValue, REG_DWORD, buffer))
    {
        if (buffer.size() == sizeof(DWORD))
        {
            dwNumber = *((DWORD *)buffer.data());
            return true;
        }
    }
    return false;
}

// KhiemDH - 2017-04-26
inline bool dkstd::registry::Set_HKCU_Key(std::wstring sKey, std::wstring sValue, DWORD & dwNumber)
{
    std::vector<uint8_t> buffer;
    buffer.resize(sizeof(DWORD));
    std::memcpy(buffer.data(), &dwNumber, sizeof(DWORD));
    return dkstd::registry::Set_HKCU_Key(sKey, sValue, REG_DWORD, buffer);
}

// KhiemDH - 2017-04-26
inline bool dkstd::registry::Read_HKCU_Key(std::wstring sKey, std::wstring sValue, std::wstring & sData)
{
    std::vector<uint8_t> buffer;
    if (dkstd::registry::Read_HKCU_Key(sKey, sValue, REG_SZ, buffer))
    {
        sData = (wchar_t *)buffer.data();
        return true;
    }
    return false;
}

// KhiemDH - 2017-04-26
inline bool dkstd::registry::Set_HKCU_Key(std::wstring sKey, std::wstring sValue, std::wstring & sData)
{
    std::vector<uint8_t> buffer;
    size_t size = sData.length() * sizeof(wchar_t);
    buffer.resize(size);
    std::memcpy(buffer.data(), sData.data(), size);
    return dkstd::registry::Set_HKCU_Key(sKey, sValue, REG_SZ, buffer);
}

// KhiemDH - 2017-04-26
// Đọc các key trong HKEY_CURRENT_USER
inline bool dkstd::registry::Read_HKCU_Key(std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data)
{
    return dkstd::registry::ReadKey(HKEY_CURRENT_USER, sKey, sValue, dwType, data);
}

// KhiemDH - 2017-04-26
// Gán giá trị cho các key trong HKEY_CURRENT_USER
inline bool dkstd::registry::Set_HKCU_Key(std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data)
{
    return dkstd::registry::SetKey(HKEY_CURRENT_USER, sKey, sValue, dwType, data);
}

// KhiemDH - 2017-04-26
inline bool dkstd::registry::Read_HKLM_Key(std::wstring sKey, std::wstring sValue, DWORD & dwNumber)
{
    std::vector<uint8_t> buffer;
    if (dkstd::registry::Read_HKLM_Key(sKey, sValue, REG_DWORD, buffer))
    {
        if (buffer.size() == sizeof(DWORD))
        {
            dwNumber = *((DWORD *)buffer.data());
            return true;
        }
    }
    return false;
}

// KhiemDH - 2017-04-26
inline bool dkstd::registry::Set_HKLM_Key(std::wstring sKey, std::wstring sValue, DWORD & dwNumber)
{
    std::vector<uint8_t> buffer;
    buffer.resize(sizeof(DWORD));
    std::memcpy(buffer.data(), &dwNumber, sizeof(DWORD));
    return dkstd::registry::Set_HKLM_Key(sKey, sValue, REG_DWORD, buffer);
}

// KhiemDH - 2017-04-26
inline bool dkstd::registry::Read_HKLM_Key(std::wstring sKey, std::wstring sValue, std::wstring & sData)
{
    std::vector<uint8_t> buffer;
    if (dkstd::registry::Read_HKLM_Key(sKey, sValue, REG_SZ, buffer))
    {
        sData = (wchar_t *)buffer.data();
        return true;
    }
    return false;
}

// KhiemDH - 2017-04-26
inline bool dkstd::registry::Set_HKLM_Key(std::wstring sKey, std::wstring sValue, std::wstring & sData)
{
    std::vector<uint8_t> buffer;
    size_t size = sData.length() * sizeof(wchar_t);
    buffer.resize(size);
    std::memcpy(buffer.data(), sData.data(), size);
    return dkstd::registry::Set_HKLM_Key(sKey, sValue, REG_SZ, buffer);
}

// KhiemDH - 2017-04-26
// Đọc các key trong HKEY_LOCAL_MACHINE
inline bool dkstd::registry::Read_HKLM_Key(std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data)
{
    return dkstd::registry::ReadKey(HKEY_LOCAL_MACHINE, sKey, sValue, dwType, data);
}

// KhiemDH - 2017-04-26
// Gán giá trị cho các key trong HKEY_LOCAL_MACHINE
inline bool dkstd::registry::Set_HKLM_Key(std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data)
{
    return dkstd::registry::SetKey(HKEY_LOCAL_MACHINE, sKey, sValue, dwType, data);
}

// KhiemDH - 2017-04-26
// Đọc giá trị trong Registry
inline bool dkstd::registry::ReadKey(HKEY hRootKey, std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data)
{
    HKEY	hKey = NULL;
    LONG	lCreate = ERROR_SUCCESS;
    LONG	lQuery = ERROR_SUCCESS;
    DWORD	dwRegOpened = REG_OPENED_EXISTING_KEY;
    DWORD	dwSize = 0;
    bool	bReturn = false;
    std::unique_ptr<uint8_t[]> buffer;

    try
    {
        lCreate = RegCreateKeyExW(hRootKey, sKey.c_str(), NULL, NULL, REG_OPTION_VOLATILE, KEY_READ, NULL, &hKey, &dwRegOpened);
        if (lCreate != ERROR_SUCCESS)
            throw registry_exception();

        lQuery = RegQueryValueExW(hKey, sValue.c_str(), NULL, &dwType, nullptr, &dwSize);
        if (lQuery != ERROR_SUCCESS)
            throw registry_exception();

        buffer = std::unique_ptr<uint8_t[]>(new uint8_t[dwSize]{ 0 });
        lQuery = RegQueryValueExW(hKey, sValue.c_str(), NULL, &dwType, buffer.get(), &dwSize);
        if (lQuery != ERROR_SUCCESS)
            throw registry_exception();

        data.resize(dwSize);
        std::copy(buffer.get(), buffer.get() + dwSize, data.begin());

        bReturn = true;
    }
    catch (registry_exception e) {}

    if (lCreate == ERROR_SUCCESS && hKey != NULL)
    {
        RegCloseKey(hKey);
        hKey = NULL;
    }

    return bReturn;
}

// KhiemDH - 2017-04-26
// Gán giá trị trong Registry
// Nếu key chưa tồn tại thì tạo mới
inline bool dkstd::registry::SetKey(HKEY hRootKey, std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data)
{
    HKEY	hKey = NULL;
    LONG	lCreate = ERROR_SUCCESS;
    LONG	lQuery = ERROR_SUCCESS;
    DWORD	dwRegOpened = REG_OPENED_EXISTING_KEY;
    DWORD	dwSize = data.size();
    bool	bReturn = false;

    try
    {
        lCreate = RegCreateKeyExW(hRootKey, sKey.c_str(), NULL, NULL, REG_OPTION_VOLATILE, KEY_WRITE, NULL, &hKey, &dwRegOpened);
        if (lCreate != ERROR_SUCCESS)
            throw registry_exception();

        lQuery = RegSetValueExW(hKey, sValue.c_str(), NULL, dwType, dwSize ? &data[0] : nullptr, dwSize);
        if (lQuery != ERROR_SUCCESS)
            throw registry_exception();

        bReturn = true;
    }
    catch (registry_exception e) {}

    if (lCreate == ERROR_SUCCESS && hKey != NULL)
    {
        RegCloseKey(hKey);
        hKey = NULL;
    }

    return bReturn;
}
