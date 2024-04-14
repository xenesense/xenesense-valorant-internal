#pragma once


extern "C"  void spoofcall_stub();

extern "C" uintptr_t proxy_call_returns[];

extern "C" size_t proxy_call_fakestack_size;
extern "C" uintptr_t * proxy_call_fakestack;

#define FIELD_OFFSET(type, field)    ((hack_long)(hack_LONG_PTR)&(((type *)0)->field))

#define IMAGE_FIRST_SECTION( ntheader ) ((PIMAGE_SECTION_HEADER)        \
    ((hack_ulong_ptr)(ntheader) +                                            \
     FIELD_OFFSET( IMAGE_NT_HEADERS, OptionalHeader ) +                 \
     ((ntheader))->FileHeader.SizeOfOptionalHeader   \
    ))



void initialize_spoofcall(hack_uint8_t* module_, hack_uint32_t max_fakestack = 12)
{
	Map<hack_int8_t, Vector<uintptr_t>> proxy_clean_returns;

	auto dos = reinterpret_cast<IMAGE_DOS_HEADER*>(module_);
	auto nt = reinterpret_cast<IMAGE_NT_HEADERS*>(module_ + dos->e_lfanew);
	auto image_size = nt->OptionalHeader.SizeOfImage;

	auto section = IMAGE_FIRST_SECTION(nt);

	MEMORY_BASIC_INFORMATION mbi;

	for (auto i = 0; i < nt->FileHeader.NumberOfSections; i++)
	{
		if ((section->Characteristics & 0x02000000) == 0) //IMAGE_SCN_MEM_DISCARDABLE
		{
			auto address = module_ + section->VirtualAddress;
			while (true)
			{
				crt::custom_memset(&mbi, 0, sizeof(mbi));

				if (!o_virtualquery(address, &mbi, sizeof(mbi))) break;

				auto base_page = (hack_uint8_t*)mbi.BaseAddress;

				if (mbi.Protect == 0x20 ||
					mbi.Protect == 0x40 ||
					mbi.Protect == 0x80)
				{
					for (auto i = 0u; i < (mbi.RegionSize - 0x10); i++)
					{
						//add rsp, xx
						//ret
						if (base_page[i] == 0x48 &&
							base_page[i + 1] == 0x83 &&
							base_page[i + 2] == 0xC4 &&
							base_page[i + 4] == 0xC3)
						{


							proxy_clean_returns[base_page[i + 3]].push_back(uintptr_t(base_page + i));
						}
					}
				}
				address = base_page + mbi.RegionSize;
				if (address >= (module_ + section->VirtualAddress + section->Misc.VirtualSize))
					break;
			}
		}
		section++;
	}


	Vector<hack_int8_t> proxy_clean_returns_keys;
	proxy_clean_returns_keys.reserve(proxy_clean_returns.size());

	Vector<uintptr_t> fakestack;
	fakestack.reserve(max_fakestack * 2);


	for (auto& it : proxy_clean_returns)
	{
		const auto index = (it.first / sizeof(uintptr_t));
		proxy_call_returns[index] = it.second.at(crt::custom_rand(10, 30) % it.second.size());

		if (index < 10 && index % 2 == 1)
			proxy_clean_returns_keys.push_back(it.first);
	}

	while (fakestack.size() < max_fakestack)
	{
		const auto pseudo_random_number = crt::custom_rand(10, 30);
		const auto return_length = proxy_clean_returns_keys.at(pseudo_random_number % proxy_clean_returns_keys.size());
		const auto params = (return_length / sizeof(uintptr_t));
		const auto& address_array = proxy_clean_returns[return_length];
		const auto random_address = address_array.at(pseudo_random_number % address_array.size());

		fakestack.push_back(random_address);
		for (auto i = 0u; i < params; i++)
			fakestack.push_back(uintptr_t(module_) + (crt::custom_rand(10, 30) % image_size));
	}

	proxy_call_fakestack_size = fakestack.size();
	proxy_call_fakestack = new uintptr_t[fakestack.size()];
	crt::custom_memcpy(proxy_call_fakestack, fakestack.data(), proxy_call_fakestack_size * sizeof(uintptr_t));



}