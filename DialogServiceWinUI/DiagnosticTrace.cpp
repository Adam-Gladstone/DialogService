#include "pch.h"


#ifdef _DEBUG
namespace Diagnostics
{
	void Trace(int line, const char* fileName, const char* msg, ...)
	{
		char text[CPP_TRACE_MAXLEN]{ 0 };
		// Format string so that we can double-click the resulting line in the output window
		sprintf_s(text, CPP_TRACE_MAXLEN, "%s(%d) : ", fileName, line);
		CPP_PRINT_DEBUG_STRING(text);

		va_list args;
		va_start(args, msg);
		vsnprintf_s(text, CPP_TRACE_MAXLEN, msg, args);
		va_end(args);
		CPP_PRINT_DEBUG_STRING(text);
	}
}
#endif

