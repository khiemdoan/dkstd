// author:      Khiêm Đoàn Hoà (KhiemDH)
// github:      https://github.com/khiemdoan/dkstd
// created:     2017-04-26
// modified:    2019-08-03

#pragma once

#ifdef _WIN32

#include "windows.h"
#pragma comment (lib, "Advapi32.lib")

#include "string"
#include "vector"
#include "memory"

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

        std::vector<std::wstring> EnumKey_HKCU_Key(std::wstring sKey);
        std::vector<std::wstring> EnumValue_HKCU_Key(std::wstring sKey);

        /* HKEY_LOCAL_MACHINE */
        bool Read_HKLM_Key(std::wstring sKey, std::wstring sValue, DWORD & dwNumber);
        bool Set_HKLM_Key(std::wstring sKey, std::wstring sValue, DWORD & dwNumber);

        bool Read_HKLM_Key(std::wstring sKey, std::wstring sValue, std::wstring & sData);
        bool Set_HKLM_Key(std::wstring sKey, std::wstring sValue, std::wstring & sData);

        bool Read_HKLM_Key(std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data);
        bool Set_HKLM_Key(std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data);

        std::vector<std::wstring> EnumKey_HKLM_Key(std::wstring sKey);
        std::vector<std::wstring> EnumValue_HKLM_Key(std::wstring sKey);

        /* Any key */
        bool ReadKey(HKEY hRootKey, std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data);
        bool SetKey(HKEY hRootKey, std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data);
        std::vector<std::wstring> EnumKey(HKEY hRootKey, std::wstring sKey);
        std::vector<std::wstring> EnumValue(HKEY hRootKey, std::wstring sKey);

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

// KhiemDH - 2019-08-03
inline std::vector<std::wstring> dkstd::registry::EnumKey_HKCU_Key(std::wstring sKey)
{
    return EnumKey(HKEY_CURRENT_USER, sKey);
}

// KhiemDH - 2019-08-03
inline std::vector<std::wstring> dkstd::registry::EnumValue_HKCU_Key(std::wstring sKey)
{
    return EnumValue(HKEY_CURRENT_USER, sKey);
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

// KhiemDH - 2019-08-03
inline std::vector<std::wstring> dkstd::registry::EnumKey_HKLM_Key(std::wstring sKey)
{
    return EnumKey(HKEY_LOCAL_MACHINE, sKey);
}

// KhiemDH - 2019-08-03
inline std::vector<std::wstring> dkstd::registry::EnumValue_HKLM_Key(std::wstring sKey)
{
    return EnumValue(HKEY_LOCAL_MACHINE, sKey);
}

// KhiemDH - 2018-07-27
// Đọc giá trị trong Registry
inline bool dkstd::registry::ReadKey(HKEY hRootKey, std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data)
{
    HKEY    hKey = NULL;
    LONG    lCreate = ERROR_SUCCESS;
    LONG    lQuery = ERROR_SUCCESS;
    DWORD   dwRegOpened = NULL;
    DWORD   dwSize = 0;
    bool    bReturn = false;
    std::unique_ptr<uint8_t[]> buffer;

    try
    {
        lCreate = RegCreateKeyExW(hRootKey, sKey.c_str(), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &hKey, &dwRegOpened);
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

// KhiemDH - 2018-07-27
// Gán giá trị trong Registry
// Nếu key chưa tồn tại thì tạo mới
inline bool dkstd::registry::SetKey(HKEY hRootKey, std::wstring sKey, std::wstring sValue, DWORD dwType, std::vector<uint8_t> & data)
{
    HKEY    hKey = NULL;
    LONG    lCreate = ERROR_SUCCESS;
    LONG    lQuery = ERROR_SUCCESS;
    DWORD   dwRegOpened = NULL;
    DWORD   dwSize = data.size();
    bool    bReturn = false;

    try
    {
        lCreate = RegCreateKeyExW(hRootKey, sKey.c_str(), NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &dwRegOpened);
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

// KhiemDH - 2019-08-03
inline std::vector<std::wstring> dkstd::registry::EnumKey(HKEY hRootKey, std::wstring sKey)
{
    DWORD       cSubKeys = 0;                   // number of subkeys
    DWORD       cbMaxSubKey = 0;                // longest subkey size
    HKEY        hKey;

    LONG        lCreate = ERROR_SUCCESS;
    LONG        lQuery = ERROR_SUCCESS;

    std::vector<std::wstring>   keys;

    try
    {
        lCreate = RegOpenKeyExW(hRootKey, sKey.c_str(), 0, KEY_READ, &hKey);
        if (lCreate != ERROR_SUCCESS)
            throw registry_exception();

        lQuery = RegQueryInfoKeyW(
            hKey,                       // key handle
            NULL,                       // buffer for class name
            NULL,                       // size of class string
            NULL,                       // reserved
            &cSubKeys,                  // number of subkeys
            &cbMaxSubKey,               // longest subkey size
            NULL,                       // longest class string
            NULL,                       // number of values for this key
            NULL,                       // longest value name
            NULL,                       // longest value data
            NULL,                       // security descriptor
            NULL);                      // last write time
        if (lQuery != ERROR_SUCCESS)
            throw registry_exception();

        std::vector<wchar_t> achKey;            // buffer for subkey name
        achKey.resize(cbMaxSubKey + 1);

        for (DWORD i = 0; i < cSubKeys; i++)
        {
            DWORD cbName = cbMaxSubKey + 1;     // size of name string

            lQuery = RegEnumKeyW(hKey, i, achKey.data(), cbName);
            if (lQuery != ERROR_SUCCESS)
                continue;

            keys.emplace_back(achKey.data());
        }
    }
    catch (registry_exception) {}

    if (lCreate == ERROR_SUCCESS && hKey != NULL)
    {
        RegCloseKey(hKey);
        hKey = NULL;
    }

    return keys;
}

// KhiemDH - 2019-08-03
inline std::vector<std::wstring> dkstd::registry::EnumValue(HKEY hRootKey, std::wstring sKey)
{
    DWORD       cValues = 0;                        // number of values for this key
    DWORD       cchMaxValue = 0;                    // longest value name
    HKEY        hKey;

    LONG        lCreate = ERROR_SUCCESS;
    LONG        lQuery = ERROR_SUCCESS;

    std::vector<std::wstring>   values;

    try
    {
        lCreate = RegOpenKeyExW(hRootKey, sKey.c_str(), 0, KEY_READ, &hKey);
        if (lCreate != ERROR_SUCCESS)
            throw registry_exception();

        lQuery = RegQueryInfoKeyW(
            hKey,                       // key handle
            NULL,                       // buffer for class name
            NULL,                       // size of class string
            NULL,                       // reserved
            NULL,                       // number of subkeys
            NULL,                       // longest subkey size
            NULL,                       // longest class string
            &cValues,                   // number of values for this key
            &cchMaxValue,               // longest value name
            NULL,                       // longest value data
            NULL,                       // security descriptor
            NULL);                      // last write time
        if (lQuery != ERROR_SUCCESS)
            throw registry_exception();

        std::vector<wchar_t> achKey;            // buffer for subkey name
        achKey.resize(cchMaxValue + 1);

        for (DWORD i = 0; i < cValues; i++)
        {
            DWORD cbName = cchMaxValue + 1;     // size of name string

            lQuery = RegEnumValueW(hKey, i, achKey.data(), &cbName, NULL, NULL, NULL, NULL);
            if (lQuery != ERROR_SUCCESS)
                continue;

            values.emplace_back(achKey.data());
        }
    }
    catch (registry_exception) {}

    if (lCreate == ERROR_SUCCESS && hKey != NULL)
    {
        RegCloseKey(hKey);
        hKey = NULL;
    }

    return values;
}

#endif
