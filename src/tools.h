#pragma once
#include <string>

#ifdef UNICODE
using _tstring = std::wstring;
#else
using _tstring = std::string;
#endif // !UNICODE


class tools
{
public:
    static _tstring LoadStringRes(unsigned int id);
};

