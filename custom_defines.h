#pragma once
typedef unsigned __int64  uintptr_t;
typedef unsigned __int64 hack_ulong_ptr, * hack_pulong_ptr;
typedef hack_ulong_ptr hack_dword_ptr, * hack_pdword_ptr;
typedef void* hack_lpvoid;
typedef unsigned char hack_byte;
typedef unsigned long long hack_uint64_t;
typedef long hack_int32_t;
typedef void* hack_pvoid;
typedef int hack_bool;
typedef unsigned long hack_dword;
typedef unsigned __int64 hack_ulonglong;
typedef hack_pvoid hack_handle;
typedef hack_dword* hack_pdword;
typedef hack_ulong_ptr hack_sizet;
typedef unsigned __int64 hack_size_t;
typedef unsigned long hack_u_long;
typedef unsigned __int64 hack_uint_ptr;
typedef unsigned char hack_uint8_t;
typedef wchar_t hack_wchar;
typedef hack_wchar* hack_pwchar;
typedef hack_byte hack_boolean;
typedef const hack_byte* hack_lpcbyte;
typedef long hack_long;
typedef hack_byte* hack_p_byte;
typedef unsigned int hack_uint;
typedef unsigned int hack_uint32_t;
typedef signed char hack_int8_t;

typedef int hack_int;
typedef int* hack_p_int;
typedef unsigned short hack_word;
typedef unsigned char hack_uchar;

typedef unsigned char   hack_u_char;
typedef unsigned short  hack_u_short;
typedef unsigned int    hack_u_int;
typedef unsigned long   hack_u_long;

typedef const void* hack_LPCVOID;
typedef long hack_LONG_PTR, * hack_PLONG_PTR;

struct hack_HINSTANCE__
{
	int unused;
}; typedef struct hack_HINSTANCE__* hack_HINSTANCE;

typedef hack_HINSTANCE hack_hmodule;

typedef const char* hack_PCSTR;
typedef char* hack_LPSTR;

#define far
#define FAR                 far