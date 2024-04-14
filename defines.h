#pragma once


namespace cached
{
    uintptr_t base_address = 0;
    int screen_width;
    int screen_height;
}

namespace settings
{
    namespace aimbot {
        bool aim_bot = true;

        bool standalone_rcs = false;
        bool no_spread = false;
        bool rcs = true;

        bool auto_aim_shoot = false;
        bool silent_aim = false;

        int aim_fov = 30;
        int aim_smooth = 3;


        bool enable_deadzone = false;
        int deadzone_fov = 10;

        bool head_enabled = true;
        bool body_enabled = false;
        bool legs_enabled;

        bool target_line = false;
        bool draw_fov = true;
    }

    bool triggerbot = false;
    bool triggerbot_on_key = true;
  
    namespace esp {


        bool master_switch = true;
        bool master_switch_world = false;

        bool player_name = false;
        bool agent_esp = false;
        bool health_bar = false;
        bool shield_bar = false;
        bool snap_lines = false;

        bool wireframe_esp = false;
        bool weapon_esp = false;
        bool weapon_icon = false;
        bool weapon_ammo = false;
        bool head_dot = false;
        bool view_angle = false;
        bool skeleton = false;
        bool box_esp = false;
        bool box_online = false;
        bool fill_box = false;
        bool engine_radar = false;
        bool dormant_esp = false;

        int box_type_index = 0;
        int health_bar_index = 0;
        int snaplines_pos_index = 0;

    }
    


    float rcs_x = 1;
    float rcs_y = 1;


  

    bool insta_lock = false;
    int instalock_index = 0;
    bool third_person = false;
    bool fast_crouch = false;
    bool migdet_mode = false;
    bool spin_bot = false;
    bool change_fov = false;
    bool dtm = false;
    bool visible_check = true;
    bool spectators = false;
    bool watermark = false;
    bool hands_glow = true;
    bool big_weapon = false;
    bool colorful_wepaon = false;
    bool recoil_crosshair = false;
    bool bunnyhop = false;
    bool wireframe_hands = false;
    bool wireframe_weaapon = false;

    bool abilities_esp = false;
    bool dropped_esp = false;
    bool spike_esp = false;
    bool spike_hud = false;

    bool dropped_name = false;
    bool dropped_box = false;

    bool spike_box = false;
    bool spike_info = false;

    float fov_value = 100;
    int chams_value = 5;

    bool debug = false;

}

namespace offsets {
    //Game
    uintptr_t uworld_state = 0xA6F1F00;
    
    uintptr_t process_event = 0x4198EA0;
    uintptr_t static_find_object = 0x41AD4E0;
    uintptr_t static_load_object = 0x41ADF90;
    uintptr_t skin_changer_decrypt = 0x2EF53A0;

    uintptr_t memory_free = 0x3DA8300;

    // World
    uintptr_t persistent_level = 0x38;                  // @uworld (ULevel)
    uintptr_t owning_game_instance = 0x1a0;                 // @uworld (UGameInstance)    
    uintptr_t game_state = 0x140;                 // @uworld (AGameStateBase)

        // Game State
    uintptr_t PlayerArray = 0x3f0;                  // @game_instance (TArray<struct ULocalPlayer*>)

    //ULevel
    uintptr_t actor_array = 0xA0; // world > persistent_level > actor_array

    // Game Instance
    uintptr_t local_players = 0x40;                  // @game_instance (TArray<struct ULocalPlayer*>)

     // Local Player
    uintptr_t viewport_client = 0x78;                  // @local_player (UGameViewportClient)
    uintptr_t player_controller = 0x38;                  // @local_player (APlayerController) 

    // Player Controller
    uintptr_t acknowledged_pawn = 0x468;                 // @player_controller (APawn)
    uintptr_t player_camera = 0x480;                 // @player_controller (APlayerCameraManager)
    uintptr_t control_rotation = 0x440;                 // @player_controller (FRotator)

    // Player Pawn
    uintptr_t root_component = 0x238;                 // @player_pawn (USceneComponent)
    uintptr_t damage_handler = 0xA08;                 // @player_pawn (UDamageableComponent)
    uintptr_t actor_id = 0x18;                  // @player_pawn (int)
    uintptr_t fname_id = 0x38;                  // @player_pawn (int)
    uintptr_t player_state = 0x3f8;                 // @player_pawn (APlayerState)
    uintptr_t current_mesh = 0x438;                 // @player_pawn (USkeletalMeshComponent)
    uintptr_t inventory = 0x9a8;                 // @player_pawn (UAresInventory)
    uintptr_t outline_component = 0x11D0;                // @player_pawn (UAresOutlineComponent)
    uintptr_t portrait_map = 0x1188;                // @player_pawn (UCharacterPortraitMinimapComponent_C)
    uintptr_t character_map = 0x1180;    // @player_pawn (UShooterCharacterMinimapComponent_C)

    uintptr_t max_shield = 0xde8;                 // @damage_handler (float)
    // Inventory
    uintptr_t current_equippable = 0x248;                 // @inventory (AAresEquippable)

    // Minimap Component
    uintptr_t local_observer = 0x530;                 // @player_pawn (bool)
    uintptr_t is_visible = 0x501;                 // @player_pawn (bool)

    uintptr_t dormant = 0x100;

    // Mesh
    uintptr_t component_to_world = 0x250;                 // @mesh (FTransform)
    uintptr_t bone_array = 0x5D8;                 // @mesh (FBoxSphereBounds)
    uintptr_t bone_count = bone_array + 0x8;      // @mesh (int)
    uintptr_t last_sub_time = 0x378;
    uintptr_t last_render_time = last_sub_time + 0x4;   // @mesh + (last_sub_time + 0x4) 
    uintptr_t outline_mode = 0x330;                 // @mesh (int)
    uintptr_t attach_children = 0x110;                 // @mesh (TArray<struct UMesh*>)
    uintptr_t attach_children_count = attach_children + 0x8; // @mesh (int)

    // Player State
    uintptr_t team_component = 0x630;                 // @player_state (UBaseTeamComponent)

    // Team Component
    uintptr_t team_id = 0xF8;                  // @team_component (int)

    // Damage Handler               
    uintptr_t current_health = 0x1B0;                 // @damage_handler (float)

    uintptr_t max_life = current_health + 0x4;  // @damange_handler + (current_health + 0x4)
    
    // Root Component
    uintptr_t relative_location = 0x164;                 // @root_component (FVector)
    uintptr_t relative_rotation = 0x170;                 // @root_component (FRotator)


}