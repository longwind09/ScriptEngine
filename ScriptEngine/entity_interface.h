#pragma once


#include "stdafx.h"




class vector3;
using namespace std;

class entity_interface
{
  public:
    entity_interface ( void );
    ~entity_interface ( void );
    
    std::string get_role_ent_id ( std::string role_type );
    
    void register_entity ( std::string entity_id, std::string script_name );
    void unregister_entity ( std::string entity_id, std::string script_name );
    
    void send_instruction_by_id ( std::string id, std::string instr );
    void add_actor ( std::string id, vector3 position, vector3 rotation, vector3 scale, std::string action );
    void complete_by_npcs();
    void set_actor_move ( std::string id, vector3 v_end, double speed );
    vector3 get_actor_position ( std::string id );
    bool check_actor_equipment ( std::string id, std::string equipment_name );
    bool check_particle_running ( const std::string& par_id );
    std::string get_actor_action ( std::string role_id );
    
    // �������------------------------------------------------------------------
    //�������ﶯ��
    void set_actor_action ( std::string id, std::string act, double vel, int delay );
    
    // ��Ա����
    void set_actors_speedup ( double acceleration );
    
    // ����˲��
    void set_actor_position ( const std::string& role_id, const vector3& dest, int flag );
    
    void attach_sub_entity ( std::string id, std::string bone, std::string meshname, int ms = 0 );
    void detach_sub_entity ( std::string id, std::string bone, std::string meshname );
    // --------------------------------------------------------------------------
    
    //button
    void set_button_run ( std::string idx1, std::string idx2, double dis, int dir );
    
    //valve
    void set_valve_run ( std::string idx1, std::string idx2, double angle, double speed, int dir );
    double get_valve_state ( std::string id );
    
    // knob
    void set_knob_turn ( const std::string& idx1, const std::string& idx2, double angle );
    int get_knob_state ( const std::string& id );
    
    //common entity
    void set_common_entity_run ( std::string idx1, std::string idx2, vector3 goal, int ifTran, double speed );
    void set_common_entity_pos ( std::string idx1, std::string idx2, vector3 goal );
    
    //particle
    void add_particle ( std::string idx1, std::string idx2, std::string pname, vector3 pos );
    void set_particle_running ( std::string idx1, std::string idx2, double v1, double v2 );
    void set_particle_run ( std::string idx1, std::string idx2, bool flag );
    void set_particle_velocity ( std::string idx1, std::string idx2, double v1, double v2, double speed1, double speed2 );
    void set_particle_dir ( std::string idx1, std::string idx2, vector3 vec );
    
    //text a  ����ô��
    void add_textblock_onscreen ( std::string id, std::string name, int x, int y, int size, vector3 color, double a );
    void show_text_onscreen ( std::string textname,
                              std::string role_id,
                              std::string text,
                              double posx,
                              double posy,
                              int fsize,
                              vector3 color,
                              int delay );
    void change_text_onscreen ( std::string textname, std::string text, int delay );
    void delete_text_onscreen ( std::string textname, int delay = 0 );
    
    // entity
    void set_entity_position ( std::string idx1, std::string idx2, vector3 vec, int delayTime );
    
    // ����ģ�ʹ�С
    void set_entity_scale ( const std::string& idx1, const std::string& idx2, double scale );
    
    // ������ģ�Ͱ󶨣��ֱ�������ʹӶ���
    /* @param ent1 ������ĸ�������
       @param ent2 ������ĸ�������
       @param dis ��ģ�ͼ����
       @param angle ģ�ͼ���ԽǶ�
       @param �Ƿ�󶨣� 1�󶨣�0��� */
    
    void set_entity_combine ( const std::string& ent1, const std::string& ent2,
                              const vector3& dis, const vector3& angle, int is_combined );
                              
    // ʵ����ת
    void set_entity_rotation ( const std::string& idx1, const std::string& idx2, vector3 rotation );
    
    void set_water_face_move ( std::string idx1, std::string idx2, vector3 goal, double speed, int ifTransient, int delayTime );
    
    // ---------------------------------����װ��---------------------------------
    void start_alarm_flicker ( std::string idx1, std::string idx2, int frameCount, int delayTime );
    
    void end_alarm_flicker ( std::string idx1, std::string idx2, int delayTime );
    
    // ���ͣ����
    void add_door_switch ( std::string id, std::string idx, std::string mesh,
                           vector3 pos, vector3 scl, vector3 rot );
                           
    // ͣ�����˶�
    void set_door_switch_run ( std::string id, std::string idx,
                               double ang, double speed, int dir );
                               
    // �������˨
    void add_hydrant ( std::string id, std::string idx,
                       std::string body_mesh,
                       std::string spanner_mesh, std::string pipe_mesh,
                       vector3 position, vector3 scale, vector3 rotation );
                       
    void set_hydrant_pipe ( std::string id, std::string idx, vector3 orig, vector3 dest );
    
    void set_hydrant_span ( std::string id, std::string idx, int is_spanning );
    
    // �򿪻�ر����ֳ���
    // @param side 1 for the left door, 0 for the right door
    void set_tricycle_door_open ( const std::string& id, const std::string& idx,
                                  int is_left, int is_open );
                                  
    //---------------------------------------------------------------------------
    
    // -------------------------------------camera-------------------------------
    // �������������
    void set_camera_lookat ( const std::string& id, const vector3& goal, int delay );
    
    // �������������
    void set_human_camera ( const std::string& human_id, const vector3& goal );
    
    void move_camera_to_goal ( std::string id, vector3 vec, double speed, int ifTransient, int delay );
    // --------------------------------------------------------------------------
    
    //added by Wu at 2013/5/5
    void add_one_music ( std::string idx, std::string MusicPath, double Volume, int IfLoop, std::string script_to_notify, std::string clientid, int delayTime );
    void stop_all_music();
    
    void send_operation ( std::string role_id, std::string op_id );
    
    //@param flag if show hint or not
    void show_operation ( const std::string& role_id, int flag );
    
    // �������в�����Ϣ
    void send_all_operation_info();
    
    // ��������
    void send_operation_progress ( const std::string& idx1, const std::string& idx2,
                                   const std::string& human_id, int is_completed );
                                   
    // 1�����û����룬0�����û�����
    void set_handle_user_input ( const std::string& role_id, int is_handled,
                                 const std::string& scp_name, int delay_time );
                                 
    // �ͻ�����ʾ��Ŀ
    void show_question ( const std::string& role_id, const std::string& ques_id, int flag );
    
    // server_ui��ʾ��Ϣ, ������Ϣ����Ϣ�ȼ�
    void send_ui_info ( const std::string& info, unsigned int level );
    
    // ��Ա��λ������Ϣ
    void get_route_info ( const std::string& role_id,
                          const vector3& current_point,
                          const vector3& next_point,
                          double distance );
                          
    // ���þ�������1���ã�0������
    void set_rectangle ( const std::string& role_id, int flag );
    
    // ��λ���뾶
    void set_positioning_radius ( const std::string& role_id, double radius );
    
    // ̧����
    void carry_stretcher ( const std::string& role_id1, const vector3& dest1,
                           const std::string& role_id2, const vector3& dest2,
                           const std::string& role_id3, const vector3& dest3 );
};

