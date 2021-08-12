// mkreglink.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

BOOL
CreateRegistrySymbolicLink(
    HKEY &outKeyHandle,
    const std::wstring &linkPath,
    const std::wstring targetPathNative)
{
    BOOL bResult = FALSE;
    DWORD disposition = 0;
    LSTATUS status = 0;
    
    status = RegCreateKeyExW(
        HKEY_LOCAL_MACHINE, linkPath.c_str(), 0,
        NULL, REG_OPTION_CREATE_LINK, KEY_ALL_ACCESS,
        NULL, &outKeyHandle, &disposition);
    if (ERROR_SUCCESS != status)
    {
        printf("RegCreateKeyExW failed with error %u\n", status);
        goto Cleanup;
    }

    if (InvalidHandle(outKeyHandle))
    {
        printf("RegCreateKeyExW didn't return a value?  Error: %u\n", status);
        goto Cleanup;
    }

    status = RegSetValueExW(
        outKeyHandle, L"SymbolicLinkValue", 0,
        REG_LINK, (PBYTE)targetPathNative.c_str(),
        (DWORD)targetPathNative.size() * sizeof(wchar_t));
    if (ERROR_SUCCESS != status)
    {
        printf("RegSetValueExW failed with error %u\n", status);
        goto Cleanup;
    }

    printf("Created registry symlink %ws => %ws\n", linkPath.c_str(), targetPathNative.c_str());
    bResult = TRUE;

Cleanup:
    return bResult;
}

int wmain(int argc, wchar_t * argv[])
{
    HKEY hKey = NULL;

    if (argc < 3)
    {
        printf("Usage: %ws Link Target\n\n", argv[0]);
        printf("     Link - Win32 syntax (Software\\Microsoft).  Currently HKLM hive only.\n");
        printf("     Target - Native syntax (\\Registry\\Machine)\n");
        return 1;
    }

    return CreateRegistrySymbolicLink(hKey, argv[1], argv[2]) ? 0 : 1;
}

