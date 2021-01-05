#pragma once
#include <ctime>
#include <chrono>
#include <asio/ip/address.hpp>

class PathHelper
{
public:
    static bool CanAccessFolder(const LPCTSTR folderName, DWORD genericAccessRights)
    {
        bool bRet = false;
        DWORD length = 0;
        if (!::GetFileSecurity(folderName, OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION
            | DACL_SECURITY_INFORMATION, nullptr, NULL, &length) &&
            ERROR_INSUFFICIENT_BUFFER == ::GetLastError()) {
	        const PSECURITY_DESCRIPTOR security = static_cast<PSECURITY_DESCRIPTOR>(::malloc(length));
            if (security && ::GetFileSecurity(folderName, OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION
                | DACL_SECURITY_INFORMATION, security, length, &length)) {
                HANDLE hToken = nullptr;
                if (::OpenProcessToken(::GetCurrentProcess(), TOKEN_IMPERSONATE | TOKEN_QUERY |
                    TOKEN_DUPLICATE | STANDARD_RIGHTS_READ, &hToken)) {
                    HANDLE hImpersonatedToken = nullptr;
                    if (::DuplicateToken(hToken, SecurityImpersonation, &hImpersonatedToken)) {
                        GENERIC_MAPPING mapping = { 0xFFFFFFFF };
                        PRIVILEGE_SET privileges = { 0 };
                        DWORD grantedAccess = 0, privilegesLength = sizeof(privileges);
                        BOOL result = FALSE;

                        mapping.GenericRead = FILE_GENERIC_READ;
                        mapping.GenericWrite = FILE_GENERIC_WRITE;
                        mapping.GenericExecute = FILE_GENERIC_EXECUTE;
                        mapping.GenericAll = FILE_ALL_ACCESS;

                        ::MapGenericMask(&genericAccessRights, &mapping);
                        if (::AccessCheck(security, hImpersonatedToken, genericAccessRights,
                            &mapping, &privileges, &privilegesLength, &grantedAccess, &result)) {
                            bRet = (result == TRUE);
                        }
                        ::CloseHandle(hImpersonatedToken);
                    }
                    ::CloseHandle(hToken);
                }
                ::free(security);
            }
        }

        return bRet;
    }
};

