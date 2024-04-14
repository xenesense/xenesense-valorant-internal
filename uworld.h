#pragma once
//
//typedef          __int64 ll;
//typedef unsigned __int64 ull;
//
//
//typedef unsigned int uint;
//typedef unsigned char uchar;
//typedef unsigned short ushort;
//typedef unsigned long ulong;
//
//typedef          char   int8;
//typedef   signed char   sint8;
//typedef unsigned char   uint8;
//typedef          short  int16;
//typedef   signed short  sint16;
//typedef unsigned short  uint16;
//typedef          int    int32;
//typedef   signed int    sint32;
//typedef unsigned int    uint32;
//typedef ll              int64;
//typedef ll              sint64;
//typedef ull             uint64;
//
//
//
//// Generate a reference to pair of operands
//template<class T>  int16 __PAIR__(int8  high, T low) { return (((int16)high) << sizeof(high) * 8) | uint8(low); }
//template<class T>  int32 __PAIR__(int16 high, T low) { return (((int32)high) << sizeof(high) * 8) | uint16(low); }
//template<class T>  int64 __PAIR__(int32 high, T low) { return (((int64)high) << sizeof(high) * 8) | uint32(low); }
//template<class T> uint16 __PAIR__(uint8  high, T low) { return (((uint16)high) << sizeof(high) * 8) | uint8(low); }
//template<class T> uint32 __PAIR__(uint16 high, T low) { return (((uint32)high) << sizeof(high) * 8) | uint16(low); }
//template<class T> uint64 __PAIR__(uint32 high, T low) { return (((uint64)high) << sizeof(high) * 8) | uint32(low); }
//
//// rotate left
//template<class T> T __ROL__(T value, int count)
//{
//	const uint nbits = sizeof(T) * 8;
//
//	if (count > 0)
//	{
//		count %= nbits;
//		T high = value >> (nbits - count);
//		if (T(-1) < 0)
//			high &= ~((T(-1) << count));
//		value <<= count;
//		value |= high;
//	}
//	else
//	{
//		count = -count % nbits;
//		T low = value << (nbits - count);
//		value >>= count;
//		value |= low;
//	}
//	return value;
//}
//
//uint8  __ROL1__(uint8  value, int count) { return __ROL__((uint8)value, count); }
//uint16 __ROL2__(uint16 value, int count) { return __ROL__((uint16)value, count); }
//uint32 __ROL4__(uint32 value, int count) { return __ROL__((uint32)value, count); }
//uint64 __ROL8__(uint64 value, int count) { return __ROL__((uint64)value, count); }
//uint8  __ROR1__(uint8  value, int count) { return __ROL__((uint8)value, -count); }
//uint16 __ROR2__(uint16 value, int count) { return __ROL__((uint16)value, -count); }
//uint32 __ROR4__(uint32 value, int count) { return __ROL__((uint32)value, -count); }
//uint64 __ROR8__(uint64 value, int count) { return __ROL__((uint64)value, -count); }
//
//// carry flag of left shift
//template<class T> int8 __MKCSHL__(T value, uint count)
//{
//	const uint nbits = sizeof(T) * 8;
//	count %= nbits;
//
//	return (value >> (nbits - count)) & 1;
//}
//
//// carry flag of right shift
//template<class T> int8 __MKCSHR__(T value, uint count)
//{
//	return (value >> (count - 1)) & 1;
//}
//
//// sign flag
//template<class T> int8 __SETS__(T x)
//{
//	if (sizeof(T) == 1)
//		return int8(x) < 0;
//	if (sizeof(T) == 2)
//		return int16(x) < 0;
//	if (sizeof(T) == 4)
//		return int32(x) < 0;
//	return int64(x) < 0;
//}
//
//// overflow flag of subtraction (x-y)
//template<class T, class U> int8 __OFSUB__(T x, U y)
//{
//	if (sizeof(T) < sizeof(U))
//	{
//		U x2 = x;
//		int8 sx = __SETS__(x2);
//		return (sx ^ __SETS__(y)) & (sx ^ __SETS__(x2 - y));
//	}
//	else
//	{
//		T y2 = y;
//		int8 sx = __SETS__(x);
//		return (sx ^ __SETS__(y2)) & (sx ^ __SETS__(x - y2));
//	}
//}
//
//// overflow flag of addition (x+y)
//template<class T, class U> int8 __OFADD__(T x, U y)
//{
//	if (sizeof(T) < sizeof(U))
//	{
//		U x2 = x;
//		int8 sx = __SETS__(x2);
//		return ((1 ^ sx) ^ __SETS__(y)) & (sx ^ __SETS__(x2 + y));
//	}
//	else
//	{
//		T y2 = y;
//		int8 sx = __SETS__(x);
//		return ((1 ^ sx) ^ __SETS__(y2)) & (sx ^ __SETS__(x + y2));
//	}
//}
//
//// carry flag of subtraction (x-y)
//template<class T, class U> int8 __CFSUB__(T x, U y)
//{
//	int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
//	if (size == 1)
//		return uint8(x) < uint8(y);
//	if (size == 2)
//		return uint16(x) < uint16(y);
//	if (size == 4)
//		return uint32(x) < uint32(y);
//	return uint64(x) < uint64(y);
//}
//
//// carry flag of addition (x+y)
//template<class T, class U> int8 __CFADD__(T x, U y)
//{
//	int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
//	if (size == 1)
//		return uint8(x) > uint8(x + y);
//	if (size == 2)
//		return uint16(x) > uint16(x + y);
//	if (size == 4)
//		return uint32(x) > uint32(x + y);
//	return uint64(x) > uint64(x + y);
//}
//
//
//
//
//// In the decompilation listing there are some objects declarared as _UNKNOWN
//// because we could not determine their types. Since the C compiler does not
//// accept void item declarations, we replace them by anything of our choice,
//// for example a char:
//
//#define _UNKNOWN char
//
////#ifdef _MSC_VER
////#define snprintf _snprintf
////#define vsnprintf _vsnprintf
////#endif
//
//__forceinline __int64 decrypt_gworld(const hack_uint32_t key, const uintptr_t* state)
//{
//
//	unsigned __int64 v19; // r11
//	unsigned __int64 v20; // r8
//	unsigned __int64 v21; // r9
//	unsigned int v22; // er10
//	unsigned __int64 v23; // rcx
//	unsigned __int64 v24; // rdx
//	unsigned __int64 v25; // rcx
//	int v26; // ebx
//	unsigned int v27; // ecx
//	__int64 v28; // rax
//	unsigned __int64 v29; // r8
//	unsigned __int64 v30; // r8
//	unsigned __int64 v31; // rcx
//	unsigned __int64 v32; // rdx
//	unsigned __int64 v33; // rcx
//
//	v19 = 2685821657736338717i64
//		* ((unsigned int)key ^ (unsigned int)(key << 25) ^ (((unsigned int)key ^ ((unsigned __int64)(unsigned int)key >> 15)) >> 12))
//		% 7;
//	v20 = state[v19];
//	v21 = (2685821657736338717i64
//		* ((unsigned int)key ^ (unsigned int)(key << 25) ^ (((unsigned int)key ^ ((unsigned __int64)(unsigned int)key >> 15)) >> 12))) >> 32;
//	v22 = (unsigned int)v19 % 7;
//	if (!((unsigned int)v19 % 7))
//	{
//		v23 = (2 * (v20 - (unsigned int)(v21 - 1))) ^ ((2 * (v20 - (unsigned int)(v21 - 1))) ^ ((v20
//			- (unsigned int)(v21 - 1)) >> 1)) & 0x5555555555555555i64;
//		v24 = (4 * v23) ^ ((4 * v23) ^ (v23 >> 2)) & 0x3333333333333333i64;
//		v25 = (16 * v24) ^ ((16 * v24) ^ (v24 >> 4)) & 0xF0F0F0F0F0F0F0Fi64;
//		v20 = __ROL8__((v25 << 8) ^ ((v25 << 8) ^ (v25 >> 8)) & 0xFF00FF00FF00FFi64, 32);
//	LABEL_26:
//		v26 = 2 * v19;
//		goto LABEL_27;
//	}
//	if (v22 != 1)
//		goto LABEL_26;
//	v26 = 2 * v19;
//	v20 = __ROL8__(v20 - (unsigned int)(2 * v19 + v21), (unsigned __int8)(((int)v21 + (int)v19) % 0x3Fu) + 1);
//LABEL_27:
//	v27 = v26 + v21;
//	if (v22 == 2)
//		v20 = ~(v20 - v27);
//	switch (v22)
//	{
//	case 3u:
//		v28 = 2 * ((2 * v20) ^ ((2 * v20) ^ (v20 >> 1)) & 0x5555555555555555i64);
//		v20 = v28 ^ (v28 ^ (((2 * v20) ^ ((2 * v20) ^ (v20 >> 1)) & 0x5555555555555555i64) >> 1)) & 0x5555555555555555i64;
//		break;
//	case 4u:
//		v29 = __ROR8__(v20, (unsigned __int8)(v27 % 0x3F) + 1);
//		v20 = (2 * v29) ^ ((2 * v29) ^ (v29 >> 1)) & 0x5555555555555555i64;
//		break;
//	case 5u:
//		v30 = __ROR8__(v20, (unsigned __int8)(v27 % 0x3F) + 1);
//		v31 = (2 * v30) ^ ((2 * v30) ^ (v30 >> 1)) & 0x5555555555555555i64;
//		v32 = (4 * v31) ^ ((4 * v31) ^ (v31 >> 2)) & 0x3333333333333333i64;
//		v33 = (16 * v32) ^ ((16 * v32) ^ (v32 >> 4)) & 0xF0F0F0F0F0F0F0Fi64;
//		v20 = __ROL8__((v33 << 8) ^ ((v33 << 8) ^ (v33 >> 8)) & 0xFF00FF00FF00FFi64, 32);
//		break;
//	case 6u:
//		v20 = ~v20 - (unsigned int)(v21 + v19);
//		break;
//	}
//	return v20 ^ (unsigned int)key;
//}
//
//__forceinline __int64 decrypt_gworld(const hack_uint32_t key, const uintptr_t* state)
//{
//
//	unsigned __int64 v19; // r11
//	unsigned __int64 v20; // r8
//	unsigned __int64 v21; // r9
//	unsigned int v22; // er10
//	unsigned __int64 v23; // rcx
//	unsigned __int64 v24; // rdx
//	unsigned __int64 v25; // rcx
//	int v26; // ebx
//	unsigned int v27; // ecx
//	__int64 v28; // rax
//	unsigned __int64 v29; // r8
//	unsigned __int64 v30; // r8
//	unsigned __int64 v31; // rcx
//	unsigned __int64 v32; // rdx
//	unsigned __int64 v33; // rcx
//
//	v19 = 2685821657736338717i64
//		* ((unsigned int)key ^ (unsigned int)(key << 25) ^ (((unsigned int)key ^ ((unsigned __int64)(unsigned int)key >> 15)) >> 12))
//		% 7;
//	v20 = state[v19];
//	v21 = (2685821657736338717i64
//		* ((unsigned int)key ^ (unsigned int)(key << 25) ^ (((unsigned int)key ^ ((unsigned __int64)(unsigned int)key >> 15)) >> 12))) >> 32;
//	v22 = (unsigned int)v19 % 7;
//	if (!((unsigned int)v19 % 7))
//	{
//		v23 = (2 * (v20 - (unsigned int)(v21 - 1))) ^ ((2 * (v20 - (unsigned int)(v21 - 1))) ^ ((v20
//			- (unsigned int)(v21 - 1)) >> 1)) & 0x5555555555555555i64;
//		v24 = (4 * v23) ^ ((4 * v23) ^ (v23 >> 2)) & 0x3333333333333333i64;
//		v25 = (16 * v24) ^ ((16 * v24) ^ (v24 >> 4)) & 0xF0F0F0F0F0F0F0Fi64;
//		v20 = __ROL8__((v25 << 8) ^ ((v25 << 8) ^ (v25 >> 8)) & 0xFF00FF00FF00FFi64, 32);
//	LABEL_26:
//		v26 = 2 * v19;
//		goto LABEL_27;
//	}
//	if (v22 != 1)
//		goto LABEL_26;
//	v26 = 2 * v19;
//	v20 = __ROL8__(v20 - (unsigned int)(2 * v19 + v21), (unsigned __int8)(((int)v21 + (int)v19) % 0x3Fu) + 1);
//LABEL_27:
//	v27 = v26 + v21;
//	if (v22 == 2)
//		v20 = ~(v20 - v27);
//	switch (v22)
//	{
//	case 3u:
//		v28 = 2 * ((2 * v20) ^ ((2 * v20) ^ (v20 >> 1)) & 0x5555555555555555i64);
//		v20 = v28 ^ (v28 ^ (((2 * v20) ^ ((2 * v20) ^ (v20 >> 1)) & 0x5555555555555555i64) >> 1)) & 0x5555555555555555i64;
//		break;
//	case 4u:
//		v29 = __ROR8__(v20, (unsigned __int8)(v27 % 0x3F) + 1);
//		v20 = (2 * v29) ^ ((2 * v29) ^ (v29 >> 1)) & 0x5555555555555555i64;
//		break;
//	case 5u:
//		v30 = __ROR8__(v20, (unsigned __int8)(v27 % 0x3F) + 1);
//		v31 = (2 * v30) ^ ((2 * v30) ^ (v30 >> 1)) & 0x5555555555555555i64;
//		v32 = (4 * v31) ^ ((4 * v31) ^ (v31 >> 2)) & 0x3333333333333333i64;
//		v33 = (16 * v32) ^ ((16 * v32) ^ (v32 >> 4)) & 0xF0F0F0F0F0F0F0Fi64;
//		v20 = __ROL8__((v33 << 8) ^ ((v33 << 8) ^ (v33 >> 8)) & 0xFF00FF00FF00FFi64, 32);
//		break;
//	case 6u:
//		v20 = ~v20 - (unsigned int)(v21 + v19);
//		break;
//	}
//	return v20 ^ (unsigned int)key;
//}
//
//
//inline uobject* find_uworld()
//{
//	static uintptr_t GWorld = 0;
//	struct state_class { uintptr_t keys[7]; };
//
//	if (!GWorld)
//	{
//		const auto state = memory::read<state_class>(cached::base_address + offsets::uworld_state); if (!&state) return 0;
//		const auto key = memory::read<uintptr_t>(cached::base_address + offsets::uworld_state + 0x38); if (!key) return 0;
//		GWorld = decrypt_gworld(key, (uintptr_t*)&state);
//	}
//
//	if (!GWorld) return 0;
//	return (uobject*)memory::read<uintptr_t>(GWorld);
//}
//