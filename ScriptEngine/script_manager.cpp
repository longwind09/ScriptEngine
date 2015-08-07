#include "stdafx.h"
#include "script_manager.h"
#include "EngineConfig.h"
#include "TextUtil.h"
#include "Script.h"
#include "DEngine.h"



script_manager::script_manager ( boost::shared_ptr<DEngine> pEng ) : pEngine ( pEng ), m_taskQueue(), m_worker ( m_taskQueue )
{

}


script_manager::~script_manager ( void )
{
}

void script_manager::load_scripts ( const string &scp_path )
{
    string scp_dir = scp_path + "\\";
    //luafunctions.txt
    string file_name = scp_dir + ( "luafunctions.txt" );
    FILE *fp = freopen ( file_name.c_str(), "r", stdin );
    
    if ( !fp ) return;
    
    std::string str_func, str_ent_ids;
    
    while ( std::cin >> str_func >> str_ent_ids )
    {
        boost::trim ( str_func );
        //*.lua
        string file_path = scp_dir + ( str_func + ".lua" );
        boost::shared_ptr<Script> pScript = load_script ( file_path, str_func );
        script_map.insert ( make_pair<string, boost::shared_ptr<Script>> ( str_func, pScript ) );
    }
    
    fclose ( fp );
}

void script_manager::init ( const EngineConfig &cfg )
{
    string script_path =  cfg.settings .at ( "script_path" );
    
    if ( script_path.length() == 0 )
    {
        cerr << ( "script_path is empty" );
        return;
    }
    else
    {
        load_scripts ( script_path );
    }
    
}

boost::shared_ptr<Script> script_manager::load_script ( const string &file_path, const string &entry )
{
    boost::shared_ptr<Script> pScript ( new Script ( file_path, entry ) );
    pScript->init ( pEngine.lock() );
    return pScript;
}

void script_manager::resume_script_by_name_async ( std::string script_name )
{
    boost::shared_ptr<Script> scp = script_map[script_name];
    
    if ( scp )
    {
        TextUtil::debug_info ( script_name + "in script_manager, async resuming" );
        async_call ( boost::bind ( &Script::resume, scp ) );
    }
}


void script_manager::run()
{
    m_worker.start();
}

void script_manager::async_call ( task_type task )
{
    m_taskQueue.push ( task );
}

void script_manager::yield_script_by_name ( std::string script_name )
{
    boost::shared_ptr<Script> scp = script_map[script_name];
    
    if ( scp ) scp->yield();
}

void script_manager::end_script_by_name ( std::string script_name )
{
    boost::shared_ptr<Script> scp = script_map[script_name];
    
    if ( scp ) scp->end();
}



void script_manager::register_paused_script ( std::string scp_name )
{

}

void script_manager::unregister_paused_script ( std::string scp_name )
{

}

void script_manager::pause_script ( std::string scr_name, unsigned int millli_delay )
{

}