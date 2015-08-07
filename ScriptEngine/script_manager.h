#pragma once

#include "stdafx.h"
#include "TaskQueue.h"
#include "worker.h"

using namespace std;

class EngineConfig;
class Script;
class inference_engine;
class DEngine;



class script_manager: public boost::enable_shared_from_this<script_manager>
{
  public:
  
    /************************************************************************/
    /*   �������ͣ������ں����ص�
         ������У����ص�����
    */
    /************************************************************************/
    typedef boost::function<void() > task_type;
    typedef TaskQueue<task_type> queue_type;
    //////////////////////////////////////////////////////////////////////////
    
    
    script_manager ( boost::shared_ptr<DEngine> pEngine );
    ~script_manager ( void );
    
    void init ( const EngineConfig &cfg );
    
    void load_scripts ( const string &scp_path );
    
    boost::shared_ptr<Script> load_script ( const string &file_path, const string &entry );
    void resume_script_by_name_async ( std::string script_name );
    void yield_script_by_name ( std::string script_name );
    void end_script_by_name ( std::string script_name );

    void register_paused_script ( std::string scp_name ); //push->list
    void unregister_paused_script ( std::string scp_name ); //list.remove(erase);
    void pause_script ( std::string scr_name, unsigned int millli_delay );

    
    //run worker
    void run();
    void async_call ( task_type task ); //ie. push��queue
    
    
    boost::weak_ptr<DEngine> pEngine;
    
    /************************************************************************/
    /* �������
    */
    /************************************************************************/
    queue_type m_taskQueue;
    Worker<queue_type> m_worker;
    //////////////////////////////////////////////////////////////////////////
    
    //lua_State *master_state;
    //boost::mutex master_state_mutex;
    
    ////scripts����
    //std::vector<boost::shared_ptr<Script>> script_vec;
    //boost::mutex scripts_mutex;
    
    //ͨ��Script�����ļ�::�������ҵ�Script
    std::map<std::string, boost::shared_ptr<Script>> script_map;//"xxx.lua::xxx" -> Script
    boost::mutex script_map_mutex;
    
    ////ͨ��entity_id�ҵ�Script
    //std::multimap<std::string, boost::weak_ptr<Script>> entity_id_map;
    //boost::mutex entity_id_map_mutex;
    //
    ////ͨ��function_name�ҵ�Script
    //std::map<std::string, boost::weak_ptr<Script>> function_map;
    //boost::mutex function_map_mutex;
    
};

