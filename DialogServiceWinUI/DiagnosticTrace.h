#pragma once

#include <cstdarg>
#include <cstdio>

#include "Windows.h"

#ifdef _DEBUG
constexpr auto CPP_TRACE_MAXLEN = 1024;
#define CPP_PRINT_DEBUG_STRING(text) OutputDebugStringA(text)
#define CPP_TRACE(msg, ...) \
	Diagnostics::Trace(__LINE__, __FILE__, msg, __VA_ARGS__)
#else
#define CPP_TRACE(msg, ...)
#endif

#ifdef _DEBUG
namespace Diagnostics
{
	void Trace(int line, const char* fileName, const char* msg, ...);
}
#endif

