#pragma once
#include "stdafx.h"
using namespace std;

using namespace luabind;
class inference_engine;
class script_manager;
class entity_interface;
class DEngine;


class Script : public boost::enable_shared_from_this<Script>
{
  public:
    Script ( void );
    Script ( const string &file_path, const string &entry );
    ~Script ( void );
    
    void init ( boost::shared_ptr<DEngine> pEngine );
    void register_debug();
    
    void register_c_apis();
    
    //pEntInf entityInteface
    void register_global ( boost::shared_ptr<inference_engine> pStateMgr,
                           boost::shared_ptr<script_manager> pScriptMgr,
                           boost::shared_ptr<entity_interface> pEntIntf );
                           
                           
    /************************************************************************/
    /*
            lua debug
    */
    /************************************************************************/
    static int pcall_callback_err_fun(lua_State* L);
    //////////////////////////////////////////////////////////////////////////
    
    
    void resume();
    int yield();
    void end();
    
    
    
    
    lua_State *child_state;
    boost::mutex lua_state_mutex;
    bool ended;
    
    luabind::object myobj;
    std::string file_name;//"xxx.lua"
    std::string entry_function;//"xxx"
    std::string file_path;
    
};

