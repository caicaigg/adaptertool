#pragma once

#ifdef SCNPARSERLIB_EXPORTS
#	define SCNPARSERLIB_DECL __declspec(dllexport)
#else
#	define SCNPARSERLIB_DECL __declspec(dllimport)
#	define __LIB_NAME__ "ScnParserLib"

#	ifndef _LIBEXTNAME
#		ifndef NDEBUG
#			define _LIBEXTNAME "d.lib"
#		else 
#			define _LIBEXTNAME ".lib"
#		endif // _DEBUG
#	endif // _LIBEXTNAME

#pragma comment(lib, __LIB_NAME__ _LIBEXTNAME)
#pragma message ("Linking to lib file: " __LIB_NAME__ _LIBEXTNAME)
#endif