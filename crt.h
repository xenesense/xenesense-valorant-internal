#pragma once
//#include <immintrin.h>

typedef struct hack_list_entry
{
	struct hack_list_entry* flink;
	struct hack_list_entry* blink;

} hack_list_entry, * hack_p_list_entry, * hack_prlist_entry;
struct UNICODE_STRING_T {
	unsigned short Length;
	unsigned short MaximumLength;
	wchar_t* Buffer;
};
typedef struct hack_peb_ldr_data
{
	unsigned char reserved_1[8];
	void* reserved_2[3];
	hack_list_entry in_memory_order_module_list;

} hack_peb_ldr_data, * hack_ppeb_ldr_data;
typedef struct hack_unicode_string
{
	unsigned short length;
	unsigned short maximum_length;
	wchar_t* buffer;

} hack_unicode_string;
typedef struct hack_rtl_user_process_parameters
{
	unsigned char reserved_1[16];
	void* reserved_2[10];
	hack_unicode_string image_path_name;
	hack_unicode_string command_line;

} hack_rtl_user_process_parameters, * hack_ptrl_user_process_parameters;

typedef void(__stdcall* pps_post_process_init_routine) (void);

typedef struct peb
{
	unsigned char reserved_1[2];
	unsigned char being_debugged;
	unsigned char reserved_2[1];
	void* reserved_3[2];
	hack_ppeb_ldr_data ldr;
	hack_ptrl_user_process_parameters process_parameters;
	void* reserved_4[3];
	void* atl_thunks_list_ptr;
	void* reserved_5;
	unsigned long reserved_6;
	void* reserved_7;
	unsigned long reserved_8;
	unsigned long atl_thunks_list_ptr_32;
	void* reserved_9[45];
	unsigned char reserved_10[96];
	pps_post_process_init_routine post_process_init_routine;
	unsigned char reserved_11[128];
	void* reserved_12[1];
	unsigned long session_id;

} hack_peb, * hack_ppeb;

struct LDR_DATA_TABLE_ENTRY_T {
	hack_list_entry InLoadOrderLinks;
	hack_list_entry InMemoryOrderLinks;
	hack_list_entry InInitializationOrderLinks;
	const char* DllBase;
	const char* EntryPoint;
	union {
		unsigned long SizeOfImage;
		const char* _dummy;
	};
	UNICODE_STRING_T FullDllName;
	UNICODE_STRING_T BaseDllName;
};

/*typedef struct _IMAGE_DOS_HEADER { // DOS .EXE header
	hack_word   e_magic;                     // Magic number
	hack_word   e_cblp;                      // Bytes on last page of file
	hack_word   e_cp;                        // Pages in file
	hack_word   e_crlc;                      // Relocations
	hack_word   e_cparhdr;                   // Size of header in paragraphs
	hack_word   e_minalloc;                  // Minimum extra paragraphs needed
	hack_word   e_maxalloc;                  // Maximum extra paragraphs needed
	hack_word   e_ss;                        // Initial (relative) SS value
	hack_word   e_sp;                        // Initial SP value
	hack_word   e_csum;                      // Checksum
	hack_word   e_ip;                        // Initial IP value
	hack_word   e_cs;                        // Initial (relative) CS value
	hack_word   e_lfarlc;                    // File address of relocation table
	hack_word   e_ovno;                      // Overlay number
	hack_word   e_res[4];                    // Reserved words
	hack_word   e_oemid;                     // OEM identifier (for e_oeminfo)
	hack_word   e_oeminfo;                   // OEM information; e_oemid specific
	hack_word   e_res2[10];                  // Reserved words
	hack_long   e_lfanew;                    // File address of new exe header
} IMAGE_DOS_HEADER, * PIMAGE_DOS_HEADER;


typedef struct _IMAGE_FILE_HEADER {
	hack_word    Machine;
	hack_word    NumberOfSections;
	hack_dword   TimeDateStamp;
	hack_dword   PointerToSymbolTable;
	hack_dword   NumberOfSymbols;
	hack_word    SizeOfOptionalHeader;
	hack_word    Characteristics;
} IMAGE_FILE_HEADER, * PIMAGE_FILE_HEADER;

typedef struct _IMAGE_DATA_DIRECTORY {
	hack_dword   VirtualAddress;
	hack_dword   Size;
} IMAGE_DATA_DIRECTORY, * PIMAGE_DATA_DIRECTORY;

typedef struct _IMAGE_OPTIONAL_HEADER64 {
	hack_word        Magic;
	hack_byte        MajorLinkerVersion;
	hack_byte        MinorLinkerVersion;
	hack_dword       SizeOfCode;
	hack_dword       SizeOfInitializedData;
	hack_dword       SizeOfUninitializedData;
	hack_dword       AddressOfEntryPoint;
	hack_dword       BaseOfCode;
	hack_ulonglong   ImageBase;
	hack_dword       SectionAlignment;
	hack_dword       FileAlignment;
	hack_word        MajorOperatingSystemVersion;
	hack_word        MinorOperatingSystemVersion;
	hack_word        MajorImageVersion;
	hack_word        MinorImageVersion;
	hack_word        MajorSubsystemVersion;
	hack_word        MinorSubsystemVersion;
	hack_dword       Win32VersionValue;
	hack_dword       SizeOfImage;
	hack_dword       SizeOfHeaders;
	hack_dword       CheckSum;
	hack_word        Subsystem;
	hack_word        DllCharacteristics;
	hack_ulonglong   SizeOfStackReserve;
	hack_ulonglong   SizeOfStackCommit;
	hack_ulonglong   SizeOfHeapReserve;
	hack_ulonglong   SizeOfHeapCommit;
	hack_dword       LoaderFlags;
	hack_dword       NumberOfRvaAndSizes;
	IMAGE_DATA_DIRECTORY DataDirectory[16];
} IMAGE_OPTIONAL_HEADER64, * PIMAGE_OPTIONAL_HEADER64;

typedef struct _IMAGE_NT_HEADERS64 {
	hack_dword Signature;
	IMAGE_FILE_HEADER FileHeader;
	IMAGE_OPTIONAL_HEADER64 OptionalHeader;
} IMAGE_NT_HEADERS64, * PIMAGE_NT_HEADERS64;

typedef struct _IMAGE_EXPORT_DIRECTORY {
	hack_dword   Characteristics;
	hack_dword   TimeDateStamp;
	hack_word    MajorVersion;
	hack_word    MinorVersion;
	hack_dword   Name;
	hack_dword   Base;
	hack_dword   NumberOfFunctions;
	hack_dword   NumberOfNames;
	hack_dword   AddressOfFunctions;     // RVA from base of image
	hack_dword   AddressOfNames;         // RVA from base of image
	hack_dword   AddressOfNameOrdinals;  // RVA from base of image
} IMAGE_EXPORT_DIRECTORY, * PIMAGE_EXPORT_DIRECTORY;


typedef IMAGE_NT_HEADERS64 IMAGE_NT_HEADERS;*/


#define contain_record(address, type, field) ((type *)( \
                                                  (char*)(address) - \
                                                  (hack_ulong_ptr)(&((type *)0)->field)))

extern "C" int _fltused = 0;

void atexit(void* function) {

}



namespace crt {


	static double 	sin_off_tbl[] = { 0.0, -3.1415926535 / 2., 0, -3.1415926535 / 2. };
	static double 	sin_sign_tbl[] = { 1,-1,-1,1 };

	static double 	cos_off_tbl[] = { 0.0, -3.1415926535 / 2., 0, -3.1415926535 / 2. };
	static double 	cos_sign_tbl[] = { 1,-1,-1,1 };

	int custom_fabs(int _X)
	{
		int s = _X >> 31;
		return (_X ^ s) - s;
	}

	double sinddd(double x)
	{
		int quadrant;
		double x2, result;

		/* Calculate the quadrant */
		quadrant = (int)(x * (2. / 3.1415926535));

		/* Get offset inside quadrant */
		x = x - quadrant * (3.1415926535 / 2.);

		/* Normalize quadrant to [0..3] */
		quadrant = (quadrant - 1) & 0x3;

		/* Fixup value for the generic function */
		x += sin_off_tbl[quadrant];

		/* Calculate the negative of the square of x */
		x2 = -(x * x);

		result = 0;

#if (PRECISION >= 10)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 * 17 * 18 * 19 * 20);
		result *= x2;
#endif
#if (PRECISION >= 9)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 * 17 * 18);
		result *= x2;
#endif
#if (PRECISION >= 8)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16);
		result *= x2;
#endif
#if (PRECISION >= 7)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14);
		result *= x2;
#endif
#if (PRECISION >= 6)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12);
		result *= x2;
#endif
#if (PRECISION >= 5)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10);
		result *= x2;
#endif
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8);
		result *= x2;

		result += 1. / (1. * 2 * 3 * 4 * 5 * 6);
		result *= x2;

		result += 1. / (1. * 2 * 3 * 4);
		result *= x2;

		result += 1. / (1. * 2);
		result *= x2;

		result += 1;

		/* Apply correct sign */
		result *= sin_sign_tbl[quadrant];

		return result;
	}
	double cosddd(double x)
	{

		int quadrant;
		double x2, result;

		/* Calculate the quadrant */
		quadrant = (int)(x * (2. / 3.1415926535));

		/* Get offset inside quadrant */
		x = x - quadrant * (3.1415926535 / 2.);

		/* Normalize quadrant to [0..3] */
		quadrant = quadrant & 0x3;

		/* Fixup value for the generic function */
		x += cos_off_tbl[quadrant];

		/* Calculate the negative of the square of x */
		x2 = -(x * x);

		result = 0;

#if (PRECISION >= 10)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 * 17 * 18 * 19 * 20);
		result *= x2;
#endif
#if (PRECISION >= 9)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 * 17 * 18);
		result *= x2;
#endif
#if (PRECISION >= 8)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16);
		result *= x2;
#endif
#if (PRECISION >= 7)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14);
		result *= x2;
#endif
#if (PRECISION >= 6)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12);
		result *= x2;
#endif
#if (PRECISION >= 5)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10);
		result *= x2;
#endif
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8);
		result *= x2;

		result += 1. / (1. * 2 * 3 * 4 * 5 * 6);
		result *= x2;

		result += 1. / (1. * 2 * 3 * 4);
		result *= x2;

		result += 1. / (1. * 2);
		result *= x2;

		result += 1;

		/* Apply correct sign */
		result *= cos_sign_tbl[quadrant];

		return result;
	}


	float custom_sqrtf(float _X)
	{
		// Check for negative Input
		if (_X < 0)
		{
			return (-(double)(((double)(1e+300 * 1e+300)) * 0.0));
		}

		// Check for zero or near-zero Input
		if (_X <= 1.192092896e-07)
		{
			return 0.0;
		}

		// Initialize the approximation
		double MySqrt = _X;

		// Iterate the approximation until it converges
		while (custom_fabs(MySqrt - _X / MySqrt) > 1.192092896e-07 * MySqrt)
		{
			MySqrt = (MySqrt + _X / MySqrt) / 2.0;
		}

		return MySqrt;
	}

	float c_powf(float base, float exponent)
	{
		float result = 1;
		for (int i = 0; i < exponent; i++) {
			result *= base;
		}
		return result;
	}

	float custom_sinf(float _X)
	{
		return sinddd(_X);
		//return _mm_cvtss_f32(_mm_sin_ps(_mm_set_ss(_X)));
		//return 0;
	}

	float custom_cosf(float _X)
	{
		return cosddd(_X);
		//return _mm_cvtss_f32(_mm_cos_ps(_mm_set_ss(_X)));
	}

	



	float custom_tanf(float _X)
	{
		return (custom_sinf(_X) / custom_cosf(_X));
		//return 0;
	}

	int custom_compare(const char* X, const char* Y)
	{
		while (*X && *Y) {
			if (*X != *Y) {
				return 0;
			}
			X++;
			Y++;
		}

		return (*Y == '\0');
	}

	int custom_wcompare(const wchar_t* X, const wchar_t* Y)
	{
		while (*X && *Y) {
			if (*X != *Y) {
				return 0;
			}
			X++;
			Y++;
		}

		return (*Y == L'\0');
	}

	const wchar_t* custom_wcsstr(const wchar_t* X, const wchar_t* Y)
	{
		while (*X != L'\0') {
			if ((*X == *Y) && custom_wcompare(X, Y)) {
				return X;
			}
			X++;
		}
		return NULL;
	}

	const char* custom_strstr(const char* X, const char* Y)
	{
		while (*X != '\0') {
			if ((*X == *Y) && custom_compare(X, Y)) {
				return X;
			}
			X++;
		}
		return NULL;
	}

	int custom_strlen(const char* string)
	{
		int cnt = 0;
		if (string)
		{
			for (; *string != 0; ++string) ++cnt;
		}
		return cnt;
	}

	int custom_wcslen(const wchar_t* string)
	{
		int cnt = 0;
		if (string)
		{
			for (; *string != 0; ++string) ++cnt;
		}
		return cnt;
	}

	char* custom_strcpy(char* destination, const char* source) {
		char* dest = destination;

		while (*source) {
			*dest = *source;
			++dest;
			++source;
		}

		*dest = '\0';

		return destination;
	}

	wchar_t* custom_wcscpy(wchar_t* destination, const wchar_t* source) {
		wchar_t* dest = destination;

		while (*source) {
			*dest = *source;
			++dest;
			++source;
		}

		*dest = L'\0';

		return destination;
	}

	int custom_isspace(int c)
	{
		return (c == '\t' || c == '\n' ||
			c == '\v' || c == '\f' || c == '\r' || c == ' ' ? 1 : 0);
	}

	int custom_isdigit(int c)
	{
		return (c >= '0' && c <= '9' ? 1 : 0);
	}

	int custom_isalpha(int c)
	{
		return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ? 1 : 0);
	}

	char custom_isupper(unsigned char c)
	{
		if (c >= (unsigned char)('A') && c <= (unsigned char)('Z'))
			return 1;
	}

	void* custopm_memcpy(void* dest, const void* src, unsigned __int64 count)
	{
		
		char* char_dest = (char*)dest;
		char* char_src = (char*)src;
		if ((char_dest <= char_src) || (char_dest >= (char_src + count)))
		{
			while (count > 0)
			{
				*char_dest = *char_src;
				char_dest++;
				char_src++;
				count--;
			}
		}
		else
		{
			char_dest = (char*)dest + count - 1;
			char_src = (char*)src + count - 1;
			while (count > 0)
			{
				*char_dest = *char_src;
				char_dest--;
				char_src--;
				count--;
			}
		}
		return dest;
		
	}

	int custom_strcmp(const char* p1, const char* p2)
	{
		const unsigned char* s1 = (const unsigned char*)p1;
		const unsigned char* s2 = (const unsigned char*)p2;

		unsigned char c1, c2;

		do
		{
			c1 = (unsigned char)*s1++;
			c2 = (unsigned char)*s2++;

			if (c1 == '\0') return c1 - c2;

		} while (c1 == c2);

		return c1 - c2;
	}

	int custom_wcsicmp(const wchar_t* string1, const wchar_t* string2)
	{
		wchar_t c1, c2;
		do
		{
			c1 = *string1++;
			c2 = *string2++;
			if (c2 == L'\0')
				return c1 - c2;
		} while (c1 == c2);
		return c1 < c2 ? -1 : 1;
	}

	unsigned custom_rand(int start, int end)
	{
		int start_range = start;
		int end_range = end;

		static unsigned int rand = 0xACE1U;

		if (start_range == end_range)
		{
			return start_range;
		}

		rand += 0x3AD;
		rand %= (end_range - start_range + 1);

		while (rand < start_range)
		{
			rand = rand + (end_range - start_range + 1);
		}

		return rand;
	}

	void* custom_memset(void* dst0, register int c0, unsigned int len)
	{
		
			unsigned int i;
			unsigned int fill;
			unsigned int chunks = len / sizeof(fill);
			char* char_dest = (char*)dst0;
			unsigned int* uint_dest = (unsigned int*)dst0;
			fill = (c0 << 24) + (c0 << 16) + (c0 << 8) + c0;

			for (i = len; i > chunks * sizeof(fill); i--) {
				char_dest[i - 1] = c0;
			}

			for (i = chunks; i > 0; i--) {
				uint_dest[i - 1] = fill;
			}

			return dst0;
		
	}

	void* custom_memcpy(void* dest, const void* src, size_t count)
	{
		char* char_dest = static_cast<char*>(dest);
		const char* char_src = static_cast<const char*>(src);

		if (char_dest < char_src) {
			for (size_t i = 0; i < count; i++) {
				char_dest[i] = char_src[i];
			}
		}
		else if (char_dest > char_src) {
			for (size_t i = count; i > 0; i--) {
				char_dest[i - 1] = char_src[i - 1];
			}
		}
		return dest;
	}

	int custom_wcscpy_s(wchar_t* dest, size_t destSize, const wchar_t* src)
	{
		if (dest == nullptr || destSize == 0)
		{
			// Invalid destination buffer
			return -1;
		}

		if (src == nullptr)
		{
			// Invalid source string
			*dest = L'\0';
			return -1;
		}

		size_t srcLength = custom_wcslen(src);
		if (srcLength >= destSize)
		{
			// Source string too long for destination buffer
			*dest = L'\0';
			return -1;
		}

		custom_wcscpy(dest, src);
		return 0;
	}

	size_t custom_mbstowcs(wchar_t* dest, const char* src, size_t max)
	{
		size_t count = 0;

		while (count < max)
		{
			if (*src == '\0')  // Reached end of source string
			{
				*dest = L'\0';
				return count;
			}
			else if ((*src & 0x80) == 0)  // ASCII character
			{
				*dest = static_cast<wchar_t>(*src);
				++src;
				++dest;
				++count;
			}
			else  // Multi-byte character
			{
				unsigned char firstByte = static_cast<unsigned char>(*src);
				unsigned char numBytes;

				if ((firstByte & 0xE0) == 0xC0)  // 2-byte character
				{
					*dest = (static_cast<wchar_t>(firstByte & 0x1F) << 6) |
						(static_cast<wchar_t>(src[1] & 0x3F));
					numBytes = 2;
				}
				else if ((firstByte & 0xF0) == 0xE0)  // 3-byte character
				{
					*dest = (static_cast<wchar_t>(firstByte & 0x0F) << 12) |
						(static_cast<wchar_t>((src[1] & 0x3F) << 6)) |
						(static_cast<wchar_t>(src[2] & 0x3F));
					numBytes = 3;
				}
				else if ((firstByte & 0xF8) == 0xF0)  // 4-byte character
				{
					*dest = (static_cast<wchar_t>(firstByte & 0x07) << 18) |
						(static_cast<wchar_t>((src[1] & 0x3F) << 12)) |
						(static_cast<wchar_t>((src[2] & 0x3F) << 6)) |
						(static_cast<wchar_t>(src[3] & 0x3F));
					numBytes = 4;
				}
				else
				{
					// Invalid multi-byte character
					*dest = L'\0';
					return static_cast<size_t>(-1);
				}

				src += numBytes;
				++dest;
				++count;
			}
		}

		// Insufficient space in destination buffer
		*dest = L'\0';
		return static_cast<size_t>(-1);
	}

	const char* to_string(int n)
	{
		int m = n;
		char s[100]; //max
		char ss[100]; //max
		int i = 0, j = 0;
		if (n < 0)
		{
			m = 0 - m;
			j = 1;
			ss[0] = '-';
		}
		while (m > 0)
		{
			s[i++] = m % 10 + '0';
			m /= 10;
		}
		s[i] = '\0';
		i = i - 1;
		while (i >= 0)
		{
			ss[j++] = s[i--];
		}
		ss[j] = '\0';
		return ss;
	}

	const wchar_t* to_wstring(int n)
	{
		int m = n;
		wchar_t s[100]; //max
		wchar_t ss[100]; //max
		int i = 0, j = 0;
		if (n < 0)
		{
			m = 0 - m;
			j = 1;
			ss[0] = '-';
		}
		while (m > 0)
		{
			s[i++] = m % 10 + '0';
			m /= 10;
		}
		s[i] = '\0';
		i = i - 1;
		while (i >= 0)
		{
			ss[j++] = s[i--];
		}
		ss[j] = '\0';
		return ss;
	}
}