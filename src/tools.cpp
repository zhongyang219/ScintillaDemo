#include "tools.h"
#include <windows.h>

_tstring tools::LoadStringRes(unsigned int id)
{
    TCHAR buff[256];
    LoadString(GetModuleHandle(NULL), id, buff, 255);
    UINT err = GetLastError();
    return _tstring(buff);
}
