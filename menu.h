#pragma once
flinearcolor invisble = flinearcolor(255, 255, 255, 255);
flinearcolor visible = flinearcolor(255, 255, 255, 255);
flinearcolor invisbleskel = flinearcolor(255, 255, 255, 255);
flinearcolor visibleskel = flinearcolor(255, 255, 255, 255);
flinearcolor fovcircle = flinearcolor(255, 255, 255, 255);
flinearcolor deadzone_fovcircle = flinearcolor(255, 0, 0, 255);
flinearcolor recoilcrosshair = flinearcolor(255, 255, 255, 255);
flinearcolor healthbar_color = flinearcolor(0, 1, 0, 1);
flinearcolor shieldbar_color = flinearcolor(0, 0.9, 1, 1);

namespace settings {
    fkey aimkey;
    fkey masterswitch_esp;
    fkey tpkey;
}


void menu_tick() {


    

    if (cached::controller->was_input_key_just_pressed(settings::tpkey)) settings::third_person = !settings::third_person;
    if (cached::controller->was_input_key_just_pressed(settings::masterswitch_esp)) settings::esp::master_switch = !settings::esp::master_switch;



        zero_gui::Input::Handle();



    if (zero_gui::new_window(_(L"x3n3 | Slotted"), &pos, fvector2d{ 884, 600 }))
    {
        //Simple Tabs

        zero_gui::next_column(24 + 24);
        zero_gui::place_dummy(fvector2d(0, 80));

        //static int tab = 0;
        auto hiddenAimbot(_(L"Aimbot"));
        if (zero_gui::button_tab(hiddenAimbot.decrypt(), L"A", fvector2d{ 109, 44 }, zero_gui::tab == 0)) zero_gui::tab = 0;
        hiddenAimbot.encrypt();

        auto hiddenESP(_(L"ESP"));
        if (zero_gui::button_tab(hiddenESP.decrypt(), L"V", fvector2d{ 109, 44 }, zero_gui::tab == 1)) zero_gui::tab = 1;
        hiddenESP.encrypt();

        auto hiddenOESP(_(L"Other"));
        if (zero_gui::button_tab(hiddenOESP.decrypt(), L"O", fvector2d{ 109, 44 }, zero_gui::tab == 3)) zero_gui::tab = 3;
        hiddenOESP.encrypt();

        auto hiddenMisc(_(L"Misc"));
        if (zero_gui::button_tab(hiddenMisc.decrypt(), L"M", fvector2d{ 109, 44 }, zero_gui::tab == 2)) zero_gui::tab = 2;
        hiddenMisc.encrypt();

        //auto hiddenColors(_(L"Colors"));
        //if (ZeroGUI::ButtonTab(hiddenColors.decrypt(), fvector2d{ 109, 44 }, tab == 3)) tab = 3;
        //hiddenColors.encrypt();

        auto posy = pos.y + 24 + 24;
        auto widtht = (850 / 2) - ((181 / 2) + (24 + 12)) - 48;

        if (zero_gui::tab == 0) {


            zero_gui::push_next_element_y(zero_gui::first_element_pos.y + 12, false);
            zero_gui::next_column((24 * 3) + 181);

            zero_gui::place_dummy(fvector2d(0, 2));

            zero_gui::check_box(hiddenAimbot.decrypt(), &settings::aimbot::aim_bot);

            hiddenAimbot.encrypt();

            zero_gui::same_line();

            zero_gui::hot_key(_(L"Aim hotkey"), fvector2d(140, 24), &settings::aimkey);
            zero_gui::slider_int(_(L"Field Of View"), &settings::aimbot::aim_fov, 10, 360);
            zero_gui::slider_int(_(L"Smoothing"), &settings::aimbot::aim_smooth, 1, 10);

            zero_gui::check_box(_(L"Enable deadzone"), &settings::aimbot::enable_deadzone);
            zero_gui::slider_int(_(L"Deadzone fov"), &settings::aimbot::deadzone_fov, 1, 120);
            if (settings::aimbot::deadzone_fov >= settings::aimbot::aim_fov - 5) {
                settings::aimbot::aim_fov = settings::aimbot::deadzone_fov + 5;
            }

            zero_gui::check_box(_(L"Recoil Control System"), &settings::aimbot::rcs);
            //zero_gui::check_box(_(L"No Spread (risk)"), &settings::aimbot::no_spread);
            //ZeroGUI::Checkbox(_(L"Auto Aim/Shoot"), &settings::auto_aim_shoot);
            zero_gui::check_box(_(L"FoV Circle"), &settings::aimbot::draw_fov);
            //ZeroGUI::Checkbox(_(L"S4ndalone RCS"), &settings::standalone_rcs);
            zero_gui::check_box(_(L"Target Line"), &settings::aimbot::target_line);


            

            //if (settings::rcs) {
            //    ZeroGUI::SliderFloat(_(L"RCS X "), &settings::rcs_x, 0, 1);
            //    ZeroGUI::SliderFloat(_(L"RCS Y "), &settings::rcs_y, 0, 1);
            //}
            zero_gui::push_next_element_y(zero_gui::first_element_pos.y + 12, false);
            zero_gui::next_column((24 * 3) + 181 + (850 / 2) - ((181 / 2) + (24 + 12)) + 24);

            zero_gui::place_dummy(fvector2d(0, 2));


            auto widtht = (850 / 2) - ((181 / 2) + (24 + 12)) - 48;
            auto x_position_center = (24 * 3) + 181 + (850 / 2) - ((181 / 2) + (24 + 12)) + 24 + (widtht / 2);
            zero_gui::push_next_element_y(12, true);
            zero_gui::next_column(x_position_center - 15);
            zero_gui::checkbox_button(_(L"HeadButt"), fvector2d(30, 30), &settings::aimbot::head_enabled);
            zero_gui::next_column(x_position_center - 40);
            zero_gui::checkbox_button(_(L"TorsoeadButt"), fvector2d(80, 80), &settings::aimbot::body_enabled);
            zero_gui::next_column(x_position_center - 20);
            zero_gui::checkbox_button(_(L"TorsoeadButt"), fvector2d(40, 70), &settings::aimbot::legs_enabled);

            //ZeroGUI::Checkbox(_(L"Trigger"), &settings::triggerbot);
            //if (settings::triggerbot_on_key) {
            //
            //    ZeroGUI::last_element_size.x = 104;
            //    ZeroGUI::Hotkey2(_(L"hotkey2"), fvector2d(120, 24), &settings::trigger_key);
            //}
            //ZeroGUI::Checkbox(_(L"On key"), &settings::triggerbot_on_key);



        }
        else if (zero_gui::tab == 1) {


            zero_gui::push_next_element_y(zero_gui::first_element_pos.y + 12, false);
            zero_gui::next_column((24 * 3) + 181);
            zero_gui::place_dummy(fvector2d(0, 2));
            zero_gui::check_box(_(L"Toggle"), &settings::esp::master_switch);
            zero_gui::same_line(); zero_gui::hot_key(_(L"AAA"), fvector2d(120, 24), &settings::masterswitch_esp);

            zero_gui::check_box(_(L"Box ESP"), &settings::esp::box_esp);


            zero_gui::check_box(_(L"Fill box"), &settings::esp::fill_box);
            zero_gui::check_box(_(L"Box outline"), &settings::esp::box_online);
            zero_gui::check_box(_(L"Enable snaplines"), &settings::esp::snap_lines);

            zero_gui::check_box(_(L"Name ESP"), &settings::esp::player_name);
            zero_gui::check_box(_(L"Agent ESP"), &settings::esp::agent_esp);
            zero_gui::check_box(_(L"Head ESP"), &settings::esp::head_dot);
            zero_gui::check_box(_(L"Skeleton ESP"), &settings::esp::skeleton);
            zero_gui::check_box(_(L"Weapon ESP"), &settings::esp::weapon_esp);
            zero_gui::check_box(_(L"Weapon icon"), &settings::esp::weapon_icon);
            zero_gui::check_box(_(L"Health Bar ESP"), &settings::esp::health_bar);
            zero_gui::check_box(_(L"Shield Bar ESP"), &settings::esp::shield_bar);
            zero_gui::check_box(_(L"Engine Radar ESP (risky)"), &settings::esp::engine_radar);


            zero_gui::push_next_element_y(zero_gui::first_element_pos.y + 12, false);
            zero_gui::next_column((24 * 3) + 181 + (850 / 2) - ((181 / 2) + (24 + 12)) + 24);
            zero_gui::place_dummy(fvector2d(0, 2));
            zero_gui::color_picker(_(L"Visible box esp"), &visible);
            zero_gui::color_picker(_(L"Invisble box esp"), &invisble);
            zero_gui::color_picker(_(L"Visible Skel esp"), &visibleskel);
            zero_gui::color_picker(_(L"Invisble Skel esp"), &invisbleskel);
            zero_gui::color_picker(_(L"Visualize aimbot"), &fovcircle);
            zero_gui::color_picker(_(L"Visualize dead zone fov"), &deadzone_fovcircle);
            zero_gui::color_picker(_(L"Recoil X/Y xhair ESP"), &recoilcrosshair);
            zero_gui::color_picker(_(L"Healthbar ESP"), &healthbar_color);
            zero_gui::color_picker(_(L"Shieldbar ESP"), &shieldbar_color);

            Vector<const char*> lmao_items;
            lmao_items.push_back("Full");
            lmao_items.push_back("Corner");
            lmao_items.push_back("3D");
            zero_gui::combo_box_new(_(L"Box type"), fvector2d(140, 24), &settings::esp::box_type_index, lmao_items);
            lmao_items.clear();

            Vector<const char*> lmao_items2;
            lmao_items2.push_back("Top");
            lmao_items2.push_back("Middle");
            lmao_items2.push_back("Bottom");
            zero_gui::combo_box_new(_(L"Snaplines pos"), fvector2d(140, 24), &settings::esp::snaplines_pos_index, lmao_items2);
            lmao_items2.clear();

            Vector<const char*> lmao_items3;
            lmao_items3.push_back("Horizontal");
            lmao_items3.push_back("Vertical");
            zero_gui::combo_box_new(_(L"Bar type"), fvector2d(140, 24), &settings::esp::health_bar_index, lmao_items3);
            lmao_items3.clear();


            //ZeroGUI::Checkbox(_(L"Ch4ms (risky!)"), &settings::chams);

        }
        else if (zero_gui::tab == 2) {

            zero_gui::push_next_element_y(zero_gui::first_element_pos.y + 12, false);
            zero_gui::next_column((24 * 3) + 181);
            zero_gui::place_dummy(fvector2d(0, 2));
            zero_gui::check_box(_(L"Disable Team Check"), &settings::dtm);
            zero_gui::check_box(_(L"Visible Check"), &settings::visible_check);
            zero_gui::check_box(_(L"Watermark"), &settings::watermark);
            zero_gui::check_box(_(L"Load Dormant Enemies"), &settings::esp::dormant_esp);


            zero_gui::check_box(_(L"Recoil crosshair"), &settings::recoil_crosshair);
            zero_gui::check_box(_(L"Wireframe hands"), &settings::wireframe_hands);
            zero_gui::check_box(_(L"Wireframe weapon"), &settings::wireframe_weaapon);




            zero_gui::push_next_element_y(zero_gui::first_element_pos.y + 12, false);
            zero_gui::next_column((24 * 3) + 181 + (850 / 2) - ((181 / 2) + (24 + 12)) + 24);
            zero_gui::place_dummy(fvector2d(0, 2));
            zero_gui::check_box(_(L"Large weapon"), &settings::big_weapon);
            zero_gui::check_box(_(L"Third person"), &settings::third_person);
            zero_gui::same_line();
            zero_gui::hot_key(_(L"TP Key"), fvector2d(120, 24), &settings::tpkey);
            //ZeroGUI::Checkbox(_(L"Fast crouch"), &settings::fast_crouch);
            zero_gui::check_box(_(L"FOV Changer"), &settings::change_fov);
            zero_gui::slider_float(_(L"F0V Value"), &settings::fov_value, 60, 360);
            zero_gui::check_box(_(L"Spin bot"), &settings::spin_bot);

        }
        else if (zero_gui::tab == 3) {

            zero_gui::push_next_element_y(zero_gui::first_element_pos.y + 12, false);
            zero_gui::next_column((24 * 3) + 181);
            zero_gui::place_dummy(fvector2d(0, 2));

            zero_gui::check_box(_(L"Master Switch"), &settings::esp::master_switch_world);
            zero_gui::check_box(_(L"Spike ESP"), &settings::spike_esp);
            zero_gui::check_box(_(L"Abilities ESP"), &settings::abilities_esp);
            zero_gui::check_box(_(L"Dropped Weapons"), &settings::dropped_esp);



            zero_gui::push_next_element_y(zero_gui::first_element_pos.y + 12, false);
            zero_gui::next_column((24 * 3) + 181 + (850 / 2) - ((181 / 2) + (24 + 12)) + 24);
            zero_gui::place_dummy(fvector2d(0, 2));

            zero_gui::check_box(_(L"Dropped box"), &settings::dropped_box);
            zero_gui::check_box(_(L"Dropped name"), &settings::dropped_name);

            zero_gui::check_box(_(L"Spike box"), &settings::spike_box);
            zero_gui::check_box(_(L"Spike Info"), &settings::spike_info);

        }


        zero_gui::post_renderer();

        fvector2d cursorPos = zero_gui::get_cursor_pos();
        zero_gui::draw_filled_rect(fvector2d(cursorPos.x - 3, cursorPos.y - 3), 6, 6, flinearcolor(1, 1, 1, 1));
    }



    
}
