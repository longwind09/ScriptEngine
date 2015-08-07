#include "StdAfx.h"
#include "entity_interface.h"
#include "vector3.h"
#include "TextUtil.h"

using namespace std;

entity_interface::entity_interface ()
{

}
entity_interface::~entity_interface( void )
{

}

void entity_interface::register_entity ( std::string entity_id, std::string script_name )
{

}

void entity_interface::unregister_entity ( std::string entity_id, std::string script_name )
{
}

void entity_interface::set_actor_move ( std::string id, vector3 v_end, double speed )
{

}

vector3 entity_interface::get_actor_position ( std::string id )
{
    return vector3 ( 0, 0, 0 );
}

std::string entity_interface::get_actor_action ( std::string role_id )
{
    return "get_actor_action";
}

void entity_interface::add_actor ( std::string id, vector3 position, vector3 rotation, vector3 scale, std::string action )
{

}

void entity_interface::complete_by_npcs()
{
    TextUtil::debug_info("complete_by_npcs");
}

void entity_interface::set_actor_action ( std::string id, std::string act, double vel, int delay )
{

}

void entity_interface::set_button_run ( std::string idx1, std::string idx2, double dis, int dir )
{

}

void entity_interface::set_valve_run ( std::string idx1, std::string idx2, double angle, double speed, int dir )
{

}

double entity_interface::get_valve_state ( std::string id )
{
    return 0.0;
}

int entity_interface::get_knob_state ( const std::string& id )
{
    return 1;
}

void entity_interface::attach_sub_entity ( std::string id, std::string bone, std::string meshname, int ms )
{

}

void entity_interface::detach_sub_entity ( std::string id, std::string bone, std::string meshname )
{

}

void entity_interface::set_common_entity_run ( std::string idx1, std::string idx2, vector3 goal, int ifTran, double speed )
{

}

void entity_interface::add_particle ( std::string idx1, std::string idx2, std::string pname, vector3 pos )
{

}

void entity_interface::set_particle_running ( std::string idx1, std::string idx2, double v1, double v2 )
{

}

void entity_interface::set_particle_velocity ( std::string idx1, std::string idx2, double v1, double v2, double speed1, double speed2 )
{

}

void entity_interface::set_particle_dir ( std::string idx1, std::string idx2, vector3 vec )
{

}

void entity_interface::add_textblock_onscreen ( std::string id, std::string name, int x, int y, int size, vector3 color, double a )
{

}

void entity_interface::show_text_onscreen ( std::string textname, std::string role_id, std::string text, double posx, double posy, int fsize, vector3 color, int delay )
{

}

void entity_interface::change_text_onscreen ( std::string textname, std::string text, int delay )
{

}

void entity_interface::delete_text_onscreen ( std::string textname, int delay )
{



}

void entity_interface::set_common_entity_pos ( std::string idx1, std::string idx2, vector3 goal )
{

}

void entity_interface::set_particle_run ( std::string idx1, std::string idx2, bool flag )
{

}

void entity_interface::set_entity_position ( std::string idx1, std::string idx2, vector3 vec , int delayTime )
{

}

void entity_interface::set_entity_scale ( const std::string& idx1, const std::string& idx2, double scale )
{

}

void entity_interface::set_entity_rotation ( const std::string& idx1, const std::string& idx2, vector3 rotation )
{

}

void entity_interface::set_water_face_move ( std::string idx1, std::string idx2, vector3 goal, double speed, int ifTransient , int delayTime )
{

}

void entity_interface::set_knob_turn ( const std::string& idx1,
                                     const std::string& idx2,
                                     double angle )
{

}

void entity_interface::start_alarm_flicker ( std::string idx1, std::string idx2, int frameCount , int delayTime )
{



}

void entity_interface::end_alarm_flicker ( std::string idx1, std::string idx2 , int delayTime )
{

}

void entity_interface::add_one_music ( std::string idx, std::string MusicPath, double Volume, int IfLoop, std::string script_to_notify, std::string clientid, int delayTime )
{

}

void entity_interface::stop_all_music()
{

}

bool entity_interface::check_actor_equipment ( std::string id, std::string equipment_name )
{
    return false;
}

bool entity_interface::check_particle_running ( const std::string& par_id )
{
    return false;
}

void entity_interface::move_camera_to_goal ( std::string id, vector3 vec, double speed, int ifTransient, int delay )
{

}

void entity_interface::send_operation ( std::string role_id, std::string op_id )
{

}

void entity_interface::add_door_switch ( std::string idx1, std::string idx2, std::string mesh, vector3 pos, vector3 scl, vector3 rot )
{

}

void entity_interface::set_door_switch_run ( std::string idx1,
        std::string idx2,
        double ang,
        double speed,
        int dir )
{

}

void entity_interface::add_hydrant ( std::string idx1, std::string idx2,
                                   std::string body_mesh,
                                   std::string spanner_mesh,
                                   std::string pipe_mesh,
                                   vector3 position,
                                   vector3 scale,
                                   vector3 rotation )
{

}

void entity_interface::set_hydrant_pipe ( std::string idx1, std::string idx2,
                                        vector3 orig, vector3 dest )
{

}

void entity_interface::set_hydrant_span ( std::string idx1, std::string idx2,
                                        int is_spanning )
{

}

void entity_interface::set_camera_lookat ( const std::string& id, const vector3& goal, int delay )
{

}

void entity_interface::set_human_camera ( const std::string& human_id, const vector3& goal )
{

}

void entity_interface::send_operation_progress (
    const std::string& idx1, const std::string& idx2,
    const std::string& human_id, int is_completed )
{

}

void entity_interface::send_all_operation_info()
{


}

void entity_interface::set_actors_speedup ( double acceleration )
{

}

void entity_interface::set_handle_user_input (
    const std::string& role_id,
    int is_handled,
    const std::string& scp_name,
    int delay_time )
{

}

void entity_interface::show_question (
    const std::string& role_id, const std::string& ques_id, int flag )
{

}

void entity_interface::send_ui_info ( const std::string& info, unsigned int level )
{

}

void entity_interface::get_route_info ( const std::string& role_id,
                                      const vector3& current_point,
                                      const vector3& next_point,
                                      double distance )
{

}

void entity_interface::set_rectangle ( const std::string& role_id, int flag )
{

}

/*
void entity_interface::show_package(const std::string& role_id) {
  boost::shared_ptr<protobuf::Message> msg;
  msg.type = msg_type::show_package;
  msg.id = role_id;
  //msg.strings =
}*/

void entity_interface::set_actor_position (
    const std::string& role_id, const vector3& dest, int flag )
{

}

void entity_interface::set_positioning_radius ( const std::string& role_id, double radius )
{

}

void entity_interface::carry_stretcher (
    const std::string& role_id1, const vector3& dest1,
    const std::string& role_id2, const vector3& dest2,
    const std::string& role_id3, const vector3& dest3 )
{

}

void entity_interface::set_tricycle_door_open ( const std::string& idx1, const std::string& idx2, int is_left, int is_open )
{

}

void entity_interface::set_entity_combine (
    const std::string& ent1, const std::string& ent2,
    const vector3& dis, const vector3& angle, int is_combined )
{

}


