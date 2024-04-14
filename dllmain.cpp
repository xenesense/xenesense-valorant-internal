#include "includes.h"
#include "menu.h"
//todo weapon esp, spike timer, distance esp





fvector OldPunch = fvector(0,0,0);


void box_3d(fvector origin, fvector extends, flinearcolor col)
{
    origin -= extends / 2.f;

    // bottom plane
    fvector one = origin;
    fvector two = origin; two.x += extends.x;
    fvector three = origin; three.x += extends.x; three.y += extends.y;
    fvector four = origin; four.y += extends.y;

    fvector five = one; five.z += extends.z;
    fvector six = two; six.z += extends.z;
    fvector seven = three; seven.z += extends.z;
    fvector eight = four; eight.z += extends.z;

    fvector2d s1, s2, s3, s4, s5, s6, s7, s8;
    s1 = cached::controller->cool_w2s(one);
    s2 = cached::controller->cool_w2s(two);
    s3 = cached::controller->cool_w2s(three);
    s4 = cached::controller->cool_w2s(four);
    s5 = cached::controller->cool_w2s(five);
    s6 = cached::controller->cool_w2s(six);
    s7 = cached::controller->cool_w2s(seven);
    s8 = cached::controller->cool_w2s(eight);

    // 3 copies of each vertex? trash
    zero_gui::canvas->Line(s1, s2, col);
    zero_gui::canvas->Line(s2, s3, col);
    zero_gui::canvas->Line(s3, s4, col);
    zero_gui::canvas->Line(s4, s1, col);

    zero_gui::canvas->Line(s5, s6, col);
    zero_gui::canvas->Line(s6, s7, col);
    zero_gui::canvas->Line(s7, s8, col);
    zero_gui::canvas->Line(s8, s5, col);

    zero_gui::canvas->Line(s1, s5, col);
    zero_gui::canvas->Line(s2, s6, col);
    zero_gui::canvas->Line(s3, s7, col);
    zero_gui::canvas->Line(s4, s8, col);
}

int get_closest_hitbox(valorant::mesh* mesh) {
    Vector<int> hitboxes;
    if (settings::aimbot::head_enabled) {
        hitboxes.push_back(8);
    }
    if (settings::aimbot::body_enabled) {
        hitboxes.push_back(6);
    }
    if (settings::aimbot::legs_enabled) {
        hitboxes.push_back(3);
    }

    int previous_hitbox = 0;
    float previous_hitbox_dist = FLT_MAX;

    for (int hitbox : hitboxes)
    {

        auto boxee = mesh->get_bone_location(hitbox);
        auto w2sed = cached::controller->cool_w2s(boxee);

        auto dx = w2sed.x - (cached::screen_width / 2);
        auto dy = w2sed.y - (cached::screen_height / 2);

        auto dist = crt::custom_sqrtf(dx * dx + dy * dy);

        if (dist < previous_hitbox_dist) {
            previous_hitbox_dist = dist;
            previous_hitbox = hitbox;
        }

        
    }


    return previous_hitbox;
}

bool done;



bool should_set_tp = false;





void draw_recoil() {
    float screen_width = cached::screen_width;
    float screen_height = cached::screen_height;

    fvector ConvertRotation = (camera_cached::camera_rotation);
    ConvertRotation.normalize();


    auto ControlRotation = cached::controller->get_control_rotation();

    fvector punchAngle = ConvertRotation - ControlRotation;
    punchAngle.normalize();

    int centerX = screen_width / 2; 
    int centerY = screen_height / 2;

    int dx = screen_width / 90;
    int dy = screen_height / 90;

    centerX += (dx * (punchAngle.y));
    centerY -= (dy * (punchAngle.x));

    zero_gui::canvas->draw_circle(centerX, centerY, 5, 10, flinearcolor(255,255,255,255));

}

void smooth(fvector Target, fvector Camera_rotation, float SmoothFactor) {

    fvector ConvertRotation = Camera_rotation;
    ConvertRotation.normalize();

    fvector Smoothed = smooth_aim(ConvertRotation, Target, SmoothFactor);
    //Smoothed.x -= cached::current_equip->get_stability_component()->get_yaw_recoil();
    //Smoothed.y -= cached::current_equip->get_stability_component()->get_pitch_recoil();


    Smoothed.clamp();

    cached::controller->set_control_rotation(Smoothed);
}
void recoil(fvector Target, fvector Camera_rotation, float SmoothFactor) {

   //  Camera 2 Control space
    fvector ConvertRotation = Camera_rotation;
    ConvertRotation.normalize();
    
    // Calculate recoil/aimpunch
    auto ControlRotation = cached::controller->get_control_rotation();
    
    fvector DeltaRotation = ConvertRotation - ControlRotation;
    DeltaRotation.normalize();
    
    DeltaRotation.x *= settings::rcs_x;
    DeltaRotation.y *= settings::rcs_y;
    
    // Remove aimpunch from CameraRotation
    ConvertRotation = Target - (DeltaRotation * SmoothFactor);
    ConvertRotation.normalize();
    
    //Smooth the whole thing
    fvector Smoothed = smooth_aim(Camera_rotation, ConvertRotation, SmoothFactor);
    Smoothed -= (DeltaRotation / SmoothFactor);
    Smoothed.clamp();
    
    
    cached::controller->set_control_rotation(Smoothed);
}

void hk_update_view_target_internal(uintptr_t PlayerCameraManager, FTViewTarget* OutVT, float DeltaTime) {
    o_update_view_target_internal(PlayerCameraManager, OutVT, DeltaTime);

    if (cached::local_pawn && cached::controller) {

        if (settings::third_person) {
            if (valorant::mesh* Mesh = cached::local_pawn->get_mesh()) {
        
                auto LocalHead = Mesh->get_bone_location(8);
                fvector ViewAngle = memory::read<fvector>(uintptr_t(OutVT) + 0x10 + 0x0c);
                fvector ConvAngle = fvector(ViewAngle.x, ViewAngle.y, ViewAngle.z);
                fvector OutputAngle{};
                angle_vectors(fvector(-ConvAngle.x, ConvAngle.y, ConvAngle.z), &OutputAngle);
                OutputAngle *= 350;
                OutputAngle.z -= 3.5f;
                auto FinalLocatoion = memory::read<fvector>(uintptr_t(OutVT) + 0x10 + 0x0) + OutputAngle;
        
                cached::local_pawn->set_3p_mesh_visible(true);
                should_set_tp = true;
                memory::write<fvector>(uintptr_t(OutVT) + 0x10 + 0x0, LocalHead - OutputAngle);
                //OutVT->POV.Location = LocalHead - OutputAngle;
        
                if (settings::spin_bot) {
                    static int i = 0;
        
                    i += 3;
                    if (i > 359) i = 0;
                    if (Mesh) {
                        Mesh->set_world_rotation(fvector(1, i, 1), 0, 0);
                    }
                }
            }
        
        }
        else {
            if (should_set_tp) {
                cached::local_pawn->set_3p_mesh_visible(false);
                should_set_tp = false;
            }
        }

        if (settings::change_fov) {
            memory::write<float>(uintptr_t(OutVT) + 0x10 + 0x18,settings::fov_value);
        }
        
        
        camera_cached::camera_location = memory::read<fvector>(uintptr_t(OutVT) + 0x10 + 0x0);
        camera_cached::camera_rotation = memory::read<fvector>(uintptr_t(OutVT) + 0x10 + 0x0c);
        camera_cached::camera_fov_angle = memory::read<float>(uintptr_t(OutVT) + 0x10 + 0x18);

    }

}


auto player_func(valorant::actor* actor, uintptr_t loc_team_id, valorant::player_state* actor_state) -> void
{
    



    auto health = actor->get_health(); if (health < 1) return;

    //auto actor_state = actor->get_player_state(); 

    if (!settings::dtm) {

        auto team_component = actor_state->get_team_component(); if (!team_component) return;
        auto team_id = memory::read<uintptr_t>(uintptr_t(team_component) + offsets::team_id);
        if (team_id == loc_team_id) return;
    }

    auto actor_mesh = actor->get_mesh(); if (!actor_mesh) return;

    auto root_component = memory::read<uintptr_t>(uintptr_t(actor) + offsets::root_component); if (!root_component) return;
    auto relative_location = memory::read<fvector>(root_component + offsets::relative_location);
    auto relative_rotation = memory::read<fvector>(root_component + offsets::relative_rotation);

    auto bone_array = memory::read<uintptr_t>(uintptr_t(actor_mesh) + offsets::bone_array);
    if (!bone_array) bone_array = memory::read<uintptr_t>(uintptr_t(actor_mesh) + offsets::bone_array + 0x10);

    auto c2w = memory::read<ftransform>(uintptr_t(actor_mesh) + offsets::component_to_world);

    
    auto world_head = actor_mesh->get_bone_location_v2(8, bone_array, c2w);
    auto screen_head = cached::controller->cool_w2s(fvector(world_head.x, world_head.y, world_head.z + 15));

 

    if (!screen_head.is_in_screen()) return;

    if (settings::esp::master_switch) {


        //fvector asdadsa;
        //bool is_visible = settings::visible_check ? cached::controller->line_of_sight_to(target_actor, asdadsa, false) : true;
        bool is_visible = settings::visible_check ? valorant::blueprint::can_player_see_player(cached::local_pawn, actor, false) : true;
       
        
        auto root_bone_out = cached::controller->cool_w2s(actor_mesh->get_bone_location_v2(0, bone_array, c2w)); if (!root_bone_out.is_in_screen()) return;
        float box_height = crt::custom_fabs(screen_head.y - root_bone_out.y);
        float box_width = box_height * 0.6;



        int dormant_val = memory::read<int>(uintptr_t(actor) + offsets::dormant);
        bool dormant = dormant_val == 0 && 1;

        if (!settings::esp::dormant_esp && dormant) return;

        if (settings::esp::fill_box) {
            zero_gui::draw_filled_rect(fvector2d(root_bone_out.x - (box_width / 2), screen_head.y), box_width, box_height, flinearcolor(0, 0, 0, 0.1));
        }
        if (settings::esp::box_esp) {
            if (settings::esp::box_type_index == 0) {
                if (settings::esp::box_online) {
                    zero_gui::canvas->draw_box(fvector2d(root_bone_out.x - (box_width / 2) - 1, screen_head.y), fvector2d(box_width, box_height), 1, flinearcolor(0, 0, 0, 1));
                    zero_gui::canvas->draw_box(fvector2d(root_bone_out.x - (box_width / 2), screen_head.y - 1), fvector2d(box_width, box_height), 1, flinearcolor(0, 0, 0, 1));
                    zero_gui::canvas->draw_box(fvector2d(root_bone_out.x - (box_width / 2) + 1, screen_head.y), fvector2d(box_width, box_height), 1, flinearcolor(0, 0, 0, 1));
                    zero_gui::canvas->draw_box(fvector2d(root_bone_out.x - (box_width / 2), screen_head.y + 1), fvector2d(box_width, box_height), 1, flinearcolor(0, 0, 0, 1));
                }
                zero_gui::canvas->draw_box(fvector2d(root_bone_out.x - (box_width / 2), screen_head.y), fvector2d(box_width, box_height), settings::esp::box_online ? 1 : 2, is_visible ? visible : invisble);
            }
            else if (settings::esp::box_type_index == 1) {
                if (settings::esp::box_online) {
                    zero_gui::canvas->draw_cornered_box(root_bone_out.x - (box_width / 2) - 1, screen_head.y, box_width, box_height, flinearcolor(0, 0, 0, 1), 1);
                    zero_gui::canvas->draw_cornered_box(root_bone_out.x - (box_width / 2), screen_head.y - 1, box_width, box_height, flinearcolor(0, 0, 0, 1), 1);
                    zero_gui::canvas->draw_cornered_box(root_bone_out.x - (box_width / 2) + 1, screen_head.y, box_width, box_height, flinearcolor(0, 0, 0, 1), 1);
                    zero_gui::canvas->draw_cornered_box(root_bone_out.x - (box_width / 2), screen_head.y + 1, box_width, box_height, flinearcolor(0, 0, 0, 1), 1);
                }
                zero_gui::canvas->draw_cornered_box(root_bone_out.x - (box_width / 2), screen_head.y, box_width, box_height, is_visible ? visible : invisble, settings::esp::box_online ? 1 : 2);
            }
            else if (settings::esp::box_type_index == 2) {
                fvector extend;
                fvector origin;
                actor->get_actor_bounds(true, false, &origin, &extend);
                box_3d(origin, extend + fvector(10, 10, 65), is_visible ? visible : invisble);
            }
        }
        if (settings::esp::player_name && actor_state) {



            auto name = actor_state->get_player_name();
            if (name.is_valid()) {
                int add_y = screen_head.y - 8;
                if (settings::esp::health_bar && settings::esp::health_bar_index == 0) {
                    add_y -= 16;
                }
                zero_gui::TextCenter2(name.c_str(), fvector2d(root_bone_out.x, add_y), flinearcolor(1, 1, 1, 1), true);

                unreal::free_memory(name.get_data());
            }


        }

        if (settings::esp::agent_esp && actor_state) {
            auto ui_data = actor_state->get_ui_data();

            if (ui_data) {
                uintptr_t utexture_display_icon_small = memory::read<uintptr_t>(ui_data + 0xa8);


                zero_gui::canvas->draw_texture(utexture_display_icon_small, fvector2d(root_bone_out.x - 12, screen_head.y - 32), fvector2d(24, 24), fvector2d(0, 0), fvector2d(1, 1), flinearcolor(1, 1, 1, 1), valorant::EBlendMode::BLEND_Translucent, 0, fvector2d(0.5, 0.5));
            }
        }

        if (settings::esp::snap_lines) {
            if (settings::esp::snaplines_pos_index == 0) {
                zero_gui::canvas->draw_line(fvector2d(cached::screen_width / 2, 0), fvector2d(root_bone_out.x, screen_head.y + box_height), 1, flinearcolor(255.0f, 255.0f, 255.0f, 1.0f));
            }
            else if (settings::esp::snaplines_pos_index == 1) {
                zero_gui::canvas->draw_line(fvector2d(cached::screen_width / 2, cached::screen_height / 2), fvector2d(root_bone_out.x, screen_head.y + box_height), 1, flinearcolor(255.0f, 255.0f, 255.0f, 1.0f));
            }
            else if (settings::esp::snaplines_pos_index == 2) {
                zero_gui::canvas->draw_line(fvector2d(cached::screen_width / 2, cached::screen_height), fvector2d(root_bone_out.x, screen_head.y + box_height), 1, flinearcolor(255.0f, 255.0f, 255.0f, 1.0f));
            }
        }
        if (settings::esp::health_bar) {
            if (settings::esp::health_bar_index == 1) {
                zero_gui::canvas->draw_health_bar(root_bone_out.x - (box_width / 2) - 6, screen_head.y, 1, box_height, health, 100, healthbar_color);

            }
            else if (settings::esp::health_bar_index == 0) {
                zero_gui::canvas->draw_health_bar(root_bone_out.x - (box_width / 2), screen_head.y - 5, box_width, 4, health, 100, healthbar_color);
            }
        }
        if (settings::esp::shield_bar) {
            if (settings::esp::health_bar_index == 1) {
                int x_minus = settings::esp::health_bar ? 11 : 6;
                zero_gui::canvas->draw_health_bar(root_bone_out.x - (box_width / 2) - x_minus, screen_head.y, 1, box_height, actor->get_shield(), 50, shieldbar_color);
            }
            else if (settings::esp::health_bar_index == 0) {
                int y_minus = settings::esp::health_bar ? 10 : 5;
                zero_gui::canvas->draw_health_bar(root_bone_out.x - (box_width / 2), screen_head.y - y_minus, box_width, 4, actor->get_shield(), 50, shieldbar_color);
            }
        }
        if (settings::esp::weapon_esp || settings::esp::weapon_ammo || settings::esp::weapon_icon) {
            auto current_inv = actor->get_inventory(); if (current_inv) {
                auto current_equip = current_inv->get_current_equippable();
                if (current_equip) {
                    if (settings::esp::weapon_esp) {
                        auto text = current_equip->get_item_name();
                        if (text.Data) {

                            auto converted_string = valorant::string::text_to_string(text);
                            if (converted_string.is_valid()) {
                                zero_gui::TextCenter2(converted_string.c_str(), fvector2d(root_bone_out.x, screen_head.y + box_height + 8), flinearcolor(1, 1, 1, 1), true);
                            }
                        }
                    }
                    if (settings::esp::weapon_ammo) {
                        auto magazine_ammo = memory::read<uintptr_t>(uintptr_t(current_equip) + 0x1008);

                        if (magazine_ammo) {
                            int ammo = memory::read<int>(magazine_ammo + 0x120);
                            int max_ammo = memory::read<int>(magazine_ammo + 0x140);

                            auto ammo_str = valorant::string::int_to_string(ammo);
                            //auto ammo_str = valorant::string::int_to_string(max_ammo);

                            auto finished_string = valorant::string::buildstring_int(ammo_str, L"/", max_ammo, L"");

                            zero_gui::TextCenter2(finished_string, fvector2d(root_bone_out.x, screen_head.y + box_height + 20), flinearcolor(1, 1, 1, 1), true);

                            unreal::free_memory(ammo_str.get_data());
                            unreal::free_memory(finished_string.get_data());
                        }
                    }
                    if (settings::esp::weapon_icon) {

                        uintptr_t weapon_icon = uintptr_t(current_equip->icon_());
                        if (weapon_icon) {

                            zero_gui::canvas->draw_texture(weapon_icon,
                                fvector2d(root_bone_out.x - 21, screen_head.y + box_height + 2),
                                fvector2d(42, 16),
                                fvector2d(0, 0),
                                fvector2d(1, 1),
                                flinearcolor(1, 1, 1, 1),
                                valorant::EBlendMode::BLEND_Translucent,
                                0,
                                fvector2d(0.5, 0.5));
                        }
                    }
                }
            }
        }
       
        if (settings::esp::head_dot) {
            zero_gui::canvas->draw_circle(screen_head.x, screen_head.y, 3, 12, flinearcolor(1, 1, 1, 1));
        }

        if (settings::esp::skeleton) {

            auto a = is_visible ? visibleskel : invisbleskel;

           

            fvector vNeck = actor_mesh->get_bone_location_v2(MaleBones::Neck, bone_array, c2w);
            fvector2d vNeckOut = cached::controller->cool_w2s(vNeck);

            fvector vUpperArmLeft = actor_mesh->get_bone_location_v2(MaleBones::L_Shoulder, bone_array, c2w);
            fvector2d vUpperArmLeftOut = cached::controller->cool_w2s(vUpperArmLeft);

            fvector vUpperArmRight = actor_mesh->get_bone_location_v2(MaleBones::R_Shoulder, bone_array, c2w);
            fvector2d vUpperArmRightOut = cached::controller->cool_w2s(vUpperArmRight);

            fvector vLeftHand = actor_mesh->get_bone_location_v2(MaleBones::L_Elbow, bone_array, c2w);
            fvector2d vLeftHandOut = cached::controller->cool_w2s(vLeftHand);

            fvector vRightHand = actor_mesh->get_bone_location_v2(MaleBones::R_Elbow, bone_array, c2w);
            fvector2d vRightHandOut = cached::controller->cool_w2s(vRightHand);

            fvector vLeftHand1 = actor_mesh->get_bone_location_v2(MaleBones::L_Hand, bone_array, c2w);
            fvector2d vLeftHandOut1 = cached::controller->cool_w2s(vLeftHand1);

            fvector vRightHand1 = actor_mesh->get_bone_location_v2(MaleBones::R_Hand, bone_array, c2w);
            fvector2d vRightHandOut1 = cached::controller->cool_w2s(vRightHand1);

            fvector vRightThigh = actor_mesh->get_bone_location_v2(82, bone_array, c2w);
            fvector2d vRightThighOut = cached::controller->cool_w2s(vRightThigh);

            fvector vLeftThigh = actor_mesh->get_bone_location_v2(75, bone_array, c2w);
            fvector2d vLeftThighOut = cached::controller->cool_w2s(vLeftThigh);

            fvector vRightCalf = actor_mesh->get_bone_location_v2(83, bone_array, c2w);
            fvector2d vRightCalfOut = cached::controller->cool_w2s(vRightCalf);

            fvector vLeftCalf = actor_mesh->get_bone_location_v2(76, bone_array, c2w);
            fvector2d vLeftCalfOut = cached::controller->cool_w2s(vLeftCalf);

            fvector vLeftFoot = actor_mesh->get_bone_location_v2(78, bone_array, c2w);
            fvector2d vLeftFootOut = cached::controller->cool_w2s(vLeftFoot);

            fvector vRightFoot = actor_mesh->get_bone_location_v2(85, bone_array, c2w);
            fvector2d vRightFootOut = cached::controller->cool_w2s(vRightFoot);

            fvector Pelvis = actor_mesh->get_bone_location_v2(3, bone_array, c2w);
            fvector2d PelvisOut = cached::controller->cool_w2s(Pelvis);

            zero_gui::canvas->draw_line(vNeckOut.x, vNeckOut.y, screen_head.x, screen_head.y, a, 1);
            zero_gui::canvas->draw_line(PelvisOut.x, PelvisOut.y, vNeckOut.x, vNeckOut.y, a, 1);

            zero_gui::canvas->draw_line(vUpperArmLeftOut.x, vUpperArmLeftOut.y, vNeckOut.x, vNeckOut.y, a, 1);
            zero_gui::canvas->draw_line(vUpperArmRightOut.x, vUpperArmRightOut.y, vNeckOut.x, vNeckOut.y, a, 1);

            zero_gui::canvas->draw_line(vLeftHandOut.x, vLeftHandOut.y, vUpperArmLeftOut.x, vUpperArmLeftOut.y, a, 1);
            zero_gui::canvas->draw_line(vRightHandOut.x, vRightHandOut.y, vUpperArmRightOut.x, vUpperArmRightOut.y, a, 1);

            zero_gui::canvas->draw_line(vLeftHandOut.x, vLeftHandOut.y, vLeftHandOut1.x, vLeftHandOut1.y, a, 1);
            zero_gui::canvas->draw_line(vRightHandOut.x, vRightHandOut.y, vRightHandOut1.x, vRightHandOut1.y, a, 1);

            zero_gui::canvas->draw_line(vLeftThighOut.x, vLeftThighOut.y, PelvisOut.x, PelvisOut.y, a, 1);
            zero_gui::canvas->draw_line(vRightThighOut.x, vRightThighOut.y, PelvisOut.x, PelvisOut.y, a, 1);

            zero_gui::canvas->draw_line(vLeftCalfOut.x, vLeftCalfOut.y, vLeftThighOut.x, vLeftThighOut.y, a, 1);
            zero_gui::canvas->draw_line(vRightCalfOut.x, vRightCalfOut.y, vRightThighOut.x, vRightThighOut.y, a, 1);
            zero_gui::canvas->draw_line(vLeftFootOut.x, vLeftFootOut.y, vLeftCalfOut.x, vLeftCalfOut.y, a, 1);
            zero_gui::canvas->draw_line(vRightFootOut.x, vRightFootOut.y, vRightCalfOut.x, vRightCalfOut.y, a, 1);



        }
        if (settings::esp::engine_radar) {
            auto portrait_map = memory::read<uintptr_t>(uintptr_t(actor) + offsets::portrait_map);
            if (portrait_map) {
                memory::write<bool>(portrait_map + offsets::is_visible, true);
                memory::write<bool>(portrait_map + offsets::local_observer, true);
            }
            auto character_map = memory::read<uintptr_t>(uintptr_t(actor) + offsets::character_map);
            if (character_map) {
                memory::write<bool>(character_map + offsets::is_visible, true);
                memory::write<bool>(character_map + offsets::local_observer, true);
            }
        }

        if (settings::esp::wireframe_esp) {
            auto a = memory::read<char>(uintptr_t(actor_mesh) + 0x71e) | (1 << 5);

            memory::write<char>(uintptr_t(actor_mesh) + 0x71e, a);
            memory::write<char>(uintptr_t(actor_mesh) + 0xc0, 0xff);
        }
    }


    if (settings::aimbot::aim_bot) {
        auto dx = screen_head.x - (cached::screen_width / 2);
        auto dy = screen_head.y - (cached::screen_height / 2);


        auto dist = crt::custom_sqrtf(dx * dx + dy * dy);

        if (dist < (settings::aimbot::aim_fov * 3 + 10) && dist < target_actor_distance) {
            target_actor_distance = dist;
            target_actor = actor;
            target_hitbox_id_closest = get_closest_hitbox(actor_mesh);
            target_offset = valorant::math::random_int(-2,1);
        }

        //if (dist < 13 && settings::triggerbot) {
        //    trigerr_actor = actor;
        //}
    }
}

auto actor_loop() -> void
{
    if (settings::debug) return;

    auto camera = (valorant::camera*)cached::controller->get_camera_manager(); if (!camera) return;

    //camera_cached::camera_location = camera->get_location();
    //camera_cached::camera_rotation = camera->get_rotation();
    //camera_cached::camera_fov_angle = camera->get_fov();


    //disable for legacy version
    if (camera_engine != uintptr_t(camera))
    {
        camera_engine = uintptr_t(camera);
        should_hook_gay = true;
    } if (!camera_engine) return;



    cached::local_pawn = cached::controller->get_pawn(); if (!cached::local_pawn) return;
    cached::local_mesh = cached::local_pawn->get_mesh(); if (!cached::local_mesh) return;

    auto loc_player_state = cached::local_pawn->get_player_state(); if (!loc_player_state) return;
    auto loc_team_component = loc_player_state->get_team_component(); if (!loc_team_component) return;
    auto loc_team_id = memory::read<uintptr_t>(uintptr_t(loc_team_component) + offsets::team_id);


    //if (settings::triggerbot) {
    //    auto scanned_actor = cached::local_pawn->simple_trace_from_camera();
    //
    //    if(scanned_actor->is_a(valorant::classes::shooter_character)) {
    //
    //        o_mouseevent(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    //        o_mouseevent(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    //    }
    //}

    auto game_state_base = memory::read<uintptr_t>(uintptr_t(cached::uworld) + offsets::game_state); if (!game_state_base) return;
    auto actors2 = memory::read<unreal::tarray<uintptr_t>>(game_state_base + offsets::PlayerArray); 
    
    
    if (actors2.is_valid()) {
        for (hack_int32_t i = 0; i < 12; i++)
        {
            auto actor_state = reinterpret_cast<valorant::player_state*>(actors2[i]); if (!actor_state) continue;
            auto actor = actor_state->spawned_character();

            if (!actor || actor == cached::local_pawn) continue;

            player_func(actor, loc_team_id, actor_state);
        }
    }

    if(settings::esp::master_switch_world) {
        auto objets_array = valorant::blueprint::find_all_game_objects(cached::uworld);

        for (hack_int32_t i = 0; i < objets_array.size(); i++)
        {
            auto actor = memory::read<valorant::actor*>(uintptr_t(objets_array.get_data()) + i * sizeof(uintptr_t));
          
            if (!actor) continue;

            auto name = valorant::system::get_object_name_v2(actor);
            auto c_name = valorant::system::get_object_class_name(actor);

            auto root_component = memory::read<uintptr_t>(uintptr_t(actor) + offsets::root_component); if (!root_component) continue;
            auto relative_location = memory::read<fvector>(root_component + offsets::relative_location);

            fvector2d rel_loc_w2s = cached::controller->cool_w2s(relative_location);

            zero_gui::canvas->text_wrapper_ooo(rel_loc_w2s + fvector2d(0, 14), flinearcolor(1, 1, 1, 1), true, c_name);
            zero_gui::canvas->text_wrapper_ooo(rel_loc_w2s + fvector2d(0, 28), flinearcolor(1, 1, 1, 1), true, name);

            if (actor->is_a(valorant::classes::shooter_equipable)) {
                if (settings::dropped_esp) {
                    auto actual_equippable = memory::read<valorant::equippable*>(uintptr_t(actor) + 0x518); //MyEquippable

                    if (settings::dropped_name) {
                        if (actual_equippable) {
                            auto text = actual_equippable->get_item_name();
                            if (text.Data) {

                                //auto converted_string = valorant::string::text_to_string(text);
                                //if (converted_string.is_valid()) {
                                    zero_gui::canvas->text_wrapper_ooo(rel_loc_w2s, flinearcolor(1, 1, 1, 1), true, text.get());
                                //}
                            }
                        }
                    }
                    if (settings::dropped_box) {

                        fvector extend;
                        fvector origin;
                        actor->get_actor_bounds(true, false, &origin, &extend);
                        box_3d(origin, fvector(60, 20, 20), flinearcolor(1, 1, 1, 1));
                    }
                }

            }
            else {
                if (settings::abilities_esp || settings::spike_esp || settings::spike_hud) {




                    if (settings::abilities_esp) {
                        if (valorant::string::contains(name, _(L"Turret_Deploy_C"))) {
                            zero_gui::canvas->text_wrapper_ooo(rel_loc_w2s, flinearcolor(1, 1, 1, 1), true, _(L"KJ Turret").decrypt());
                        }
                        else if (valorant::string::contains(name, _(L"Alarmbot_C"))) {
                            zero_gui::canvas->text_wrapper_ooo(rel_loc_w2s, flinearcolor(1, 1, 1, 1), true, _(L"KJ Alarm Bot").decrypt());
                        }
                        else if (valorant::string::contains(name, _(L"RemoteBees_MultiDetonate_C"))) {
                            zero_gui::canvas->text_wrapper_ooo(rel_loc_w2s, flinearcolor(1, 1, 1, 1), true, _(L"KJ Multi Detonate").decrypt());
                        }
                        else if (valorant::string::contains(name, _(L"Deadeye_E_Trap_C"))) {
                            zero_gui::canvas->text_wrapper_ooo(rel_loc_w2s, flinearcolor(1, 1, 1, 1), true, _(L"Chamber TRAP").decrypt());
                        }
                        else if (valorant::string::contains(name, _(L"Gumshoe_E_TripWire_C"))) {
                            zero_gui::canvas->text_wrapper_ooo(rel_loc_w2s, flinearcolor(1, 1, 1, 1), true, _(L"Cypher Tripwire").decrypt());
                        }
                        else if (valorant::string::contains(name, _(L"CageTrap_C"))) {
                            zero_gui::canvas->text_wrapper_ooo(rel_loc_w2s, flinearcolor(1, 1, 1, 1), true, _(L"Cypher CageTrap").decrypt());
                        }
                        else if (valorant::string::contains(name, _(L"PossessableCamera_C"))) {
                            zero_gui::canvas->text_wrapper_ooo(rel_loc_w2s, flinearcolor(1, 1, 1, 1), true, _(L"Cypher Camera").decrypt());
                        }
                        else {
                            zero_gui::canvas->text_wrapper_ooo(rel_loc_w2s, flinearcolor(1, 1, 1, 1), true, name);
                        }
                    }

                    if (settings::spike_esp) {
                        if (valorant::string::contains(name, _(L"TimedBomb_C"))) {
                            if (settings::spike_box) {
                                fvector extend;
                                fvector origin;
                                actor->get_actor_bounds(true, false, &origin, &extend);
                                box_3d(origin, fvector(50, 70, 50), flinearcolor(1, 1, 1, 1));
                            }
                            if (settings::spike_info) {
                                zero_gui::canvas->text_wrapper_ooo(rel_loc_w2s, flinearcolor(1, 1, 1, 1), true, _(L"BOMB").decrypt());

                                auto remaining_time = memory::read<float>(uintptr_t(actor) + 0x4e4);

                                auto translated = valorant::string::int_to_string(int(remaining_time));

                                zero_gui::canvas->text_wrapper_ooo(rel_loc_w2s + fvector2d(0, 12), flinearcolor(1, 1, 1, 1), true, translated);
                            }

                        }
                    }
                    unreal::free_memory(name.get_data());
                }
            }
        }
    }

    if (cached::local_pawn && cached::controller) {
        if (camera_engine == uintptr_t(camera) && should_hook_gay) {
            memory::vmt((void*)camera_engine, hk_update_view_target_internal, 0xF8, (void**)&o_update_view_target_internal);
            should_hook_gay = false;
        }


        if (target_actor && settings::aimbot::aim_bot) {
            if (target_actor->get_health() >= 1) {

                auto enemymesh = target_actor->get_mesh(); if (!enemymesh) return;

                auto enemyhead = enemymesh->get_bone_location(target_hitbox_id_closest) + fvector(0,0, target_offset);

                auto enemyheadw2s = cached::controller->cool_w2s(enemyhead);

                if (settings::aimbot::target_line && settings::esp::master_switch) {
                    zero_gui::canvas->draw_line(fvector2d(cached::screen_width / 2, cached::screen_height / 2), enemyheadw2s, 1, flinearcolor(255, 0, 0, 255));
                }





                if (cached::controller->is_input_key_down(settings::aimkey)) {
                    sdk::unreal::fvector asdadsa;
                    bool is_visible = settings::visible_check ? valorant::blueprint::can_player_see_player(cached::local_pawn, target_actor, false) : true;

                    auto dx = enemyheadw2s.x - (cached::screen_width / 2);
                    auto dy = enemyheadw2s.y - (cached::screen_height / 2);


                    auto dist = crt::custom_sqrtf(dx * dx + dy * dy);

                    bool checked = settings::aimbot::enable_deadzone ? dist < (settings::aimbot::deadzone_fov * 3 + 10) : false;
                    
                  
                    if (is_visible && !checked) {
                        fvector aimpos = calc_angle(camera_cached::camera_location, enemyhead);
                        aimpos.clamp();

                        if (settings::aimbot::rcs) {
                            recoil(aimpos, camera_cached::camera_rotation, settings::aimbot::aim_smooth);
                        }
                        else {
                            smooth(aimpos, camera_cached::camera_rotation, settings::aimbot::aim_smooth);
                        }


                    }
                    else {
                        target_actor_distance = FLT_MAX;
                        target_actor = 0;
                    }
                }
                else {
                    target_actor_distance = FLT_MAX;
                    target_actor = 0;
                }

            }
            else {
                target_actor_distance = FLT_MAX;
                target_actor = 0;
            }
        }

      

        if (settings::recoil_crosshair) {
            draw_recoil();
        }

        auto MeshOverlay1p = memory::read<uintptr_t>(uintptr_t(cached::local_pawn) + 0xc68);
        if (MeshOverlay1p) {
            if (settings::wireframe_hands)
            {
                auto a = memory::read<char>(MeshOverlay1p + 0x71e) | (1 << 3);

                memory::write<char>(MeshOverlay1p + 0x71e, a);
                memory::write<char>(MeshOverlay1p + 0xc0, 0xff);
            }
        }

        auto local_weapon = cached::local_pawn->get_inventory()->get_current_equippable();
        if (local_weapon) {

            //ZeroGUI::canvas->text_wrapper(fvector2d(10, 10), flinearcolor(255, 255, 255, 255), false, valorant::system::get_object_name_v2(local_weapon));

            if (weapn_cached != uintptr_t(local_weapon))
            {
                weapn_cached = uintptr_t(local_weapon);
                skinchanger::run(cached::uworld, cached::controller, local_weapon);
            }


            auto local_wep_mesh = local_weapon->mesh();
            auto local_wep_mesh3p = local_weapon->mesh_3p();

            
            if (settings::wireframe_weaapon) {
                auto a = memory::read<char>(uintptr_t(local_wep_mesh) + 0x71e) | (1 << 3);

                memory::write<char>(uintptr_t(local_wep_mesh) + 0x71e, a);
                memory::write<char>(uintptr_t(local_wep_mesh) + 0xc0, 0xff);

                auto b = memory::read<char>(uintptr_t(local_wep_mesh3p) + 0x71e) | (1 << 3);

                memory::write<char>(uintptr_t(local_wep_mesh3p) + 0x71e, b);
                memory::write<char>(uintptr_t(local_wep_mesh3p) + 0xc0, 0xff);
            }

            if (settings::big_weapon) {
                memory::write<fvector>(uintptr_t(local_wep_mesh3p) + 0x17c, fvector(3, 3, 3));
            }     
        }
    }
}

void hk_draw_transition(valorant::game_viewport_client* game_viewport, valorant::canvas* canvas) {



    if (canvas && game_viewport) {

        if (!valorant::classes::font) {
            valorant::classes::font = game_viewport->get_engine()->get_small_font();
            valorant::classes::medium_font = game_viewport->get_engine()->get_medium_font();
            valorant::classes::big_font = game_viewport->get_engine()->get_large_font();
        }

        if (!zero_gui::canvas) {
            zero_gui::setup_canvas(canvas);
        }
        cached::screen_width = canvas->getSizeX();
        cached::screen_height = canvas->getSizeY();
        
        cached::uworld = game_viewport->get_world(); if (!cached::uworld) return;

        auto owning_game_instance = (uintptr_t)game_viewport->get_game_instance(); if (!owning_game_instance) return;

        auto local_player = memory::read<uintptr_t>(memory::read<uintptr_t>(owning_game_instance + offsets::local_players)); if (!local_player) return;

        cached::controller = reinterpret_cast<valorant::controller*>(memory::read<uintptr_t>(local_player + offsets::player_controller)); if (!cached::controller) return;

     

        //static bool done = false;
        //if (cached::controller->is_a(valorant::classes::shooter_pregame_controller) && settings::insta_lock) {
        //    if (!done) {
        //        cached::controller->get_pregame_view_controller()->lock_character((uobject*)sdk::unreal::uobject::static_load_object(0, (uobject*)-1, L"Wushu", true));
        //        done = true;
        //    }
        //}

        menu_tick();

        if (settings::watermark) {
            auto size = zero_gui::canvas->strlen(valorant::classes::font, _(L"XENE - SLOTTED").decrypt());
            zero_gui::draw_filled_rect(fvector2d(cached::screen_width - size.x - 30, 10), size.x + 16, 22, flinearcolor(0,0,0,1));
            zero_gui::canvas->draw_line(fvector2d(cached::screen_width - size.x - 30, 10), fvector2d(cached::screen_width - 14, 10), 1, flinearcolor(0.27, 0.00, 0.43, 1));
            zero_gui::canvas->text_wrapper_ooo(fvector2d(cached::screen_width - size.x - 28, 12), flinearcolor(1,1,1,1), false, _(L"XENE - SLOTTED").decrypt());
        }

        if (settings::aimbot::draw_fov && settings::aimbot::aim_bot) canvas->draw_circle(cached::screen_width / 2, cached::screen_height / 2, settings::aimbot::aim_fov * 3 + 10, 32, fovcircle);
        if (settings::aimbot::enable_deadzone && settings::aimbot::aim_bot) canvas->draw_circle(cached::screen_width / 2, cached::screen_height / 2, settings::aimbot::deadzone_fov * 3 + 10, 32, deadzone_fovcircle);

        actor_loop();

        
    }

    return o_draw_transition(game_viewport, canvas);

   
}


static uobject* find_world_new() {
    const wchar_t* uworld_names[] = {
        L"/Game/Maps/Init/Init.Init",
        L"/Game/Maps/Menu/MainMenuV2.MainMenuV2",
        L"/Game/Maps/Poveglia/Range.Range", //range
        L"/Game/Maps/Poveglia/Poveglia.Poveglia", //island
        L"/Game/Maps/Ascent/Ascent.Ascent", //ascent
        L"/Game/Maps/Canyon/Canyon.Canyon", //fracture
        L"/Game/Maps/Bonsai/Bonsai.Bonsai", //split
        L"/Game/Maps/Duality/Duality.Duality", //bind
        L"/Game/Maps/Foxtrot/Foxtrot.Foxtrot", //breeze
        L"/Game/Maps/Port/Port.Port", //icebox
        L"/Game/Maps/Triad/Triad.Triad", //haven
        L"/Game/Maps/Pitt/Pitt.Pitt", //pearl
        L"/Game/Maps/Jam/Jam.Jam", //lotus
        L"/Game/Maps/Juliett/Juliett.Juliett", //sunset
        L"/Game/Maps/HURM/HURM_Yard/HURM_Yard.HURM_Yard", //piazza
        L"/Game/Maps/HURM/HURM_Alley/HURM_Alley.HURM_Alley", //district
        L"/Game/Maps/HURM/HURM_Bowl/HURM_Bowl.HURM_Bowl", //kasbah
        L"/Game/Maps/HURM/HURM_Helix/HURM_Helix.HURM_Helix", //drift
    };

    for (int i = 0; i < sizeof(uworld_names) / sizeof(wchar_t*); i++)
    {
        uobject* cache_uworld = uobject::find_object(uworld_names[i],
            reinterpret_cast<uobject*>(-1));

        if (cache_uworld)
            return cache_uworld;
    }
    return nullptr;
}

void c_main()
{

    cached::base_address  = memory::get_module_base(); if (!cached::base_address) return;
                                

    o_virtualalloc        = (PFN_VirtualAlloc)memory::get_proc_address(_("VirtualAlloc"));
    o_virtualfree         = (PFN_VirtualFree)memory::get_proc_address(_("VirtualFree"));
    o_virtualquery        = (VirtualQueryFunc)memory::get_proc_address(_("VirtualQuery"));

                            valorant::classes::initialize();

    auto uworld = find_world_new(); if (!uworld) {
        return;
    }
    auto gameinstance     = memory::read<uintptr_t>(uintptr_t(uworld) + offsets::owning_game_instance); if (!gameinstance) return;
    auto ee               = valorant::system::get_outer_object((uobject*)gameinstance); if (!ee) return;
    auto viewport_client  = memory::read<uintptr_t>((uintptr_t)ee + 0x8c0); if (!viewport_client) return;

    invisble = flinearcolor(255, 255, 255, 255);
    visible = flinearcolor(255, 255, 255, 255);
    invisbleskel = flinearcolor(255, 255, 255, 255);
    visibleskel = flinearcolor(255, 255, 255, 255);
    fovcircle = flinearcolor(255, 255, 255, 255);
    deadzone_fovcircle = flinearcolor(255, 0, 0, 255);
    recoilcrosshair = flinearcolor(255, 255, 255, 255);
    healthbar_color = flinearcolor(0, 1, 0, 1);
    shieldbar_color = flinearcolor(0, 0.9, 1, 1);

    settings::aimkey = valorant::classes::keys::XButton1;
    settings::masterswitch_esp = valorant::classes::keys::F9;
    settings::tpkey = valorant::classes::keys::F3;

    memory::vmt((void*)viewport_client, hk_draw_transition, 0x6A, (void**)&o_draw_transition);

}

