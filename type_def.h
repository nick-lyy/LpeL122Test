#ifndef __TYPE_DEF_H__
#define __TYPE_DEF_H__


typedef unsigned char   U8;
typedef short           I16;
typedef unsigned short  U16;
typedef long            I32;
typedef unsigned long   U32;
typedef float           F32;
typedef double          F64;


#if defined(_WIN32)
#   ifndef PASCAL
#   define PASCAL __stdcall
#   endif
#else
#   define PASCAL
#endif


#endif //__TYPE_DEF_H__
