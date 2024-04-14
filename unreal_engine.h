#pragma once


namespace sdk
{
	namespace unreal
	{
		template<class type> class tarray {
		public: friend class fstring;
		public:
			tarray() : data(nullptr), count(hack_int32_t()), maxx(hack_int32_t()) { }
			tarray(type* data, hack_int32_t count, hack_int32_t maxx) : data(data), count(count), maxx(maxx) { }

			const bool is_valid() const
			{
				return !(this->data == nullptr);
			}

			const hack_int32_t size() const
			{
				return this->count;
			}

			type operator[](hack_int32_t index)
			{
				//return data[index];

				return (type)memory::read<uintptr_t>(uintptr_t(this->data) + index * sizeof(type));
				//return *(type*)(this->data + index * sizeof(type));
			}

			const type& operator[](hack_int32_t index) const
			{
				//return data[index];
				return (type&)memory::read<uintptr_t>(uintptr_t(this->data) + index * sizeof(type));
			}

			type* get_data() {
				return data;
			}

			bool is_valid_index(hack_int32_t index) const
			{
				return index < this->size();
			}

		protected:
			type* data;
			hack_int32_t count;
			hack_int32_t maxx;
		};

		template<class type> class enum_as_byte {
		public:
			enum_as_byte() { }
			enum_as_byte(type value) : value(static_cast<hack_uint8_t>(value)) { }

			explicit enum_as_byte(hack_int32_t value) : value(static_cast<hack_uint8_t>(value)) { }
			explicit enum_as_byte(hack_uint8_t value) : value(value) { }

			operator type() const { return type(value); }
			type get() const { return type(value); }

		private:
			hack_uint8_t value;
		};

		class fstring : public tarray<wchar_t> {
		public:
			fstring() {}
			fstring(const wchar_t* other)
			{
				if (this->maxx = this->count = *other ? static_cast<hack_int32_t>(crt::custom_wcslen(other)) + 1 : 0)
					this->data = const_cast<wchar_t*>(other);
			};

			const wchar_t* c_str() const
			{
				return this->data;
			}
		};

		class ftextdata {
		public:

			char pad_0x0000[0x28];  //0x0000
			wchar_t* Name;          //0x0028 
			__int32 Length;         //0x0030 
		};

		struct  ftext {
			ftextdata* Data;
			char UnknownData[0x10];

			wchar_t* get() const {
				if (Data)
					return Data->Name;

				return nullptr;
			}
		};

		class fname {
		public:
			fname() : comparison_index(hack_uint32_t()), number(hack_int32_t()) {};
			fname(hack_uint32_t index) : comparison_index(index), number(hack_int32_t()) {};

			bool operator==(const fname& other) const noexcept {
				return this->comparison_index == other.comparison_index;
			};

		public:
			hack_uint32_t comparison_index;
			hack_int32_t number;
			hack_int32_t unk_1;
		};

		struct fkey
		{
			fname KeyName;
			unsigned char Padding_00[0x14];
		};




		


		struct fmatrix2 {
			union {
				struct {
					float        _11, _12, _13, _14;
					float        _21, _22, _23, _24;
					float        _31, _32, _33, _34;
					float        _41, _42, _43, _44;

				};
				float m[4][4];
			};
		};

		
		class fvector2d {
		public:
			fvector2d() : x(0.f), y(0.f) {}
			fvector2d(float x, float y) : x(x), y(y) {}

			fvector2d operator + (const fvector2d& other) const { return { this->x + other.x, this->y + other.y }; }
			fvector2d operator - (const fvector2d& other) const { return { this->x - other.x, this->y - other.y }; }
			fvector2d operator * (float scalar) const { return { this->x * scalar, this->y * scalar }; }
			fvector2d operator / (float divide) const { return { this->x / divide, this->y / divide }; }

			fvector2d& operator *= (const float other) { this->x *= other; this->y *= other; return *this; }
			fvector2d& operator /= (const float other) { this->x /= other; this->y /= other; return *this; }

			fvector2d& operator =  (const fvector2d& other) { this->x = other.x; this->y = other.y; return *this; }
			fvector2d& operator += (const fvector2d& other) { this->x += other.x; this->y += other.y; return *this; }
			fvector2d& operator -= (const fvector2d& other) { this->x -= other.x; this->y -= other.y; return *this; }
			fvector2d& operator *= (const fvector2d& other) { this->x *= other.x; this->y *= other.y; return *this; }
			fvector2d& operator /= (const fvector2d& other) { this->x /= other.x; this->y /= other.y; return *this; }

			friend bool operator==(const fvector2d& first, const fvector2d& second)
			{
				return first.x == second.x && first.y == second.y;
			}

			friend bool operator!=(const fvector2d& first, const fvector2d& second)
			{
				return !(first == second);
			}

			bool is_in_screen(int over = 30) {
				if (x > -over && x < cached::screen_width + over && y > -over && y < cached::screen_height + over) {
					return true;
				}
				else {
					return false;
				}
			}

		public:
			float x = 0.f;
			float y = 0.f;
		};

		class fvector {
		public:
			fvector() : x(0.f), y(0.f), z(0.f) {}
			fvector(float x, float y, float z) : x(x), y(y), z(z) {}
			//fvector(const frotator& rotator) : x(rotator.pitch), y(rotator.yaw), z(rotator.roll) {}

			fvector operator + (const fvector& other) const { return { this->x + other.x, this->y + other.y, this->z + other.z }; }
			fvector operator - (const fvector& other) const { return { this->x - other.x, this->y - other.y, this->z - other.z }; }
			fvector operator * (float scalar) const { return { this->x * scalar, this->y * scalar, this->z * scalar }; }
			fvector operator / (float divide) const { return { this->x / divide, this->y / divide, this->z / divide }; }

			fvector& operator *= (const float other) { this->x *= other; this->y *= other; this->z *= other; return *this; }
			fvector& operator /= (const float other) { this->x /= other; this->y /= other; this->z /= other; return *this; }

			fvector& operator =  (const fvector& other) { this->x = other.x; this->y = other.y; this->z = other.z; return *this; }
			fvector& operator += (const fvector& other) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
			fvector& operator -= (const fvector& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
			fvector& operator *= (const fvector& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
			fvector& operator /= (const fvector& other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }

			friend bool operator==(const fvector& first, const fvector& second)
			{
				return first.x == second.x && first.y == second.y && first.z == second.z;
			}

			friend bool operator!=(const fvector& first, const fvector& second)
			{
				return !(first == second);
			}

			float Dot(fvector v)
			{
				return x * v.x + y * v.y + z * v.z;
			}

			void clamp() {
				if (x < 0.f)
					x += 360.f;

				if (x > 360.f)
					x -= 360.f;

				if (y < 0.f) y += 360.f;
				if (y > 360.f) y -= 360.f;
				z = 0.f;
			}

			void normalize()
			{
				if (x > 89.f) x -= 360.f;
				else if (x < -89.f) x += 360.f;

				// in.y = fmodf(in.y, 360.0f);
				while (y > 180) y -= 360;
				while (y < -180) y += 360;
				z = 0;
			}


			float distance(fvector v)
			{
				return float(crt::custom_sqrtf(crt::c_powf(v.x - x, 2.0) + crt::c_powf(v.y - y, 2.0) + crt::c_powf(v.z - z, 2.0)));
			}


			float Length()
			{
				return crt::custom_sqrtf((x * x) + (y * y) + (z * z));
			}
		public:
			float x = 0.f;
			float y = 0.f;
			float z = 0.f;
		};

		class flinearcolor {
		public:
			flinearcolor() : red(0.f), green(0.f), blue(0.f), alpha(0.f) {}
			flinearcolor(float red, float green, float blue, float alpha) : red(red), green(green), blue(blue), alpha(alpha) {}

		public:
			float red;
			float green;
			float blue;
			float alpha;
		};

		class fplane : public fvector {
		public:
			fplane() : w(0.f) {}

		public:
			float w;
		};

		class fmatrix {
		public:
			fmatrix() : x(fplane()), y(fplane()), z(fplane()), w(fplane()) {}
		public:
			fplane x;
			fplane y;
			fplane z;
			fplane w;
		};

		struct fquat
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct ftransform
		{
			fquat rot;
			fvector translation;
			char pad[4];
			fvector scale;
			char pad1[4];

			fmatrix2 ToMatrixWithScale()
			{
				fmatrix2 m;
				m._41 = translation.x;
				m._42 = translation.y;
				m._43 = translation.z;

				float x2 = rot.x + rot.x;
				float y2 = rot.y + rot.y;
				float z2 = rot.z + rot.z;

				float xx2 = rot.x * x2;
				float yy2 = rot.y * y2;
				float zz2 = rot.z * z2;
				m._11 = (1.0f - (yy2 + zz2)) * scale.x;
				m._22 = (1.0f - (xx2 + zz2)) * scale.y;
				m._33 = (1.0f - (xx2 + yy2)) * scale.z;

				float yz2 = rot.y * z2;
				float wx2 = rot.w * x2;
				m._32 = (yz2 - wx2) * scale.z;
				m._23 = (yz2 + wx2) * scale.y;

				float xy2 = rot.x * y2;
				float wz2 = rot.w * z2;
				m._21 = (xy2 - wz2) * scale.y;
				m._12 = (xy2 + wz2) * scale.x;

				float xz2 = rot.x * z2;
				float wy2 = rot.w * y2;
				m._31 = (xz2 + wy2) * scale.z;
				m._13 = (xz2 - wy2) * scale.x;

				m._14 = 0.0f;
				m._24 = 0.0f;
				m._34 = 0.0f;
				m._44 = 1.0f;

				return m;
			}
		};

		fmatrix2 MatrixMultiplication(fmatrix2 pM1, fmatrix2 pM2)
		{
			fmatrix2 pOut;
			pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
			pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
			pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
			pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
			pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
			pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
			pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
			pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
			pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
			pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
			pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
			pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
			pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
			pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
			pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
			pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

			return pOut;
		}

		class uclass
		{
		public:
			hack_byte _padding_0[0x48];
			uclass* super_class = memory::read<uclass*>(uintptr_t(this) + 0x48);
		};

		class uobject {
		public:
			void** vtable;
			hack_int32_t flags;
			hack_int32_t index;
			uclass* class_private;
			fname name;
			uobject* outer;

			void process_event(uobject* function, void* args, void* out_args = nullptr, void* stack = nullptr) {

				auto f_process_event = reinterpret_cast<void (*)(uobject*, uobject*, void*, void*, void*)>(cached::base_address + offsets::process_event); if (!f_process_event) return;
				return reinterpret_cast<void(*)(uobject*, uobject*, void*, void*, void*, hack_uint64_t, void*)>(spoofcall_stub)(this, function, args, out_args, stack, 0x18952362, f_process_event);
			
				//return f_process_event(this, function, args, out_args, stack);
			}

			template<typename type = uobject> static inline type* find_object(const wchar_t* name, uobject* outer = nullptr, bool exact = true) {
				return reinterpret_cast<type*>(uobject::static_find_bject(nullptr, outer, name, exact));
			}


			

			static inline void* static_find_bject(uclass* klass, uobject* outer, const wchar_t* name, bool exact) {


				auto fStaticLoadObject = reinterpret_cast<void* (*)(uclass*, uobject*, const wchar_t*, bool)>(cached::base_address + offsets::static_find_object); if (!fStaticLoadObject) return 0;
				return reinterpret_cast<void* (__cdecl*)(uclass*, uobject*, const wchar_t*, bool, uintptr_t, void*)>(spoofcall_stub)(klass, outer, name, exact, 0x18952362, fStaticLoadObject);
				//auto f_static_load_object = reinterpret_cast<void* (*)(uclass*, uobject*, const wchar_t*, bool)>(cached::base_address + offsets::static_find_object); if (!f_static_load_object) return 0;

			}




			static inline void* static_load_object(uclass* klass,
				uobject* in_outer,
				const wchar_t* name,
				const wchar_t* file_name,
				hack_uint32_t load_flags,
				uintptr_t sandbox,
				bool bAllowObjectReconciliation, 
				uintptr_t inserializecontext) {


				auto fStaticLoadObject = reinterpret_cast<void* (*)(uclass*, uobject*, const wchar_t*, const wchar_t* , hack_uint32_t, uintptr_t, bool, uintptr_t)>(cached::base_address + offsets::static_load_object); if (!fStaticLoadObject) return 0;
				return reinterpret_cast<void* (__cdecl*)(uclass*, uobject*, const wchar_t*, const wchar_t*, hack_uint32_t, uintptr_t, bool, uintptr_t, uintptr_t, void*)>(spoofcall_stub)(
					klass, in_outer, name, file_name, load_flags, sandbox, bAllowObjectReconciliation, inserializecontext, 0x18952362, fStaticLoadObject);
				
			}


			bool is_a(hack_pvoid parent_class)
			{

				for (auto super = memory::read<uclass*>(uintptr_t(this) + 0x10); super; super = memory::read<uclass*>(uintptr_t(super) + 0x48))
				{
					if (super == parent_class)
					{
						return 1;
					}
				}

				return 0;
			}
		};

		void free_memory(void* buffer) {

			//return reinterpret_cast<void(*)(void*, void* , unsigned int)>((uintptr_t)cached::base_address + offsets::memory_free)(buffer,0,0);
		}


		//void memory_free(void* memory_addy) {
		//	auto free_memory = reinterpret_cast<void (*)(void*)>(cached::base_address + offsets::memory_free); if (!free_memory) return;
		//	//return reinterpret_cast<void(*)(uobject*, uobject*, void*, void*, void*, uint64_t, void*)>(spoofcall_stub)(this, function, args, out_args, stack, 0x18952362, f_process_event);
		//
		//	free_memory(memory_addy);
		//}


	}
}

using namespace sdk;
using namespace unreal;






