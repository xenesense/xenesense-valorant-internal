#pragma once

extern "C" long nt_read_virtual_memory(hack_handle process, void* address, void* buffer, size_t number_of_bytes_to_read, size_t * number_of_bytes_readed);
extern "C" long nt_write_virtual_memory(hack_handle process, void* address, void* buffer, size_t number_of_bytes_to_write, size_t * number_of_bytes_written);

extern "C" uintptr_t __asm_get_peb();


//typedef short(__stdcall* PFN_GetAsyncKeyState)(int);
//typedef hack_uint(__stdcall* PFN_MapVirtualKeyA)(hack_uint uCode, hack_uint uMapType);
//typedef int(__stdcall* PFN_GetKeyNameTextA)(hack_long lParam, hack_LPSTR lpString, int cchSize);
typedef hack_lpvoid(__stdcall* PFN_VirtualAlloc)(hack_lpvoid, hack_size_t, hack_dword, hack_dword);
typedef hack_bool(__stdcall* PFN_VirtualFree)(hack_lpvoid, hack_size_t, hack_dword);
typedef LPVOID(__stdcall* VirtualQueryFunc)(LPCVOID, PMEMORY_BASIC_INFORMATION, size_t);

typedef void (__stdcall* PFN_mouse_event)(
	hack_dword dwFlags,
	hack_dword dx,
	hack_dword dy,
	hack_dword dwData,
	hack_ulong_ptr dwExtraInfo);

/*typedef int(__stdcall* ConnectFunction)(h_SOCKET, const struct h_sockaddr*, int);
typedef int (__stdcall* SendFunction)(h_SOCKET, const char*, int, int);
typedef int (__stdcall* RecvFunction)(h_SOCKET, char*, int, int);
typedef int (__stdcall* CloseSocketFunction)(h_SOCKET);
typedef int (__stdcall* WSACleanupFunction)();
typedef int (__stdcall* WSAStartupFunction)(hack_word, h_LPWSADATA);
typedef int (__stdcall* InetPtonFunction)(int, hack_PCSTR, hack_pvoid);
typedef h_SOCKET(__stdcall* SocketFunction)(int, int, int);
typedef hack_u_short(__stdcall* HtonsFunction)(hack_u_short);*/



//PFN_GetAsyncKeyState o_getasynckeystate;
//PFN_MapVirtualKeyA o_mapvirtualkeya;
//PFN_GetKeyNameTextA o_getkeynametexta;
PFN_VirtualAlloc o_virtualalloc;
PFN_VirtualFree o_virtualfree;
VirtualQueryFunc o_virtualquery;
PFN_mouse_event o_mouseevent;




class memory {
public:

	static bool read_virtual_memory(uintptr_t address, hack_uint8_t* buffer, size_t size)
	{
		size_t number_of_bytes_readed = {};
		return nt_read_virtual_memory(hack_handle(-1), reinterpret_cast<void*>(address), buffer, size, &number_of_bytes_readed) == 0;
	}

	static bool write_virtual_memory(uintptr_t address, hack_uint8_t* buffer, size_t size)
	{
		size_t number_of_bytes_written = {};
		return nt_write_virtual_memory(hack_handle(-1), reinterpret_cast<void*>(address), buffer, size, &number_of_bytes_written) == 0;
	}




	template<typename R>
	static R read(uintptr_t address)
	{
		hack_uint8_t buffer[sizeof(R)] = {};
		if (!read_virtual_memory(address, buffer, sizeof(R))) return {};
		return *reinterpret_cast<R*>(buffer);
	}

	template<typename W>
	static void write(uintptr_t address, W value)
	{
		write_virtual_memory(address, reinterpret_cast<hack_uint8_t*>(&value), sizeof(W));
	}



	static uintptr_t get_module_base()
	{
		return *(uintptr_t*)(__asm_get_peb() + 0x10);
	}


	static void vmt(void* addr, void* pDes, int index, void** ret)
	{
		uintptr_t* vtable = *(uintptr_t**)addr;

		int methods = 0;
		while (*(uintptr_t*)((uintptr_t)vtable + (methods * 0x8)))
		{
			++methods;
		}

		// Allocate a new vtable on heap and copy the original vtable
		hack_uint64_t* vtable_buf = new hack_uint64_t[methods + 1];
		crt::custom_memcpy(vtable_buf, vtable, methods * 0x8);

		// Add a null terminator at the end of the new vtable for safety
		vtable_buf[methods] = 0;

		// Save the original function pointer to return it
		*ret = (void*)vtable_buf[index];

		// Overwrite the function at the given index with our own function
		vtable_buf[index] = (uintptr_t)(pDes);

		// Finally, replace the vtable in the original object with our new vtable
		*(hack_uint64_t**)addr = vtable_buf;

		// Do NOT delete[] vtable_buf here
	}



	


	static uintptr_t get_proc_address(const char* functionName)
	{
		hack_ppeb peb = (hack_ppeb)__asm_get_peb();
		auto ldr = peb->ldr;
		auto module_list = (hack_p_list_entry)ldr->in_memory_order_module_list.flink;

		module_list = module_list->flink;

		while (module_list != (hack_p_list_entry)&ldr->in_memory_order_module_list)
		{
			auto ldr_entry = contain_record(module_list, LDR_DATA_TABLE_ENTRY_T, InMemoryOrderLinks);

			IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)ldr_entry->DllBase;
			IMAGE_NT_HEADERS* ntHeaders = (IMAGE_NT_HEADERS*)((char*)(dosHeader)+dosHeader->e_lfanew);
			IMAGE_DATA_DIRECTORY* dataDirectory = &ntHeaders->OptionalHeader.DataDirectory[0];
			IMAGE_EXPORT_DIRECTORY* exportDirectory = (IMAGE_EXPORT_DIRECTORY*)((char*)(dosHeader)+dataDirectory->VirtualAddress);
			hack_dword* nameTable = (hack_dword*)((char*)(dosHeader)+exportDirectory->AddressOfNames);
			hack_word* ordinalTable = (hack_word*)((char*)(dosHeader)+exportDirectory->AddressOfNameOrdinals);
			hack_dword* functionTable = (hack_dword*)((char*)(dosHeader)+exportDirectory->AddressOfFunctions);

			for (hack_dword i = 0; i < exportDirectory->NumberOfNames; ++i)
			{
				const char* exportName = (const char*)((char*)(dosHeader)+nameTable[i]);
				if (crt::custom_strcmp(exportName, functionName) == 0)
				{
					hack_word ordinal = ordinalTable[i];
				
					
					return (uintptr_t)((char*)(dosHeader)+functionTable[ordinal]);
				}
			}

			module_list = module_list->flink;
		}

		return 0;
	}
	
};