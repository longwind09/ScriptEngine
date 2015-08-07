#include "stdafx.h"
#include "Script.h"
#include "inference_engine.h"
#include "script_manager.h"
#include "entity_interface.h"
#include "DEngine.h"
#include "vector3.h"
#include "TextUtil.h"

Script::Script ( void )
{
}

Script::Script ( const string &filePath, const string &entry ) : file_path ( filePath ), entry_function ( entry )
{
    child_state = NULL;
}


Script::~Script ( void )
{
}

void Script::init ( boost::shared_ptr<DEngine> pEngine )
{
    ended = false;
    child_state = luaL_newstate();
    luaL_openlibs ( child_state );
    open ( child_state );
    register_c_apis();
    register_global ( pEngine->pStateMgr, pEngine->pScriptMgr, pEngine->pEntIntf );
    register_debug();
    string file_name = file_path;
   // TextUtil::replace_all_distinct ( file_name, "\\", "\\\\" );
    int ret = luaL_dofile ( child_state, const_cast<char*> ( file_name.c_str() )  );
    
    if ( ret != 0 )
    {
        string error_info = "luaL_dofile error with file " + file_path;
        TextUtil::debug_info ( error_info );
        throw new std::exception ( error_info.c_str() );
    }
}

void Script::register_c_apis()
{
    module ( child_state )
    [
        class_<vector3> ( "vector3" )
        .def ( constructor<double, double, double>() )
        .def_readwrite ( "x", &vector3::x )
        .def_readwrite ( "y", &vector3::y )
        .def_readwrite ( "z", &vector3::z )
        .def ( self == vector3() )
    ];
    module ( child_state )
    [
        class_<entity_interface> ( "entity_interface" )
        //def ( constructor<>() ) //opt
        .def ( "register_entity", &entity_interface::register_entity )
        .def ( "unregister_entity", &entity_interface::unregister_entity )
        .def ( "complete_by_npcs", &entity_interface::complete_by_npcs )
        .def ( "set_actor_move", &entity_interface::set_actor_move )
        .def ( "get_actor_position", &entity_interface::get_actor_position )
        .def ( "set_actor_action", &entity_interface::set_actor_action )
        .def ( "get_actor_action", &entity_interface::get_actor_action )
        .def ( "set_button_run", &entity_interface::set_button_run )
        .def ( "set_valve_run", &entity_interface::set_valve_run )
        .def ( "get_valve_state", &entity_interface::get_valve_state )
        .def ( "set_knob_turn", &entity_interface::set_knob_turn )
        .def ( "get_knob_state", &entity_interface::get_knob_state )
        .def ( "attach_sub_entity", &entity_interface::attach_sub_entity )
        .def ( "detach_sub_entity", &entity_interface::detach_sub_entity )
        .def ( "set_common_entity_run", &entity_interface::set_common_entity_run )
        .def ( "set_common_entity_pos", &entity_interface::set_common_entity_pos )
        .def ( "add_particle", &entity_interface::add_particle )
        .def ( "set_particle_running", &entity_interface::set_particle_running )
        .def ( "set_particle_run", &entity_interface::set_particle_run )
        .def ( "set_particle_velocity", &entity_interface::set_particle_velocity )
        .def ( "set_particle_direction", &entity_interface::set_particle_dir )
        .def ( "show_text_onscreen", &entity_interface::show_text_onscreen )
        .def ( "change_text_onscreen", &entity_interface::change_text_onscreen )
        .def ( "delete_text_onscreen", &entity_interface::delete_text_onscreen )
        .def ( "set_entity_position", &entity_interface::set_entity_position )
        .def ( "set_entity_rotation", &entity_interface::set_entity_rotation )
        .def ( "set_water_face_move", &entity_interface::set_water_face_move )
        .def ( "start_alarm_flicker", &entity_interface::start_alarm_flicker )
        .def ( "end_alarm_flicker", &entity_interface::end_alarm_flicker )
        .def ( "add_one_music", &entity_interface::add_one_music )
        .def ( "stop_all_music", &entity_interface::stop_all_music )
        .def ( "check_actor_equipment", &entity_interface::check_actor_equipment )
        .def ( "check_particle_running", &entity_interface::check_particle_running )
        .def ( "move_camera_to_goal", &entity_interface::move_camera_to_goal )
        .def ( "send_operation", &entity_interface::send_operation )
        .def ( "show_question", &entity_interface::show_question )
        //added on 2013/08/08
        .def ( "add_door_switch", &entity_interface::add_door_switch )
        .def ( "set_door_switch_run", &entity_interface::set_door_switch_run )
        .def ( "add_hydrant", &entity_interface::add_hydrant )
        .def ( "set_hydrant_pipe", &entity_interface::set_hydrant_pipe )
        .def ( "set_hydrant_span", &entity_interface::set_hydrant_span )
        .def ( "set_camera_lookat", &entity_interface::set_camera_lookat )
        .def ( "set_human_camera", &entity_interface::set_human_camera )
        .def ( "send_all_operation_info", &entity_interface::send_all_operation_info )
        .def ( "send_operation_progress", &entity_interface::send_operation_progress )
        .def ( "set_actors_speedup", &entity_interface::set_actors_speedup )
        .def ( "set_handle_user_input", &entity_interface::set_handle_user_input )
        .def ( "get_route_info", &entity_interface::get_route_info )
        .def ( "set_rectangle", &entity_interface::set_rectangle )
        .def ( "set_actor_position", &entity_interface::set_actor_position )
        .def ( "set_positioning_radius", &entity_interface::set_positioning_radius )
        .def ( "set_entity_scale", &entity_interface::set_entity_scale )
        .def ( "carry_stretcher", &entity_interface::carry_stretcher )
        .def ( "set_tricycle_door_open", &entity_interface::set_tricycle_door_open )
        .def ( "set_entity_combine", &entity_interface::set_entity_combine )
    ];
    module ( child_state )
    [
        class_<inference_engine> ( "inference_engine" )
        .def ( constructor<boost::shared_ptr<script_manager>>() ) //opt
        .def ( "state_work_done", &inference_engine::state_work_done )
        .def ( "add_fact", &inference_engine::add_fact )
    ];
    module ( child_state )
    [
        class_<script_manager> ( "script_manager" )
        .def ( constructor<boost::shared_ptr<DEngine>>() ) //opt
        .def ( "end_script_by_name", &script_manager::end_script_by_name )
        .def ( "register_paused_script", &script_manager::register_paused_script )
        .def ( "unregister_paused_script", &script_manager::unregister_paused_script )
        .def ( "pause_script", &script_manager::pause_script )
    ];
}


void Script::register_global ( boost::shared_ptr<inference_engine> pStateMgr, boost::shared_ptr<script_manager> pScriptMgr, boost::shared_ptr<entity_interface> pEntIntf )
{
    luabind::object global_table = luabind::globals ( child_state );
    
    global_table["entity_interface"] = pEntIntf;
    global_table["script_manager"] = pScriptMgr;
    global_table["inference_engine"] = pStateMgr;
}



void Script::resume()
{
    if ( ended ) return;
    
    static bool started = false;
    boost::mutex::scoped_lock lock ( lua_state_mutex );
    
    TextUtil::debug_info ( entry_function + "in script, resuming lua script" );
    
    if ( !started )
    {
        started = true;
        luabind::resume_function<void> ( child_state, const_cast<char*> ( entry_function.c_str() ) );
    }
    
    else
    {
        luabind::resume_function<void> ( child_state, const_cast<char*> ( entry_function.c_str() ) );
    }
}

int Script::yield()
{
    return lua_yield ( child_state, 0 );
}

void Script::end()
{
    ended = true;
}

int Script::pcall_callback_err_fun ( lua_State* L )
{
    lua_Debug debug;
    lua_getstack ( L, 2, &debug );
    lua_getinfo ( L, "Sln", &debug );
    
    std::string err = lua_tostring ( L, -1 );
    lua_pop ( L, 1 );
    std::stringstream msg;
    msg << debug.short_src << ": line " << debug.currentline;
    
    if ( debug.name != 0 )
    {
        msg << " ( " << debug.namewhat << " " << debug.name << " ) ";
    }
    
    msg << " [" << err << "]";
    lua_pushstring ( L, msg.str().c_str() );
    TextUtil::debug_info ( msg.str() );
    return 1;
}

void Script::register_debug()
{
    luabind::set_pcall_callback ( &pcall_callback_err_fun );
}
