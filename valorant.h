#pragma once

namespace camera_cached {
	fvector  camera_location;
	fvector  camera_rotation;
	float	 camera_fov_angle;
}

namespace valorant {

	namespace classes
	{
		static inline uobject* gameplay_statics = nullptr;
		static inline uobject* shooter_blueprint_library = nullptr;
		static inline uobject* team_component = nullptr;

		static inline uobject* system = nullptr;
		static inline uobject* render_system = nullptr;
		static inline uobject* string = nullptr;
		static inline uobject* text = nullptr;
		static inline uobject* input = nullptr;
		static inline uobject* math = nullptr;
		static inline uobject* blueprint = nullptr;
		static inline uobject* ares_instance = nullptr;
		static inline uobject* outline_rendering = nullptr;
		static inline uobject* content_library = nullptr;
		static inline uobject* cheat_manager = nullptr;
		static inline uobject* ares_class = nullptr;
		static inline uobject* ares_outline_rendering = nullptr;
		static inline uobject* shooter_pregame_controller = nullptr;

		static inline uobject* planted_bomb = nullptr;
		static inline uobject* shooter_equipable = nullptr;
		static inline uobject* shooter_character = nullptr;

		static inline uclass* font_class = nullptr;

		static inline fkey Insert;

		uobject* font;
		uobject* medium_font;
		uobject* big_font;

		namespace keys {

			//MOUSE
			fkey XButton1;
			fkey XButton2;
			fkey LeftMouseButton;
			fkey RightMouseButton;
			fkey MiddleMouseButton;

			fkey F1;
			fkey F2;
			fkey F3;
			fkey F4;
			fkey F5;
			fkey F6;
			fkey F7;
			fkey F8;
			fkey F9;
			fkey F10;
			fkey F11;
			fkey F12;

			fkey Q;
			fkey W;
			fkey E;
			fkey R;
			fkey T;
			fkey Y;
			fkey U;
			fkey I;
			fkey O;
			fkey P;
			fkey A;
			fkey S;
			fkey D;
			fkey F;
			fkey G;
			fkey H;
			fkey J;
			fkey K;
			fkey L;
			fkey Z;
			fkey X;
			fkey C;
			fkey V;
			fkey B;
			fkey N;
			fkey M;

			fkey LeftShift;
			fkey RightShift;
			fkey LeftControl;
			fkey RightControl;
			fkey LeftAlt;
			fkey RightAlt;

			fkey TabKey;

			fkey array_of_keys[51];

		}

		void initialize();

		
	};

	const wchar_t* ValorantAgents_GameNames[] =
	{
	L"Rift",
	L"Breach",
	L"Sarge",
	L"Deadeye",
	L"Gumshoe",
	L"BountyHunter",
	L"Wushu",
	L"Grenadier",
	L"Killjoy",
	L"Sprinter",
	L"Wraith",
	L"Phoenix",
	L"Clay",
	L"Vampire",
	L"Thorne",
	L"Guide",
	L"Hunter_NPE",
	L"Pandemic",
	L"Stealth"
	L"AggroBot"
	L"Mage"
	};

	typedef struct _D3DMATRIX {
		union {
			struct {
				float        _11, _12, _13, _14;
				float        _21, _22, _23, _24;
				float        _31, _32, _33, _34;
				float        _41, _42, _43, _44;

			};
			float m[4][4];
		};
	} D3DXMATRIX;

	D3DXMATRIX ToMatrix(fvector Rotation, fvector origin)
	{
		float Pitch = (Rotation.x * float(3.1415926535) / 180.f);
		float Yaw = (Rotation.y * float(3.1415926535) / 180.f);
		float Roll = (Rotation.z * float(3.1415926535) / 180.f);

		float SP = crt::custom_sinf(Pitch);
		float CP = crt::custom_cosf(Pitch);
		float SY = crt::custom_sinf(Yaw);
		float CY = crt::custom_cosf(Yaw);
		float SR = crt::custom_sinf(Roll);
		float CR = crt::custom_cosf(Roll);

		D3DXMATRIX Matrix;
		Matrix._11 = CP * CY;
		Matrix._12 = CP * SY;
		Matrix._13 = SP;
		Matrix._14 = 0.f;

		Matrix._21 = SR * SP * CY - CR * SY;
		Matrix._22 = SR * SP * SY + CR * CY;
		Matrix._23 = -SR * CP;
		Matrix._24 = 0.f;

		Matrix._31 = -(CR * SP * CY + SR * SY);
		Matrix._32 = CY * SR - CR * SP * SY;
		Matrix._33 = CR * CP;
		Matrix._34 = 0.f;

		Matrix._41 = origin.x;
		Matrix._42 = origin.y;
		Matrix._43 = origin.z;
		Matrix._44 = 1.f;

		return Matrix;
	}

	class string {
	public:
		enum search_case : hack_uint8_t {
			case_sensitive, ignore_case
		};

		static inline fstring int_to_string(const hack_int32_t value) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.KismetStringLibrary.Conv_IntToString"));

			if (function == nullptr)
				return {};

			struct
			{
				hack_int32_t value;
				fstring return_value;
			} params;

			params.value = value;

			classes::string->process_event(function, &params);

			return params.return_value;
		}

		static inline fstring float_to_string(const float value) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.KismetStringLibrary.Conv_FloatToString"));

			if (function == nullptr)
				return {};

			struct
			{
				float value;
				fstring return_value;
			} params;

			params.value = value;

			classes::string->process_event(function, &params);

			return params.return_value;
		}

		static inline fstring int_to_string(const int value) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.KismetStringLibrary.Conv_IntToString"));

			if (function == nullptr)
				return {};

			struct
			{
				int value;
				fstring return_value;
			} params;

			params.value = value;

			classes::string->process_event(function, &params);

			return params.return_value;
		}


		static inline fname string_to_name(const wchar_t* string) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.KismetStringLibrary.Conv_StringToName"));

			if (function == nullptr) return {};


			struct
			{
				fstring string;
				fname return_value;
			} params;

			params.string = string;

			classes::string->process_event(function, &params);

			return params.return_value;
		}

		static inline fstring name_to_string(const fname& name) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.KismetStringLibrary.Conv_NameToString"));

			if (function == nullptr)
				return {};

			struct
			{
				fname name;
				fstring return_value;
			} params;

			params.name = name;

			classes::string->process_event(function, &params);

			return params.return_value;
		}

		static inline ftext string_to_text(const wchar_t* string) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.KismetTextLibrary.Conv_StringToText"));

			if (function == nullptr)
				return {};

			struct
			{
				fstring string;
				ftext return_value;
			} params;

			params.string = string;

			classes::text->process_event(function, &params);

			return params.return_value;
		}

		static inline fstring text_to_string(ftext string) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.KismetTextLibrary.Conv_TextToString"));

			if (function == nullptr)
				return {};

			struct
			{
				ftext string;
				fstring return_value;
			} params;

			params.string = string;

			classes::text->process_event(function, &params);

			return params.return_value;
		}

		static inline bool starts_with(const wchar_t* source, const wchar_t* prefix, const enum_as_byte<search_case>& search_case = string::ignore_case) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.KismetStringLibrary.StartsWith"));

			if (function == nullptr)
				return false;

			struct
			{
				fstring source;
				fstring prefix;
				hack_uint8_t search_case;
				bool return_value;
			} params;

			params.source = source;
			params.prefix = prefix;
			params.search_case = search_case.get();

			classes::string->process_event(function, &params);

			return params.return_value;
		}

		static inline bool contains(fstring search_in, const wchar_t* sub_string, bool use_case = false, bool search_from_end = false) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.KismetStringLibrary.Contains"));

			if (function == nullptr)
				return false;

			struct
			{
				fstring search_in;
				fstring sub_string;
				bool use_case;
				bool search_from_end;
				bool return_value;
			} params;

			params.search_in = search_in;
			params.sub_string = sub_string;
			params.use_case = use_case;
			params.search_from_end = search_from_end;

			classes::string->process_event(function, &params);

			return params.return_value;
		}

		static inline fstring buildstring_int(fstring append_to, fstring prefix, int value, fstring suffix) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.KismetStringLibrary.BuildString_Int"));

			if (function == nullptr)
				return fstring(L"NONE");

			struct
			{
				fstring append_to;
				fstring prefix;
				int value;
				fstring suffix;
				fstring return_value;
			} params;

			params.append_to = append_to;
			params.prefix = prefix;
			params.value = value;
			params.suffix = suffix;

			classes::string->process_event(function, &params);

			return params.return_value;
		}
	};

	class actor;
	class system {
	public:
		static inline fstring get_object_name_v2(uobject* object) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.KismetSystemLibrary.GetObjectName"));

			if (function == nullptr || object == nullptr)
				return {};

			struct
			{
				uobject* object;
				fstring return_value;
			} params;

			params.object = object;
			//WCHAR result[256];
			classes::system->process_event(function, &params);
			//crt::custom_wcscpy_s(result, sizeof(result), params.return_value.c_str());
			//FreeMemory((PVOID)params.return_value.get_data());
			return params.return_value;
		}

		static inline fstring get_object_class_name(uobject* object) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.KismetSystemLibrary.GetClassDisplayName"));

			if (function == nullptr || object == nullptr)
				return {};

			struct
			{
				uobject* object;
				fstring return_value;
			} params;

			params.object = object;
			//WCHAR result[256];
			classes::system->process_event(function, &params);
			//crt::custom_wcscpy_s(result, sizeof(result), params.return_value.c_str());
			//FreeMemory((PVOID)params.return_value.get_data());
			return params.return_value;
		}


		static inline WString get_object_name(uobject* object) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.KismetSystemLibrary.GetObjectName"));

			if (function == nullptr || object == nullptr)
				return {};

			struct
			{
				uobject* object;
				fstring return_value;
			} params;

			params.object = object;
			WCHAR result[256];
			classes::system->process_event(function, &params);
			crt::custom_wcscpy_s(result, sizeof(result), params.return_value.c_str());
			free_memory((PVOID)params.return_value.get_data());
			return result;
		}

		
		static inline uobject* get_outer_object(uobject* object) {
			//static uobject* function = 0; if (!function) function = uobject::load_object(_(L"Engine.KismetSystemLibrary.GetOuterObject"));
			//
			//if (function == nullptr)
			//	return nullptr;
			//
			//struct
			//{
			//	uobject* object;
			//	uobject* return_value;
			//} params;
			//
			//params.object = object;
			//
			//classes::system->process_event(function, &params);
			//
			//return params.return_value;
			return memory::read<uobject*>(uintptr_t(object) + 0x28);
		}


		//	bool LineTraceSingle(struct UObject* WorldContextObject, struct FVector Start, struct FVector End, enum class ETraceTypeQuery TraceChannel, bool bTraceComplex, struct TArray<struct AActor*>& ActorsToIgnore, enum class EDrawDebugTrace DrawDebugType, struct FHitResult& OutHit, bool bIgnoreSelf, struct FLinearColor TraceColor, struct FLinearColor TraceHitColor, float DrawTime); // Function Engine.KismetSystemLibrary.LineTraceSingle
		enum class ETraceTypeQuery : hack_uint8_t {
			TraceTypeQuery1 = 0,
			TraceTypeQuery2 = 1,
			TraceTypeQuery3 = 2,
			TraceTypeQuery4 = 3,
			TraceTypeQuery5 = 4,
			TraceTypeQuery6 = 5,
			TraceTypeQuery7 = 6,
			TraceTypeQuery8 = 7,
			TraceTypeQuery9 = 8,
			TraceTypeQuery10 = 9,
			TraceTypeQuery11 = 10,
			TraceTypeQuery12 = 11,
			TraceTypeQuery13 = 12,
			TraceTypeQuery14 = 13,
			TraceTypeQuery15 = 14,
			TraceTypeQuery16 = 15,
			TraceTypeQuery17 = 16,
			TraceTypeQuery18 = 17,
			TraceTypeQuery19 = 18,
			TraceTypeQuery20 = 19,
			TraceTypeQuery21 = 20,
			TraceTypeQuery22 = 21,
			TraceTypeQuery23 = 22,
			TraceTypeQuery24 = 23,
			TraceTypeQuery25 = 24,
			TraceTypeQuery26 = 25,
			TraceTypeQuery27 = 26,
			TraceTypeQuery28 = 27,
			TraceTypeQuery29 = 28,
			TraceTypeQuery30 = 29,
			TraceTypeQuery31 = 30,
			TraceTypeQuery32 = 31,
			TraceTypeQuery_MAX = 32,
			ETraceTypeQuery_MAX = 33
		};
		enum class EDrawDebugTrace : hack_uint8_t {
			None = 0,
			ForOneFrame = 1,
			ForDuration = 2,
			Persistent = 3,
			EDrawDebugTrace_MAX = 4
		};


		static inline bool line_trace_single(uobject* uworld, fvector start, fvector end) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.KismetSystemLibrary.LineTraceSingle"));

			if (function == nullptr)
				return false;

			struct
			{
				uobject* WorldContextObject;
				fvector Start;
				fvector End;
				enum class ETraceTypeQuery TraceChannel;
				bool bTraceComplex;
				tarray<actor*>* ActorsToIgnore;
				EDrawDebugTrace DrawDebugType;
				char out_hitpad[0x90];
				bool bIgnoreSelf;
				flinearcolor TraceColor;
				flinearcolor TraceHitColor;
				float DrawTime;
				bool return_value;
			} params;

			params.WorldContextObject = uworld;
			params.Start = start;
			params.End = end;
			params.TraceChannel = ETraceTypeQuery::TraceTypeQuery1;
			params.bTraceComplex = false;
			params.ActorsToIgnore = {};
			params.DrawDebugType = EDrawDebugTrace::None;
			params.bIgnoreSelf = false;
			params.TraceColor = flinearcolor(0,0,0,0);
			params.TraceHitColor = flinearcolor(0,0,0,0);
			params.DrawTime = 0;

			classes::system->process_event(function, &params);

			return params.return_value;
		}
	};

	enum class EBlendMode : hack_uint8_t {
		BLEND_Opaque = 0,
		BLEND_Masked = 1,
		BLEND_Translucent = 2,
		BLEND_Additive = 3,
		BLEND_Modulate = 4,
		BLEND_AlphaComposite = 5,
		BLEND_AlphaHoldout = 6,
		BLEND_MAX = 7
	};

	class canvas : public uobject {
	public:


		int getSizeX()
		{
			return memory::read<int>((uintptr_t)this + 0x48);
		}

		int getSizeY()
		{
			return memory::read<int>((uintptr_t)this + 0x4c);
		}

		void draw_box(const fvector2d& position, const fvector2d& size, float thickness, const flinearcolor& color) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.Canvas.K2_DrawBox"));

			if (function == nullptr)
			{
				return;
			}

			struct
			{
				fvector2d position;
				fvector2d size;
				float thickness;
				flinearcolor color;
			} params;

			params.position = position;
			params.size = size;
			params.thickness = thickness;
			params.color = color;

			this->process_event(function, &params);
		}

		void filled_rect(int x, int y, int sizex, int sizey, flinearcolor c) noexcept
		{
			flinearcolor col;
			col.red = ((float)c.red) / 255.f;
			col.green = ((float)c.green) / 255.f;
			col.blue = ((float)c.blue) / 255.f;
			col.alpha = ((float)c.alpha) / 255.f;

			for (float i = 0.0f; i < sizey; i += 1.0f)
				this->draw_line(fvector2d(x, y + i), fvector2d(x + sizex, y + i), 1.f, col);
		}

		void draw_text(uobject* font, const fstring& text, const fvector2d& position, const fvector2d& scale, const flinearcolor& color, float kerning, const flinearcolor& shadow_color, const fvector2d& shadow_offset, bool centre_x, bool centre_y, bool outlined, const flinearcolor& outline_color) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.Canvas.K2_DrawText"));

			if (function == nullptr)
			{
				return;
			}

			struct
			{
				uobject* font;
				fstring text;
				fvector2d position;
				fvector2d scale;
				flinearcolor color;
				float kerning;
				flinearcolor shadow_color;
				fvector2d shadow_offset;
				bool centre_x;
				bool centre_y;
				bool outlined;
				flinearcolor outline_color;
			} params;

			params.font = font;
			params.text = text;
			params.position = position;
			params.scale = scale;
			params.color = color;
			params.kerning = kerning;
			params.shadow_color = shadow_color;
			params.shadow_offset = shadow_offset;
			params.centre_x = centre_x;
			params.centre_y = centre_y;
			params.outlined = outlined;
			params.outline_color = outline_color;

			this->process_event(function, &params);
		}

		void draw_line(const fvector2d ScreenPositionA, const fvector2d ScreenPositionB, float Thickness, const flinearcolor& renderColor) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.Canvas.K2_DrawLine"));

			if (function == nullptr)
			{
				return;
			}

			struct
			{
				fvector2d screenposa;
				fvector2d screenposb;
				float thickness;
				flinearcolor render;
			} params;

			params.screenposa = ScreenPositionA;
			params.screenposb = ScreenPositionB;
			params.thickness = Thickness;
			params.render = renderColor;

			this->process_event(function, &params);
		}

		void draw_line_v2(const fvector2d ScreenPositionA, const fvector2d ScreenPositionB, float Thickness, const flinearcolor& renderColor) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.Canvas.K2_DrawTransparentLine"));

			if (function == nullptr)
			{
				return;
			}

			struct
			{
				fvector2d screenposa;
				fvector2d screenposb;
				float thickness;
				flinearcolor render;
			} params;

			params.screenposa = ScreenPositionA;
			params.screenposb = ScreenPositionB;
			params.thickness = Thickness;
			params.render = renderColor;

			this->process_event(function, &params);
		}


		void draw_line(double x, double y, double x1, double x2, const flinearcolor& renderColor, int thicknees ) {
			this->draw_line(fvector2d(x,y), fvector2d(x1,x2), thicknees, renderColor);
		}

		void draw_circle(int x, int y, int radius, int numsides, flinearcolor color)
		{
			float step = 3.14159265358979323846264338327950288419716939937510 * 2.0 / numsides;
			int count = 0;

			fvector2d v[128];

			for (float a = 0; a < 3.14159265358979323846264338327950288419716939937510 * 2.0; a += step)
			{
				float x1 = radius * crt::custom_cosf(a) + x;
				float y1 = radius * crt::custom_sinf(a) + y;
				float x2 = radius * crt::custom_cosf(a + step) + x;
				float y2 = radius * crt::custom_sinf(a + step) + y;

				v[count].x = x1;
				v[count].y = y1;
				v[count + 1].x = x2;
				v[count + 1].y = y2;

				this->draw_line(fvector2d({ v[count].x, v[count].y }), fvector2d({ x2, y2 }), 1.0f, color);
			}
		}



		fvector2d strlen(uobject* font, const fstring text)
		{
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.Canvas.K2_StrLen"));

			if (function == nullptr)
				return {};

			struct {
				uobject* font;
				fstring text;
				fvector2d return_value;
			} params;

			params.font = font;
			params.text = text;

			this->process_event(function, &params);

			return params.return_value;
		}

		void draw_cornered_box(int x, int y, int w, int h, const flinearcolor& color, int thickness) {
			float line_w = (w / 4);
			float line_h = (h / 6.2);
			draw_line(fvector2d(x, y), fvector2d(x, y + line_h), thickness, color);
			draw_line(fvector2d(x, y), fvector2d(x + line_w, y), thickness, color);
			draw_line(fvector2d(x + w - line_w, y), fvector2d(x + w, y), thickness, color);
			draw_line(fvector2d(x + w, y), fvector2d(x + w, y + line_h), thickness, color);
			draw_line(fvector2d(x, y + h - line_h), fvector2d(x, y + h), thickness, color);
			draw_line(fvector2d(x, y + h), fvector2d(x + line_w, y + h), thickness, color);
			draw_line(fvector2d(x + w - line_w, y + h), fvector2d(x + w, y + h), thickness, color);
			draw_line(fvector2d(x + w, y + h - line_h), fvector2d(x + w, y + h), thickness, color);
		}


		void draw_health_bar(float X, float Y, float Width, float Height, int health, int healthMax, flinearcolor Color) {

			if (healthMax == 0)
				return;

			for (int i = 0; i < Height; i++) {
				this->draw_line(fvector2d(X - 1, Y + i), fvector2d(X + Width + 1, Y + i), 1, flinearcolor(0, 0, 0, 1)); // Draw background
				if (i > 0 && i < Height - 1) {
					this->draw_line(fvector2d(X, Y + i), fvector2d(X + (Width * health / healthMax), Y + i), 1, Color); // Draw foreground
				}
			}
		}

		void draw_health_bar_horizontal(float X, float Y, float Width, float Height, int health, int healthMax, flinearcolor Color) {

			if (healthMax == 0)
				return;

			for (int i = 0; i < Width; i++) {
				this->draw_line(fvector2d(X - 1, Y), fvector2d(X + i + 1, Y + Height), 1, flinearcolor(0, 0, 0, 1)); // Draw background

				this->draw_line(fvector2d(X, Y), fvector2d(X + Width, Y + (Height * health / healthMax)), 1, Color); // Draw foreground
			}

		}

		void text_wrapper(fvector2d position, flinearcolor c, bool center, fstring text) noexcept
		{
			flinearcolor col;
			col.red = ((float)c.red) / 255.f;
			col.green = ((float)c.green) / 255.f;
			col.blue = ((float)c.blue) / 255.f;
			col.alpha = ((float)c.alpha) / 255.f;



			this->draw_text(classes::font, text, position, fvector2d(1.1f, 1.1f), col, 0.f, flinearcolor(), position, center, center, false, flinearcolor(0.f, 0.f, 0.f, 1.f));
		}


		void text_wrapper_ooo(fvector2d position, flinearcolor c, bool center, fstring text) noexcept
		{



			this->draw_text(classes::font, text, position, fvector2d(1.1f, 1.1f), c, 0.f, flinearcolor(), position, center, center, false, flinearcolor(0.f, 0.f, 0.f, 1.f));
		}

		void text_wrapper(fvector2d position, flinearcolor c, bool center, fstring text, uobject* font) noexcept
		{
			flinearcolor col;
			col.red = ((float)c.red) / 255.f;
			col.green = ((float)c.green) / 255.f;
			col.blue = ((float)c.blue) / 255.f;
			col.alpha = ((float)c.alpha) / 255.f;



			this->draw_text(font, text, position, fvector2d(1.1f, 1.1f), col, 0.f, flinearcolor(), position, center, center, false, flinearcolor(0.f, 0.f, 0.f, 1.f));
		}


		void text_wrapper(fvector2d position, flinearcolor c, bool centerx, bool centery, fstring text) noexcept
		{
			flinearcolor col;
			col.red = ((float)c.red) / 255.f;
			col.green = ((float)c.green) / 255.f;
			col.blue = ((float)c.blue) / 255.f;
			col.alpha = ((float)c.alpha) / 255.f;



			this->draw_text(classes::font, text, position, fvector2d(1.1f, 1.1f), col, 0.f, flinearcolor(), position, centerx, centery, false, flinearcolor(0.f, 0.f, 0.f, 1.f));
		}


		void Line(fvector2d origin, fvector2d dest, flinearcolor col)
		{
			this->draw_line(origin,dest, 1, col);
		}
		
	


		void draw_texture(uintptr_t RenderTexture,
			fvector2d ScreenPosition,
			fvector2d ScreenSize,
			fvector2d CoordinatePosition,
			fvector2d CoordinateSize,
			flinearcolor RenderColor,
			EBlendMode BlendMode,
			float Rotation,
			fvector2d PivotPoint) 
		{
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.Canvas.K2_DrawTexture"));

			if (function == nullptr)
			{
				return;
			}

			struct
			{
				uintptr_t RenderTexture;
				fvector2d ScreenPosition;
				fvector2d ScreenSize;
				fvector2d CoordinatePosition;
				fvector2d CoordinateSize;
				flinearcolor RenderColor;
				EBlendMode BlendMode;
				float Rotation;
				fvector2d PivotPoint;
			} params;

			params.RenderTexture = RenderTexture;
			params.ScreenPosition = ScreenPosition;
			params.ScreenSize = ScreenSize;
			params.CoordinatePosition = CoordinatePosition;
			params.CoordinateSize = CoordinateSize;
			params.RenderColor = RenderColor;
			params.BlendMode = BlendMode;
			params.Rotation = Rotation;
			params.PivotPoint = PivotPoint;

			this->process_event(function, &params);
		}


	};



	class engine {
	public:
		uobject* get_tiny_font() noexcept {
			return memory::read<uobject*>(uintptr_t(this + 0x38));
		}

		uobject* get_small_font() noexcept {
			return memory::read<uobject*>(uintptr_t(this + 0x60));
		}

		uobject* get_medium_font() noexcept {
			return memory::read<uobject*>(uintptr_t(this + 0x88));
		}

		uobject* get_large_font() noexcept {
			return memory::read<uobject*>(uintptr_t(this + 0xB0));
		}

		uobject* get_subtitle_font() noexcept {
			return memory::read<uobject*>(uintptr_t(this + 0xD8));
		}
	};

	class game_viewport_client {
	public:
		uobject* get_world() noexcept {
			return memory::read<uobject*>(uintptr_t(this + 0x80));
		}

		uobject* get_game_instance() noexcept {
			return memory::read<uobject*>(uintptr_t(this + 0x88));
		}

		engine* get_engine() noexcept {
			return reinterpret_cast<engine*>(system::get_outer_object(this->get_game_instance()));
		}
	};

	class actor;

	class pregame_view_controller : public uobject {
	public:

		void lock_character(uobject* agent)
		{
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.PregameViewController.LockCharacter"));

			if (function == nullptr)
				return;

			struct
			{
				uobject* agent;
			} params = { agent };

			this->process_event(function, &params);
		}

		void select_character(uobject* agent)
		{
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.PregameViewController.SelectCharacter"));

			if (function == nullptr)
				return;

			struct
			{
				uobject* agent;
			} params = { agent };

			this->process_event(function, &params);
		}
	};

	class controller : public uobject {
	public:

		pregame_view_controller* get_pregame_view_controller() {
			return memory::read<pregame_view_controller*>(uintptr_t(this) + 0x9d0);
		}
		

		bool is_input_key_down(fkey key) {
			if (!this) return false;
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.PlayerController.IsInputKeyDown"));

			if (function == nullptr)
				return false;

			struct
			{
				fkey key;
				bool return_value;
			} params;

			params.key = key;

			this->process_event(function, &params);

			return params.return_value;
		}

		bool was_input_key_just_pressed(fkey key) {
			if (!this) return false;

			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.PlayerController.WasInputKeyJustPressed"));

			if (function == nullptr)
				return false;

			struct
			{
				fkey key;
				bool return_value;
			} params;

			params.key = key;

			this->process_event(function, &params);

			return params.return_value;
		}

		uintptr_t get_camera_manager()
		{

			return memory::read<uintptr_t>(uintptr_t(this) + offsets::player_camera);
		}

		actor* get_pawn() {
			return reinterpret_cast<actor*>(memory::read<uintptr_t>(uintptr_t(this) + offsets::acknowledged_pawn));
		}

		fvector2d cool_w2s(fvector in)
		{
			auto out = world_to_screen(in, camera_cached::camera_location, camera_cached::camera_rotation, camera_cached::camera_fov_angle);
			return out;
		}

		fvector2d world_to_screen(fvector world_location, fvector position, fvector rotation, float fov)
		{
			fvector2d screen_location = fvector2d(0, 0);

			D3DXMATRIX tempMatrix = ToMatrix(rotation, fvector(0, 0, 0));

			fvector vAxisX, vAxisY, vAxisZ;

			vAxisX = fvector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
			vAxisY = fvector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
			vAxisZ = fvector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

			fvector vDelta = world_location - position;
			fvector vTransformed = fvector(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

			if (vTransformed.z < 1.f)
				vTransformed.z = 1.f;

			float FovAngle = fov;
			float ScreenCenterX = cached::screen_width / 2.0f;
			float ScreenCenterY = cached::screen_height / 2.0f;

			screen_location.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / crt::custom_tanf(FovAngle * (float)3.1415926535 / 360.f)) / vTransformed.z;
			screen_location.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / crt::custom_tanf(FovAngle * (float)3.1415926535 / 360.f)) / vTransformed.z;

			return screen_location;
		}

		fvector get_control_rotation() {

			return memory::read<fvector>((uintptr_t)this + 0x448);
		}
		void set_control_rotation(fvector rotation) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.Controller.SetControlRotation"));

			if (function == nullptr)
				return;

			struct
			{
				fvector value;
			} params;

			params.value = rotation;

			this->process_event(function, &params);

		}

	

		fvector2d get_mouse_position()
		{

			static uobject* function = 0; if (!function) { auto getmouseposition = _(L"Engine.PlayerController.GetMousePosition"); function = uobject::find_object(getmouseposition); getmouseposition.clear(); }
			if (function == nullptr)
				return {};

			struct player_controller_get_mouse_position_params
			{
				float location_x; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
				float location_y; // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
				bool return_value; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
			};
			player_controller_get_mouse_position_params params{};


			this->process_event(function, &params);

			return fvector2d(params.location_x, params.location_y);
		}


		float get_game_time_since_creation()
		{

			static uobject* function = 0; 
			if (!function) { auto game_time = _(L"Engine.Actor.GetGameTimeSinceCreation"); function = uobject::find_object(game_time); game_time.clear(); }
			if (function == nullptr)
				return 0;

			struct player_controller_get_mouse_position_params
			{
				float return_value; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
			};
			player_controller_get_mouse_position_params params{};


			this->process_event(function, &params);

			return params.return_value;
		}

		void start_fire(char fire_mode_enum)
		{

			static uobject* function = 0; if (!function) { auto getmouseposition = _(L"Engine.PlayerController.StartFire"); function = uobject::find_object(getmouseposition); getmouseposition.clear(); }
			if (function == nullptr)
				return;

			struct player_controller_start_fire
			{
				char fire_mode_enum;
			};
			player_controller_start_fire params{};
			params.fire_mode_enum = fire_mode_enum;

			this->process_event(function, &params);
		}
		
		
	};
	class camera : public uobject {
	public:
		fvector get_location() {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.PlayerCameraManager.GetCameraLocation"));

			if (function == nullptr)
				return {};

			struct
			{
				fvector return_value;
			} params;

			this->process_event(function, &params);

			return params.return_value;
		}

		fvector get_rotation() {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.PlayerCameraManager.GetCameraRotation"));

			if (function == nullptr)
				return {};

			struct
			{
				fvector return_value;
			} params;

			this->process_event(function, &params);

			return params.return_value;
		}
		float get_fov() {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.PlayerCameraManager.GetFOVAngle"));

			if (function == nullptr)
				return {};

			struct
			{
				float return_value;
			} params;

			this->process_event(function, &params);

			return params.return_value;
		}
	};

	class stability_component : public uobject {
	public:
		float get_yaw_recoil() {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.StabilityComponent.GetYawRecoil"));

			if (function == nullptr)
				return {};

			struct
			{
				float return_value;
			} params;

			this->process_event(function, &params);

			return params.return_value;
		}

		float get_pitch_recoil() {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.StabilityComponent.GetPitchRecoil"));

			if (function == nullptr)
				return {};

			struct
			{
				float return_value;
			} params;

			this->process_event(function, &params);

			return params.return_value;
		}
	};

	class equippable_skin_data_asset;
	class equippable_skin_chroma_inventory_model;

	class equippable_skin_inventory_model : public uobject {
	public:
		equippable_skin_data_asset* get_equipped_skin_data_asset()
		{
			return memory::read<equippable_skin_data_asset*>(uintptr_t(this) + 0x108);
		}

		equippable_skin_chroma_inventory_model* get_skin_inventory_chroma_asset()
		{
			return memory::read<equippable_skin_chroma_inventory_model*>(uintptr_t(this) + 0x158);
		}
	};

	class equippable_inventory_model : public uobject {
	public:


		equippable_skin_inventory_model* get_equipped_skin_model()
		{
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.EquippableInventoryModel.GetEquippedSkin"));

			if (function == nullptr)
				return nullptr;

			struct {
				equippable_skin_inventory_model* return_value;
			} params;


			this->process_event(function, &params);

			return params.return_value;
		}

		struct equippable_charm_instance_inventory_model* get_equipped_charm_instance() {
			return memory::read<equippable_charm_instance_inventory_model*>(uintptr_t(this) + 0x178);
		}
	};
	class equippable_skin_chroma_inventory_model : public uobject {
	public:
		uobject* get_skin_chroma_data_asset()
		{
			return memory::read<uobject*>(uintptr_t(this) + 0x108);
		}
	};
	class equippable_skin_data_asset : public uobject {
	public:
		struct type {
			const wchar_t* search = nullptr;
			const char* config = nullptr;

			hack_int32_t index = 0;

			const bool is_valid() const noexcept {
				return this->search != nullptr || this->config != nullptr;
			}
		};

		static inline equippable_skin_data_asset::type types[] = {
			{ L"basepistol", "classic" },
			{ L"sawedoffshotgun", "shorty" },
			{ L"autopistol", "frenzy" },
			{ L"luger", "ghost" },
			{ L"revolver", "sheriff" },

			{ L"vector", "stinger" },
			{ L"mp5", "spectre" },

			{ L"pumpshotgun", "bucky" },
			{ L"automaticshotgun", "judge" },

			{ L"burst", "bulldog" },
			{ L"dmr", "guardian" },
			{ L"assaultrifle_acr", "phantom" },
			{ L"ak", "vandal" },

			{ L"leversniperrifle", "marshal" },
			{ L"boltsniper", "operator" },

			{ L"lmg", "ares" },
			{ L"heavymachinegun", "odin" },

			{ L"melee", "knife" },

			{ L"carbine", "phantom", 11 },
			{ L"automaticpistol", "frenzy", 2 },
			{ L"subMachinegun_mp5", "spectre", 6 },
			{ L"Slim", "shorty", 1 },
			{ L"hmg", "odin", 16 },
			{ L"lightmachinegun", "odin", 15 },
			{ L"assaultrifle_ak", "vandal", 12 },
			{ L"AssaultRifle_Burst", "bulldog", 9 },
			{ L"AutoShotgun", "judge", 8 },
			{ L"LeverSniper", "marshal", 13 },
			{ L"DS_Gun", "outlaw", 28 },
		};

		equippable_skin_data_asset::type get_type() {
			WString wname = system::get_object_name(this);

			
			for (hack_int32_t index = 0; index < sizeof(equippable_skin_data_asset::types) / sizeof(equippable_skin_data_asset::type); index++) {
				equippable_skin_data_asset::type type = equippable_skin_data_asset::types[index];

				if (type.index == 0) type.index = index;
				if (string::contains(wname.c_str(), type.search)) return { type.search, type.config, type.index };
			}

			return {};
		}

		struct tarray<int> get_skin_levels() {
			return memory::read<tarray<int>>(uintptr_t(this) + 0x88);
		}
	};


	class arsenal_view_model : public uobject {
	public:
		tarray<equippable_inventory_model*> get_gun_models() {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.ArsenalViewModel.GetGunModels"));

			if (function == nullptr)
				return tarray<equippable_inventory_model*>();

			struct {
				tarray<equippable_inventory_model*> return_value;
			} params;

			this->process_event(function, &params);

			return params.return_value;
		}
	};

	class arsenal_view_controller : public uobject {
	public:
		arsenal_view_model* get_view_model() {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.ArsenalViewController.GetViewModel"));

			if (function == nullptr)
				return nullptr;

			struct {
				arsenal_view_model* return_value;
			} params;


			this->process_event(function, &params);

			return params.return_value;
		}
	};



	struct equippable : public uobject {
		struct type {
			const wchar_t* search = nullptr;
			const char* config = nullptr;

			hack_int32_t index = 0;

			const bool is_valid() const noexcept {
				return this->search != nullptr || this->config != nullptr;
			}
		};

		//stability_component* get_stability_component()
		//{
		//	return memory::read<stability_component*>(uintptr_t(this) + 0x1030);
		//}

		uintptr_t get_firing_state_component()
		{
			return memory::read<uintptr_t>(uintptr_t(this) + 0x1080);
		}

		static inline equippable::type types[] = {
			{ L"basepistol", "classic" },
			{ L"sawedoffshotgun", "shorty" },
			{ L"automaticpistol", "frenzy" },
			{ L"lugerpistol", "ghost" },
			{ L"revolverpistol", "sheriff" },

			{ L"vector", "stinger" },
			{ L"submachinegun_mp5", "spectre" },

			{ L"pumpshotgun", "bucky" },
			{ L"automaticshotgun", "judge" },

			{ L"assaultrifle_burst", "bulldog" },
			{ L"dmr", "guardian" },
			{ L"assaultrifle_acr", "phantom" },
			{ L"assaultrifle_ak", "vandal" },

			{ L"leversniperrifle", "marshal" },
			{ L"boltsniper", "operator" },

			{ L"lightmachinegun", "ares" },
			{ L"heavymachinegun", "odin" },

			{ L"ability_melee_base", "knife" },

			{ L"gun_sprinter_x_heavylightninggun_production", "neon_x" },
			{ L"ability_wushu_x_dagger_production", "jett_dagger" },
			{ L"DS_Gun", "outlaw", 28 }
		};

		equippable::type get_type() {
			WString wname = system::get_object_name(this);

			for (hack_int32_t index = 0; index < sizeof(equippable::types) / sizeof(equippable::type); index++) {
				equippable::type type = equippable::types[index];

				if (type.index == 0)
					type.index = index;

				if (string::starts_with(wname.c_str(), type.search))
					return { type.search, type.config, type.index };
			}

			return {};
		}

		struct equippable_skin_data_asset* get_equippable_skin_data_asset() {
			return memory::read<equippable_skin_data_asset*>(uintptr_t(this) + 0xDD8);
		}

		struct firing_state_component* firing_state() {
			return memory::read<firing_state_component*>(uintptr_t(this) + 0x1040);
		}

	

		uobject* mesh_3p() {
			//ShooterGame.AresEquippable.GetMesh3P
			static uobject* fn = nullptr;
			if (!fn)
				fn = uobject::find_object(_(L"ShooterGame.AresEquippable.GetMesh3P"));

			struct {
				uobject* ret;
			} params = { 0 };

			this->process_event(fn, &params);

			return params.ret;
		}
		
		ftext get_item_name() {
			static uobject* fn = nullptr;
			if (!fn)
				fn = uobject::find_object(_(L"ShooterGame.AresItem.GetItemNameText"));

			struct {
				ftext ret;
			} params = { 0 };

			this->process_event(fn, &params);

			return params.ret;
		}

		uobject* mesh() {
			static uobject* fn = nullptr;
			if (!fn)
				fn = uobject::find_object(_(L"ShooterGame.AresEquippable.GetEquippableMesh"));

			struct {
				uobject* ret;
			} params = { 0 };

			this->process_event(fn, &params);

			return params.ret;
		}

		uobject* icon_() {
			static uobject* fn = nullptr;
			if (!fn)
				fn = uobject::find_object(_(L"ShooterGame.AresItem.GetItemIcon"));

			struct {
				uobject* ret;
			} params = { 0 };

			this->process_event(fn, &params);

			return params.ret;
		}

		

		void clear_weapon_components() {
			static uobject* fn = nullptr;
			if (!fn)
				fn = uobject::find_object(_(L"ShooterGame.ContentLibrary.ClearWeaponComponents"));

			struct {
				uobject* parent;
			} params = { this };

			classes::content_library->process_event(fn, &params);
		}

		void apply_skin(uobject* skin_asset, uobject* chroma_asset, int skin_level, uobject* charm_asset, int charm_level) {
			static uobject* fn = nullptr;
			if (!fn)
				fn = uobject::find_object(_(L"ShooterGame.ContentLibrary.ApplySkin"));

			struct {
				uobject* parent;
				uobject* skin_asset;
				uobject* chroma_asset;
				int skin_level;
				uobject* charm_asset;
				int charm_level;
			} params = { this, skin_asset, chroma_asset, skin_level, charm_asset, charm_level };

			classes::content_library->process_event(fn, &params);
		}
	};



	class inventory : public uobject {
	public:
		equippable* get_current_equippable() {
			return (equippable*)memory::read<uintptr_t>(uintptr_t(this) + offsets::current_equippable);
		}
	};



	enum class EAresOutlineMode : hack_uint8_t {
		None = 0,
		Outline = 1,
		Block = 2,
		Enemy = 3,
		AlwaysOutline = 4,
		AlwaysEnemy = 5,
		EAresOutlineMode_MAX = 6
	};

	class mesh : public uobject {
	public:

		fvector get_bone_location(int bone_id)
		{
			if(!this) return fvector(0, 0, 0);

			auto bone_array = memory::read<uintptr_t>(uintptr_t(this) + offsets::bone_array);
			if (!bone_array) bone_array = memory::read<uintptr_t>(uintptr_t(this) + offsets::bone_array + 0x10);
			

			if (bone_array)
			{
				auto c2w = memory::read<ftransform>(uintptr_t(this) + offsets::component_to_world);

				auto Bone = memory::read<ftransform>(bone_array + (bone_id * 0x30));

				auto Matrix = MatrixMultiplication(Bone.ToMatrixWithScale(), c2w.ToMatrixWithScale());

				return fvector(Matrix._41, Matrix._42, Matrix._43);
			}
			else {
				return fvector(0, 0, 0);
			}
		}

		fvector get_bone_location_v2(int bone_id, uintptr_t bone_array, ftransform c2w)
		{
			if (!this) return fvector(0, 0, 0);

			
			if (bone_array)
			{
				
				auto Bone = memory::read<ftransform>(bone_array + (bone_id * 0x30));

				auto Matrix = MatrixMultiplication(Bone.ToMatrixWithScale(), c2w.ToMatrixWithScale());

				return fvector(Matrix._41, Matrix._42, Matrix._43);
			}
			else {
				return fvector(0, 0, 0);
			}
		}

		void set_world_rotation(fvector NewRotation, bool bsweep, bool bteleport)
		{

			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.SceneComponent.K2_SetWorldRotation"));

			if (function == nullptr)
				return;

			struct {
				fvector NewRotation;
				bool bsweep;
				uintptr_t FHitResult;
				bool bTeleport;
			} params = { NewRotation, bsweep, 0, bteleport };

			this->process_event(function, &params);
		}



		
	};
	class player_state : public uobject {
	public:
		fstring get_player_name() {

			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.PlayerState.GetPlayerName"));

			if (function == nullptr)
				return nullptr;

			struct {
				fstring return_var;
			} params;

			this->process_event(function, &params);

			return params.return_var;
		}

		uintptr_t get_team_component() {

			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.AresPlayerStateBase.GetTeamComponent"));

			if (function == nullptr)
				return 0;

			struct {
				uintptr_t return_var;
			} params;

			this->process_event(function, &params);

			return params.return_var;
		}

		uintptr_t get_ui_data() {

			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.ShooterPlayerState.GetDesiredClassUIData"));

			if (function == nullptr)
				return 0;

			struct {
				uintptr_t return_var;
			} params;

			this->process_event(function, &params);

			return params.return_var;
		}

		actor* spawned_character() {
			return reinterpret_cast<actor*>(memory::read<uintptr_t>(uintptr_t(this) + 0x918)); //SpawnedCharacter
		}

		tarray<player_state*> get_players_spectating() {

			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.ShooterPlayerState.GetPlayersSpectating"));

			if (function == nullptr)
				return {};

			struct {
				tarray<player_state*> return_var;
			} params;

			this->process_event(function, &params);

			return params.return_var;
		}
	};
	class udamageablecomponent : public uobject {

	};
	class actor : public uobject {
	public:
		void disable_input(controller* value)
		{
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.Actor.DisableInput"));

			if (function == nullptr)
				return;

			struct
			{
				controller* controller;

			} params;

			params.controller = value;

			this->process_event(function, &params);
		}

		void enable_input(controller* value)
		{
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.Actor.EnableInput"));

			if (function == nullptr)
				return;

			struct
			{
				controller* controller;

			} params;

			params.controller = value;

			this->process_event(function, &params);
		}

		player_state* get_player_state() {
			return (player_state*)memory::read<uintptr_t>(uintptr_t(this) + offsets::player_state);

		}

		uintptr_t unique_id() {

			return memory::read<uintptr_t>(uintptr_t(this) + 0x38);
		}


		udamageablecomponent* get_damageablecomponent() {
			return (udamageablecomponent*)memory::read<uintptr_t>(uintptr_t(this) + offsets::damage_handler);
		}

		float get_max_shield() {
			return memory::read<float>(uintptr_t(this) + offsets::max_shield);
		}

		float get_health() {
			auto damage_handler = memory::read<uintptr_t>(uintptr_t(this) + offsets::damage_handler); if (!damage_handler) return 0;
			return memory::read<float>(damage_handler + offsets::current_health);
			/*
			static uobject* function = 0; if (!function) function = uobject::load_object(_(L"ShooterGame.ShooterCharacter.GetHealth"));

			if (function == nullptr)
				return {};

			struct
			{
				float return_value;
			} params;

			this->process_event(function, &params);

			return params.return_value;*/
		}

		float get_shield() {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.ShooterCharacter.GetShield"));

			if (function == nullptr)
				return {};

			struct
			{
				float return_value;
			} params;

			this->process_event(function, &params);

			return params.return_value;

		}

		mesh* get_mesh() {
			return (mesh*)memory::read<uintptr_t>(uintptr_t(this) + offsets::current_mesh);
		}

	
		void set_3p_mesh_visible(bool state) {

			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.ShooterCharacter.Set3PMeshVisible"));

			if (function == nullptr)
				return;

			struct
			{
				bool b_set_3p_visible;
			} params;

			params.b_set_3p_visible = state;

			this->process_event(function, &params);
		}

		inventory* get_inventory() {
			return (inventory*)memory::read<uintptr_t>(uintptr_t(this) + offsets::inventory);
		}

		void get_actor_bounds(bool only_colliding_components, bool include_from_child_actors, fvector* origin, fvector* box_extent) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.Actor.GetActorBounds"));

			if (function == nullptr)
				return;

			struct
			{
				bool only_colliding_components;
				bool include_from_child_actors;
				fvector origin;
				fvector box_extent;
			} params;

			params.only_colliding_components = only_colliding_components;
			params.include_from_child_actors = include_from_child_actors;

			this->process_event(function, &params);

			if (origin)
				*origin = params.origin;

			if (box_extent)
				*box_extent = params.box_extent;
		}

		void get_firing_location_and_direction(fvector* Location, fvector* Rotation, bool bApplyRecoil = false) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.ShooterCharacter.GetFiringLocationAndDirection"));

			if (function == nullptr)
				return;

			struct
			{
				fvector location;
				fvector rotation;
				bool bapplyrecoil;
			} params;

			params.bapplyrecoil = bApplyRecoil;

			this->process_event(function, &params);

			*Location = params.location;
			*Rotation = params.rotation;
		}


		enum class ECollisionChannel
		{
			ECC_WorldStatic = 0,
			ECC_WorldDynamic = 1,
			ECC_Pawn = 2,
			ECC_Visibility = 3,
			ECC_Camera = 4,
			ECC_PhysicsBody = 5,
			ECC_Vehicle = 6,
			ECC_Destructible = 7,
			ECC_EngineTraceChannel1 = 8,
			ECC_EngineTraceChannel2 = 9,
			ECC_EngineTraceChannel3 = 10,
			ECC_EngineTraceChannel4 = 11,
			ECC_EngineTraceChannel5 = 12,
			ECC_EngineTraceChannel6 = 13,
			ECC_GameTraceChannel1 = 14,
			ECC_GameTraceChannel2 = 15,
			ECC_GameTraceChannel3 = 16,
			ECC_GameTraceChannel4 = 17,
			ECC_GameTraceChannel5 = 18,
			ECC_GameTraceChannel6 = 19,
			ECC_GameTraceChannel7 = 20,
			ECC_GameTraceChannel8 = 21,
			ECC_GameTraceChannel9 = 22,
			ECC_GameTraceChannel10 = 23,
			ECC_GameTraceChannel11 = 24,
			ECC_GameTraceChannel12 = 25,
			ECC_GameTraceChannel13 = 26,
			ECC_GameTraceChannel14 = 27,
			ECC_GameTraceChannel15 = 28,
			ECC_GameTraceChannel16 = 29,
			ECC_GameTraceChannel17 = 30,
			ECC_GameTraceChannel18 = 31,
			ECC_OverlapAll_Deprecated = 32,
			ECC_MAX = 33,
		};

		actor* simple_trace_from_camera(float dist) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.ShooterCharacter.SimpleTraceFromCamera"));

			if (function == nullptr)
				return {};


			struct
			{
				float Distance;
				ECollisionChannel Channel;
				fvector HitPoint;
				bool bBlockingHit;
				actor* return_value;
			} params;

			params.Distance = dist;
			params.Channel = ECollisionChannel::ECC_GameTraceChannel1;
			fvector sadfsdfsfda = fvector(0, 0, 0);
			params.HitPoint = sadfsdfsfda;
			params.bBlockingHit = false;

			this->process_event(function, &params);

			return params.return_value;

		}
		
		float get_game_time_since_creation()
		{

			static uobject* function = 0;
			if (!function) { auto game_time = _(L"Engine.Actor.GetGameTimeSinceCreation"); function = uobject::find_object(game_time); game_time.clear(); }
			if (function == nullptr)
				return 0;

			struct player_controller_get_mouse_position_params
			{
				float return_value; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
			};
			player_controller_get_mouse_position_params params{};


			this->process_event(function, &params);

			return params.return_value;
		}
	};

	class inventory_manager : public uobject {
	public:

		inventory_manager* get_equippable_skin_model(uobject* data)
		{
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.InventoryManager.GetEquippableSkinModel"));

			if (function == nullptr)
				return nullptr;

			struct {
				uobject* data;
				inventory_manager* return_value;
			} params;

			params.data = data;
			this->process_event(function, &params);

			return params.return_value;
		}

	};

	class ares_client_game_instace : public uobject {
	public:

		inventory_manager* get_inventory_manager()
		{
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.AresClientGameInstance.GetInventoryManager"));

			if (function == nullptr)
				return nullptr;

			struct {
				inventory_manager* return_value;
			} params;


			this->process_event(function, &params);

			return params.return_value;
		}


		arsenal_view_controller* get_aresnal_view_controller()
		{
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.AresClientGameInstance.GetArsenalViewController"));

			if (function == nullptr)
				return nullptr;

			struct {
				arsenal_view_controller* return_value;
			} params;


			this->process_event(function, &params);

			return params.return_value;
		}


		void disconnect_from_server()
		{
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.AresClientGameInstance.DisconnectFromServer"));

			if (function == nullptr)
			{
				return;
			}

			this->process_event(function, nullptr);
		}


	};

	class ares_instance {
	public:
		static inline class ares_client_game_instace* get_ares_client_game_instance(uobject* world_context)
		{
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.AresClientGameInstance.GetAresClientGameInstance"));

			if (function == nullptr)
			{
				return {};
			}

			struct {
				uobject* uworld;
				ares_client_game_instace* return_value;
			} params;

			params.uworld = world_context;

			classes::ares_instance->process_event(function, &params);

			return params.return_value;
		}
	};


	class content_library {
	public:
		static void apply_skin(uobject* parent, uobject* skin_asset, uobject* chroma_asset, int skin_level, uobject* charm_asset, int charm_level) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.ContentLibrary.ApplySkin"));

			if (function == nullptr) return;

			struct
			{
				uobject* parent;
				uobject* skin_asset;
				uobject* chroma_asset;
				int skin_level;
				uobject* charm_asset;
				int charm_level;
			} params;

			params.parent = parent;
			params.skin_asset = skin_asset;
			params.chroma_asset = chroma_asset;
			params.skin_level = skin_level;
			params.charm_asset = charm_asset;
			params.charm_level = charm_level;

			classes::content_library->process_event(function, &params);
		}

		static void clear_weapon_components(uobject* parent) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.ContentLibrary.ClearWeaponComponents"));

			if (function == nullptr)
				return;

			struct
			{
				uobject* parent;
			} params;

			params.parent = parent;

			classes::content_library->process_event(function, &params);
		}

		static int get_highest_unlocked_level_for_equippable_skin(uobject* uworld, uobject* skin_data) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.ContentLibrary.GetHighestUnlockedLevelForEquippableSkin"));

			if (function == nullptr)
				return 1;

			struct
			{
				uobject* uworld;
				uobject* skin_data;
				int level;
			} params;

			params.uworld = uworld;
			params.skin_data = skin_data;

			classes::content_library->process_event(function, &params);

			return params.level;
		}
	};

	class math {
	public:



		static inline bool class_is_child_of(uobject* test_class, uobject* parent_class)
		{
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Engine.KismetMathLibrary.ClassIsChildOf"));
			if (function == nullptr)
				return false;

			struct
			{
				uobject* test_class;
				uobject* parent_class;
				bool return_value;
			} params;

			params.test_class = test_class;
			params.parent_class = parent_class;

			classes::math->process_event(function, &params);

			return params.return_value;
		}

		static float sdk_atan(float  a)
		{
			struct u_kismet_math_library_sin_params
			{
				float a; // (Parm, ZeroConstructor, IsPlainOldData)
				float return_value; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
			};

			u_kismet_math_library_sin_params params{};
			params.a = a;


			static uobject* function = 0; if (!function) { auto asin = _(L"Engine.KismetMathLibrary.Atan");  function = uobject::find_object(asin); asin.clear(); }

			if (function == nullptr) return 0;

			classes::math->process_event(function, &params);

			return params.return_value;
		}

		static float sdk_acos(float  a)
		{
			struct u_kismet_math_library_sin_params
			{
				float a; // (Parm, ZeroConstructor, IsPlainOldData)
				float return_value; // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
			};

			u_kismet_math_library_sin_params params{};
			params.a = a;


			static uobject* function = 0; if (!function) { auto asin = _(L"Engine.KismetMathLibrary.Acos");  function = uobject::find_object(asin); asin.clear(); }

			if (function == nullptr) return 0;

			classes::math->process_event(function, &params);

			return params.return_value;
		}

		static hack_int32_t random_int(hack_int32_t Min, hack_int32_t Max)
		{
			static uobject* Function = 0;
			if (!Function) Function = uobject::find_object(_(L"KismetMathLibrary.RandomIntegerInRange"));

			struct {
				hack_int32_t Min;
				hack_int32_t Max;
				hack_int32_t ReturnValue;
			} Params = { Min, Max };

			classes::math->process_event(Function, &Params);

			return Params.ReturnValue;
		}
	};

	class blueprint {
	public:
		static inline class controller* get_local_controller(uobject* world_context) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.ShooterBlueprintLibrary.GetLocalController"));

			if (function == nullptr || world_context == nullptr) return {};

			struct {
				uobject* world_context;
				class controller* return_value;
			} params = { world_context };

			classes::blueprint->process_event(function, &params);

			return params.return_value;
		}

		static inline tarray<actor*> find_all_game_objects(uobject* world_context)
		{
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.ShooterBlueprintLibrary.FindAllGameObjects"));

			if (function == nullptr || world_context == nullptr) return {};

			struct {
				uobject* world_context;
				tarray<actor*> return_value;
			} params = { world_context };

			

			classes::blueprint->process_event(function, &params);

			return params.return_value;
		}

		enum class ECollisionChannel : hack_uint8_t {
			ECC_WorldStatic = 0,
			ECC_WorldDynamic = 1,
			ECC_Pawn = 2,
			ECC_Visibility = 3,
			ECC_Camera = 4,
			ECC_PhysicsBody = 5,
			ECC_Vehicle = 6,
			ECC_Destructible = 7,
			ECC_EngineTraceChannel1 = 8,
			ECC_EngineTraceChannel2 = 9,
			ECC_EngineTraceChannel3 = 10,
			ECC_EngineTraceChannel4 = 11,
			ECC_EngineTraceChannel5 = 12,
			ECC_EngineTraceChannel6 = 13,
			ECC_GameTraceChannel1 = 14,
			ECC_GameTraceChannel2 = 15,
			ECC_GameTraceChannel3 = 16,
			ECC_GameTraceChannel4 = 17,
			ECC_GameTraceChannel5 = 18,
			ECC_GameTraceChannel6 = 19,
			ECC_GameTraceChannel7 = 20,
			ECC_GameTraceChannel8 = 21,
			ECC_GameTraceChannel9 = 22,
			ECC_GameTraceChannel10 = 23,
			ECC_GameTraceChannel11 = 24,
			ECC_GameTraceChannel12 = 25,
			ECC_GameTraceChannel13 = 26,
			ECC_GameTraceChannel14 = 27,
			ECC_GameTraceChannel15 = 28,
			ECC_GameTraceChannel16 = 29,
			ECC_GameTraceChannel17 = 30,
			ECC_GameTraceChannel18 = 31,
			ECC_OverlapAll_Deprecated = 32,
			ECC_MAX = 33
		};

		static bool can_player_see_player(actor* actor1, actor* actor2, bool obey_smokes)
		{
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"ShooterGame.ShooterBlueprintLibrary.CanPlayerSeePlayer"));

			if (function == nullptr) return false;
			if (!actor1 || !actor2) return false;

			struct {
				actor* Viewer;
				actor* Viewee;
				ECollisionChannel ChannelType;
				bool bObeySightDebuffs;
				hack_int32_t VisibilityTargets;
				bool return_value;
			} params;

			params.Viewer = actor1;
			params.Viewee = actor2;
			params.ChannelType = ECollisionChannel::ECC_Visibility;
			params.bObeySightDebuffs = obey_smokes;
			params.VisibilityTargets = 5;

			classes::blueprint->process_event(function, &params);

			return params.return_value;
		}
	};

	class outline_rendering : public uobject {
	public:
		static inline void set_outline_colors_for_render(uobject* world_context, const flinearcolor& ally, const flinearcolor& enemy) {
			static uobject* function = 0; if (!function) function = uobject::find_object(_(L"Renderer.AresOutlineRendering.SetOutlineColorsForRender"));

			if (function == nullptr)
				return;

			struct {
				uobject* world_context;
				flinearcolor ally;
				flinearcolor enemy;
			} params;

			params.world_context = world_context;
			params.ally = ally;
			params.enemy = enemy;


			classes::ares_outline_rendering->process_event(function, &params);
		}
	};

	
}

namespace cached {
	uobject* uworld = 0;
	valorant::controller* controller = 0;
	valorant::actor* local_pawn = 0;
	valorant::inventory* local_inventory = 0;
	valorant::equippable* current_equip = 0;
	valorant::mesh* local_mesh = 0;
}

struct FMinimalViewInfo {
	struct fvector Location; // 0x00(0x0c)
	struct fvector Rotation; // 0x0c(0x0c)
	float FOV; // 0x18(0x04)
	float DesiredFOV; // 0x1c(0x04)
	float OrthoWidth; // 0x20(0x04)
	float OrthoNearClipPlane; // 0x24(0x04)
	float OrthoFarClipPlane; // 0x28(0x04)
	float AspectRatio; // 0x2c(0x04)
	char bConstrainAspectRatio : 1; // 0x30(0x01)
	char bUseFieldOfViewForLOD : 1; // 0x30(0x01)
	char pad_30_2 : 6; // 0x30(0x01)
	char pad_31[0x3]; // 0x31(0x03)
	char pad_34[0x01]; // 0x34(0x01)
	char pad_35[0x3]; // 0x35(0x03)
	float PostProcessBlendWeight; // 0x38(0x04)
	char pad_3C[0x4]; // 0x3c(0x04)
	char pad_3c4[0x600];
	struct fvector2d OffCenterProjectionOffset; // 0x640(0x08)
	char pad_648[0x48]; // 0x648(0x48)
};


struct FTViewTarget {
	valorant::actor* Target; // 0x00(0x08)
	char pad_8[0x8]; // 0x08(0x08)
	struct FMinimalViewInfo POV; // 0x10(0x690)
	struct valorant::player_state* PlayerState; // 0x6a0(0x08)
	char pad_6A8[0x8]; // 0x6a8(0x08)
};

void (*o_draw_transition)(valorant::game_viewport_client* game_viewport, valorant::canvas* canvas);
void (*o_update_view_target_internal)(uintptr_t, FTViewTarget*, float);



float target_actor_distance = FLT_MAX;
valorant::actor* target_actor = 0;
valorant::actor* trigger_actor = 0;
int target_hitbox_id_closest = 0;
int target_offset = 0;


fvector2d pos = fvector2d(100, 100);


uintptr_t camera_engine;
uintptr_t weapn_cached;
bool should_hook_gay;


enum MaleBones {
	Skeleton = 0,
	Root = 1,
	Splitter = 2,
	Spine1 = 3,
	Spine2 = 4,
	Spine3 = 5,
	Spine4 = 6,
	Neck = 7,
	Head = 8,
	Mouth_Top = 9,
	L_Brows = 10,
	R_Eyeball = 11,
	Jaw = 12,
	Mouth_Bot = 13,
	L_Eyeball = 14,
	L_EyeLids = 15,
	MouthCorner = 16,
	R_EyeLids = 17,
	R_Brows = 18,
	R_Lower_EyeLid = 19,
	L_Lower_EyeLid = 20,
	Collar = 21,
	L_Clavicle = 22,
	L_Shoulder = 23,
	L_Elbow = 24,
	L_Hand = 25,
	L_WeaponPoint = 26,
	L_Thumb1 = 27,
	L_Thumb2 = 28,
	L_Thumb3 = 29,
	L_Index1 = 30,
	L_Index2 = 31,
	L_Index3 = 32,
	L_Middle1 = 33,
	L_Middle2 = 34,
	L_Middle3 = 35,
	L_Pinky1 = 36,
	L_Pinky2 = 37,
	L_Pinky3 = 38,
	L_Ring1 = 39,
	L_Ring2 = 40,
	L_Ring3 = 41,
	L_Elbow_Ndl = 42,
	L_Elbow_Twst2 = 43,
	L_Elbow_Twst3 = 44,
	L_Shoulder_Twst1 = 45,
	L_Shoulder_Helper = 46,
	L_Shoulder_Twst3 = 47,
	R_Clavicle = 48,
	R_Shoulder = 49,
	R_Elbow = 50,
	R_Hand = 51,
	R_WeaponPoint = 52,
	R_Thumb1 = 53,
	R_Thumb2 = 54,
	R_Thumb3 = 55,
	R_Index1 = 56,
	R_Index2 = 57,
	R_Index3 = 58,
	R_Middle1 = 59,
	R_Middle2 = 60,
	R_Middle3 = 61,
	R_Pinky1 = 62,
	R_Pinky2 = 63,
	R_Pinky3 = 64,
	R_Ring1 = 65,
	R_Ring2 = 66,
	R_Ring3 = 67,
	R_Elbow_Ndl = 68,
	R_Elbow_Twst2 = 69,
	R_Elbow_Twst3 = 70,
	R_Shoulder_Twst1 = 71,
	R_Shoulder_Helper = 72,
	R_Shoulder_Twst3 = 73,
	Pelvis = 74,
	R_Foot_IKpv_IUE = 75,
	L_Foot_IKpv_IUE = 76,
	L_Hip = 77,
	L_Knee = 78,
	L_Knee_Ndl = 79,
	L_Foot = 80,
	L_Toe = 81,
	L_Hip_Twst1 = 82,
	L_Hip_Twst3 = 83,
	R_Hip = 84,
	R_Knee = 85,
	R_Knee_Ndl = 86,
	R_Foot = 87,
	R_Toe = 88,
	R_Hip_Twst1 = 89,
	R_Hip_Twst3 = 90,
	MasterWeaponAim = 91,
	MasterWeapon = 92,
	L_WeaponMaster = 93,
	R_WeaponMaster = 94,
	L_Weapon_HandTarget = 95,
	L_Weapon_HandOffset = 96,
	R_Weapon_HandTarget = 97,
	L_Hand_IKpv_IUE = 98,
	R_Hand_IKpv_IUE = 99,
	IK_RootTarget = 100,
	L_IK_FootTarget = 101,
	R_IK_FootTarget = 102,
	TP_Camera = 103,
};

enum FemaleBones {
	F_Skeleton = 0,
	F_Root = 1,
	F_Splitter = 2,
	F_Spine1 = 3,
	F_Spine2 = 4,
	F_Spine3 = 5,
	F_Spine4 = 6,
	F_Neck = 7,
	F_Head = 8,
	F_Jaw = 9,
	F_Mouth_Bot = 10,
	F_R_Eyeball = 11,
	F_Mouth_Top = 12,
	F_L_Eyeball = 13,
	F_MouthCorner = 14,
	F_L_Brows = 15,
	F_R_Brows = 16,
	F_R_EyeLids = 17,
	F_L_EyeLids = 18,
	F_R_Lower_EyeLid = 19,
	F_L_Lower_EyeLid = 20,
	F_Collar = 21,
	F_L_Clavicle = 22,
	F_L_Shoulder = 23,
	F_L_Elbow = 24,
	F_L_Hand = 25,
	F_L_Pinky1 = 26,
	F_L_Pinky2 = 27,
	F_L_Pinky3 = 28,
	F_L_Thumb1 = 29,
	F_L_Thumb2 = 30,
	F_L_Thumb3 = 31,
	F_L_Index1 = 32,
	F_L_Index2 = 33,
	F_L_Index3 = 34,
	F_L_Ring1 = 35,
	F_L_Ring2 = 36,
	F_L_Ring3 = 37,
	F_L_Middle1 = 38,
	F_L_Middle2 = 39,
	F_L_Middle3 = 40,
	F_L_WeaponPoint = 41,
	F_L_Elbow_Ndl = 42,
	F_L_Elbow_Twst2 = 43,
	F_L_Elbow_Twst3 = 44,
	F_L_Shoulder_Twst1 = 45,
	F_L_Shoulder_Twst3 = 46,
	F_R_Clavicle = 47,
	F_R_Shoulder = 48,
	F_R_Elbow = 49,
	F_R_Hand = 50,
	F_R_WeaponPoint = 51,
	F_R_Index1 = 52,
	F_R_Index2 = 53,
	F_R_Index3 = 54,
	F_R_Thumb1 = 55,
	F_R_Thumb2 = 56,
	F_R_Thumb3 = 57,
	F_R_Ring1 = 58,
	F_R_Ring2 = 59,
	F_R_Ring3 = 60,
	F_R_Pinky1 = 61,
	F_R_Pinky2 = 62,
	F_R_Pinky3 = 63,
	F_R_Middle1 = 64,
	F_R_Middle2 = 65,
	F_R_Middle3 = 66,
	F_R_Elbow_Ndl = 67,
	F_R_Elbow_Twst2 = 68,
	F_R_Elbow_Twst3 = 69,
	F_R_Shoulder_Twst1 = 70,
	F_R_Shoulder_Twst3 = 71,
	F_Pelvis = 72,
	F_R_Foot_IKpv_IUE = 73,
	F_L_Foot_IKpv_IUE = 74,
	F_L_Hip = 75,
	F_L_Knee = 76,
	F_L_Knee_Ndl = 77,
	F_L_Foot = 78,
	F_L_Toe = 79,
	F_L_Hip_Twst1 = 80,
	F_L_Hip_Twst3 = 81,
	F_R_Hip = 82,
	F_R_Knee = 83,
	F_R_Knee_Ndl = 84,
	F_R_Foot = 85,
	F_R_Toe = 86,
	F_R_Hip_Twst1 = 87,
	F_R_Hip_Twst3 = 88,
	F_MasterWeaponAim = 89,
	F_MasterWeapon = 90,
	F_L_WeaponMaster = 91,
	F_R_WeaponMaster = 92,
	F_R_Weapon_HandTarget = 93,
	F_L_Weapon_HandTarget = 94,
	F_L_Weapon_HandOffset = 95,
	F_L_Hand_IKpv_IUE = 96,
	F_R_Hand_IKpv_IUE = 97,
	F_IK_RootTarget = 98,
	F_L_IK_FootTarget = 99,
	F_R_IK_FootTarget = 100,
};


void valorant::classes::initialize() {
	classes::gameplay_statics = uobject::find_object(_(L"Engine.GameplayStatics"));
	classes::team_component = uobject::find_object(_(L"ShooterGame.BaseTeamComponent"));
	classes::system = uobject::find_object(_(L"Engine.KismetSystemLibrary"));
	classes::render_system = uobject::find_object(_(L"Engine.KismetRenderingLibrary"));
	classes::string = uobject::find_object(_(L"Engine.KismetStringLibrary"));
	classes::text = uobject::find_object(_(L"Engine.KismetTextLibrary"));
	classes::input = uobject::find_object(_(L"Engine.KismetInputLibrary"));
	classes::math = uobject::find_object(_(L"Engine.KismetMathLibrary"));
	classes::blueprint = uobject::find_object(_(L"ShooterGame.ShooterBlueprintLibrary"));
	classes::cheat_manager = uobject::find_object(_(L"ShooterGame.MainMenuCheatManager"));
	classes::content_library = uobject::find_object(_(L"ShooterGame.ContentLibrary"));
	classes::ares_instance = uobject::find_object(_(L"ShooterGame.AresClientGameInstance"));
	classes::outline_rendering = uobject::find_object(_(L"Renderer.AresOutlineRendering"));
	classes::ares_class = uobject::find_object(_(L"ShooterGame.AresOutlineComponent"));
	classes::ares_outline_rendering = uobject::find_object(_(L"Renderer.AresOutlineRendering"));
	classes::shooter_pregame_controller = uobject::find_object(_(L"ShooterGame.PregamePlayerController"));
	classes::shooter_character = uobject::find_object(_(L"ShooterGame.ShooterCharacter"));
	classes::planted_bomb = uobject::find_object(_(L"TimedBomb.TimedBomb_C"));
	classes::shooter_equipable = uobject::find_object(_(L"ShooterGame.AresOnGroundEquippable"));

	//classes::font_class = (uclass*)uobject::find_object(_(L"Engine.Font"));



	auto xbutton1name = _(L"ThumbMouseButton"); keys::XButton1 = fkey{ fname { string::string_to_name(xbutton1name.decrypt()) } , 0 }; xbutton1name.clear();
	keys::array_of_keys[0] = keys::XButton1;
	
	auto xbutton2name = _(L"ThumbMouseButton2"); keys::XButton2 = fkey{ fname { string::string_to_name(xbutton2name.decrypt()) } , 0 }; xbutton2name.clear();
	keys::array_of_keys[1] = keys::XButton2;
	
	auto lmb = _(L"LeftMouseButton"); keys::LeftMouseButton = fkey{ fname { string::string_to_name(lmb.decrypt()) } , 0 }; lmb.clear();
	keys::array_of_keys[2] = keys::LeftMouseButton;
	
	auto rmb = _(L"RightMouseButton"); keys::RightMouseButton = fkey{ fname { string::string_to_name(rmb.decrypt()) } , 0 }; rmb.clear();
	keys::array_of_keys[3] = keys::RightMouseButton;
	
	auto mmb = _(L"MiddleMouseButton"); keys::MiddleMouseButton = fkey{ fname { string::string_to_name(mmb.decrypt()) } , 0 }; rmb.clear();
	keys::array_of_keys[4] = keys::MiddleMouseButton;
	
	auto LeftShiftn = _(L"LeftShift"); keys::LeftShift = fkey{ fname { string::string_to_name(LeftShiftn.decrypt()) } , 0 }; LeftShiftn.clear();
	keys::array_of_keys[5] = keys::LeftShift;
	auto RightShiftN = _(L"RightShift"); keys::RightShift = fkey{ fname { string::string_to_name(RightShiftN.decrypt()) } , 0 }; RightShiftN.clear();
	keys::array_of_keys[6] = keys::RightShift;
	auto LeftControlN = _(L"LeftControl"); keys::LeftControl = fkey{ fname { string::string_to_name(LeftControlN.decrypt()) } , 0 }; LeftControlN.clear();
	keys::array_of_keys[7] = keys::LeftControl;
	auto RightControlN = _(L"RightControl"); keys::RightControl = fkey{ fname { string::string_to_name(RightControlN.decrypt()) } , 0 }; RightControlN.clear();
	keys::array_of_keys[8] = keys::RightControl;
	auto LeftAltN = _(L"LeftAlt"); keys::LeftAlt = fkey{ fname { string::string_to_name(LeftAltN.decrypt()) } , 0 }; LeftAltN.clear();
	keys::array_of_keys[9] = keys::LeftAlt;
	auto RightAltN = _(L"RightAlt"); keys::RightAlt = fkey{ fname { string::string_to_name(RightAltN.decrypt()) } , 0 }; RightAltN.clear();
	keys::array_of_keys[10] = keys::RightAlt;
	
	
	
	// Function KEYS
	keys::F1 = fkey{ fname { string::string_to_name(_(L"F1").decrypt())} , 0 }; keys::array_of_keys[11] = keys::F1;
	keys::F2 = fkey{ fname { string::string_to_name(_(L"F2").decrypt())} , 0 }; keys::array_of_keys[12] = keys::F2;
	keys::F3 = fkey{ fname { string::string_to_name(_(L"F3").decrypt())} , 0 }; keys::array_of_keys[13] = keys::F3;
	keys::F4 = fkey{ fname { string::string_to_name(_(L"F4").decrypt())} , 0 }; keys::array_of_keys[14] = keys::F4;
	keys::F5 = fkey{ fname { string::string_to_name(_(L"F5").decrypt())} , 0 }; keys::array_of_keys[15] = keys::F5;
	keys::F6 = fkey{ fname { string::string_to_name(_(L"F6").decrypt())} , 0 }; keys::array_of_keys[16] = keys::F6;
	keys::F7 = fkey{ fname { string::string_to_name(_(L"F7").decrypt())} , 0 }; keys::array_of_keys[17] = keys::F7;
	keys::F8 = fkey{ fname { string::string_to_name(_(L"F8").decrypt())} , 0 }; keys::array_of_keys[18] = keys::F8;
	keys::F9 = fkey{ fname { string::string_to_name(_(L"F9").decrypt())} , 0 }; keys::array_of_keys[19] = keys::F9;
	keys::F10 = fkey{ fname { string::string_to_name(_(L"F10").decrypt())} , 0 }; keys::array_of_keys[20] = keys::F10;
	keys::F11 = fkey{ fname { string::string_to_name(_(L"F11").decrypt())} , 0 }; keys::array_of_keys[21] = keys::F11;
	keys::F12 = fkey{ fname { string::string_to_name(_(L"F12").decrypt())} , 0 }; keys::array_of_keys[22] = keys::F12;
	
	keys::Q = fkey{ fname { string::string_to_name(_(L"Q").decrypt())} , 0 }; keys::array_of_keys[23] = keys::Q;
	keys::W = fkey{ fname { string::string_to_name(_(L"W").decrypt())} , 0 }; keys::array_of_keys[24] = keys::W;
	keys::E = fkey{ fname { string::string_to_name(_(L"E").decrypt())} , 0 };	keys::array_of_keys[25] = keys::E;
	keys::R = fkey{ fname { string::string_to_name(_(L"R").decrypt())} , 0 };	keys::array_of_keys[26] = keys::R;
	keys::T = fkey{ fname { string::string_to_name(_(L"T").decrypt())} , 0 };	keys::array_of_keys[27] = keys::T;
	keys::Y = fkey{ fname { string::string_to_name(_(L"Y").decrypt())} , 0 };	keys::array_of_keys[28] = keys::Y;
	keys::U = fkey{ fname { string::string_to_name(_(L"U").decrypt())} , 0 };	keys::array_of_keys[29] = keys::U;
	keys::I = fkey{ fname { string::string_to_name(_(L"I").decrypt())} , 0 };	keys::array_of_keys[30] = keys::I;
	keys::O = fkey{ fname { string::string_to_name(_(L"O").decrypt())} , 0 };	keys::array_of_keys[31] = keys::O;
	keys::P = fkey{ fname { string::string_to_name(_(L"P").decrypt())} , 0 };	keys::array_of_keys[32] = keys::P;
	keys::A = fkey{ fname { string::string_to_name(_(L"A").decrypt())} , 0 };	keys::array_of_keys[33] = keys::A;
	keys::S = fkey{ fname { string::string_to_name(_(L"S").decrypt())} , 0 };	keys::array_of_keys[34] = keys::S;
	keys::D = fkey{ fname { string::string_to_name(_(L"D").decrypt())} , 0 };	keys::array_of_keys[35] = keys::D;
	keys::F = fkey{ fname { string::string_to_name(_(L"F").decrypt())} , 0 };	keys::array_of_keys[36] = keys::F;
	keys::G = fkey{ fname { string::string_to_name(_(L"G").decrypt())} , 0 };	keys::array_of_keys[37] = keys::G;
	keys::H = fkey{ fname { string::string_to_name(_(L"H").decrypt())} , 0 };	keys::array_of_keys[38] = keys::H;
	keys::J = fkey{ fname { string::string_to_name(_(L"J").decrypt())} , 0 };	keys::array_of_keys[39] = keys::J;
	keys::K = fkey{ fname { string::string_to_name(_(L"K").decrypt())} , 0 };	keys::array_of_keys[40] = keys::K;
	keys::L = fkey{ fname { string::string_to_name(_(L"L").decrypt())} , 0 };	keys::array_of_keys[41] = keys::L;
	keys::Z = fkey{ fname { string::string_to_name(_(L"Z").decrypt())} , 0 };	keys::array_of_keys[42] = keys::Z;
	keys::X = fkey{ fname { string::string_to_name(_(L"X").decrypt())} , 0 };	keys::array_of_keys[43] = keys::X;
	keys::C = fkey{ fname { string::string_to_name(_(L"C").decrypt())} , 0 };	keys::array_of_keys[44] = keys::C;
	keys::V = fkey{ fname { string::string_to_name(_(L"V").decrypt())} , 0 };	keys::array_of_keys[45] = keys::V;
	keys::B = fkey{ fname { string::string_to_name(_(L"B").decrypt())} , 0 };	keys::array_of_keys[46] = keys::B;
	keys::N = fkey{ fname { string::string_to_name(_(L"N").decrypt())} , 0 };	keys::array_of_keys[47] = keys::N;
	keys::M = fkey{ fname { string::string_to_name(_(L"M").decrypt())} , 0 };	keys::array_of_keys[48] = keys::M;
	
	keys::TabKey = fkey{ fname { string::string_to_name(_(L"Tab").decrypt()) } , 0 };
	keys::array_of_keys[49] = keys::TabKey;

	
}