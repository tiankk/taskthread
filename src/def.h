/**
 *    @file:        def.h
 *    @author:      tiankk <tiankk@gmail.com>
 *    @created:     2014/02/13
 */

#ifndef __DEF_H__
#define __DEF_H__

#include <tchar.h>
#include <string>
#include <fstream>
#include <sstream>

#ifdef UNICODE
#define tstring std::wstring
#define tostream std::wostream
#define tistream std::wistream
#define tifstream std::wifstream
#define tofstream std::wofstream
#define tsstream std::wstringstream
#else
#define tstring std::string
#define tostream std::ostream
#define tistream std::istream
#define tifstream std::ifstream
#define tofstream std::ofstream
#define tsstream std::stringstream
#endif

namespace tthread
{
    namespace utility
    {
        const unsigned int g_Magic_Identifer = 20120821; // magic number for identifying message
    } // namespace utility
} // namespace tthread

#endif // __DEF_H__
