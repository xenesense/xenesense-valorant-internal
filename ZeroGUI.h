#pragma once

wchar_t* s2wc(const char* c)
{
	const size_t cSize = crt::custom_strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	crt::custom_mbstowcs(wc,c, cSize);
	return wc;
}

namespace zero_gui
{
	namespace Colors
	{
		flinearcolor Text{ 1.0f, 1.0f, 1.0f, 1.0f };
		flinearcolor Text_Shadow{ 0.0f, 0.0f, 0.0f, 0.0f };
		flinearcolor Text_Outline{ 0.0f, 0.0f, 0.0f, 0.30f };

		flinearcolor Window_Background{ 0.009f, 0.009f, 0.009f, 1.0f };
		flinearcolor Window_Header{ 0.10f, 0.15f, 0.84f, 1.0f };

		flinearcolor Button_Idle{ 0.10f, 0.15f, 0.84f, 1.0f };
		flinearcolor Button_Hovered{ 0.15f, 0.20f, 0.89f, 1.0f };
		flinearcolor Button_Active{ 0.20f, 0.25f, 0.94f, 1.0f };

		flinearcolor Checkbox_Idle{ 0.17f, 0.16f, 0.23f, 1.0f };
		flinearcolor Checkbox_Hovered{ 0.22f, 0.30f, 0.72f, 1.0f };
		flinearcolor Checkbox_Enabled{ 0.20f, 0.25f, 0.94f, 1.0f };

		flinearcolor Combobox_Idle{ 0.17f, 0.16f, 0.23f, 1.0f };
		flinearcolor Combobox_Hovered{ 0.17f, 0.16f, 0.23f, 1.0f };
		flinearcolor Combobox_Elements{ 0.239f, 0.42f, 0.82f, 1.0f };

		flinearcolor Slider_Idle{ 0.17f, 0.16f, 0.23f, 1.0f };
		flinearcolor Slider_Hovered{ 0.17f, 0.16f, 0.23f, 1.0f };
		flinearcolor Slider_Progress{ 0.22f, 0.30f, 0.72f, 1.0f };
		flinearcolor Slider_Button{ 0.10f, 0.15f, 0.84f, 1.0f };

		flinearcolor ColorPicker_Background{ 0.006f, 0.006f, 0.006f, 1.0f };
	}

	namespace PostRenderer
	{
		struct DrawList
		{
			int type = -1; //1 = FilledRect, 2 = TextLeft, 3 = TextCenter, 4 = Draw_Line
			fvector2d pos;
			fvector2d size;
			flinearcolor color;
			const char* name;
			bool outline;

			fvector2d from;
			fvector2d to;
			int thickness;
		};
		DrawList drawlist[128];

		void drawFilledRect(fvector2d pos, float w, float h, flinearcolor color)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 1;
					drawlist[i].pos = pos;
					drawlist[i].size = fvector2d{ w, h };
					drawlist[i].color = color;
					return;
				}
			}
		}
		void TextLeft(const char* name, fvector2d pos, flinearcolor color, bool outline)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 2;
					drawlist[i].name = name;
					drawlist[i].pos = pos;
					drawlist[i].outline = outline;
					drawlist[i].color = color;
					return;
				}
			}
		}
		void TextCenter(char* name, fvector2d pos, flinearcolor color, bool outline)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 3;
					drawlist[i].name = name;
					drawlist[i].pos = pos;
					drawlist[i].outline = outline;
					drawlist[i].color = color;
					return;
				}
			}
		}
		void Draw_Line(fvector2d from, fvector2d to, int thickness, flinearcolor color)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 4;
					drawlist[i].from = from;
					drawlist[i].to = to;
					drawlist[i].thickness = thickness;
					drawlist[i].color = color;
					return;
				}
			}
		}
	}

	valorant::canvas* canvas;


	bool hover_element = false;
	fvector2d menu_pos = fvector2d{ 0, 0 };
	float offset_x = 0.0f;
	float offset_y = 0.0f;

	fvector2d first_element_pos = fvector2d{ 0, 0 };

	fvector2d last_element_pos = fvector2d{ 0, 0 };
	fvector2d last_element_size = fvector2d{ 0, 0 };

	int current_element = -1;
	fvector2d current_element_pos = fvector2d{ 0, 0 };
	fvector2d current_element_size = fvector2d{ 0, 0 };
	int elements_count = 0;

	bool sameLine = false;

	bool pushY = false;
	float pushYvalue = 0.0f;

	bool is_open;

	int tab = 0;

	void setup_canvas(valorant::canvas * _canvas)
	{
		canvas = _canvas;
	}

	fvector2d get_cursor_pos()
	{
		//POINT cursorPos;
		//o_getcursorpos(&cursorPos);
		//return fvector2d{ (float)cursorPos.x, (float)cursorPos.y };
		return cached::controller->get_mouse_position();
	}
	bool mouse_in_zone(fvector2d pos, fvector2d size)
	{
		fvector2d cursor_pos = get_cursor_pos();

		if (cursor_pos.x > pos.x && cursor_pos.y > pos.y)
			if (cursor_pos.x < pos.x + size.x && cursor_pos.y < pos.y + size.y)
				return true;

		return false;
	}



	void same_line()
	{
		sameLine = true;
	}
	void push_next_element_y(float y, bool from_last_element = true)
	{
		pushY = true;
		if (from_last_element)
			pushYvalue = last_element_pos.y + last_element_size.y + y;
		else
			pushYvalue = y;
	}
	void next_column(float x)
	{
		offset_x = x;
		//PushNextElementY(first_element_pos.y, false);
	}
	void ClearFirstPos()
	{
		first_element_pos = fvector2d{ 0, 0 };
	}

	void TextLeft(const char* name, fvector2d pos, flinearcolor color, bool outline)
	{
		canvas->draw_text(valorant::classes::font, s2wc(name), pos, fvector2d{ 0.97f, 0.97f }, color, false, Colors::Text_Shadow, fvector2d{ pos.x + 1, pos.y + 1 }, false, true, true, Colors::Text_Outline);
	}
	void TextCenter(const char* name, fvector2d pos, flinearcolor color, bool outline)
	{
		canvas->draw_text(valorant::classes::font, s2wc(name), pos, fvector2d{ 0.97f, 0.97f }, color, false, Colors::Text_Shadow, fvector2d{ pos.x + 1, pos.y + 1 }, true, true, true, Colors::Text_Outline);
	}

	void TextCenter2(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline)
	{
		canvas->draw_text(valorant::classes::font, name, pos, fvector2d{ 0.97f, 0.97f }, color, false, Colors::Text_Shadow, fvector2d{ pos.x + 1, pos.y + 1 }, true, true, true, Colors::Text_Outline);
	}

	void TextCenter2(fstring name, fvector2d pos, flinearcolor color, bool outline)
	{
		canvas->draw_text(valorant::classes::font, name, pos, fvector2d{ 0.97f, 0.97f }, color, false, Colors::Text_Shadow, fvector2d{ pos.x + 1, pos.y + 1 }, true, true, true, Colors::Text_Outline);
	}

	void GetColor(flinearcolor* color, float* r, float* g, float* b, float* a)
	{
		*r = color->red;
		*g = color->green;
		*b = color->blue;
		*a = color->alpha;
	}


	void Draw_Line(fvector2d from, fvector2d to, int thickness, flinearcolor color)
	{
		canvas->draw_line(fvector2d{ from.x, from.y }, fvector2d{ to.x, to.y }, thickness, color);
	}
	void draw_filled_rect(fvector2d initial_pos, float w, float h, flinearcolor color)
	{
		for (float i = 0.0f; i < h; i += 1.0f)
			canvas->draw_line_v2(fvector2d{ initial_pos.x, initial_pos.y + i }, fvector2d{ initial_pos.x + w, initial_pos.y + i }, 1.0f, color);
	}
	void draw_filled_circle(fvector2d pos, float r, flinearcolor color)
	{
		float smooth = 0.07f;

		double PI = 3.14159265359;
		int size = (int)(2.0f * PI / smooth) + 1;

		float angle = 0.0f;
		int i = 0;

		for (; angle < 2 * PI; angle += smooth, i++)
		{
			Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ pos.x + crt::custom_cosf(angle) * r, pos.y + crt::custom_sinf(angle) * r }, 1.0f, color);
		}
	}

	//void DrawFilledCircleSegment(fvector2d pos, float radius, float startAngle, float endAngle, flinearcolor color) {
	//	constexpr int numSegments = 30; // Adjust this value for smoother curves
	//
	//	float angleStep = (endAngle - startAngle) / numSegments;
	//	Vector<fvector2d> points;
	//
	//	for (int i = 0; i <= numSegments; ++i) {
	//		float angle = startAngle + angleStep * i;
	//		float x = pos.x + radius * crt::custom_cosf(angle);
	//		float y = pos.y + radius * crt::custom_sinf(angle);
	//		points.push_back({ x, y });
	//	}
	//
	//	// Draw the filled segment using triangles
	//	for (int i = 0; i < numSegments; ++i) {
	//		canvas->draw_line(points[i], points[i + 1],1, color);
	//		canvas->draw_line(pos, points[i],1, color);
	//		canvas->draw_line(pos, points[i + 1], 1,color);
	//	}
	//}


	void DrawCircle(fvector2d pos, int radius, int numSides, flinearcolor Color)
	{
		float PI = 3.1415927f;

		float Step = PI * 2.0 / numSides;
		int Count = 0;
		fvector2d V[128];
		for (float a = 0; a < PI * 2.0; a += Step) {
			float X1 = radius * crt::custom_cosf(a) + pos.x;
			float Y1 = radius * crt::custom_sinf(a) + pos.y;
			float X2 = radius * crt::custom_cosf(a + Step) + pos.x;
			float Y2 = radius * crt::custom_sinf(a + Step) + pos.y;
			V[Count].x = X1;
			V[Count].y = Y1;
			V[Count + 1].x = X2;
			V[Count + 1].y = Y2;
			//Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ X2, Y2 }, 1.0f, Color); // Points from Centre to ends of circle
			Draw_Line(fvector2d{ V[Count].x, V[Count].y }, fvector2d{ X2, Y2 }, 1.0f, Color);// Circle Around
		}
	}


	fvector2d dragPos;
	bool new_window(wchar_t* name, fvector2d* pos, fvector2d size)
	{
		elements_count = 0;

		if (cached::controller->was_input_key_just_pressed(valorant::classes::keys::F8))
		{
			is_open = !is_open;
			if (cached::local_pawn)
			{
				if (is_open)
				{
					cached::local_pawn->disable_input(cached::controller);
				}
				else
				{
					cached::local_pawn->enable_input(cached::controller);
				}
			}
		}

		if (!is_open)
			return false;

		bool isHovered = mouse_in_zone(fvector2d{ pos->x, pos->y }, size);

		bool MouseHold = cached::controller->is_input_key_down(valorant::classes::keys::LeftMouseButton);

		//Drop last element
		if (current_element != -1 && !MouseHold)
		{
			current_element = -1;
		}

		//Drag
		if (hover_element && MouseHold)
		{

		}
		else if ((isHovered || dragPos.x != 0) && !hover_element)
		{
			if (Input::IsMouseClicked(0, elements_count, true))
			{
				fvector2d cursorPos = get_cursor_pos();

				cursorPos.x -= size.x;
				cursorPos.y -= size.y;

				if (dragPos.x == 0)
				{
					dragPos.x = (cursorPos.x - pos->x);
					dragPos.y = (cursorPos.y - pos->y);
				}
				pos->x = cursorPos.x - dragPos.x;
				pos->y = cursorPos.y - dragPos.y;
			}
			else
			{
				dragPos = fvector2d{ 0, 0 };
			}
		}
		else
		{
			hover_element = false;
		}


		offset_x = 0.0f; offset_y = 0.0f;
		menu_pos = fvector2d{ pos->x, pos->y };
		first_element_pos = fvector2d{ 0, 0 };
		current_element_pos = fvector2d{ 0, 0 };
		current_element_size = fvector2d{ 0, 0 };

		//Bg
		 
		//drawRoundedFilledRect(fvector2d{ pos->x, pos->y }, size.x, size.y, 8, flinearcolor(0.02217, 0.0185, 0.01764, 0.07036));
		 
		//DrawRoundedFilledRect_2(fvector2d{ pos->x, pos->y }, size.x, size.y, 5,flinearcolor{ 0.006f, 0.006f, 0.006f, 1.0f });

		// background
		draw_filled_rect(fvector2d{ pos->x, pos->y }, size.x, size.y, flinearcolor{ 0.00368, 0.00304, 0.00273, 0.87137 });

		// tabs
		draw_filled_rect(fvector2d{ pos->x + 24, pos->y + 24 }, 181, 650 - 24 * 2, flinearcolor{ 0.02217, 0.0185, 0.01764, 0.07036 });

		// childs with functions
		draw_filled_rect(fvector2d{ pos->x + (24 * 2) + 181 , pos->y + 24 }, (850 / 2) - ((181 / 2) + (24 + 12)), 650 - 24 * 2, flinearcolor{ 0.02217, 0.0185, 0.01764, 0.07036 });

		draw_filled_rect(fvector2d{ pos->x + (24 * 3) + 181 + (850 / 2) - ((181 / 2) + (24 + 12)), pos->y + 24 }, (850 / 2) - ((181 / 2) + ( 12)), 650 - 24 * 2, flinearcolor{ 0.02217, 0.0185, 0.01764, 0.07036 });
		
		// childs titles

		auto posy = pos->y + 24 + 24;
		auto widtht = (850 / 2) - ((181 / 2) + (24 + 12)) - 48;


		draw_filled_rect(fvector2d{ pos->x + (24 * 2) + 181 + 24 ,posy }, widtht, 37, flinearcolor{ 0.09531, 0.0865, 0.07619, 0.05286 });
		Draw_Line(fvector2d{ pos->x + (24 * 2) + 181 + 24 + (widtht / 2 ) - 24,posy + 28 }, fvector2d{ pos->x + (24 * 2) + 181 + 24 + (widtht / 2 ) + 24,posy + 28 }, 2, flinearcolor(0.27, 0.00, 0.43, 1));
		fvector2d titlePos_child = fvector2d{ pos->x + (24 * 2) + 181 + 24 + (widtht / 2), posy + 12 };

		switch (tab) {
		case 0:
			canvas->text_wrapper(titlePos_child, flinearcolor{ 255,255,255,255 }, true, _(L"Aim").decrypt(), valorant::classes::big_font);
			break;
		case 1:
			canvas->text_wrapper(titlePos_child, flinearcolor{ 255,255,255,255 }, true, _(L"ESP").decrypt(), valorant::classes::big_font);
			break;
		case 2:
			canvas->text_wrapper(titlePos_child, flinearcolor{ 255,255,255,255 }, true, _(L"Misc 1").decrypt(), valorant::classes::big_font);
			break;
		case 3:
			canvas->text_wrapper(titlePos_child, flinearcolor{ 255,255,255,255 }, true, _(L"World ESP").decrypt(), valorant::classes::big_font);
			break;
		}
		

		draw_filled_rect(fvector2d{ pos->x + (24 * 3) + 181 + (850 / 2) - ((181 / 2) + (24 + 12)) + 24, posy }, widtht, 37, flinearcolor{ 0.09531, 0.0865, 0.07619, 0.05286 });
		Draw_Line(fvector2d{ pos->x + (24 * 3) + 181 + (850 / 2) - ((181 / 2) + (24 + 12)) + 24 + (widtht / 2) - 24,posy + 28 }, fvector2d{ pos->x + (24 * 3) + 181 + (850 / 2) - ((181 / 2) + (24 + 12)) + 24 + (widtht / 2) + 24,posy + 28 }, 2, flinearcolor(0.27, 0.00, 0.43, 1));
		
		fvector2d titlePos_child_2 = fvector2d{ pos->x +(24 * 3) + 181 + (850 / 2) - ((181 / 2) + (24 + 12)) + 24 + (widtht / 2), posy + 12 };

		switch (tab) {
		case 0:
			canvas->text_wrapper(titlePos_child_2, flinearcolor{ 255,255,255,255 }, true, _(L"Other").decrypt(), valorant::classes::big_font);
			break;
		case 1:
			canvas->text_wrapper(titlePos_child_2, flinearcolor{ 255,255,255,255 }, true, _(L"Settings").decrypt(), valorant::classes::big_font);
			break;
		case 2:
			canvas->text_wrapper(titlePos_child_2, flinearcolor{ 255,255,255,255 }, true, _(L"Misc 2").decrypt(), valorant::classes::big_font);
			break;
		case 3:
			canvas->text_wrapper(titlePos_child_2, flinearcolor{ 255,255,255,255 }, true, _(L"Settings").decrypt(), valorant::classes::big_font);
			break;
		}



		//canvas->text_wrapper(titlePos_child_2, flinearcolor{ 255,255,255,255 }, true, name, valorant::classes::big_font);


		offset_y += 25.0f;

		//Title
		fvector2d titlePos = fvector2d{ pos->x + 24 + 181 / 2, pos->y + 66};
		//TextCenter(name, titlePos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

		canvas->text_wrapper_ooo(titlePos, flinearcolor{ 0.27, 0.00, 0.43,1 }, true, name);

		return true;
	}

	void text(const wchar_t* text, bool center = false, bool outline = false)
	{
		elements_count++;

		float size = 25;
		fvector2d padding = fvector2d{ 10, 10 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		if (!sameLine)
			offset_y += size + padding.y;

		//Text
		//fvector2d textPos = fvector2d{ pos.x + 5.0f, pos.y + size / 2 };
		//if (center)
		//	TextCenter(text, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);
		//else
		//	TextLeft(text, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, outline);

		sameLine = false;
		last_element_pos = pos;
		//last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}

	void place_dummy(fvector2d dummysize)
	{
		elements_count++;

		float size = 0;
		fvector2d padding = fvector2d{ dummysize.x, dummysize.y };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		if (!sameLine)
			offset_y += size + padding.y;


		sameLine = false;
		last_element_pos = pos;
		//last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}


	bool button_tab(const wchar_t* name, const wchar_t* letter, fvector2d size, bool active)
	{
		elements_count++;

		fvector2d padding = fvector2d{ 10, 8 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = mouse_in_zone(fvector2d{ pos.x, pos.y }, size);

		//accent -> 0.27, 0.00, 0.43

		//Bg
		if (active)
		{
			draw_filled_rect(fvector2d{ pos.x, pos.y }, size.x, size.y, flinearcolor{ 0.09531, 0.0865, 0.07619 , 0.07036 });
			draw_filled_rect(fvector2d{ pos.x + 8, pos.y + 8 }, 28, size.y - 16, flinearcolor{ 0.27, 0.00, 0.43 , 1 });
		}
		else if (isHovered)
		{
			draw_filled_rect(fvector2d{ pos.x, pos.y }, size.x, size.y, flinearcolor{ 0.09531, 0.0865, 0.07619 ,0.02624 });
			draw_filled_rect(fvector2d{ pos.x + 8, pos.y + 8 }, 28, size.y - 16, flinearcolor{ 0.09531, 0.0865, 0.07619 ,0.02624 });
			hover_element = true;
		}
		else
		{
			draw_filled_rect(fvector2d{ pos.x, pos.y }, size.x, size.y, flinearcolor{ 0.09531, 0.0865, 0.07619 ,0.00972 });
			draw_filled_rect(fvector2d{ pos.x + 8, pos.y + 8 }, 28, size.y - 16, flinearcolor{ 0.09531, 0.0865, 0.07619 , 0.00972 });
		}

		if (!sameLine)
			offset_y += size.y + padding.y;

		//Text
		fvector2d textPos = fvector2d{ pos.x + size.x / 2 - 8, pos.y + size.y / 2 };
		canvas->text_wrapper(fvector2d(textPos.x, textPos.y), flinearcolor{ 255,255,255,255 }, false, true, name);

		fvector2d letterPos = fvector2d{ pos.x + 8 + 28 /2 , pos.y + size.y / 2 };
		canvas->text_wrapper(fvector2d(letterPos.x, letterPos.y), flinearcolor{ 255,255,255,255 }, true, true, letter);

		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
			return true;

		return false;
	}
	bool button(wchar_t* name, fvector2d size)
	{
		elements_count++;

		fvector2d padding = fvector2d{ 5, 10 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = mouse_in_zone(fvector2d{ pos.x, pos.y }, size);

		//Bg
		if (isHovered)
		{
			draw_filled_rect(fvector2d{ pos.x, pos.y }, size.x, size.y, flinearcolor{ 0.09531, 0.0865, 0.07619, 0.07036 });
			hover_element = true;
		}
		else
		{
			draw_filled_rect(fvector2d{ pos.x, pos.y }, size.x, size.y, flinearcolor{ 0.09531, 0.0865, 0.07619, 0.02624 });
		}

		if (!sameLine)
			offset_y += size.y + padding.y;

		//Text
		fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
		//if (!TextOverlapedFromActiveElement(textPos))
		//TextCenter(name, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

		canvas->text_wrapper(fvector2d(textPos.x, textPos.y), flinearcolor{ 255,255,255,255 }, true, name);


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
			return true;

		return false;
	}

	bool checkbox_button(wchar_t* name, fvector2d size, bool* out_boolean)
	{
		elements_count++;

		fvector2d padding = fvector2d{ 0, 00 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = mouse_in_zone(fvector2d{ pos.x, pos.y }, size);

		if (*out_boolean) {
			draw_filled_rect(fvector2d{ pos.x, pos.y }, size.x, size.y, flinearcolor{ 0.27, 0.00, 0.43,1 });
		}

		//Bg
		if (isHovered)
		{
			canvas->draw_box(fvector2d{ pos.x, pos.y }, fvector2d{ size.x, size.y }, 2, flinearcolor(1, 1, 1, 1));

			hover_element = true;
		}
		else
		{
			canvas->draw_box(fvector2d{ pos.x, pos.y }, fvector2d{ size.x, size.y }, 2, flinearcolor(1, 1, 1, 1));
		}

		if (!sameLine)
			offset_y += size.y + padding.y;

		//Text
		fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
		//if (!TextOverlapedFromActiveElement(textPos))
		//TextCenter(name, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

		//canvas->text_wrapper(fvector2d(textPos.x, textPos.y), flinearcolor{ 255,255,255,255 }, true, name);



		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false)) {
			*out_boolean = !*out_boolean;
			return true;
		}


		return false;
	}

	void check_box(wchar_t* name, bool* value)
	{
		elements_count++;

		float size = 17;
		fvector2d padding = fvector2d{ 10, 10 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = mouse_in_zone(fvector2d{ pos.x , pos.y }, fvector2d{ size + canvas->strlen(valorant::classes::font,name).x + 5, size });



		//Bg
		if (isHovered)
		{

			draw_filled_rect(fvector2d{ pos.x, pos.y }, size, size, flinearcolor{ 0.09531, 0.0865, 0.07619, 0.07036 });

			hover_element = true;
		}
		else
		{
			draw_filled_rect(fvector2d{ pos.x, pos.y }, size, size, flinearcolor{ 0.09531, 0.0865, 0.07619, 0.02624 });
			
		}

		if (!sameLine)
			offset_y += size + padding.y;

		if (*value)
		{

			draw_filled_rect(fvector2d{ pos.x, pos.y }, size , size , flinearcolor{ 0.27, 0.00, 0.43,255 });

			Draw_Line(fvector2d(pos.x + 5, pos.y + size / 2), fvector2d(pos.x + size / 2, pos.y + size - 5), 1, flinearcolor(1,1,1,1));
			Draw_Line(fvector2d(pos.x + size / 2, pos.y + size - 5), fvector2d(pos.x + size - 4, pos.y + 5), 1, flinearcolor(1,1,1,1));

			//Draw_Line(fvector2d(pos.x + 3, pos.y + size / 2), fvector2d(pos.x + size / 2 - 2, pos.y + size - 5), 2, flinearcolor(1, 1, 1, 1));
			//Draw_Line(fvector2d(pos.x + size / 2 - 3, pos.y + size - 4), fvector2d(pos.x + size - 5, pos.y + 5), 2, flinearcolor(1, 1, 1, 1));
			//drawFilledRect(fvector2d{ pos.x + 9, pos.y + 9 }, size - 18, size - 18, Colors::Checkbox_Hovered);
		}

		flinearcolor text_color = flinearcolor(1,1,1,1);
		if (*value) {
			text_color = flinearcolor(1,1,1,1);
		}
		else if (isHovered) {
			text_color = flinearcolor(1, 1, 1, 0.30499);
		}
		else {
			text_color = flinearcolor(1, 1, 1, 0.12744);
		}

		//Text
		fvector2d textPos = fvector2d{ pos.x + size + 5.0f, pos.y - 3 };
		//if (!TextOverlapedFromActiveElement(textPos))
		//TextLeft(name, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
		canvas->text_wrapper_ooo(fvector2d(textPos.x, textPos.y), text_color, false, name);


		sameLine = false;
		last_element_pos = pos;
		//last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
			*value = !*value;
	}
	void slider_int(wchar_t* name, int* value, int min, int max)
	{
		elements_count++;

		fvector2d size = fvector2d{ 240, 30 };
		fvector2d slider_size = fvector2d{ 170, 8 };
		fvector2d padding = fvector2d{ 10, 10 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = mouse_in_zone(fvector2d{ pos.x, pos.y + slider_size.y + padding.y * 2 }, slider_size);
		bool isClicked = false;

		if (!sameLine)
			offset_y += size.y + padding.y;

		//Bg
		if (isHovered || current_element == elements_count)
		{
			//Drag
			if (Input::IsMouseClicked(0, elements_count, true))
			{
				current_element = elements_count;

				fvector2d cursorPos = get_cursor_pos();
				*value = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
				if (*value < min) *value = min;
				if (*value > max) *value = max;

				isClicked = true;
			}
			else {
				isClicked = false;
			}


			hover_element = true;
		}
		else
		{

		}


		//Text


		//Empty
		float oneP = slider_size.x / (max - min);

		flinearcolor kolorek = flinearcolor{ 0.09531, 0.0865, 0.07619, 0.07036 };
		flinearcolor kolorek2 = flinearcolor{1,1,1,1 };
		if (isHovered) {
			kolorek = flinearcolor{ 0.09531, 0.0865, 0.07619, 0.07036 };
			kolorek2 = flinearcolor{ 1,1,1,1 };
		}
		else {
			kolorek = flinearcolor{ 0.09531, 0.0865, 0.07619, 0.02624 };
			kolorek2 = flinearcolor{ 1,1,1,0.30499 };
		}


		draw_filled_rect(fvector2d(pos.x, pos.y + slider_size.y + padding.y * 2), slider_size.x, slider_size.y, kolorek);

		//Value
		draw_filled_rect(fvector2d(pos.x, pos.y + slider_size.y + padding.y * 2), oneP * (*value - min), slider_size.y, flinearcolor{ 0.27, 0.00, 0.43,255 });

		fvector2d textPos = fvector2d{ pos.x, pos.y + 7 };
		canvas->text_wrapper_ooo(fvector2d(textPos.x, textPos.y), kolorek2, false, name);

		auto value_converted = valorant::string::int_to_string(*value);
		canvas->text_wrapper_ooo(fvector2d(textPos.x + slider_size.x - canvas->strlen(valorant::classes::font, value_converted).x, textPos.y), kolorek2, false, value_converted);


		draw_filled_circle(fvector2d{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 13.6f + padding.y }, 6.0f, flinearcolor(1,1,1,1));


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}
	void slider_float(wchar_t* name, float* value, float min, float max, const char* format = "%.0f")
	{
		elements_count++;

		fvector2d size = fvector2d{ 210, 30 };
		fvector2d slider_size = fvector2d{ 170, 8 };
		fvector2d adjust_zone = fvector2d{ 0, 20 };
		fvector2d padding = fvector2d{ 10, 10 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = mouse_in_zone(fvector2d{ pos.x, pos.y + slider_size.y + padding.y - adjust_zone.y }, fvector2d{ slider_size.x, slider_size.y + adjust_zone.y * 1.5f });

		if (!sameLine)
			offset_y += size.y + padding.y;

		//Bg
		if (isHovered || current_element == elements_count)
		{
			//Drag
			if (Input::IsMouseClicked(0, elements_count, true))
			{
				current_element = elements_count;

				fvector2d cursorPos = get_cursor_pos();
				*value = ((cursorPos.x - pos.x) * ((max - min) / slider_size.x)) + min;
				if (*value < min) *value = min;
				if (*value > max) *value = max;
			}

			//drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, Colors::Slider_Hovered);
			//DrawFilledCircle(fvector2d{ pos.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Progress);
			//DrawFilledCircle(fvector2d{ pos.x + slider_size.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Hovered);

			hover_element = true;
		}
		else
		{
			//drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y }, slider_size.x, slider_size.y, Colors::Slider_Idle);
			//DrawFilledCircle(fvector2d{ pos.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Progress);
			//DrawFilledCircle(fvector2d{ pos.x + slider_size.x, pos.y + padding.y + 9.3f }, 3.1f, Colors::Slider_Idle);
		}


		//Value
		float oneP = slider_size.x / (max - min);

		flinearcolor kolorek = flinearcolor{ 0.09531, 0.0865, 0.07619, 0.07036 };
		flinearcolor kolorek2 = flinearcolor{ 1,1,1,1 };
		if (isHovered) {
			kolorek = flinearcolor{ 0.09531, 0.0865, 0.07619, 0.07036 };
			kolorek2 = flinearcolor{ 1,1,1,1 };
		}
		else {
			kolorek = flinearcolor{ 0.09531, 0.0865, 0.07619, 0.02624 };
			kolorek2 = flinearcolor{ 1,1,1,0.30499 };
		}

		//drawFilledRect(fvector2d{ pos.x, pos.y + slider_size.y + padding.y }, oneP * (*value - min), slider_size.y, Colors::Slider_Progress);
		//DrawFilledCircle(fvector2d{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 2.66f + padding.y }, 8.0f, Colors::Slider_Button);
		//DrawFilledCircle(fvector2d{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 2.66f + padding.y }, 4.0f, Colors::Slider_Progress);

		draw_filled_rect(fvector2d(pos.x, pos.y + slider_size.y + padding.y * 2), slider_size.x, slider_size.y, kolorek);

		//Value
		draw_filled_rect(fvector2d(pos.x, pos.y + slider_size.y + padding.y * 2), oneP * (*value - min), slider_size.y, flinearcolor{ 0.27, 0.00, 0.43,255 });

		fvector2d textPos = fvector2d{ pos.x, pos.y + 7 };
		canvas->text_wrapper_ooo(fvector2d(textPos.x, textPos.y), kolorek2, false, name);

		auto value_converted = valorant::string::float_to_string(*value);
		canvas->text_wrapper_ooo(fvector2d(textPos.x + slider_size.x - canvas->strlen(valorant::classes::font, value_converted).x, textPos.y), kolorek2, false, value_converted);


		draw_filled_circle(fvector2d{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 13.6f + padding.y }, 6.0f, flinearcolor(1, 1, 1, 1));

		//char buffer[32];
		//sprintf_s(buffer, format, *value);
		//fvector2d valuePos = fvector2d{ pos.x + oneP * (*value - min), pos.y + slider_size.y + 20 + padding.y };
		//TextCenter(buffer, valuePos, Colors::Text, false);


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}



	bool checkbox_enabled[256];


	void combo_box_new(wchar_t* name, fvector2d size, int* value, Vector<const char*> Items)
	{
		elements_count++;

		fvector2d padding = fvector2d{ 5, 10 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = mouse_in_zone(fvector2d{ pos.x, pos.y }, size);

		//Bg
		if (isHovered || checkbox_enabled[elements_count])
		{
			draw_filled_rect(fvector2d{ pos.x, pos.y }, size.x, size.y, flinearcolor{ 0.09531, 0.0865, 0.07619, 0.07036 });

			hover_element = true;
		}
		else
		{
			draw_filled_rect(fvector2d{ pos.x, pos.y }, size.x, size.y, flinearcolor{ 0.09531, 0.0865, 0.07619, 0.02624 });
		}

		if (!sameLine)
			offset_y += size.y + padding.y;

		//Text
		fvector2d textPos = fvector2d{ pos.x + size.x + 5.0f, pos.y };
		canvas->text_wrapper(fvector2d(textPos.x, textPos.y), flinearcolor{ 255,255,255,255 }, false, name);

		//TextLeft(name, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

		//Elements
		bool isHovered2 = false;
		fvector2d element_pos = pos;
		int num = 0;

		if (checkbox_enabled[elements_count])
		{
			current_element_size.x = element_pos.x - 5.0f;
			current_element_size.y = element_pos.y - 5.0f;
		}
		for (int i = 0; i < Items.size(); i++)
		{
			auto item = Items[i];
			//Selected Element
			if (num == *value)
			{
				fvector2d _textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
				TextCenter((char*)item, _textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
			}

			
			if (checkbox_enabled[elements_count])
			{
				element_pos.y += 35.0f;

				isHovered2 = mouse_in_zone(fvector2d{ element_pos.x, element_pos.y }, fvector2d{ size.x, 35.0f });
				//0.01096, 0.00857, 0.00605
				PostRenderer::drawFilledRect(fvector2d{ element_pos.x, element_pos.y }, size.x, 35.0f, flinearcolor(0.01096, 0.00857, 0.00605, 0.7913));
				if (isHovered2)
				{
					hover_element = true;
					PostRenderer::drawFilledRect(fvector2d{ element_pos.x + 3, element_pos.y + 3 }, size.x - 6, 35.0f - 6, flinearcolor{ 0.09531, 0.0865, 0.07619, 0.07036 });

					//Click
					if (Input::IsMouseClicked(0, elements_count, false))
					{
						*value = num;
						checkbox_enabled[elements_count] = false;
					}
				}
				else
				{
					PostRenderer::drawFilledRect(fvector2d{ element_pos.x + 3, element_pos.y + 3 }, size.x - 6, 35.0f - 6, flinearcolor{ 0.09531, 0.0865, 0.07619, 0.02624 });
				}

				PostRenderer::TextLeft(item, fvector2d{ element_pos.x + 5.0f, element_pos.y + 16.0f }, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
			}
			
			num++;
			
		}
		if (checkbox_enabled[elements_count])
		{
			current_element_size.x = element_pos.x + 5.0f;
			current_element_size.y = element_pos.y + 5.0f;
		}


		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && Input::IsMouseClicked(0, elements_count, false))
		{
			checkbox_enabled[elements_count] = !checkbox_enabled[elements_count];
		}
		if (!isHovered && !isHovered2 && Input::IsMouseClicked(0, elements_count, false))
		{
			checkbox_enabled[elements_count] = false;
		}
	}


	int active_hotkey = -1;
	bool already_pressed = false;

	//String VirtualKeyCodeToString(hack_uchar virtualKey)
	//{
	//	hack_uint scanCode = o_mapvirtualkeya(virtualKey, 0);
	//
	//	if (virtualKey == 0x01)
	//	{
	//		return _("MOUSE0").decrypt();
	//	}
	//	if (virtualKey == 0x02)
	//	{
	//		return _("MOUSE1").decrypt();
	//	}
	//	if (virtualKey == 0x04)
	//	{
	//		return _("MBUTTON").decrypt();
	//	}
	//	if (virtualKey == 0x05)
	//	{
	//		return _("XBUTTON1").decrypt();
	//	}
	//	if (virtualKey == 0x06)
	//	{
	//		return _("XBUTTON2").decrypt();
	//	}
	//
	//	char szName[128];
	//	int result = 0;
	//	switch (virtualKey)
	//	{
	//	case 0x25: case 0x26: case 0x27: case 0x28:
	//	case 0xA3: case 0xA5:
	//	case 0x5B: case 0x5C: case 0x5D:
	//	case 0x21: case 0x22:
	//	case 0x23: case 0x24:
	//	case 0x2D: case 0x2E:
	//	case 0x6F:
	//	case 0x90:
	//		scanCode |= 0x0100;
	//	default:
	//		result = o_getkeynametexta(scanCode << 16, szName, 128);
	//	}
	//
	//	return szName;
	//}
	void hot_key(wchar_t* name, fvector2d size, fkey* key)
	{
		elements_count++;
		
		fvector2d padding = fvector2d{ 5, 10 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y};
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y + (last_element_size.y / 2) - size.y / 2 - 16;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = mouse_in_zone(fvector2d{ pos.x, pos.y }, size);
		
		//Bg
		if (isHovered)
		{
			draw_filled_rect(fvector2d{ pos.x, pos.y }, size.x, size.y, flinearcolor{ 0.27, 0.00, 0.43,255 });
			hover_element = true;
		}
		else
		{
			draw_filled_rect(fvector2d{ pos.x, pos.y }, size.x, size.y, flinearcolor{ 0.27, 0.00, 0.43,255 });
		}
		
		if (!sameLine)
			offset_y += size.y + padding.y;
		
		static bool is_pressed = false;
		
		if (is_pressed)
		{
			//Text
			fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
			TextCenter(_("[Press Key]"), textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
		
			if (!cached::controller->is_input_key_down(valorant::classes::keys::LeftMouseButton))
			{
				already_pressed = false;
			}
		
			if (!already_pressed)
			{
				for (int keys_amount = 0; keys_amount < 50; keys_amount++) {
					if (cached::controller->is_input_key_down(valorant::classes::keys::array_of_keys[keys_amount])) {
						*key = valorant::classes::keys::array_of_keys[keys_amount];
						is_pressed = false;
					}
				}
			}
		}
		else
		{
			fkey nigga_key = *key;
		
			//Text
			fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
			//TextCenter((char*)VirtualKeyCodeToString(*key).c_str(), textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
			TextCenter2(valorant::string::name_to_string(nigga_key.KeyName).c_str(), textPos, flinearcolor{1.0f, 1.0f, 1.0f, 1.0f}, false);
		
			if (isHovered)
			{
				if (Input::IsMouseClicked(0, elements_count, false))
				{
					already_pressed = true;
					is_pressed = true;
					//active_hotkey = elements_count;
		
					//Queue Fix
					for (int keys_amount = 0; keys_amount < 50; keys_amount++) {
						if (cached::controller->is_input_key_down(valorant::classes::keys::array_of_keys[keys_amount])) {
		
						}
					}
				}
			}
			else
			{
				if (Input::IsMouseClicked(0, elements_count, false))
				{
					is_pressed = false;
					//active_hotkey = -1;
				}
			}
		}
		
		
		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}

	//void Hotkey2(wchar_t* name, fvector2d size, int* key)
	//{
	//	elements_count++;
	//
	//	fvector2d padding = fvector2d{ 5, 10 };
	//	fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
	//	if (sameLine)
	//	{
	//		pos.x = last_element_pos.x + last_element_size.x + padding.x;
	//		pos.y = last_element_pos.y + (last_element_size.y / 2) - size.y / 2 - 16;
	//	}
	//	if (pushY)
	//	{
	//		pos.y = pushYvalue;
	//		pushY = false;
	//		pushYvalue = 0.0f;
	//		offset_y = pos.y - menu_pos.y;
	//	}
	//	bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);
	//
	//	//Bg
	//	if (isHovered)
	//	{
	//		draw_filled_rect(fvector2d{ pos.x, pos.y }, size.x, size.y, flinearcolor{ 0.27, 0.00, 0.43,255 });
	//		hover_element = true;
	//	}
	//	else
	//	{
	//		draw_filled_rect(fvector2d{ pos.x, pos.y }, size.x, size.y, flinearcolor{ 0.27, 0.00, 0.43,255 });
	//	}
	//
	//	if (!sameLine)
	//		offset_y += size.y + padding.y;
	//
	//	static bool is_pressed = false;
	//
	//	if (is_pressed)
	//	{
	//		//Text
	//		fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
	//		TextCenter(_("[Press Key]"), textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
	//
	//		if (!ZeroGUI::Input::IsAnyMouseDown())
	//		{
	//			already_pressed = false;
	//		}
	//
	//		if (!already_pressed)
	//		{
	//			for (int code = 0; code < 255; code++)
	//			{
	//				if (o_getasynckeystate(code))
	//				{
	//					*key = code;
	//					is_pressed = false;
	//				}
	//			}
	//		}
	//	}
	//	else
	//	{
	//		//Text
	//		fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
	//		TextCenter((char*)VirtualKeyCodeToString(*key).c_str(), textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);
	//
	//		if (isHovered)
	//		{
	//			if (Input::IsMouseClicked(0, elements_count, false))
	//			{
	//				already_pressed = true;
	//				is_pressed = true;
	//				//active_hotkey = elements_count;
	//
	//				//Queue Fix
	//				for (int code = 0; code < 255; code++)
	//					if (o_getasynckeystate(code)) {}
	//			}
	//		}
	//		else
	//		{
	//			if (Input::IsMouseClicked(0, elements_count, false))
	//			{
	//				is_pressed = false;
	//				//active_hotkey = -1;
	//			}
	//		}
	//	}
	//
	//
	//	sameLine = false;
	//	last_element_pos = pos;
	//	last_element_size = size;
	//	if (first_element_pos.x == 0.0f)
	//		first_element_pos = pos;
	//}


	int active_picker = -1;
	flinearcolor saved_color;
	bool ColorPixel(fvector2d pos, fvector2d size, flinearcolor* original, flinearcolor color)
	{
		PostRenderer::drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, color);

		//Выбранный цвет
		if (original->red == color.red && original->green == color.green && original->blue == color.blue)
		{
			PostRenderer::Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ pos.x + size.x - 1, pos.y }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
			PostRenderer::Draw_Line(fvector2d{ pos.x, pos.y + size.y - 1 }, fvector2d{ pos.x + size.x - 1, pos.y + size.y - 1 }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
			PostRenderer::Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ pos.x, pos.y + size.y - 1 }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
			PostRenderer::Draw_Line(fvector2d{ pos.x + size.x - 1, pos.y }, fvector2d{ pos.x + size.x - 1, pos.y + size.y - 1 }, 1.0f, flinearcolor{ 0.0f, 0.0f, 0.0f, 1.0f });
		}

		//Смена цвета
		bool isHovered = mouse_in_zone(fvector2d{ pos.x, pos.y }, size);
		if (isHovered)
		{
			if (Input::IsMouseClicked(0, elements_count, false))
				*original = color;
		}

		return true;
	}
	void color_picker(const wchar_t* name, flinearcolor* color)
	{
		elements_count++;

		float size = 17;
		fvector2d padding = fvector2d{ 10, 10 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = mouse_in_zone(fvector2d{ pos.x, pos.y }, fvector2d{ size, size });

		if (!sameLine)
			offset_y += size + padding.y;

		if (active_picker == elements_count)
		{
			hover_element = true;

			float sizePickerX = 250;
			float sizePickerY = 250;
			bool isHoveredPicker = mouse_in_zone(fvector2d{ pos.x, pos.y }, fvector2d{ sizePickerX, sizePickerY - 60 });

			//Background
			PostRenderer::drawFilledRect(fvector2d{ pos.x, pos.y }, sizePickerX, sizePickerY - 65, Colors::ColorPicker_Background);

			//float pixedSize = sizePickerY / pixels;
			//flinearcolor temp_color{1.0f, 1.0f, 1.0f, 1.0f};
			//float iterator = 0.0f;
			//
			//for (int y = 0; y < pixels; y++)
			//{
			//	for (int x = 0; x < pixels; x++)
			//	{
			//		ColorPixel(fvector2d{ pos.x + pixedSize * x, pos.y + pixedSize * y }, pixedSize, color, temp_color);
			//		temp_color.R -= (1.0f - saved_color.R) / pixels;
			//		temp_color.G -= (1.0f - saved_color.G) / pixels;
			//		temp_color.B -= (1.0f - saved_color.B) / pixels;
			//	}
			//	
			//	iterator += 1.0f / pixels;
			//	temp_color = flinearcolor{ 1.0f - iterator, 1.0f - iterator, 1.0f - iterator, 1.0f };
			//}

			fvector2d pixelSize = fvector2d{ sizePickerX / 12, sizePickerY / 12 };

			//0
			{
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 174 / 255.f, 235 / 255.f, 253 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 136 / 255.f, 225 / 255.f, 251 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 108 / 255.f, 213 / 255.f, 250 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 89 / 255.f, 175 / 255.f, 213 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 76 / 255.f, 151 / 255.f, 177 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 60 / 255.f, 118 / 255.f, 140 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 43 / 255.f, 85 / 255.f, 100 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 32 / 255.f, 62 / 255.f, 74 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 0, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.0f });
			}
			//1
			{
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 175 / 255.f, 205 / 255.f, 252 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 132 / 255.f, 179 / 255.f, 252 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 90 / 255.f, 152 / 255.f, 250 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 55 / 255.f, 120 / 255.f, 250 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 49 / 255.f, 105 / 255.f, 209 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 38 / 255.f, 83 / 255.f, 165 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 28 / 255.f, 61 / 255.f, 120 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 20 / 255.f, 43 / 255.f, 86 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 1, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 247 / 255.f, 247 / 255.f, 247 / 255.f, 1.0f });
			}
			//2
			{
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 153 / 255.f, 139 / 255.f, 250 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 101 / 255.f, 79 / 255.f, 249 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 64 / 255.f, 50 / 255.f, 230 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 54 / 255.f, 38 / 255.f, 175 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 39 / 255.f, 31 / 255.f, 144 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 32 / 255.f, 25 / 255.f, 116 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 21 / 255.f, 18 / 255.f, 82 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 16 / 255.f, 13 / 255.f, 61 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 2, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 228 / 255.f, 228 / 255.f, 228 / 255.f, 1.0f });
			}
			//3
			{
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 194 / 255.f, 144 / 255.f, 251 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 165 / 255.f, 87 / 255.f, 249 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 142 / 255.f, 57 / 255.f, 239 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 116 / 255.f, 45 / 255.f, 184 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 92 / 255.f, 37 / 255.f, 154 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 73 / 255.f, 29 / 255.f, 121 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 53 / 255.f, 21 / 255.f, 88 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 37 / 255.f, 15 / 255.f, 63 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 3, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 203 / 255.f, 203 / 255.f, 203 / 255.f, 1.0f });
			}
			//4
			{
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 224 / 255.f, 162 / 255.f, 197 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 210 / 255.f, 112 / 255.f, 166 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 199 / 255.f, 62 / 255.f, 135 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 159 / 255.f, 49 / 255.f, 105 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 132 / 255.f, 41 / 255.f, 89 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 104 / 255.f, 32 / 255.f, 71 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 75 / 255.f, 24 / 255.f, 51 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 54 / 255.f, 14 / 255.f, 36 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 4, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 175 / 255.f, 175 / 255.f, 175 / 255.f, 1.0f });
			}
			//5
			{
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 235 / 255.f, 175 / 255.f, 176 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 227 / 255.f, 133 / 255.f, 135 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 219 / 255.f, 87 / 255.f, 88 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 215 / 255.f, 50 / 255.f, 36 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 187 / 255.f, 25 / 255.f, 7 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 149 / 255.f, 20 / 255.f, 6 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 107 / 255.f, 14 / 255.f, 4 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 77 / 255.f, 9 / 255.f, 3 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 5, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 144 / 255.f, 144 / 255.f, 144 / 255.f, 1.0f });
			}
			//6
			{
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 241 / 255.f, 187 / 255.f, 171 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 234 / 255.f, 151 / 255.f, 126 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 229 / 255.f, 115 / 255.f, 76 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 227 / 255.f, 82 / 255.f, 24 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 190 / 255.f, 61 / 255.f, 15 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 150 / 255.f, 48 / 255.f, 12 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 107 / 255.f, 34 / 255.f, 8 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 79 / 255.f, 25 / 255.f, 6 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 6, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 113 / 255.f, 113 / 255.f, 113 / 255.f, 1.0f });
			}
			//7
			{
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 245 / 255.f, 207 / 255.f, 169 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 240 / 255.f, 183 / 255.f, 122 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 236 / 255.f, 159 / 255.f, 74 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 234 / 255.f, 146 / 255.f, 37 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 193 / 255.f, 111 / 255.f, 28 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 152 / 255.f, 89 / 255.f, 22 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 110 / 255.f, 64 / 255.f, 16 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 80 / 255.f, 47 / 255.f, 12 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 7, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 82 / 255.f, 82 / 255.f, 82 / 255.f, 1.0f });
			}
			//8
			{
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 247 / 255.f, 218 / 255.f, 170 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 244 / 255.f, 200 / 255.f, 124 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 241 / 255.f, 182 / 255.f, 77 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 239 / 255.f, 174 / 255.f, 44 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 196 / 255.f, 137 / 255.f, 34 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 154 / 255.f, 108 / 255.f, 27 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 111 / 255.f, 77 / 255.f, 19 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 80 / 255.f, 56 / 255.f, 14 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 8, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 54 / 255.f, 54 / 255.f, 54 / 255.f, 1.0f });
			}
			//9
			{
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 254 / 255.f, 243 / 255.f, 187 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 253 / 255.f, 237 / 255.f, 153 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 253 / 255.f, 231 / 255.f, 117 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 254 / 255.f, 232 / 255.f, 85 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 242 / 255.f, 212 / 255.f, 53 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 192 / 255.f, 169 / 255.f, 42 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 138 / 255.f, 120 / 255.f, 30 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 101 / 255.f, 87 / 255.f, 22 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 9, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 29 / 255.f, 29 / 255.f, 29 / 255.f, 1.0f });
			}
			//10
			{
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 247 / 255.f, 243 / 255.f, 185 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 243 / 255.f, 239 / 255.f, 148 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 239 / 255.f, 232 / 255.f, 111 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 235 / 255.f, 229 / 255.f, 76 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 208 / 255.f, 200 / 255.f, 55 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 164 / 255.f, 157 / 255.f, 43 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 118 / 255.f, 114 / 255.f, 31 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 86 / 255.f, 82 / 255.f, 21 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 10, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 9 / 255.f, 9 / 255.f, 9 / 255.f, 1.0f });
			}
			//11
			{
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 0 }, pixelSize, color, flinearcolor{ 218 / 255.f, 232 / 255.f, 182 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 1 }, pixelSize, color, flinearcolor{ 198 / 255.f, 221 / 255.f, 143 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 2 }, pixelSize, color, flinearcolor{ 181 / 255.f, 210 / 255.f, 103 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 3 }, pixelSize, color, flinearcolor{ 154 / 255.f, 186 / 255.f, 76 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 4 }, pixelSize, color, flinearcolor{ 130 / 255.f, 155 / 255.f, 64 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 5 }, pixelSize, color, flinearcolor{ 102 / 255.f, 121 / 255.f, 50 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 6 }, pixelSize, color, flinearcolor{ 74 / 255.f, 88 / 255.f, 36 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 7 }, pixelSize, color, flinearcolor{ 54 / 255.f, 64 / 255.f, 26 / 255.f, 1.0f });
				ColorPixel(fvector2d{ pos.x + pixelSize.x * 11, pos.y + pixelSize.y * 8 }, pixelSize, color, flinearcolor{ 0 / 255.f, 0 / 255.f, 0 / 255.f, 1.0f });
			}



			if (isHoveredPicker)
			{
				if (Input::IsMouseClicked(0, elements_count, false))
				{

				}
			}
			else
			{
				if (Input::IsMouseClicked(0, elements_count, false))
				{
					active_picker = -1;
					//hover_element = false;
				}
			}
		}
		else
		{
			//Bg
			if (isHovered)
			{
				draw_filled_rect(fvector2d{ pos.x, pos.y }, size, size, Colors::Checkbox_Hovered);
				hover_element = true;
			}
			else
			{
				draw_filled_rect(fvector2d{ pos.x, pos.y }, size, size, Colors::Checkbox_Idle);
			}

			//Color
			draw_filled_rect(fvector2d{ pos.x , pos.y }, size , size , *color);

			//Text
			fvector2d textPos = fvector2d{ pos.x + size + 5.0f, pos.y};

			flinearcolor kolorek2 = flinearcolor{ 1,1,1,1 };
			if (isHovered) {
				kolorek2 = flinearcolor{ 1,1,1,1 };
			}
			else {
				kolorek2 = flinearcolor{ 1,1,1,0.30499 };
			}


			canvas->text_wrapper_ooo(fvector2d(textPos.x, textPos.y), kolorek2, false, name);

			//TextLeft(name, textPos, flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, false);

			if (isHovered && Input::IsMouseClicked(0, elements_count, false))
			{
				saved_color = *color;
				active_picker = elements_count;
			}
		}


		sameLine = false;
		last_element_pos = pos;
		//last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}


	void post_renderer()
	{
		for (int i = 0; i < 128; i++)
		{
			if (PostRenderer::drawlist[i].type != -1)
			{
				//Filled Rect
				if (PostRenderer::drawlist[i].type == 1)
				{
					zero_gui::draw_filled_rect(PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].size.x, PostRenderer::drawlist[i].size.y, PostRenderer::drawlist[i].color);
				}
				//TextLeft
				else if (PostRenderer::drawlist[i].type == 2)
				{
					zero_gui::TextLeft(PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].color, PostRenderer::drawlist[i].outline);
				}
				//TextCenter
				else if (PostRenderer::drawlist[i].type == 3)
				{
					zero_gui::TextCenter(PostRenderer::drawlist[i].name, PostRenderer::drawlist[i].pos, PostRenderer::drawlist[i].color, PostRenderer::drawlist[i].outline);
				}
				//Draw_Line
				else if (PostRenderer::drawlist[i].type == 4)
				{
					Draw_Line(PostRenderer::drawlist[i].from, PostRenderer::drawlist[i].to, PostRenderer::drawlist[i].thickness, PostRenderer::drawlist[i].color);
				}

				PostRenderer::drawlist[i].type = -1;
			}
		}
	}
}

