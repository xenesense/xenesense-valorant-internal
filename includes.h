#pragma once


#define VC_EXTRALEAN

#define WIN32_LEAN_AND_MEAN
#define BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN

#define WIN64_LEAN_AND_MEAN
#define BOOST_INTERPROCESS_WIN64_LEAN_AND_MEAN

#define FLT_MAX     3.40282347E+38F
#define NULL 0
#include <windows.h>

//#include <cstdint>
//#include <cmath>
//#include <iostream>

#include "custom_defines.h"
#include "crt.h"
#include "c_alloc.h"
#include "memory.h"

void* __cdecl operator new(size_t size)
{
	return static_cast<void*>(malloc(size));
}
void operator delete(void* p)
{
	if (p != NULL)
		free(p);
}
void* __cdecl operator new[](size_t n)
{
	return operator new(n);
}
void  __cdecl operator delete[](void* p)
{
	operator delete(p);
}
void  __cdecl operator delete[](void* p, size_t)
{
	operator delete[](p);
}
void  __cdecl operator delete(void* p, size_t)
{
	operator delete(p);
}


#include "c_vector.h"
#include "c_string.h"
#include "c_map.h"

#include "str_crypt.h"

#include "defines.h"

#include "return_spoofer.h"

#include "unreal_engine.h"
#include "uworld.h"
#include "valorant.h"
#include "ZeroInput.h"
#include "ZeroGUI.h"
#include "math.h"
#include "unlock_all.h"

